#ifndef art__paperback__carousel__object_hxx_
#define art__paperback__carousel__object_hxx_

#include <art/paperback/types.hxx>
#include <art/paperback/forward.hxx>
#include <art/paperback/visitor.hxx>

#include <art/paperback/carousel/object-model.hxx>

namespace Art::Paperback::Carousel
{

  /// Represents a COS-file object.
  ///
  class Object
  {
  public:
    /// Constructor.
    ///
    Object(Undefined const&);

    /// Constructor.
    ///
    Object(Array);

    /// Constructor.
    ///
    Object(Boolean);

    /// Constructor.
    ///
    Object(Dictionary);

    /// Constructor.
    ///
    Object(Integer);

    /// Constructor.
    ///
    Object(Name);

    /// Constructor.
    ///
    Object(Real);

    /// Constructor.
    ///
    Object(Text);

    /// Constructor.
    ///
    Object(Object const&);

    /// Constructor.
    ///
    Object(Object&&);

    /// Attach object to owner.
    ///
    void
    attach(Object_model::Owner&);

    /// Check if the objcet is a reference.
    ///
    bool
    is_reference() const;

    /// Get object identity, if reference.
    ///
    Identity const&
    identity() const;

    template<typename>
    friend
    bool
    is_of_type(Object const&);

    template<typename T>
    friend
    T&
    object_cast(Object&);

    template<typename T>
    friend
    T const&
    object_cast(Object const&);

    friend
    Object
    clone(Object&);

    friend
    void
    accept(Object&, Visitor&);

    friend
    void
    accept(Object const&, Visitor&);

    /// Assignment.
    ///
    Object&
    operator=(Object const&);

    /// Assignment.
    ///
    Object&
    operator=(Object&&);

    /// Comparison.
    ///
    bool
    operator==(Object const&) const;

    /// Comparison.
    ///
    bool
    operator!=(Object const&) const;

  private:
    friend File;
    friend Writer;

    /// Constructor.
    ///
    explicit
    Object(shared_ptr<Object_model::Abstract>);

    /// Get the container of the object.
    ///
    Object_model::Container_base&
    container();

    /// Get the container of the object.
    ///
    Object_model::Container_base const&
    container() const;

  private:
    /// Holds the data of the object, either an instance of
    /// Object_model::Reference for references, or an instance of
    /// Object_model::Container for direct objects.
    ///
    shared_ptr<Object_model::Abstract> _data;

  };

  /// Check object type.
  ///
  template<typename T>
  bool
  is_of_type(Object const& object)
  {
    return typeid(T) == object.container().type();
  }

  /// This function provides access to the value of an object.
  ///
  template<typename T>
  T&
  object_cast(Object& object)
  {
    return object.container().get<T>();
  }

  /// This function provides access to the value of an object.
  ///
  template<typename T>
  T const&
  object_cast(Object const& object)
  {
    return object.container().get<T>();
  }

  /// Clone an object.
  ///
  Object
  clone(Object&);

  /// Accept visitor on object.
  ///
  void
  accept(Object&, Visitor&);

  /// Accept visitor on object.
  ///
  void
  accept(Object const&, Visitor&);

} // namespace Art::Paperback::Carousel

#endif
