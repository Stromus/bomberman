/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_SCALE_HPP
#define INDIE_STUDIO_SCALE_HPP

#include <irrTypes.h>
#include <rect.h>

class Scale {
public:
	Scale() = default;
	~Scale() = default;

	static irr::core::rect<irr::s32> scaleRes(irr::s32 x, irr::s32 y, irr::s32 x2, irr::s32 y2);
};
#endif //INDIE_STUDIO_SCALE_HPP
