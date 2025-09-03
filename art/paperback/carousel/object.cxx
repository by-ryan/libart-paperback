#include <art/paperback/carousel/object.hxx>

#include <art/paperback/except.hxx>

#include <art/paperback/carousel/file.hxx>
#include <art/paperback/carousel/object-model.hxx>

#include <art/paperback/carousel/array.hxx>
#include <art/paperback/carousel/boolean.hxx>
#include <art/paperback/carousel/dictionary.hxx>
#include <art/paperback/carousel/integer.hxx>
#include <art/paperback/carousel/name.hxx>
#include <art/paperback/carousel/real.hxx>
#include <art/paperback/carousel/stream.hxx>
#include <art/paperback/carousel/text.hxx>
#include <art/paperback/carousel/undefined.hxx>

namespace Art::Paperback::Carousel
{

  /// \class Object
  ///
  /// The Object class represents a COS-file object. An object can be
  /// either a direct object or an indirect object. The eight supported
  /// object types are:
  ///
  /// - Boolean values
  /// - Integer and real numbers
  /// - Strings
  /// - Names
  /// - Arrays
  /// - Dictionaries
  /// - Streams
  /// - Null (undefined)
  ///
  /// See Section 3.2, "Objects" in the PDF-1.4 specification for
  /// further information.
  ///
  /// Instances of Object maintain a pointer to the underlying data.
  /// Copying an object creates a new reference to the same underlying
  /// data. This is not to be confused with indirect COS objects. See
  /// the example below for clarification. Also note, that an object
  /// can only have a maximum of one owner, so adding an object to
  /// say two different arrays at the same time will result in an
  /// exception being thrown.
  ///
  /// \todo Describe assigning to already created objects.
  ///
  /// ```cxx
  /// using namespace Art::Paperback::Carousel;
  ///
  /// // Create a direct object of array type.
  /// //
  /// Object object0{Array{}};
  ///
  /// // Create a new direct object pointing to the same data as object0.
  /// //
  /// Object object1{object0};
  ///
  /// // Changes made in object0 will be reflected in object1, and vice versa.
  /// //
  ///
  /// // If an identitcal copy is desired, the clone function can be used:
  /// //
  /// Object object2{clone(object0)};
  ///
  /// // Changes made to object2 will not be reflected in object0 nor object1.
  /// //
  ///
  /// // Indirect objects work differently. Cloning an indirect object
  /// // will clone the reference to the indirect object, not the data
  /// // of the object.
  /// //
  ///
  /// File file;
  ///
  /// // Create an indirect object of array type.
  /// //
  /// Object object3{file.create_object<Array>()};
  ///
  /// Object object4{object3};
  /// Object object5{clone(object3)};
  ///
  /// // At this point, both object4 and object5 point to the indirect
  /// // object first allocated in object3. This includes object5 since
  /// // it's a clone of a reference.
  /// //
  /// ```
  ///
  /// Access to the data of an object is provided by the \ref object_cast
  /// function, see the example below:
  ///
  /// ```cxx
  /// using namespace Art::Paperback::Carousel;
  ///
  /// Object my_array{Array{}};
  ///
  /// object_cast<Array>(my_array).push_back(Integer{0});
  /// ```
  ///

  /// This constructor creates a null (undefined) object.
  ///
  Object::
  Object(Undefined const& undefined)
    : _data{make_shared<Object_model::Container<Undefined>>(undefined)}
  {}

  /// This constructor creates an array object.
  ///
  /// \param array The array.
  ///
  Object::
  Object(Array array)
    : _data{make_shared<Object_model::Container<Array>>(std::move(array))}
  {}

  /// This constructor creates a boolean object.
  ///
  /// \param boolean The boolean value.
  ///
  Object::
  Object(Boolean boolean)
    : _data{make_shared<Object_model::Container<Boolean>>(std::move(boolean))}
  {}

