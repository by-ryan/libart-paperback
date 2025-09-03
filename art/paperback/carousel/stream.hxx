#ifndef art__paperback__carousel__stream_hxx_
#define art__paperback__carousel__stream_hxx_

#include <art/paperback/types.hxx>
#include <art/paperback/forward.hxx>

#include <art/paperback/carousel/object-model.hxx>

namespace Art::Paperback::Carousel
{

  /// Represents a COS stream.
  ///
  class Stream
    : public Object_model::Value_base
  {
  public:
    /// Constructor.
    ///
    Stream();

    /// Constructor.
    ///
    Stream(Stream const&);

    /// Constructor.
    ///
    Stream(Stream&&);

    /// Destructor.
    ///
    ~Stream() noexcept;

    /// Clear stream.
    ///
    void
    clear();

    /// Returns the stream metadata as a dictionary.
    ///
    Dictionary
    as_dictionary() const;

    /// Access the buffer as a string.
    ///
    string
    str() const;

    /// Access buffer.
    ///
    std::basic_streambuf<char>*
    rdbuf() const;

    /// Access data stream.
    ///
    iostream*
    operator->();

    /// Access data stream.
    ///
    iostream const*
    operator->() const;

    /// Access data stream.
    ///
    iostream&
    operator*();

    /// Access data stream.
    ///
    iostream const&
    operator*() const;

    /// Assignment.
    ///
    Stream&
    operator=(Stream const&);

    /// Assignment.
    ///
    Stream&
    operator=(Stream&&);

    /// Comparison.
    ///
    bool
    operator==(Stream const&) const;

    /// Comparison.
    ///
    bool
    operator!=(Stream const&) const;

  private:
    struct Internal;
    unique_ptr<Internal> _internal;

  };

  /// Access stream object.
  ///
  iostream&
  stream_cast(Object&);

} // namespace Art::Paperback::Carousel

#endif
