/*
** EPITECH PROJECT, 2021
** indie_studio
** File Description:
** Created by simong,
*/

#include <settings/Settings.hpp>
#include "engine/game/player/Human.hpp"

engine::Human::Human(
	const engine::IPlayer::playerType &type,
	const short &id, const Vector2<float> &pos, const std::string &meshName)
	: APlayer(type, id, pos, meshName)
{
	_meshNode = Irrlicht::getInstance()->createMesh(
		meshName, {pos.x, 1, pos.y}, irr::core::vector3df(1, 1, 1)
	);
}

void engine::Human::updatePlayer(const std::vector<std::vector<engine::IChunk *>> &map,\
					const std::vector<engine::IPlayer *> &players)
{
	for (auto key = Controls::keyIS::KEY_A; key != Controls::keyIS::MAX_KEY;\
	key = static_cast<Controls::keyIS>(static_cast<int>(key + 1))) {
		Controls::actions action = Settings::getInstance()->getAction(key, _type);
		if (action == Controls::actions::UNDEFINED ||
			!Controls::getInstance()->isKeyPressed(key))
			continue;
		createRequest(action);
	}
	if (_capacity == capacity::AUTOBOMB)
		_requests.push({Controls::actions::BOMB, {_position.x + 0.5f, _position.y + 0.5f}});
	if (_requests.empty())
		_meshNode->switchAnimation(render::MeshNode::IDLE);
	else
		_meshNode->switchAnimation(render::MeshNode::WALK);
}