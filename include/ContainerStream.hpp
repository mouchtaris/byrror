#pragma once

#include <ContainerStream.h>

#include <iterator>
#include <optional>

using std::begin,
      std::end;

template <typename _Container>
auto ContainerStream<_Container>::head() const
    -> std::optional<Element>
{
    if (current == end)
        std::nullopt;
    else
        
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
