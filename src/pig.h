#pragma once

#ifdef ENABLE_PIG
#   include <string>
#endif

namespace pig {

#   ifdef ENABLE_PIG

    template <typename T> struct Pig { std::string name = "  xxx  "; };
    template <typename T> std::string make_pig() { return std::move(Pig<T> { }.name); }
    template <typename T> inline std::string pig = make_pig<T>();

    template <typename T> std::string pig_copy(T const&) { return pig<T>; }
    template <typename T> std::string pig_pod(T) { return pig<T>; }
    template <typename T> std::string pig_ref(T&) { return pig<T>; }
    template <typename T> std::string pig_move(T&&) { return pig<T>; }

    template <typename T> struct Pig<T&> { std::string name = make_pig<T>() + '&'; };
    template <typename T> struct Pig<T&&> { std::string name = make_pig<T>() + "&&"; };
    template <typename T> struct Pig<T const> { std::string name = make_pig<T>() + " const"; };

    template <typename T> struct PigWrap {
        std::string wrap;
        std::string name = wrap + '<' + make_pig<T>() + '>';
    };

#   define PIG_STD(TYPE)                                                        \
        template <> struct Pig<TYPE> { char const* name = #TYPE; }
    PIG_STD(char);
    PIG_STD(unsigned char);
    PIG_STD(short);
    PIG_STD(unsigned short);
    PIG_STD(int);
    PIG_STD(unsigned int);
    PIG_STD(long);
    PIG_STD(unsigned long);
    PIG_STD(long long);
    PIG_STD(unsigned long long);

#   define PIG_WRAP(WRAP)                                                   \
        template <typename T> struct pig::Pig<WRAP<T>>: public PigWrap<T> { \
            Pig():                                                          \
                PigWrap<T> { #WRAP }                                        \
                { }                                                         \
        }

#   else // ENABLE_PIG
#       define PIG_WRAP(WRAP)
#   endif // ENABLE_PIG
}

#ifdef PIG_STDLIB
#   include <optional>
    PIG_WRAP(std::optional);
#   include <type_traits>
    PIG_WRAP(std::reference_wrapper);
#   include <vector>
    PIG_WRAP(std::vector);
#   include <deque>
    PIG_WRAP(std::deque);
#   include <list>
    PIG_WRAP(std::list);
#endif
