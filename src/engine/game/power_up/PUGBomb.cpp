/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <sound/Noise.hpp>
#include "engine/game/bomb/GBomb.hpp"
#include "engine/game/power_up/PUGBomb.hpp"

engine::PUGBomb::PUGBomb()
	: APowerUp(IPowerUp::PowerUpType::G_BOMB)
{
	_meshName = "PUGBomb";
}

void engine::PUGBomb::capacityActivation(engine::IPlayer *player)
{
	Noise::getInstance()->play(Noise::GOOD_POWER_UP);
	if (player->getBomb()->getType() == IBomb::bombType::G_BOMB)
		return;
	player->setBomb(new GBomb(player->getPlayerID()));
}