/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <sound/Noise.hpp>
#include "engine/game/power_up/PUQuantityDown.hpp"

engine::PUQuantityDown::PUQuantityDown()
	: APowerUp(QUANTITY_DOWN)
{
	_meshName = "PUQuantityDown";
}

void engine::PUQuantityDown::capacityActivation(engine::IPlayer *player)
{
	Noise::getInstance()->play(Noise::BAD_POWER_UP);
	if (player->getBombQuantity() == 1)
		return;
	player->setBombQuantity(player->getBombQuantity() - static_cast<short>(1));
}