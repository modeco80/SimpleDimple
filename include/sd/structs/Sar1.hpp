//
// SimpleDimple
//
// (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once
#include <sd/structs/ImHexAdapter.hpp>
#include <sd/util/FourCC.hpp>
#include <variant>

namespace sd::structs {

	enum class Sar1Version : u32 {
		Ver258 = 258,
		Ver528 = 528
	};



	// SAR1 (Simple Archive version 1) header.
	struct Sar1Header {

		constexpr static auto VALID_MAGIC = util::FourCC<"SAR1", std::endian::big>();

		u32 magic; // '1RAS'

		// full file size
		// (aligned just like the file)
		u32 fileSize;

		Sar1Version version;

		u32 nrFiles;
		u32 tocOffset;

		// Note that this is the aligned end of the
		// TOC block.
		//
		// You can read individual Sar1TocEntry structures just fine
		// for a simple reader.
		u32 tocEndOffset;

		// padding to 0x20 size ?
		u64 padding;

		// some debug path.
		char debugPath[128];

		[[nodiscard]] constexpr bool Validate() const {
			using enum Sar1Version;
			return
				magic == VALID_MAGIC &&                     // valid magic... and
				(version == Ver258 || version == Ver528);   // version fits discovered versions

		}
	};

	template<size_t NameLen>
	struct Sar1TocEntry_Common {
		u32 startOffset;
		u32 size;

		// Used for faster searching of the archive,
		// hashed with mm::mtl::HashStrCrc(), which
		// uses a relatively standard CRC32 table.
		u32 nameCRC;

		char fileName[NameLen];
	};

	struct Sar1TocEntry_Ver258 : Sar1TocEntry_Common<52> {
		// 258 has 0x10 padding data with nothing seemingly in it
	};

	struct Sar1TocEntry_Ver528 : Sar1TocEntry_Common<36> {
		float unk1;
		float unk2; // usually 100?
		float unk3; // i have no idea

		u32 fileIndex;

		u32 unkThing;
		u32 unkOtherThing; // sometimes 0x64?
		u32 unkRest[6];
	};


	using Sar1TocEntry = std::variant<
		Sar1TocEntry_Ver258,
		Sar1TocEntry_Ver528
	>;

}