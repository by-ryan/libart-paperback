#ifndef art__paperback__primitives_hxx_
#define art__paperback__primitives_hxx_

#include <art/paperback/types.hxx>
#include <art/paperback/forward.hxx>

namespace Art::Paperback
{

  /// Represents a point in a two-dimensional space.
  ///
  struct Point_2D
  {
    /// The X coordinate.
    ///
    double x{};

    /// The Y coordinate.
    ///
    double y{};

  };

  /// Represents a PDF rectangle.
  ///
  class Rectangle
  {
  public:
    /// Constructor.
    ///
    Rectangle();

    /// Constructor.
    ///
    Rectangle(double, double, double, double);

    double
    left() const;

    double
    bottom() const;

    double
    right() const;

    double
    top() const;

    /// Create COS array from rectangle.
    ///
    Carousel::Array
    to_array() const;

    static
    Rectangle
    letter();

    static
    Rectangle
    legal();

    static
    Rectangle
    tabloid();

    static
    Rectangle
    a3();

    static
    Rectangle
    a4();

    static
    Rectangle
    a5();

    static
    Rectangle
    c3();

    static
    Rectangle
    c4();

    static
    Rectangle
    c5();

    static
    Rectangle
    executive();

  private:
    double _left{};
    double _bottom{};
    double _right{};
    double _top{};

  };

} // namespace Art::Paperback

#endif
