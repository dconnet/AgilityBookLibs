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
 * 2018-12-16 Convert to fmt.
 * 2017-12-19 Added pRawFileBaseName for debugging.
 *            Fixed tidy calls to properly quote "&" from web data.
 * 2013-06-10 Separated from Win/CalendarSiteUSDAA.cpp
 */

#include "stdafx.h"
#include "LibTidyHtml/LibTidyHtml.h"

#include "tidy.h"
#include "tidybuffio.h"
#include <fstream>

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>
#else
#include <errno.h>
#endif


std::string TidyHtmlData(std::string const& data, fmt::memory_buffer& err, std::string const* pRawFileBaseName)
{
	std::string tidyData;

	if (!data.empty())
	{
		TidyDoc tdoc = tidyCreate();

		tidyOptSetBool(tdoc, TidyXhtmlOut, yes);
		tidyOptSetBool(tdoc, TidyNumEntities, yes);
		tidyOptSetBool(tdoc, TidyQuoteAmpersand, yes);

		TidyBuffer errbuf = {0};
		if (0 > tidySetErrorBuffer(tdoc, &errbuf))
		{
			tidyRelease(tdoc);
			return tidyData;
		}

		if (0 > tidyParseString(tdoc, data.c_str()))
		{
			if (errbuf.size > 0)
			{
				std::string errmsg((const char*)errbuf.bp, errbuf.size);
				fmt::format_to(std::back_inserter(err), "TIDY Error: {}", errmsg);
			}
			tidyBufFree(&errbuf);
			tidyRelease(tdoc);
			return tidyData;
		}

		if (0 > tidyCleanAndRepair(tdoc))
		{
			if (errbuf.size > 0)
			{
				std::string errmsg((const char*)errbuf.bp, errbuf.size);
				fmt::format_to(std::back_inserter(err), "TIDY Error: {}", errmsg);
			}
			tidyBufFree(&errbuf);
			tidyRelease(tdoc);
			return tidyData;
		}

		tidyRunDiagnostics(tdoc);
		tidyOptSetBool(tdoc, TidyForceOutput, yes);

		TidyBuffer output = {0};
		if (0 > tidySaveBuffer(tdoc, &output))
		{
			if (errbuf.size > 0)
			{
				std::string errmsg((const char*)errbuf.bp, errbuf.size);
				fmt::format_to(std::back_inserter(err), "TIDY Error: {}", errmsg);
			}
			tidyBufFree(&errbuf);
			tidyBufFree(&output);
			tidyRelease(tdoc);
			return tidyData;
		}

		if (pRawFileBaseName && !pRawFileBaseName->empty())
		{
			std::string out(*pRawFileBaseName);
			out += ".out";
			std::ofstream file(out.c_str(), std::ios_base::out | std::ios_base::binary);
			if (file.is_open())
			{
				file.write((const char*)output.bp, output.size);
				file.close();
			}
		}

		tidyData = std::string((const char*)output.bp, output.size);

		tidyBufFree(&errbuf);
		tidyBufFree(&output);
		tidyRelease(tdoc);
	}
	return tidyData;
}
