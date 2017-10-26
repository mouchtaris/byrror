#pragma once

#include "pig.h"
#include "iter_stream.h"

#include <vector>
#include <list>
#include <deque>
#include <set>

namespace stream {

#   define CONTAINER_STREAM_DEFINITION(CONTAINER)               \
        template <typename T> struct                            \
        StreamOf<CONTAINER<T>> {                                \
            using Container = CONTAINER<T>;                     \
            using Iter = typename Container::const_iterator;    \
            using IP = iter_stream::IterPack<Iter>;             \
            using type = StreamOps<IP>;                         \
        };                                                      \
                                                                \
        template <typename T> struct                            \
        StreamOpsConstructorOf<CONTAINER<T>> {                  \
                                                                \
            struct ContainerStreamConstructor {                 \
                auto operator () (CONTAINER<T> const& self) const \
                    -> stream_of_t<CONTAINER<T>>                \
                    { return { { cbegin(self), cend(self) } }; }\
            };                                                  \
                                                                \
            using type = ContainerStreamConstructor;            \
                                                                \
        }                                                       \

    CONTAINER_STREAM_DEFINITION(std::vector);
    CONTAINER_STREAM_DEFINITION(std::list);
    CONTAINER_STREAM_DEFINITION(std::deque);
    CONTAINER_STREAM_DEFINITION(std::set);

}
