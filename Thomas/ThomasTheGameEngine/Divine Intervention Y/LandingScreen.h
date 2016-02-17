//Author:	Mathieu Violette
//Date:		2/17/2016

#include <Level.h>
#include "Landing_GUI.h"

class LandingScreen : public Level
{
private:
	Landing_GUI *gui;
public:
	LandingScreen();
	~LandingScreen();

	void LoadContent() override;

	void LevelUpdate(float timeStep_) override;
};