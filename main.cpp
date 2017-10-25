#include <functional>
#include <array>
#include <list>
#include <tuple>
#include <optional>
#include <vector>
#include <iostream>
#include <string>
#include <type_traits>

#define CONCEPT_CHECK(NAME) static_assert(Check:: NAME ::value, #NAME)

namespace stream {

    using std::get,
          std::next;

    //
    // Stream entrypoints
    //
    template <typename T> struct Stream;
    template <typename T> struct of { using type = Stream<T>; };
    template <typename T> using of_t = typename of<T>::type;
    template <typename T> of_t<std::decay_t<T>> ops() { return { }; }
    template <typename T> auto head(T&& self) { return ops<T>().Head(std::forward<T>(self)); }
    template <typename T> auto tail(T&& self) { return ops<T>().tail(std::forward<T>(self)); }

    //
    // Iterator stream
    //
    template <typename Iter> using Iters = std::tuple<Iter, Iter>;
    template <typename Iter> struct ItersOps {
        using iterator = Iter;
        using Iters = stream::Iters<Iter>;
        iterator begin(Iters iters) const { return get<0>(iters); }
        iterator end(Iters iters) const { return get<1>(iters); }
        bool is_end(Iters iters) const { return begin(iters) == end(iters); }
        Iters next(Iters iters) const { return { std::next(begin(iters)), end(iters) }; }
    };

    template <typename Iter> struct Stream<Iters<Iter>> {
        using Ops = ItersOps<Iter>;
        using Self = typename Ops::Iters;
        using Element = typename Iter::value_type;
        Ops __ops() const { return { }; }
        auto head(Self iters) const
            -> std::optional<Element> { return *__ops().begin(iters); }
        auto tail(Self iters) const
            -> Self { return __ops().is_end(iters) ? iters : __ops().next(iters); }

        const std::function<std::optional<Element> (Self)> Head =
            [this] (Self iters){ return *__ops().begin(iters); };
    };

    //
    // Container streams
    //
    template <typename Container>
    struct ContainerStream {
        using Self = Container;
        using iterator = typename Self::const_iterator;
        using Iters = stream::Iters<iterator>;
        using IterStream = Stream<Iters>;
        using Element = typename IterStream::Element;
        static_assert(
            std::is_same_v<Element, typename Container::value_type>,
            "failed");
        Iters __iters(Self const& c) const { return { begin(c), end(c) }; }
        auto head(Self const& c) const { return stream::head(__iters(c)); }
        auto tail(Self const& c) const { return stream::tail(__iters(c)); }

        const std::function<std::optional<Element> (Self const&)> Head =
            [this] (Self const& c) { return stream::head(__iters(c)); };
    };

#   define DEFINE_CONTAINER_STREAM(CONTAINER) \
        template <typename T> struct Stream<CONTAINER<T>>: public ContainerStream<CONTAINER<T>> { }
    DEFINE_CONTAINER_STREAM(std::vector);
    DEFINE_CONTAINER_STREAM(std::list);


    //
    // Stream concept
    //
    template <typename T> struct __ConceptChecks {
        template <typename = 
            decltype(std::declval<of_t<T>>().head(std::declval<T>()))
            >
            using head = std::true_type;
        template <int = 0> using is = std::true_type;
    };

    template <typename T> struct __ConceptAssertions {
        using Checks = __ConceptChecks<T>;
        static_assert(Checks::head_type::value, "failed");
    };

    template <typename T> extern constexpr bool is = __ConceptChecks<std::decay_t<T>>::template is<>::value;
    template <typename T> constexpr bool is_type_of(T&&) { return is<T>; }
}

namespace pig {
    template <typename T> struct Pig;

    template <typename T> struct PigOf
        { using type = Pig<T>; };

    template <typename T> using PigOf_t = typename PigOf<T>::type;

    template <typename T> static std::string pig = PigOf_t<T> { }.name;

    //
    // Type mods
    //
    template <typename T> struct Pig<const T> { const std::string name = std::string("const ") + pig<T>; };
    template <typename T> struct Pig<T&> { const std::string name = pig<T> + "&"; };
    template <typename T> struct Pig<T&&> { const std::string name = pig<T> + "&&"; };

    //
    // Standard types
    //
#   define PIG_SIMPLE(TYPE) \
        template <> struct Pig<TYPE> { const std::string name = #TYPE; }
    PIG_SIMPLE(char);
    PIG_SIMPLE(unsigned char);
    PIG_SIMPLE(short);
    PIG_SIMPLE(unsigned short);
    PIG_SIMPLE(int);
    PIG_SIMPLE(unsigned int);
    PIG_SIMPLE(long);
    PIG_SIMPLE(unsigned long);
    PIG_SIMPLE(long long);
    PIG_SIMPLE(unsigned long long);

    //
    // Type constructors 1
    //
}

//
// STD AUGMENTATION
//
template <typename T> std::ostream& operator << (std::ostream& o, std::optional<T>&& opt) {
    return opt.has_value() ? (o << opt.value()) : (o << "<nothing>");
}

//
// Stream => C++ Iterable
//

int main(int, char**) {
    using stream::head,
          stream::tail;
    std::vector<int> v = { 1, 2, 3 };
    std::list<int> l = { 4, 5, 6 };
    std::array<int, 3> a = { { 7, 8, 9 } };
    std::cout
        << pig::pig<const unsigned long long> << '\n'
        << stream::is_type_of(v) << '\n'
        << stream::is_type_of(l) << '\n'
        << head(v) << '\n'
        << head(l) << '\n'
        << head(tail(v)) << '\n'
        << head(tail(l)) << '\n'
//        << stream::is_type_of(a) << '\n'
        ;
    return 0;
}
