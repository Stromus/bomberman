/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

#include "exception/IndieStudioException.hpp"
#include "render/Irrlicht.hpp"
#include "render/EventReceiver.hpp"
#include "render/Animator.hpp"
#include "settings/Settings.hpp"

Irrlicht	*Irrlicht::singleton = nullptr;

Irrlicht *Irrlicht::getInstance()
{
	if (singleton == nullptr)
		singleton = new Irrlicht();
	return singleton;
}

irr::IrrlichtDevice * Irrlicht::getDevice()
{
	return _device;
}

irr::video::IVideoDriver * Irrlicht::getVideo()
{
	return _video;
}

irr::scene::ISceneManager * Irrlicht::getSceneManager()
{
	return _scene;
}

irr::gui::IGUIEnvironment * Irrlicht::getGUIEnv()
{
	return _env;
}

irr::IEventReceiver * Irrlicht::getEvent()
{
	return _event;
}

bool Irrlicht::isDrawingScene3D()
{
	return _drawScene3D;
}

bool Irrlicht::isDispatchingKey()
{
	return _dispatchKey;
}

void Irrlicht::setDevice(irr::IrrlichtDevice * device)
{
	_device = device;
}

void Irrlicht::setVideo(irr::video::IVideoDriver * video)
{
	_video = video;
}

void Irrlicht::setSceneManager(irr::scene::ISceneManager * scene)
{
	_scene = scene;
}

void Irrlicht::setGUIEnv(irr::gui::IGUIEnvironment * env)
{
	_env = env;
}

void Irrlicht::setEvent(irr::IEventReceiver * event)
{
	_event = event;
	_device->setEventReceiver(_event);
}

void Irrlicht::setDrawScene3D(bool drawScene3D)
{
	_drawScene3D = drawScene3D;
}

void Irrlicht::setDispatchKey(bool dispatchKey)
{
	_dispatchKey = dispatchKey;
}

void Irrlicht::draw()
{
	_video->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
	if (_drawScene3D)
		_scene->drawAll();
	_env->drawAll();
	_video->endScene();
	const irr::s32 fps = _video->getFPS();
	irr::core::stringw str = L"Indie Studio [";
	str += _video->getName();
	str += "] FPS:";
	str += fps;
	_device->setWindowCaption(str.c_str());
}

void Irrlicht::loadMeshFactory()
{
	if (_factory == nullptr)
		_factory = new render::MeshNodeFactory();
}

render::MeshNode * Irrlicht::createMesh(std::string name, irr::core::vector3df pos, irr::core::vector3df scale)
{
	render::MeshNode *mesh = _factory->getMeshNode(name);

	if (!mesh)
		return nullptr;
	mesh->getNode()->setPosition(pos);
	mesh->getNode()->setScale(scale);
	return mesh;
}

void Irrlicht::removeStartScreen()
{
	_startScreen->remove();
}

Irrlicht::Irrlicht()
{
	Settings *settings = Settings::getInstance();
	auto dim = settings->getResolution();
	_device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(dim.x, dim.y), 16, settings->isFullScreen());
	if (_device == nullptr)
		throw ise::IndieStudioException(ise::CRITICAL, "failed to create device");
	_device->setWindowCaption(L"Indie Studio");
	_video = _device->getVideoDriver();
	_scene = _device->getSceneManager();
	_env = _device->getGUIEnvironment();
	_event = _device->getEventReceiver();
	_drawScene3D = false;
	_dispatchKey = false;
	_factory = nullptr;
	setEvent(new render::EventReceiver());
	_startScreen = _env->addImage({ 0, 0, static_cast<irr::s32>(dim.x), static_cast<irr::s32>(dim.y) }, 0, -1, L"", true);
	_startScreen->setScaleImage(true);
	_startScreen->setImage(_video->getTexture("res/sprite/img/first_screen.jpg"));
	draw();
}
