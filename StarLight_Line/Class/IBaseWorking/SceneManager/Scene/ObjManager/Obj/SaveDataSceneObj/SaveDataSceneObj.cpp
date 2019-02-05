/// <filename>
/// 
/// </filename>
/// <summary>
/// 
/// </summary>
/// <author>
/// 
/// </author>

#include "SaveDataSceneObj.h"

#include <windows.h>
#include <tchar.h>

#include <d3dx9.h>

#include "../Obj.h"
#include "../MainSceneObj/ADV/Chapter/Section/Text/Tstring/TString.h"
#include "../MainSceneObj/ADV/Chapter/Section/Text/Data/TextFormat.h"
#include "../MainSceneObj/ADV/Chapter/Section/Text/NumText/NumText.h"

VOID SaveDataSaveDatas::Render()
{
	RenderBriefFrame();
	RenderBriefDatas();

	RenderDetailFrame();
	RenderDetailData();
}

VOID SaveDataSaveDatas::RenderBriefFrame()
{
	ObjData frameData;
	frameData.m_halfScale = { m_WND_SIZE.m_x * 0.26f, m_WND_SIZE.m_y * 0.14f, 0.0f };

	for (INT i = 0; i < m_SAVE_DATAS_MAX; ++i)
	{
		frameData.m_center = { m_WND_SIZE.m_x * 0.28f, m_WND_SIZE.m_y * (0.2f + 0.3f * i), m_Z };

		frameData.m_texUV = { 0.0f, 0.0f, 1.0f, 0.5f };

		CustomVertex frame[4];
		m_rGameLib.CreateRect(frame, frameData);

		m_rGameLib.SetLeftRightARGB(frame, m_FRAME_COLOR[i][0], m_FRAME_COLOR[i][1]);

		m_rGameLib.Render(frame, m_rGameLib.GetTex(_T("Frame")));

		if (i == m_selectingData)	//! 選択されているときの枠を既存の枠にかぶせる
		{
			RenderSelectFrame(&frameData);
		}
	}
}

VOID SaveDataSaveDatas::RenderSelectFrame(ObjData* pObjData)
{
	pObjData->m_texUV = { 0.0f, 0.5f, 1.0f, 1.0f };

	CustomVertex frame[4];
	m_rGameLib.CreateRect(frame, *pObjData);

	static INT flashFrameCnt = 0;
	m_rGameLib.FlashRect(frame, &flashFrameCnt, 120, 255, 180);

	m_rGameLib.Render(frame, m_rGameLib.GetTex(_T("Frame")));
}

VOID SaveDataSaveDatas::RenderTotalTimeBrief()
{
	for (INT i = 0; i < m_SAVE_DATAS_MAX; ++i)
	{
		TString totalTimeTextString(_T("TOTAL TIME"));
		Text totalTimeTextText(totalTimeTextString, _T("2DTextures/Fonts/a_9.png"));

		TextFormat totalTimeTextFormat;
		totalTimeTextFormat.m_charHalfScale = { 11, 15 };
		totalTimeTextFormat.m_topLeft = { 400.0f, 70.0f + 215.0f * i };

		totalTimeTextFormat.m_color1 = m_WORD_COLOR[i];

		totalTimeTextText.Write(totalTimeTextFormat);

		TString totalTimeStr(m_pPREVIEWS[i].m_totalTime_partHour, _T("%d"));
		totalTimeStr.WriteInCharPrevEnd(_T(':'));
		totalTimeStr.WriteInNumPrevEnd(m_pPREVIEWS[i].m_totalTime_partMin, _T("%02d"));
		Text totalTimeText(totalTimeStr, _T("2DTextures/Fonts/a_9.png"));

		TextFormat txtFormat;
		txtFormat.m_charHalfScale = { 11, 15 };
		txtFormat.m_topLeft = { 400.0f, 105.0f + 215.0f * i };

		txtFormat.m_color1 = m_WORD_COLOR[i];

		totalTimeText.Write(txtFormat);
	}
}

VOID SaveDataSaveDatas::RenderSaveDataNum()
{
	for (INT i = 0; i < m_SAVE_DATAS_MAX; ++i)
	{
		TextFormat dataTextFormat;
		dataTextFormat.m_charHalfScale = { 15, 22 };
		dataTextFormat.m_topLeft = { 70.0f, 70.0f + 215.0f * i };

		dataTextFormat.m_color1 = m_WORD_COLOR[i];
		dataTextFormat.m_color2 = 0xFF000000;
		dataTextFormat.m_gradationType = GT_OBLIQUE_BOTTOM_LEFT;

		TString dataTextString(_T("DATA "));
		dataTextString.WriteInNumPrevEnd(i + 1, _T("%d"));
		Text dataTextText(dataTextString, _T("2DTextures/Fonts/a_9.png"));

		dataTextText.Write(dataTextFormat);
	}
}

VOID SaveDataSaveDatas::RenderClearAchievement()
{
	for (INT i = 0; i < m_SAVE_DATAS_MAX; ++i)
	{
		if (m_pPREVIEWS[i].m_clearNum != STAGE_MAX)	
		{
			continue;
		};

		//! 全てのステージをクリアしたセーブデータのみ
		TextFormat clearTextFormat;
		clearTextFormat.m_charHalfScale = { 20, 30 };
		clearTextFormat.m_topLeft = { 70.0f, 150.0f + 215.0f * i };

		clearTextFormat.m_color1 = 0xCCFFFF23;

		TString clearTextString(_T("CLEAR"));
		Text clearTextText(clearTextString, _T("2DTextures/Fonts/a_9.png"));

		clearTextText.Write(clearTextFormat);
	}
}

