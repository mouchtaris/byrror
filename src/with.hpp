#pragma once
#include <utility>

template <typename ...Ts>
struct with {

    template <
        template <typename ...> class T,
        typename ...CArgs >
    static inline T<Ts...> make(CArgs&&... args) {
        return { std::forward<CArgs>(args)... };
    }

};
