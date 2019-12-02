/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <sound/Noise.hpp>
#include "engine/game/power_up/PUFireDown.hpp"

engine::PUFireDown::PUFireDown()
	: APowerUp(FIRE_DOWN)
{
	_meshName = "PUFireDown";
}

void engine::PUFireDown::capacityActivation(engine::IPlayer *player)
{
	Noise::getInstance()->play(Noise::BAD_POWER_UP);
	if (player->getFireRange() == 1)
		return;
	player->setFireRange(player->getFireRange() - static_cast<short>(1));
}