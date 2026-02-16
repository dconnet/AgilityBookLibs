3rd Party code.
Note: When bumping 'gsl', 'tidy', 'stduuid', update AgilityBookLibs\Include\LibARBWin\About.h
Those libs don't have a version number in their headers.


Catch: v3.13.0
.../catch/catch3/
- https://github.com/philsquared/Catch/releases
- Only copied 'src' from github, plus LICENSE.txt, README.md
-- #include "catch2/catch_all.hpp"


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


gsl: v4.2.1 (needed for stduuid for pre-C++20)
.../gsl/
- https://github.com/microsoft/GSL
- Only copied 'include' from github, plus LICENSE, README.md
