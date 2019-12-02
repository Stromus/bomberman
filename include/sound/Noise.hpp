/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_NOISE_HPP
#define INDIE_STUDIO_NOISE_HPP

#include <string>
#include <map>
#include <vector>
#include "SFML/Audio.hpp"
#include <list>

class Noise {
public:
	enum noiseID {
		MENU_SELECTION = 0,
		MENU_ENTER,
		BOMB_EXPLOSION,
		BAD_POWER_UP,
		GOOD_POWER_UP,
		DEATH
	};

	Noise(const Noise &noise) = delete;
	Noise(Noise &&noise) = delete;
	Noise &operator=(const Noise &noise) = delete;

public:
	static Noise *getInstance();

	void	play(const noiseID &id) noexcept;
	void	updateVolume() noexcept;

private:
	bool	checkIfLoadInBufferSounds(const noiseID &id) const;
	void	loadNoise();
	void	checkUnloadNoise() const;
	void	checkSeparator(const std::string &line) const;
	void	checkNoiseID(const std::string &line) const;
	void	tryToLoadBufferSound(const std::string &line);

private:
	explicit	Noise();
	~Noise();
	static Noise	singleton;
	sf::SoundBuffer	_soundBuffer;

private:
	std::map<std::string, noiseID>	_corres = {
		{"MENU_SELECTION", MENU_SELECTION},
		{"MENU_ENTER", MENU_ENTER},
		{"BOMB_EXPLOSION", BOMB_EXPLOSION},
		{"BAD_POWER_UP", BAD_POWER_UP},
		{"GOOD_POWER_UP", GOOD_POWER_UP},
		{"DEATH", DEATH}
	};
	std::map<noiseID, sf::SoundBuffer>	_bufferSound;
	std::list<sf::Sound *>			_activSound;
};

#endif //INDIE_STUDIO_NOISE_HPP
