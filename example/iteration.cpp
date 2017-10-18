#include <iterator>
#include <iostream>

using std::begin;
using std::end;

struct lol_t {
    static const int a = 10, b = a + 10, c = b + 10, d = c + 10;
};
lol_t lol;
const int lol_t::a, lol_t::b, lol_t::c, lol_t::d;

const int* begin(lol_t const& l) {
    std::cout << "begin(lol)\n";
    return &l.a;
}

const int* end(lol_t const& l) {
    std::cout << "end(lol)\n";
    return &l.d + 1;
}

int example_iteration(int, char**) {
    std::cout << begin(lol) << ',' << end(lol) << '\n';
    for (auto i = begin(lol); i != end(lol); ++i)
        std::cout << *i << ',';
    std::cout << '\n';
    for (auto el: lol)
        std::cout << el << ',';
    std::cout << '\n';
    return 0;
}
