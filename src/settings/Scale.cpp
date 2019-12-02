/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include "template/Vector.hpp"
#include "settings/Settings.hpp"
#include "settings/Scale.hpp"

irr::core::rect<irr::s32> Scale::scaleRes(irr::s32 x, irr::s32 y, irr::s32 x2, irr::s32 y2)
{
	Vector2<size_t> res = Settings::getInstance()->getResolution();

	auto	resX = static_cast<float>(res.x);
	auto	resY = static_cast<float>(res.y);
	return {static_cast<irr::s32 >((resX / 1920.0) * x), static_cast<irr::s32 >((resY / 1080.0) * y),\
	static_cast<irr::s32 >((resX / 1920.0) * x2), static_cast<irr::s32 >((resY / 1080.0) * y2)};
}
