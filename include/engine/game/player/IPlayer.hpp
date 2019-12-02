/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_IPLAYER_HPP
#define INDIE_STUDIO_IPLAYER_HPP

#include <vector>
#include <string>
#include "engine/game/arena/IChunk.hpp"
#include "template/Vector.hpp"
#include "engine/game/bomb/IBomb.hpp"
#include "settings/Controls.hpp"

namespace engine {
	class IPlayer {
	public:
		enum playerType {
			AI = 0,
			PLAYER1,
			PLAYER2
		};

		enum capacity {
			NONE = 0,
			SHIELD,
			GHOST,
			INVERT_CONTROL,
			AUTOBOMB
		};
		struct stats {
			short	bombQuantity;
			short	fireRange;
			short	speed;
		};

		struct request {
			Controls::actions	action;
			Vector2<float>		requestPos;
		};

		virtual ~IPlayer() = default;
		/* getters */
		virtual playerType	getType() const = 0;
		virtual std::wstring	getTypeName() const = 0;
		virtual short	getBombQuantity() const = 0;
		virtual short	getFireRange() const = 0;
		virtual short	getSpeed() const = 0;
		virtual short	getNbLife() const = 0;
		virtual short	getTeam() const = 0;
		virtual std::wstring	getTeamName() const = 0;
		virtual int	getTargetRotation() const = 0;
		virtual capacity getCapacity() const = 0;
		virtual std::wstring getCapacityName() const = 0;
		virtual IBomb	*getBomb() const = 0;
		virtual bool	isCollisionActivate() const = 0;
		virtual bool	isControlInverted() const = 0;
		virtual bool	isPlantBombActivate() const = 0;
		virtual Vector2<float>	getPosition() const = 0;
		virtual playerType	getPlayerType() const = 0;
		virtual short		getPlayerID() const = 0;
		virtual const std::string getMeshName() const = 0;
		virtual std::queue<engine::IPlayer::request>	&getPlayerRequests() = 0;
		/* setters */
		virtual void	setTeam(playerType value) = 0;
		virtual void	setBombQuantity(short value) = 0;
		virtual void	setFireRange(short value) = 0;
		virtual void	setSpeed(short value) = 0;
		virtual void	setNbLife(short value) = 0;
		virtual void	setTeam(short value) = 0;
		virtual void	setCapacity(capacity value) = 0;
		virtual void	setBomb(IBomb *bomb) = 0;
		virtual void	setCollision(bool collision) = 0;
		virtual void	setInvertControl(bool control) = 0;
		virtual void	setPlantBomb(bool plant) = 0;
		virtual void	setPosition(Vector2<float> pos) = 0;
		virtual void	update(const std::vector<std::vector<engine::IChunk *>> &map, const std::vector<IPlayer *> &players) = 0;
		virtual void	updatePlayer(const std::vector<std::vector<engine::IChunk *>> &map, const std::vector<IPlayer *> &players) = 0;
		virtual void	createRequest(Controls::actions action) = 0;
		virtual void	setThen(irr::u32 then) = 0;
		virtual void	setTargetRotation(int targetRotation) = 0;
		virtual void	setRotationSpeed(int rotationSpeed) = 0;
		virtual void	putBomb() = 0;
		virtual void	stop() = 0;
	};
}

#endif //INDIE_STUDIO_IPLAYER_HPP
