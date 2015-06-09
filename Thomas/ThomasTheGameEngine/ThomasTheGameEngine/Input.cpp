//Author: Nathan Senter
//Date: 6/9/2015(NS)

#include "Input.h"

std::vector<bool *> Input::activeKeys;

//static Vec2 initialMousePosition;

bool Input::Key_A;
bool Input::Key_B;
bool Input::Key_C;
bool Input::Key_D;
bool Input::Key_E;
bool Input::Key_F;
bool Input::Key_G;
bool Input::Key_H;
bool Input::Key_I;
bool Input::Key_J;
bool Input::Key_K;
bool Input::Key_L;
bool Input::Key_M;
bool Input::Key_N;
bool Input::Key_O;
bool Input::Key_P;
bool Input::Key_Q;
bool Input::Key_R;
bool Input::Key_S;
bool Input::Key_T;
bool Input::Key_U;
bool Input::Key_V;
bool Input::Key_W;
bool Input::Key_X;
bool Input::Key_Y;
bool Input::Key_Z;

bool Input::Key_0;
bool Input::Key_1;
bool Input::Key_2;
bool Input::Key_3;
bool Input::Key_4;
bool Input::Key_5;
bool Input::Key_6;
bool Input::Key_7;
bool Input::Key_8;
bool Input::Key_9;

bool Input::Key_ESCAPE;
bool Input::Key_F1;
bool Input::Key_F2;
bool Input::Key_F3;
bool Input::Key_F4;
bool Input::Key_F5;
bool Input::Key_F6;
bool Input::Key_F7;
bool Input::Key_F8;
bool Input::Key_F9;
bool Input::Key_F10;
bool Input::Key_F11;
bool Input::Key_F12;

bool Input::Key_PLUS;
bool Input::Key_MINUS;
bool Input::Key_BACKSPACE;

bool Input::Key_TAB;
bool Input::Key_CAPS;
bool Input::Key_LSHIFT;
bool Input::Key_LCTRL;
bool Input::Key_LALT;

bool Input::Key_SPACE;
bool Input::Key_UP;
bool Input::Key_DOWN;
bool Input::Key_RIGHT;
bool Input::Key_LEFT;
bool Input::Key_RETURN;

bool Input::Key_SLASH;
bool Input::Key_RSHIFT;
bool Input::Key_RCTRL;
bool Input::Key_RALT;

bool Input::Key_RBRACKET;
bool Input::Key_LBRACKET;
bool Input::Key_COLON;
bool Input::Key_QUOTE;
bool Input::Key_COMMA;
bool Input::Key_PERIOD;
bool Input::Key_QUESTION;

bool Input::Mouse_RIGHT;
bool Input::Mouse_LEFT;
bool Input::Mouse_MIDDLE;

Input::Input()
{
}


Input::~Input()
{
	activeKeys.clear();
}

