#pragma once

namespace nstd {

    template <typename ...Ts>
    struct OverloadSet : Ts... {
        using Ts::operator()...;
    };

    template <typename ...Ts>
    OverloadSet(Ts...) -> OverloadSet<Ts...>;

}
