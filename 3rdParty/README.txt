3rd Party code.

Catch: v2.13.10
.../catch/catch2/
- https://github.com/philsquared/Catch/releases
-- #include "catch2/catch.hpp"


Catch: v3.7.1
.../catch/catch3/
- https://github.com/philsquared/Catch/releases
- Only copied 'src' from github, plus LICENSE.txt, README.md
-- #include "catch2/catch_all.hpp"


LibFmt: fmtlib v11.0.2
.../LibFmt/
DevNote: When updating, update .../res/LibFmt.rc2 with version number and copyright
- https://github.com/fmtlib/fmt/releases
- http://fmtlib.net/dev/index.html
- Only README.md, LICENSE, include, src
-- Changes
  - In format.h, add (and ending ifdef/pop block)
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4061) // enumerator '<value>' in switch of enum '<enum>' is not explicitly handled by a case label
#endif
  - In chrono.h, add (and ending ifdef/pop block)
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4583) // 'fmt::v11::detail::get_locale::locale_': destructor is not implicitly called
#endif


LibTidyHtml: tidy v5.8.0: My wrapper to hide tidy
.../LibTidyHtml/
DevNote: When updating, update .../res/LibTidyHtml.rc2 with version number and copyright
- https://github.com/htacg/tidy-html5/releases
- Only 'README', 'include', and 'src' directories are included.
-- #include "LibTidyHtml/LibTidyHtml.h"


stduuid: v1.2.3
.../stduuid/
- https://github.com/mariusbancila/stduuid
- Only copied 'uuid.h' from github, plus LICENSE, README.md
- Note: I created an extra directory in the include that's not in the source.
-- #include "stduuid/uuid.h"


gsl: v4.0.0 (needed for stduuid for pre-C++20)
.../gsl/
- https://github.com/microsoft/GSL
- Only copied 'include' from github, plus LICENSE, README.md
