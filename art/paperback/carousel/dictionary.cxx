#include <art/paperback/carousel/dictionary.hxx>

#include <art/paperback/carousel/object.hxx>
#include <art/paperback/carousel/undefined.hxx>

namespace Art::Paperback::Carousel
{

  Dictionary::
  Dictionary()
  {}

  Dictionary::
  Dictionary(map<Name, Object> data)
    : _data{std::move(data)}
  {}

  Dictionary::
  Dictionary(Dictionary const& other)
    : _data{other._data}
  {}

  Dictionary::
  Dictionary(Dictionary&& other)
    : _data{other._data}
  {}

  Dictionary::
  ~Dictionary() noexcept
  {}

  size_t
  Dictionary::
  size() const
  {
    return _data.size();
  }

  bool
  Dictionary::
  empty() const
  {
    return _data.empty();
  }

  bool
  Dictionary::
  contains(Name const& key)
  {
    return _data.contains(key);
  }

  Object&
  Dictionary::
  at(Name const& key)
  {
    return _data.at(key);
  }

  Object const&
  Dictionary::
  at(Name const& key) const
  {
    return _data.at(key);
  }

  Dictionary::iterator
  Dictionary::
  begin()
  {
    return _data.begin();
  }

  Dictionary::const_iterator
  Dictionary::
  begin() const
  {
    return _data.begin();
  }

  Dictionary::const_iterator
  Dictionary::
  cbegin() const
  {
    return _data.cbegin();
  }

  Dictionary::iterator
  Dictionary::
  end()
  {
    return _data.end();
  }

  Dictionary::const_iterator
  Dictionary::
  end() const
  {
    return _data.end();
  }

  Dictionary::const_iterator
  Dictionary::
  cend() const
  {
    return _data.cend();
  }

  void
  Dictionary::
  insert(Name const& key, Object object)
  {
    if (is_of_type<Undefined>(object)) {
      erase(key);
      return;
    }

    auto [it, _] = _data.insert_or_assign(key, object);

    if (auto ptr = owner(); ptr) {
      it->second.attach(*ptr);
      ptr->mark_as_modified();
    }
  }

  void
  Dictionary::
  erase(Name const& key)
  {
    _data.erase(key);

    if (auto ptr = owner(); ptr) {
      ptr->mark_as_modified();
    }
  }

  Dictionary&
  Dictionary::
  operator=(Dictionary const& other)
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

  Dictionary&
  Dictionary::
  operator=(Dictionary&& other)
  {
    return operator=(other);
  }

  bool
  Dictionary::
  operator==(Dictionary const& other) const
  {
    return _data == other._data;
  }

  bool
  Dictionary::
  operator!=(Dictionary const& other) const
  {
    return !(*this == other);
  }

  void
  Dictionary::
  attach_children(Object_model::Owner& owner)
  {
    for (auto& j : _data) {
      j.second.attach(owner);
    }
  }

} // namespace Art::Paperback::Carousel
