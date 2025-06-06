#pragma once

/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Type definitions.
 * @author David Connet
 *
 * Revision History
 * 2018-08-15 Changed ARBVersion to use std::array
 * 2016-09-04 Add a ToString wrapper.
 * 2015-12-22 Changed bAlwaysStripZeros to eStripZeros.
 * 2015-11-01 Added clear and IsSet.
 * 2014-06-09 Move string->arbversion parsing to ARBVersion.
 *            Added missing ARBVersion operator!=.
 * 2013-07-17 Moved SanitizeStringForHTML to ARBMisc.
 * 2012-08-13 Moved ARB_Q to separate file.
 * 2012-05-04 Add bAlwaysStripZeros to ARBDouble::ToString.
 * 2011-08-22 ARBVersion was only using 16 instead of 32bits.
 * 2009-09-13 Add support for wxWidgets 2.9, deprecate tstring.
 * 2009-04-20 Added DNR.
 * 2008-06-29 Moved string stuff to ARBString.
 * 2006-02-16 Cleaned up memory usage with smart pointers.
 * 2005-06-25 Removed ARBDouble.
 * 2004-09-28 Changed how error reporting is done when loading.
 * 2004-04-06 Added op< to ARB_Q.
 * 2003-11-26 Changed version number to a complex value.
 * 2003-09-01 Added 'operator+=' and 'operator-=' to ARBDouble.
 */

#include "LibwxARBCommon.h"

#include <array>

#define ARB_TYPEDEF(name) \
	class name; \
	typedef std::shared_ptr<name> name##Ptr;
#define ARB_TYPEDEF2(name) \
	class name; \
	typedef std::weak_ptr<name> name##WPtr; \
	typedef std::shared_ptr<name> name##Ptr;
#define ARB_TYPEDEF_LIST(name) \
	class name; \
	class name##List; \
	typedef std::shared_ptr<name> name##Ptr;
#define ARB_TYPEDEF2_LIST(name) \
	class name; \
	class name##List; \
	typedef std::weak_ptr<name> name##WPtr; \
	typedef std::shared_ptr<name> name##Ptr;


namespace dconSoft
{
namespace ARBCommon
{
ARB_TYPEDEF(Element)
ARB_TYPEDEF2(ElementNode)
ARB_TYPEDEF2(ElementText)


/**
 * Helper functions for quickly/easily converting doubles to strings.
 */
namespace ARBDouble
{
/// How to handle trailing zeros
enum class ZeroStrip
{
	Compatible, ///< Strip, unless inPrec = 2
	Strip,      ///< Strip
	AsIs        ///< Don't touch
};

/**
 * Trailing zeros are trimmed unless inPrec=2.
 * Then they are only trimmed if all zero (and inPrec=2).
 */
ARBCOMMON_API wxString
ToString(double inValue, int inPrec = 2, bool bUseCurrentLocale = true, ZeroStrip eStripZeros = ZeroStrip::Compatible);

ARBCOMMON_API wxString ToString(double inValue, int inPrec, ZeroStrip eStripZeros);

/**
 * Compare two doubles, allowing for 'prec' error.
 */
ARBCOMMON_API bool equal(double const& inVal1, double const& inVal2, double inPrec = 1e-9);

} // namespace ARBDouble

/////////////////////////////////////////////////////////////////////////////
/**
 * A version has a major and minor number.
 * Differences between major numbers prevents older versions of the program
 * from reading newer files. Differences in minor numbers allows an older
 * version to read the newer file, but warns that some information may be
 * lost if the file is saved.
 */
class ARBCOMMON_API ARBVersion
{
	typedef std::array<unsigned short, 2> VERSION_ARB;

public:
	ARBVersion()
		: m_Version({{0, 0}})
	{
	}

	ARBVersion(unsigned short major, unsigned short minor)
		: m_Version({{major, minor}})
	{
	}

	ARBVersion(ARBVersion const& inVer)
		: m_Version(inVer.m_Version)
	{
	}

	ARBVersion(ARBVersion&& inVer)
		: m_Version(std::move(inVer.m_Version))
	{
	}

	explicit ARBVersion(wxString inStr);

	~ARBVersion()
	{
	}

	ARBVersion& operator=(ARBVersion const& rhs)
	{
		if (this != &rhs)
		{
			m_Version = rhs.m_Version;
		}
		return *this;
	}
	ARBVersion& operator=(ARBVersion&& rhs)
	{
		if (this != &rhs)
		{
			m_Version = std::move(rhs.m_Version);
		}
		return *this;
	}
	bool operator==(ARBVersion const& rhs) const
	{
		return m_Version == rhs.m_Version;
	}
	bool operator!=(ARBVersion const& rhs) const
	{
		return m_Version != rhs.m_Version;
	}
	bool operator<(ARBVersion const& rhs) const
	{
		return m_Version < rhs.m_Version;
	}
	bool operator<=(ARBVersion const& rhs) const
	{
		return m_Version <= rhs.m_Version;
	}
	bool operator>(ARBVersion const& rhs) const
	{
		return m_Version > rhs.m_Version;
	}
	bool operator>=(ARBVersion const& rhs) const
	{
		return m_Version >= rhs.m_Version;
	}

	void clear()
	{
		m_Version = {{0, 0}};
	}
	bool IsSet() const
	{
		return m_Version > VERSION_ARB({{0, 0}});
	}

	unsigned short Major() const
	{
		return m_Version[0];
	}
	unsigned short Minor() const
	{
		return m_Version[1];
	}
	wxString str() const;

private:
	VERSION_ARB m_Version;
};

} // namespace ARBCommon
} // namespace dconSoft
