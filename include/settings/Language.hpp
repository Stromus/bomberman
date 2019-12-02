/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by simong,
*/

#ifndef INDIE_STUDIO_LANGUAGE_HPP
#define INDIE_STUDIO_LANGUAGE_HPP

#include <exception>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class Settings;

class Language {
public:
	Language(const Language &Language) = delete;
	Language(Language &&Language) = delete;
	Language& operator=(const Language &Language) = delete;

public:
	enum languageCode {
		EN = 0,
		FR,
		SP
	};

	struct Lang {
		languageCode	code;
		std::string	flag;
		std::string	path;
	};

	enum textID {
		LOADING = 0,
		NEW_GAME,
		SETTINGS,
		CHOOSE,
		CREDITS,
		QUIT,
		RETURN_MENU,
		PLAYER_CHOICE,
		PLAY,
		CONTINUE,
		QUIT_GAME,
		GAME_SETTINGS,
		COLUMNS,
		LINES,
		GENERATE_WITH,
		GAME_DURATION,
		AI_DIFFICULTY,
		NUMBER_OF_TEAM,
		GAME_MODE,
		GENERAL,
		PREVIOUS_TAB,
		NEXT_TAB,
		FRAMERATE,
		SOUND_VOLUME,
		MUSIC_VOLUME,
		RESOLUTION_PATCH,
		ACTIVATE_FULLSCREEN,
		LANGUAGE,
		CONTROLS,
		PLAYER1,
		PLAYER2,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		BOMB,
		SAVE_CONTROLS,
		ERROR,
		SAVE,
		NB_PLAYERS,
		ALL_DEATH,
		PLAYER,
		VICTORIOUS,
	};

public:
	static Language		*getInstance();
	const std::wstring	getTranslate(const Language::textID &id);
	Language::languageCode convertStringToCode(const std::string &line);
	const		std::string &convertCodeToString(const languageCode &code);
	const		std::vector<Language::Lang> getLanguagesList() const noexcept;
	const bool	isLanguageUpdated() noexcept;
	void		setUpdated(const bool &isUpdated) noexcept;

private:
	void		setLanguages();
	void		checkSeparator(const std::string &line, const int &nb) const;
	void		checkUnicode(const std::string &unicode) const;
	void		setTranslation(const languageCode &langCode);
	void		checkCurrentLoadedLanguage() noexcept;
	void		checkContainer(const std::string &line) const;
	void		checkTextID(const std::string &textid);
	void		fillLangStruct(std::string &line);
	void		checkUnloadTranslation() const;
	void		checkCodeFile(const std::string &line) const;
	bool		isUnicodeAlreadyExist(const std::string &line) const noexcept;
	Lang		getCorrespondLanguageStruct(const languageCode &langCode) const;
	std::wstring	stows(const std::string &in) const noexcept;

private:
	explicit		Language();
	static Language		singleton;

private:
	languageCode		_actual;
	bool				_isUpdated;
	std::vector<Lang>	_languages;
	std::map<textID, std::wstring>	_translate;
	std::map<std::string, languageCode> _corresToLanguageCode = {
		{"EN", EN},
		{"FR", FR},
		{"SP", SP}
	};
	std::map<std::string, textID>	_corresToTextID = {
		{"LOADING", LOADING},
		{"NEW_GAME", NEW_GAME},
		{"SETTINGS", SETTINGS},
		{"CHOOSE", CHOOSE},
		{"CREDITS", CREDITS},
		{"QUIT", QUIT},
		{"RETURN_MENU", RETURN_MENU},
		{"PLAYER_CHOICE", PLAYER_CHOICE},
		{"PLAY", PLAY},
		{"CONTINUE", CONTINUE},
		{"QUIT_GAME", QUIT_GAME},
		{"GAME SETTINGS", GAME_SETTINGS},
		{"COLUMNS", COLUMNS},
		{"LINES", LINES},
		{"GENERATE_WITH", GENERATE_WITH},
		{"GAME_DURATION", GAME_DURATION},
		{"AI_DIFFICULTY", AI_DIFFICULTY},
		{"NUMBER_OF_TEAM", NUMBER_OF_TEAM},
		{"GAME_MODE", GAME_MODE},
		{"GENERAL", GENERAL},
		{"PREVIOUS_TAB", PREVIOUS_TAB},
		{"NEXT_TAB", NEXT_TAB},
		{"FRAMERATE", FRAMERATE},
		{"SOUND_VOLUME", SOUND_VOLUME},
		{"MUSIC_VOLUME", MUSIC_VOLUME},
		{"RESOLUTION_PATCH", RESOLUTION_PATCH},
		{"ACTIVATE_FULLSCREEN", ACTIVATE_FULLSCREEN},
		{"LANGUAGE", LANGUAGE},
		{"CONTROLS", CONTROLS},
		{"PLAYER1", PLAYER1},
		{"PLAYER2", PLAYER2},
		{"UP", UP},
		{"DOWN", DOWN},
		{"LEFT", LEFT},
		{"RIGHT", RIGHT},
		{"BOMB", BOMB},
		{"SAVE_CONTROLS", SAVE_CONTROLS},
		{"ERROR", ERROR},
		{"SAVE", SAVE},
		{"NB_PLAYERS", NB_PLAYERS},
		{"ALL_DEATH", ALL_DEATH},
		{"PLAYER", PLAYER},
		{"VICTORIOUS", VICTORIOUS},
	};
};

#endif //INDIE_STUDIO_LANGUAGE_HPP
