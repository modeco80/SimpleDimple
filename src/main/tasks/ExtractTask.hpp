//
// SimpleDimple
//
// (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <CommonDefs.hpp>

namespace sd::tasks {

	struct ExtractTask {
		struct Arguments {
			fs::path inputPath;
			fs::path outputDirectory;
			bool verbose;
		};

		int Run(Arguments&& args);
	};

} // namespace sd::tasks
