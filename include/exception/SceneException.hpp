/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_SCENEEXCEPTION_HPP
#define INDIE_STUDIO_SCENEEXCEPTION_HPP

#include "exception/IndieStudioException.hpp"

namespace ise {
	class SceneException : public IndieStudioException {
	public:
		explicit SceneException(const errorType &errType, const std::string &msg) noexcept;
		~SceneException() override = default;

	private:
		std::string	_msg;
		errorType 	_errType;
	};
}

#endif //INDIE_STUDIO_SCENEEXCEPTION_HPP
