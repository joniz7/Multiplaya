// Class header
#include "keylookup.h"

#include<iostream>
#include<iomanip>
#include<fstream>
#include<algorithm>

namespace mp
{
	/**
	 * Returns the SFML key associated with the supplied string.
	 */
    sf::Keyboard::Key KeyLookup::getKey(std::string keyName)
    {
		// Letters
		if(keyName=="kb_a")
			return sf::Keyboard::A;
		else if(keyName=="kb_b")
			return sf::Keyboard::B;
		else if(keyName=="kb_c")
			return sf::Keyboard::C;
		else if(keyName=="kb_d")
			return sf::Keyboard::D;
		else if(keyName=="kb_e")
			return sf::Keyboard::E;
		else if(keyName=="kb_f")
			return sf::Keyboard::F;
		else if(keyName=="kb_g")
			return sf::Keyboard::G;
		else if(keyName=="kb_h")
			return sf::Keyboard::H;
		else if(keyName=="kb_i")
			return sf::Keyboard::I;
		else if(keyName=="kb_j")
			return sf::Keyboard::J;
		else if(keyName=="kb_k")
			return sf::Keyboard::K;
		else if(keyName=="kb_l")
			return sf::Keyboard::L;
		else if(keyName=="kb_m")
			return sf::Keyboard::M;
		else if(keyName=="kb_n")
			return sf::Keyboard::N;
		else if(keyName=="kb_o")
			return sf::Keyboard::O;
		else if(keyName=="kb_p")
			return sf::Keyboard::P;
		else if(keyName=="kb_q")
			return sf::Keyboard::Q;
		else if(keyName=="kb_r")
			return sf::Keyboard::R;
		else if(keyName=="kb_s")
			return sf::Keyboard::S;
		else if(keyName=="kb_t")
			return sf::Keyboard::T;
		else if(keyName=="kb_u")
			return sf::Keyboard::U;
		else if(keyName=="kb_v")
			return sf::Keyboard::V;
		else if(keyName=="kb_x")
			return sf::Keyboard::X;
		else if(keyName=="kb_y")
			return sf::Keyboard::Y;
		else if(keyName=="kb_z")
			return sf::Keyboard::Z;

		// Numbers
		else if(keyName=="kb_0")
			return sf::Keyboard::Num0;
		else if(keyName=="kb_1")
			return sf::Keyboard::Num1;
		else if(keyName=="kb_2")
			return sf::Keyboard::Num2;
		else if(keyName=="kb_3")
			return sf::Keyboard::Num3;
		else if(keyName=="kb_4")
			return sf::Keyboard::Num4;
		else if(keyName=="kb_5")
			return sf::Keyboard::Num5;
		else if(keyName=="kb_6")
			return sf::Keyboard::Num6;
		else if(keyName=="kb_7")
			return sf::Keyboard::Num7;
		else if(keyName=="kb_8")
			return sf::Keyboard::Num8;
		else if(keyName=="kb_9")
			return sf::Keyboard::Num9;

		// Numpad
		else if(keyName=="kb_kp0")
			return sf::Keyboard::Numpad0;
		else if(keyName=="kb_kp1")
			return sf::Keyboard::Numpad1;
		else if(keyName=="kb_kp2")
			return sf::Keyboard::Numpad2;
		else if(keyName=="kb_kp3")
			return sf::Keyboard::Numpad3;
		else if(keyName=="kb_kp4")
			return sf::Keyboard::Numpad4;
		else if(keyName=="kb_kp5")
			return sf::Keyboard::Numpad5;
		else if(keyName=="kb_kp6")
			return sf::Keyboard::Numpad6;
		else if(keyName=="kb_kp7")
			return sf::Keyboard::Numpad7;
		else if(keyName=="kb_kp8")
			return sf::Keyboard::Numpad8;
		else if(keyName=="kb_kp9")
			return sf::Keyboard::Numpad9;

		// Arrows
		else if(keyName=="kb_left")
			return sf::Keyboard::Left;
		else if(keyName=="kb_right")
			return sf::Keyboard::Right;
		else if(keyName=="kb_up")
			return sf::Keyboard::Up;
		else if(keyName=="kb_down")
			return sf::Keyboard::Down;

		// Function keys
		else if(keyName=="kb_f1")
			return sf::Keyboard::F1;
		else if(keyName=="kb_f2")
			return sf::Keyboard::F2;
		else if(keyName=="kb_f3")
			return sf::Keyboard::F3;
		else if(keyName=="kb_f4")
			return sf::Keyboard::F4;
		else if(keyName=="kb_f5")
			return sf::Keyboard::F5;
		else if(keyName=="kb_f6")
			return sf::Keyboard::F6;
		else if(keyName=="kb_f7")
			return sf::Keyboard::F7;
		else if(keyName=="kb_f8")
			return sf::Keyboard::F8;
		else if(keyName=="kb_f9")
			return sf::Keyboard::F9;
		else if(keyName=="kb_f10")
			return sf::Keyboard::F10;
		else if(keyName=="kb_f11")
			return sf::Keyboard::F11;
		else if(keyName=="kb_f12")
			return sf::Keyboard::F12;
		else if(keyName=="kb_f13")
			return sf::Keyboard::F13;
		else if(keyName=="kb_f14")
			return sf::Keyboard::F14;
		else if(keyName=="kb_f15")
			return sf::Keyboard::F15;

		// Other
		else if(keyName=="kb_esc")
			return sf::Keyboard::Escape;
		else if(keyName=="kb_lctrl")
			return sf::Keyboard::LControl;
		else if(keyName=="kb_lshift")
			return sf::Keyboard::LShift;
		else if(keyName=="kb_lalt")
			return sf::Keyboard::LAlt;
		else if(keyName=="kb_rctrl")
			return sf::Keyboard::RControl;
		else if(keyName=="kb_rshift")
			return sf::Keyboard::RShift;
		else if(keyName=="kb_ralt")
			return sf::Keyboard::RAlt;
		else if(keyName=="kb_space")
			return sf::Keyboard::Space;
		else if(keyName=="kb_return")
			return sf::Keyboard::Return;
		else if(keyName=="kb_back")
			return sf::Keyboard::Back;
		else if(keyName=="kb_tab")
			return sf::Keyboard::Tab;
		else if(keyName=="kb_pgup")
			return sf::Keyboard::PageUp;
		else if(keyName=="kb_pgdn")
			return sf::Keyboard::PageDown;
		else if(keyName=="kb_end")
			return sf::Keyboard::End;
		else if(keyName=="kb_home")
			return sf::Keyboard::Home;
		else if(keyName=="kb_insert")
			return sf::Keyboard::Insert;
		else if(keyName=="kb_delete")
			return sf::Keyboard::Delete;
		else if(keyName=="kb_pause")
			return sf::Keyboard::Pause;
		else
			return sf::Keyboard::A;
    }

	/**
	 * Returns the SFML mouse button associated with the supplied string.
	 */
    sf::Mouse::Button KeyLookup::getMouseButton(std::string keyName)
    {
		if(keyName=="mouse1")
			return sf::Mouse::Left;
		else if(keyName=="mouse2")
			return sf::Mouse::Right;
		else if(keyName=="mouse3")
			return sf::Mouse::Middle;
		else if(keyName=="mouse4")
			return sf::Mouse::XButton1;
		else if(keyName=="mouse5")
			return sf::Mouse::XButton2;
		else
			return sf::Mouse::Left;
	}
}
