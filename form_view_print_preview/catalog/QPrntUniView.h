#pragma once



// QPrntUniView view
class CGridCtrl;

class QPrntUniView : public CScrollView
{
	DECLARE_DYNCREATE(QPrntUniView)

protected:
	QPrntUniView();           // protected constructor used by dynamic creation
	virtual ~QPrntUniView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);

	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//virtual void OnPreviewPrint();
	DECLARE_MESSAGE_MAP()

public:
	void PrintPreview(CGridCtrl * ap_ctrl);
	void OnFilePrint();

	CGridCtrl *m_pCtrl;
	//CFrameWnd *m_pOldFrame;
};


