#include <art/paperback/graphics/color.hxx>

namespace Art::Paperback::Graphics
{

  Color_RGB::
  Color_RGB()
  {}

  /// \param red The red component.
  /// \param green The green component.
  /// \param blue The blue component.
  Color_RGB::
  Color_RGB(double red, double green, double blue)
    : _red{red},
      _green{green},
      _blue{blue}
  {}

  /// \param other The Color_RGB to copy from.
  ///
  Color_RGB::
  Color_RGB(Color_RGB const& other)
    : _red{other._red},
      _green{other._green},
      _blue{other._blue}
  {}

  /// \param other The Color_RGB to move from.
  ///
  Color_RGB::
  Color_RGB(Color_RGB&& other)
    : _red{other._red},
      _green{other._green},
      _blue{other._blue}
  {}

  /// \return Returns the red component.
  ///
  double
  Color_RGB::
  red() const
  {
    return _red;
  }

  /// \return Returns the green component.
  ///
  double
  Color_RGB::
  green() const
  {
    return _green;
  }

  /// \return Returns the blue component.
  ///
  double
  Color_RGB::
  blue() const
  {
    return _blue;
  }

  /// \param other The Color_RGB to copy from.
  ///
  Color_RGB&
  Color_RGB::
  operator=(Color_RGB const& other)
  {
    _red = other._red;
    _green = other._green;
    _blue = other._blue;

    return *this;
  }

  /// \param other The Color_RGB to move from.
  ///
  Color_RGB&
  Color_RGB::
  operator=(Color_RGB&& other)
  {
    _red = other._red;
    _green = other._green;
    _blue = other._blue;

    return *this;
  }

} // namespace Art::Paperback::Graphics