//Posts the SDL_Event to the InputHub to be handled
void Input::PostEvent(SDL_Event _e)
{
	if (_e.type == SDL_KEYDOWN)
	{
		//ALPHABET
		if (_e.key.keysym.sym == SDLK_a)
		{
			activeKeys.push_back(&Key_A);
			toggleKey(&Key_A);
		}
		else if (_e.key.keysym.sym == SDLK_b)
		{
			activeKeys.push_back(&Key_B);
			toggleKey(&Key_B);
		}
		else if (_e.key.keysym.sym == SDLK_c)
		{
			activeKeys.push_back(&Key_C);
			toggleKey(&Key_C);
		}
		else if (_e.key.keysym.sym == SDLK_d)
		{
			activeKeys.push_back(&Key_D);
			toggleKey(&Key_D);
		}
		else if (_e.key.keysym.sym == SDLK_e)
		{
			activeKeys.push_back(&Key_E);
			toggleKey(&Key_E);
		}
		else if (_e.key.keysym.sym == SDLK_f)
		{
			activeKeys.push_back(&Key_F);
			toggleKey(&Key_F);
		}
		else if (_e.key.keysym.sym == SDLK_g)
		{
			activeKeys.push_back(&Key_G);
			toggleKey(&Key_G);
		}
		else if (_e.key.keysym.sym == SDLK_h)
		{
			activeKeys.push_back(&Key_H);
			toggleKey(&Key_H);
		}
		else if (_e.key.keysym.sym == SDLK_i)
		{
			activeKeys.push_back(&Key_I);
			toggleKey(&Key_I);
		}
		else if (_e.key.keysym.sym == SDLK_j)
		{
			activeKeys.push_back(&Key_J);
			toggleKey(&Key_J);
		}
		else if (_e.key.keysym.sym == SDLK_k)
		{
			activeKeys.push_back(&Key_K);
			toggleKey(&Key_K);
		}
		else if (_e.key.keysym.sym == SDLK_l)
		{
			activeKeys.push_back(&Key_L);
			toggleKey(&Key_L);
		}
		else if (_e.key.keysym.sym == SDLK_m)
		{
			activeKeys.push_back(&Key_M);
			toggleKey(&Key_M);
		}
		else if (_e.key.keysym.sym == SDLK_n)
		{
			activeKeys.push_back(&Key_N);
			toggleKey(&Key_N);
		}
		else if (_e.key.keysym.sym == SDLK_o)
		{
			activeKeys.push_back(&Key_O);
			toggleKey(&Key_O);
		}
		else if (_e.key.keysym.sym == SDLK_p)
		{
			activeKeys.push_back(&Key_P);
			toggleKey(&Key_P);
		}
		else if (_e.key.keysym.sym == SDLK_q)
		{
			activeKeys.push_back(&Key_Q);
			toggleKey(&Key_Q);
		}
		else if (_e.key.keysym.sym == SDLK_r)
		{
			activeKeys.push_back(&Key_R);
			toggleKey(&Key_R);
		}
		else if (_e.key.keysym.sym == SDLK_s)
		{
			activeKeys.push_back(&Key_S);
			toggleKey(&Key_S);
		}
		else if (_e.key.keysym.sym == SDLK_t)
		{
			activeKeys.push_back(&Key_T);
			toggleKey(&Key_T);
		}
		else if (_e.key.keysym.sym == SDLK_u)
		{
			activeKeys.push_back(&Key_U);
			toggleKey(&Key_U);
		}
		else if (_e.key.keysym.sym == SDLK_v)
		{
			activeKeys.push_back(&Key_V);
			toggleKey(&Key_V);
		}
		else if (_e.key.keysym.sym == SDLK_w)
		{
			activeKeys.push_back(&Key_W);
			toggleKey(&Key_W);
		}
		else if (_e.key.keysym.sym == SDLK_x)
		{
			activeKeys.push_back(&Key_X);
			toggleKey(&Key_X);
		}
		else if (_e.key.keysym.sym == SDLK_y)
		{
			activeKeys.push_back(&Key_Y);
			toggleKey(&Key_Y);
		}
		else if (_e.key.keysym.sym == SDLK_z)
		{
			activeKeys.push_back(&Key_Z);
			toggleKey(&Key_Z);
		}

		//SPACE AND ARROWS
		else if (_e.key.keysym.sym == SDLK_SPACE)
		{
			activeKeys.push_back(&Key_SPACE);
			toggleKey(&Key_SPACE);
		}
		else if (_e.key.keysym.sym == SDLK_RETURN)
		{
			activeKeys.push_back(&Key_RETURN);
			toggleKey(&Key_RETURN);
		}
		else if (_e.key.keysym.sym == SDLK_UP)
		{
			activeKeys.push_back(&Key_UP);
			toggleKey(&Key_UP);
		}
		else if (_e.key.keysym.sym == SDLK_DOWN)
		{
			activeKeys.push_back(&Key_DOWN);
			toggleKey(&Key_DOWN);
		}
		else if (_e.key.keysym.sym == SDLK_LEFT)
		{
			activeKeys.push_back(&Key_LEFT);
			toggleKey(&Key_LEFT);
		}
		else if (_e.key.keysym.sym == SDLK_RIGHT)
		{
			activeKeys.push_back(&Key_RIGHT);
			toggleKey(&Key_RIGHT);
		}

		//NUMBER KEYS
		else if (_e.key.keysym.sym == SDLK_0)
		{
			activeKeys.push_back(&Key_0);
			toggleKey(&Key_0);
		}
		else if (_e.key.keysym.sym == SDLK_1)
		{
			activeKeys.push_back(&Key_1);
			toggleKey(&Key_1);
		}
		else if (_e.key.keysym.sym == SDLK_2)
		{
			activeKeys.push_back(&Key_2);
			toggleKey(&Key_2);
		}
		else if (_e.key.keysym.sym == SDLK_3)
		{
			activeKeys.push_back(&Key_3);
			toggleKey(&Key_3);
		}
		else if (_e.key.keysym.sym == SDLK_4)
		{
			activeKeys.push_back(&Key_4);
			toggleKey(&Key_4);
		}
		else if (_e.key.keysym.sym == SDLK_5)
		{
			activeKeys.push_back(&Key_5);
			toggleKey(&Key_5);
		}
		else if (_e.key.keysym.sym == SDLK_6)
		{
			activeKeys.push_back(&Key_6);
			toggleKey(&Key_6);
		}
		else if (_e.key.keysym.sym == SDLK_7)
		{
			activeKeys.push_back(&Key_7);
			toggleKey(&Key_7);
		}
		else if (_e.key.keysym.sym == SDLK_8)
		{
			activeKeys.push_back(&Key_8);
			toggleKey(&Key_8);
		}
		else if (_e.key.keysym.sym == SDLK_9)
		{
			activeKeys.push_back(&Key_9);
			toggleKey(&Key_9);
		}

		//TOP ROW KEYS
		else if (_e.key.keysym.sym == SDLK_ESCAPE)
		{
			activeKeys.push_back(&Key_ESCAPE);
			toggleKey(&Key_ESCAPE);
		}
		else if (_e.key.keysym.sym == SDLK_F1)
		{
			activeKeys.push_back(&Key_F1);
			toggleKey(&Key_F1);
		}
		else if (_e.key.keysym.sym == SDLK_F2)
		{
			activeKeys.push_back(&Key_F2);
			toggleKey(&Key_F2);
		}
		else if (_e.key.keysym.sym == SDLK_F3)
		{
			activeKeys.push_back(&Key_F3);
			toggleKey(&Key_F3);
		}
		else if (_e.key.keysym.sym == SDLK_F4)
		{
			activeKeys.push_back(&Key_F4);
			toggleKey(&Key_F4);
		}
		else if (_e.key.keysym.sym == SDLK_F5)
		{
			activeKeys.push_back(&Key_F5);
			toggleKey(&Key_F5);
		}
		else if (_e.key.keysym.sym == SDLK_F6)
		{
			activeKeys.push_back(&Key_F6);
			toggleKey(&Key_F6);
		}
		else if (_e.key.keysym.sym == SDLK_F7)
		{
			activeKeys.push_back(&Key_F7);
			toggleKey(&Key_F7);
		}
		else if (_e.key.keysym.sym == SDLK_F8)
		{
			activeKeys.push_back(&Key_F8);
			toggleKey(&Key_F8);
		}
		else if (_e.key.keysym.sym == SDLK_F9)
		{
			activeKeys.push_back(&Key_F9);
			toggleKey(&Key_F9);
		}
		else if (_e.key.keysym.sym == SDLK_F10)
		{
			activeKeys.push_back(&Key_F10);
			toggleKey(&Key_F10);
		}
		else if (_e.key.keysym.sym == SDLK_F11)
		{
			activeKeys.push_back(&Key_F11);
			toggleKey(&Key_F11);
		}
		else if (_e.key.keysym.sym == SDLK_F12)
		{
			activeKeys.push_back(&Key_F12);
			toggleKey(&Key_F12);
		}

		//MORE NUMBER ROW
		else if (_e.key.keysym.sym == SDLK_PLUS)
		{
			activeKeys.push_back(&Key_PLUS);
			toggleKey(&Key_PLUS);
		}
		else if (_e.key.keysym.sym == SDLK_MINUS)
		{
			activeKeys.push_back(&Key_MINUS);
			toggleKey(&Key_MINUS);
		}
		else if (_e.key.keysym.sym == SDLK_BACKSPACE)
		{
			activeKeys.push_back(&Key_BACKSPACE);
			toggleKey(&Key_BACKSPACE);
		}

		//LEFT SIDE
		else if (_e.key.keysym.sym == SDLK_TAB)
		{
			activeKeys.push_back(&Key_TAB);
			toggleKey(&Key_TAB);
		}
		else if (_e.key.keysym.sym == SDLK_CAPSLOCK)
		{
			activeKeys.push_back(&Key_CAPS);
			toggleKey(&Key_CAPS);
		}
		else if (_e.key.keysym.sym == SDLK_LSHIFT)
		{
			activeKeys.push_back(&Key_LSHIFT);
			toggleKey(&Key_LSHIFT);
		}
		else if (_e.key.keysym.sym == SDLK_LCTRL)
		{
			activeKeys.push_back(&Key_LCTRL);
			toggleKey(&Key_LCTRL);
		}
		else if (_e.key.keysym.sym == SDLK_LALT)
		{
			activeKeys.push_back(&Key_LALT);
			toggleKey(&Key_LALT);
		}

		//RIGHT SIDE
		else if (_e.key.keysym.sym == SDLK_BACKSLASH)
		{
			activeKeys.push_back(&Key_SLASH);
			toggleKey(&Key_SLASH);
		}
		else if (_e.key.keysym.sym == SDLK_RSHIFT)
		{
			activeKeys.push_back(&Key_RSHIFT);
			toggleKey(&Key_RSHIFT);
		}
		else if (_e.key.keysym.sym == SDLK_RCTRL)
		{
			activeKeys.push_back(&Key_RCTRL);
			toggleKey(&Key_RCTRL);
		}
		else if (_e.key.keysym.sym == SDLK_RALT)
		{
			activeKeys.push_back(&Key_RALT);
			toggleKey(&Key_RALT);
		}

		//OTHER KEYS AMONG THE LETTERS
		else if (_e.key.keysym.sym == SDLK_LEFTBRACKET)
		{
			activeKeys.push_back(&Key_LBRACKET);
			toggleKey(&Key_LBRACKET);
		}
		else if (_e.key.keysym.sym == SDLK_RIGHTBRACKET)
		{
			activeKeys.push_back(&Key_RBRACKET);
			toggleKey(&Key_RBRACKET);
		}
		else if (_e.key.keysym.sym == SDLK_SEMICOLON)
		{
			activeKeys.push_back(&Key_COLON);
			toggleKey(&Key_COLON);
		}
		else if (_e.key.keysym.sym == SDLK_QUOTE)
		{
			activeKeys.push_back(&Key_QUOTE);
			toggleKey(&Key_QUOTE);
		}
		else if (_e.key.keysym.sym == SDLK_COMMA)
		{
			activeKeys.push_back(&Key_COMMA);
			toggleKey(&Key_COMMA);
		}
		else if (_e.key.keysym.sym == SDLK_PERIOD)
		{
			activeKeys.push_back(&Key_PERIOD);
			toggleKey(&Key_PERIOD);
		}
		else if (_e.key.keysym.sym == SDLK_SLASH)
		{
			activeKeys.push_back(&Key_QUESTION);
			toggleKey(&Key_QUESTION);
		}
	}
	else if (_e.type == SDL_MOUSEBUTTONDOWN)
	{
		if (_e.button.button == SDL_BUTTON_LEFT)
		{
			activeKeys.push_back(&Mouse_LEFT);
			toggleKey(&Mouse_LEFT);
		}
		else if (_e.button.button == SDL_BUTTON_MIDDLE)
		{
			activeKeys.push_back(&Mouse_MIDDLE);
			toggleKey(&Mouse_MIDDLE);
		}
		else if (_e.button.button == SDL_BUTTON_RIGHT)
		{
			activeKeys.push_back(&Mouse_RIGHT);
			toggleKey(&Mouse_RIGHT);
		}
	}
	else if (_e.type == SDL_MOUSEMOTION)
	{
		//WHEN MATH LIBRARY IS IN DO MOUSE STUFF
	}

}

