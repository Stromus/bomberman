/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include "open_target/File.hpp"
#include "settings/Settings.hpp"
#include "exception/SettingsException.hpp"
#include <exception>
#include <algorithm>
#include <iostream>
#include <string>

Settings Settings::singleton;

Settings *Settings::getInstance()
{
	return &singleton;
}

Settings::Settings():
	_musicVolume(50),
	_soundVolume(50),
	_numberFPS(60),
	_fullScreen(false),
	_resolution({1280, 720}),
	_language(Language::languageCode::EN)
{
	this->_typeCorrespondance["music"] = settingFields::music;
	this->_typeCorrespondance["sound"] = settingFields::sound;
	this->_typeCorrespondance["fps"] = settingFields::fps;
	this->_typeCorrespondance["fullscreen"] = settingFields::fullscreen;
	this->_typeCorrespondance["resolution"] = settingFields::resolution;
	this->_typeCorrespondance["language"] = settingFields::language;
	this->_typeCorrespondance["control"] = settingFields::control;

	this->_controls.insert(std::make_pair(Controls::keyIS::KEY_Z, std::make_pair(1, Controls::actions::MOVE_UP)));
	this->_controls.insert(std::make_pair(Controls::keyIS::KEY_Q, std::make_pair(1, Controls::actions::MOVE_LEFT)));
	this->_controls.insert(std::make_pair(Controls::keyIS::KEY_S, std::make_pair(1, Controls::actions::MOVE_DOWN)));
	this->_controls.insert(std::make_pair(Controls::keyIS::KEY_D, std::make_pair(1, Controls::actions::MOVE_RIGHT)));
	this->_controls.insert(std::make_pair(Controls::keyIS::KEY_SPACE, std::make_pair(1, Controls::actions::BOMB)));

	this->_controls.insert(std::make_pair(Controls::keyIS::KEY_ARROW_UP, std::make_pair(2, Controls::actions::MOVE_UP)));
	this->_controls.insert(std::make_pair(Controls::keyIS::KEY_ARROW_LEFT, std::make_pair(2, Controls::actions::MOVE_LEFT)));
	this->_controls.insert(std::make_pair(Controls::keyIS::KEY_ARROW_DOWN, std::make_pair(2, Controls::actions::MOVE_DOWN)));
	this->_controls.insert(std::make_pair(Controls::keyIS::KEY_ARROW_RIGHT, std::make_pair(2, Controls::actions::MOVE_RIGHT)));
	this->_controls.insert(std::make_pair(Controls::keyIS::KEY_ENTER, std::make_pair(2, Controls::actions::BOMB)));

	try {
		File settingFile("./.save/settings/settings.txt", File::F_IN);

		std::string line;
		auto fileContent = settingFile.getContent();
		while (std::getline(fileContent, line))
			this->parseSettingLine(line);
	}
	catch (const ise::SettingsException &error) {
		std::cerr << error.what();
		exit(84);
	}
}

Settings::~Settings()
{
	try {
		File settingFile("./.save/settings/settings.txt", File::F_OUT);
		Language *language = Language::getInstance();

		settingFile.writeContent("music=" + std::to_string(this->_musicVolume) + "\n");
		settingFile.writeContent("sound=" + std::to_string(this->_soundVolume) + "\n");
		settingFile.writeContent("fps=" + std::to_string(this->_numberFPS) + "\n");
		settingFile.writeContent("fullscreen=" + std::to_string(this->_fullScreen) + "\n");
		settingFile.writeContent("resolution=" + std::to_string(this->_resolution.x) + "x" + std::to_string(this->_resolution.y) + "\n");
		settingFile.writeContent("language=" + language->convertCodeToString(this->_language) + "\n");
	
		/* Save controls */
		for (int i = 1; i != 3; ++i) {
			std::string controlString("control=" + std::to_string(i));
			for (auto &control : this->_controls) {
				if (control.second.first == i)
					controlString += "," + std::to_string(control.first) + ":" + std::to_string(control.second.second);
			}
			settingFile.writeContent(controlString + "\n");
		}
	}
	catch (const ise::SettingsException &error) {
		std::cerr << error.what();
		exit(84);
	}
}

