#ifndef art__paperback__carousel__real_hxx_
#define art__paperback__carousel__real_hxx_

#include <art/paperback/types.hxx>
#include <art/paperback/forward.hxx>

#include <art/paperback/carousel/object-model.hxx>

namespace Art::Paperback::Carousel
{

  /// Represents a COS real.
  ///
  class Real
    : public Object_model::Value_base
  {
  public:
    /// Constructor.
    ///
    Real();

    /// Constructor.
    ///
    Real(double);

    /// Constructor.
    ///
    Real(Real const&);

    /// Constructor.
    ///
    Real(Real&&);

    /// Destructor.
    ///
    ~Real() noexcept;

    /// Access real.
    ///
    double const&
    operator*() const;

    /// Assignment.
    ///
    Real&
    operator=(Real const&);

    /// Assignment.
    ///
    Real&
    operator=(Real&&);

    /// Comparison.
    ///
    bool
    operator==(Real const&) const;

    /// Comparison.
    ///
    bool
    operator!=(Real const&) const;

  private:
    double _data{};

  };

} // namespace Art::Paperback::Carousel

#endif
