#ifndef libart_paperback__visitor_hxx_
#define libart_paperback__visitor_hxx_

namespace Art::Paperback
{

  /// Virtual base class for visitors.
  ///
  class Visitor
  {
  protected:
    Visitor() = default;

    virtual
    ~Visitor() noexcept = default;

  };

  /// Base class for visitors of type T.
  ///
  template<typename T>
  class Basic_visitor
  {
  public:
    /// Visit.
    ///
    /// \param visitee The visitee.
    ///
    virtual
    void
    visit(T& visitee)
    {
      visit(const_cast<T const&>(visitee));
    }

    /// Visit.
    ///
    /// \param visitee The visitee.
    ///
    virtual
    void
    visit(T const& visitee) = 0;

  protected:
    /// Constructor.
    ///
    Basic_visitor() = default;

    /// Destructor.
    ///
    virtual
    ~Basic_visitor() noexcept = default;

  };

  /// Accept visitor on visitee.
  ///
  /// \param visitee The visitee.
  /// \param v The visitor.
  ///
  template<typename T>
  void
  accept(T const& visitee, Visitor& v)
  {
    auto& v_cast = dynamic_cast<Basic_visitor<T>&>(v);
    v_cast.visit(visitee);
  }

} // namespace Art::Paperback

#endif
