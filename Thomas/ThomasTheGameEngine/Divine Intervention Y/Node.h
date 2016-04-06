#pragma once
#include <Billboard.h>
#include <Flipbook.h>

class Node :
	public GameObject
{
	friend class Level_Descriptor;

public:
	Node(Level *, Vec3, std::string fileName_);
	~Node();

	void Update(float _deltaTime) override;

	std::string GetFileName();
private:

	//String that dictates which xml to load
	std::string levelFileName;

	int par;
	std::string objectiveName;
	std::string description;

	float elapsedTime;

	Billboard * b;
	Flipbook * fb;
};

