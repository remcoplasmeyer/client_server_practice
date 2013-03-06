#ifndef worldSettings_h
#define worldSettings_h


class worldSettings {

 public:
	float VELMOVING			;		//velocity (speed) for moving left, right
	float VELSLOWMOVING		;		//velocity when slow down powerup is in effect
	float VELMOVING_CHICKEN ;		//speed of the chicken in the gamemode capturethechicken
	float VELMOVINGADD		;
	float VELTURBOMOVING	;
	float VELJUMP			;		//velocity for jumping
	float VELSLOWJUMP		;		//velocity for jumping when slow down powerup is in effect
	float VELTURBOJUMP		;		//velocity for turbo jumping
	float VELSUPERJUMP		;			//super jump (jumping off of orange note blocks)
	float VELPUSHBACK		;
	float GRAVITATION		;
	int TILESIZE;
	float MAXWALKSPEED		;
	float GROUNDFRICTION	;
	float AIRFRICTION		;

	worldSettings();

};

#endif // worldSettings_h
