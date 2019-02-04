#ifndef JOYCON_MANAGER_H_
#define JOYCON_MANAGER_H_

#include "Joycon/Joycon.h"

class JoyconManager
{
public:
	JoyconManager();

	~JoyconManager();

	/**
	* @brief Joyconを取得する
	* @param controllerType 取得するコントローラの種類
	*/
	Joycon* GetJoycon(Joycon::CONTROLLER_TYPE controllerType) const
	{
		return m_pJoycon[controllerType];
	}

	bool Connect(Joycon::CONTROLLER_TYPE controllerType) const
	{
		return m_pJoycon[controllerType]->Connect(controllerType);
	}

	void Disconnect(Joycon::CONTROLLER_TYPE controllerType) const
	{
		m_pJoycon[controllerType]->Disconnect();
	}

	void InputState();

	/**
	* @brief 引数に渡した向きを入れると
	*		 アナログスティックがその方向に入力されたかを判断する
	*
	* @param controllerType 取得するコントローラの種類
	* @param Direction アナログスティックの向き
	*/
	bool PushAnalogStick(Joycon::CONTROLLER_TYPE controllerType, int direction) const
	{
		const Joycon::ANALOG_STICK_STATE* AnalogStick = m_pJoycon[controllerType]->GetAnalogStickState();

		if (AnalogStick[direction] == Joycon::PUSH_ANALOG_STICK) return true;

		return false;
	}

	/**
	* @brief 引数に渡した向きを入れると
	*		 アナログスティックがその方向に入力され続けているかを判断する
	*
	* @param controllerType 取得するコントローラの種類
	* @param Direction アナログスティックの向き
	*/
	bool HoldAnalogStick(Joycon::CONTROLLER_TYPE controllerType, int direction) const
	{
		const Joycon::ANALOG_STICK_STATE* AnalogStick = m_pJoycon[controllerType]->GetAnalogStickState();

		if (AnalogStick[direction] == Joycon::HOLD_ANALOG_STICK) return true;

		return false;
	}

	/**
	* @brief 引数に渡した向きを入れると
	*		 アナログスティックが離されたかを判断する
	*
	* @param controllerType 取得するコントローラの種類
	* @param Direction アナログスティックの向き
	*/
	bool ReleaseAnalogStick(Joycon::CONTROLLER_TYPE controllerType, int direction) const
	{
		const Joycon::ANALOG_STICK_STATE* AnalogStick = m_pJoycon[controllerType]->GetAnalogStickState();

		if (AnalogStick[direction] == Joycon::RELEASE_ANALOG_STICK) return true;

		return false;
	}

	/**
	* @brief 引数に渡した向きを入れると
	*		 アナログスティックがニュートラル状態かを判断する
	*
	* @param controllerType 取得するコントローラの種類
	* @param Direction アナログスティックの向き
	*/
	bool NeutralAnalogStick(Joycon::CONTROLLER_TYPE controllerType, int direction) const
	{
		const Joycon::ANALOG_STICK_STATE* AnalogStick = m_pJoycon[controllerType]->GetAnalogStickState();

		if (AnalogStick[direction] == Joycon::NEUTRAL_ANALOG_STICK) return true;

		return false;
	}

	/**
	* @breif ジャイロが入力されているかを判断する
	* @param controllerType 取得するコントローラの種類
	* @param Direction ジャイロの向き
	*/
	bool InputGyroSensor(Joycon::CONTROLLER_TYPE controllerType, int direction) const
	{
		const Joycon::GYRO_SENSOR_STATE* GyroSensor = m_pJoycon[controllerType]->GetGyroSensorState();

		if (GyroSensor[direction] == Joycon::INPUT_GYRO_SENSOR) return true;

		return false;
	}

	/**
	* @breif ジャイロが動き続けているかを判断する
	* @param controllerType 取得するコントローラの種類
	* @param Direction ジャイロの向き
	*/
	bool MoveGyroSensor(Joycon::CONTROLLER_TYPE controllerType, int direction) const
	{
		const Joycon::GYRO_SENSOR_STATE* GyroSensor = m_pJoycon[controllerType]->GetGyroSensorState();

		if (GyroSensor[direction] == Joycon::MOVE_GYRO_SENSOR) return true;

		return false;
	}

