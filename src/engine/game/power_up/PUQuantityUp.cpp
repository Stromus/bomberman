/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <sound/Noise.hpp>
#include "engine/game/power_up/PUQuantityUp.hpp"

engine::PUQuantityUp::PUQuantityUp()
	: APowerUp(QUANTITY_UP)
{
	_meshName = "PUQuantityUp";
}

void engine::PUQuantityUp::capacityActivation(engine::IPlayer *player)
{
	Noise::getInstance()->play(Noise::GOOD_POWER_UP);
	player->setBombQuantity(player->getBombQuantity() + static_cast<short>(1));
}