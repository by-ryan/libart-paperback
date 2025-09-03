#ifndef art__paperback__internals__cp1252_hxx_
#define art__paperback__internals__cp1252_hxx_

#include <art/paperback/types.hxx>

#include <art/unicode/reader.hxx>
#include <art/unicode/utf8-decoder.hxx>

namespace Art::Paperback::Internals::cp1252
{

  char
  from_unicode(uint32_t);

  template<typename I>
  string
  from_utf8(I&&, I const&);

  string
  from_utf8(string const&);

} // namespace Art::Paperback::Internals::cp1252

#include <art/paperback/internals/cp1252.txx>

#endif
