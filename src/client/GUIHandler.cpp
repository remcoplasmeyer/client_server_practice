/*
 * GUI.cpp

 *
 *  Created on: Oct 10, 2012
 *      Author: Remco
 */

#include "../Log.h"
#include "GUI.h"
#include "GUIHandler.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "SFGUI\SFGUI.hpp"
#include "SFGUI\Window.hpp"

GUIHandler::GUIHandler(GUI *_gui) {
	this->gui = _gui;
	init();
}

void GUIHandler::init() {
	guiChat = GUIChat(this);
}

void GUIHandler::update() {
	this->gui->window->resetGLStates();
	this->guiChat.chatWindow->Update(0.f);
}


GUIHandler::~GUIHandler() {
	// TODO Auto-generated destructor stub
}

