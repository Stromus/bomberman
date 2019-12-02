/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include "exception/SoundException.hpp"

ise::SoundException::SoundException(const errorType &errType, const std::string &msg) noexcept
	: IndieStudioException(errType, "SoundException: " + msg)
{}