void Settings::checkMusic(const std::string &line)
{
	if (line.find_first_not_of("0123456789") != std::string::npos)
		throw ise::SettingsException(ise::CONFIGURATION, "Volume music: invalid value ('" + line + "')");
	_musicVolume = std::stoi(line.data());
}

void Settings::checkSound(const std::string &line)
{
	if (line.find_first_not_of("0123456789") != std::string::npos)
		throw ise::SettingsException(ise::CONFIGURATION, "Sound music: invalid value ('" + line + "')");
	_soundVolume = std::stoi(line.data());
}

void Settings::checkFps(const std::string &line)
{
	if (line.find_first_not_of("0123456789") != std::string::npos)
		throw ise::SettingsException(ise::CONFIGURATION, "Number of FPS: invalid value ('" + line + "')");
	_numberFPS = std::stoi(line.data());
}

void Settings::checkResolution(const std::string &line)
{
	if (line.find_first_not_of("0123456789x") != std::string::npos)
		throw ise::SettingsException(ise::CONFIGURATION, "Resolution: invalid value ('" + line + "')");
	if (std::count(line.begin(), line.end(), 'x') != 1)
		throw ise::SettingsException(ise::CONFIGURATION, "Resolution: invalid value ('" + line + "')");

	Vector2<size_t> resolution = {};
	std::size_t pos = line.find('x');
	resolution.x = static_cast<unsigned int>(std::stoi(line.substr(0, pos).data()));
	resolution.y = static_cast<unsigned int>(std::stoi(line.substr(pos + 1).data()));
	this->setResolution(resolution);
}

void Settings::checkFullScreen(const std::string &line)
{
	if (line.find_first_not_of("01") != std::string::npos)
		throw ise::SettingsException(ise::CONFIGURATION, "Full screen: invalid value ('" + line + "')");
	_fullScreen = static_cast<bool>(std::stoi(line.data()));
}

void Settings::checkLanguage(const std::string &line)
{
	Language	*language = Language::getInstance();

	if (language == nullptr)
		throw ise::SettingsException(ise::CONFIGURATION, "Cannot get singleton Language");
	Language::languageCode code = language->convertStringToCode(line);
	this->_language = code;
}

void Settings::setPlayerControl(const std::vector<std::string> &commands)
{
	std::string excludedChars("12");
	int i = 0;
	int player = 0;

	for (auto &command : commands) {
		if (command.find_first_not_of(excludedChars) != std::string::npos)
			throw ise::SettingsException(ise::CONFIGURATION, "Invalid control ('" + command + "')");
		if (i == 0) {
			player = std::atoi(command.data());
			excludedChars = "0123456789:";
			i += 1;
			continue;
		}
		size_t separatorPos = command.find_first_of(':');
		if (separatorPos == std::string::npos || command.length() < 3 || player == 0)
			throw ise::SettingsException(ise::CONFIGURATION, "Invalid control ('" + command + "')");
		int key = std::atoi(command.substr(0, separatorPos).data());
		int control = std::atoi(command.substr(separatorPos + 1).data());
		if (key >= Controls::keyIS::MAX_KEY || control >= Controls::actions::MAX_ACTION)
			throw ise::SettingsException(ise::CONFIGURATION, "Invalid control ('" + command + "')");
		this->setAction(static_cast<Controls::actions>(control), static_cast<Controls::keyIS>(key), player);
	}
}

void Settings::checkControl(std::string line)
{
	std::vector<std::string> parsedString;
	size_t separatorPos = line.find(',');

	while (separatorPos != std::string::npos) {
		std::string substring = line.substr(0, separatorPos);
		parsedString.push_back(substring);
		line = line.substr(separatorPos + 1);
		separatorPos = line.find(',');
	}
	parsedString.push_back(line);
	this->setPlayerControl(parsedString);
}

