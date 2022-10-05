#pragma once

/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * Wrapper around any UUID library that gets used in case I want to change.
 *
 * Supported input formats:
 * hhhhhhhh-hhhh-hhhh-hhhh-hhhhhhhhhhhh
 * {hhhhhhhh-hhhh-hhhh-hhhh-hhhhhhhhhhhh}
 * hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh
 * {hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh}
 * Output format:
 * hhhhhhhh-hhhh-hhhh-hhhh-hhhhhhhhhhhh
 *
 * Revision History
 * 2022-10-05 Created
 */

#include "LibwxARBCommon.h"


namespace dconSoft
{
namespace ARBCommon
{
class CUniqueIdImpl;

class ARBCOMMON_API CUniqueId
{
public:
	explicit CUniqueId(bool autoCreate = false);
	explicit CUniqueId(std::wstring const& str);
	CUniqueId(CUniqueId const& rhs);
	~CUniqueId();

	bool Create();
	bool IsNull() const;

	CUniqueId& operator=(CUniqueId const& rhs);

	bool operator==(CUniqueId const& rhs) const;
	bool operator!=(CUniqueId const& rhs) const
	{
		return !operator==(rhs);
	}
	bool operator<(CUniqueId const& rhs) const;
	bool operator>(CUniqueId const& rhs) const
	{
		return rhs.operator<(*this);
	}
	bool operator<=(CUniqueId const& rhs) const
	{
		return !operator>(rhs);
	}
	bool operator>=(CUniqueId const& rhs) const
	{
		return !operator<(rhs);
	}

	std::wstring ToString() const; // Always lower-case
	bool ParseString(std::wstring const& str);

private:
	CUniqueIdImpl* m_impl;
};

} // namespace ARBCommon
} // namespace dconSoft
