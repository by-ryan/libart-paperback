#ifndef art__paperback__graphics__font_hxx_
#define art__paperback__graphics__font_hxx_

#include <art/paperback/types.hxx>
#include <art/paperback/forward.hxx>

namespace Art::Paperback::Graphics
{

  /// Represents text width computations.
  ///
  struct Text_width
  {
    /// Character count.
    ///
    uint32_t character_count{};

    /// Space count.
    ///
    uint32_t space_count{};

    /// Text width.
    ///
    double width{};

  };

  /// Base class for fonts.
  ///
  class Font
  {
  public:
    /// Destructor.
    ///
    virtual
    ~Font() noexcept
    {}

    /// Access the parent document of this font.
    ///
    virtual
    Document&
    document() = 0;

    /// Get the COS object for this font.
    ///
    virtual
    Carousel::Object
    object() = 0;

    /// Get the name of the font.
    ///
    /// \return Returns the name of the font.
    ///
    virtual
    string
    name() const = 0;

    /// Get the font ascent.
    ///
    /// \return Returns the font ascent.
    ///
    virtual
    int16_t
    get_ascent() const = 0;

    /// Get the font descent.
    ///
    virtual
    int16_t
    get_descent() const = 0;

    /// Get the font X-height.
    ///
    virtual
    uint16_t
    get_xheight() const = 0;

    /// Get the font cap-height.
    ///
    virtual
    uint16_t
    get_capheight() const = 0;

    /// Compute text width.
    ///
    virtual
    Text_width
    get_text_width(string const&) = 0;

  protected:
    /// Constructor.
    ///
    Font()
    {}

  private:
    Font(Font const&) = delete;
    Font(Font&&) = delete;
    Font& operator=(Font const&) = delete;
    Font& operator=(Font&&) = delete;

  };

} // namespace Art::Paperback::Graphics

#endif
