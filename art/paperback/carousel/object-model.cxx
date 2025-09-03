#include <art/paperback/carousel/object-model.hxx>
#include <art/paperback/carousel/file.hxx>

#include <art/paperback/except.hxx>


namespace Art::Paperback::Carousel::Object_model
{

  /// \class Abstract
  ///

  Abstract::
  ~Abstract() noexcept
  {}

  Abstract::
  Abstract()
  {}

  /// \class Container_base
  ///

  Container_base::
  ~Container_base() noexcept
  {}

  Container_base::
  Container_base()
  {}

  /// \class Reference
  ///
  ///

  /// \param file The parent file.
  /// \param identity The identity of the reference.
  ///
  Reference::
  Reference(File& file, Identity identity)
    : _file{file},
      _identity{identity}
  {}

  File&
  Reference::
  file() const
  {
    return _file;
  }

  Identity const&
  Reference::
  identity() const
  {
    return _identity;
  }

  std::type_info const&
  Reference::
  type() const
  {
    return typeid(Reference);
  }

  Container_base&
  Reference::
  container()
  {
    return file().get_container(identity());
  }

  Container_base const&
  Reference::
  container() const
  {
    return file().get_container(identity());
  }

  Owner*
  Reference::
  owner()
  {
    return nullptr;
  }

  Owner const*
  Reference::
  owner() const
  {
    return nullptr;
  }

  void
  Reference::
  attach(Owner& owner)
  {
    // No-op.
    //
  }

  shared_ptr<Abstract>
  Reference::
  clone() const
  {
    return make_shared<Reference>(file(), identity());
  }

  /// \class Value_base
  ///

  /// \param owner Reference to the owner.
  ///
  void
  Value_base::
  attach(Owner& owner)
  {
    if (_owner) {
      raise<Internal_error>{} << "object already attached";
    }

    _owner = &owner;
    attach_children(owner);
  }

  /// \return Returns a pointer to the owner, if attached.
  ///
  Owner*
  Value_base::
  owner()
  {
    return _owner;
  }

  /// \return Returns a pointer to the owner, if attached.
  ///
  Owner const*
  Value_base::
  owner() const
  {
    return _owner;
  }

  Value_base::
  Value_base()
  {}

  Value_base::
  ~Value_base()
  {}

  /// \param owner The owner of the children.
  ///
  void
  Value_base::
  attach_children(Owner& owner)
  {}

  /// \class Owner
  ///

  /// \param container The object container.
  ///
  Owner::
  Owner(shared_ptr<Container_base> container)
    : _container{container}
  {
    if (!_container) {
      raise<Internal_error>{} << "container must not be null";
    }

    _container->attach(*this);
  }

  Owner::
  ~Owner() noexcept
  {}

  Container_base&
  Owner::
  container()
  {
    return *_container;
  }

  Container_base const&
  Owner::
  container() const
  {
    return *_container;
  }

  bool
  Owner::
  modified() const
  {
    return _modified;
  }

  void
  Owner::
  mark_as_modified()
  {
    _modified = true;
  }

  void
  Owner::
  reset()
  {
    _modified = false;
  }

} // namespace Art::Paperback::Carousel::Object_model
