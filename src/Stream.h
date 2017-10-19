#pragma once

template <typename _Self>
struct Stream;

struct StreamIterEnd_t { };
extern StreamIterEnd_t StreamIterEnd;

template <typename _Self>
struct StreamIter {
    Stream<_Self> s;

    auto operator *() const
        { return s.head().value(); };

    StreamIter<_Self>& operator ++() {
        s = s.tail();
        return *this;
    }

    bool operator == (StreamIterEnd_t) const
        { return !s.head().has_value(); }

    bool operator != (StreamIterEnd_t) const
        { return s.head().has_value(); }
};

template <typename _Self> StreamIter<_Self> begin(Stream<_Self> const& s) { return { s }; }
template <typename _Self> StreamIterEnd_t end(Stream<_Self> const&) { return StreamIterEnd; }

