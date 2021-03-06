#include "worldSettings.h"

/*
	Holds all the settings of the current world/map:
	map size
*/

worldSettings::worldSettings() {
	VELMOVING			= 1.0f;		//velocity (speed) for moving left, right
	VELSLOWMOVING		= 2.2f;		//velocity when slow down powerup is in effect
	VELMOVING_CHICKEN 	= 2.9f;		//speed of the chicken in the gamemode capturethechicken
	VELMOVINGADD			= 0.5f;
	VELTURBOMOVING		= 5.5f;
	VELJUMP				= 19.0f;		//velocity for jumping
	VELSLOWJUMP			= 7.0f;		//velocity for jumping when slow down powerup is in effect
	VELTURBOJUMP			= 10.2f;		//velocity for turbo jumping
	VELSUPERJUMP			= 13.0f;		//super jump (jumping off of orange note blocks)
	VELPUSHBACK			= 5.0f;
	GRAVITATION			= 0.90f;
	TILESIZE = 64;
	GROUNDFRICTION		= 1.0f;
	AIRFRICTION			= 0.6f;

	MAXWALKSPEED = 8.0f;
}