#ifndef art__paperback__carousel__text_hxx_
#define art__paperback__carousel__text_hxx_

#include <art/paperback/types.hxx>
#include <art/paperback/forward.hxx>

#include <art/paperback/carousel/object-model.hxx>

namespace Art::Paperback::Carousel
{

  /// Represents COS text.
  ///
  class Text
    : public Object_model::Value_base
  {
  public:
    /// Enumeration of text conventions.
    ///
    /// See Section 3.2.3, "String Objects" in the PDF-1.4 specification
    /// for details about text strings and their representation.
    ///
    enum class Convention
    {
      /// Indicates the literal convention. When used, the text string
      /// will be written verbatim to the output file, enclosed in
      /// parentheses.
      ///
      /// Special characters will be written as escape-sequences.
      ///
      literal,

      /// Indicates the hexadecimal convention. When used, the text
      /// string will be written as a sequence of hexadecimal digits,
      /// enclosed within angle brackets.
      ///
      /// The size of the written data will be double the length of
      /// the text string when this convention is used.
      ///
      hexadecimal

    };

    /// Constructor.
    ///
    Text(Convention = Convention::literal);

    /// Constructor.
    ///
    Text(string, Convention = Convention::literal);

    /// Constructor.
    ///
    Text(char const*, Convention = Convention::literal);

    /// Constructor.
    ///
    Text(Text const&);

    /// Constructor.
    ///
    Text(Text&&);

    /// Destructor.
    ///
    ~Text() noexcept;

    /// Get the text convention used for this object.
    ///
    Convention
    convention() const;

    /// Access text string.
    ///
    string const&
    operator*() const;

    /// Access text string.
    ///
    string const*
    operator->() const;

    /// Assignment.
    ///
    Text&
    operator=(Text const&);

    /// Assignment.
    ///
    Text&
    operator=(Text&&);

    /// Comparison.
    ///
    bool
    operator==(Text const&) const;

    /// Comparison.
    ///
    bool
    operator!=(Text const&) const;

    /// Comparison.
    ///
    bool
    operator<(Text const&) const;

    /// Comparison.
    ///
    bool
    operator<=(Text const&) const;

    /// Comparison.
    ///
    bool
    operator>(Text const&) const;

    /// Comparison.
    ///
    bool
    operator>=(Text const&) const;

  private:
    Convention _convention;
    string _data;

  };

} // namespace Art::Paperback::Carousel

#endif
