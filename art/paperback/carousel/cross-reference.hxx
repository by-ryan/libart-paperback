#ifndef art__paperback__carousel__cross_reference_hxx_
#define art__paperback__carousel__cross_reference_hxx_

#include <art/paperback/types.hxx>
#include <art/paperback/forward.hxx>

#include <art/paperback/carousel/writer.hxx>

namespace Art::Paperback::Carousel
{

  /// Implements the COS cross-reference table.
  ///
  class cross_Reference
  {
  public:
    /// Constructor.
    ///
    cross_Reference();

    /// Constructor.
    ///
    cross_Reference(cross_Reference const&);

    /// Constructor.
    ///
    cross_Reference(cross_Reference&&);

    /// Destructor.
    ///
    ~cross_Reference() noexcept;

    /// Get the size of the cross-reference table.
    ///
    uint32_t
    size() const;

    /// Allocate a new object index.
    ///
    Identity
    allocate();

    /// Get the offset of a used entry.
    ///
    int64_t
    get_offset(Identity) const;

    /// Set the offset of a used entry.
    ///
    void
    set_offset(Identity, int64_t);

    /// Get the next available object identity.
    ///
    Identity
    next() const;

    /// Write the cross-reference to an output stream.
    ///
    void
    write(Writer&, bool);

    /// Clears the offsets of used entries.
    ///
    void
    clear_offsets();

    /// Assignment.
    ///
    cross_Reference&
    operator=(cross_Reference const&);

    /// Assignment.
    ///
    cross_Reference&
    operator=(cross_Reference&&);

  private:
    struct Free_entry;
    struct Used_entry;

    using Entry = variant<Free_entry, Used_entry>;

    /// Cross-reference table entries.
    ///
    map<Identity, Entry> _table;

  };

} // namespace Art::Paperback::Carousel

#endif
