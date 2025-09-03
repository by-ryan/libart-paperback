#include <art/paperback/internals/font-collection.hxx>
#include <art/paperback/internals/resource-collection.hxx>

#include <art/paperback/except.hxx>
#include <art/paperback/document.hxx>

#include <art/paperback/carousel/dictionary.hxx>
#include <art/paperback/carousel/file.hxx>
#include <art/paperback/carousel/name.hxx>
#include <art/paperback/carousel/object.hxx>

#include <art/paperback/graphics/font.hxx>

namespace Art::Paperback::Internals
{

  struct Font_collection::Internal
  {
    Internal(Resource_collection& parent)
      : parent{parent},
        object{Carousel::Dictionary{}},
        data{object_cast<Carousel::Dictionary>(object)}
    {}

    Resource_collection& parent;
    Carousel::Object          object;
    Carousel::Dictionary&     data;

    Carousel::Name
    get_next_local_name()
    {
      stringstream str;
      str << "F" << data.size();

      return Carousel::Name{str.str()};
    }

  };

  /// This constructor creates a new font collection.
  ///
  /// \param parent The parent resource collection.
  ///
  Font_collection::
  Font_collection(Create_new const&,
                    Resource_collection& parent)
    : internal{new Internal{parent}}
  {}

  Font_collection::
  ~Font_collection() noexcept
  {}

  /// \return Returns a reference to the parent resource collection.
  ///
  Resource_collection&
  Font_collection::
  resource_collection()
  {
    return internal->parent;
  }

  /// \return Return the data object for this font collection.
  ///
  Carousel::Object
  Font_collection::
  object()
  {
    return internal->object;
  }

  /// \param font The font to embed.
  /// \return Returns the local name of the embedded font.
  ///
  Carousel::Name
  Font_collection::
  embed(Graphics::Font& font)
  {
    auto local_name = internal->get_next_local_name();

    if (internal->data.contains(local_name)) {
      raise<Internal_error>{} << "font local name already used";
    }

    internal->data.insert(local_name, font.object());

    return local_name;
  }

} // namespace Art::Paperback::Internals
