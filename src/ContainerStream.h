#pragma once

#include "Stream.h"

#include <deque>
#include <list>
#include <set>
#include <vector>

#include <optional>

template <typename MDT, typename _Container>
struct ContainerStream {
    using Container = _Container;
    using Iter = typename Container::const_iterator;

    using Self = ContainerStream<MDT, Container>;

    Iter current;
    Iter last;

    using Element = std::decay_t<decltype(*current)>;

    std::optional<Element> head() const;
    MDT tail() const;
};

#define CONTAINER_STREAM_DEFINITION(container) \
    template <typename T>                       \
    struct Stream< container <T> > :            \
        public ContainerStream<                 \
            Stream< container <T> >,            \
            container <T>                       \
        >                                       \
    {                                           \
    }
CONTAINER_STREAM_DEFINITION(std::deque);
CONTAINER_STREAM_DEFINITION(std::list);
CONTAINER_STREAM_DEFINITION(std::set);
CONTAINER_STREAM_DEFINITION(std::vector);
