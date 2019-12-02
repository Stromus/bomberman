/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_ICHUNK_HPP
#define INDIE_STUDIO_ICHUNK_HPP

#include "render/Irrlicht.hpp"

namespace engine {
	class IChunk {
	public:
		virtual ~IChunk() = default;
	public:
		enum chunkType {
			BREAKABLE = 0,
			UNBREAKABLE,
			POWERUP,
			BOMB,
			EMPTY
		};
	public:
		/* getters */
		virtual bool	isBreakable() = 0;
		virtual irr::core::vector3df	getPosition() = 0;
		virtual std::string	getMeshName() = 0;
		virtual chunkType	getType() = 0;

		/* setters */
		virtual void	setBreakable(bool &breakable) = 0;
		virtual void	setPosition(irr::core::vector3df &position) = 0;
		virtual void	stop() = 0;
	};
}

#endif //INDIE_STUDIO_ICHUNK_HPP
