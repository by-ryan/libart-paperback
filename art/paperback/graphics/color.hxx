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
  class RGB
  {
  public:
    /// Constructor.
    ///
    RGB();

    /// Constructor.
    ///
    RGB(RGB const&);

    /// Constructor.
    ///
    RGB(RGB&&);

    /// Constructor.
    ///
    RGB(double, double, double);

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
    RGB&
    operator=(RGB const&);

    /// Assignment.
    ///
    RGB&
    operator=(RGB&&);

  private:
    double _red{};
    double _green{};
    double _blue{};

  };

} // namespace Art::Paperback::Graphics

#endif
