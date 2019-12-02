/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_SCENESETTINGS_HPP
#define INDIE_STUDIO_SCENESETTINGS_HPP

#include "engine/scene/AGuiScene.hpp"

namespace engine {
	class SceneSettings : public AGuiScene {
	public:
		enum scene {
			BACKGROUND = 0,
			TITLE,
			TAB_CONTROL,
			MAIN_TAB,
			SCROLL_FPS,
			FPS_WORD,
			FPS_VALUE,
			SCROLL_SOUND,
			SOUND_WORD,
			SOUND_VALUE,
			SCROLL_MUSIC,
			MUSIC_WORD,
			MUSIC_VALUE,
			RESOLUTION_TXT,
			RESOLUTION,
			FULLSCREEN,
			CTRL_TAB,
			MOVE_UP_1,
			MOVE_DOWN_1,
			MOVE_LEFT_1,
			MOVE_RIGHT_1,
			BOMB_CTRL_1,
			MOVE_UP_1_TXT,
			MOVE_DOWN_1_TXT,
			MOVE_LEFT_1_TXT,
			MOVE_RIGHT_1_TXT,
			BOMB_1_TXT,
			MOVE_UP_2,
			MOVE_DOWN_2,
			MOVE_LEFT_2,
			MOVE_RIGHT_2,
			BOMB_CTRL_2,
			MOVE_UP_2_TXT,
			MOVE_DOWN_2_TXT,
			MOVE_LEFT_2_TXT,
			MOVE_RIGHT_2_TXT,
			BOMB_2_TXT,
			PLAYER1_TXT,
			PLAYER2_TXT,
			SAVE_CONTROLS,
			LANGUAGE_TAB,
			PREV_TAB = 100,
			NEXT_TAB,
			RETURN,
		};

		explicit SceneSettings();
		~SceneSettings() final = default;

	private:
		void	createMainTab();
		void	createControlsTab();
		void	createLanguageTab();
		void	analyseEvent(std::pair<int, render::eventData> &event, sceneIndex &index,\
		sceneIndex lastScene, LoadGame &loadGame) final;
		void	changeControls(std::pair<int, render::eventData> &event);
		void	checkControlValidity();
		void	changeLanguage(std::pair<int, render::eventData> &event);


		std::pair<std::vector<Controls::keyIS>, std::vector<Controls::keyIS>> _controls;
		std::vector<int> _idxLanguagesEvents;
	};
}
#endif //INDIE_STUDIO_SCENESETTINGS_HPP
