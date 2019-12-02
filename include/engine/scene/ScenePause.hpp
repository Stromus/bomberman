/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_PAUSE_HPP
#define INDIE_STUDIO_PAUSE_HPP

#include "engine/scene/AGuiScene.hpp"

namespace engine {
	class ScenePause : public AGuiScene {
	public:
		enum scene {
			BACKGROUND = 0,
			CONTINUE,
			LOAD,
			SAVE,
			SETTINGS,
			QUIT
		};
		ScenePause();
		~ScenePause() final = default;

		void	analyseEvent(std::pair<int, render::eventData> &event, sceneIndex &index,\
		sceneIndex lastScene, LoadGame &loadGame) final;
	};
}
#endif //INDIE_STUDIO_PAUSE_HPP
