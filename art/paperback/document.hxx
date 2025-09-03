#ifndef art__paperback__document_hxx_
#define art__paperback__document_hxx_

#include <art/paperback/types.hxx>
#include <art/paperback/forward.hxx>
#include <art/paperback/page.hxx>

namespace Art::Paperback
{

  class Document
  {
  public:
    struct Create_new {};

    /// Tag used to indicate the creation of a new document.
    ///
    static constexpr Create_new const create_new{};

    /// Constructor.
    ///
    Document(Create_new const&, std::iostream&, int, int);

    /// Destructor.
    ///
    ~Document();

    /// Get document major version.
    ///
    int
    major() const;

    /// Get document minor version.
    ///
    int
    minor() const;

    /// Check that the document meets minimum version requirements.
    ///
    void
    check_minimum_version(int, int) const;

    /// Get document information.
    ///
    Document_information&
    information();

    /// Create new page.
    ///
    Page&
    create_page(Page::Properties const&);

    /// Access the underlying COS file.
    ///
    Carousel::File&
    file();

    /// Flush current document state to output stream.
    ///
    void
    flush();

  private:
    Document(Document const&) = delete;
    Document(Document&&) = delete;
    Document& operator=(Document const&) = delete;
    Document& operator=(Document&&) = delete;

  private:
    struct Internal;
    std::unique_ptr<Internal> internal;

  };

} // namespace Art::Paperback

#endif
