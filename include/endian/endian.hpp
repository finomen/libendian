#pragma once

#include <cstdint>
#include <bit>
#include <type_traits>

#ifndef __cpp_lib_byteswap
#include <ranges>
#include <algorithm>
#endif

namespace endian {

    static_assert(std::endian::big != std::endian::little);
    static_assert(std::endian::big == std::endian::native || std::endian::little == std::endian::native);

    namespace detail {
        template<typename T>
        concept Integral = std::is_integral_v<T>;
#ifdef __cpp_lib_byteswap
        using std::byteswap;
#else
        template<Integral T>
        constexpr T byteswap(T value) noexcept{
            if constexpr (std::is_signed_v<T>) {
                return std::bit_cast<T>(byteswap(std::bit_cast<std::make_unsigned_t<T>>(value)));
            }
            auto representation = std::bit_cast<std::array<std::byte, sizeof(T)>>(value);
            std::ranges::reverse(representation);
            return std::bit_cast<T>(representation);
        }
#endif

        template<Integral T>
        class SwapEndian final {
        public:
            constexpr SwapEndian(T value = {}) noexcept  : mValue(byteswap(value)) {
                static_assert(sizeof(SwapEndian<T>) == sizeof(T));
            }

            constexpr SwapEndian(const SwapEndian&) noexcept = default;
            constexpr SwapEndian(SwapEndian&&) noexcept  = default;
            constexpr SwapEndian &operator=(const SwapEndian&)  noexcept = default;
            constexpr SwapEndian &operator=(SwapEndian&&) noexcept  = default;

            constexpr operator T() const noexcept {
                return byteswap(mValue);
            }

        private:
            T mValue;
        };

        template<typename T, std::endian E>
        using FixedEndian = std::conditional_t<E == std::endian::native, T, SwapEndian<T>>;
    }

    using int16_be = detail::FixedEndian<int16_t, std::endian::big>;
    using int32_be = detail::FixedEndian<int32_t, std::endian::big>;
    using int64_be = detail::FixedEndian<int64_t, std::endian::big>;
    using uint16_be = detail::FixedEndian<uint16_t, std::endian::big>;
    using uint32_be = detail::FixedEndian<uint32_t, std::endian::big>;
    using uint64_be = detail::FixedEndian<uint64_t, std::endian::big>;

    using int16_le = detail::FixedEndian<int16_t, std::endian::little>;
    using int32_le = detail::FixedEndian<int32_t, std::endian::little>;
    using int64_le = detail::FixedEndian<int64_t, std::endian::little>;
    using uint16_le = detail::FixedEndian<uint16_t, std::endian::little>;
    using uint32_le = detail::FixedEndian<uint32_t, std::endian::little>;
    using uint64_le = detail::FixedEndian<uint64_t, std::endian::little>;
}