void Settings::setFieldValue(std::pair<std::string, std::string> splitedLine)
{
	settingFields type_id;
	
	try {
		type_id = this->_typeCorrespondance.at(splitedLine.first);
	}
	catch (const std::out_of_range &e) {
		throw ise::SettingsException(ise::CONFIGURATION, "Unknown field in settings.txt ('" + splitedLine.first + "')");
	}

	switch (type_id) {
		case settingFields::music:
			this->checkMusic(splitedLine.second);
			break;
		case settingFields::sound:
			this->checkSound(splitedLine.second);
			break;
		case settingFields::fps:
			this->checkFps(splitedLine.second);
			break;
		case settingFields::fullscreen:
			this->checkFullScreen(splitedLine.second);
			break;
		case settingFields::resolution:
			this->checkResolution(splitedLine.second);
			break;
		case settingFields::language:
			this->checkLanguage(splitedLine.second);
			break;
		case settingFields::control:
			this->checkControl(splitedLine.second);
			break;
		default:
			throw ise::SettingsException(ise::CONFIGURATION, "Unknown field in settings.txt ('" + splitedLine.first + "')");
	};
}

void Settings::parseSettingLine(const std::string &line)
{
	try {
		if (std::count(line.begin(), line.end(), '=') != 1)
			throw ise::SettingsException(ise::CONFIGURATION, "Missing or multiples '=' separator in '" + line + "'");
		std::size_t pos = line.find('=');
		std::pair<std::string, std::string> splitedLine = {line.substr(0, pos), line.substr(pos + 1)};
		this->setFieldValue(splitedLine);
	}
	catch (const ise::SettingsException &e) {
		std::cerr << e.what() << std::endl;
	}
}

/*----- GETTER -----*/

Controls::keyIS Settings::getKeyByAction(Controls::actions action, int player_nb) const noexcept
{
	for (auto &control : this->_controls) {
		if (control.second.second == action && control.second.first == player_nb)
			return (control.first);
	}
	return (Controls::keyIS::ERROR);
}

Controls::actions Settings::getAction(Controls::keyIS key, int player_nb) const noexcept
{
	try {
		auto pair = this->_controls.at(key);

		if (pair.first == player_nb)
			return (pair.second);
		return (Controls::actions::UNDEFINED);
	}
	catch (const std::out_of_range &e) {
		return (Controls::actions::UNDEFINED);
	}
}

int Settings::getTeam(Controls::actions action, Controls::keyIS key) const noexcept
{
	for (auto &control : this->_controls) {
		if (control.second.second == action && control.first == key)
			return (control.second.first);
	}
	return (0);
}

int Settings::getMusicVolume() const noexcept
{
	return _musicVolume;
}

int Settings::getSoundVolume() const noexcept
{
	return _soundVolume;
}

int Settings::getNumberFPS() const noexcept
{
	return _numberFPS;
}

bool Settings::isFullScreen() const noexcept
{
	return _fullScreen;
}

Vector2<size_t> Settings::getResolution() const noexcept
{
	return _resolution;
}

Language::languageCode Settings::getLanguage() const noexcept
{
	return _language;
}

/*----- SETTER -----*/

void Settings::setAction(Controls::actions action, Controls::keyIS key, int player_nb) noexcept
{
	Controls::keyIS oldKey;

	for (auto &control : this->_controls) {
		if (control.second.second == action && control.second.first == player_nb) {
			oldKey = control.first;
			this->_controls.erase(oldKey);
			this->_controls.insert(std::make_pair(key, std::make_pair(player_nb, action)));
			return;
		}
	}
}

void Settings::setMusicVolume(const int &musicVolume) noexcept
{
	_musicVolume = musicVolume;
}

void Settings::setSoundVolume(const int &soundVolume) noexcept
{
	_soundVolume = soundVolume;
}

void Settings::setNumberFPS(const int &numberFPS) noexcept
{
	_numberFPS = numberFPS;
}

void Settings::setFullScreen(const bool &fullScreen) noexcept
{
	_fullScreen = fullScreen;
}

void Settings::setResolution(const Vector2<size_t> &resolution) noexcept
{
	_resolution = resolution;
}

void Settings::setLanguage(const Language::languageCode &language) noexcept
{
	_language = language;
}