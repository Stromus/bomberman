/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_IPOWERUP_HPP
#define INDIE_STUDIO_IPOWERUP_HPP

#include "engine/game/player/IPlayer.hpp"

namespace engine {
	class IPowerUp {
	public:
		const double INVULNERABILITY_TIME = 500;
		enum PowerUpType {
			FIRE_UP,
			FIRE_DOWN,
			SPEED_UP,
			SPEED_DOWN,
			QUANTITY_UP,
			QUANTITY_DOWN,
			SHIELD,
			INVERT_CONTROL,
			AUTOBOMB,
			P_BOMB,
			G_BOMB,
			LAVA_BOMB,
			GHOST,
			RANDOM
		};
		virtual ~IPowerUp() = default;

		virtual void		capacityActivation(IPlayer *player) = 0;
		virtual bool		isInvulnerable() noexcept = 0;
		virtual PowerUpType	getType() = 0;
		virtual std::string	getMeshName() = 0;
		virtual int getTickID() = 0;
	};
}
#endif //INDIE_STUDIO_IPOWERUP_HPP
