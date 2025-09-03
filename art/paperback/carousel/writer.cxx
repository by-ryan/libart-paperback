#include <art/paperback/carousel/writer.hxx>

#include <art/paperback/carousel/object.hxx>

#include <art/paperback/carousel/array.hxx>
#include <art/paperback/carousel/boolean.hxx>
#include <art/paperback/carousel/dictionary.hxx>
#include <art/paperback/carousel/integer.hxx>
#include <art/paperback/carousel/name.hxx>
#include <art/paperback/carousel/real.hxx>
#include <art/paperback/carousel/stream.hxx>
#include <art/paperback/carousel/text.hxx>

#include <art/paperback/except.hxx>

#include <art/unicode/writer.hxx>
#include <art/unicode/utf8-encoder.hxx>

#include <iomanip>

namespace Art::Paperback::Carousel
{

  /// \param output The output stream to write to.
  /// \param major The major version of the document to write.
  /// \param minor The minor version of the document to write.
  ///
  Writer::
  Writer(ostream& output, int major, int minor)
    : _output{output},
      _major{major},
      _minor{minor}
  {}

  /// \return Returns a reference to the underlying output stream.
  ///
  ostream&
  Writer::
  output()
  {
    return _output;
  }

  /// This function will automatically write a binary comment immediately
  /// following the COS-file header, as per the recommendation of the PDF-1.4
  /// specification.
  ///
  /// \param header The COS-file header.
  ///
  void
  Writer::
  write_header(string const& header)
  {
    output() << '%' << header << "\r\n" << "%\x80\xff\x80\xff\r\n";
  }

  /// \param identity The identity of the object.
  /// \param container The object container.
  ///
  void
  Writer::
  write_object(Identity const& identity,
               Object_model::Container_base const& container)
  {
    output() << identity.index << ' '
             << identity.generation << " obj\r\n";

    dispatch_emit(container);

    if (container.type() == typeid(Stream)) {
      auto str = container.get<Stream>().str();

      output() << "\r\nstream\r\n";
      output().write(str.c_str(), str.size());
      output() << "\r\nendstream";
    }

    output() << "\r\nendobj\r\n";
  }

  void
  Writer::
  begin_xref()
  {
    output() << "xref\r\n";
  }

  /// \param index The first index of this chunk.
  /// \param count The size of this chunk.
  ///
  void
  Writer::
  begin_xref_chunk(Index index, uint16_t count)
  {
    output() << index << ' ' << count << "\r\n";
  }

  /// \param offset The offset of the entry.
  /// \param generation The generation of the entry.
  ///
  void
  Writer::
  write_xref_used_entry(streamoff offset, Generation generation)
  {
    using std::setfill;
    using std::setw;

    std::ostringstream str;
    str << setw(10) << setfill('0') << offset << ' ';
    str << setw(5) << setfill('0') << generation << " n\r\n";

    output() << str.str();
  }

  /// \param next The index of the next entry.
  /// \param generation The next generation number of the entry.
  ///
  void
  Writer::
  write_xref_free_entry(Index next, Generation generation)
  {
    using std::setfill;
    using std::setw;

    std::ostringstream str;
    str << setw(10) << setfill('0') << next << ' ';
    str << setw(5) << setfill('0') << generation << " f\r\n";

    output() << str.str();
  }

  /// \param dictionary The trailer dictionary.
  ///
  void
  Writer::
  write_trailer(Dictionary const& dictionary)
  {
    output() << "trailer\r\n";
    emit(dictionary);
    output() << "\r\n";
  }

  /// \param xref_offset The offset of the cross-reference table.
  ///
  void
  Writer::
  write_eof(streamoff xref_offset)
  {
    output() << "startxref\r\n";
    output() << xref_offset << "\r\n";
    output() << "%%EOF\r\n";
  }

  /// \param index The object reference index.
  /// \param generation The object reference generation.
  ///
  void
  Writer::
  emit_reference(Identity const& identity)
  {
    output() << identity.index << ' ' << identity.generation << ' ' << 'R';
  }

  void
  Writer::
  emit(Undefined const&)
  {
    output() << "null";
  }

  /// \param boolean The boolean to write.
  ///
  void
  Writer::
  emit(Boolean const& boolean)
  {
    output() << (*boolean ? "true" : "false");
  }

  /// \param integer The integer to write.
  ///
  void
  Writer::
  emit(Integer const& integer)
  {
    output() << *integer;
  }

  /// \param real The real to write.
  ///
  void
  Writer::
  emit(Real const& real)
  {
    stringstream str;
    str.imbue(std::locale::classic());
    str << std::fixed << *real;
    output() << str.str();
  }

