#ifndef art__paperback__graphics__canvas_hxx_
#define art__paperback__graphics__canvas_hxx_

#include <art/paperback/types.hxx>
#include <art/paperback/forward.hxx>

#include <art/paperback/graphics/color.hxx>

namespace Art::Paperback::Graphics
{

  /// Represents the drawable canvas of a page.
  ///
  class Canvas
  {
  public:
    struct Clear {};

    /// Dispatch-tag used to clear a canvas.
    ///
    static constexpr Clear const clear{};

    /// Constructor.
    ///
    Canvas(Clear const&, Page&);

    /// Destructor.
    ///
    ~Canvas();

    /// Access the parent page.
    ///
    Page&
    page();

    /// Access the parent page.
    ///
    Page const&
    page() const;

    /// Access the content stream.
    ///
    Carousel::Stream&
    content();

    /// Access the content stream.
    ///
    Carousel::Stream const&
    content() const;

    class Save;
    friend Save;

    /// Set stroke greyscale value.
    ///
    void
    set_stroke(double);

    /// Set fill greyscale value.
    ///
    void
    set_fill(double);

    /// Set stroke RGB color.
    ///
    void
    set_stroke(RGB const&);

    /// Set fill RGB color.
    ///
    void
    set_fill(RGB const&);

    class Path;
    friend Path;

    class Begin_text;
    friend Begin_text;

    class Set_font;
    friend Set_font;

    /// Compute text width.
    ///
    double
    get_text_width(string const&) const;

  private:
    Canvas(Canvas const&) = delete;
    Canvas(Canvas&&) = delete;
    Canvas& operator=(Canvas const&) = delete;
    Canvas& operator=(Canvas&&) = delete;

  private:
    struct Internal;
    unique_ptr<Internal> internal;

  };

  /// Saves graphics state.
  ///
  class Canvas::Save
  {
  public:
    /// Constructor.
    ///
    explicit
    Save(Canvas&);

    /// Destructor.
    ///
    ~Save() noexcept;

    /// Access parent canvas.
    ///
    Canvas&
    canvas();

    /// Access parent canvas.
    Canvas const&
    canvas() const;

  private:
    Save(Save const&) = delete;
    Save(Save&&) = delete;
    Save& operator=(Save const&) = delete;
    Save& operator=(Save&&) = delete;

  private:
    Canvas& _canvas;

  };

  /// Path construction class.
  ///
  /// \todo Add example.
  ///
  class Canvas::Path
  {
  public:
    /// Paint mode enumeration.
    ///
    enum Paint_mode
    {
      /// Stroke.
      ///
      stroke,

      /// Fill.
      ///
      fill,

      /// Fill then stroke.
      ///
      fill_then_stroke

    };

    /// Constructor.
    ///
    Path(Canvas&, Paint_mode);

    /// Destructor.
    ///
    ~Path() noexcept;

    /// Access parent canvas.
    ///
    Canvas&
    canvas();

    /// Access parent canvas.
    Canvas const&
    canvas() const;

    /// Move starting point.
    ///
    void
    move_to(double, double);

    /// Draw line.
    ///
    void
    line_to(double, double);

    /// Draw bezier curve.
    ///
    void
    bezier_curve_to(double,
                    double,
                    double,
                    double,
                    double,
                    double);


  private:
    Path(Path const&) = delete;
    Path(Path&&) = delete;
    Path& operator=(Path const&) = delete;
    Path& operator=(Path&&) = delete;

  private:
    Canvas& _canvas;
    Paint_mode _mode;

  };

  class Canvas::Begin_text
  {
  public:
    explicit
    Begin_text(Canvas&);

    Begin_text(Begin_text const&) = delete;

    Begin_text(Begin_text&&) = delete;

    ~Begin_text() noexcept;

    Canvas&
    canvas();

    Canvas const&
    canvas() const;

    void
    move_text_pos(double, double);

    void
    show_text(string const&);

    Begin_text&
    operator=(Begin_text const&) = delete;

    Begin_text&
    operator=(Begin_text&&) = delete;

  private:
    Canvas& _canvas;

  };

  class Canvas::Set_font
  {
  public:
    Set_font(Canvas&, Font&, double);

    Set_font(Set_font const&) = delete;

    Set_font(Set_font&&) = delete;

    ~Set_font() noexcept;

    Canvas&
    canvas();

    Canvas const&
    canvas() const;

    Set_font&
    operator=(Set_font const&) = delete;

    Set_font&
    operator=(Set_font&&) = delete;

  private:
    Canvas& _canvas;

  };

} // namespace Art::Paperback::Graphics

#endif
