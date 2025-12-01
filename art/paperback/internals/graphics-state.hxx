#ifndef art__paperback__internals__graphics_state_hxx_
#define art__paperback__internals__graphics_state_hxx_

#include <art/paperback/types.hxx>

#include <art/paperback/graphics/color.hxx>
#include <art/paperback/graphics/font.hxx>

namespace Art::Paperback::Internals
{

  struct Matrix
  {
    double a;
    double b;
    double c;
    double d;
    double e;
    double f;

  };

  Matrix
  apply(Matrix const&, Matrix const&);

  enum class Text_rendering_mode
  {
    fill,
    stroke,
    fill_then_stroke,
    invisble,
    fill_clippping,
    stroke_clipping,
    fill_stroke_clipping,
    clipping

  };

  enum class Line_cap_style
  {
    butt_end,
    round_end,
    projecting_square_end

  };

  enum class Line_join_style
  {
    miter_join,
    round_join,
    bevel_join

  };

  struct Graphics_state
  {
    Matrix ctm;

    Graphics::Color_space cs_stroke{Graphics::Color_space::device_grey};
    Graphics::Color_space cs_fill{Graphics::Color_space::device_grey};

    Graphics::Color_RGB rgb_stroke;
    Graphics::Color_RGB rgb_fill;

    double grey_stroke{};
    double grey_fill{};

    double                text_cspace{};
    double                text_hspace{};
    double                text_hscale{};
    double                text_leading{};
    Graphics::Font*     current_font{};
    double                font_size{};
    Text_rendering_mode text_rendering_mode{};
    double                ts_rise{};

    double            line_width{1.0};
    Line_cap_style  line_cap{};
    Line_join_style line_join{};
    double            miter_limit{10.0};
    double            flatness{1.0};

  };

} // namespace Art::Paperback::Internals

#endif
