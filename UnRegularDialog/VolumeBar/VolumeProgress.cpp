// VolumeProgress.cpp : implementation file
//

#include "stdafx.h"
#include "VolumeBar.h"
#include "VolumeProgress.h"


// CVolumeProgress

IMPLEMENT_DYNAMIC(CVolumeProgress, CStatic)

CVolumeProgress::CVolumeProgress()
{

}

CVolumeProgress::~CVolumeProgress()
{
}


BEGIN_MESSAGE_MAP(CVolumeProgress, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CVolumeProgress message handlers




BOOL CVolumeProgress::Create(LPCTSTR lpszText, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd,int rctNum, int rctWidth, int rctDistance,
							COLORREF backgroundColor,COLORREF rctFrameColor,COLORREF rctProgressColor,UINT nID)
{
	m_rctNumTobePartFill = 0;

	if(rctNum > VOLUME_RCT_NUM)
	{
		m_rctNum = VOLUME_RCT_NUM;
	}
	else
	{
		m_rctNum = rctNum;
	}

	ASSERT(rctNum * rctWidth + (rctNum - 1)*rctDistance <= (rect.right - rect.left) );

	m_rctWidth = rctWidth;
	m_rctDistance = rctDistance;

	m_backgroundColor = backgroundColor;
	m_rctFrameColor = rctFrameColor;
	m_rctProgressColor = rctProgressColor;

	m_backgroundBrush.CreateSolidBrush(m_backgroundColor);
	m_rctFrameBrush.CreateSolidBrush(m_rctFrameColor);
	m_rctProgressBrush.CreateSolidBrush(m_rctProgressColor);

	m_maxInnerVolumeLength = 0;
	m_overFlowLengh = 0;
	m_actualVolumeLength = 0;
	m_maxVolumeLength = m_rctNum * m_rctWidth + (m_rctNum - 1) * m_rctDistance;

	InitializeVolumeRct(rect);

	return CStatic::Create(lpszText, dwStyle, rect, pParentWnd, nID);
}

void CVolumeProgress::InitializeVolumeRct(CRect rct)
{
	for (int i = 0; i < m_rctNum; i++)
	{
		CRect tempRct;

		m_volumeRct[i].left = i * (m_rctWidth + m_rctDistance);
		m_volumeRct[i].top = rct.top;
		m_volumeRct[i].right = m_volumeRct[i].left + m_rctWidth;
		m_volumeRct[i].bottom = rct.bottom;

		tempRct = m_volumeRct[i];

		tempRct.InflateRect(-1,-1);

		m_innerVolumeRct[i] = tempRct;

		m_maxInnerVolumeLength += m_innerVolumeRct[i].Width();
	}
}

void CVolumeProgress::OnPaint()
{
	CPaintDC dc(this); 

	for (int i = 0; i < m_rctNum; i++)
	{
		dc.FillRect(m_volumeRct[i],&m_rctFrameBrush);

		if (i < m_rctNumTobePartFill)
		{
			dc.FillRect(m_innerVolumeRct[i],&m_rctProgressBrush);
		}
		else if ( i == m_rctNumTobePartFill)
		{
			CRect leftRct = m_innerVolumeRct[i];
			CRect rightRct = m_innerVolumeRct[i];

			leftRct.InflateRect(0,0,-(m_innerVolumeRct[i].Width() - m_overFlowLengh),0);
			rightRct.InflateRect(- m_overFlowLengh,0,0,0);

			dc.FillRect(leftRct,&m_rctProgressBrush);
			dc.FillRect(rightRct,&m_backgroundBrush);
		}
		else
		{
			dc.FillRect(m_innerVolumeRct[i],&m_backgroundBrush);
		}
	}
}

int CVolumeProgress::GetRctNum()
{
	return m_rctNum;
}

int CVolumeProgress::GetRctDistance()
{
	return m_rctDistance;
}

int CVolumeProgress::GetVolumeLength()
{
	return m_maxVolumeLength;
}

void CVolumeProgress::SetBackgroundColor(COLORREF color)
{
	m_backgroundColor = color;
}

void CVolumeProgress::SetRctFrameColor(COLORREF color)
{
	m_rctFrameColor = color;
}

void CVolumeProgress::SetProgressColor(COLORREF color)
{
	m_rctProgressColor = color;
}

void CVolumeProgress::SetVolume(int num)
{
	m_actualVolumeLength = num * m_maxInnerVolumeLength / 100;

	if(m_innerVolumeRct[0].Width() !=0)
	{
		m_rctNumTobePartFill = m_actualVolumeLength / m_innerVolumeRct[0].Width();
		m_overFlowLengh = m_actualVolumeLength % m_innerVolumeRct[0].Width();
	}
	
	Invalidate();
}
