/*
 * GUI.cpp

 *
 *  Created on: Oct 10, 2012
 *      Author: Remco
 */

#include "../Log.h"
#include "GUIHandler.h"
#include "GUIChat.h"
#include "GUI.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "SFGUI\SFGUI.hpp"
#include "SFGUI\Window.hpp"

GUIChat::GUIChat(GUIHandler *_guiHandler) {
	this->guiHandler = _guiHandler;
	init();
	show();
}

void GUIChat::init() {
	this->chatWindow = sfg::Window::Create();
	this->chatWindow->SetTitle("Chat");

	//// Create a box with 10 pixel spacing.
	this->chatBox = sfg::Box::Create(sfg::Box::VERTICAL, 10.f);
	this->scrolledwindow = sfg::ScrolledWindow::Create();
	this->scrolledwindow->SetScrollbarPolicy( sfg::ScrolledWindow::HORIZONTAL_NEVER | sfg::ScrolledWindow::VERTICAL_ALWAYS );

	this->scrolledwindow->SetRequisition( sf::Vector2f( 500.f, 100.f ) );

	this->chatBox->Pack(this->scrolledwindow, false, true );
	moveToScreenBottom();
	chatWindow->Add(this->chatBox);
	chatWindow->Update(0.f);
}

void GUIChat::moveToScreenBottom() {
	this->chatWindow->Refresh();
	this->chatWindow->SetPosition(
		sf::Vector2f(
			0,
			static_cast<float>( this->guiHandler->gui->window->getSize().y ) - chatWindow->GetAllocation().height
		)
	);
}

void GUIChat::hide() {

}

void GUIChat::show() {

}


GUIChat::~GUIChat() {
	// TODO Auto-generated destructor stub
}

