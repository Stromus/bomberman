/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include "engine/game/arena/ChunkEmpty.hpp"

engine::ChunkEmpty::ChunkEmpty(const irr::core::vector3df &pos)
	: AChunk(IChunk::EMPTY, pos)
{}