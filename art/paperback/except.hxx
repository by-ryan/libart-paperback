#ifndef art__paperback__exception_hxx_
#define art__paperback__exception_hxx_

#include <art/paperback/types.hxx>

#include <source_location>

namespace Art::Paperback
{

  /// Base class for errors.
  ///
  class Fault
    : public runtime_error
  {
  public:
    /// Constructor.
    ///
    /// \param origin The C++ source origin of the exception.
    /// \param what A description of the error.
    ///
    Fault(std::source_location origin, string what)
      : runtime_error{std::move(what)},
        _origin{std::move(origin)}
    {}

    /// Access the C++ source origin of the exception.
    ///
    std::source_location const&
    origin() const;

  private:
    std::source_location _origin;

  };

  /// Exception class used to indicate internal errors, typically the result
  /// of an insect hiding somewhere. If found, please be so kind and squash it
  /// mercilessly.
  ///
  class Internal_error
    : public Fault
  {
  public:
    using Fault::Fault;

  };

  /// Exception class used to indicate too low document version.
  ///
  class Upgrade_required
    : public Fault
  {
  public:
    using Fault::Fault;

  };

  /// Exception class used to indicate an invalid operation.
  ///
  class Invalid_operation
    : public Fault
  {
  public:
    using Fault::Fault;

  };

  /// Helper to throw exceptions.
  ///
  template<typename T>
  class raise
  {
  public:
    raise(std::source_location origin = std::source_location::current())
      : _origin{origin}
    {}

    /// Copy-construction is prohibited.
    ///
    raise(raise const&) = delete;

    /// Move-construction is prohibited.
    ///
    raise(raise&&) = delete;

    [[noreturn]]
    ~raise() noexcept(false)
    {
      throw T{_origin, _str.str()};
    }

    /// Copy-assignment is prohibited.
    ///
    raise& operator=(raise const&) = delete;

    /// Move-assignment is prohibited.
    ///
    raise& operator=(raise&&) = delete;

    template<typename U>
    raise<T>&
    operator<<(U const& other)
    {
      _str << other;
      return *this;
    }

  private:
    std::source_location _origin;
    stringstream _str;

  };

} // namespace Art::Paperback

#endif
