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

#pragma warning(disable:5246)
#if defined(WIN32) || defined(__APPLE__)
// We could define this for all platforms. Just becomes an linking issue.
#define UUID_SYSTEM_GENERATOR
#endif
#include "stduuid/uuid.h"


namespace dconSoft
{
namespace ARBCommon
{

class CUniqueIdImpl
{
	CUniqueIdImpl(CUniqueIdImpl&& rhs) = delete;
	CUniqueIdImpl& operator=(CUniqueIdImpl const&) = delete;
	CUniqueIdImpl& operator=(CUniqueIdImpl&&) = delete;

public:
	CUniqueIdImpl()
		: m_uuid()
	{
	}
	~CUniqueIdImpl() = default;

	CUniqueIdImpl(CUniqueIdImpl const& rhs)
		: m_uuid{rhs.m_uuid}
	{
	}

	void clear()
	{
		m_uuid = uuids::uuid();
	}

	bool Create()
	{
#ifdef UUID_SYSTEM_GENERATOR
		m_uuid = uuids::uuid_system_generator{}();
#else
		std::random_device rd;
		auto seed_data = std::array<int, std::mt19937::state_size>{};
		std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
		std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
		std::mt19937 generator(seq);
		uuids::uuid_random_generator gen{generator};

		m_uuid = gen();
#endif
		return !m_uuid.is_nil();
	}

	CUniqueIdImpl* Clone() const
	{
		return new CUniqueIdImpl(*this);
	}

	bool IsNull() const
	{
		return m_uuid.is_nil();
	}

	void Assign(CUniqueIdImpl const* rhs)
	{
		m_uuid = rhs->m_uuid;
	}

	bool IsEqual(CUniqueIdImpl const* rhs) const
	{
		return m_uuid == rhs->m_uuid;
	}

	bool IsLessThan(CUniqueIdImpl const* rhs) const
	{
		return m_uuid < rhs->m_uuid;
	}

	wxString ToString() const
	{
		return uuids::to_string<wchar_t>(m_uuid);
	}

	bool ParseString(wxString const& str)
	{
		auto uuid = uuids::uuid::from_string(str.wc_str());
		if (uuid)
			m_uuid = *uuid;
		else
			clear();
		return !m_uuid.is_nil();
	}

private:
#if 0
	// This was originally written directly to the Win32 api.
	// That can only parse strings in a normalized form.
	// At first CUniqueIdImpl was virtual (with this func) and I had
	// CUniqueIdImplMS and CUniqueIdImplStd impls. Decided just to use
	// stduuid (with it using the system generators).

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
			ss << s.substr(0, 8) << '-' << s.substr(8, 4) << '-' << s.substr(12, 4) << '-' << s.substr(16, 4) << '-'
			   << s.substr(20);
			s = ss.str();
		}
		return s;
	}
#endif

	uuids::uuid m_uuid;
};

/////////////////////////////////////////////////////////////////////////////

CUniqueId::CUniqueId()
	: m_impl(new CUniqueIdImpl())
{
}


CUniqueId::CUniqueId(wxString const& str)
	: CUniqueId()
{
	m_impl->ParseString(str);
}


CUniqueId::CUniqueId(CUniqueId const& rhs)
	: m_impl(rhs.m_impl->Clone())
{
}


CUniqueId::CUniqueId(CUniqueId&& rhs)
	: m_impl(std::move(rhs.m_impl))
{
}


CUniqueId::~CUniqueId()
{
	delete m_impl;
}


void CUniqueId::clear()
{
	m_impl->clear();
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


CUniqueId& CUniqueId::operator=(CUniqueId&& rhs)
{
	if (this != &rhs)
		m_impl = std::move(rhs.m_impl);
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


wxString CUniqueId::ToString() const
{
	return m_impl->ToString();
}


bool CUniqueId::ParseString(wxString const& str)
{
	return m_impl->ParseString(str);
}

} // namespace ARBCommon
} // namespace dconSoft
