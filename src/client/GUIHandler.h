/*
 * GUI.h
 *
 *  Created on: Oct 10, 2012
 *      Author: Remco
 */
#pragma once
#ifndef GUIHANDLER_H_
#define GUIHANDLER_H_
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "SFGUI\SFGUI.hpp"
#include "SFGUI\Window.hpp"
#include "GUIChat.h"

class GUI;					//we don't include Client.h in the header file to prevent infinite recursion

class GUIHandler {
public:
	GUI *gui;
	GUIChat guiChat;

	GUIHandler() { };
	GUIHandler(GUI *_gui);
	~GUIHandler();
	void update();

private:
	void init();
};

#endif /* GUIHANDLER_H_ */
