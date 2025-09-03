#include <art/paperback/carousel/cross-reference.hxx>

#include <art/paperback/except.hxx>

namespace Art::Paperback::Carousel
{

  /// Represents a free entry in the cross-reference table.
  ///
  /// In contrast with used entries, free entries are always written
  /// to the cross-reference section of the COS-file.
  ///
  struct cross_Reference::Free_entry
  {
    /// The next free index in the cross-reference table.
    ///
    Index next{};

    /// The generation of the next entry.
    ///
    Generation next_generation{};

  };

  /// Represents a used entry in the cross-reference table.
  ///
  /// The offset of the object is set during write, and only entries
  /// with a set offset will be written to the COS-file
  /// cross-reference section.
  ///
  struct cross_Reference::Used_entry
  {
    /// The offset in the COS-file of this entry.
    ///
    optional<int64_t> offset{};

  };

  /// \class cross_Reference
  ///
  /// The cross-reference table maintains a link between an object
  /// index/generation and its position in the COS-file.
  ///
  /// The paperback implementation of the PDF 1.4 specification
  /// does not re-use the index of a previously deleted object, hence
  /// the generation of new objects will always be zero (0).
  ///

  /// This constructor creates a new cross-reference table.
  ///
  /// Object 0 will be automatically allocated.
  ///
  cross_Reference::
  cross_Reference()
  {
    // Make sure to allocate the special object 0.
    //
    _table[Identity{0, 0}] = Free_entry{0, 0xffff};
  }

  cross_Reference::
  cross_Reference(cross_Reference const&) = default;

  cross_Reference::
  cross_Reference(cross_Reference&&) = default;

  cross_Reference::
  ~cross_Reference() noexcept
  {}

  /// \return Returns the size of the cross-reference table.
  ///
  uint32_t
  cross_Reference::
  size() const
  {
    uint32_t size{};

    for (auto const& j : _table) {
      if (j.first.index > size) {
        size = j.first.index;
      }
    }

    return size + 1;
  }

  /// \return Returns the identity of the newly allocated object.
  ///
  Identity
  cross_Reference::
  allocate()
  {
    auto identity = next();
    _table[identity] = Used_entry{nullopt};
    return identity;
  }

  /// \param identity The object identity for which to retrieve the offset.
  /// \return Returns the file offset of the object.
  ///
  int64_t
  cross_Reference::
  get_offset(Identity identity) const
  {
#if 0
    auto it = _table.find(identity);

    if (it == _table.end()) {
      return 0;
    }

    if (it->second.free) {
      return 0;
    }

    return it->second.offset;
#endif
    return 0;
  }

  /// \throw Internal_error Thrown if the object is not allocated.
  ///
  void
  cross_Reference::
  set_offset(Identity identity, int64_t offset)
  {
    auto entry = _table.find(identity);

    if (entry == _table.end()) {
      raise<Internal_error>{} << "invalid object index";
    }

    if (!holds_alternative<Used_entry>(entry->second)) {
      raise<Internal_error>{} << "invalid object index";
    }

    std::get<Used_entry>(entry->second).offset = offset;
  }

  /// \return Returns the index of the next available object.
  ///
  Identity
  cross_Reference::
  next() const
  {
    Index next{};

    for (auto const& j : _table) {
      if (next < j.first.index) {
        next = j.first.index;
      }
    }

    return Identity{next + 1, 0};
  }

  /// \param w The COS-file writer.
  /// \param update True if this is an update; false otherwise.
  ///
  void
  cross_Reference::
  write(Writer& w, bool update)
  {
    w.begin_xref();

    // Cross-reference table entry.
    //
    struct Entry
    {
      // The index of this entry.
      //
      Index index{};

      // Either the offset for used entries, or the next free index
      // for free entries.
      //
      uint32_t param0{};

      // Either the generation for used entries, or the next
      // generation for free entries.
      //
      uint16_t param1{};

      // Is this a free entry?
      //
      bool free{};

    };

    vector<Entry> entries;

    for (auto it = _table.begin(); it != _table.end(); ++it) {
      auto v = [&](auto&& entry)
      {
        using T = std::decay_t<decltype(entry)>;

        if constexpr (std::is_same_v<T, Used_entry>) {
          // Ignore used entries without an offset. This will be the
          // case for allocated objects that hasn't been written out.
          //
          if (entry.offset == nullopt) {
            return;
          }

          auto index = it->first.index;
          auto offset = *entry.offset;
          auto generation = it->first.generation;

          entries.emplace_back(
            index,
            offset,
            generation,
            false
          );
        }
        else if constexpr (std::is_same_v<T, Free_entry>) {
          // As we do not support the removal of objects, we only
          // write free entries when writing the first cross-reference
          // table in a file.
          //
          if (update) {
            return;
          }

          auto index = it->first.index;
          auto next = entry.next;
          auto next_generation = entry.next_generation;

          entries.emplace_back(
            index,
            next,
            next_generation,
            true
          );
        }
        else {
          static_assert(false, "non-exhaustive visitor");
        }
      };

      std::visit(v, it->second);
    }

    // Write the cross-reference table.
    //
    for (auto it = entries.begin(); it != entries.end();) {
      uint32_t start{it->index};
      uint32_t count{1};

      auto k = it;
      auto prev = k++;

      while (
        k != entries.end() && k->index == prev->index + 1
      ) {
        prev = k++;
        ++count;
      }

      w.begin_xref_chunk(start, count);

      auto kt = it;

      for (uint32_t i{0}; i < count; ++i, ++kt) {
        if (kt->free) {
          w.write_xref_free_entry(kt->param0, kt->param1);
          continue;
        }

        w.write_xref_used_entry(kt->param0, kt->param1);
      }

      it = k;
    }
  }

  // This is typically called after the cross-reference table has been
  // written out.
  //
  void
  cross_Reference::
  clear_offsets()
  {
    for (auto& j : _table) {
      if (holds_alternative<Used_entry>(j.second)) {
        std::get<Used_entry>(j.second).offset = nullopt;
      }
    }
  }

  cross_Reference&
  cross_Reference::
  operator=(cross_Reference const&) = default;

  cross_Reference&
  cross_Reference::
  operator=(cross_Reference&&) = default;

} // namespace Art::Paperback::Carousel
