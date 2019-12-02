/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <sound/Noise.hpp>
#include "engine/game/power_up/PUGhost.hpp"

engine::PUGhost::PUGhost()
	: APowerUp(GHOST)
{
	_meshName = "PUGhost";
}

void engine::PUGhost::capacityActivation(engine::IPlayer *player)
{
	Noise::getInstance()->play(Noise::GOOD_POWER_UP);
	player->setPlantBomb(false);
	player->setInvertControl(false);
	player->setCapacity(IPlayer::capacity::GHOST);
	player->setCollision(false);
}