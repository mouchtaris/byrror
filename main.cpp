#include <iostream>
#include <vector>
#include <sstream>
#include <functional>
#include <list>
#include <iterator>
#include <optional>

#include <with.hpp>
#include <base.hpp>

template <typename _cont_type>
struct ContainerStream {
    using Self = _cont_type;
    using Element = typename Self::value_type;

    std::optional<Element> head() const 
        { return atTheEnd() ? std::nullopt : std::make_optional(*current); }
    ContainerStream<Self> tail() const
        { return atTheEnd() ? *this : ContainerStream<Self> {std::next(current, 1), end}; }

// private
    using Iter = typename Self::iterator;
    inline bool atTheEnd() const { return current == end; }
    Iter current;
    Iter const end;
};

int main(int, char**) {
    std::vector<int> v = { 1, 2, 3, 4, };
    auto cont = ContainerStream<decltype(v)> { std::begin(v), std::end(v) };
    for (auto el = cont.head(); el.has_value(); el = cont.tail().head())
        std::cout << el.value_or(666) << ',';
    return 0;
}
