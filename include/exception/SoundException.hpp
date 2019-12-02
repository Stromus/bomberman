/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_SOUNDEXCEPTION_HPP
#define INDIE_STUDIO_SOUNDEXCEPTION_HPP

#include "exception/IndieStudioException.hpp"

namespace ise {
	class SoundException : public IndieStudioException {
	public:
		explicit SoundException(const errorType &errType, const std::string &msg) noexcept;
		~SoundException() override = default;

	private:
		std::string	_msg;
		errorType 	_errType;
	};
}

#endif //INDIE_STUDIO_SOUNDEXCEPTION_HPP
