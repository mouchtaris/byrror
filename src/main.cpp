#define ENABLE_PIG
#define PIG_STDLIB

#include "pig.h"
#include "stream.h"

#include <tuple>
#include <functional>
#include <type_traits>
#include <deque>
#include <array>
#include <list>
#include <vector>
#include <iostream>


using std::get;


namespace iter_stream {
    using namespace stream;

    template <typename I> struct IterPack {
        I begin, end;
    };

    template <typename I> IterPack<I> make_iter_pack(I begin, I end) { return { begin, end }; }

}

PIG_WRAP(iter_stream::IterPack);

template <typename I> struct stream::StreamOps<iter_stream::IterPack<I>> {
    using Element = std::add_const_t<typename I::value_type>;
    using Self = iter_stream::IterPack<I>;
    using This = StreamOps<Self>;

    const Self self;

    const bool __is_at_the_end = self.begin == self.end;
    head_t<Self> __just_head() const { return *self.begin; }
    Self __just_tail() const { return { next(self.begin), self.end }; }

    head_t<Self> head() const { return __is_at_the_end ? std::nullopt : __just_head(); }
    Self tail() const { return __is_at_the_end ? self : __just_tail(); }
};

namespace container_stream {
    using namespace iter_stream;

    template <typename T> struct is_container: public std::false_type { };
#   define CONTAINER_IS_CONTAINER(CONTAINER)    \
        template <typename T> struct is_container<CONTAINER<T>>: public std::true_type { }
    CONTAINER_IS_CONTAINER(std::vector);
    CONTAINER_IS_CONTAINER(std::list);
    CONTAINER_IS_CONTAINER(std::deque);
}

template <typename T> struct stream::StreamOf<std::vector<T>> {
    using Container = std::vector<T>;
    using Iter = typename Container::const_iterator;
    using IP = iter_stream::IterPack<Iter>;
    using type = StreamOps<IP>;
};

template <typename T> struct stream::StreamOpsConstructorOf<std::vector<T>> {
    struct ctor {
        stream_of_t<std::vector<T>> operator () (std::vector<T> const& self) const
            { return { { cbegin(self), cend(self) } }; }
    };
    using type = ctor;
};

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

