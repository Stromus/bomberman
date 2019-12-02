/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_INDIESTUDIOEXCEPTION_HPP
#define INDIE_STUDIO_INDIESTUDIOEXCEPTION_HPP

#include <iostream>
#include <exception>

namespace ise {
	enum errorType {
		CONFIGURATION,
		WARNING,
		CRITICAL,
	};

	class IndieStudioException : public std::exception {
	public:
		explicit IndieStudioException(const errorType &errType, const std::string &msg) noexcept;
		~IndieStudioException() override = default;

		const char *what() const noexcept override;
		const errorType getErrorType() const noexcept;

	private:
		std::string	_msg;
		errorType	_errType;
	};
}

#endif //INDIE_STUDIO_INDIESTUDIOEXCEPTION_HPP