	/**
	* @breif ジャイロが止まったかを判断する
	* @param controllerType 取得するコントローラの種類
	* @param Direction ジャイロの向き
	*/
	bool StopGyroSensor(Joycon::CONTROLLER_TYPE controllerType, int direction) const
	{
		const Joycon::GYRO_SENSOR_STATE* GyroSensor = m_pJoycon[controllerType]->GetGyroSensorState();

		if (GyroSensor[direction] == Joycon::STOP_GYRO_SENSOR) return true;

		return false;
	}

	/**
	* @breif ジャイロがニュートラル状態かを判断する
	* @param controllerType 取得するコントローラの種類
	* @param Direction ジャイロの向き
	*/
	bool NeutralGyroSensor(Joycon::CONTROLLER_TYPE controllerType, int direction) const
	{
		const Joycon::GYRO_SENSOR_STATE* GyroSensor = m_pJoycon[controllerType]->GetGyroSensorState();

		if (GyroSensor[direction] == Joycon::NEUTRAL_GYRO_SENSOR) return true;

		return false;
	}

	/**
	* @brief 引数で渡されたボタンの種類が押されたかを判断する
	* @param controllerType 取得するコントローラの種類
	* @param button ボタンの種類
	*/
	bool PushButton(Joycon::CONTROLLER_TYPE controllerType, int button) const
	{
		const Joycon::BUTTON_STATE* Button = m_pJoycon[controllerType]->GetButtonState();
		
		if (Button[button] == Joycon::PUSH_BUTTON) return true;

		return false;
	}

	/**
	* @brief 引数で渡されたボタンの種類が離されたかを判断する
	* @param controllerType 取得するコントローラの種類
	* @param button ボタンの種類
	*/
	bool ReleaseButton(Joycon::CONTROLLER_TYPE controllerType, int button) const
	{
		const Joycon::BUTTON_STATE* Button = m_pJoycon[controllerType]->GetButtonState();

		if (Button[button] == Joycon::RELEASE_BUTTON) return true;

		return false;
	}

	/**
	* @brief 引数で渡されたボタンの種類が押され続けているかを判断する
	* @param controllerType 取得するコントローラの種類
	* @param button ボタンの種類
	*/
	bool HoldButton(Joycon::CONTROLLER_TYPE controllerType, int button) const
	{
		const Joycon::BUTTON_STATE* Button = m_pJoycon[controllerType]->GetButtonState();

		if (Button[button] == Joycon::HOLD_BUTTON) return true;

		return false;
	}

	/**
	* @brief 引数で渡されたボタンの種類が何も押されてないかを判断する
	* @param controllerType 取得するコントローラの種類
	* @param button ボタンの種類
	*/
	bool NeutralButton(Joycon::CONTROLLER_TYPE controllerType, int button) const
	{
		const Joycon::BUTTON_STATE* Button = m_pJoycon[controllerType]->GetButtonState();

		if (Button[button] == Joycon::NEUTRAL_BUTTON) return true;

		return false;
	}

private:
	void CheckButton(Joycon::CONTROLLER_TYPE controllerType, int button) const
	{
		m_pJoycon[controllerType]->CheckButton(button);
	}

	void CheckAnalogStick() const
	{
		for (int i = 0;i < Joycon::MAX_CONTROLLER;++i)
		{
			m_pJoycon[i]->CheckAnalogStick();
		}
	}

	void CheckGyroSensor() const
	{
		for (int i = 0;i < Joycon::MAX_CONTROLLER;++i)
		{
			m_pJoycon[i]->CheckGyroSensor();
		}
	}

	JoyconManager(const JoyconManager&) = delete;
	JoyconManager& operator=(const JoyconManager&) = delete;

	Joycon* m_pJoycon[Joycon::MAX_CONTROLLER];

};

#endif
