/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_CHUNKUNBREAKABLE_HPP
#define INDIE_STUDIO_CHUNKUNBREAKABLE_HPP

#include "engine/game/arena/AChunk.hpp"

namespace engine {
	class ChunkUnbreakable : public AChunk {
	public:
		ChunkUnbreakable(const irr::core::vector3df &pos);
		~ChunkUnbreakable() final;
		void	stop() final;

	private:
		render::MeshNode	*_bloc;
	};
}
#endif //INDIE_STUDIO_CHUNKUNBREAKABLE_HPP
