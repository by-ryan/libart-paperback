#include <art/paperback/document-information.hxx>

#include <art/paperback/document.hxx>
#include <art/paperback/except.hxx>

#include <art/paperback/carousel/dictionary.hxx>
#include <art/paperback/carousel/file.hxx>
#include <art/paperback/carousel/name.hxx>
#include <art/paperback/carousel/object.hxx>
#include <art/paperback/carousel/text.hxx>

namespace Art::Paperback
{

  /// Holds document information internal data.
  ///
  struct Document_information::Internal
  {
    Internal(Document& document)
      : document{document},
        data{document.file().info()}
    {}

    Document& document;
    Carousel::Dictionary& data;

  };

  Document_information::
  Document_information(Create_new const&,
                         Document& document)
    : internal{new Internal{document}}
  {}

  Document_information::
  ~Document_information() noexcept
  {}

  Document&
  Document_information::
  document()
  {
    return internal->document;
  }

  Document const&
  Document_information::
  document() const
  {
    return internal->document;
  }

  /// Returns the title of the document, if available.
  ///
  std::optional<std::string>
  Document_information::
  title() const
  {
    document().check_minimum_version(1, 1);

    if (internal->data.contains("Title")) {
      return *object_cast<Carousel::Text>(internal->data.at("Title"));
    }

    return nullopt;
  }

  /// If \a value is \c nullopt the title is removed.
  ///
  /// \param value The new title.
  ///
  void
  Document_information::
  set_title(std::optional<std::string> value)
  {
    document().check_minimum_version(1, 1);

    if (value) {
      internal->data.insert("Title", Carousel::Text{*value});
    }
    else {
      internal->data.erase("Title");
    }
  }

  std::optional<std::string>
  Document_information::
  author() const
  {
    if (internal->data.contains("Author")) {
      return *object_cast<Carousel::Text>(internal->data.at("Author"));
    }

    return nullopt;
  }

  /// If \a value is \c nullopt the author is removed.
  ///
  /// \param value The new author.
  ///
  void
  Document_information::
  set_author(std::optional<std::string> value)
  {
    if (value) {
      internal->data.insert("Author", Carousel::Text{*value});
    }
    else {
      internal->data.erase("Author");
    }
  }

  std::optional<std::string>
  Document_information::
  subject() const
  {
    document().check_minimum_version(1, 1);

    if (internal->data.contains("Subject")) {
      return *object_cast<Carousel::Text>(internal->data.at("Subject"));
    }

    return nullopt;
  }

  /// If \a value is \c nullopt the subject is removed.
  ///
  /// \param value The new subject.
  ///
  void
  Document_information::
  set_subject(std::optional<std::string> value)
  {
    document().check_minimum_version(1, 1);

    if (value) {
      internal->data.insert("Subject", Carousel::Text{*value});
    }
    else {
      internal->data.erase("Subject");
    }
  }

  std::optional<std::string>
  Document_information::
  keywords() const
  {
    document().check_minimum_version(1, 1);

    if (internal->data.contains("Keywords")) {
      return *object_cast<Carousel::Text>(internal->data.at("Keywords"));
    }

    return nullopt;
  }

  /// If \a value is \c nullopt the keywords are removed.
  ///
  /// \param value The new keywords.
  ///
  void
  Document_information::
  set_keywords(std::optional<std::string> value)
  {
    document().check_minimum_version(1, 1);

    if (value) {
      internal->data.insert("Keywords", Carousel::Text{*value});
    }
    else {
      internal->data.erase("Keywords");
    }
  }

  std::optional<std::string>
  Document_information::
  creator() const
  {
    if (internal->data.contains("Creator")) {
      return *object_cast<Carousel::Text>(internal->data.at("Creator"));
    }

    return nullopt;
  }

  /// If \a value is \c nullopt the creator is removed.
  ///
  /// \param value The new creator.
  ///
  void
  Document_information::
  set_creator(std::optional<std::string> value)
  {
    if (value) {
      internal->data.insert("Creator", Carousel::Text{*value});
    }
    else {
      internal->data.erase("Creator");
    }
  }

  std::optional<std::string>
  Document_information::
  producer() const
  {
    if (internal->data.contains("Producer")) {
      return *object_cast<Carousel::Text>(internal->data.at("Producer"));
    }

    return nullopt;
  }

  /// If \a value is \c nullopt the producer is removed.
  ///
  /// \param value The new producer.
  ///
  void
  Document_information::
  set_producer(std::optional<std::string> value)
  {
    if (value) {
      internal->data.insert("Producer", Carousel::Text{*value});
    }
    else {
      internal->data.erase("Producer");
    }
  }

} // namespace Art::Paperback
