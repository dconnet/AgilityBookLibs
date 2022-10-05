/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief UUID class
 *
 * Revision History
 * 2022-10-05 Created
 */

#include "stdafx.h"
#include "ARBCommon/UniqueId.h"

#include <sstream>

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>
#endif

#ifdef __WXMSW__
#include <rpcdce.h>
#pragma comment(lib, "rpcrt4.lib")
#endif


namespace dconSoft
{
namespace ARBCommon
{

class CUniqueIdImpl
{
public:
	CUniqueIdImpl()
	{
	}
	CUniqueIdImpl(CUniqueIdImpl const& rhs)
	{
	}
	virtual ~CUniqueIdImpl()
	{
	}
	virtual bool Create()
	{
		return false;
	}
	virtual CUniqueIdImpl* Clone() const
	{
		return new CUniqueIdImpl();
	}
	virtual bool IsNull() const
	{
		return true;
	}
	virtual void Assign(CUniqueIdImpl const* rhs)
	{
	}
	virtual bool IsEqual(CUniqueIdImpl const* rhs) const
	{
		return true;
	}
	virtual bool IsLessThan(CUniqueIdImpl const* rhs) const
	{
		return false;
	}
	virtual std::wstring ToString() const
	{
		// Make sure any new platform always returns lower-case for consistency.
		return L"00000000-0000-0000-0000-000000000000";
	}
	virtual bool ParseString(std::wstring const& str)
	{
		return false;
	}

protected:
	// Normalize format to "hhhhhhhh-hhhh-hhhh-hhhh-hhhhhhhhhhhh"
	std::wstring NormalizeString(std::wstring const& str)
	{
		auto len = str.length();
		if (36 == len)
			return str;
		if (38 == len && str[0] == '{')
			return str.substr(1, str.length() - 2);
		std::wstring s(str);
		if (34 == len && str[0] == '{')
			s = str.substr(1, str.length() - 2);
		if (32 == s.length())
		{
			std::wstringstream ss;
			ss << s.substr(0, 8)
				<< '-'
				<< s.substr(8, 4)
				<< '-'
				<< s.substr(12, 4)
				<< '-'
				<< s.substr(16, 4)
				<< '-'
				<< s.substr(20);
			s = ss.str();
		}
		return s;
	}
};


#ifdef __WXMSW__
class CUniqueIdImplMS : public CUniqueIdImpl
{
public:
	CUniqueIdImplMS()
		: m_uuid{0}
	{
		UuidCreateNil(&m_uuid);
	}

	CUniqueIdImplMS(CUniqueIdImplMS const& rhs)
		: m_uuid{rhs.m_uuid}
	{
	}

	bool Create() override
	{
		return RPC_S_OK == UuidCreate(&m_uuid);
	}

	CUniqueIdImpl* Clone() const override
	{
		return new CUniqueIdImplMS(*this);
	}

	bool IsNull() const override
	{
		UUID id1 = m_uuid;
		RPC_STATUS status;
		int rc = UuidIsNil(&id1, &status);
		if (RPC_S_OK == status)
			return rc == TRUE; // MS's TRUE
		return false;
	}

	void Assign(CUniqueIdImpl const* rhs) override
	{
		m_uuid = static_cast<CUniqueIdImplMS const*>(rhs)->m_uuid;
	}

	bool IsEqual(CUniqueIdImpl const* rhs) const override
	{
		UUID id1 = m_uuid; // Because Uuid* takes non-const ptr.
		UUID id2 = static_cast<CUniqueIdImplMS const*>(rhs)->m_uuid;
		RPC_STATUS status;
		int rc = UuidEqual(&id1, &id2, &status);
		if (RPC_S_OK == status)
			return rc == TRUE; // MS's TRUE
		return false;
	}

	bool IsLessThan(CUniqueIdImpl const* rhs) const override
	{
		UUID id1 = m_uuid;
		UUID id2 = static_cast<CUniqueIdImplMS const*>(rhs)->m_uuid;
		RPC_STATUS status;
		int rc = UuidCompare(&id1, &id2, &status);
		if (RPC_S_OK == status)
			return rc < 0;
		return false;
	}

	std::wstring ToString() const override
	{
		std::wstring str(L"00000000-0000-0000-0000-000000000000");
		RPC_WSTR rpcstr = nullptr;
		if (RPC_S_OK == UuidToStringW(&m_uuid, &rpcstr))
		{
			str = (wchar_t*)rpcstr;
			RpcStringFreeW(&rpcstr);
		}
		return str;
	}

	bool ParseString(std::wstring const& str) override
	{
		// This only recognizes format "hhhhhhhh-hhhh-hhhh-hhhh-hhhhhhhhhhhh"
		std::wstring s = NormalizeString(str);
		return RPC_S_OK == UuidFromStringW((RPC_WSTR)s.c_str(), &m_uuid);
	}

private:
	UUID m_uuid;
};
#endif

/////////////////////////////////////////////////////////////////////////////

CUniqueId::CUniqueId(bool autoCreate)
#ifdef __WXMSW__
	: m_impl(new CUniqueIdImplMS())
#else
	: m_impl(new CUniqueIdImpl())
#endif
{
	if (autoCreate)
		m_impl->Create();
}


CUniqueId::CUniqueId(std::wstring const& str)
	: CUniqueId()
{
	m_impl->ParseString(str);
}


CUniqueId::CUniqueId(CUniqueId const& rhs)
	: m_impl(rhs.m_impl->Clone())
{
}


CUniqueId::~CUniqueId()
{
	delete m_impl;
}


bool CUniqueId::Create()
{
	return m_impl->Create();
}


bool CUniqueId::IsNull() const
{
	return m_impl->IsNull();
}


CUniqueId& CUniqueId::operator=(CUniqueId const& rhs)
{
	if (this != &rhs)
		m_impl->Assign(rhs.m_impl);
	return *this;
}


bool CUniqueId::operator==(CUniqueId const& rhs) const
{
	return m_impl->IsEqual(rhs.m_impl);
}


bool CUniqueId::operator<(CUniqueId const& rhs) const
{
	return m_impl->IsLessThan(rhs.m_impl);
}


std::wstring CUniqueId::ToString() const
{
	return m_impl->ToString();
}


bool CUniqueId::ParseString(std::wstring const& str)
{
	return m_impl->ParseString(str);
}

} // namespace ARBCommon
} // namespace dconSoft
