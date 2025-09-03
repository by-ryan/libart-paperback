#ifndef art__paperback__carousel__writer_hxx_
#define art__paperback__carousel__writer_hxx_

#include <art/paperback/types.hxx>
#include <art/paperback/forward.hxx>

#include <art/paperback/carousel/object-model.hxx>

namespace Art::Paperback::Carousel
{

  class Writer
  {
  public:
    /// Constructor.
    ///
    Writer(ostream&, int, int);

    /// Access the underlying output stream.
    ///
    ostream&
    output();

    /// Write a COS-file header.
    ///
    void
    write_header(string const&);

    /// Write an object.
    ///
    void
    write_object(Identity const&, Object_model::Container_base const&);

    /// Begin a new cross-reference table.
    ///
    void
    begin_xref();

    /// Begin a new cross-reference table chunk.
    ///
    void
    begin_xref_chunk(Index, uint16_t);

    /// Write a used entry.
    ///
    void
    write_xref_used_entry(streamoff, Generation);

    /// Write a free entry.
    ///
    void
    write_xref_free_entry(Index, Generation);

    /// Write a COS-file trailer.
    ///
    void
    write_trailer(Dictionary const&);

    /// Write an EOF marker.
    ///
    void
    write_eof(streamoff);

  private:
    /// Emit a reference to an indirect object.
    ///
    void
    emit_reference(Identity const&);

    /// Emit undefined.
    ///
    void
    emit(Undefined const&);

    /// Emit a boolean object.
    ///
    void
    emit(Boolean const&);

    /// Emit an integer object.
    ///
    void
    emit(Integer const&);

    /// Emit a real object.
    ///
    void
    emit(Real const&);

    /// Emit a text object.
    ///
    void
    emit(Text const&);

    /// Emit a name object.
    ///
    void
    emit(Name const&);

    /// Emit an array object.
    ///
    void
    emit(Array const&);

    /// Emit a dictionary object.
    ///
    void
    emit(Dictionary const&);

    /// Dispatch the emission of an object.
    ///
    void
    dispatch_emit(Object const&);

    /// Dispatch the emission of an object.
    ///
    void
    dispatch_emit(Object_model::Container_base const&);

    /// Write a new line marker.
    ///
    void
    new_line();

  private:
    Writer(Writer const&) = delete;
    Writer(Writer&&) = delete;
    Writer& operator=(Writer const&) = delete;
    Writer& operator=(Writer&&) = delete;

  private:
    ostream& _output;
    int _major{};
    int _minor{};

    string::size_type _indent{};

  };

} // namespace Art::Paperback::Carousel

#endif
