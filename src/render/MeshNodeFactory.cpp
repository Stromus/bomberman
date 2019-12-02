/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by Stromus,
*/

#include "exception/IndieStudioException.hpp"
#include "render/MeshNodeFactory.hpp"
#include "open_target/File.hpp"

render::MeshNodeFactory::MeshNodeFactory()
{
	readMeshFile("res/assets/assets.txt");
}

void render::MeshNodeFactory::addMeshNode(std::string name, std::string meshFile, std::vector<std::string> textureFile)
{
	if (_factory.find(name) != _factory.end()) {
		throw ise::IndieStudioException(ise::WARNING, "mesh already loaded");
	}
	_factory[name] = new render::MeshNode(meshFile, textureFile);
}

render::MeshNode *render::MeshNodeFactory::getMeshNode(std::string name)
{
	auto it = _factory.find(name);
	if (it == _factory.end()) {
		throw ise::IndieStudioException(ise::CRITICAL, "unknown mesh");
	}
	return it->second->clone();
}

void render::MeshNodeFactory::readMeshFile(std::string fileName)
{
	File file(fileName, File::fileMode::F_IN);
	std::string line;
	auto stream = file.getContent();

	while (std::getline(stream, line)) {
		std::stringstream sstream(line);
		std::string name;
		std::string meshfile;
		std::string tmp;
		std::vector<std::string> textureFile;

		std::getline(sstream, name, ':');
		std::getline(sstream, meshfile, ':');
		while (std::getline(sstream, tmp, ':'))
			textureFile.push_back(tmp);
		addMeshNode(name, meshfile, textureFile);
	}
}