#include <art/paperback/graphics/standard-font.hxx>

#include <art/paperback/document.hxx>

#include <art/paperback/carousel/dictionary.hxx>
#include <art/paperback/carousel/file.hxx>
#include <art/paperback/carousel/object.hxx>

#include <art/paperback/internals/base14-fontdata.hxx>

#include <art/unicode/reader.hxx>
#include <art/unicode/utf8-decoder.hxx>

namespace Art::Paperback::Graphics
{

  struct Standard_font::Internal
  {
    Internal(Document& document)
      : document{document},
        object{document.file().create_object<Carousel::Dictionary>()},
        data{object_cast<Carousel::Dictionary>(object)}
    {}

    Document&        document;
    Carousel::Object      object;
    Carousel::Dictionary& data;

    string name;

    Internals::Base14_font_data const* font_data;

  };

  /// \class Standard_font
  ///
  /// This class represents one of the 14 standard fonts supported by
  /// the PDF-specification.
  ///

  /// \param document A reference to the parent document.
  /// \param base_font The name of the base font.
  ///
  Standard_font::
  Standard_font(Document& document, string const& base_font)
    : internal{new Internal{document}}
  {
    internal->data.insert("Type", Carousel::Name{"Font"});
    internal->data.insert("Subtype", Carousel::Name{"Type1"});
    internal->data.insert("BaseFont", Carousel::Name{base_font});
    internal->data.insert("Encoding", Carousel::Name{"WinAnsiEncoding"});

    internal->name = base_font;

    auto font_data = Internals::base14_fonts.find(base_font);

    if (font_data == Internals::base14_fonts.end()) {
      throw std::invalid_argument{"invalid base font"};
    }

    internal->font_data = &font_data->second;
  }

  Standard_font::
  ~Standard_font() noexcept
  {}

  Document&
  Standard_font::
  document()
  {
    return internal->document;
  }

  Carousel::Object
  Standard_font::
  object()
  {
    return internal->object;
  }

  string
  Standard_font::
  name() const
  {
    return internal->name;
  }

  /// \return Returns the font ascent.
  ///
  int16_t
  Standard_font::
  get_ascent() const
  {
    return internal->font_data->ascent;
  }

  /// \return Returns the font descent.
  ///
  int16_t
  Standard_font::
  get_descent() const
  {
    return internal->font_data->descent;
  }

  /// \return Returns the font X-height.
  ///
  uint16_t
  Standard_font::
  get_xheight() const
  {
    return internal->font_data->x_height;
  }

  /// \return Returns the font Cap-height.
  ///
  uint16_t
  Standard_font::
  get_capheight() const
  {
    return internal->font_data->cap_height;
  }

  /// \a text is assumed to be encoded in UTF-8 and will be
  /// decoded as such during text width computation.
  ///
  /// \param text The text for which to compute metrics.
  ///
  Text_width
  Standard_font::
  get_text_width(string const& text)
  {
    Text_width tw{};

    art::unicode::iterator_reader_t reader{text.begin(), text.end()};
    art::unicode::utf8_decoder_t decoder{reader};

    for (auto it = decoder.begin(); it != decoder.end(); ++it) {
      auto const c = *it;

      if (c == ' ')
        ++tw.space_count;

      ++tw.character_count;

      for (auto const& j : internal->font_data->cdata) {
        if (c == j.unicode) {
          tw.width += j.width;
          break;
        }
      }
    }

    return tw;
  }

} // namespace Art::Paperback::Graphics
