/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_CHUNKBOMB_HPP
#define INDIE_STUDIO_CHUNKBOMB_HPP

#include "engine/game/bomb/IBomb.hpp"
#include "engine/game/arena/AChunk.hpp"

namespace engine {
	class ChunkBomb : public AChunk {
	public:
		ChunkBomb(IBomb *_bomb, const irr::core::vector3df &pos);
		~ChunkBomb() final;

		bool	isExplosed() noexcept;
		IBomb	*getBomb() const noexcept;
		void	stop() final;
		void	explosedFaster();
		int		getTickID();
		void setNbTotalTick(int tick) noexcept;
		int getNbTotalTick() const noexcept;

	private:
		IBomb			*_bomb;
		int			_tickID;
		render::MeshNode	*_meshBomb;
		int			_nbTotalTick;
	};
}

#endif //INDIE_STUDIO_CHUNKBOMB_HPP