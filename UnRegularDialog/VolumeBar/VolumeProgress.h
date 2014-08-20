#pragma once


// CVolumeProgress

#define VOLUME_RCT_NUM	20

class CVolumeProgress : public CStatic
{
	DECLARE_DYNAMIC(CVolumeProgress)

public:
	CVolumeProgress();
	virtual ~CVolumeProgress();

protected:
	DECLARE_MESSAGE_MAP()

private:
	int m_rctNum;
	int m_rctWidth;
	int m_rctDistance;

	int m_rctNumTobePartFill;
	int m_overFlowLengh;

	int m_maxVolumeLength;
	int m_maxInnerVolumeLength;
	int m_actualVolumeLength;


	CBrush m_backgroundBrush;
	CBrush m_rctFrameBrush;
	CBrush m_rctProgressBrush;

	COLORREF m_backgroundColor;
	COLORREF m_rctFrameColor;
	COLORREF m_rctProgressColor;

	CRect m_volumeRct[VOLUME_RCT_NUM];
	CRect m_innerVolumeRct[VOLUME_RCT_NUM];

private:
	afx_msg void OnPaint();
	void InitializeVolumeRct(CRect rct);

public:
	int GetRctNum();
	int GetRctDistance();
	int GetVolumeLength();
	
	void SetBackgroundColor(COLORREF color);
	void SetRctFrameColor(COLORREF color);
	void SetProgressColor(COLORREF color);
	
	void SetVolume(int num); //0 =< num <= 100

	virtual BOOL Create(LPCTSTR lpszText, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, int rctNum, int rctWidth, int rctDistance, 
		COLORREF backgroundColor,COLORREF rctFrameColor,COLORREF rctProgressColor, UINT nID = 0xffff);
};


