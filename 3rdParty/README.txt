3rd Party code.

Catch: v2.13.10
.../catch/catch2/
- https://github.com/philsquared/Catch/releases
-- #include "catch2/catch.hpp"


Catch: v3.6.0
.../catch/catch3/
- https://github.com/philsquared/Catch/releases
- Only copied 'src' from github, plus LICENSE.txt, README.md
-- #include "catch2/catch_all.hpp"


LibFmt: fmtlib v11.0.1
.../LibFmt/
DevNote: When updating, update .../res/LibFmt.rc2 with version number and copyright
- https://github.com/fmtlib/fmt/releases
- http://fmtlib.net/dev/index.html
- Only README.md, LICENSE, include, src
(note: diff is against 11.0.0, same thing needs to be done for all)
-- Changes [git diff COMMIT~] COMMIT is commit number, run in bash - not cmd.

diff --git a/include/fmt/format.h b/include/fmt/format.h
index 7c2a19b4..2951e9a9 100644
--- a/include/fmt/format.h
+++ b/include/fmt/format.h
@@ -33,6 +33,11 @@
 #ifndef FMT_FORMAT_H_
 #define FMT_FORMAT_H_

+#ifdef _MSC_VER
+#pragma warning(push)
+#pragma warning(disable : 4061) // enumerator '<value>' in switch of enum '<enum>' is not explicitly handled by a case label
+#endif
+
 #ifndef _LIBCPP_REMOVE_TRANSITIVE_INCLUDES
 #  define _LIBCPP_REMOVE_TRANSITIVE_INCLUDES
 #  define FMT_REMOVE_TRANSITIVE_INCLUDES
@@ -4416,4 +4421,8 @@ FMT_END_NAMESPACE
 #  undef _LIBCPP_REMOVE_TRANSITIVE_INCLUDES
 #endif

+#ifdef _MSC_VER
+#pragma warning(pop)
+#endif
+
 #endif  // FMT_FORMAT_H_


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
