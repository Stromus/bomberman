/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_SCENELOAD_HPP
#define INDIE_STUDIO_SCENELOAD_HPP

#include "engine/scene/AGuiScene.hpp"

namespace engine {
	class SceneLoad : public AGuiScene {
		enum element {
			BACKGROUND = 0,
			TITLE,
			SAVE_1,
			SAVE_2,
			SAVE_3,
			SAVE_4,
			SAVE_5,
			RETURN
		};
	public:
		SceneLoad();
		~SceneLoad() final = default;

		void	analyseEvent(std::pair<int, render::eventData> &event, sceneIndex &index,\
		sceneIndex lastScene, LoadGame &loadGame) final;
		std::vector<std::string> _saveNames;
	};
}
#endif //INDIE_STUDIO_SCENELOAD_HPP
