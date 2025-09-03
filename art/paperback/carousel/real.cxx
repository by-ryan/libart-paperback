#include <art/paperback/carousel/real.hxx>

namespace Art::Paperback::Carousel
{

  Real::
  Real()
  {}

  Real::
  Real(double value)
    : _data{value}
  {}

  Real::
  Real(Real const& other)
    : _data{other._data}
  {}

  Real::
  Real(Real&& other)
    : _data{other._data}
  {}

  Real::
  ~Real() noexcept
  {}

  double const&
  Real::
  operator*() const
  {
    return _data;
  }

  Real&
  Real::
  operator=(Real const& other)
  {
    if (this != &other) {
      _data = other._data;

      if (auto ptr = owner(); ptr) {
        ptr->mark_as_modified();
      }
    }

    return *this;
  }

  Real&
  Real::
  operator=(Real&& other)
  {
    return *this = other;
  }

  bool
  Real::
  operator==(Real const& other) const
  {
    return _data == other._data;
  }

  bool
  Real::
  operator!=(Real const& other) const
  {
    return !(*this == other);
  }

} // namespace Art::Paperback::Carousel