  /// This constructor creates a dictionary object.
  ///
  /// \param dictionary The dictionary.
  ///
  Object::
  Object(Dictionary dictionary)
    : _data{make_shared<Object_model::Container<Dictionary>>(std::move(dictionary))}
  {}

  /// This constructor creates an integer object.
  ///
  /// \param integer The integer value.
  ///
  Object::
  Object(Integer integer)
    : _data{make_shared<Object_model::Container<Integer>>(std::move(integer))}
  {}

  /// This constructor creates a name object.
  ///
  /// \param name The name.
  ///
  Object::
  Object(Name name)
    : _data{make_shared<Object_model::Container<Name>>(std::move(name))}
  {}

  /// This constructor creates a real object.
  ///
  /// \param real The real value.
  ///
  Object::
  Object(Real real)
    : _data{make_shared<Object_model::Container<Real>>(std::move(real))}
  {}

  /// This constructor creates a text (string) object.
  ///
  /// \param text The text (string) value.
  ///
  Object::
  Object(Text text)
    : _data{make_shared<Object_model::Container<Text>>(std::move(text))}
  {}

  /// \param other The object to copy from.
  ///
  Object::
  Object(Object const& other)
    : _data{other._data}
  {
    if (!_data) {
      raise<Internal_error>{} << "invalid object data";
    }
  }

  /// This constructor makes a copy of \a other rather than moving
  /// from it. This avoids the problem of having invalid-state
  /// objects.
  ///
  /// \param other The object to move from.
  ///
  Object::
  Object(Object&& other)
    : _data{other._data}
  {
    if (!_data) {
      raise<Internal_error>{} << "invalid object data";
    }
  }

  /// \param owner The owner to tie this object with.
  ///
  void
  Object::
  attach(Object_model::Owner& owner)
  {
    _data->attach(owner);
  }

  /// \return Returns true if this object is an indirect reference.
  ///
  bool
  Object::
  is_reference() const
  {
    return typeid(Object_model::Reference) == _data->type();
  }

  /// \throw Internal_error Thrown if the object is not an indirect object.
  /// \return Returns the identity of the object, if it is an indirect
  ///         object.
  ///
  Identity const&
  Object::
  identity() const
  {
    if (is_reference()) {
      return dynamic_cast<Object_model::Reference const&>(*_data).identity();
    }

    raise<Internal_error>{} << "object is not a reference";
  }

  /// \param other The object to assign from.
  ///
  Object&
  Object::
  operator=(Object const& other)
  {
    if (this != &other) {
      container().assign(other.container());
    }

    return *this;
  }

  /// \param other The object to assign from.
  ///
  Object&
  Object::
  operator=(Object&& other)
  {
    if (this != &other) {
      container().assign(other.container());
    }

    return *this;
  }

  /// \param other The object to compare with.
  ///
  bool
  Object::
  operator==(Object const& other) const
  {
    return container().compare(other.container());
  }

  /// \param other The object to compare with.
  ///
  bool
  Object::
  operator!=(Object const& other) const
  {
    return !(*this == other);
  }

  /// This is an internal constructor to create an indirect object.
  ///
  Object::
  Object(shared_ptr<Object_model::Abstract> data)
    : _data{std::move(data)}
  {
    if (!_data) {
      raise<Internal_error>{} << "data must not be null";
    }
  }

  Object_model::Container_base&
  Object::
  container()
  {
    return _data->container();
  }

  Object_model::Container_base const&
  Object::
  container() const
  {
    return _data->container();
  }

  /// \param object The object to clone.
  ///
  Object
  clone(Object& object)
  {
    return Object{object._data->clone()};
  }

  /// \param visitee The visitee.
  /// \param v The visitor.
  ///
  void
  accept(Object& visitee, Visitor& v)
  {
    visitee.container().do_accept(v);
  }

  /// \param visitee The visitee.
  /// \param v The visitor.
  ///
  void
  accept(Object const& visitee, Visitor& v)
  {
    visitee.container().do_accept(v);
  }

} // namespace Art::Paperback::Carousel
