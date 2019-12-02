/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by Stromus,
*/

#include "exception/IndieStudioException.hpp"
#include "render/MeshNode.hpp"
#include "open_target/File.hpp"

render::MeshNode::MeshNode(std::string meshFile, std::vector<std::string> &textureFile)
	: _meshName(meshFile),
	_node(nullptr),
	_mesh(nullptr),
	_animation(NONE),
	_transition(false)
{
	Irrlicht *singleton = Irrlicht::getInstance();

	_mesh = singleton->getSceneManager()->getMesh(meshFile.c_str());
	if (!_mesh)
		throw ise::IndieStudioException(ise::WARNING, "failed to load mesh");
	_node = singleton->getSceneManager()->addAnimatedMeshSceneNode(_mesh);
	if (!_node)
		throw ise::IndieStudioException(ise::WARNING, "failed to load meshNode");
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	if (meshFile == "res/assets/anim/BB8.x" && textureFile.size() == 2) {
		_node->getMaterial(0).setTexture(0, singleton->getVideo()->getTexture(textureFile[1].c_str()));
		_node->getMaterial(1).setTexture(0, singleton->getVideo()->getTexture(textureFile[1].c_str()));
		_node->getMaterial(2).setTexture(0, singleton->getVideo()->getTexture(textureFile[1].c_str()));
		_node->getMaterial(3).setTexture(0, singleton->getVideo()->getTexture(textureFile[0].c_str()));
		_node->getMaterial(4).setTexture(0, singleton->getVideo()->getTexture(textureFile[0].c_str()));
	} else {
		_node->setMaterialTexture(0, singleton->getVideo()->getTexture(textureFile[0].c_str()));
	}
	_node->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
	_node->setVisible(false);
	_type = render::MeshNode::TypeMeshNode::MODEL;
}

render::MeshNode::~MeshNode()
{
	if (_type != MODEL)
		_node->remove();
}

render::MeshNode *render::MeshNode::clone()
{
	return new render::MeshNode(*this);
}

render::MeshNode::MeshNode(const MeshNode & node)
{
	_meshName = node._meshName;
	_type = render::MeshNode::TypeMeshNode::NODE;
	_mesh = node._mesh;
	_node = static_cast<irr::scene::IAnimatedMeshSceneNode *>(node._node->clone());
	initAnimation();
	_node->setVisible(true);
}

render::MeshNode & render::MeshNode::operator=(const MeshNode & node)
{
	if (this == &node)
		return *this;
	_meshName = node._meshName;
	_type = render::MeshNode::TypeMeshNode::NODE;
	_mesh = node._mesh;
	_node = static_cast<irr::scene::IAnimatedMeshSceneNode *>(node._node->clone());
	initAnimation();
	_node->setVisible(true);
	return *this;
}

irr::scene::IAnimatedMeshSceneNode * render::MeshNode::getNode()
{
	return _node;
}

irr::scene::IAnimatedMesh * render::MeshNode::getMesh()
{
	return _mesh;
}

void render::MeshNode::initAnimation()
{
	std::string file = _meshName;

	if (_meshName.compare(_meshName.length() - 2, 2, ".x") == 0) {
		_node->setRotation({ 0, 180, 0 });
		file.replace(_meshName.length() - 2, 2, "_anim.txt");
		File anim(file, File::F_IN);
		auto stream = anim.getContent();
		std::string tmp;
		int i = 0;

		while (getline(stream, tmp)) {
			_animationFrame.insert({ static_cast<render::MeshNode::Animation>(i), std::pair<int, int>(std::stoi(tmp.substr(0, tmp.find(","))), std::stoi(tmp.substr(tmp.find(",") + 1))) });
			i++;
		}
		setAnimation(IDLE);
		_animation = IDLE;
		_transition = false;
	}
}

void render::MeshNode::setAnimation(render::MeshNode::Animation animation)
{
	std::pair<int, int> frame;
	try {
		frame = _animationFrame.at(animation);
	}
	catch (std::out_of_range e) {
		return;
	}
	_node->setFrameLoop(frame.first, frame.second);
}

void render::MeshNode::switchAnimation(render::MeshNode::Animation animation)
{
	if (_animation != animation && _transition == false) {
		setAnimation(static_cast<render::MeshNode::Animation>(_animation + 2));
		_node->setAnimationSpeed(120);
		_transition = true;
		_node->setLoopMode(false);
	} else if (_animation != animation && _transition == true) {
		if (_node->getFrameNr() >= _animationFrame[static_cast<render::MeshNode::Animation>(_animation + 2)].second) {
			setAnimation(animation);
			_animation = animation;
			_transition = false;
			_node->setLoopMode(true);
			_node->setAnimationSpeed(30);
		}
	} else if (_animation == animation && _transition == true) {
		int frame = _node->getFrameNr() - _animationFrame[static_cast<render::MeshNode::Animation>(_animation + 2)].first;
		_animation = static_cast<render::MeshNode::Animation>(!(_animation));
		setAnimation(static_cast<render::MeshNode::Animation>(_animation + 2));
		_node->setAnimationSpeed(120);
		_node->setCurrentFrame(_animationFrame[static_cast<render::MeshNode::Animation>(_animation + 2)].second - frame);
	}
}




