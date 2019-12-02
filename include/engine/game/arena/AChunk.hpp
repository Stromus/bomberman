/*
** EPITECH PROJECT, 2021
** indie_studio
** File Description:
** Created by simong,
*/
#ifndef INDIE_STUDIO_ACHUNK_HPP
#define INDIE_STUDIO_ACHUNK_HPP

#include "IChunk.hpp"

namespace engine {
	class AChunk : public IChunk {
	public:
		explicit AChunk(const chunkType &type, const irr::core::vector3df &pos);
		~AChunk() override;

	public:
		bool			isBreakable() override;
		irr::core::vector3df	getPosition() override;
		std::string			getMeshName() override;
		IChunk::chunkType	getType() override;

		void	setBreakable(bool &breakable) override;
		void	setPosition(irr::core::vector3df &position) override;
		void	stop() override;

	protected:
		bool			_breakable;
		std::string		_meshName;
		render::MeshNode	*_floor;
		irr::core::vector3df	_position;
		chunkType		_type;
	};
}

#endif /* !INDIE_STUDIO_ACHUNK_HPP */
