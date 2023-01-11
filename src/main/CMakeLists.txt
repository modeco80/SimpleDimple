#
# SimpleDimple
#
# (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

add_executable(simpledimple
        main.cpp

        Utils.cpp

        # Tasks
        tasks/InfoTask.cpp
        tasks/ExtractTask.cpp
        )

target_link_libraries(simpledimple PUBLIC
        sd::libsd
        argparse::argparse
        indicators::indicators
        )

configure_file(SdConfig.hpp.in
        ${CMAKE_CURRENT_BINARY_DIR}/SdConfig.hpp
        )

target_include_directories(simpledimple PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(simpledimple PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})