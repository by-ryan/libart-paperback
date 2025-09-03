#include <art/paperback/internals/page-tree.hxx>

#include <art/paperback/internals/document-catalog.hxx>

#include <art/paperback/carousel/array.hxx>
#include <art/paperback/carousel/dictionary.hxx>
#include <art/paperback/carousel/file.hxx>
#include <art/paperback/carousel/integer.hxx>
#include <art/paperback/carousel/name.hxx>

#include <art/paperback/document.hxx>
#include <art/paperback/except.hxx>
#include <art/paperback/page.hxx>

namespace Art::Paperback::Internals
{

  struct Page_tree::Internal
  {
    Internal(Create_new const&,
               Document_catalog& document_catalog)
      : document_catalog{document_catalog},
        object{
          document_catalog.document().file().create_object<Carousel::Dictionary>(
            map<Carousel::Name, Carousel::Object>{
              {Carousel::Name{"Type"}, Carousel::Name{"Pages"}},
              {Carousel::Name{"Kids"}, Carousel::Array{}},
              {Carousel::Name{"Count"}, Carousel::Integer{0}}
            }
          )
        },
        data{object_cast<Carousel::Dictionary>(object)},
        kids{object_cast<Carousel::Array>(data.at("Kids"))},
        count{object_cast<Carousel::Integer>(data.at("Count"))}
    {}

    Document_catalog& document_catalog;
    Carousel::Object       object;
    Carousel::Dictionary&  data;
    Carousel::Array&       kids;
    Carousel::Integer&     count;

    // This is a map of all currently loaded pages, rather than all
    // pages in the document. It is populated on page creation or when
    // requesting a page not already loaded.
    //
    map<size_t, Page> pages;

  };

  /// \class Page_tree
  ///
  /// \warning
  /// The current Page_tree implementation maintains a flat array of
  /// all pages in the tree. This is far from optimal. We should
  /// probably implement a self-balancing tree in the future.
  ///

  /// This constructor creates a new page tree.
  ///
  /// \param document_catalog The parent document catalog.
  ///
  Page_tree::
  Page_tree(Create_new const&, Document_catalog& document_catalog)
    : internal{new Internal{create_new, document_catalog}}
  {}

  Page_tree::
  ~Page_tree() noexcept
  {}

  /// \return Returns a reference to the parent document catalog.
  ///
  Document_catalog&
  Page_tree::
  document_catalog() const
  {
    return internal->document_catalog;
  }

  Carousel::Object
  Page_tree::
  object() const
  {
    return internal->object;
  }

  /// \param properties The properties of the new page.
  ///
  Page&
  Page_tree::
  create_page(Page::Properties const& properties)
  {
    auto index = internal->kids.size();
    auto [it, unused] = internal->pages.try_emplace(
      index,
      Page::create_new,
      *this,
      properties
    );

    internal->kids.push_back(it->second.object());
    internal->count = internal->kids.size();

    return it->second;
  }

  Page&
  Page_tree::
  get_page(size_t)
  {
    raise<Internal_error>{} << "function not implemented";
  }

  Page const&
  Page_tree::
  get_page(size_t) const
  {
    raise<Internal_error>{} << "function not implemented";
  }

  void
  Page_tree::
  erase_page(size_t)
  {
    raise<Internal_error>{} << "function not implemented";
  }

  /// \param page_tree The page tree.
  /// \return Returns a reference to the parent document.
  ///
  Document&
  document(Page_tree& page_tree)
  {
    return page_tree.document_catalog().document();
  }

  /// \param page_tree The page tree.
  /// \return Returns a reference to the parent document.
  ///
  Document const&
  document(Page_tree const& page_tree)
  {
    return page_tree.document_catalog().document();
  }

} // namespace Art::Paperback::Internals
