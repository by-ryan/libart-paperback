#include <art/paperback/carousel/file.hxx>

#include <art/paperback/carousel/dictionary.hxx>
#include <art/paperback/carousel/integer.hxx>

namespace Art::Paperback::Carousel
{

  /// Represents a COS-file revision.
  ///
  struct File::Revision
  {
    /// Construct a new revision.
    ///
    Revision(int64_t offset, cross_Reference xref)
      : offset{offset},
        xref{std::move(xref)}
    {}

    /// The offset of this revision's cross-reference table.
    ///
    int64_t offset{};

    /// The cross-reference table for this revision.
    ///
    cross_Reference xref;

  };

  /// COS-file internals.
  ///
  struct File::Internal
  {
    /// Constructor.
    ///
    /// This constructor is intended to be used when creating a new
    /// COS-file.
    ///
    Internal(Create_new const&,
               iostream& ios,
               string    header,
               int       major,
               int       minor)
      : ios{ios},
        header{std::move(header)},
        major{major},
        minor{minor}
    {}

    /// Underlying io stream.
    ///
    iostream& ios;

    /// The file header.
    ///
    string header;

    /// The major version.
    ///
    int major{};

    /// The minor version.
    ///
    int minor{};

    /// Previous revisions of this file.
    ///
    /// Revisions are created when writing the file, or when opening
    /// an existing file.
    ///
    deque<Revision> revisions;

    /// All objects in this file. Populated as objects are created or
    /// during file opening.
    ///
    map<Identity, Object_model::Owner> objects;

    /// The current revision's cross-reference table.
    ///
    cross_Reference xref;

    /// The document catalog, see Section 3.6.1, “Document Catalog” in
    /// the PDF-1.4 specification. Allocated on first use or when
    /// opening an existing PDF-file.
    ///
    optional<Object> document_catalog;

    /// The document information dictionary, see Section 9.2.1,
    /// “Document Information Dictionary” in the PDF-1.4
    /// specification. Allocated on first use or when opening an
    /// existing PDF-file.
    ///
    optional<Object> document_information;

  };

  /// \class File
  ///
  /// Object generations are not used for new files in the
  /// paperback implementation of the COS file format.
  ///
  /// Newly allocated objects are always assigned the next available
  /// object index with a generation of 0.
  ///
  /// Note though that paperback io support _enerations when
  /// opening an existing PDF file. That is, the index and generation
  /// will be used when looking up an object reference.
  ///

  /// Creates a new COS-file.
  ///
  /// The parameters \a major and \a minor correspond to the version
  /// of the PDF-document which the file represents.
  ///
  /// \param ios The io stream for this COS-file.
  /// \param major The major version of the document.
  /// \param minor The minor version of the document.
  /// \param header The COS-file header, e.g. \c PDF-1.4.
  ///
  File::
  File(Create_new const&,
         iostream& ios,
         int major,
         int minor,
         string header)
    : internal{
        new Internal{create_new, ios, std::move(header), major, minor}
      }
  {}

  /// This destructor will automatically commit the current revision,
  /// but any exceptions thrown during write will be ignored.
  ///
  File::
  ~File() noexcept
  {
    try {
      commit_revision();
    }
    catch (...) {
      // Nothing to do here, so just ignore the exception.
      //
    }
  }

  /// \return Returns a reference to the COS-file catalog dictionary.
  ///
  Dictionary&
  File::
  catalog()
  {
    if (!internal->document_catalog) {
      internal->document_catalog.emplace(create_object<Dictionary>());
    }

    return object_cast<Dictionary>(*internal->document_catalog);
  }

  /// \return Returns a reference to the COS-file info dictionary.
  ///
  Dictionary&
  File::
  info()
  {
    if (!internal->document_information) {
      internal->document_information.emplace(create_object<Dictionary>());
    }

    return object_cast<Dictionary>(*internal->document_information);
  }

  /// Calling this function will write all objects in the current
  /// revision to the output stream.
  ///
  /// A new revision will be created automatically.
  ///
  /// All modified objects will be marked as clean.
  ///
  void
  File::
  commit_revision()
  {
    // Is this an update or a new file?
    //
    bool const update = internal->revisions.size() > 0;

    Writer w{internal->ios, internal->major, internal->minor};

    if (!update) {
      // Write out header at the start for new files.
      //
      internal->ios.seekp(0);
      w.write_header(internal->header);
    }
    else {
      // Seek to the end for updates.
      //
      internal->ios.seekp(0, std::ios_base::end);
    }

    bool objects_written{false};

    for (auto& j : internal->objects) {
      if (!j.second.modified()) {
        continue;
      }

      objects_written = true;

      auto offset = static_cast<int64_t>(internal->ios.tellp());
      auto identity = j.first;

      internal->xref.set_offset(identity, offset);

      w.write_object(identity, j.second.container());

      // Clear the modifed mark.
      //
      j.second.reset();
    }

    // Skip writing the rest if this is an update and no objects have
    // been written out.
    //
    if (update && !objects_written) {
      return;
    }

    auto xref_offset = internal->ios.tellp();
    internal->xref.write(w, update);

    Dictionary trailer;

    // Size of the cross-reference table. Required.
    //
    trailer.insert("Size", Integer{internal->xref.size()});

    if (internal->document_catalog) {
      trailer.insert("Root", *internal->document_catalog);
    }

    if (internal->document_information) {
      trailer.insert("Info", *internal->document_information);
    }

    // Point to the previous revision, if we have one.
    //
    if (internal->revisions.size() > 0) {
      auto const& prev = internal->revisions.back();
      trailer.insert("Prev", Integer{prev.offset});
    }

    w.write_trailer(trailer);
    w.write_eof(xref_offset);

    // Add the revision we just wrote.
    //
    internal->revisions.emplace_back(xref_offset, internal->xref);

    // Reset the offsets of the used objects in the cross-reference
    // table. This ensures only modified objects will be written to
    // the cross-reference section during the next commit.
    //
    internal->xref.clear_offsets();

    // Make sure everything is flushed.
    //
    internal->ios.flush();
  }

  Object_model::Container_base&
  File::
  get_container(Identity const& identity)
  {
    return internal->objects.at(identity).container();
  }

  Object_model::Container_base const&
  File::
  get_container(Identity const& identity) const
  {
    return internal->objects.at(identity).container();
  }

  /// \return Returns the allocated index.
  ///
  Identity
  File::
  allocate()
  {
    return internal->xref.allocate();
  }

  /// \param identity The identity of the object.
  /// \param container The container of the object.
  ///
  void
  File::
  insert(Identity const& identity,
         shared_ptr<Object_model::Container_base> container)
  {
    internal->objects.emplace(identity, std::move(container));
  }

} // namespace Art::Paperback::Carousel
