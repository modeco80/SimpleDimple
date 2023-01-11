//
// SimpleDimple
//
// (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sd/io/SarReader.hpp>
#include <tasks/InfoTask.hpp>
#include <Utils.hpp>

namespace sd::tasks {

	int InfoTask::Run(Arguments&& args) {
		std::ifstream ifs(args.inputPath.string(), std::ifstream::binary);

		if(!ifs) {
			std::cout << "Error: Could not open file " << args.inputPath << ".\n";
			return 1;
		}

		sd::io::SarReader reader(ifs);

		reader.ReadData();

		if(reader.Invalid()) {
			std::cout << "Error: Invalid Sar1 file " << args.inputPath << ".\n";
			return 1;
		}

		std::string version = "Version 258";

		if(reader.GetHeader().version == structs::Sar1Version::Ver528)
			version = "Version 528";

		std::cout << "Archive " << args.inputPath << ":\n";
		std::cout << "    Version: " << version << '\n';
		std::cout << "    Size: " << FormatUnit(reader.GetHeader().fileSize) << '\n';
		std::cout << "    File Count: " << reader.GetHeader().nrFiles << " files\n";

		// Print a detailed file list if verbose.
		if(args.verbose) {
			for(auto& [filename, file] : reader.GetFiles()) {
				// clang-format off

				std::visit([&](auto& value) {
					std::cout << "File \"" << filename << "\":\n";
					std::cout << "    Size: " << FormatUnit(value.size) << '\n';
				},  file.GetTocEntry());

				// clang-format on
			}
		}
		return 0;
	}

} // namespace sd::tasks