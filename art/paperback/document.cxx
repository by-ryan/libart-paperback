#include <art/paperback/document.hxx>
#include <art/paperback/except.hxx>

#include <art/paperback/document-information.hxx>

#include <art/paperback/internals/document-catalog.hxx>

#include <art/paperback/carousel/file.hxx>

#include <sstream>

namespace Art::Paperback
{

  /// Helper to create a PDF-file header.
  ///
  static
  string
  make_header(int major, int minor)
  {
    std::stringstream str;
    str << "PDF-" << major << '.' << minor;
    return str.str();
  }

  struct Document::Internal
  {
    Internal(iostream& ios, int major, int minor)
      : file{
          Carousel::File::create_new,
          ios,
          major,
          minor,
          make_header(major, minor),
        },
        major{major},
        minor{minor}
    {}

    Carousel::File file;
    int major{};
    int minor{};

    optional<Internals::Document_catalog> catalog;

    optional<Document_information> info;

  };

  Document::
  Document(Create_new const&, iostream& ios, int major, int minor)
    : internal{new Internal{ios, major, minor}}
  {
    if (major < 1 || 1 < major) {
      throw invalid_argument{"unsupported major version"};
    }

    if (minor < 1 || 4 < minor) {
      throw invalid_argument{"unsupported minor version"};
    }
  }

  Document::
  ~Document()
  {
    file().commit_revision();
  }

  int
  Document::
  major() const
  {
    return internal->major;
  }

  int
  Document::
  minor() const
  {
    return internal->minor;
  }

  /// \param major The minimum required major version.
  /// \param minor The minimum required minor version.
  /// \throw Upgrade_required Thrown if the document does not meet
  ///                           the specified version requirements.
  void
  Document::
  check_minimum_version(int major, int minor) const
  {
    if (major > this->major()) {
      raise<Upgrade_required>{} << "document version upgrade required";
    }

    if (minor > this->minor()) {
      raise<Upgrade_required>{} << "document version upgrade required";
    }
  }

  Document_information&
  Document::
  information()
  {
    if (!internal->info) {
      internal->info.emplace(Document_information::create_new, *this);
    }

    return *internal->info;
  }

  /// \param properties The properties of the new page.
  ///
  Page&
  Document::
  create_page(Page::Properties const& properties)
  {
    if (!internal->catalog) {
      internal->catalog.emplace(
        Internals::Document_catalog::create_new,
        *this
      );
    }

    return internal->catalog->pages().create_page(properties);
  }

  Carousel::File&
  Document::
  file()
  {
    return internal->file;
  }

  void
  Document::
  flush()
  {
    internal->file.commit_revision();
  }

} // namespace Art::Paperback
