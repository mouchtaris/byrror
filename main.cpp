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
    // Iterator stream
    //
    template <typename Iter> using Iters = std::tuple<Iter, Iter>;
    template <typename I> auto __current(Iters<I> iters)
        { return get<0>(iters); }
    template <typename I> auto __end(Iters<I> iters)
        { return get<1>(iters); }
    template <typename I> bool __is_end(Iters<I> iters)
        { return __current(iters) == __end(iters); }
    //
    template <typename I> auto head(Iters<I> iters)
        { return __is_end(iters) ? std::nullopt : std::make_optional(*__current(iters)); }
    template <typename I> auto tail(Iters<I> iters)
        { return Iters<I> { next(__current(iters)), __end(iters) }; }

    //
    // Container streams
    //
    template <typename Container> auto __make_iters(Container const& c)
        -> Iters<typename Container::const_iterator>
        { return { begin(c), end(c) }; }

#   define DEFINE_CONTAINER_STREAM(CONTAINER)                       \
    template <typename T> auto head(CONTAINER <T> const& c)         \
        { return head(__make_iters(c)); }                           \
    template <typename T> auto tail(CONTAINER <T> const& c)         \
        { return tail(__make_iters(c)); }
    DEFINE_CONTAINER_STREAM(std::vector);
    DEFINE_CONTAINER_STREAM(std::list);


    //
    // Stream concept
    //
    template <typename T> struct __ConceptChecks {
        using __head_t = decltype(head(std::declval<T>()));
        using head = std::is_same<__head_t, __head_t>;

        using __tail_t = decltype(tail(std::declval<T>()));
        using tail = std::is_same<__tail_t, __tail_t>;

        using is = head;
    };

    template <typename T> struct __ConceptAssertions {
        using Check = __ConceptChecks<T>;
        CONCEPT_CHECK(head);
    };

    template <typename T> extern constexpr bool is = __ConceptChecks<T>::is::value;
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
template <typename T>
struct StreamIter {

};
template <typename T>
auto begin(T const& stream)
    -> std::enable_if<stream::is<T>, 

int main(int, char**) {
    using stream::head,
          stream::tail;
    std::vector<int> v = { 1, 2, 3 };
    std::list<int> l = { 4, 5, 6 };
    std::cout
        << pig::pig<const unsigned long long> << '\n'
        << stream::is_type_of(v) << '\n'
        << stream::is_type_of(l) << '\n'
        << head(v) << '\n'
        << head(l) << '\n'
        << head(tail(v)) << '\n'
        << head(tail(l)) << '\n'
        ;
    return 0;
}
