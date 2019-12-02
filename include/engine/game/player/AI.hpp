/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_AI_HPP
#define INDIE_STUDIO_AI_HPP

#include <stack>
#include "engine/game/arena/ChunkBomb.hpp"
#include "engine/game/player/APlayer.hpp"

namespace engine {
	class AI : public APlayer {
	public:
		AI(const short &ID, const Vector2<float> &pos, const std::string &meshName);
		~AI() final = default;

	public:
		void	updatePlayer(const std::vector<std::vector<engine::IChunk *>> &map,\
		const std::vector<IPlayer *> &players) final;

	private:
		struct objectif {
			float	x;
			float	y;
			int	range;
		};

		enum breadthType {
			BREADTH_SAFE_ZONE,
			BREADTH_BLOC,
			BREADTH_PLAYERS,
			BREADTH_POWER_UP
		};

		enum objectifType {
			NOTHING = 0,
			SURVIVE_FROM_EXPLS,
			PLAYER_TO_KILL,
			BLOC_TO_DESTROY,
			POWER_UP_TO_TAKE
		};

		void	calculExplosionRange(const std::vector<std::vector<engine::IChunk *>> &map, int i,\
		int j, IBomb *bomb, short dir);
		void	addExplosionRangeToExplosionMap(const std::vector<std::vector<engine::IChunk *>> &map, int i,\
		int j, const ChunkBomb *chunk);
		void	initializeCollisionMap(const std::vector<std::vector<engine::IChunk *>> &map);
		void	initializeExplosionMap(const std::vector<std::vector<engine::IChunk *>> &map);
		void	updateCollisionMap(const std::vector<std::vector<engine::IChunk *>> &map);
		void	updateExplosionMap(const std::vector<std::vector<engine::IChunk *>> &map);

	private:
		void	breadthAlgorithm(const breadthType &type, int rangeMax);
		void	beginAIAlgorithm(const std::vector<IPlayer *> &players);
		void	createNewObjectif(const std::vector<IPlayer *> &players);
		void	createNewRequestFromObjectif(const std::vector<IPlayer *> &players);
		bool	amISafe();
		bool	canGoOnThisChunk(float x, float y);
		bool	AmISafeOnThisChunk(float x, float y);

		int	getMinValueInAllPaths(int rangeMax);
		void	checkStopCondition(std::queue<objectif> obj, float x, float y, int range, const breadthType &type);
		bool	foundEnemyPlayer(float x, float y);
		bool	foundGoodPowerUp(float x, float y);

	private:
		std::vector<std::vector<bool>>	_collisionMap;
		std::vector<std::vector<bool>>	_explosionMap;
		objectifType			_currentObj;
		std::queue<objectif>		_positionToReach;
		std::queue<std::queue<objectif>>	_paths;
		std::vector<std::vector<engine::IChunk *>> _map;
		std::vector<IPlayer *> 			_players;
		Vector2<float>				_ancientPos;
		std::vector<std::queue<objectif>>	_validPaths;
	};
}
#endif //INDIE_STUDIO_AI_HPP
