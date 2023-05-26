#pragma once

#include <ranges>
#include <utility>
#include <algorithm>
#include <iterator>

namespace nstd::ranges {

    namespace detail {
        
        template <typename C, typename R>
        concept reservable = std::ranges::sized_range<R> && requires (C &c, R &&rng) {
            { c.capacity() } -> std::same_as<std::ranges::range_size_t<C>>;
            { c.reserve(std::ranges::range_size_t<R>(0)) };
        };

        template <typename C>
        concept insertable = requires(C c) {
            std::inserter(c, std::ranges::end(c));
        };
    
        template <typename>
        constexpr inline bool always_false = false;

        template <typename C, typename R>
        concept matroshkable = 
            std::ranges::input_range<C> && 
            std::ranges::input_range<R> &&
            std::ranges::input_range<std::ranges::range_value_t<C>> &&
            std::ranges::input_range<std::ranges::range_value_t<R>> &&
            ! std::ranges::view<std::ranges::range_value_t<C>> &&
            std::indirectly_copyable<
                std::ranges::iterator_t<std::ranges::range_value_t<R>>,
                std::ranges::iterator_t<std::ranges::range_value_t<C>>
            > &&
            detail::insertable<C>;

        template <std::ranges::input_range R>
        struct fake_input_iterator {
            using iterator_category = std::input_iterator_tag;
            using value_type = std::ranges::range_value_t<R>;
            using difference_type = std::ranges::range_difference_t<R>;
            using pointer = std::ranges::range_value_t<R>*;
            using reference = std::ranges::range_reference_t<R>;
        
            reference operator*();
            fake_input_iterator &operator++();
            fake_input_iterator operator++(int);
            fake_input_iterator() = default;
            friend bool operator==(fake_input_iterator, fake_input_iterator) { return false; };
        };

        template <template <typename...> typename C, std::ranges::input_range R, typename ...Args>
        struct ctad_container {
            template <typename V = R>
            static auto deduce(int) -> decltype(C(std::declval<V>(), std::declval<Args>()...));
        
            template <typename Iter = fake_input_iterator<R>>
            static auto deduce(...) -> decltype(C(std::declval<Iter>(), std::declval<Iter>(), std::declval<Args>()...));
        
            using type = decltype(deduce(0));
        };

    }

    template <std::ranges::input_range C, std::ranges::input_range R, typename ...Args>
    requires (! std::ranges::view<C>)
    constexpr C to(R &&r, Args &&...args) {
        if constexpr (std::constructible_from<C, R, Args...>) {
            return C(std::forward<R>(r), std::forward<Args>(args)...);
        }
        else if constexpr (
            std::constructible_from<C, Args...> && 
            std::indirectly_copyable<std::ranges::iterator_t<R>, std::ranges::iterator_t<C>> &&
            detail::insertable<C>
        ) {
            C c(std::forward<Args>(args)...);

            if constexpr (std::ranges::sized_range<R> && detail::reservable<C, R>) {
                c.reserve(std::ranges::size(r));
            }

            std::ranges::copy(r, std::inserter(c, std::end(c)));

            return c;
        }
        else if constexpr (detail::matroshkable<C, R>) {
            C c(std::forward<Args>(args)...);

            if constexpr (std::ranges::sized_range<R> && detail::reservable<C, R>) {
                c.reserve(std::ranges::size(r));
            }

            auto v = r | std::views::transform([] (auto &&element) {
                return nstd::ranges::to<std::ranges::range_value_t<C>>(element);
            });

            std::ranges::copy(v, std::inserter(c, std::end(c)));

            return c;
        }
        else if constexpr (std::constructible_from<C, 
            std::ranges::iterator_t<R>, 
            std::ranges::sentinel_t<R>, 
            Args... >) {
            return C(std::ranges::begin(r), std::ranges::end(r), std::forward<Args>(args)...);
        }
        else {
            static_assert(detail::always_false<C>, "C is not constructible from R");
        }
    }

    template <
        template <typename...> typename C, 
        std::ranges::input_range R, 
        typename ...Args, 
        typename ContainerType = typename detail::ctad_container<C, R, Args...>::type
    >
    constexpr auto to(R &&r, Args &&...args) -> ContainerType {
        return nstd::ranges::to<ContainerType>(std::forward<R>(r), std::forward<Args>(args)...);
    }

    namespace detail {
        template <std::ranges::input_range C, typename ...Args>
        struct closure_range {
            template <typename ...A>
            closure_range(A &&...as) : args_(std::forward<A>(as)...) {}

            std::tuple<Args...> args_;
        };

        template <std::ranges::input_range R, std::ranges::input_range C, typename ...Args>
        auto constexpr operator|(R &&r, closure_range<C, Args...> &&c) {
            return std::apply(
                [&r] (auto &&...inner_args) {
                    return nstd::ranges::to<C>(
                        std::forward<R>(r), 
                        std::forward<decltype(inner_args)>(inner_args)...
                    );
                }, std::move(c.args_)
            );
        }

        template <template <typename...> typename C, typename ...Args>
        struct closure_ctad{
            template <typename ...A>
            closure_ctad(A &&...as) : args_(std::forward<A>(as)...) {}

            std::tuple<Args...> args_;
        };

        template <std::ranges::input_range R, template <typename...> typename C, typename ...Args>
        auto constexpr operator|(R &&r, closure_ctad<C, Args...> &&c) {
            return std::apply(
                [&r] (auto &&...) {
                    return nstd::ranges::to<C>(std::forward<R>(r));
                }, std::move(c.args_)
            );
        }
    }

    template <template <typename...> typename C, typename ...Args>
    constexpr auto to(Args &&...args) {
        return detail::closure_ctad<C, Args...>{ std::forward<Args>(args)... };
    }

    template <std::ranges::input_range C, typename ...Args>
    constexpr auto to(Args &&...args) {
        return detail::closure_range<C, Args...>{ std::forward<Args>(args)... };
    }

    // template <std::ranges::input_range R>
    // constexpr auto enumerate(R &&r) {
    //     return std::views::zip(
    //         std::views::iota(size_t{ 0 }),
    //         r
    //     );
    // }

}
