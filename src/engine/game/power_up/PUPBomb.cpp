/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <sound/Noise.hpp>
#include "engine/game/bomb/PBomb.hpp"
#include "engine/game/power_up/PUPBomb.hpp"

engine::PUPBomb::PUPBomb()
	: APowerUp(P_BOMB)
{
	_meshName = "PUPBomb";
}

void engine::PUPBomb::capacityActivation(engine::IPlayer *player)
{
	Noise::getInstance()->play(Noise::GOOD_POWER_UP);
	if (player->getBomb()->getType() == IBomb::bombType::P_BOMB)
		return;
	player->setBomb(new PBomb(player->getPlayerID()));
}