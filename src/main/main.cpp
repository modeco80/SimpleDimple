//
// SimpleDimple
//
// (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <argparse/argparse.hpp>
#include <SdConfig.hpp>
#include <tasks/ExtractTask.hpp>
#include <tasks/InfoTask.hpp>

int main(int argc, char** argv) {
	argparse::ArgumentParser parser("simpledimple", SD_VERSION_STR);
	parser.add_description("SimpleDimple (SAR1 Multi-Tool) v" SD_VERSION_STR);

	argparse::ArgumentParser infoParser("info", SD_VERSION_STR, argparse::default_arguments::help);
	infoParser.add_description("Print information about a Sar1 file.");
	infoParser.add_argument("input")
	.help("Input archive")
	.metavar("ARCHIVE");

	infoParser.add_argument("--verbose")
	.help("Increase information output verbosity (print a list of files).")
	.default_value(false)
	.implicit_value(true);

	argparse::ArgumentParser extractParser("extract", SD_VERSION_STR, argparse::default_arguments::help);
	extractParser.add_description("Extract a Sar1 file.");
	extractParser.add_argument("-d", "--directory")
	.default_value("")
	.metavar("DIRECTORY")
	.help("Directory to extract to.");
	extractParser.add_argument("input")
	.help("Input archive")
	.metavar("ARCHIVE");

	extractParser.add_argument("--verbose")
	.help("Increase extraction output verbosity")
	.default_value(false)
	.implicit_value(true);

	parser.add_subparser(infoParser);
	parser.add_subparser(extractParser);

	try {
		parser.parse_args(argc, argv);
	} catch(std::runtime_error& error) {
		std::cout << error.what() << '\n'
				  << parser;
		return 1;
	}

	// Run the given task

	if(parser.is_subcommand_used("extract")) {
		sd::tasks::ExtractTask task;
		sd::tasks::ExtractTask::Arguments args;

		args.verbose = extractParser.get<bool>("--verbose");
		args.inputPath = sd::fs::path(extractParser.get("input"));

		if(extractParser.is_used("--directory")) {
			args.outputDirectory = sd::fs::path(extractParser.get("--directory"));
		} else {
			// Default to the basename appended to current path
			// as a "relatively sane" default path to extract to.
			// Should be okay.
			args.outputDirectory = sd::fs::current_path() / args.inputPath.stem();
		}

		std::cout << "Input Sar1: " << args.inputPath << '\n';
		std::cout << "Output Directory: " << args.outputDirectory << '\n';

		return task.Run(std::move(args));
	}

	if(parser.is_subcommand_used("info")) {
		sd::tasks::InfoTask task;
		sd::tasks::InfoTask::Arguments args;

		args.verbose = infoParser.get<bool>("--verbose");
		args.inputPath = sd::fs::path(infoParser.get("input"));

		return task.Run(std::move(args));
	}

	return 0;
}