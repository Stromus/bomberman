/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_CHUNKEMPTY_HPP
#define INDIE_STUDIO_CHUNKEMPTY_HPP

#include "engine/game/arena/AChunk.hpp"

namespace engine {
	class ChunkEmpty : public AChunk {
	public:
		explicit ChunkEmpty(const irr::core::vector3df &pos);
		~ChunkEmpty() final = default;
	};
}

#endif //INDIE_STUDIO_CHUNKEMPTY_HPP
