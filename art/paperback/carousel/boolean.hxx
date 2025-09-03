#ifndef art__paperback__carousel__boolean_hxx_
#define art__paperback__carousel__boolean_hxx_

#include <art/paperback/types.hxx>
#include <art/paperback/forward.hxx>

#include <art/paperback/carousel/object-model.hxx>

namespace Art::Paperback::Carousel
{

  /// Represents a COS boolean.
  ///
  class Boolean
    : public Object_model::Value_base
  {
  public:
    /// Constructor.
    ///
    Boolean();

    /// Constructor.
    ///
    Boolean(bool);

    /// Constructor.
    ///
    Boolean(Boolean const&);

    /// Constructor.
    ///
    Boolean(Boolean&&);

    /// Destructor.
    ///
    ~Boolean() noexcept;

    /// Access boolean.
    ///
    bool const&
    operator*() const;

    /// Assignment.
    ///
    Boolean&
    operator=(Boolean const&);

    /// Assignment.
    ///
    Boolean&
    operator=(Boolean&&);

    /// Comparison.
    ///
    bool
    operator==(Boolean const&) const;

    /// Comparison.
    ///
    bool
    operator!=(Boolean const&) const;

  private:
    bool _data{};

  };

} // namespace Art::Paperback::Carousel

#endif
