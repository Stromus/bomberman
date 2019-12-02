/*
** EPITECH PROJECT, 2021
** indie_studio
** File Description:
** Created by simong,
*/
#ifndef INDIE_STUDIO_HUMAN_HPP
#define INDIE_STUDIO_HUMAN_HPP

#include "engine/game/player/APlayer.hpp"

namespace engine {
	class Human : public APlayer {
	public:
		Human(const playerType &type, const short &ID, const Vector2<float> &pos, const std::string &meshName);
		~Human() final = default;

		void	updatePlayer(const std::vector<std::vector<engine::IChunk *>> &map, const std::vector<IPlayer *> &players) final;
	};
}

#endif /* !INDIE_STUDIO_HUMAN_HPP */
