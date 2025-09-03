#ifndef art__paperback__carousel__integer_hxx_
#define art__paperback__carousel__integer_hxx_

#include <art/paperback/types.hxx>
#include <art/paperback/forward.hxx>

#include <art/paperback/carousel/object-model.hxx>

namespace Art::Paperback::Carousel
{

  /// Represents a COS integer.
  ///
  class Integer
    : public Object_model::Value_base
  {
  public:
    /// Constructor.
    ///
    Integer(int64_t);

    /// Constructor.
    ///
    Integer(Integer const&);

    /// Constructor.
    ///
    Integer(Integer&&);

    /// Destructor.
    ///
    ~Integer() noexcept;

    /// Access integer.
    ///
    int64_t const&
    operator*() const;

    /// Assignment.
    ///
    Integer&
    operator=(Integer const&);

    /// Assignment.
    ///
    Integer&
    operator=(Integer&&);

    /// Comparison.
    ///
    bool
    operator==(Integer const&) const;

    /// Comparison.
    ///
    bool
    operator!=(Integer const&) const;

  private:
    int64_t _data{};

  };

} // namespace Art::Paperback::Carousel

#endif
