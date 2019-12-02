/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_AGAMEMODE_HPP
#define INDIE_STUDIO_AGAMEMODE_HPP

#include "engine/game_mode/IGameMode.hpp"

namespace engine {
	class AGameMode : public IGameMode {
	public:
		explicit AGameMode();
		~AGameMode() override = default;

		bool	isAllDestructible() const noexcept final;
		bool	isNoWall() const noexcept final;
		bool	isInverted() const noexcept final;
		bool	isBetterBomb() const noexcept final;
		bool	isGhost() const noexcept final;
		bool	isCastle() const noexcept final;
		bool	isCustomStats() const noexcept final;
		IPlayer::stats	getCustomStats() const noexcept final;

	protected:
		bool		_allDestructible;
		bool		_noWall;
		bool		_invertControl;
		bool		_betterBomb;
		bool		_ghost;
		bool		_castle;
		IPlayer::stats	_stats;
	};
}
#endif //INDIE_STUDIO_AGAMEMODE_HPP
