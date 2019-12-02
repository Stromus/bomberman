/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_ILOADGAME_HPP
#define INDIE_STUDIO_ILOADGAME_HPP

#include <vector>

#include "engine/game/arena/Map.hpp"
#include "engine/game/player/IPlayer.hpp"
#include "engine/scene/IGuiScene.hpp"

#define SAVE_DIRECTORY "./.save/game/"

namespace engine {
	class LoadGame {
	public:
		LoadGame();
		~LoadGame();

		enum loadMode {
			LOAD = 0,
			SAVE
		};

		void		generateMap();
		void		cleanMap();
		void	updateGame(Controls::keyIS);
		void	loadFromSave(const std::string &file);
		void	saveGame(const std::string &file);
		unsigned long	getNbPlayers();
		void		cleanPlayers();
		void		addPlayer(engine::IPlayer *player);
		void	setMode(loadMode mode);
		loadMode	getMode();
		int	getWinner();
		void	updateWinner();
		
		const engine::IPlayer const* getPlayerByID(const short id) const;

	private:
		void	interpretPlayerBomb(std::map<std::wstring, std::wstring> playerDatas, engine::IPlayer *player);

		std::vector<std::map<std::wstring, std::wstring>> convertXmlToMap(const std::string &file);
		void loadPlayer(const std::map<std::wstring, std::wstring> &playerDatas);
		void loadSettings(const std::map<std::wstring, std::wstring> &playerDatas);
		void loadMap(std::map<std::wstring, std::wstring> &playerDatas);
		engine::IBomb *loadBomb(const std::map<std::wstring, std::wstring> &datas);

		void savePlayer(irr::io::IXMLWriter* xwriter);
		void saveStats(irr::io::IXMLWriter* xwriter, engine::IPlayer *player);
		void savePos(irr::io::IXMLWriter* xwriter, engine::IPlayer *player);
		void savePlayerBomb(irr::io::IXMLWriter* xwriter, engine::IPlayer *player);
		void saveGameSettings(irr::io::IXMLWriter* xwriter);
		void saveMap(irr::io::IXMLWriter* xwriter);

		loadMode _mode;

		engine::Map	*_map;
		std::vector<engine::IPlayer *> _players;
		std::map<short, short>	_quantityPerPlayer;
		int	_winnerID;
		int _nbChunk;
	};
}

#endif //INDIE_STUDIO_ILOADGAME_HPP