//Takes a bool * for the ease of resetting booleans without more massive ifs
void Input::toggleKey(bool * _keyPressed)
{
	*_keyPressed = !*_keyPressed;
}

//Resets the InputHub to its untouched state
void Input::Clear()
{
	for (int i = 0; i < activeKeys.size(); i++)
	{
		*activeKeys[i] = false;
	}
	activeKeys.clear();
}

bool Input::Keydown_A(){ return Key_A; }
bool Input::Keydown_B(){ return Key_B; }
bool Input::Keydown_C(){ return Key_C; }
bool Input::Keydown_D(){ return Key_D; }
bool Input::Keydown_E(){ return Key_E; }
bool Input::Keydown_F(){ return Key_D; }
bool Input::Keydown_G(){ return Key_G; }
bool Input::Keydown_H(){ return Key_H; }
bool Input::Keydown_I(){ return Key_I; }
bool Input::Keydown_J(){ return Key_J; }
bool Input::Keydown_K(){ return Key_K; }
bool Input::Keydown_L(){ return Key_L; }
bool Input::Keydown_M(){ return Key_M; }
bool Input::Keydown_N(){ return Key_N; }
bool Input::Keydown_O(){ return Key_O; }
bool Input::Keydown_P(){ return Key_P; }
bool Input::Keydown_Q(){ return Key_Q; }
bool Input::Keydown_R(){ return Key_R; }
bool Input::Keydown_S(){ return Key_S; }
bool Input::Keydown_T(){ return Key_T; }
bool Input::Keydown_U(){ return Key_U; }
bool Input::Keydown_V(){ return Key_V; }
bool Input::Keydown_W(){ return Key_W; }
bool Input::Keydown_X(){ return Key_X; }
bool Input::Keydown_Y(){ return Key_Y; }
bool Input::Keydown_Z(){ return Key_Z; }

