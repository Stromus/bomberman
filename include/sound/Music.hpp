/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_MUSIC_HPP
#define INDIE_STUDIO_MUSIC_HPP

#include <map>
#include "SFML/Audio.hpp"

class Music {
public:
	enum musicID {
		INTRO = 0,
		BATTLE,
		CREDITS,
		MENU,
		WINNER
	};
	Music(const Music &music) = delete;
	Music(Music &&music) = delete;
	Music &operator=(const Music &music) = delete;

public:
	static Music *getInstance();

	void	play(const musicID &id, const bool &loop) noexcept;
	void	pause(const musicID &id) noexcept;
	void	stop(const musicID &id) noexcept;
	void	updateVolume() noexcept;

private:
	bool	checkIfLoadInMusics(const musicID &id) const;
	void	loadMusics();
	void	checkUnloadMusics();
	void	checkSeparator(const std::string &line) const;
	void	checkMusicID(const std::string &line) const;
	void	tryToLoadMusic(const std::string &line);

private:
	explicit	Music();
	~Music();

private:
	static Music	singleton;
	sf::Music	*_music;
	std::string	_actualMusic;
	std::map<std::string, musicID>	_corres = {
		{"INTRO", INTRO},
		{"BATTLE", BATTLE},
		{"CREDITS", CREDITS},
		{"MENU", MENU},
		{"WINNER", WINNER}
	};
	std::map<musicID, std::string>	_musics;
};

#endif //INDIE_STUDIO_MUSIC_HPP
