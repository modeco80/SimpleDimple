//
// SimpleDimple
//
// (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once
#include <cstdint>

namespace sd::util {

	/**
	 * A compile-time string. Usable as a C++20 cNTTP.
	 */
	template <std::size_t N>
	struct FixedString {
		char buf[N + 1] {};

		constexpr FixedString(const char* s) { // NOLINT
			for(unsigned i = 0; i != N; ++i)
				buf[i] = s[i];
		}

		constexpr operator const char*() const { // NOLINT
			return buf;
		}

		[[nodiscard]] constexpr std::size_t Length() const {
			return N;
		}
	};

	template <std::size_t N>
	FixedString(char const (&)[N]) -> FixedString<N - 1>;

} // namespace sd::util
