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
	*		 アナログスティックがその方向に向いているかを判断する関数
	*
	* @param controllerType 取得するコントローラの種類
	* @param Direction アナログスティックの向き
	*/
	bool SearchAnalogStick(Joycon::CONTROLLER_TYPE controllerType, int direction);

private:
	void CheckButton(Joycon::CONTROLLER_TYPE controllerType, int button) const
	{
		m_pJoycon[controllerType]->CheckButton(button);
	}

	JoyconManager(const JoyconManager&) = delete;
	JoyconManager& operator=(const JoyconManager&) = delete;

	Joycon* m_pJoycon[Joycon::MAX_CONTROLLER];

};

#endif
