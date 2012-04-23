////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "keylookup.h"

#include<iostream>
#include<iomanip>
#include<fstream>
#include<algorithm>

////////////////////////////////////////////////////////////
/// Class for translating config key codes to SFML keys and
/// mouse buttons.
////////////////////////////////////////////////////////////

namespace mp	
{
	////////////////////////////////////////////////////////////
	// Returns an SFML key.
	////////////////////////////////////////////////////////////
    sf::Keyboard::Key KeyLookup::getKey(std::string keyName)
    {
		// Letters
		if(keyName=="kb_a")
			return sf::Keyboard::Key::A;
		else if(keyName=="kb_b")
			return sf::Keyboard::Key::B;
		else if(keyName=="kb_c")
			return sf::Keyboard::Key::C;
		else if(keyName=="kb_d")
			return sf::Keyboard::Key::D;
		else if(keyName=="kb_e")
			return sf::Keyboard::Key::E;
		else if(keyName=="kb_f")
			return sf::Keyboard::Key::F;
		else if(keyName=="kb_g")
			return sf::Keyboard::Key::G;
		else if(keyName=="kb_h")
			return sf::Keyboard::Key::H;
		else if(keyName=="kb_i")
			return sf::Keyboard::Key::I;
		else if(keyName=="kb_j")
			return sf::Keyboard::Key::J;
		else if(keyName=="kb_k")
			return sf::Keyboard::Key::K;
		else if(keyName=="kb_l")
			return sf::Keyboard::Key::L;
		else if(keyName=="kb_m")
			return sf::Keyboard::Key::M;
		else if(keyName=="kb_n")
			return sf::Keyboard::Key::N;
		else if(keyName=="kb_o")
			return sf::Keyboard::Key::O;
		else if(keyName=="kb_p")
			return sf::Keyboard::Key::P;
		else if(keyName=="kb_q")
			return sf::Keyboard::Key::Q;
		else if(keyName=="kb_r")
			return sf::Keyboard::Key::R;
		else if(keyName=="kb_s")
			return sf::Keyboard::Key::S;
		else if(keyName=="kb_t")
			return sf::Keyboard::Key::T;
		else if(keyName=="kb_u")
			return sf::Keyboard::Key::U;
		else if(keyName=="kb_v")
			return sf::Keyboard::Key::V;
		else if(keyName=="kb_x")
			return sf::Keyboard::Key::X;
		else if(keyName=="kb_y")
			return sf::Keyboard::Key::Y;
		else if(keyName=="kb_z")
			return sf::Keyboard::Key::Z;

		// Numbers
		else if(keyName=="kb_0")
			return sf::Keyboard::Key::Num0;
		else if(keyName=="kb_1")
			return sf::Keyboard::Key::Num1;
		else if(keyName=="kb_2")
			return sf::Keyboard::Key::Num2;
		else if(keyName=="kb_3")
			return sf::Keyboard::Key::Num3;
		else if(keyName=="kb_4")
			return sf::Keyboard::Key::Num4;
		else if(keyName=="kb_5")
			return sf::Keyboard::Key::Num5;
		else if(keyName=="kb_6")
			return sf::Keyboard::Key::Num6;
		else if(keyName=="kb_7")
			return sf::Keyboard::Key::Num7;
		else if(keyName=="kb_8")
			return sf::Keyboard::Key::Num8;
		else if(keyName=="kb_9")
			return sf::Keyboard::Key::Num9;

		// Numpad
		else if(keyName=="kb_kp0")
			return sf::Keyboard::Key::Numpad0;
		else if(keyName=="kb_kp1")
			return sf::Keyboard::Key::Numpad1;
		else if(keyName=="kb_kp2")
			return sf::Keyboard::Key::Numpad2;
		else if(keyName=="kb_kp3")
			return sf::Keyboard::Key::Numpad3;
		else if(keyName=="kb_kp4")
			return sf::Keyboard::Key::Numpad4;
		else if(keyName=="kb_kp5")
			return sf::Keyboard::Key::Numpad5;
		else if(keyName=="kb_kp6")
			return sf::Keyboard::Key::Numpad6;
		else if(keyName=="kb_kp7")
			return sf::Keyboard::Key::Numpad7;
		else if(keyName=="kb_kp8")
			return sf::Keyboard::Key::Numpad8;
		else if(keyName=="kb_kp9")
			return sf::Keyboard::Key::Numpad9;

		// Arrows
		else if(keyName=="kb_left")
			return sf::Keyboard::Key::Left;
		else if(keyName=="kb_right")
			return sf::Keyboard::Key::Right;
		else if(keyName=="kb_up")
			return sf::Keyboard::Key::Up;
		else if(keyName=="kb_down")
			return sf::Keyboard::Key::Down;

		// Function keys
		else if(keyName=="kb_f1")
			return sf::Keyboard::Key::F1;
		else if(keyName=="kb_f2")
			return sf::Keyboard::Key::F2;
		else if(keyName=="kb_f3")
			return sf::Keyboard::Key::F3;
		else if(keyName=="kb_f4")
			return sf::Keyboard::Key::F4;
		else if(keyName=="kb_f5")
			return sf::Keyboard::Key::F5;
		else if(keyName=="kb_f6")
			return sf::Keyboard::Key::F6;
		else if(keyName=="kb_f7")
			return sf::Keyboard::Key::F7;
		else if(keyName=="kb_f8")
			return sf::Keyboard::Key::F8;
		else if(keyName=="kb_f9")
			return sf::Keyboard::Key::F9;
		else if(keyName=="kb_f10")
			return sf::Keyboard::Key::F10;
		else if(keyName=="kb_f11")
			return sf::Keyboard::Key::F11;
		else if(keyName=="kb_f12")
			return sf::Keyboard::Key::F12;
		else if(keyName=="kb_f13")
			return sf::Keyboard::Key::F13;
		else if(keyName=="kb_f14")
			return sf::Keyboard::Key::F14;
		else if(keyName=="kb_f15")
			return sf::Keyboard::Key::F15;
		
		// Other
		else if(keyName=="kb_esc")
			return sf::Keyboard::Key::Escape;
		else if(keyName=="kb_lctrl")
			return sf::Keyboard::Key::LControl;
		else if(keyName=="kb_lshift")
			return sf::Keyboard::Key::LShift;
		else if(keyName=="kb_lalt")
			return sf::Keyboard::Key::LAlt;
		else if(keyName=="kb_rctrl")
			return sf::Keyboard::Key::RControl;
		else if(keyName=="kb_rshift")
			return sf::Keyboard::Key::RShift;
		else if(keyName=="kb_ralt")
			return sf::Keyboard::Key::RAlt;
		else if(keyName=="kb_space")
			return sf::Keyboard::Key::Space;
		else if(keyName=="kb_return")
			return sf::Keyboard::Key::Return;
		else if(keyName=="kb_back")
			return sf::Keyboard::Key::Back;
		else if(keyName=="kb_tab")
			return sf::Keyboard::Key::Tab;
		else if(keyName=="kb_pgup")
			return sf::Keyboard::Key::PageUp;
		else if(keyName=="kb_pgdn")
			return sf::Keyboard::Key::PageDown;
		else if(keyName=="kb_end")
			return sf::Keyboard::Key::End;
		else if(keyName=="kb_home")
			return sf::Keyboard::Key::Home;
		else if(keyName=="kb_insert")
			return sf::Keyboard::Key::Insert;
		else if(keyName=="kb_delete")
			return sf::Keyboard::Key::Delete;
		else if(keyName=="kb_pause")
			return sf::Keyboard::Key::Pause;
    }

	////////////////////////////////////////////////////////////
	// Returns an SFML mouse button.
	////////////////////////////////////////////////////////////
    sf::Mouse::Button KeyLookup::getMouseButton(std::string keyName)
    {
		if(keyName=="mouse1")
			return sf::Mouse::Button::Left;
		else if(keyName=="mouse2")
			return sf::Mouse::Button::Right;
		else if(keyName=="mouse3")
			return sf::Mouse::Button::Middle;
		else if(keyName=="mouse4")
			return sf::Mouse::Button::XButton1;
		else if(keyName=="mouse5")
			return sf::Mouse::Button::XButton2;
	}
}
