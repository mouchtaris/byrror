#pragma once

#include "ContainerStream.h"

#include <iterator>
#include <optional>

using std::begin,
      std::end;

template <typename MDT, typename _Container>
auto ContainerStream<MDT, _Container>::head() const
    -> std::optional<Element>
{
    if (current == last)
        return std::nullopt;
    return std::make_optional(*current);
}

template <typename MDT, typename _Container>
auto ContainerStream<MDT, _Container>::tail() const
    -> MDT
{
    return {
        Self {
            std::next(current, 1),
            last,
        },
    };
}

template <typename T>
Stream<std::vector<T>> stream(std::vector<T> const& self) {
    return
        {
            {
                begin(self),
                end(self),
            },
        };
}
