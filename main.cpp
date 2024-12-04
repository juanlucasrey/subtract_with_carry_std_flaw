#include "subtract_with_carry_engine.hpp"

#include <cassert>
#include <cstdint>
#include <random>

namespace detail {
template <std::size_t N, class T> inline constexpr auto pow(T base) -> T {
  if constexpr (N == 1) {
    return base;
  } else if constexpr (N % 2 == 0) {
    T power = pow<N / 2>(base);
    return power * power;

  } else {
    T power = pow<N / 2>(base);
    return base * power * power;
  }
};
} // namespace detail

template <class RNG>
constexpr auto period(RNG const & /* rng */) -> unsigned long long {
  constexpr auto w = RNG::word_size;
  constexpr auto r = RNG::long_lag;
  constexpr auto s = RNG::short_lag;
  return detail::pow<r>(w) - detail::pow<s>(w);
}

int main() {
  int result = 0;

  {
    std::subtract_with_carry_engine<std::uint_fast32_t, 16, 2, 4> rng1;
    std::subtract_with_carry_engine<std::uint_fast32_t, 16, 2, 4> rng2;

    constexpr unsigned long long full_cycle = period(rng1); // 65280

    rng2.discard(full_cycle);

    // this should be equal!!
    assert(rng1 != rng2);

    // first simulation is equal
    assert(rng1() == rng2());

    // then state is the same
    assert(rng1 == rng2);
  }

  {
    stdfix::subtract_with_carry_engine<std::uint_fast32_t, 16, 2, 4> rng1;
    stdfix::subtract_with_carry_engine<std::uint_fast32_t, 16, 2, 4> rng2;
    constexpr unsigned long long full_cycle = period(rng1); // 65280
    rng2.discard(full_cycle);
    assert(rng1 == rng2);
  }

  return result;
}
