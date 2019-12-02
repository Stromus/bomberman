/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_IGAMEMODE_HPP
#define INDIE_STUDIO_IGAMEMODE_HPP

#include "engine/game/player/IPlayer.hpp"

namespace engine {
	class IGameMode {
	public:
		virtual ~IGameMode() = default;

		virtual bool	isAllDestructible() const noexcept = 0;
		virtual bool	isNoWall() const noexcept = 0;
		virtual bool	isInverted() const noexcept = 0;
		virtual bool	isBetterBomb() const noexcept = 0;
		virtual bool	isGhost() const noexcept = 0;
		virtual bool	isCastle() const noexcept = 0;
		virtual bool	isCustomStats() const noexcept = 0;
		virtual IPlayer::stats	getCustomStats() const noexcept = 0;
	};
}

#endif //INDIE_STUDIO_IGAMEMODE_HPP
