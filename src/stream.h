#pragma once

#include "pig.h"

#include <optional>
#include <type_traits>

namespace stream {

    template <typename T> struct
    StreamOps;

    template <typename T> struct
    StreamOf {
        using type = StreamOps<std::decay_t<T>>;
    };

    template <typename T> using
    stream_of_t =
        typename StreamOf<std::decay_t<T>>::type;

    template <typename T> struct
    StreamOpsConstructor {
        stream_of_t<T> operator () (T&& self) const
            { return { std::forward<T>(self) }; }
    };

    template <typename T> struct
    StreamOpsConstructorOf {
        using type = StreamOpsConstructor<std::decay_t<T>>;
    };

    template <typename T> using
    constructor_of_t =
        typename StreamOpsConstructorOf<std::decay_t<T>>::type;

    template <typename T> auto
    constructor()
        -> constructor_of_t<T>
        { return { }; }

    template <typename T> auto
    ops(T&& self)
        -> stream_of_t<T>
        { return constructor<T>()(std::forward<T>(self)); }

    template <typename T> using
    element_t =
        typename stream_of_t<std::decay_t<T>>::Element;

    template <typename T> using
    head_t =
        std::optional<std::reference_wrapper<element_t<T>>>;

    template <typename T> auto
    head(T&& self)
        -> head_t<T>
        { return ops(std::forward<T>(self)).head(); }

    template <typename T> auto
        tail(T&& self)
        { return ops(std::forward<T>(self)).tail(); }

}

PIG_WRAP(stream::StreamOps);
PIG_WRAP(stream::StreamOf);
PIG_WRAP(stream::StreamOpsConstructor);
PIG_WRAP(stream::StreamOpsConstructorOf);
