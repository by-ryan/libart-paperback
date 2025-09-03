#ifndef art__paperback__internals__document_catalog_hxx_
#define art__paperback__internals__document_catalog_hxx_

#include <art/paperback/types.hxx>
#include <art/paperback/forward.hxx>

#include <art/paperback/internals/page-tree.hxx>

namespace Art::Paperback::Internals
{

  class Document_catalog
  {
  public:
    struct Create_new {};
    static constexpr Create_new const create_new{};

    /// Constructor.
    ///
    Document_catalog(Create_new const&, Document&);

    /// Destructor.
    ///
    ~Document_catalog() noexcept;

    /// Access the parent document.
    ///
    Document&
    document();

    /// Access the parent document.
    ///
    Document const&
    document() const;

    /// Access the page tree.
    ///
    Page_tree&
    pages();

  private:
    Document_catalog(Document_catalog const&) = delete;
    Document_catalog(Document_catalog&&) = delete;
    Document_catalog& operator=(Document_catalog const&) = delete;
    Document_catalog& operator=(Document_catalog&&) = delete;

    struct Internal;
    unique_ptr<Internal> internal;

  };

} // namespace Art::Paperback::Internals

#endif
