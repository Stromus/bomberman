/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_SCENEPLAYERCHOICE_HPP
#define INDIE_STUDIO_SCENEPLAYERCHOICE_HPP

#include "engine/scene/AGuiScene.hpp"

namespace engine {
	class ScenePlayerChoice : public AGuiScene {
	public:
		enum scene {
			BACKGROUND = 0,
			RETURN,
			PICK,
			NB_PLAYER_BAR,
			NB_PLAYER_VALUE,
			NB_PLAYER_TEXT,
			SKIN_BB8_1,
			SKIN_BB8_2,
			SKIN_BB8_3,
			SKIN_BB8_4,
			SKIN_BB8_5,
			SKIN_BB8_6,
			SKIN_R2D2_1,
			SKIN_R2D2_2,
			SKIN_R2D2_3,
			SKIN_R2D2_4,
			SKIN_R2D2_5,
			SKIN_R2D2_6,
			BUTTON_BB8_1,
			BUTTON_BB8_2,
			BUTTON_BB8_3,
			BUTTON_BB8_4,
			BUTTON_BB8_5,
			BUTTON_BB8_6,
			BUTTON_R2D2_1,
			BUTTON_R2D2_2,
			BUTTON_R2D2_3,
			BUTTON_R2D2_4,
			BUTTON_R2D2_5,
			BUTTON_R2D2_6,
			PLAY
		};
		ScenePlayerChoice();
		~ScenePlayerChoice() final = default;

		void analyseEvent(std::pair<int, render::eventData> &event,
			sceneIndex &index, sceneIndex lastScene,
			LoadGame &loadGame) final;

	private:
		void	playButtonPressed(engine::LoadGame &loadGame);
		void	fillPlayerMeshMap(std::string &meshName, scene sceneID);

	private:
		std::map<short, std::string> _meshMap = {
			{0, ""},
			{1, ""},
			{2, ""},
			{3, ""}
		};
		std::map<scene, std::string> _meshSkin = {
			{BUTTON_BB8_1, "BB8_basic"},
			{BUTTON_BB8_2, "BB8_blue"},
			{BUTTON_BB8_3, "BB8_green"},
			{BUTTON_BB8_4, "BB8_pink"},
			{BUTTON_BB8_5, "BB8_purple"},
			{BUTTON_BB8_6, "BB8_red"},
			{BUTTON_R2D2_1, "R2D2_basic"},
			{BUTTON_R2D2_2, "R2D2_gold"},
			{BUTTON_R2D2_3, "R2D2_green"},
			{BUTTON_R2D2_4, "R2D2_pink"},
			{BUTTON_R2D2_5, "R2D2_purple"},
			{BUTTON_R2D2_6, "R2D2_red"}
		};
		int	_nbHumanPlayer;
	};
}
#endif //INDIE_STUDIO_SCENEPLAYERCHOICE_HPP
