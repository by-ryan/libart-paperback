#include <art/paperback/carousel/text.hxx>

namespace Art::Paperback::Carousel
{

  /// \class Text
  ///
  /// The Text class does not impose any limit on the length of the
  /// text string.

  Text::
  Text(Convention convention)
    : _convention{convention}
  {}

  Text::
  Text(string data, Convention convention)
    : _convention{convention},
      _data{std::move(data)}
  {}

  Text::
  Text(char const* data, Convention convention)
    : _convention{convention},
      _data{data}
  {}

  Text::
  Text(Text const& other)
    : _data{other._data}
  {}

  Text::
  Text(Text&& other)
    : _data{std::move(other._data)}
  {}

  Text::
  ~Text() noexcept
  {}

  Text::Convention
  Text::
  convention() const
  {
    return _convention;
  }

  string const&
  Text::
  operator*() const
  {
    return _data;
  }

  string const*
  Text::
  operator->() const
  {
    return &_data;
  }

  Text&
  Text::
  operator=(Text const& other)
  {
    if (this != &other) {
      _convention = other._convention;
      _data = other._data;

      if (auto ptr = owner(); ptr) {
        ptr->mark_as_modified();
      }
    }

    return *this;
  }

  Text&
  Text::
  operator=(Text&& other)
  {
    return *this = other;
  }

  /// This function only compares the string value of \c this with \a
  /// other. The text convention used by either string is ignored.
  ///
  bool
  Text::
  operator==(Text const& other) const
  {
    return _data == other._data;
  }

  /// This function only compares the string value of \c this with \a
  /// other. The text convention used by either string is ignored.
  ///
  bool
  Text::
  operator!=(Text const& other) const
  {
    return !(*this == other);
  }

  bool
  Text::
  operator<(Text const& other) const
  {
    return _data < other._data;
  }

  bool
  Text::
  operator<=(Text const& other) const
  {
    return _data <= other._data;
  }

  bool
  Text::
  operator>(Text const& other) const
  {
    return _data > other._data;
  }

  bool
  Text::
  operator>=(Text const& other) const
  {
    return _data >= other._data;
  }

} // namespace Art::Paperback::Carousel
