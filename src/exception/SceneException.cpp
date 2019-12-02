/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include "exception/SceneException.hpp"

ise::SceneException::SceneException(const errorType &errType, const std::string &msg) noexcept
	: IndieStudioException(errType, "SceneException: " + msg)
{}