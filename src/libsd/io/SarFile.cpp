//
// SimpleDimple
//
// (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <sd/io/SarFile.hpp>

namespace sd::io {

	const SarFile::DataType& SarFile::GetData() const {
		return data;
	}

	void SarFile::SetData(SarFile::DataType&& newData) {
		data = std::move(newData);
	}

} // namespace sd::io