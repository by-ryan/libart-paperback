#include <art/paperback/graphics/color.hxx>

namespace Art::Paperback::Graphics
{

  RGB::
  RGB()
  {}

  /// \param red The red component.
  /// \param green The green component.
  /// \param blue The blue component.
  RGB::
  RGB(double red, double green, double blue)
    : _red{red},
      _green{green},
      _blue{blue}
  {}

  /// \param other The RGB to copy from.
  ///
  RGB::
  RGB(RGB const& other)
    : _red{other._red},
      _green{other._green},
      _blue{other._blue}
  {}

  /// \param other The RGB to move from.
  ///
  RGB::
  RGB(RGB&& other)
    : _red{other._red},
      _green{other._green},
      _blue{other._blue}
  {}

  /// \return Returns the red component.
  ///
  double
  RGB::
  red() const
  {
    return _red;
  }

  /// \return Returns the green component.
  ///
  double
  RGB::
  green() const
  {
    return _green;
  }

  /// \return Returns the blue component.
  ///
  double
  RGB::
  blue() const
  {
    return _blue;
  }

  /// \param other The RGB to copy from.
  ///
  RGB&
  RGB::
  operator=(RGB const& other)
  {
    _red = other._red;
    _green = other._green;
    _blue = other._blue;

    return *this;
  }

  /// \param other The RGB to move from.
  ///
  RGB&
  RGB::
  operator=(RGB&& other)
  {
    _red = other._red;
    _green = other._green;
    _blue = other._blue;

    return *this;
  }

} // namespace Art::Paperback::Graphics
