/*
 * GUI.h
 *
 *  Created on: Febr 2, 2013
 *      Author: Remco
 */
#pragma once
#ifndef GUICHAT_H_
#define GUICHAT_H_
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "SFGUI\SFGUI.hpp"
#include "SFGUI\Window.hpp"

class GUIHandler;

class GUIChat {
public:
	GUIHandler *guiHandler;
	sfg::Window::Ptr chatWindow;
	sfg::Box::Ptr chatBox;			
	sfg::ScrolledWindow::Ptr scrolledwindow;	 //scrollable box inside window

	GUIChat() { };
	GUIChat(GUIHandler *_guiHandler);
	~GUIChat();
	void addChatLine(std::string text);
	void hide();
	void show();
	
private:
	void init();
	void moveToScreenBottom();
};

#endif /* GUICHAT_H_ */
