#include <art/paperback/internals/resource-collection.hxx>

#include <art/paperback/carousel/dictionary.hxx>
#include <art/paperback/carousel/file.hxx>
#include <art/paperback/carousel/name.hxx>
#include <art/paperback/carousel/object.hxx>

#include <art/paperback/document.hxx>
#include <art/paperback/page.hxx>

namespace Art::Paperback::Internals
{

  struct Resource_collection::Internal
  {
    Internal(Create_new const&, Page& page)
      : page{page},
        object{Carousel::Dictionary{}},
        data{object_cast<Carousel::Dictionary>(object)}
    {}

    Page& page;

    /// COS object for this resource collection.
    ///
    Carousel::Object object;

    /// Data dictionary for this resource collection.
    ///
    Carousel::Dictionary& data;

    /// Optional font collection, allocated on first use.
    ///
    optional<Font_collection> fonts;

  };

  /// This contructor creates a new resource collection.
  ///
  /// \param page The parent page of this resource collection.
  /// \param object The object for this resource collection.
  ///
  Resource_collection::
  Resource_collection(Create_new, Page& page)
    : internal{new Internal{create_new, page}}
  {
    Carousel::Array procset;
    procset.push_back(Carousel::Name{"PDF"});
    procset.push_back(Carousel::Name{"Text"});
    procset.push_back(Carousel::Name{"ImageB"});
    procset.push_back(Carousel::Name{"ImageC"});
    procset.push_back(Carousel::Name{"ImageI"});

    internal->data.insert("ProcSet", procset);
  }

  Resource_collection::
  ~Resource_collection() noexcept
  {}

  Page&
  Resource_collection::
  page()
  {
    return internal->page;
  }

  Page const&
  Resource_collection::
  page() const
  {
    return internal->page;
  }

  Carousel::Object
  Resource_collection::
  object()
  {
    return internal->object;
  }

  Font_collection&
  Resource_collection::
  fonts()
  {
    if (!internal->fonts) {
      internal->fonts.emplace(Font_collection::create_new, *this);
      internal->data.insert("Font", internal->fonts->object());
    }

    return *internal->fonts;
  }

  /// \return Returns a reference to the document.
  ///
  Document&
  document(Resource_collection& resource_collection)
  {
    return document(resource_collection.page());
  }

  /// \return Returns a reference to the document.
  ///
  Document const&
  document(Resource_collection const& resource_collection)
  {
    return document(resource_collection.page());
  }

} // namespace cooper
