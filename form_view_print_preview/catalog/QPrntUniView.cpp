// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// QPrntUniView.cpp : implementation file
//

#include "../stdafx.h"
#include "QPrntUniView.h"
#include "../../common/QUtilsDraw.h"
#include "../../GridCtrl/GridCtrl.h"

// QPrntUniView

IMPLEMENT_DYNCREATE(QPrntUniView, CScrollView)

QPrntUniView::QPrntUniView()
:m_pCtrl(nullptr)
{
}

QPrntUniView::~QPrntUniView()
{
}


BEGIN_MESSAGE_MAP(QPrntUniView, CScrollView)
	
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)

END_MESSAGE_MAP()


// QPrntUniView drawing

void QPrntUniView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void QPrntUniView::OnDraw(CDC* )
{
//	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// QPrntUniView diagnostics

#ifdef _DEBUG
void QPrntUniView::AssertValid() const
{
	CScrollView::AssertValid();
}



void QPrntUniView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
void QPrntUniView::PrintPreview(CGridCtrl * ap_ctrl)
{
	m_pCtrl = ap_ctrl;
	CView::OnFilePrintPreview();
}

BOOL QPrntUniView::OnPreparePrinting(CPrintInfo* pInfo)
{
	QUtilsDraw::SetupPrinterOri(OriPortrait, nullptr);


	pInfo->SetMinPage(1);
	
	// default preparation
	return DoPreparePrinting(pInfo);
}

void QPrntUniView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	/*
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetViewportExt(pDC->GetDeviceCaps(LOGPIXELSX), pDC->GetDeviceCaps(LOGPIXELSY));
	int xx = 250;
	pDC->SetWindowExt(xx, xx);

	pDC->Ellipse(10, 10, 1000, 1000);
	CString ls_what = _T("strana ") + Int2String(pInfo->m_nCurPage);
	CRect l_rect(500, 500, 1000, 1000);
	pDC->DrawText(ls_what, l_rect, DT_CENTER); //TextOut(500, 500, ls_what);
	*/
	if (m_pCtrl)
	{
		m_pCtrl->OnPrint(pDC, pInfo);
	}
	
}
//this is called when user cancels PP and ALSO before the actual printing
void QPrntUniView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView)
{
	CView::OnEndPrintPreview(pDC, pInfo, point, pView);

	GetParentFrame()->PostMessage(WM_CLOSE);

}

void QPrntUniView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	if (m_pCtrl)
	{
		m_pCtrl->OnBeginPrinting(pDC, pInfo);
	}
}

void QPrntUniView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	if (m_pCtrl)
	{
		m_pCtrl->OnEndPrinting(pDC, pInfo);
	}
}


void QPrntUniView::OnFilePrint()
{
	if (m_pCtrl)
	{
		m_pCtrl->Print();
	}
}





// QPrntUniView message handlers
