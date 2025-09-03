#include <art/paperback/carousel/boolean.hxx>

namespace Art::Paperback::Carousel
{

  Boolean::
  Boolean()
  {}

  Boolean::
  Boolean(bool value)
    : _data{value}
  {}

  Boolean::
  Boolean(Boolean const& other)
    : _data{other._data}
  {}

  Boolean::
  Boolean(Boolean&& other)
    : _data{other._data}
  {}

  Boolean::
  ~Boolean() noexcept
  {}

  bool const&
  Boolean::
  operator*() const
  {
    return _data;
  }

  Boolean&
  Boolean::
  operator=(Boolean const& other)
  {
    if (this != &other) {
      _data = other._data;

      if (auto ptr = owner(); ptr) {
        ptr->mark_as_modified();
      }
    }

    return *this;
  }

  Boolean&
  Boolean::
  operator=(Boolean&& other)
  {
    return *this = other;
  }

  bool
  Boolean::
  operator==(Boolean const& other) const
  {
    return _data == other._data;
  }

  bool
  Boolean::
  operator!=(Boolean const& other) const
  {
    return !(*this == other);
  }

} // namespace Art::Paperback::Carousel
