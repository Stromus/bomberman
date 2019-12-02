/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include "exception/SettingsException.hpp"

ise::SettingsException::SettingsException(const errorType &errType, const std::string &msg) noexcept
	: IndieStudioException(errType, "SettingsException: " + msg)
{}