  /// \param text The text to write.
  ///
  void
  Writer::
  emit(Text const& text)
  {
    auto to_hex = [](char c) -> char
    {
      return (c < 10) ? ('0' + c) : ('a' + (c - 10));
    };

    switch (text.convention()) {
      case Text::Convention::literal: {
        output() << '(';

        for (auto const& j : *text) {
          switch (j) {
            case '\n':
              output() << "\\n";
              break;

            case '\r':
              output() << "\\r";
              break;

            case '\t':
              output() << "\\t";
              break;

            case '\b':
              output() << "\\b";
              break;

            case '\f':
              output() << "\\f";
              break;

            case '(':
              output() << "\\(";
              break;

            case ')':
              output() << "\\)";
              break;

            case '\\':
              output() << "\\\\";
              break;

            default:
              output() << j;
              break;
          }
        }

        output() << ')';

        return;
      }

      case Text::Convention::hexadecimal: {
        output() << '<';

        for (auto const& j : *text) {
          char high = (j & 0xF0) >> 4;
          char low = (j & 0x0F);

          output() << to_hex(high) << to_hex(low);
        }

        output() << '>';

        return;
      }
    }

    raise<Internal_error>{} << "unhandled text convention";
  }

  void
  Writer::
  emit(Name const& name)
  {
    if (_major == 1 && _minor < 2) {
      output() << *name;
      return;
    }

    auto to_hex = [](char c) -> char
    {
      return (c < 10) ? ('0' + c) : ('a' + (c - 10));
    };

    output() << '/';

    for (auto const& j : *name) {
      if (j == '#') {
        output() << "#23";
      }
      else if (33 <= j && j <= 126) {
        output() << j;
      }
      else {
        char high = (j & 0xF0) >> 4;
        char low = (j & 0x0F);

        output() << "#" << to_hex(high) << to_hex(low);
      }
    }
  }

  void
  Writer::
  emit(Array const& array)
  {
    output() << "[ ";

    auto it = array.begin();

    if (it == array.end()) {
      output() << "]";
      return;
    }

    auto base_indent = _indent;
    _indent += 1;

    dispatch_emit(*it);
    ++it;

    for (; it != array.end(); ++it) {
      new_line();
      output() << ' ';
      dispatch_emit(*it);
    }

    _indent = base_indent;

    new_line();

    output() << ']';
  }

  void
  Writer::
  emit(Dictionary const& dictionary)
  {
    output() << "<< ";

    auto it = dictionary.begin();

    if (it == dictionary.end()) {
      output() << ">>";
      return;
    }

    auto base_indent = _indent;

    emit(it->first);
    output() << ' ';
    _indent = base_indent + it->first->length() + 5;
    dispatch_emit(it->second);
    ++it;
    _indent = base_indent;
    new_line();

    for (; it != dictionary.end(); ++it) {
      output() << "   ";
      emit(it->first);
      output() << " ";
      _indent = base_indent + it->first->length() + 5;
      dispatch_emit(it->second);
      _indent = base_indent;
      new_line();
    }

    _indent = base_indent;

    output() << ">>";
  }

  void
  Writer::
  dispatch_emit(Object const& object)
  {
    // If the object is an indirect object we emit a reference (N N R)
    // instead of the object value.
    //
    if (object.is_reference()) {
      emit_reference(object.identity());
      return;
    }

    dispatch_emit(object.container());
  }

  void
  Writer::
  dispatch_emit(Object_model::Container_base const& container)
  {

    // Else emit the object directly.
    //
    struct dispatcher : Visitor,
                        Basic_visitor<Undefined >,
                        Basic_visitor<Boolean>,
                        Basic_visitor<Integer>,
                        Basic_visitor<Real>,
                        Basic_visitor<Text>,
                        Basic_visitor<Name>,
                        Basic_visitor<Array>,
                        Basic_visitor<Dictionary>,
                        Basic_visitor<Stream> {
      Writer& w;

      explicit
      dispatcher(Writer& w)
        : w{w}
      {}

      void
      visit(Undefined const& v) override
      {
        w.emit(v);
      }

      void
      visit(Boolean const& v) override
      {
        w.emit(v);
      }

      void
      visit(Integer const& v) override
      {
        w.emit(v);
      }

      void
      visit(Real const& v) override
      {
        w.emit(v);
      }

      void
      visit(Text const& v) override
      {
        w.emit(v);
      }

      void
      visit(Name const& v) override
      {
        w.emit(v);
      }

      void
      visit(Array const& v) override
      {
        w.emit(v);
      }

      void
      visit(Dictionary const& v) override
      {
        w.emit(v);
      }

      void
      visit(Stream const& v) override
      {
        w.emit(v.as_dictionary());
      }
    };

    dispatcher d{*this};
    container.do_accept(d);
  }

  void
  Writer::
  new_line()
  {
    output() << "\r\n" << std::string(_indent, ' ');
  }

} // namespace Art::Paperback::Carousel
