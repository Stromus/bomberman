/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <fstream>
#include <sstream>
#include "open_target/File.hpp"
#include "settings/Settings.hpp"
#include "exception/SoundException.hpp"
#include "exception/SettingsException.hpp"
#include "sound/Noise.hpp"

Noise	Noise::singleton;

Noise *Noise::getInstance()
{
	return &singleton;
}

Noise::Noise()
{
	try {
		loadNoise();
		checkUnloadNoise();
	}
	catch (const ise::SettingsException &error) {
		std::cerr << error.what();
		exit(84);
	}
}

Noise::~Noise()
{
	for (auto &sound : _activSound) {
		sound->stop();
	}
}

void Noise::tryToLoadBufferSound(const std::string &line)
{
	if (!_soundBuffer.loadFromFile(line))
		throw ise::SoundException(ise::CONFIGURATION, \
"In res/sound/file/noise.txt: \"" + line + "\": Isn't a valid noise path.\t[LINE SKIPPED]");
}

void Noise::checkSeparator(const std::string &line) const
{
	if (line.find(':') == std::string::npos)
		throw ise::SoundException(ise::CONFIGURATION, \
"In res/sound/file/noise.txt: \"" + line + "\": need ':' separator.\t[LINE SKIPPED]");
}

void Noise::checkNoiseID(const std::string &line) const
{
	if (_corres.find(line) == _corres.end())
		throw ise::SoundException(ise::CONFIGURATION, \
"In res/sound/file/noise.txt: \"" + line + "\": Isn't a valid name ID.\t[LINE SKIPPED]");
}

void Noise::loadNoise()
{
	try {
		File file("res/sound/file/noise.txt", File::fileMode::F_IN);
		std::stringstream stream = file.getContent();
		std::string line;
		std::string idToken;

		while (getline(stream, line)) {
			try {
				checkSeparator(line);
				idToken = line.substr(0, line.find(':'));
				checkNoiseID(idToken);
				line.erase(0, idToken.size() + 1);
				line = "res/sound/noise/" + line;
				tryToLoadBufferSound(line);
				_bufferSound.insert(std::pair<noiseID, sf::SoundBuffer>(_corres[idToken], _soundBuffer));
			} catch (const ise::SoundException &error) {
				std::cerr << error.what() << std::endl;
			}
		}
	}
	catch (const ise::SettingsException &error) {
		std::cerr << error.what();
	}
}

void Noise::checkUnloadNoise() const
{
	for (auto &noise : _corres) {
		try {
			if (_bufferSound.find(noise.second) == _bufferSound.end())
				throw ise::SoundException(ise::WARNING,\
				"The given file 'noise.txt' doesn't load the ID: '" +\
				std::to_string(noise.second) + "'");
		}
		catch(const ise::SoundException &error) {
			std::cerr << error.what() << std::endl;
		}
	}

}

bool Noise::checkIfLoadInBufferSounds(const Noise::noiseID &id) const
{
	try {
		if (_bufferSound.find(id) == _bufferSound.end())
			throw ise::SoundException(ise::WARNING, "'" +\
			std::to_string(id) +\
			"': Cannot interact with a noise if his ID isn't set in noise database.");
	}
	catch (const ise::SoundException &error) {
		std::cerr << error.what() << std::endl;
		return false;
	}
	return true;
}

void Noise::updateVolume() noexcept
{
	for (auto &sound : _activSound)
		sound->setVolume(static_cast<float>(Settings::getInstance()->getSoundVolume()));
}

void Noise::play(const Noise::noiseID &id) noexcept
{
	if (!checkIfLoadInBufferSounds(id))
		return;
	for (auto sound : _activSound) {
		if (sound->getStatus() != sf::Sound::Playing) {
			sound->setBuffer(_bufferSound.find(id)->second);
			sound->setVolume(static_cast<float>(Settings::getInstance()->getSoundVolume()));
			sound->play();
			return;
		}
	}
	if (_activSound.size() > 100)
		return;
	auto *sound = new sf::Sound(_bufferSound.find(id)->second);
	sound->setVolume(static_cast<float>(Settings::getInstance()->getSoundVolume()));
	sound->play();
	_activSound.push_back(sound);
}