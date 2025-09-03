#include <art/paperback/carousel/integer.hxx>

namespace Art::Paperback::Carousel
{

  Integer::
  Integer(int64_t value)
    : _data{value}
  {}

  Integer::
  Integer(Integer const& other)
    : _data{other._data}
  {}

  Integer::
  Integer(Integer&& other)
    : _data{other._data}
  {}

  Integer::
  ~Integer() noexcept
  {}

  int64_t const&
  Integer::
  operator*() const
  {
    return _data;
  }

  Integer&
  Integer::
  operator=(Integer const& other)
  {
    _data = other._data;

    if (auto ptr = owner(); ptr) {
      ptr->mark_as_modified();
    }

    return *this;
  }

  Integer&
  Integer::
  operator=(Integer&& other)
  {
    _data = other._data;

    if (auto ptr = owner(); ptr) {
      ptr->mark_as_modified();
    }

    return *this;
  }

  bool
  Integer::
  operator==(Integer const& other) const
  {
    return _data == other._data;
  }

  bool
  Integer::
  operator!=(Integer const& other) const
  {
    return !(*this == other);
  }

} // namespace Art::Paperback::Carousel
