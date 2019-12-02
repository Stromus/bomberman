/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include "exception/IndieStudioException.hpp"

ise::IndieStudioException::IndieStudioException(const errorType &errType, const std::string &msg) noexcept
	: _errType(errType),
	_msg(msg)
{
	if (errType == WARNING)
		_msg = "[WARNING]: " + _msg;
	if (errType == CRITICAL)
		_msg = "[CRITICAL ERROR]: " + _msg;
	if (errType == CONFIGURATION)
		_msg = "[CONFIGURATION]: " + _msg;
}

const char *ise::IndieStudioException::what() const noexcept
{
	return _msg.c_str();
}

const ise::errorType ise::IndieStudioException::getErrorType() const noexcept
{
	return _errType;
}