bool Input::Keydown_0(){ return Key_0; }
bool Input::Keydown_1(){ return Key_1; }
bool Input::Keydown_2(){ return Key_2; }
bool Input::Keydown_3(){ return Key_3; }
bool Input::Keydown_4(){ return Key_4; }
bool Input::Keydown_5(){ return Key_5; }
bool Input::Keydown_6(){ return Key_6; }
bool Input::Keydown_7(){ return Key_7; }
bool Input::Keydown_8(){ return Key_8; }
bool Input::Keydown_9(){ return Key_9; }

bool Input::Keydown_ESCAPE(){ return Key_ESCAPE; }
bool Input::Keydown_F1(){ return Key_F1; }
bool Input::Keydown_F2(){ return Key_F2; }
bool Input::Keydown_F3(){ return Key_F3; }
bool Input::Keydown_F4(){ return Key_F4; }
bool Input::Keydown_F5(){ return Key_F5; }
bool Input::Keydown_F6(){ return Key_F6; }
bool Input::Keydown_F7(){ return Key_F7; }
bool Input::Keydown_F8(){ return Key_F8; }
bool Input::Keydown_F9(){ return Key_F9; }
bool Input::Keydown_F10(){ return Key_F10; }
bool Input::Keydown_F11(){ return Key_F11; }
bool Input::Keydown_F12(){ return Key_F12; }

