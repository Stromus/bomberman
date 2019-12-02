/*
** EPITECH PROJECT, 2021
** indie_studio
** File Description:
** Created by simong,
*/
#ifndef INDIE_STUDIO_ABOMB_HPP
#define INDIE_STUDIO_ABOMB_HPP

#include <string>
#include "engine/game/bomb/IBomb.hpp"

namespace engine {
	class ABomb : public IBomb {
	public:
		explicit ABomb(const short &memberShipPlayer);
		~ABomb() override = default;

		bombStatus	getStatus() override;
		short		getRange() override;
		Vector2<size_t> getPosition() override;
		std::string	getMeshName() override;
		bombType	getType() override;
		std::wstring	getTypeName() override;
		short	getMemberShipPlayer() override;

		void	setStatus(bombStatus status) final;
		void	setRange(short range) final;
		void	setPosition(Vector2<size_t> position) final;
		virtual IBomb *clone();

	protected:
		bool		_pierceBloc;
		bombStatus	_status;
		short		_range;
		Vector2<size_t>	_position;
		std::string	_meshName;
		bombType	_type;
		short		_playerMemberShip;
	};
}

#endif /* !INDIE_STUDIO_ABOMB_HPP */
