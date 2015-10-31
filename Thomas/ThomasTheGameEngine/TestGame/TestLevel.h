//Author:	Mathieu Violette
//Date:		10/21/2015
//Example Level

#pragma once

#include <Level.h>

class TestLevel : public Level
{
public:
	TestLevel();
	~TestLevel();

	void DebugRender() override;
	void LevelUpdate(UINT32 _timeStep) override;
};