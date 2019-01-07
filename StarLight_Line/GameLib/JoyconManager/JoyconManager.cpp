#include "JoyconManager.h"

//----------------------------------------------------------------------
// Constructor	Destructor
//----------------------------------------------------------------------

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
		delete m_pJoycon[i];
		m_pJoycon[i] = nullptr;
	}
	hid_exit();
}

bool JoyconManager::SearchAnalogStick(Joycon::CONTROLLER_TYPE controllerType, int direction)
{
	const FLOAT THRESHOLD_VALUE = 0.15f;

	switch (direction)
	{
	case Joycon::UP_SLOPE:
		if (m_pJoycon[controllerType]->GetAnalogStick().y > THRESHOLD_VALUE) return TRUE;

		break;

	case Joycon::DOWN_SLOPE:
		if (m_pJoycon[controllerType]->GetAnalogStick().y < -THRESHOLD_VALUE) return TRUE;

		break;

	case Joycon::RIGHT_SLOPE:
		if (m_pJoycon[controllerType]->GetAnalogStick().x < -THRESHOLD_VALUE) return TRUE;

		break;

	case Joycon::LEFT_SLOPE:
		if (m_pJoycon[controllerType]->GetAnalogStick().x > THRESHOLD_VALUE) return TRUE;

		break;
	}

	return FALSE;
}
