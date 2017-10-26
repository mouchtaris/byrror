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
    std::list<unsigned int> l { 5, 6, 7 };
    std::deque<char> d { 8, 9, 0 };
    std::set<long long> s { -1, -2, -3, };

    auto printit = [](auto v) {
        std::cout << "hi" << '\n'
            << head(v) << '\n'
            << head(tail(v)) << '\n'
            << head(tail(tail(v))) << '\n'
            << head(tail(tail(tail(v)))) << '\n'
            << head(tail(tail(tail(tail(v))))) << '\n'
            ;
    };

    printit(v);
    printit(l);
    printit(d);
    printit(s);

    return 0;
}

