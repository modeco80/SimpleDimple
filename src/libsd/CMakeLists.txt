#
# SimpleDimple
#
# (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

add_library(sd_libsd
        # Implementation details
        io/StreamUtils.cpp

        # Pak IO
        io/SarFile.cpp
        io/SarReader.cpp

        )

target_include_directories(sd_libsd PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_features(sd_libsd PUBLIC cxx_std_20)

add_library(sd::libsd ALIAS sd_libsd)