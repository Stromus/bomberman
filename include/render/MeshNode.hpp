/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by Stromus,
*/

#ifndef INDIE_STUDIO_MESHNODE_HPP
#define INDIE_STUDIO_MESHNODE_HPP

#include "Irrlicht.hpp"
#include <string>
#include <vector>

namespace render {
	
	class MeshNode {
	public:
		enum TypeMeshNode {
			MODEL,
			NODE,
		};

		enum Animation {
			NONE = -1,
			IDLE = 0,
			WALK,
			IDLE_TO_WALK,
			WALK_TO_IDLE,
		};

	public:
		MeshNode(std::string meshFile, std::vector<std::string> &textureFile);
		~MeshNode();
		MeshNode(const MeshNode &node);
		MeshNode &operator=(const MeshNode &node);

		render::MeshNode *clone();

		irr::scene::IAnimatedMeshSceneNode *getNode();
		irr::scene::IAnimatedMesh *getMesh();

		void initAnimation();
		void setAnimation(enum Animation);
		void switchAnimation(enum Animation);

	private:
		std::string _meshName;
		TypeMeshNode _type;
		irr::scene::IAnimatedMesh *_mesh;
		irr::scene::IAnimatedMeshSceneNode *_node;
		Animation _animation;
		bool _transition;
		std::map<enum Animation, std::pair<int, int>> _animationFrame;
	};

};

#endif