#ifndef art__paperback__internals__font_collection_hxx_
#define art__paperback__internals__font_collection_hxx_

#include <art/paperback/types.hxx>
#include <art/paperback/forward.hxx>

namespace Art::Paperback::Internals
{

  class Font_collection
  {
  public:
    struct Create_new {};
    static constexpr Create_new const create_new{};

    /// Constructor.
    ///
    Font_collection(Create_new const&, Resource_collection&);

    /// Destructor.
    ///
    ~Font_collection() noexcept;

    /// Access the parent resource collection.
    ///
    Resource_collection&
    resource_collection();

    /// Get the object for this font collection.
    ///
    Carousel::Object
    object();

    /// Embed font in this font collection and return the local name of the
    /// embedded font.
    ///
    Carousel::Name
    embed(Graphics::Font& f);

  private:
    Font_collection(Font_collection const&) = delete;
    Font_collection(Font_collection&&) = delete;
    Font_collection& operator=(Font_collection const&) = delete;
    Font_collection& operator=(Font_collection&&) = delete;

  private:
    struct Internal;
    unique_ptr<Internal> internal;

  };

} // namespace Art::Paperback::Internals

#endif
