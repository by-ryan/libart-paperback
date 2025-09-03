#ifndef art__paperback__page_hxx_
#define art__paperback__page_hxx_

#include <art/paperback/types.hxx>
#include <art/paperback/forward.hxx>
#include <art/paperback/primitives.hxx>

namespace Art::Paperback
{

  class Page
  {
  public:
    struct Create_new {};
    static constexpr Create_new const create_new{};

    /// Properties of a new page.
    ///
    struct Properties
    {
      /// Specifies the page's media box (required).
      ///
      Rectangle media_box;

      /// Specifies the page's crop box.
      ///
      optional<Rectangle> crop_box;

      /// Specifies the page's bleed box.
      ///
      optional<Rectangle> bleed_box;

      /// Specifies the page's trim box.
      ///
      optional<Rectangle> trim_box;

      /// Specifies the page's art box.
      ///
      optional<Rectangle> art_box;

    };

    /// Constructor.
    ///
    Page(Create_new const&,
           Internals::Page_tree&,
           Properties const&);

    /// Destructor.
    ///
    ~Page() noexcept;

    /// Access the parent page tree.
    ///
    Internals::Page_tree&
    page_tree() const;

    /// Access the page's object.
    ///
    Carousel::Object
    object() const;

    /// Access the page content stream.
    ///
    Carousel::Stream&
    contents();

    /// Access page resource collection.
    ///
    Internals::Resource_collection&
    resources();

  private:
    Page(Page const&) = delete;
    Page(Page&&) = delete;
    Page& operator=(Page const&) = delete;
    Page& operator=(Page&&) = delete;

  private:
    struct Internal;
    unique_ptr<Internal> internal;

  };

  /// Get the document associated with a page.
  ///
  Document&
  document(Page&);

  /// Get the document associated with a page.
  ///
  Document const&
  document(Page const&);

} // namespace Art::Paperback

#endif
