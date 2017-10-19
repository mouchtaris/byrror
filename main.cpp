#include <iostream>
#include <vector>
#include <sstream>
#include <functional>
#include <list>
#include <iterator>
#include <optional>
#include <type_traits>

#include "src/with.hpp"
#include "src/base.hpp"

#include "src/Stream.h"
#include "src/ContainerStream.hpp"

using std::begin,
      std::end;

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

    // for (auto i = begin(s); i != end(s); ++i)
    //     p(*i);
    // done();

    // for (auto el: s) p(el);
    // done();
}
