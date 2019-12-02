/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_CHUNKBREAKABLE_HPP
#define INDIE_STUDIO_CHUNKBREAKABLE_HPP

#include "engine/game/arena/AChunk.hpp"

namespace engine {
	class ChunkBreakable : public AChunk {
	public:
		explicit ChunkBreakable(const irr::core::vector3df &pos);
		~ChunkBreakable() final;
		void	stop() final;

	private:
		render::MeshNode	*_bloc;
	};
}

#endif //INDIE_STUDIO_CHUNKBREAKABLE_HPP
