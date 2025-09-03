#ifndef art__paperback__internals__page_tree_hxx_
#define art__paperback__internals__page_tree_hxx_

#include <art/paperback/types.hxx>
#include <art/paperback/forward.hxx>
#include <art/paperback/page.hxx>

#include <art/paperback/carousel/object.hxx>

namespace Art::Paperback::Internals
{

  /// Represents a PDF page tree.
  ///
  class Page_tree
  {
  public:
    struct Create_new {};
    static constexpr Create_new const create_new{};

    /// Constructor.
    ///
    Page_tree(Create_new const&, Document_catalog&);

    /// Destructor.
    ///
    ~Page_tree() noexcept;

    /// Access the parent document catalog.
    ///
    Document_catalog&
    document_catalog() const;

    /// Access the associated data object.
    ///
    Carousel::Object
    object() const;

    /// Create a new page and add it to the page tree.
    ///
    Page&
    create_page(Page::Properties const&);

    /// Get page.
    ///
    Page&
    get_page(size_t);

    /// Get page.
    ///
    Page const&
    get_page(size_t) const;

    /// Erase page.
    ///
    void
    erase_page(size_t);

  private:
    Page_tree(Page_tree const&) = delete;
    Page_tree(Page_tree&&) = delete;
    Page_tree& operator=(Page_tree const&) = delete;
    Page_tree& operator=(Page_tree&&) = delete;

  private:
    struct Internal;
    unique_ptr<Internal> internal;

  };

  /// Get the document associated with a page tree.
  ///
  Document&
  document(Page_tree&);

  /// Get the document associated with a page tree.
  ///
  Document const&
  document(Page_tree const&);

} // namespace Art::Paperback::Internals

#endif
