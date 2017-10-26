#pragma once

#include "pig.h"
#include "iter_stream.h"

#include <vector>
#include <list>
#include <deque>
#include <set>

namespace container_stream  {

    struct
    ContainerStreamConstructor {

        template <typename Container>
        auto operator () (Container&& self) const
            -> stream::stream_of_t<Container>
            { return { { cbegin(self), cend(self) } }; }

    };

}

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
            using type = container_stream::ContainerStreamConstructor; \
        }                                                       \

    CONTAINER_STREAM_DEFINITION(std::vector);
    CONTAINER_STREAM_DEFINITION(std::list);
    CONTAINER_STREAM_DEFINITION(std::deque);
    CONTAINER_STREAM_DEFINITION(std::set);

}