bool Input::Keydown_PLUS(){ return Key_PLUS; }
bool Input::Keydown_MINUS(){ return Key_MINUS; }
bool Input::Keydown_BACKSPACE(){ return Key_BACKSPACE; }

bool Input::Keydown_TAB(){ return Key_TAB; }
bool Input::Keydown_CAPS(){ return Key_CAPS; }
bool Input::Keydown_LSHIFT(){ return Key_LSHIFT; }
bool Input::Keydown_LCTRL(){ return Key_LCTRL; }
bool Input::Keydown_LALT(){ return Key_LALT; }

bool Input::Keydown_SPACE(){ return Key_SPACE; }
bool Input::Keydown_RETURN(){ return Key_RETURN; }
bool Input::Keydown_UP(){ return Key_UP; }
bool Input::Keydown_DOWN(){ return Key_DOWN; }
bool Input::Keydown_RIGHT(){ return Key_RIGHT; }
bool Input::Keydown_LEFT(){ return Key_LEFT; }

bool Input::Keydown_SLASH(){ return Key_SLASH; }
bool Input::Keydown_RSHIFT(){ return Key_RSHIFT; }
bool Input::Keydown_RCTRL(){ return Key_RCTRL; }
bool Input::Keydown_RALT(){ return Key_RALT; }

bool Input::Keydown_RBRACKET(){ return Key_RBRACKET; }
bool Input::Keydown_LBRACKET(){ return Key_LBRACKET; }
bool Input::Keydown_COLON(){ return Key_COLON; }
bool Input::Keydown_QUOTE(){ return Key_QUOTE; }
bool Input::Keydown_COMMA(){ return Key_COMMA; }
bool Input::Keydown_PERIOD(){ return Key_PERIOD; }
bool Input::Keydown_QUESTION(){ return Key_QUESTION; }

bool Input::Mouse_LEFT_CLICK(){ return Mouse_LEFT; }
bool Input::Mouse_MIDDLE_CLICK(){ return Mouse_MIDDLE; }
bool Input::Mouse_RIGHT_CLICK(){ return Mouse_RIGHT; }