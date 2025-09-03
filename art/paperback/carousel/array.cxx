#include <art/paperback/carousel/array.hxx>

#include <art/paperback/carousel/object.hxx>

namespace Art::Paperback::Carousel
{

  Array::
  Array()
  {}

  Array::
  Array(vector<Object> init)
    : _data{init.begin(), init.end()}
  {}

  Array::
  Array(Array const& other)
    : _data{other._data}
  {}

  Array::
  Array(Array&& other)
    : _data{other._data}
  {}

  Array::
  ~Array() noexcept
  {}

  size_t
  Array::
  size() const
  {
    return _data.size();
  }

  bool
  Array::
  empty() const
  {
    return _data.empty();
  }

  Object&
  Array::
  front()
  {
    return _data.front();
  }

  Object const&
  Array::
  front() const
  {
    return _data.front();
  }

  Object&
  Array::
  back()
  {
    return _data.back();
  }

  Object const&
  Array::
  back() const
  {
    return _data.back();
  }

  Array::iterator
  Array::
  begin()
  {
    return _data.begin();
  }

  Array::const_iterator
  Array::
  begin() const
  {
    return _data.begin();
  }

  Array::const_iterator
  Array::
  cbegin() const
  {
    return _data.cbegin();
  }

  Array::iterator
  Array::
  end()
  {
    return _data.end();
  }

  Array::const_iterator
  Array::
  end() const
  {
    return _data.end();
  }

  Array::const_iterator
  Array::
  cend() const
  {
    return _data.cend();
  }

  Object&
  Array::
  push_front(Object const& object)
  {
    _data.push_front(object);

    if (auto ptr = owner(); ptr) {
      front().attach(*ptr);
      ptr->mark_as_modified();
    }

    return _data.front();
  }

  Object&
  Array::
  push_back(Object const& object)
  {
    _data.push_back(object);

    if (auto ptr = owner(); ptr) {
      back().attach(*ptr);
      ptr->mark_as_modified();
    }

    return _data.back();
  }

  void
  Array::
  pop_front()
  {
    _data.pop_front();
  }

  void
  Array::
  pop_back()
  {
    _data.pop_back();
  }

  Array&
  Array::
  operator=(Array const& other)
  {
    if (this != &other) {
      _data = other._data;

      if (auto ptr = owner(); ptr) {
        ptr->mark_as_modified();
        attach_children(*ptr);
      }
    }

    return *this;
  }

  Array&
  Array::
  operator=(Array&& other)
  {
    return *this = other;
  }

  bool
  Array::
  operator==(Array const& other) const
  {
    return _data == other._data;
  }

  bool
  Array::
  operator!=(Array const& other) const
  {
    return !(*this == other);
  }

  void
  Array::
  attach_children(Object_model::Owner& owner)
  {
    for (auto& j : _data) {
      j.attach(owner);
    }
  }

} // namespace Art::Paperback::Carousel
