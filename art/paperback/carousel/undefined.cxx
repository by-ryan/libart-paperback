#include <art/paperback/carousel/undefined.hxx>

namespace Art::Paperback::Carousel
{
  Undefined::
  Undefined()
  {}

  Undefined::
  Undefined(Undefined const&)
  {}

  Undefined::
  Undefined(Undefined&&)
  {}

  Undefined::
  ~Undefined() noexcept
  {}

  Undefined&
  Undefined::
  operator=(Undefined const&)
  {
    return *this;
  }

  Undefined&
  Undefined::
  operator=(Undefined&&)
  {
    return *this;
  }

  bool
  Undefined::
  operator==(Undefined const&) const
  {
    return true;
  }

  bool
  Undefined::
  operator!=(Undefined const&) const
  {
    return false;
  }

} // namespace Art::Paperback::Carousel
