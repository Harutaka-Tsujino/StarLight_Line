#include "JoyconManager.h"

JoyconManager::JoyconManager()
{
	for (int i = 0; i < Joycon::MAX_CONTROLLER; i++)
	{
		m_pJoycon[i] = new Joycon();
	}
}

JoyconManager::~JoyconManager()
{
	for (int i = 0; i < Joycon::MAX_CONTROLLER; i++)
	{
		if (m_pJoycon[i]->GetIsConnect())
		{
			m_pJoycon[i]->Disconnect();
		}

		delete m_pJoycon[i];
		m_pJoycon[i] = nullptr;
	}
	hid_exit();
}

void JoyconManager::InputState()
{
	CheckButton(Joycon::RIGHT_CONTROLLER, Joycon::A_BUTTON);
	CheckButton(Joycon::RIGHT_CONTROLLER, Joycon::B_BUTTON);
	CheckButton(Joycon::RIGHT_CONTROLLER, Joycon::X_BUTTON);
	CheckButton(Joycon::RIGHT_CONTROLLER, Joycon::Y_BUTTON);
	CheckButton(Joycon::RIGHT_CONTROLLER, Joycon::R_BUTTON);
	CheckButton(Joycon::RIGHT_CONTROLLER, Joycon::ZR_BUTTON);
	CheckButton(Joycon::RIGHT_CONTROLLER, Joycon::SR_BUTTON);
	CheckButton(Joycon::RIGHT_CONTROLLER, Joycon::HOME_BUTTON);
	CheckButton(Joycon::RIGHT_CONTROLLER, Joycon::MINUS_PLUS_BUTTON);
	CheckButton(Joycon::LEFT_CONTROLLER, Joycon::DOWN_BUTTON);
	CheckButton(Joycon::LEFT_CONTROLLER, Joycon::UP_BUTTON);
	CheckButton(Joycon::LEFT_CONTROLLER, Joycon::LEFT_BUTTON);
	CheckButton(Joycon::LEFT_CONTROLLER, Joycon::RIGHT_BUTTON);
	CheckButton(Joycon::LEFT_CONTROLLER, Joycon::L_BUTTON);
	CheckButton(Joycon::LEFT_CONTROLLER, Joycon::ZL_BUTTON);
	CheckButton(Joycon::LEFT_CONTROLLER, Joycon::SL_BUTTON);
	CheckButton(Joycon::LEFT_CONTROLLER, Joycon::HOME_BUTTON);
	CheckButton(Joycon::LEFT_CONTROLLER, Joycon::MINUS_PLUS_BUTTON);
	CheckAnalogStick();
	CheckGyroSensor();
}
