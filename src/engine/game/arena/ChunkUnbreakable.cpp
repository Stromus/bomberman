/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include "engine/game/arena/ChunkUnbreakable.hpp"

engine::ChunkUnbreakable::ChunkUnbreakable(const irr::core::vector3df &pos)
	: AChunk(IChunk::UNBREAKABLE, pos)
{
	_bloc = Irrlicht::getInstance()->createMesh("CubeB", pos, irr::core::vector3df(1, 1, 1));
}

engine::ChunkUnbreakable::~ChunkUnbreakable()
{}

void engine::ChunkUnbreakable::stop()
{
	_bloc->getNode()->remove();
	AChunk::stop();
}
