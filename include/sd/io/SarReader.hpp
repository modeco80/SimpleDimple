//
// SimpleDimple
//
// (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <sd/io/SarFile.hpp>
#include <iosfwd>
#include <string>
#include <unordered_map>

namespace sd::io {

	struct SarReader {
		using MapType = std::unordered_map<std::string, SarFile>;

		explicit SarReader(std::istream& is);

		void ReadData();

		void ReadFiles();

		/**
		 * Read in a specific file.
		 */
		void ReadFile(const std::string& file);

		bool Invalid() const {
			return invalid;
		}

		MapType& GetFiles();
		const MapType& GetFiles() const;

		// implement in cpp later, lazy and just wanna get this out :vvv
		const structs::Sar1Header& GetHeader() const { return header; }

	   private:
		std::istream& stream;
		bool invalid { false };

		structs::Sar1Header header {};

		MapType files;
	};

} // namespace europa::io
