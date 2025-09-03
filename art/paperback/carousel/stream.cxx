#include <art/paperback/carousel/stream.hxx>

#include <art/paperback/carousel/dictionary.hxx>
#include <art/paperback/carousel/integer.hxx>
#include <art/paperback/carousel/name.hxx>
#include <art/paperback/carousel/object.hxx>

namespace Art::Paperback::Carousel
{

  struct Stream::Internal
  {
    Internal()
    {}

    stringstream data;

  };

  /// \class Stream
  ///
  /// A stream is a special COS object type containing a data stream
  /// of bytes. A stream object is always an indirect object.
  ///

  Stream::
  Stream()
    : _internal{new Internal{}}
  {}

  Stream::
  Stream(Stream const& other)
    : _internal{new Internal{}}
  {
    _internal->data.str(other._internal->data.str());
  }

  Stream::
  Stream(Stream&& other)
    : _internal{new Internal{}}
  {
    _internal->data.str(other._internal->data.str());
  }

  Stream::
  ~Stream() noexcept
  {}

  void
  Stream::
  clear()
  {
    _internal->data.str(string{});

    if (auto ptr = owner(); ptr) {
      ptr->mark_as_modified();
    }
  }

  Dictionary
  Stream::
  as_dictionary() const
  {
    _internal->data.seekg(0, std::ios::end);
    auto size = _internal->data.tellg();

    Dictionary dictionary;

    dictionary.insert(
      "Length",
      Integer{static_cast<int64_t>(size)}
    );

    return dictionary;
  }

  string
  Stream::
  str() const
  {
    return _internal->data.str();
  }

  std::basic_streambuf<char>*
  Stream::
  rdbuf() const
  {
    _internal->data.seekg(0);
    return _internal->data.rdbuf();
  }

  iostream*
  Stream::
  operator->()
  {
    if (auto ptr = owner(); ptr) {
      ptr->mark_as_modified();
    }

    return &_internal->data;
  }

  iostream const*
  Stream::
  operator->() const
  {
    return &_internal->data;
  }

  iostream&
  Stream::
  operator*()
  {
    if (auto ptr = owner(); ptr) {
      ptr->mark_as_modified();
    }

    return _internal->data;
  }

  iostream const&
  Stream::
  operator*() const
  {
    return _internal->data;
  }

  Stream&
  Stream::
  operator=(Stream const& other)
  {
    if (this != &other) {
      _internal->data.str(other._internal->data.str());

      if (auto ptr = owner(); ptr) {
        ptr->mark_as_modified();
      }
    }

    return *this;
  }

  Stream&
  Stream::
  operator=(Stream&& other)
  {
    return *this = other;
  }

  bool
  Stream::
  operator==(Stream const& other) const
  {
    return _internal->data.str() == other._internal->data.str();
  }

  bool
  Stream::
  operator!=(Stream const& other) const
  {
    return !(*this == other);
  }

  /// \param object The object containing a stream.
  /// \return Returns a reference to the iostream.
  ///
  iostream&
  stream_cast(Object& object)
  {
    return *object_cast<Stream>(object);
  }

} // namespace Art::Paperback::Carousel
