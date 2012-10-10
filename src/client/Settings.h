/*
 * Settings.h
 *
 *  Created on: Oct 10, 2012
 *      Author: Remco
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_
#include <string>

/*contains all the settings of client, hardcoded for now
 * also contains default settings for when settings can not be loaded or do not exist
 */

class Settings {
public:
	unsigned int windowHeight;
	unsigned int windowWidth;
	std::string username;

	Settings();
	~Settings();
};

#endif /* SETTINGS_H_ */
