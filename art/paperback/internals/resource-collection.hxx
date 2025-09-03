#ifndef art__paperback__internals__resource_collection_hxx_
#define art__paperback__internals__resource_collection_hxx_

#include <art/paperback/types.hxx>
#include <art/paperback/forward.hxx>

#include <art/paperback/internals/font-collection.hxx>

#include <art/paperback/carousel/object.hxx>

namespace Art::Paperback::Internals
{

  /// Represents a PDF resource collection.
  ///
  class Resource_collection
  {
  public:
    struct Create_new {};
    static constexpr Create_new const create_new{};

    /// Constructor.
    ///
    Resource_collection(Create_new, Page&);

    /// Destructor.
    ///
    ~Resource_collection() noexcept;

    /// Get the parent page.
    ///
    Page&
    page();

    /// Get the parent page.
    ///
    Page const&
    page() const;

    /// Get the object for this resource collection.
    ///
    Carousel::Object
    object();

    /// Get the font collection.
    ///
    Font_collection&
    fonts();

  private:
    Resource_collection(Resource_collection const&) = delete;
    Resource_collection(Resource_collection&&) = delete;
    Resource_collection& operator=(Resource_collection const&) = delete;
    Resource_collection& operator=(Resource_collection&&) = delete;

  private:
    struct Internal;
    unique_ptr<Internal> internal;

  };

  /// Get the document associated with a resource collection.
  ///
  Document&
  document(Resource_collection&);

  /// Get the document associated with a resource collection.
  ///
  Document const&
  document(Resource_collection const&);

} // namespace cooper

#endif
