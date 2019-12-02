/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_APLAYER_HPP
#define INDIE_STUDIO_APLAYER_HPP

#include <vector>
#include <string>
#include <engine/game/arena/IChunk.hpp>
#include "template/Vector.hpp"
#include "render/MeshNode.hpp"
#include "engine/game/player/IPlayer.hpp"

namespace engine {
	class APlayer : public IPlayer {
	public:
		explicit APlayer(const playerType &type, const short &ID, const Vector2<float> &pos,
			const std::string &meshName);
		~APlayer() override = default;
		/* setters */
		void	setTeam(playerType value) override;
		void	setBombQuantity(short value) override;
		void	setFireRange(short value) override;
		void	setSpeed(short value) override;
		void	setNbLife(short value) override;
		void	setTeam(short value) override;
		void	setCapacity(capacity value) override;
		void	setBomb(IBomb *bomb) override;
		void	setCollision(bool collision) override;
		void	setInvertControl(bool control) override;
		void	setPlantBomb(bool plant) override;
		void	setPosition(Vector2<float> pos) override;
		void	setThen(irr::u32 then) override;
		void	setTargetRotation(int targetRotation) override;
		void	setRotationSpeed(int rotationSpeed) override;
		/* getters */
		playerType	getPlayerType() const override;
		short		getPlayerID() const override;
		std::queue<engine::IPlayer::request>	&getPlayerRequests() override;
		playerType	getType() const override;
		std::wstring	getTypeName() const override;
		short	getBombQuantity() const override;
		short	getFireRange() const override;
		short	getSpeed() const override;
		short	getNbLife() const override;
		short	getTeam() const override;
		std::wstring	getTeamName() const override;
		int		getTargetRotation() const override;
		capacity getCapacity() const override;
		std::wstring	getCapacityName() const override;
		const std::string getMeshName() const override;
		IBomb	*getBomb() const override;
		bool	isCollisionActivate() const override;
		bool	isControlInverted() const override;
		bool	isPlantBombActivate() const override;
		Vector2<float>	getPosition() const override;

		void	createRequest(Controls::actions action) final;
		void	update(const std::vector<std::vector<engine::IChunk *>> &map, const std::vector<IPlayer *> &players) override;
		void	updatePlayer(const std::vector<std::vector<engine::IChunk *>> &map, const std::vector<IPlayer *> &players) override;

		void putBomb() override;
		void stop() override;

	protected:
		playerType	_type;
		stats		_stats;
		short		_nbLife;
		short		_team;
		short		_playerID;
		bool		_checkCollision;
		bool		_invertedControl;
		bool		_plantBomb;
		capacity	_capacity;
		IBomb		*_bomb;
		std::string	_pseudonyme;
		render::MeshNode	*_meshNode;
		Vector2<float>		_position;
		size_t			_movementSpeed;
		irr::u32		_then;
		std::queue<engine::IPlayer::request>	_requests;
		int		_targetRotation;
		int		_rotationSpeed;
		irr::f32	_frameDeltaTime;
		const std::string _meshName;
	};
}
#endif //INDIE_STUDIO_APLAYER_HPP
