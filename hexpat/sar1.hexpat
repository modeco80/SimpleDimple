//
// SimpleDimple
//
// (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#include <std/io.pat>
#include <std/mem.pat>
#pragma endian little

// SAR1 (Simple Archive version 1) header.
struct Sar1Header {
	u32 magic [[name("Magic")]]; // '1RAS'
	
	// full file size
	// (aligned just like the file)
	u32 fileSize [[name("Archive Size")]];
	
	// arc::CArcData::find() looks at this?
	u32 maybeVersion [[name("Version")]];
	
	u32 nrFiles [[name("File Count")]];
	u32 tocOffset [[name("TOC Offset")]];
	
	// Note that this is the aligned end of the 
	// TOC block.
	//
	// You can read individual Sar1TocEntry structures just fine
	// for a simple reader.
	u32 tocEndOffset [[name("TOC End Offset")]]; 
	
	// padding to 0x20 size ?
	padding[8];
	
	// some debug path.
	char debugName[128] [[name("Archive Dest Debug Path")]];
} [[static]];

// SAR1 TOC entry. Size dependent on archive version.
struct Sar1TocEntry {
	u32 startOffset [[name("Start Offset")]];
	u32 size [[name("Size")]];
	
	// Used for faster searching of the archive,
	// hashed with mm::mtl::HashStrCrc(), which
	// uses a relatively standard CRC32 table.
	u32 nameCRC [[name("Filename CRC32")]];
	
	// "New" fields?
	if(parent.parent.header.maybeVersion == 0x210) {
    	char name[36] [[name("Filename")]];
    	
    	float unk1;
    	float unk2; // usually 100?
    	float unk3; // i have no idea
    	
    	u32 fileIndex  [[name("File Index")]];
    	
    	u32 unkThing;
    	u32 unkOtherThing; // sometimes 0x64?
    	u32 unkRest[6];
	} else {
	    // "old" fields
	    char name[52] [[name("Filename")]];
	}
};

// SAR1 file. Seperate from Sar1TocEntry for cleanliness.
struct Sar1File : Sar1TocEntry {
	u8 data[size] @ startOffset;
};

struct Sar1 {
	Sar1Header header;
	Sar1File files[header.nrFiles];
}; Sar1 sar1 @ 0x0;
