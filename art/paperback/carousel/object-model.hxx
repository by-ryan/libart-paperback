#ifndef art__paperback__carousel__object_model_hxx_
#define art__paperback__carousel__object_model_hxx_

#include <art/paperback/types.hxx>
#include <art/paperback/forward.hxx>
#include <art/paperback/visitor.hxx>

#include <typeinfo>

namespace Art::Paperback::Carousel::Object_model
{

  /// Abstract base class for object tree.
  ///
  class Abstract
  {
  public:
    /// Destructor.
    ///
    virtual
    ~Abstract() noexcept;

    /// Get contained type info.
    ///
    virtual
    std::type_info const&
    type() const = 0;

    /// Get container.
    ///
    virtual
    Container_base&
    container() = 0;

    /// Get container.
    ///
    virtual
    Container_base const&
    container() const = 0;

    /// Access node owner.
    ///
    virtual
    Owner*
    owner() = 0;

    /// Access node owner.
    ///
    virtual
    Owner const*
    owner() const = 0;

    /// Attach node to owner.
    ///
    virtual
    void
    attach(Owner&) = 0;

    /// Clone.
    ///
    virtual
    shared_ptr<Abstract>
    clone() const = 0;

  protected:
    /// Constructor.
    ///
    Abstract();

  private:
    Abstract(Abstract const&) = delete;
    Abstract(Abstract&&) = delete;
    Abstract& operator=(Abstract const&) = delete;
    Abstract& operator=(Abstract&&) = delete;

  };

  /// Base class for containers.
  ///
  class Container_base
    : public Abstract
  {
  public:
    /// Destructor.
    ///
    ~Container_base() noexcept override;

    /// Get.
    ///
    template<typename T>
    T&
    get()
    {
      return dynamic_cast<Container<T>&>(*this).get();
    }

    /// Get.
    ///
    template<typename T>
    T const&
    get() const
    {
      return dynamic_cast<Container<T> const&>(*this).get();
    }

    virtual
    void
    assign(Container_base const&) = 0;

    virtual
    bool
    compare(Container_base const&) const = 0;

    virtual
    void
    do_accept(Visitor&) = 0;

    virtual
    void
    do_accept(Visitor&) const = 0;

  protected:
    /// Constructor.
    ///
    Container_base();

  private:
    Container_base(Container_base const&) = delete;
    Container_base(Container_base&&) = delete;
    Container_base& operator=(Container_base const&) = delete;
    Container_base& operator=(Container_base&&) = delete;

  };

  template<typename T>
  class Container
    : public Container_base,
      public std::enable_shared_from_this<Container<T>>
  {
  public:
    template<typename... Args>
    explicit
    Container(Args&&... args)
      : _value{std::forward<Args>(args)...}
    {}

    Container_base&
    container() override
    {
      return *this;
    }

    Container_base const&
    container() const override
    {
      return *this;
    }

    std::type_info const&
    type() const override
    {
      return typeid(T);
    }

    T&
    get()
    {
      return _value;
    }

    T const&
    get() const
    {
      return _value;
    }

    void
    assign(Container_base const& other) override
    {
      _value = other.get<T>();
    }

    bool
    compare(Container_base const& other) const override
    {
      return _value == other.get<T>();
    }

    void
    do_accept(Visitor& v) override
    {
      accept(_value, v);
    }

    void
    do_accept(Visitor& v) const override
    {
      accept(_value, v);
    }

    Owner*
    owner() override
    {
      return _value.owner();
    }

    Owner const*
    owner() const override
    {
      return _value.owner();
    }

    void
    attach(Owner& owner) override
    {
      return _value.attach(owner);
    }

    shared_ptr<Abstract>
    clone() const override
    {
      return make_shared<Container<T>>(_value);
    }

  private:
    Container(Container<T> const&) = delete;
    Container(Container<T>&&) = delete;
    Container<T>& operator=(Container<T> const&) = delete;
    Container<T>& operator=(Container<T>&&) = delete;

  private:
    T _value;

  };

  /// Represents a reference to an indirect object.
  ///
  class Reference
    : public Abstract,
      public std::enable_shared_from_this<Reference>
  {
  public:
    /// Constructor.
    ///
    Reference(File&, Identity);

    /// Access parent file.
    ///
    File&
    file() const;

    /// Access the identity of this reference.
    ///
    Identity const&
    identity() const;

    std::type_info const&
    type() const override;

    Container_base&
    container() override;

    Container_base const&
    container() const override;

    Owner*
    owner() override;

    Owner const*
    owner() const override;

    void
    attach(Owner& owner) override;

    /// Clone.
    ///
    shared_ptr<Abstract>
    clone() const override;

  private:
    Reference(Reference const&) = delete;
    Reference(Reference&&) = delete;
    Reference& operator=(Reference const&) = delete;
    Reference& operator=(Reference&&) = delete;

  private:
    File& _file;
    Identity _identity;

  };

  /// Base class for value types.
  ///
  class Value_base
  {
  public:
    /// Attach value to owner.
    ///
    void
    attach(Owner&);

    /// Access owner, if any.
    ///
    Owner*
    owner();

    /// Access owner, if any.
    ///
    Owner const*
    owner() const;

  protected:
    /// Constructor.
    ///
    Value_base();

    /// Destructor.
    ///
    ~Value_base();

    /// Attach any children.
    ///
    virtual
    void
    attach_children(Owner&);

  private:
    Value_base(Value_base const&) = delete;
    Value_base(Value_base&&) = delete;
    Value_base& operator=(Value_base const&) = delete;
    Value_base& operator=(Value_base&&) = delete;

  private:
    Owner* _owner{};

  };

  /// Owner of an indirect object.
  ///
  class Owner
  {
  public:
    /// Constructor.
    ///
    explicit
    Owner(shared_ptr<Container_base>);

    /// Destructor.
    ///
    ~Owner() noexcept;

    /// Access container.
    ///
    Container_base&
    container();

    /// Access container.
    ///
    Container_base const&
    container() const;

    /// Check if modified.
    ///
    bool
    modified() const;

    /// Mark as modified.
    ///
    void
    mark_as_modified();

    /// Reset modification mark.
    ///
    void
    reset();

  private:
    Owner(Owner const&) = delete;
    Owner(Owner&&) = delete;
    Owner& operator=(Owner const&) = delete;
    Owner& operator=(Owner&&) = delete;

  private:
    shared_ptr<Container_base> _container;

    /// Change tracking.
    ///
    bool _modified{true};

  };

} // namespace Art::Paperback::Carousel::Object_model

#endif
