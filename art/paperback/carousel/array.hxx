#ifndef art__paperback__carousel__array_hxx_
#define art__paperback__carousel__array_hxx_

#include <art/paperback/types.hxx>
#include <art/paperback/forward.hxx>

#include <art/paperback/carousel/object-model.hxx>

namespace Art::Paperback::Carousel
{

  class Array
    : public Object_model::Value_base
  {
  public:
    /// Iterator type.
    ///
    using iterator = typename deque<Object>::iterator;

    /// Immutbale iterator type.
    ///
    using const_iterator = typename deque<Object>::const_iterator;

    /// Constructor.
    ///
    Array();

    /// Constructor.
    ///
    Array(vector<Object>);

    /// Constructor.
    ///
    Array(Array const&);

    /// Constructor.
    ///
    Array(Array&&);

    /// Destructor.
    ///
    ~Array() noexcept;

    /// Get the size of the array.
    ///
    size_t
    size() const;

    /// Check if the array is empty.
    ///
    bool
    empty() const;

    /// Get a reference to the first element.
    ///
    Object&
    front();

    /// Get a reference to the first element.
    ///
    Object const&
    front() const;

    /// Get a reference to the last element.
    ///
    Object&
    back();

    /// Get a reference to the last element.
    ///
    Object const&
    back() const;

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

    /// Push element to the front of the array.
    ///
    Object&
    push_front(Object const&);

    /// Push element to the back of the array.
    ///
    Object&
    push_back(Object const&);

    void
    pop_front();

    void
    pop_back();

    /// Assignment.
    ///
    Array&
    operator=(Array const&);

    /// Assignment.
    ///
    Array&
    operator=(Array&&);

    /// Comparison.
    ///
    bool
    operator==(Array const&) const;

    /// Comparison.
    ///
    bool
    operator!=(Array const&) const;

  protected:
    void
    attach_children(Object_model::Owner&) override;

  private:
    deque<Object> _data;

  };

} // namespace Art::Paperback::Carousel

#endif
