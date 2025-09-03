#ifndef art__paperback__carousel__name_hxx_
#define art__paperback__carousel__name_hxx_

#include <art/paperback/types.hxx>
#include <art/paperback/forward.hxx>

#include <art/paperback/carousel/object-model.hxx>

namespace Art::Paperback::Carousel
{

  /// Represents a COS name.
  ///
  class Name
    : public Object_model::Value_base
  {
  public:
    /// Constructor.
    ///
    Name();

    /// Constructor.
    ///
    Name(string);

    /// Constructor.
    ///
    Name(char const*);

    /// Constructor.
    ///
    Name(Name const&);

    /// Constructor.
    ///
    Name(Name&&);

    /// Destructor.
    ///
    ~Name() noexcept;

    /// Access string value.
    ///
    string const&
    operator*() const;

    /// Access string value.
    ///
    string const*
    operator->() const;

    /// Assignment.
    ///
    Name&
    operator=(Name const&);

    /// Assignment.
    ///
    Name&
    operator=(Name&&);

    /// Comparison.
    ///
    bool
    operator==(Name const&) const;

    /// Comparison.
    ///
    bool
    operator!=(Name const&) const;

    /// Comparison.
    ///
    bool
    operator<(Name const&) const;

    /// Comparison.
    ///
    bool
    operator<=(Name const&) const;

    /// Comparison.
    ///
    bool
    operator>(Name const&) const;

    /// Comparison.
    ///
    bool
    operator>=(Name const&) const;

  private:
    string _data;

  };

} // namespace Art::Paperback::Carousel

#endif
