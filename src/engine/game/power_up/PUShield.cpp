/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <sound/Noise.hpp>
#include "engine/game/power_up/PUShield.hpp"

engine::PUShield::PUShield()
	: APowerUp(SHIELD)
{
	_meshName = "PUShield";
}

void engine::PUShield::capacityActivation(engine::IPlayer *player)
{
	Noise::getInstance()->play(Noise::GOOD_POWER_UP);
	player->setInvertControl(false);
	player->setPlantBomb(false);
	player->setCollision(true);
	player->setCapacity(IPlayer::capacity::SHIELD);
	player->setNbLife(player->getNbLife() + static_cast<short>(1));
}