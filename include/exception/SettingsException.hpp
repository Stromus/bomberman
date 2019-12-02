/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_SETTINGSEXCEPTION_HPP
#define INDIE_STUDIO_SETTINGSEXCEPTION_HPP

#include "exception/IndieStudioException.hpp"

namespace ise {
	class SettingsException : public IndieStudioException {
	public:
		explicit SettingsException(const errorType &errType, const std::string &msg) noexcept;
		~SettingsException() override = default;

	private:
		std::string	_msg;
		errorType 	_errType;
	};
}

#endif //INDIE_STUDIO_SETTINGSEXCEPTION_HPP
