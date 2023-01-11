#
# SimpleDimple
#
# (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

cmake_minimum_required(VERSION 3.10)

# Prohibit in-source tree builds.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "In-source builds are strictly prohibited.")
endif()

include(cmake/Policies.cmake)

project(SimpleDimple
        VERSION 1.0.0
        LANGUAGES C CXX
        DESCRIPTION "Multi-tool for Monolith/Framework SAR1 archives"
        )

include(FetchContent)

# declare dependencies
FetchContent_Declare(indicators
        GIT_REPOSITORY https://github.com/p-ranav/indicators.git
        )

FetchContent_Declare(argparse
        GIT_REPOSITORY https://github.com/p-ranav/argparse.git
        )
		
FetchContent_MakeAvailable(indicators argparse)

add_subdirectory(src/libsd)
add_subdirectory(src/main)
