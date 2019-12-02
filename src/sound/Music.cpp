/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <iostream>
#include <sstream>
#include "settings/Settings.hpp"
#include "open_target/File.hpp"
#include "sound/Music.hpp"
#include "exception/SoundException.hpp"
#include "exception/SettingsException.hpp"

#ifdef _MSC_VER
#pragma comment(lib, "sfml-audio.lib")
#endif

Music	Music::singleton;

Music::Music()
	: _music(new sf::Music()),
	_actualMusic("")
{
	try {
		loadMusics();
		checkUnloadMusics();
	}
	catch (const ise::SettingsException &error) {
		std::cerr << error.what();
		exit(84);
	}
}

Music::~Music()
{
	if (_music != nullptr)
		_music->stop();
}

Music	*Music::getInstance()
{
	return &singleton;
}

void Music::checkUnloadMusics()
{
	for (auto &music : _corres) {
		try {
			if (_musics.find(music.second) == _musics.end())
				throw ise::SoundException(ise::WARNING,\
				"The given file 'music.txt' doesn't load the ID: '" +\
				std::to_string(music.second) + "'");
		}
		catch(const ise::SoundException &error) {
			std::cerr << error.what() << std::endl;
		}
	}
}

void Music::checkSeparator(const std::string &line) const
{
	if (line.find(':') == std::string::npos)
		throw ise::SoundException(ise::CONFIGURATION, \
"In res/sound/file/music.txt: \"" + line + "\": need ':' separator.\t[LINE SKIPPED]");
}

void Music::checkMusicID(const std::string &line) const
{
	if (_corres.find(line) == _corres.end())
		throw ise::SoundException(ise::CONFIGURATION, \
"In res/sound/file/music.txt: \"" + line + "\": Isn't a valid name ID.\t[LINE SKIPPED]");
}

void Music::tryToLoadMusic(const std::string &line)
{
	if (!_music->openFromFile(line)) {
		throw ise::SoundException(ise::CONFIGURATION, \
"In res/sound/file/music.txt: \"" + line + "\": Isn't a valid music path.\t[LINE SKIPPED]");
	}
}

void Music::loadMusics()
{
	try {
		File file("res/sound/file/music.txt", File::fileMode::F_IN);
		std::stringstream stream = file.getContent();
		std::string line;
		std::string idToken;
		while (getline(stream, line)) {
			try {
				checkSeparator(line);
				idToken = line.substr(0, line.find(':'));
				checkMusicID(idToken);
				line.erase(0, idToken.size() + 1);
				line = "res/sound/music/" + line;
				tryToLoadMusic(line);
				_musics.insert(std::pair<musicID, std::string>(
					_corres[idToken], line));
			} catch (const ise::SoundException &error) {
				std::cerr << error.what() << std::endl;
			}
		}
	}
	catch (const ise::SettingsException &error) {
		std::cerr << error.what() << std::endl;
	}
}

bool Music::checkIfLoadInMusics(const Music::musicID &id) const
{
	try {
		if (_musics.find(id) == _musics.end())
			throw ise::SoundException(ise::WARNING, "'" +\
			std::to_string(id) +\
			"': Cannot interact with a music if his ID isn't set in music database.");
	}
	catch (const ise::SoundException &error) {
		std::cerr << error.what() << std::endl;
		return false;
	}
	return true;
}

void Music::play(const musicID &id, const bool &loop) noexcept
{
	if (!checkIfLoadInMusics(id))
		return;
	if (_actualMusic == _musics[id]) {
		updateVolume();
		_music->play();
		return;
	}
	_music->stop();
	_music->openFromFile(_musics[id]);
	_music->setLoop(loop);
	updateVolume();
	_music->play();
}

void Music::stop(const musicID &id) noexcept
{
	if (checkIfLoadInMusics(id))
		_music->stop();
}

void Music::pause(const musicID &id) noexcept
{
	if (checkIfLoadInMusics(id))
		_music->pause();
}

void Music::updateVolume() noexcept
{
	_music->setVolume(static_cast<float>(Settings::getInstance()->getMusicVolume()));
}
