#include <iostream>
#include <vector>
#include <sstream>
#include <functional>
#include <list>
#include <iterator>
#include <optional>
#include <type_traits>

#include <with.hpp>
#include <base.hpp>

#include <Stream.h>
#include <ContainerStream.hpp>

using std::begin,
      std::end;

struct StreamIterEnd_t { } StreamIterEnd;

template <typename _Self>
struct StreamIter {
    Stream<_Self> const& s;

    auto operator *() const {
        return s.head().value();
    };

    StreamIter<_Self> operator ++() const {
        return { s.tail() };
    }

    bool operator == (StreamIterEnd_t) const {
        return !s.head().has_value();
    }
};

template <typename _Self> StreamIter<_Self> begin(Stream<_Self> const& s) { return { s }; }
template <typename _Self> StreamIterEnd_t end(Stream<_Self> const&) { return StreamIterEnd; }

//template <typename _Container>
//auto begin(ContainerStream<_Container> const& s)
//    -> typename ContainerStream<_Container>::Iter
//{
//    return s.current;
//}
//
//template <typename _Container>
//auto end(ContainerStream<_Container> const& s)
//    -> typename ContainerStream<_Container>::Iter
//{
//    return s.last;
//}


int main(int argc, char** argv) {
    (void) argc;
    (void) argv;

    std::vector<int> v { 1, 2, 3, };
    auto s = stream(v);
    (void) s;

    auto p = [](auto wat) { std::cout << wat << ','; };
    auto done = [] { std::cout << std::endl; };

    for (auto el: v) p(el);
    done();

    for (auto i = begin(s); i != end(s); ++i)
        p(*i);
    done();

    // for (auto el: s) p(el);
    // done();
}
