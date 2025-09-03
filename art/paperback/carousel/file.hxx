#ifndef art__paperback__carousel__file_hxx_
#define art__paperback__carousel__file_hxx_

#include <art/paperback/types.hxx>
#include <art/paperback/forward.hxx>

#include <art/paperback/carousel/array.hxx>
#include <art/paperback/carousel/cross-reference.hxx>
#include <art/paperback/carousel/name.hxx>
#include <art/paperback/carousel/object.hxx>
#include <art/paperback/carousel/writer.hxx>

namespace Art::Paperback::Carousel
{

  /// Represents a COS-format file.
  ///
  class File
  {
  public:
    struct Create_new {};

    /// Dispatch-tag for creating a new COS-file.
    ///
    static constexpr Create_new create_new{};

    /// Constructor.
    ///
    File(Create_new const&, iostream&, int, int, string);

    /// Destructor.
    ///
    ~File() noexcept;

    /// Access the COS-file catalog dictionary object.
    ///
    Dictionary&
    catalog();

    /// Access the COS-file info dictionary object.
    ///
    Dictionary&
    info();

    /// Create a new object.
    ///
    template<typename T, typename... Args>
    Object
    create_object(Args&&... args)
    {
      auto identity = allocate();

      auto container = make_shared<Object_model::Container<T>>(
        std::forward<Args>(args)...
      );

      insert(identity, std::move(container));

      return Object{
        make_shared<Object_model::Reference>(*this, identity)
      };
    }

    /// Commit the current COS-file revision to the output stream.
    ///
    void
    commit_revision();

  private:
    friend Object_model::Reference;

    /// Get container.
    ///
    Object_model::Container_base&
    get_container(Identity const&);

    /// Get container.
    ///
    Object_model::Container_base const&
    get_container(Identity const&) const;

  private:
    File(File const&) = delete;
    File(File&&) = delete;
    File& operator=(File const&) = delete;
    File& operator=(File&&) = delete;

    /// Allocates a new index.
    ///
    Identity
    allocate();

    /// Inserts an object into the cross-reference table.
    ///
    void
    insert(Identity const&, shared_ptr<Object_model::Container_base>);

    struct Revision;

    struct Internal;
    unique_ptr<Internal> internal;

  };

} // namespace Art::Paperback::Carousel

#endif
