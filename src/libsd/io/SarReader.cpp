//
// SimpleDimple
//
// (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#include <cstring>
#include <sd/io/SarReader.hpp>

#include "StreamUtils.hpp"

namespace sd::io {

	SarReader::SarReader(std::istream& is)
		: stream(is) {
	}

	void SarReader::ReadData() {
		header = impl::ReadStreamType<structs::Sar1Header>(stream);

		if(!header.Validate()) {
			invalid = true;
			return;
		}

		for(u32 i = 0; i < header.nrFiles; ++i) {
			using enum structs::Sar1Version;
			structs::Sar1TocEntry tocEnt;

			// clang-format off

			switch(header.version) {
				case Ver258: tocEnt = impl::ReadStreamType<structs::Sar1TocEntry_Ver258>(stream); break;
				case Ver528: tocEnt = impl::ReadStreamType<structs::Sar1TocEntry_Ver528>(stream); break;

				// Stop trying to fuzz me ;w;
				default: invalid = true; return;
			}

			std::visit([&](auto& value) {
				files[value.fileName].GetTocEntry() = tocEnt;
			}, tocEnt);

			// clang-format on
		}
	}

	void SarReader::ReadFiles() {
		for(auto& [filename, file] : files)
			ReadFile(filename);
	}

	void SarReader::ReadFile(const std::string& file) {
		auto& fileObject = files[file];

		// This file was previously read, we don't mess with it.
		if(!fileObject.data.empty())
			return;

		// clang-format off

		// nvm no it wasn't ;w;
		std::visit([&](auto& value) {
			fileObject.data.resize(value.size);
			stream.seekg(value.startOffset, std::istream::beg);
			stream.read(reinterpret_cast<char*>(&fileObject.data[0]), value.size);
		}, fileObject.GetTocEntry());

		// clang-format on
	}

	SarReader::MapType& SarReader::GetFiles() {
		return files;
	}

	const SarReader::MapType& SarReader::GetFiles() const {
		return files;
	}

} // namespace sd::io