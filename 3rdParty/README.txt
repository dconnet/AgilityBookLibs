3rd Party code.

Catch: v2.13.10
.../catch/catch2/
- https://github.com/philsquared/Catch/releases
-- #include "catch2/catch.hpp"

Catch: v3.5.4
.../catch/catch3/
- https://github.com/philsquared/Catch/releases
- Only copied 'src' from github, plus LICENSE.txt, README.md
-- #include "catch2/catch_all.hpp"


LibFmt: fmtlib v10.2.1
.../LibFmt/
DevNote: When updating, update .../res/LibFmt.rc2 with version number and copyright
- https://github.com/fmtlib/fmt/releases
- http://fmtlib.net/dev/index.html
- Only README.md, LICENSE, include, src
(note: diff is against 10.2.0, same thing needs to be done for all)
-- Changes [git diff COMMIT~] COMMIT is commit number, run in bash - not cmd.

diff --git a/include/fmt/format.h b/include/fmt/format.h
index 4972a02b..beb2ae4a 100644
--- a/include/fmt/format.h
+++ b/include/fmt/format.h
@@ -2128,7 +2128,17 @@ auto write_int(OutputIt out, UInt value, unsigned prefix,
   }
   case presentation_type::chr:
     return write_char(out, static_cast<Char>(value), specs);
-  default:
+  case presentation_type::hexfloat_lower:
+  case presentation_type::hexfloat_upper:
+  case presentation_type::exp_lower:
+  case presentation_type::exp_upper:
+  case presentation_type::fixed_lower:
+  case presentation_type::fixed_upper:
+  case presentation_type::general_lower:
+  case presentation_type::general_upper:
+  case presentation_type::string:
+  case presentation_type::pointer:
+  case presentation_type::debug:
     throw_format_error("invalid format specifier");
   }
 
@@ -2244,7 +2254,17 @@ FMT_CONSTEXPR FMT_INLINE auto write_int(OutputIt out, write_int_arg<T> arg,
   }
   case presentation_type::chr:
     return write_char(out, static_cast<Char>(abs_value), specs);
-  default:
+  case presentation_type::hexfloat_lower:
+  case presentation_type::hexfloat_upper:
+  case presentation_type::exp_lower:
+  case presentation_type::exp_upper:
+  case presentation_type::fixed_lower:
+  case presentation_type::fixed_upper:
+  case presentation_type::general_lower:
+  case presentation_type::general_upper:
+  case presentation_type::string:
+  case presentation_type::pointer:
+  case presentation_type::debug:
     throw_format_error("invalid format specifier");
   }
   return out;
@@ -2475,7 +2495,16 @@ FMT_CONSTEXPR auto parse_float_type_spec(const format_specs<Char>& specs)
   case presentation_type::hexfloat_lower:
     result.format = float_format::hex;
     break;
-  default:
+  case presentation_type::dec:
+  case presentation_type::oct:
+  case presentation_type::hex_lower:
+  case presentation_type::hex_upper:
+  case presentation_type::bin_lower:
+  case presentation_type::bin_upper:
+  case presentation_type::chr:
+  case presentation_type::string:
+  case presentation_type::pointer:
+  case presentation_type::debug:
     throw_format_error("invalid format specifier");
     break;
   }


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
