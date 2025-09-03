#ifndef art__paperback__forward_hxx_
#define art__paperback__forward_hxx_

/// Primary paperback namespace.
///
namespace Art::Paperback
{

  class Visitor;

  template<typename>
  class Basic_visitor;

  /// COS file format implementation namespace.
  ///
  namespace Carousel
  {

    class Object;

    template<typename>
    bool
    is_of_type(Object const&);

    template<typename T>
    T&
    object_cast(Object&);

    template<typename T>
    T const&
    object_cast(Object const&);

    Object
    clone(Object&);

    void
    accept(Object&, Visitor&);

    void
    accept(Object const&, Visitor&);

    class Undefined;

    class Array;
    class Boolean;
    class Dictionary;
    class Integer;
    class Name;
    class Real;
    class Text;

    class Stream;

    class Cross_reference;

    class Writer;
    class File;

    /// COS object model namespace.
    ///
    /// This namespace contains classes implementing the COS object
    /// model (values, references, containers and owners).
    ///
    namespace Object_model
    {

      class abstract_value;
      template<typename>

      class Value;

      class Abstract;
      class Reference;

      class Owner;

      class Container_base;

      template<typename>
      class Container;

    } // namespace Object_model

  } // namespace Carousel

  /// Internal namespace.
  ///
  /// This namespace contains internal classes and functions.
  ///
  namespace Internals
  {

    class Document_catalog;
    class Font_collection;
    class Page_tree;
    class Resource_collection;

  } // namespace Internals

  /// Graphics namespace.
  ///
  /// Text, font and graphics related classes.
  ///
  namespace Graphics
  {

    class Canvas;

    class Font;
    class Standard_font;

  } // namespace Graphics

  class Document_information;
  class Document;
  class Page;

  class Rectangle;

} // namespace Art::Paperback

#endif
