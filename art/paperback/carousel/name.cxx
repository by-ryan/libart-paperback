#include <art/paperback/carousel/name.hxx>

namespace Art::Paperback::Carousel
{

  Name::
  Name()
  {}

  Name::
  Name(string data)
    : _data{std::move(data)}
  {}

  Name::
  Name(char const* data)
    : _data{data}
  {}

  Name::
  Name(Name const& other)
    : _data{other._data}
  {}

  Name::
  Name(Name&& other)
    : _data{std::move(other._data)}
  {}

  Name::
  ~Name() noexcept
  {}

  string const&
  Name::
  operator*() const
  {
    return _data;
  }

  string const*
  Name::
  operator->() const
  {
    return &_data;
  }

  Name&
  Name::
  operator=(Name const& other)
  {
    if (this != &other) {
      _data = other._data;

      if (auto ptr = owner(); ptr) {
        ptr->mark_as_modified();
      }
    }

    return *this;
  }

  Name&
  Name::
  operator=(Name&& other)
  {
    return *this = other;
  }

  bool
  Name::
  operator==(Name const& other) const
  {
    return _data == other._data;
  }

  bool
  Name::
  operator!=(Name const& other) const
  {
    return !(*this == other);
  }

  bool
  Name::
  operator<(Name const& other) const
  {
    return _data < other._data;
  }

  bool
  Name::
  operator<=(Name const& other) const
  {
    return _data <= other._data;
  }

  bool
  Name::
  operator>(Name const& other) const
  {
    return _data > other._data;
  }

  bool
  Name::
  operator>=(Name const& other) const
  {
    return _data >= other._data;
  }

} // namespace Art::Paperback::Carousel
