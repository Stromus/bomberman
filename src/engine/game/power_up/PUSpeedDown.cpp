/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <sound/Noise.hpp>
#include "engine/game/power_up/PUSpeedDown.hpp"

engine::PUSpeedDown::PUSpeedDown()
	: APowerUp(SPEED_DOWN)
{
	_meshName = "PUSpeedDown";
}

void engine::PUSpeedDown::capacityActivation(engine::IPlayer *player)
{
	Noise::getInstance()->play(Noise::BAD_POWER_UP);
	if (player->getSpeed() == 1)
		return;
	player->setSpeed(player->getSpeed() - static_cast<short>(1));
}