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

template <typename T> struct Traverse;

template <typename T> void
traverse(T&& self, typename Traverse<T>::Callback f)
    { Traverse<T> { self }(f); }

template <typename T> struct
Traverse {
    using Self = T;
    using Element = stream::element_t<T>;
    using Callback = std::function<void (Element const&)>;

    Self self;

    void operator () (Callback f) const {
        auto&& head = stream::head(self);

        if (head.has_value()) {
            f(head.value());
            traverse(stream::tail(self), f);
        }
    }
};
PIG_WRAP(Traverse);

struct TheVoid {
    template <typename ...Args>
    TheVoid& operator << (Args&&...) { return *this; }
};
TheVoid the_void;

int main(int, char**) {
    using stream::head,
          stream::tail,
          pig::pig,
          pig::pig_move,
          pig::pig_copy,
          pig::pig_pod,
          pig::pig_ref;

    const std::vector<int> v { 1, 2, 3 };
    const std::list<unsigned int> l { 5, 6, 7 };
    const std::deque<char> d { 8, 9, 0 };
    const std::set<long long> s { -1, -2, -3, };

    auto printit = [](auto&& v) {
        the_void << "hi" << '\n'
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

    auto const enlist = [](auto i) { std::cout << i << ", "; };
    auto const nl = []() { std::cout << '\n'; };
    traverse(v, enlist); nl();
    traverse(l, enlist); nl();
    traverse(d, enlist); nl();
    traverse(s, enlist); nl();

    return 0;
}

