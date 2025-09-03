./: {art/ tests/ examples/} doc{README.md} legal{LICENSE} manifest

define doxyfile: file
doxyfile{*}: extension = ""
doxyfile{*}: in.substitution = lax

doxyfile{Doxyfile}: in{Doxyfile} $src_root/manifest
{
  PRIVATE = "NO"
}

doxyfile{Doxyfile-private}: in{Doxyfile} $src_root/manifest
{
  PRIVATE = "YES"
}

alias{docs}: doxyfile{Doxyfile} fsdir{$out_root/docs}
{{
  diag doxygen $path($<[0])
  doxygen $path($<[0])
}}

alias{docs-private}: doxyfile{Doxyfile-private} fsdir{$out_root/docs}
{{
  diag doxygen $path($<[0])
  doxygen $path($<[0])
}}

# Don't install tests.
#
tests/: install = false
