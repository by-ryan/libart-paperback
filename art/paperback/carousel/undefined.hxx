#ifndef art__paperback__carousel__undefined_hxx_
#define art__paperback__carousel__undefined_hxx_

#include <art/paperback/types.hxx>
#include <art/paperback/forward.hxx>

#include <art/paperback/carousel/object-model.hxx>

namespace Art::Paperback::Carousel
{

  class Undefined
    : public Object_model::Value_base
  {
  public:
    /// Constructor.
    ///
    Undefined();

    /// Constructor.
    ///
    Undefined(Undefined const&);

    /// Constructor.
    ///
    Undefined(Undefined&&);

    /// Destructor.
    ///
    ~Undefined() noexcept;

    /// Assignment.
    ///
    Undefined&
    operator=(Undefined const&);

    /// Assignment.
    ///
    Undefined&
    operator=(Undefined&&);

    /// Comparison.
    ///
    bool
    operator==(Undefined const&) const;

    /// Comparison.
    ///
    bool
    operator!=(Undefined const&) const;

  };

} // namespace Art::Paperback::Carousel

#endif
