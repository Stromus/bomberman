/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by Stromus,
*/

#ifndef INDIE_STUDIO_MESHNODEFACTORY_HPP
#define INDIE_STUDIO_MESHNODEFACTORY_HPP

#include <iostream>
#include <map>
#include <vector>

namespace render {
	class MeshNode;
}

#include "MeshNode.hpp"

namespace render {

	class MeshNodeFactory {
	public:
		MeshNodeFactory();
		MeshNodeFactory(const MeshNodeFactory &factory) = delete;
		MeshNodeFactory(MeshNodeFactory &&factory) = delete;
		MeshNodeFactory &operator=(const MeshNodeFactory &factory) = delete;

		void addMeshNode(std::string name, std::string meshFile, std::vector<std::string> textureFile);
		render::MeshNode *getMeshNode(std::string name);
		void readMeshFile(std::string fileName);

	private:
		std::map<std::string, render::MeshNode *> _factory;
	};

};

#endif