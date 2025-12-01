#ifndef art__paperback__graphics__color_hxx_
#define art__paperback__graphics__color_hxx_

#include <art/paperback/types.hxx>

namespace Art::Paperback::Graphics
{

  /// PDF color space enumeration.
  ///
  enum class Color_space
  {
    /// Device grey.
    ///
    device_grey,

    /// Device RGB.
    ///
    device_rgb

  };

  /// Represents an RGB color value.
  ///
  class Color_RGB
  {
  public:
    /// Constructor.
    ///
    Color_RGB();

    /// Constructor.
    ///
    Color_RGB(Color_RGB const&);

    /// Constructor.
    ///
    Color_RGB(Color_RGB&&);

    /// Constructor.
    ///
    Color_RGB(double, double, double);

    /// Access red component.
    ///
    double
    red() const;

    /// Access green component.
    ///
    double
    green() const;

    /// Access blue component.
    ///
    double
    blue() const;

    /// Assignment.
    ///
    Color_RGB&
    operator=(Color_RGB const&);

    /// Assignment.
    ///
    Color_RGB&
    operator=(Color_RGB&&);

  private:
    double _red{};
    double _green{};
    double _blue{};

  };

} // namespace Art::Paperback::Graphics

#endif
