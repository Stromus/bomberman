/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <sound/Noise.hpp>
#include "engine/game/power_up/PUSpeedUp.hpp"

engine::PUSpeedUp::PUSpeedUp()
	: APowerUp(SPEED_UP)
{
	_meshName = "PUSpeedUp";
}

void engine::PUSpeedUp::capacityActivation(engine::IPlayer *player)
{
	Noise::getInstance()->play(Noise::GOOD_POWER_UP);
	player->setSpeed(player->getSpeed() + static_cast<short>(1));
}