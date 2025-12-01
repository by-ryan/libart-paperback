#include <art/paperback/graphics/canvas.hxx>
#include <art/paperback/graphics/font.hxx>

#include <art/paperback/except.hxx>
#include <art/paperback/page.hxx>

#include <art/paperback/carousel/name.hxx>
#include <art/paperback/carousel/object.hxx>
#include <art/paperback/carousel/stream.hxx>

#include <art/paperback/internals/cp1252.hxx>
#include <art/paperback/internals/graphics-state.hxx>
#include <art/paperback/internals/resource-collection.hxx>

namespace Art::Paperback::Graphics
{

  /// Holds internal canvas data.
  ///
  struct Canvas::Internal
  {
    Internal(Page& page)
      : page{page},
        contents{page.contents()}
    {
      gstates.push(Internals::Graphics_state{});
    }

    /// Write single byte to content stream.
    ///
    void
    write(char c)
    {
      contents->write(&c, 1);
    }

    /// Write string to content stream.
    ///
    void
    write(string const& str)
    {
      contents->write(str.c_str(), str.size());
    }

    /// Write real value to stream.
    ///
    void
    write(double v)
    {
      stringstream str;
      str.imbue(std::locale::classic());
      str << std::fixed << v;
      write(str.str());
    }

    /// Write integer value to stream.
    ///
    void
    write(long long int v)
    {
      stringstream str;
      str.imbue(std::locale::classic());
      str << v;
      write(str.str());
    }

    /// Write name to content stream.
    ///
    void
    write_name(string const& n)
    {
      write('/');
      write(n);
    }

    /// Write encoded text string to content stream.
    ///
    /// The text is hexadecimally coded.
    ///
    void
    write_encode_text(string const& text)
    {
      auto to_hex = [](char c) -> char
      {
        return (c < 10) ? ('0' + c) : ('a' + (c - 10));
      };

      auto encoded = Internals::cp1252::from_utf8(text);

      write('<');
      for (auto const& j : encoded) {
          char high = (j & 0xF0) >> 4;
          char low = (j & 0x0F);

          write(to_hex(high));
          write(to_hex(low));
      }
      write('>');
    }

    /// Reference to parent page.
    ///
    Page& page;

    /// Canvas content stream.
    ///
    Carousel::Stream& contents;

    /// Holds the graphics states.
    ///
    stack<Internals::Graphics_state> gstates;

  };

  /// \param page The parent page of this canvas.
  ///
  Canvas::
  Canvas(Clear const&, Page& page)
    : internal{new Internal{page}}
  {
    content().clear();
  }

  Canvas::
  ~Canvas()
  {}

  Page&
  Canvas::
  page()
  {
    return internal->page;
  }

  Page const&
  Canvas::
  page() const
  {
    return internal->page;
  }

  Carousel::Stream&
  Canvas::
  content()
  {
    return internal->contents;
  }

  Carousel::Stream const&
  Canvas::
  content() const
  {
    return internal->contents;
  }

  /// \param grey_level The new grey level.
  ///
  void
  Canvas::
  set_stroke(double grey_level)
  {
    if (grey_level < 0 || 1 < grey_level) {
      throw std::out_of_range{"grey level out of range (0-1)"};
    }

    internal->write(grey_level);
    internal->write("G\r\n");

    internal->gstates.top().cs_stroke = Color_space::device_grey;
    internal->gstates.top().grey_stroke = grey_level;
  }

  /// \param grey_level The new grey level.
  ///
  void
  Canvas::
  set_fill(double grey_level)
  {
    if (grey_level < 0 || 1 < grey_level) {
      throw std::out_of_range{"grey level out of range (0-1)"};
    }

    internal->write(grey_level);
    internal->write(' ');
    internal->write("g\r\n");

    internal->gstates.top().cs_fill = Color_space::device_grey;
    internal->gstates.top().grey_fill = grey_level;
  }

  /// \param color The new RGB color.
  ///
  void
  Canvas::
  set_stroke(Color_RGB const& color)
  {
    internal->write(color.red());
    internal->write(' ');
    internal->write(color.green());
    internal->write(' ');
    internal->write(color.blue());
    internal->write(' ');
    internal->write("RG\r\n");

    internal->gstates.top().cs_stroke = Color_space::device_rgb;
    internal->gstates.top().rgb_stroke = color;
  }

  /// \param color The new RGB color.
  ///
  void
  Canvas::
  set_fill(Color_RGB const& color)
  {
    internal->write(color.red());
    internal->write(' ');
    internal->write(color.green());
    internal->write(' ');
    internal->write(color.blue());
    internal->write(' ');
    internal->write("rg\r\n");

    internal->gstates.top().cs_fill = Color_space::device_rgb;
    internal->gstates.top().rgb_fill = color;
  }

