//
// SimpleDimple
//
// (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <cstdint>
#include <vector>

#include <sd/structs/Sar1.hpp>

namespace sd::io {

	struct SarReader;

	struct SarFile {
		using DataType = std::vector<std::uint8_t>;

		/**
		 * Get the file data.
		 */
		[[nodiscard]] const DataType& GetData() const;


		void SetData(DataType&& data);


		const structs::Sar1TocEntry& GetTocEntry() const {
			return tocEntry;
		}

		structs::Sar1TocEntry& GetTocEntry() {
			return tocEntry;
		}

	   private:
		friend SarReader;

		std::vector<std::uint8_t> data;

		structs::Sar1TocEntry tocEntry;
	};

} // namespace sd::io
