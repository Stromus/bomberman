/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <sound/Noise.hpp>
#include "engine/game/bomb/LavaBomb.hpp"
#include "engine/game/power_up/PULavaBomb.hpp"

engine::PULavaBomb::PULavaBomb()
	: APowerUp(LAVA_BOMB)
{
	_meshName = "PULavaBomb";
}

void engine::PULavaBomb::capacityActivation(engine::IPlayer *player)
{
	Noise::getInstance()->play(Noise::GOOD_POWER_UP);
	if (player->getBomb()->getType() == IBomb::bombType::LAVA_BOMB)
		return;
	player->setBomb(new LavaBomb(player->getPlayerID()));
}