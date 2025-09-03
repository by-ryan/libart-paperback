#ifndef art__paperback__internals__base14_fontdata_hxx_
#define art__paperback__internals__base14_fontdata_hxx_

#include <art/paperback/types.hxx>
#include <art/paperback/primitives.hxx>

namespace Art::Paperback::Internals
{

  /// Base font character data.
  ///
  struct Base14_character_data
  {
    int16_t char_cd;

    /// Unicode code point.
    ///
    uint16_t unicode;

    double width;

  };

  /// Represents font data for one of the 14 standard PDF fonts.
  ///
  struct Base14_font_data
  {
    /// Font character data.
    ///
    vector<Base14_character_data> const& cdata;

    bool is_font_specific;

    /// Font ascent.
    ///
    int16_t ascent;

    /// Font descent.
    ///
    int16_t descent;

    /// Font X-height.
    ///
    uint16_t x_height;

    /// Font Cap-height.
    ///
    uint16_t cap_height;

    /// Font bounding box.
    ///
    Rectangle bbox;

  };

  /// Map of base fonts.
  ///
  extern
  map<string, Base14_font_data> const
  base14_fonts;

} // namespace Art::Paperback::Internals

#endif
