#ifndef art__paperback__graphics__standard_font_hxx_
#define art__paperback__graphics__standard_font_hxx_

#include <art/paperback/types.hxx>
#include <art/paperback/forward.hxx>

#include <art/paperback/graphics/font.hxx>

namespace Art::Paperback::Graphics
{

  /// Represents a standard PDF font.
  ///
  class Standard_font
    : public Font
  {
  public:
    /// Constructor.
    ///
    Standard_font(Document&, string const&);

    /// Destructor.
    ///
    ~Standard_font() noexcept override;

    Document&
    document() override;

    Carousel::Object
    object() override;

    string
    name() const override;

    int16_t
    get_ascent() const override;

    int16_t
    get_descent() const override;

    uint16_t
    get_xheight() const override;

    uint16_t
    get_capheight() const override;

    Text_width
    get_text_width(string const&) override;

  private:
    Standard_font(Standard_font const&) = delete;
    Standard_font(Standard_font&&) = delete;
    Standard_font& operator=(Standard_font const&) = delete;
    Standard_font& operator=(Standard_font&&) = delete;

  private:
    struct Internal;
    unique_ptr<Internal> internal;

  };

} // namespace Art::Paperback::Graphics

#endif
