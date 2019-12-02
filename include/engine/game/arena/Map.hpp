/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_MAP_HPP
#define INDIE_STUDIO_MAP_HPP

#include <vector>
#include <string>
#include "engine/game/player/IPlayer.hpp"
#include "engine/game/arena/IChunk.hpp"
#include "engine/game/arena/ChunkBomb.hpp"
#include "template/Vector.hpp"

namespace engine {
	class Map {
	public:
		enum generate {
			GENERATE_MAP = 0,
			NOT_GENERATE_MAP
		};

		enum direction {
			NORTH = 0,
			EAST,
			SOUTH,
			WEST
		};
		enum Side {
			NORTH_WEST = 0,
			NORTH_EAST,
			SOUTH_WEST,
			SOUTH_EAST
		};

		explicit Map(const generate &gen);
		~Map();

		IChunk	*generateNewChunk(size_t y, size_t x);
		IChunk	*generateRandomChunk(size_t y, size_t x);
		bool	checkSide(size_t y, size_t x, Side side);
		bool	isBorderMap(size_t y, size_t x);
		bool	isPlayerEmplacement(size_t y, size_t x);
		bool	isIndestructiblePosition(size_t y, size_t x);

		void	setMapSize(Vector2<size_t> size);

		void	update(std::map<short, short> &quantity, std::vector<engine::IPlayer *> &players);
		void	updateMapWithBombExplosion(ChunkBomb *chunk, std::vector<engine::IPlayer *> &players);
		void	updateDirectionExplosion(short range, Vector2<int> pos, const direction &dir,\
		const IBomb::bombType &type, std::vector<engine::IPlayer *> &players);
		std::vector<std::vector<IChunk *>>	&getMap();
		void	analyseNewRequest(const IPlayer::request &req, IPlayer *player, const std::map<short, short> &quantity);
		bool	analyseCollision(const engine::IPlayer::request &req, const IChunk::chunkType &type,  const Controls::actions &side);
		bool	isMapValid();

	private:
		std::vector<std::vector<IChunk *>>	_map;
		Vector2<size_t>	_mapSize;
	};
}
#endif //INDIE_STUDIO_MAP_HPP
