/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_SETTINGS_HPP
#define INDIE_STUDIO_SETTINGS_HPP

#include <map>
#include <functional>
#include "template/Vector.hpp"
#include "settings/Language.hpp"
#include "Controls.hpp"

class Settings {
public:
	Settings(const Settings &settings) = delete;
	Settings(Settings &&settings) = delete;
	Settings& operator=(const Settings &settings) = delete;

public:
	static Settings	*getInstance();

	Controls::keyIS getKeyByAction(Controls::actions action, int player_nb) const noexcept;
	Controls::actions getAction(Controls::keyIS key, int player_nb) const noexcept;
	int	getTeam(Controls::actions action, Controls::keyIS key) const noexcept;
	int	getMusicVolume() const noexcept;
	int	getSoundVolume() const noexcept;
	int	getNumberFPS() const noexcept;
	bool	isFullScreen() const noexcept;
	Vector2<size_t>	getResolution() const noexcept;
	Language::languageCode	getLanguage() const noexcept;

	/*----- SETTER -----*/
	void	setAction(Controls::actions action, Controls::keyIS key, int player_nb) noexcept;
	void	setMusicVolume(const int &musicVolume) noexcept;
	void	setSoundVolume(const int &soundVolume) noexcept;
	void	setNumberFPS(const int &numberFPS) noexcept;
	void	setFullScreen(const bool &fullScreen) noexcept;
	void	setResolution(const Vector2<size_t> &resolution) noexcept;
	void	setLanguage(const Language::languageCode &language) noexcept;

private:
	explicit Settings();
	~Settings();
	static Settings	singleton;
	void	parseSettingLine(const std::string &line);
	void	checkMusic(const std::string &line);
	void	checkSound(const std::string &line);
	void	checkFps(const std::string &line);
	void	checkResolution(const std::string &line);
	void	checkFullScreen(const std::string &line);
	void	checkLanguage(const std::string &line);
	void	checkControl(std::string line);
	void	setFieldValue(std::pair<std::string, std::string> splitedLine);
	void	setPlayerControl(const std::vector<std::string> &commands);

private:
	enum settingFields {
		music = 0,
		sound,
		fps,
		fullscreen,
		resolution,
		language,
		control
	};
	int	_musicVolume;
	int	_soundVolume;
	int	_numberFPS;
	bool	_fullScreen;
	Vector2<size_t>	_resolution;
	std::map<std::string, settingFields>	_typeCorrespondance;
	Language::languageCode			_language;
	std::map<Controls::keyIS, std::pair<int, Controls::actions>>	_controls;
};

#endif //INDIE_STUDIO_SETTINGS_HPP