VOID SaveDataSaveDatas::RenderLastTimeBrief()
{
	for (INT i = 0; i < m_SAVE_DATAS_MAX; ++i)
	{
		TString lastTimeTextString(_T("LAST DATA"));
		Text lastTimeTextText(lastTimeTextString, _T("2DTextures/Fonts/a_9.png"));

		TextFormat lastTimeTextFormat;
		lastTimeTextFormat.m_charHalfScale = { 11, 15 };
		lastTimeTextFormat.m_topLeft = { 400.0f, 150.0f + 215.0f * i };

		lastTimeTextFormat.m_color1 = m_WORD_COLOR[i];

		lastTimeTextText.Write(lastTimeTextFormat);
	
		TString lastPlayStr(m_pPREVIEWS[i].pLastPlayTm->tm_year + 1900, _T("%d"));
		lastPlayStr.WriteInCharPrevEnd(_T('/'));
		lastPlayStr.WriteInNumPrevEnd(m_pPREVIEWS[i].pLastPlayTm->tm_mon + 1, _T("%d"));
		lastPlayStr.WriteInCharPrevEnd(_T('/'));
		lastPlayStr.WriteInNumPrevEnd(m_pPREVIEWS[i].pLastPlayTm->tm_mday, _T("%d"));
		Text lastPlayTxt(lastPlayStr, _T("2DTextures/Fonts/a_9.png"));

		TextFormat txtFormat;
		txtFormat.m_charHalfScale = { 11, 15 };
		txtFormat.m_topLeft = { 400.0f, 185.0f + 215.0f * i };

		txtFormat.m_color1 = m_WORD_COLOR[i];

		lastPlayTxt.Write(txtFormat);
	}
}

VOID SaveDataSaveDatas::RenderBriefDatas()
{
	RenderSaveDataNum();
	RenderClearAchievement();
	RenderTotalTimeBrief();
	RenderLastTimeBrief();
}

VOID SaveDataSaveDatas::RenderDetailFrame()
{
	ObjData detailFrameData;
	detailFrameData.m_center = { m_WND_SIZE.m_x * 0.77f, m_WND_SIZE.m_y * 0.5f, m_Z };
	detailFrameData.m_halfScale = { m_WND_SIZE.m_x * 0.21f, m_WND_SIZE.m_y * 0.45f, 0.0f };

	CustomVertex detailFrame[4];
	m_rGameLib.CreateRect(detailFrame, detailFrameData);

	m_rGameLib.SetLeftRightARGB(detailFrame, m_FRAME_COLOR[m_selectingData][0], m_FRAME_COLOR[m_selectingData][1]);

	m_rGameLib.Render(detailFrame, m_rGameLib.GetTex(_T("DetailFrame")));
}

VOID SaveDataSaveDatas::RenderDetailStageIcons()
{
	const FLOAT HALF_SCALE = 60.0f;							//! 作成する矩形の半分の幅

	const FLOAT ICON_SCALE = 300.0f;						//! 統合ファイルの中にあるアイコン一つの幅
	const D3DXVECTOR2 IMAGE_SCALE = { 2048.0f, 1024.0f };	//! 統合ファイルの幅

	for (INT i = 0; i < STAGE_MAX; ++i)
	{
		ObjData obj;
		obj.m_center = { 831.0f + 2 * (HALF_SCALE + 20) * (i % 3), 202.0f + 2 * (HALF_SCALE + 6) * (i / 3), m_Z };
		obj.m_halfScale = { HALF_SCALE, HALF_SCALE, 0.0f };

		obj.m_texUV =
		{
			ICON_SCALE * (i % 6) / IMAGE_SCALE.x,
			ICON_SCALE * (i / 6) / IMAGE_SCALE.y,
			ICON_SCALE * (i % 6 + 1) / IMAGE_SCALE.x,
			ICON_SCALE * (i / 6 + 1) / IMAGE_SCALE.y,
		};

		//! クリアしているステージは白色
		obj.m_aRGB = (i < m_pPREVIEWS[m_selectingData].m_clearNum) ? 0xFFFFFFFF : 0xFF333333;

		CustomVertex vertices[4];
		m_rGameLib.CreateRect(vertices, obj);

		if (obj.m_aRGB == 0xFFFFFFFF)
		{
			m_rGameLib.SetTopBottomARGB(vertices, 0xEEFFFF7F, 0xEEFFFFF4);
		}

		m_rGameLib.Render(vertices, m_rGameLib.GetTex(_T("StageIcons")));
	}
}

VOID SaveDataSaveDatas::RenderDetailData()
{
	TString dataTextString(_T("DATA "));
	dataTextString.WriteInNumPrevEnd(m_selectingData + 1, _T("%d"));
	Text dataTextText(dataTextString, _T("2DTextures/Fonts/a_9.png"));

	TextFormat dataTextFormat;
	dataTextFormat.m_charHalfScale = { 13, 19 };
	dataTextFormat.m_topLeft = { 772.0f, 53.0f };

	dataTextFormat.m_color1 = m_WORD_COLOR[m_selectingData];

	dataTextText.Write(dataTextFormat);

	RenderDetailStageIcons();
}
