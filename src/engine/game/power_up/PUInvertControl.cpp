/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <sound/Noise.hpp>
#include "engine/game/power_up/PUInvertControl.hpp"

engine::PUInvertControl::PUInvertControl()
	: APowerUp(INVERT_CONTROL)
{
	_meshName = "PUInvertControl";
}

void engine::PUInvertControl::capacityActivation(engine::IPlayer *player)
{
	Noise::getInstance()->play(Noise::BAD_POWER_UP);
	player->setPlantBomb(false);
	player->setCollision(true);
	player->setCapacity(IPlayer::capacity::INVERT_CONTROL);
	player->setInvertControl(true);
}