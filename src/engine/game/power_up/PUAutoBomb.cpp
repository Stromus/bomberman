/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <sound/Noise.hpp>
#include "engine/game/power_up/PUAutobomb.hpp"

engine::AutoBomb::AutoBomb()
	: APowerUp(AUTOBOMB)
{
	_meshName = "PUAutoBomb";
}

void engine::AutoBomb::capacityActivation(engine::IPlayer *player)
{
	Noise::getInstance()->play(Noise::GOOD_POWER_UP);
	player->setCollision(true);
	player->setInvertControl(false);
	player->setCapacity(IPlayer::capacity::AUTOBOMB);
	player->setPlantBomb(true);
}