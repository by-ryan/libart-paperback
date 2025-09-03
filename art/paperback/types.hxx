#ifndef art__paperback__types_hxx_
#define art__paperback__types_hxx_

#include <cstdint>
#include <deque>
#include <initializer_list>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <optional>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

namespace Art::Paperback
{

#ifndef GENERATING_DOCUMENTATION
  using std::initializer_list;

  using std::invalid_argument;
  using std::logic_error;
  using std::runtime_error;

  using std::int8_t;
  using std::int16_t;
  using std::int32_t;
  using std::int64_t;

  using std::uint8_t;
  using std::uint16_t;
  using std::uint32_t;
  using std::uint64_t;

  using std::unique_ptr;
  using std::shared_ptr;
  using std::make_shared;
  using std::make_unique;

  using std::variant;
  using std::holds_alternative;

  using std::deque;
  using std::list;
  using std::map;
  using std::stack;
  using std::vector;

  using std::optional;
  using std::nullopt;

  using std::string;

  using std::istream;
  using std::ostream;
  using std::iostream;
  using std::streampos;
  using std::streamoff;
  using std::stringstream;

  using std::cin;
  using std::cout;
  using std::cerr;
#endif

  /// Index type.
  ///
  using Index = uint32_t;

  /// Generation type.
  ///
  using Generation = uint16_t;

  /// Represents the identity of an indirect object.
  ///
  struct Identity
  {
    /// Constructor.
    ///
    /// This constructor creates an identity with index 0 and
    /// generation 0.
    ///
    Identity()
    {}

    /// Constructor.
    ///
    /// \param index The index of the identity.
    /// \param generation The generation of the identity.
    ///
    Identity(Index index, Generation generation)
      : index{index}, generation{generation}
    {}

    Index index{};
    Generation generation{};

    /// Compare this identity with another.
    ///
    /// \param other The identity to compare with.
    ///
    bool
    operator==(Identity const& other) const
    {
      return index == other.index && generation == other.generation;
    }

    /// Compare this identity with another.
    ///
    /// \param other The identity to compare with.
    ///
    bool
    operator!=(Identity const& other) const
    {
      return !(*this == other);
    }

    /// Compare this identity with another.
    ///
    bool
    operator<(Identity const& other) const
    {
      if (index < other.index) {
        return true;
      }

      if (generation < other.generation) {
        return true;
      }

      return false;
    }

  };

} // namespace Art::Paperback

#endif
