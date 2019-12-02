/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <sound/Noise.hpp>
#include "engine/game/power_up/PUFireUp.hpp"

engine::PUFireUp::PUFireUp()
	: APowerUp(FIRE_UP)
{
	_meshName = "PUFireUp";
}

void engine::PUFireUp::capacityActivation(engine::IPlayer *player)
{
	Noise::getInstance()->play(Noise::GOOD_POWER_UP);
	player->setFireRange(player->getFireRange() + static_cast<short>(1));
}
