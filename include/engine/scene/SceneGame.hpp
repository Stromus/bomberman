/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_SCENEGAME_HPP
#define INDIE_STUDIO_SCENEGAME_HPP

#include "engine/scene/AGuiScene.hpp"

namespace engine {
	class SceneGame : public AGuiScene {
	public:
		enum scene {
			P1_TYPE,
			P1_BOMB_QUANTITY,
			P1_FIRE_RANGE,
			P1_SPEED,
			P1_NB_LIFE,
			P1_TEAM,
			P1_CAPACITY,
			P1_BOMB,
			P2_TYPE,
			P2_BOMB_QUANTITY,
			P2_FIRE_RANGE,
			P2_SPEED,
			P2_NB_LIFE,
			P2_TEAM,
			P2_CAPACITY,
			P2_BOMB,
			P3_TYPE,
			P3_BOMB_QUANTITY,
			P3_FIRE_RANGE,
			P3_SPEED,
			P3_NB_LIFE,
			P3_TEAM,
			P3_CAPACITY,
			P3_BOMB,
			P4_TYPE,
			P4_BOMB_QUANTITY,
			P4_FIRE_RANGE,
			P4_SPEED,
			P4_NB_LIFE,
			P4_TEAM,
			P4_CAPACITY,
			P4_BOMB
		};
		SceneGame();
		~SceneGame() final = default;

		void	desactivateVisibility() final;
		void	activateVisibility() final;
		void	analyseEvent(std::pair<int, render::eventData> &event, sceneIndex &index,\
		sceneIndex lastScene, LoadGame &loadGame) final;
		void	updateScene(sceneIndex &index, sceneIndex lastScene, LoadGame &loadGame) final;

	private:
		bool _p1_dead;
		bool _p2_dead;
		bool _p3_dead;
		bool _p4_dead;
	};
}
#endif //INDIE_STUDIO_SCENEGAME_HPP
