#pragma once

#include "pig.h"
#include "stream.h"

namespace iter_stream {
    using namespace stream;

    template <typename I> struct
    IterPack {
        I begin, end;
    };

    template <typename I> auto
    make_iter_pack(I begin, I end)
        -> IterPack<I>
        { return { begin, end }; }

}

namespace stream {

    template <typename I> struct
    StreamOps<iter_stream::IterPack<I>> {
        using Element = std::add_const_t<typename I::value_type>;
        using Self = iter_stream::IterPack<I>;
        using This = StreamOps<Self>;

        const Self self;

        const bool __is_at_the_end =
            self.begin == self.end;
        auto __just_head() const -> head_t<Self>
            { return *self.begin; }
        auto __just_tail() const -> Self
            { return { next(self.begin), self.end }; }

        auto head() const -> head_t<Self>
            { return __is_at_the_end ? std::nullopt : __just_head(); }
        auto tail() const
            -> Self
            { return __is_at_the_end ? self : __just_tail(); }
    };
}


PIG_WRAP(iter_stream::IterPack);
