#define ENABLE_PIG
#define PIG_STDLIB

#include "pig.h"
#include "container_stream.h"

#include <tuple>
#include <functional>
#include <type_traits>
#include <deque>
#include <array>
#include <list>
#include <vector>
#include <iostream>

using std::get;

namespace container_stream {
    using namespace iter_stream;

    template <typename T> struct is_container: public std::false_type { };
#   define CONTAINER_IS_CONTAINER(CONTAINER)    \
        template <typename T> struct is_container<CONTAINER<T>>: public std::true_type { }
    CONTAINER_IS_CONTAINER(std::vector);
    CONTAINER_IS_CONTAINER(std::list);
    CONTAINER_IS_CONTAINER(std::deque);
}

template <typename T> std::ostream& operator << (std::ostream& o, std::optional<T> opt) {
    return opt.has_value() ? (o << "optional[" << opt.value() << ']') : ( o << "<nothing>" );
}

int main(int, char**) {
    using stream::head,
          stream::tail,
          pig::pig,
          pig::pig_move,
          pig::pig_copy,
          pig::pig_pod,
          pig::pig_ref;

    std::vector<int> v { 1, 2, 3 };

    std::cout << "hi" << '\n'
        << head(v) << '\n'
        << head(tail(v)) << '\n'
        << head(tail(tail(v))) << '\n'
        << head(tail(tail(tail(v)))) << '\n'
        << head(tail(tail(tail(tail(v))))) << '\n'
        ;

    return 0;
}

