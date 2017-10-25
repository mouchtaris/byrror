#pragma once

#include "pig.h"
#include "iter_stream.h"

#include <vector>

namespace stream {

    template <typename T> struct
    StreamOf<std::vector<T>> {
        using Container = std::vector<T>;
        using Iter = typename Container::const_iterator;
        using IP = iter_stream::IterPack<Iter>;
        using type = StreamOps<IP>; // IterStream
    };

    template <typename T> struct
    StreamOpsConstructorOf<std::vector<T>> {

        struct ContainerStreamConstructor {
            auto operator () (std::vector<T> const& self) const
                -> stream_of_t<std::vector<T>>
                { return { { cbegin(self), cend(self) } }; }
        };

        using type = ContainerStreamConstructor;

    };


}