  /// \param text The text for which to compute the width.
  ///
  double
  Canvas::
  get_text_width(string const& text) const
  {
    auto& gstate = internal->gstates.top();
    auto& font = *gstate.current_font;
    auto font_size = gstate.font_size;

    auto tw = font.get_text_width(text);

    auto width = static_cast<double>(tw.width) * font_size / 1000;

    // FIXME: the missing functions mentioned below.
    //
    width += tw.character_count * 0; // gstate.get_text_character_spacing();
    width += tw.space_count * 0; // gstate.get_text_word_spacing();

    return width;
  }

  /// \param canvas The parent canvas.
  ///
  Canvas::Save::
  Save(Canvas& canvas)
    : _canvas{canvas}
  {
    canvas.internal->gstates.push(canvas.internal->gstates.top());
  }

  Canvas::Save::
  ~Save() noexcept
  {
    canvas().internal->gstates.pop();
  }

  Canvas&
  Canvas::Save::
  canvas()
  {
    return _canvas;
  }

  Canvas const&
  Canvas::Save::
  canvas() const
  {
    return _canvas;
  }

  /// \param canvas The parent canvas.
  /// \param mode The paint mode.
  ///
  Canvas::Path::
  Path(Canvas& canvas, Paint_mode mode)
    : _canvas{canvas},
      _mode{mode}
  {}

  Canvas::Path::
  ~Path() noexcept
  {
    canvas().internal->write("h\r\n");

    switch (_mode) {
      case stroke:
        canvas().internal->write("S\r\n");
        break;

      case fill:
        canvas().internal->write("R\r\n");
        break;

      case fill_then_stroke:
        canvas().internal->write("B\r\n");
        break;
    }
  }

  /// \return Returns a reference to the parent canvas.
  ///
  Canvas&
  Canvas::Path::
  canvas()
  {
    return _canvas;
  }

  /// \return Returns a reference to the parent canvas.
  ///
  Canvas const&
  Canvas::Path::
  canvas() const
  {
    return _canvas;
  }

  void
  Canvas::Path::
  move_to(double x, double y)
  {
    canvas().internal->write(x);
    canvas().internal->write(' ');
    canvas().internal->write(y);
    canvas().internal->write(" m\r\n");
  }

  void
  Canvas::Path::
  line_to(double x, double y)
  {
    canvas().internal->write(x);
    canvas().internal->write(' ');
    canvas().internal->write(y);
    canvas().internal->write(" l\r\n");
  }

  void
  Canvas::Path::
  bezier_curve_to(double x1,
                  double y1,
                  double x2,
                  double y2,
                  double x3,
                  double y3)
  {
    canvas().internal->write(x1);
    canvas().internal->write(' ');
    canvas().internal->write(y1);
    canvas().internal->write(' ');
    canvas().internal->write(x2);
    canvas().internal->write(' ');
    canvas().internal->write(y2);
    canvas().internal->write(' ');
    canvas().internal->write(x3);
    canvas().internal->write(' ');
    canvas().internal->write(y3);
    canvas().internal->write(" c\r\n");
  }

  /// \param canvas The parent canvas.
  ///
  Canvas::Begin_text::
  Begin_text(Canvas& canvas)
    : _canvas{canvas}
  {
    canvas.internal->write("BT\r\n");
  }

  Canvas::Begin_text::
  ~Begin_text() noexcept
  {
    canvas().internal->write("ET\r\n");
  }

  Canvas&
  Canvas::Begin_text::
  canvas()
  {
    return _canvas;
  }

  Canvas const&
  Canvas::Begin_text::
  canvas() const
  {
    return _canvas;
  }

  void
  Canvas::Begin_text::
  move_text_pos(double x, double y)
  {
    canvas().internal->write(x);
    canvas().internal->write(' ');
    canvas().internal->write(y);
    canvas().internal->write(" Td\r\n");
  }

  void
  Canvas::Begin_text::
  show_text(string const& text)
  {
    canvas().internal->write_encode_text(text);
    canvas().internal->write(" Tj\r\n");
  }

  /// \param canvas The parent canvas.
  /// \param f The new font.
  /// \param size The font size.
  /// \throw Invalid_operation Thrown if a font is already set.
  ///
  Canvas::Set_font::
  Set_font(Canvas& canvas, Font& f, double size)
    : _canvas{canvas}
  {
    if (canvas.internal->gstates.top().current_font) {

      raise<Invalid_operation>{} << "font already set";
    }

    auto local_name = canvas.page().resources().fonts().embed(f);

    canvas.internal->write_name(*local_name);
    canvas.internal->write(' ');
    canvas.internal->write(size);
    canvas.internal->write(" Tf ");

    canvas.internal->gstates.top().current_font = &f;
    canvas.internal->gstates.top().font_size = size;
  }

  /// The current font will be resent during deconstruction.
  ///
  Canvas::Set_font::
  ~Set_font() noexcept
  {
    canvas().internal->gstates.top().current_font = nullptr;
  }

  Canvas&
  Canvas::Set_font::
  canvas()
  {
    return _canvas;
  }

  Canvas const&
  Canvas::Set_font::
  canvas() const
  {
    return _canvas;
  }

} // namespace Art::Paperback::Graphics
