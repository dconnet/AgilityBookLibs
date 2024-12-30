#pragma once

/*
 * Copyright (c) David Connet. All Rights Reserved.
 *
 * License: See License.txt
 */

/**
 * @file
 * @brief Tidy html
 * @author David Connet
 *
 * Revision History
 * 2022-05-03 Changed API to return string (because this is compiled as MBCS)
 * 2017-12-19 Added pRawFileBaseName for debugging.
 * 2013-06-10 Separated from Win/CalendarSiteUSDAA.cpp
 */

#if defined(_DLL) && defined(_WIN32)
#if defined(LIBTIDYHTML_EXPORT)
#define LIBTIDYHTML_API __declspec(dllexport)
#else
#define LIBTIDYHTML_API __declspec(dllimport)
#endif
#else
#define LIBTIDYHTML_API
#endif

#include <string>


namespace dconSoft
{
namespace TidyHtml
{

LIBTIDYHTML_API std::string TidyHtmlData(
	std::string const& data,
	std::string& err,
	std::string const* pRawFileBaseName = nullptr);

} // namespace TidyHtml
} // namespace dconSoft
