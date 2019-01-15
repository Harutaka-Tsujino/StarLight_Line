#ifndef BASE_STAR_H_
#define BASE_STAR_H_

#include <Windows.h>

#include <d3dx9.h>

#include "../../../Obj.h"
#include "../../Enum/STAR_TYPE.h"

struct StarPlace
{
	D3DXVECTOR3	m_Pos = { 0.0f, -600.0f, 0.0f };		//x,y,z座標
	STAR_TYPE m_Type;									//スターの種類
	int m_Measure;										//節数
	float m_Beat;										//拍数
	float m_StarsNumInNote;								//n分音符
	float m_Line;										//n分音符の中の数字
	float m_DropPerMinute;								//1分間にどれだけ落ちてくるか
	LONGLONG m_Time;									//落ちてくる時間
	float m_XMovementDeg;								//x座標の移動量
	float m_screenXBasePos;								//xの動く前のスクリーン座標

	D3DXVECTOR3 m_CollisionPos = { 0.0f, -0.0f, 0.0f };	//当たり判定用の座標
};

/*
*ベーススタークラス
*/
class BaseStar :public Obj
{
public:
	BaseStar() :Obj(OT_TRANSPARENCY, 0.5f), m_rEnemyStar(m_rGameLib.GetFbx(_T("StarFBX")))
	{
		D3DXMatrixIdentity(&m_MatWorld);
		Init();
	}

	virtual ~BaseStar() {};

	virtual VOID Init();
	virtual VOID Update();
	virtual VOID Render();

	VOID SetStarInfo(const StarPlace& StarInfo);

	VOID SetType(const STAR_TYPE& Type) { m_Info.m_Type = Type; }
	STAR_TYPE& GetType() { return m_Info.m_Type; }
	D3DXVECTOR3* GetCollisionPos() { return &m_Info.m_CollisionPos; }
	
protected:
	VOID TransScreenPosByTime(const LONGLONG& CurrentTime);		//y座標を移動させる関数
	VOID DefaultLight();										//ライトのデフォルト値設定関数
	VOID ConvertLocalToWorld(D3DXMATRIX* matWorld);				//ローカル座標からワールド座標への変換

	inline BOOL ShouldCulling()
	{
		const FLOAT STAR_HALF_SCALE = 50.0f;

		return (m_Info.m_Pos.y < -STAR_HALF_SCALE - 100.0f || m_Info.m_Pos.y > 2.5f * m_WND_SIZE.m_y + STAR_HALF_SCALE);	//カメラが傾いているので-100.0ｆする
	}

	StarPlace m_Info;				//スターの基本情報
	D3DXMATRIX m_MatWorld;			//ワールド座標

	const float ColorMax = 0xFF;

	ULONGLONG m_DegZ = 0;	//演出用の回転角度

	FbxRelated& m_rEnemyStar;
};

#endif // !BASE_STAR_H_
