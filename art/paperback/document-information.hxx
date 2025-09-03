#ifndef art__paperback__document_information_hxx_
#define art__paperback__document_information_hxx_

#include <art/paperback/types.hxx>
#include <art/paperback/forward.hxx>

namespace Art::Paperback
{

  class Document_information
  {
  public:
    struct Create_new {};
    static constexpr Create_new const create_new{};

    Document_information(Create_new const&, Document&);

    ~Document_information() noexcept;

    /// Access the owning document.
    ///
    Document&
    document();

    /// Access the owning document.
    ///
    Document const&
    document() const;

    /// Get the object for the document information.
    ///
    Carousel::Object
    object();

    /// Access the title.
    ///
    optional<string>
    title() const;

    /// Set or remove the title.
    ///
    void
    set_title(optional<string>);

    /// Access the author.
    ///
    optional<string>
    author() const;

    /// Set or remove the author.
    ///
    void
    set_author(optional<string>);

    /// Access the subject.
    ///
    optional<string>
    subject() const;

    /// Set or remove the subject.
    ///
    void
    set_subject(optional<string>);

    /// Access the keywords.
    ///
    optional<string>
    keywords() const;

    /// Set or remove the keywords.
    ///
    void
    set_keywords(optional<string>);

    /// Access the creator.
    ///
    optional<string>
    creator() const;

    /// Set or remove the creator.
    ///
    void
    set_creator(optional<string>);

    /// Access the producer.
    ///
    optional<string>
    producer() const;

    /// Set or remove the producer.
    ///
    void
    set_producer(optional<string>);

  private:
    Document_information(Document_information const&) = delete;
    Document_information(Document_information&&) = delete;
    Document_information& operator=(Document_information const&) = delete;
    Document_information& operator=(Document_information&&) = delete;

    struct Internal;
    unique_ptr<Internal> internal;

  };

} // namespace Art::Paperback

#endif
