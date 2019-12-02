/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_IRRLICHT_HPP
#define INDIE_STUDIO_IRRLICHT_HPP

#include <irrlicht.h>

namespace render {
	class MeshNodeFactory;
}

#include "MeshNodeFactory.hpp"

class Irrlicht {
public:
	/* Set Irrlicht uncopiable */
	Irrlicht(const Irrlicht &irrlicht) = delete;
	Irrlicht(Irrlicht &&Irrlicht) = delete;
	Irrlicht& operator=(const Irrlicht &fpsControl) = delete;

public:
	/* Get instance of Irrlicht */
	static Irrlicht	*getInstance();

	/* Getter */
	irr::IrrlichtDevice *getDevice();
	irr::video::IVideoDriver *getVideo();
	irr::scene::ISceneManager *getSceneManager();
	irr::gui::IGUIEnvironment *getGUIEnv();
	irr::IEventReceiver *getEvent();
	bool isDrawingScene3D();
	bool isDispatchingKey();

	/* Setter */
	void setDevice(irr::IrrlichtDevice *device);
	void setVideo(irr::video::IVideoDriver *video);
	void setSceneManager(irr::scene::ISceneManager *scene);
	void setGUIEnv(irr::gui::IGUIEnvironment *env);
	void setEvent(irr::IEventReceiver *event);
	void setDrawScene3D(bool drawScene3D);
	void setDispatchKey(bool dispatchKey);

	void loadMeshFactory();
	render::MeshNode *createMesh(std::string name, irr::core::vector3df pos, irr::core::vector3df scale);
	void draw();
	void removeStartScreen();

private:
	explicit Irrlicht();
	static Irrlicht	*singleton;

private:
	irr::IrrlichtDevice *_device;
	irr::video::IVideoDriver *_video;
	irr::scene::ISceneManager *_scene;
	irr::gui::IGUIEnvironment *_env;
	irr::IEventReceiver *_event;
	render::MeshNodeFactory *_factory;
	bool _drawScene3D;
	bool _dispatchKey;
	irr::gui::IGUIImage *_startScreen;
};

#endif //INDIE_STUDIO_IRRLICHT_HPP
