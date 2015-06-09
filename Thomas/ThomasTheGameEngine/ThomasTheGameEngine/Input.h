//Author: Nathan Senter
//Date: 6/9/2015(NS)

#pragma once
#include<vector>
#include<SDL_events.h>

class Input
{
public:
	Input();
	~Input();

	//Posts the SDL_Event to the InputHub to be handled
	static void PostEvent(SDL_Event);

	//Resets the InputHub to its untouched state
	static void Clear();

	static bool Keydown_A();
	static bool Keydown_B();
	static bool Keydown_C();
	static bool Keydown_D();
	static bool Keydown_E();
	static bool Keydown_F();
	static bool Keydown_G();
	static bool Keydown_H();
	static bool Keydown_I();
	static bool Keydown_J();
	static bool Keydown_K();
	static bool Keydown_L();
	static bool Keydown_M();
	static bool Keydown_N();
	static bool Keydown_O();
	static bool Keydown_P();
	static bool Keydown_Q();
	static bool Keydown_R();
	static bool Keydown_S();
	static bool Keydown_T();
	static bool Keydown_U();
	static bool Keydown_V();
	static bool Keydown_W();
	static bool Keydown_X();
	static bool Keydown_Y();
	static bool Keydown_Z();

	static bool Keydown_0();
	static bool Keydown_1();
	static bool Keydown_2();
	static bool Keydown_3();
	static bool Keydown_4();
	static bool Keydown_5();
	static bool Keydown_6();
	static bool Keydown_7();
	static bool Keydown_8();
	static bool Keydown_9();

	static bool Keydown_ESCAPE();
	static bool Keydown_F1();
	static bool Keydown_F2();
	static bool Keydown_F3();
	static bool Keydown_F4();
	static bool Keydown_F5();
	static bool Keydown_F6();
	static bool Keydown_F7();
	static bool Keydown_F8();
	static bool Keydown_F9();
	static bool Keydown_F10();
	static bool Keydown_F11();
	static bool Keydown_F12();

	static bool Keydown_PLUS();
	static bool Keydown_MINUS();
	static bool Keydown_BACKSPACE();

	static bool Keydown_TAB();
	static bool Keydown_CAPS();
	static bool Keydown_LSHIFT();
	static bool Keydown_LCTRL();
	static bool Keydown_LALT();

	static bool Keydown_SPACE();
	static bool Keydown_UP();
	static bool Keydown_DOWN();
	static bool Keydown_RIGHT();
	static bool Keydown_LEFT();
	static bool Keydown_RETURN();

	static bool Keydown_SLASH();
	static bool Keydown_RSHIFT();
	static bool Keydown_RCTRL();
	static bool Keydown_RALT();

	static bool Keydown_RBRACKET();
	static bool Keydown_LBRACKET();
	static bool Keydown_COLON();
	static bool Keydown_QUOTE();
	static bool Keydown_COMMA();
	static bool Keydown_PERIOD();
	static bool Keydown_QUESTION();

	static bool Mouse_LEFT_CLICK();
	static bool Mouse_RIGHT_CLICK();
	static bool Mouse_MIDDLE_CLICK();

	//static Vec2 mousePosition();
	//static Vec2 deltaMouse;

private:
	static std::vector<bool *> activeKeys;

	//static Vec2 initialMousePosition;
	static void toggleKey(bool *);

	static bool Key_A;
	static bool Key_B;
	static bool Key_C;
	static bool Key_D;
	static bool Key_E;
	static bool Key_F;
	static bool Key_G;
	static bool Key_H;
	static bool Key_I;
	static bool Key_J;
	static bool Key_K;
	static bool Key_L;
	static bool Key_M;
	static bool Key_N;
	static bool Key_O;
	static bool Key_P;
	static bool Key_Q;
	static bool Key_R;
	static bool Key_S;
	static bool Key_T;
	static bool Key_U;
	static bool Key_V;
	static bool Key_W;
	static bool Key_X;
	static bool Key_Y;
	static bool Key_Z;

	static bool Key_0;
	static bool Key_1;
	static bool Key_2;
	static bool Key_3;
	static bool Key_4;
	static bool Key_5;
	static bool Key_6;
	static bool Key_7;
	static bool Key_8;
	static bool Key_9;

	static bool Key_ESCAPE;
	static bool Key_F1;
	static bool Key_F2;
	static bool Key_F3;
	static bool Key_F4;
	static bool Key_F5;
	static bool Key_F6;
	static bool Key_F7;
	static bool Key_F8;
	static bool Key_F9;
	static bool Key_F10;
	static bool Key_F11;
	static bool Key_F12;

	static bool Key_PLUS;
	static bool Key_MINUS;
	static bool Key_BACKSPACE;

	static bool Key_TAB;
	static bool Key_CAPS;
	static bool Key_LSHIFT;
	static bool Key_LCTRL;
	static bool Key_LALT;

	static bool Key_SPACE;
	static bool Key_UP;
	static bool Key_DOWN;
	static bool Key_RIGHT;
	static bool Key_LEFT;
	static bool Key_RETURN;

	static bool Key_SLASH;
	static bool Key_RSHIFT;
	static bool Key_RCTRL;
	static bool Key_RALT;

	static bool Key_RBRACKET;
	static bool Key_LBRACKET;
	static bool Key_COLON;
	static bool Key_QUOTE;
	static bool Key_COMMA;
	static bool Key_PERIOD;
	static bool Key_QUESTION;

	static bool Mouse_RIGHT;
	static bool Mouse_LEFT;
	static bool Mouse_MIDDLE;
};