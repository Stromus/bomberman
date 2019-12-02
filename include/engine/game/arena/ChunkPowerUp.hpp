/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_CHUNKPOWERUP_HPP
#define INDIE_STUDIO_CHUNKPOWERUP_HPP

#include "engine/game/power_up/IPowerUp.hpp"
#include "engine/game/arena/AChunk.hpp"

namespace engine {
	class ChunkPowerUp : public AChunk {
	public:
		ChunkPowerUp(const irr::core::vector3df &pos,
			engine::IPowerUp::PowerUpType powerUpType = engine::IPowerUp::RANDOM);
		~ChunkPowerUp() final;

	public:
		IPowerUp	*getPowerUp() noexcept;
		void	stop() final;

	private:
		void	createCapacityPU() noexcept;
		void	createStatsPU() noexcept;
		void	createSpecialPU() noexcept;
		void	createBonusStats() noexcept;
		void	createMalusStats() noexcept;
		void	createBombPU() noexcept;

	private:
		IPowerUp		*_powerUp;
		render::MeshNode	*_meshPowerUp;
	};
}

#endif //INDIE_STUDIO_CHUNKPOWERUP_HPP
