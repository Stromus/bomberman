/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_APOWERUP_HPP
#define INDIE_STUDIO_APOWERUP_HPP

#include "engine/game/player/IPlayer.hpp"
#include "engine/game/power_up/IPowerUp.hpp"

namespace engine {
	class APowerUp : public IPowerUp {
	public:
		explicit APowerUp(const PowerUpType &type);
		~APowerUp() override = default;

		void		capacityActivation(IPlayer *player) override;
		bool		isInvulnerable() noexcept override;
		PowerUpType	getType() override;
		std::string	getMeshName() override;
		int getTickID() override;

	protected:
		PowerUpType	_type;
		bool		_invulnerability;
		int		_tickID;
		std::string	_meshName;
	};
}
#endif //INDIE_STUDIO_APOWERUP_HPP
