/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_SCENECREDITS_HPP
#define INDIE_STUDIO_SCENECREDITS_HPP

#include "engine/scene/AGuiScene.hpp"

namespace engine {
	class SceneCredits : public AGuiScene {
	public:
		enum scene {
			BACKGROUND = 0,
			RETURN,
			GRAVILLON_IMAGE,
			GRAVILLON_TEXT,
			SIMON_IMAGE,
			SIMON_TEXT,
			NICOLAS_IMAGE,
			NICOLAS_TEXT,
			JUSTIN_IMAGE,
			JUSTIN_TEXT,
			MELVYN_IMAGE,
			MELVYN_TEXT
		};

		SceneCredits();
		~SceneCredits() final = default;

		void	analyseEvent(std::pair<int, render::eventData> &event, sceneIndex &index,\
		sceneIndex lastScene, LoadGame &loadGame) final;
	};
}

#endif //INDIE_STUDIO_SCENECREDITS_HPP
