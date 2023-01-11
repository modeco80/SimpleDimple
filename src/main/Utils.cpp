//
// SimpleDimple
//
// (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: GPL-3.0-or-later
//


#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS     // this damn compiler is going to give me a migrane the size of the moon
#endif

#include <algorithm>
#include <Utils.hpp>

namespace sd {

	std::string FormatUnit(std::uint64_t bytes) {
		char buf[1024];
		constexpr auto unit = 1024;

		std::size_t exp {};
		std::size_t div = unit;

		if(bytes < unit) {
			sprintf(buf, "%zu B", bytes);
			return buf;
		} else {
			for(std::uint64_t i = bytes / unit; i >= unit; i /= unit) {
				// Break out if we're gonna set the exponent too high
				if((exp + 1) > 2)
					break;

				div *= unit;

				exp++;
			}
		}

#define CHECKED_LIT(literal, expression) (literal)[std::clamp(expression, std::size_t(0), sizeof(literal) - 1)]
		sprintf(buf, "%0.2f %cB", float(bytes) / float(div), CHECKED_LIT("kMG", exp));
#undef CHECKED_LIT
		return buf;
	}

} // namespace sd