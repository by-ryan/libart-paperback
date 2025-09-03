#include <art/paperback/page.hxx>
#include <art/paperback/primitives.hxx>
#include <art/paperback/document.hxx>

#include <art/paperback/carousel/array.hxx>
#include <art/paperback/carousel/dictionary.hxx>
#include <art/paperback/carousel/file.hxx>
#include <art/paperback/carousel/name.hxx>
#include <art/paperback/carousel/object.hxx>
#include <art/paperback/carousel/stream.hxx>

#include <art/paperback/internals/document-catalog.hxx>
#include <art/paperback/internals/page-tree.hxx>
#include <art/paperback/internals/resource-collection.hxx>

namespace Art::Paperback
{

  struct Page::Internal
  {
    Internal(Create_new const&,
               Internals::Page_tree& page_tree)
      : page_tree{page_tree},
        object{document(page_tree).file().create_object<Carousel::Dictionary>()},
        data{object_cast<Carousel::Dictionary>(object)},
        contents{document(page_tree).file().create_object<Carousel::Stream>()}
    {}

    /// Parent page tree.
    ///
    Internals::Page_tree& page_tree;

    /// COS object for this page.
    ///
    Carousel::Object object;

    /// Data dictionary for this page.
    ///
    Carousel::Dictionary& data;

    /// The page's contents stream object.
    ///
    Carousel::Object contents;

    /// On-demand allocated resource collection.
    ///
    optional<Internals::Resource_collection> resources;

  };

  /// This constructor creates a new page.
  ///
  /// \param page_tree A reference to the parent page tree.
  /// \param properties The properties of the new page.
  ///
  Page::
  Page(Create_new const&,
         Internals::Page_tree& page_tree,
         Properties const& properties)
    : internal{new Internal{create_new, page_tree}}
  {
    internal->data.insert("Type", Carousel::Name{"Page"});
    internal->data.insert("MediaBox", properties.media_box.to_array());
    internal->data.insert("Parent", page_tree.object());
    internal->data.insert("Contents", internal->contents);

    internal->resources.emplace(
      Internals::Resource_collection::create_new, *this
    );

    internal->data.insert("Resources", internal->resources->object());
  }

  Page::
  ~Page() noexcept
  {}

  Internals::Page_tree&
  Page::
  page_tree() const
  {
    return internal->page_tree;
  }

  Carousel::Object
  Page::
  object() const
  {
    return internal->object;
  }

  Carousel::Stream&
  Page::
  contents()
  {
    return object_cast<Carousel::Stream>(internal->contents);

#if 0
    if (!internal->contents) {
      auto stream = document(*this).file().create_object<Carousel::Stream>();
      internal->data.insert("Contents", stream);
      internal->contents.emplace(stream);
    }

    return *internal->contents;
#endif
  }

  Internals::Resource_collection&
  Page::
  resources()
  {
    if (!internal->resources) {
    }

    return *internal->resources;
  }

  Document&
  document(Page& page)
  {
    return document(page.page_tree());
  }

  Document const&
  document(Page const& page)
  {
    return document(page.page_tree());
  }

} // namespace Art::Paperback
