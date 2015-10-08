// InputTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "../ThomasTheGameEngine/InputComponent.h"
#include "../Math/four_dimensions.hpp"
#include <conio.h>

SDL_Event _event;
bool quit;

using namespace std;

void MathsTests(){
	cout << "This is the maths test, enjoy" << endl;

	cout << "Test #1: 2D vectors and matrix maths:" << endl << "Multiplying 2 matricies: " << endl;
	Vec2 testVector = Vec2(1, 5);

	Matrix2 neo = Matrix2(
		4, 9,
		8, 6);
	Matrix2 multi = Matrix2(
		2, 2,
		14, 7);

	Matrix2 result = neo + multi;
	//cout << "Matrix addition: See comments for expected results: " 

	//Testing vec2 tostring
	cout << testVector.toString() << endl;
	while (!_kbhit()){}
	return;

}


class InputTester : public InputComponent {
public:
	void whenPressed(){
		std::cout << "I have been pressed" << std::endl;
	}
};

void InputTests(){

	InputController::getInstance(); //Acts as an initialize.
	InputTester* testBed = new InputTester();
	InputController::getInstance()->bindKey(SDLK_w, testBed);
	quit = false;



	while (!quit){
		while (SDL_PollEvent(&_event)){
			std::cout << "This is the event type code: " << _event.type << std::endl;
			if (_event.type == SDL_KEYDOWN){
				std::cout << "Keydown" << std::endl;
				InputController::getInstance()->hitKey(_event.key.keysym.sym);
			}
			else if (_event.type == SDL_QUIT){
				quit = true;
			}
			else if (_event.type == SDL_MOUSEBUTTONDOWN){
				std::cout << "Mouse button!" << std::endl;
			}

		}
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	//MathsTests();
	return 0;
}