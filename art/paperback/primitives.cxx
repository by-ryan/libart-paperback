#include <art/paperback/primitives.hxx>

#include <art/paperback/carousel/array.hxx>
#include <art/paperback/carousel/object.hxx>
#include <art/paperback/carousel/real.hxx>

namespace Art::Paperback
{

  Rectangle::
  Rectangle()
  {}

  Rectangle::
  Rectangle(double left, double bottom, double right, double top)
    : _left{left},
      _bottom{bottom},
      _right{right},
      _top{top}
  {}

  double
  Rectangle::
  left() const
  {
    return _left;
  }

  double
  Rectangle::
  bottom() const
  {
    return _bottom;
  }

  double
  Rectangle::
  right() const
  {
    return _right;
  }

  double
  Rectangle::
  top() const
  {
    return _top;
  }

  Carousel::Array
  Rectangle::
  to_array() const
  {
    Carousel::Array array{
      {
        Carousel::Real{left()},
        Carousel::Real{bottom()},
        Carousel::Real{right()},
        Carousel::Real{top()}
      }
    };

    return array;
  }

  Rectangle
  Rectangle::
  letter()
  {
    return Rectangle{0, 0, 612, 792};
  }

  Rectangle
  Rectangle::
  legal()
  {
    return Rectangle{0, 0, 612, 1008};
  }

  Rectangle
  Rectangle::
  tabloid()
  {
    return Rectangle{0, 0, 792, 1224};
  }

  Rectangle
  Rectangle::
  a3()
  {
    return Rectangle{0, 0, 842, 1191};
  }

  Rectangle
  Rectangle::
  a4()
  {
    return Rectangle{0, 0, 595, 842};
  }

  Rectangle
  Rectangle::
  a5()
  {
    return Rectangle{0, 0, 420, 595};
  }

  Rectangle
  Rectangle::
  c3()
  {
    return Rectangle{0, 0, 918, 1296};
  }

  Rectangle
  Rectangle::
  c4()
  {
    return Rectangle{0, 0, 649, 918};
  }

  Rectangle
  Rectangle::
  c5()
  {
    return Rectangle{0, 0, 459, 649};
  }

  Rectangle
  Rectangle::
  executive()
  {
    return Rectangle{0, 0, 522, 756};
  }

} // namespace Art::Paperback
