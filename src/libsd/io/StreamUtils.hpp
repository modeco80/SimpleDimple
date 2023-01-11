//
// SimpleDimple
//
// (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <iostream>
#include <string>

namespace sd::io::impl {

	namespace detail {
		void ReadStreamTypeImpl(std::istream& is, char* buffer, std::size_t size);
		void WriteStreamTypeImpl(std::ostream& os, const char* buffer, std::size_t buffer_size);
	} // namespace detail

	// This is lame. But it works :)
	template <class T>
	constexpr T ReadStreamType(std::istream& is) {
		T object {};

		detail::ReadStreamTypeImpl(is, std::bit_cast<char*>(&object), sizeof(T));

		return object;
	}

	template <class T>
	constexpr void WriteStreamType(std::ostream& os, const T& object) {
		detail::WriteStreamTypeImpl(os, std::bit_cast<char*>(&object), sizeof(T));
	}

	std::string ReadZeroTerminatedString(std::istream& is);

} // namespace sd::io::impl
