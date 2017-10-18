#pragma once

#include <Stream.h>

#include <vector>

template <typename _Container>
struct ContainerStream {
    using Container = _Container;
    using Iter = typename Container::const_iterator;

    using Self = ContainerStream<Container>;

    Iter current;
    Iter const last;

    using Element = decltype(*current);

    std::optional<Element> head() const;
    Self tail() const;
};

template <typename T>
struct Stream<std::vector<T>>
    : public ContainerStream<std::vector<T>>
{
};
