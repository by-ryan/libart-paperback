#ifndef art__paperback__carousel__dictionary_hxx_
#define art__paperback__carousel__dictionary_hxx_

#include <art/paperback/types.hxx>
#include <art/paperback/forward.hxx>

#include <art/paperback/carousel/name.hxx>
#include <art/paperback/carousel/object-model.hxx>

namespace Art::Paperback::Carousel
{

  /// Represents a COS dictionary.
  ///
  class Dictionary
    : public Object_model::Value_base
  {
  public:
    /// Iterator type.
    ///
    using iterator = typename map<Name, Object>::iterator;

    /// Immutable iterator type.
    ///
    using const_iterator = typename map<Name, Object>::const_iterator;

    /// Constructor.
    ///
    Dictionary();

    /// Constructor.
    ///
    explicit
    Dictionary(map<Name, Object>);

    /// Constructor.
    ///
    Dictionary(Dictionary const&);

    /// Constructor.
    ///
    Dictionary(Dictionary&&);

    /// Destructor.
    ///
    ~Dictionary() noexcept;

    /// Get the size of the dictionary.
    ///
    size_t
    size() const;

    /// Check if the dictionary is empty.
    ////
    bool
    empty() const;

    /// Check if the dictionary contains a key.
    ///
    bool
    contains(Name const&);

    /// Access entry.
    ///
    Object&
    at(Name const&);

    /// Access entry.
    ///
    Object const&
    at(Name const&) const;

    /// Get begin iterator.
    ///
    iterator
    begin();

    /// Get begin iterator.
    ///
    const_iterator
    begin() const;

    /// Get begin iterator.
    ///
    const_iterator
    cbegin() const;

    /// Get past-the-end iterator.
    ///
    iterator
    end();

    /// Get past-the-end iterator.
    ///
    const_iterator
    end() const;

    /// Get past-the-end iterator.
    ///
    const_iterator
    cend() const;

    /// Insert entry into dictionary.
    ///
    void
    insert(Name const&, Object);

    /// Remove entry from dictionary.
    ///
    void
    erase(Name const&);

    /// Assignment.
    ///
    Dictionary&
    operator=(Dictionary const&);

    /// Assignment.
    ///
    Dictionary&
    operator=(Dictionary&&);

    /// Comparison.
    ///
    bool
    operator==(Dictionary const&) const;

    /// Comparison.
    ///
    bool
    operator!=(Dictionary const&) const;

  protected:
    void
    attach_children(Object_model::Owner&) override;

  private:
    map<Name, Object> _data;

  };

} // namespace Art::Paperback::Carousel

#endif
