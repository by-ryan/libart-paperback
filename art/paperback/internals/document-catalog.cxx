#include <art/paperback/internals/document-catalog.hxx>

#include <art/paperback/document.hxx>

#include <art/paperback/carousel/dictionary.hxx>
#include <art/paperback/carousel/file.hxx>

namespace Art::Paperback::Internals
{

  struct Document_catalog::Internal
  {
    Internal(Document& document)
      : document{document}
    {}

    Document& document;

    /// The page tree of the document. Allocated on first use.
    ///
    optional<Page_tree> pages;

  };

  Document_catalog::
  Document_catalog(Create_new const&, Document& document)
    : internal{new Internal{document}}
  {
    document.file().catalog() = Carousel::Dictionary{};
    document.file().catalog().insert("Type", Carousel::Name{"Catalog"});
  }

  Document_catalog::
  ~Document_catalog() noexcept
  {}

  Document&
  Document_catalog::
  document()
  {
    return internal->document;
  }

  Document const&
  Document_catalog::
  document() const
  {
    return internal->document;
  }

  Page_tree&
  Document_catalog::
  pages()
  {
    if (!internal->pages) {
      internal->pages.emplace(Page_tree::create_new, *this);
      document().file().catalog().insert("Pages", internal->pages->object());
    }

    return *internal->pages;
  }

} // namespace Art::Paperback::Internals
