/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_IBOMB_HPP
#define INDIE_STUDIO_IBOMB_HPP

#include <iostream>
#include "template/Vector.hpp"

namespace engine {
	class IBomb {
	public:
		enum bombType {
			SIMPLE_BOMB,
			P_BOMB,
			G_BOMB,
			LAVA_BOMB
		};

		enum bombStatus {
			DESTROYED,
			UNUSED,
			LAID
		};

		virtual ~IBomb() = default;

		virtual bombStatus	getStatus() = 0;
		virtual short		getRange() = 0;
		virtual Vector2<size_t> getPosition() = 0; //Position inutile ?
		virtual std::string	getMeshName() = 0;
		virtual bombType	getType() = 0;
		virtual std::wstring	getTypeName() = 0;
		virtual short		getMemberShipPlayer() = 0;
		virtual void		setStatus(bombStatus status) = 0;
		virtual void		setRange(short range) = 0;
		virtual void		setPosition(Vector2<size_t>) = 0; //same
		virtual IBomb		*clone() = 0;
	};
}

#endif //INDIE_STUDIO_IBOMB_HPP
