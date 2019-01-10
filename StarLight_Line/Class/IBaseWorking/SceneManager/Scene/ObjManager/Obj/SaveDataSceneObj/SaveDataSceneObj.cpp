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
	ObjData frameData;
	frameData.m_halfScale = { m_WND_SIZE.m_x * 0.2f, m_WND_SIZE.m_y * 0.12f, 0.0f };

	for (INT i = 0; i < m_SAVE_DATAS_MAX; ++i)
	{
		frameData.m_center = { m_WND_SIZE.m_x * 0.25f, m_WND_SIZE.m_y * (0.2f + 0.3f * i), m_Z };

		CustomVertex frame[4];
		m_rGameLib.CreateRect(frame, frameData);

		m_rGameLib.Render(frame, m_rGameLib.GetTex(_T("Frame")));
	}

	RenderBriefDatas();

	RenderDetailData();
}

VOID SaveDataSaveDatas::RenderBriefDatas()
{
	for (INT i = 0; i < m_SAVE_DATAS_MAX; ++i)
	{
		TextFormat txtFormat;
		txtFormat.m_charHalfScale = { 14, 14 };
		txtFormat.m_charGap = { -10.0f, 0.0f };
		txtFormat.m_topLeft = { 150, 175 + 215.0f * i };

		TString totalTimeStr_partHour(m_pPREVIEWS[i].m_totalTime_partHour, _T("%3d"));
		NumText totalTimeText_partHour(totalTimeStr_partHour, _T("2DTextures/Result/Nums.png"));
		totalTimeText_partHour.Write(txtFormat);

		TString totalTimeStr_partMin(m_pPREVIEWS[i].m_totalTime_partMin, _T("%2d"));
		NumText totalTimeText(totalTimeStr_partMin, _T("2DTextures/Result/Nums.png"));
		txtFormat.m_topLeft.x += txtFormat.m_charHalfScale.m_x * 5.0f;
		totalTimeText.Write(txtFormat);

		TString lastPlayStr_partYear(m_pPREVIEWS[i].pLastPlayTm->tm_year + 1900, _T("%d"));
		NumText lastPlayTxt_partYear(lastPlayStr_partYear, _T("2DTextures/Result/Nums.png"));
		txtFormat.m_topLeft.x += txtFormat.m_charHalfScale.m_x * 10.0f;
		lastPlayTxt_partYear.Write(txtFormat);

		TString lastPlayStr_partMonth(m_pPREVIEWS[i].pLastPlayTm->tm_mon + 1, _T("%d"));
		NumText lastPlayTxt_partMonth(lastPlayStr_partMonth, _T("2DTextures/Result/Nums.png"));
		txtFormat.m_topLeft.x += txtFormat.m_charHalfScale.m_x * 6.5f;
		lastPlayTxt_partMonth.Write(txtFormat);

		TString lastPlayStr_partDay(m_pPREVIEWS[i].pLastPlayTm->tm_mday, _T("%d"));
		NumText lastPlayTxt_partDay(lastPlayStr_partDay, _T("2DTextures/Result/Nums.png"));
		txtFormat.m_topLeft.x += txtFormat.m_charHalfScale.m_x * 3.5f;
		lastPlayTxt_partDay.Write(txtFormat);
	}
}

VOID SaveDataSaveDatas::RenderDetailData()
{
	ObjData detailFrameData;
	detailFrameData.m_center	= { m_WND_SIZE.m_x * 0.75f, m_WND_SIZE.m_y * 0.5f, m_Z };
	detailFrameData.m_halfScale = { m_WND_SIZE.m_x * 0.2f, m_WND_SIZE.m_y * 0.4f, 0.0f };

	CustomVertex detailFrame[4];
	m_rGameLib.CreateRect(detailFrame, detailFrameData);

	m_rGameLib.Render(detailFrame, m_rGameLib.GetTex(_T("DetailFrame")));

	TextFormat txtFormat;
	txtFormat.m_charHalfScale = { 25, 25 };
	txtFormat.m_charGap = { -12.5f, 0.0f };
	txtFormat.m_topLeft = { 750.0f, 250.0f };

	TString totalTimeStr_partHour(m_pPREVIEWS[m_selectingData].m_totalTime_partHour, _T("%3d"));
	NumText totalTimeText_partHour(totalTimeStr_partHour, _T("2DTextures/Result/Nums.png"));
	totalTimeText_partHour.Write(txtFormat);

	TString totalTimeStr_partMin(m_pPREVIEWS[m_selectingData].m_totalTime_partMin, _T("%2d"));
	NumText totalTimeText(totalTimeStr_partMin, _T("2DTextures/Result/Nums.png"));
	txtFormat.m_topLeft.x += txtFormat.m_charHalfScale.m_x * 5;
	totalTimeText.Write(txtFormat);

	TString lastPlayStr_partYear(m_pPREVIEWS[m_selectingData].pLastPlayTm->tm_year + 1900, _T("%d"));
	NumText lastPlayTxt_partYear(lastPlayStr_partYear, _T("2DTextures/Result/Nums.png"));
	txtFormat.m_topLeft = { 750.0f, 250.0f };
	txtFormat.m_topLeft.y += txtFormat.m_charHalfScale.m_y * 10;
	lastPlayTxt_partYear.Write(txtFormat);

	TString lastPlayStr_partMonth(m_pPREVIEWS[m_selectingData].pLastPlayTm->tm_mon + 1, _T("%d"));
	NumText lastPlayTxt_partMonth(lastPlayStr_partMonth, _T("2DTextures/Result/Nums.png"));
	txtFormat.m_topLeft.x += txtFormat.m_charHalfScale.m_x * 6.5f;
	lastPlayTxt_partMonth.Write(txtFormat);

	TString lastPlayStr_partDay(m_pPREVIEWS[m_selectingData].pLastPlayTm->tm_mday, _T("%d"));
	NumText lastPlayTxt_partDay(lastPlayStr_partDay, _T("2DTextures/Result/Nums.png"));
	txtFormat.m_topLeft.x += txtFormat.m_charHalfScale.m_x * 3.5f;
	lastPlayTxt_partDay.Write(txtFormat);
}
