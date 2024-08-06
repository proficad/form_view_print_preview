// form_view_print_previewView.cpp : implementation of the Cform_view_print_previewView class
//

#include "stdafx.h"
#include "form_view_print_preview.h"

#include "form_view_print_previewDoc.h"
#include "form_view_print_previewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cform_view_print_previewView

IMPLEMENT_DYNCREATE(Cform_view_print_previewView, CView)

BEGIN_MESSAGE_MAP(Cform_view_print_previewView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_ERASEBKGND()
	ON_WM_NCPAINT()
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cform_view_print_previewView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_MESSAGE(WM_PRINTCLIENT, &Cform_view_print_previewView::OnPrintClient)
END_MESSAGE_MAP()

// Cform_view_print_previewView construction/destruction

Cform_view_print_previewView::Cform_view_print_previewView()
{
	// TODO: add construction code here

}

Cform_view_print_previewView::~Cform_view_print_previewView()
{
}

BOOL Cform_view_print_previewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Cform_view_print_previewView drawing

void Cform_view_print_previewView::OnDraw(CDC* pDC)
{
	Cform_view_print_previewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	if (!pDC->IsPrinting())
	{
		CRect rectClient;
		GetClientRect(rectClient);

		pDC->FillSolidRect(rectClient, CBCGPVisualManager::GetInstance()->GetControlFillColor());
	}
}


// Cform_view_print_previewView printing

void Cform_view_print_previewView::OnFilePrintPreview()
{
	BCGPPrintPreview (this);
}

BOOL Cform_view_print_previewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return BCGPPreparePrinting(this, pInfo);
}

void Cform_view_print_previewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Cform_view_print_previewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// Cform_view_print_previewView diagnostics

#ifdef _DEBUG
void Cform_view_print_previewView::AssertValid() const
{
	CView::AssertValid();
}

void Cform_view_print_previewView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cform_view_print_previewDoc* Cform_view_print_previewView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cform_view_print_previewDoc)));
	return (Cform_view_print_previewDoc*)m_pDocument;
}
#endif //_DEBUG


// Cform_view_print_previewView message handlers

BOOL Cform_view_print_previewView::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

LRESULT Cform_view_print_previewView::OnPrintClient(WPARAM wp, LPARAM lp)
{
	if ((lp & PRF_CLIENT) == PRF_CLIENT)
	{
		CDC* pDC = CDC::FromHandle((HDC)wp);
		ASSERT_VALID(pDC);

		OnDraw(pDC);
	}

	return 0;
}

void Cform_view_print_previewView::OnNcPaint()
{
	if (!CBCGPVisualManager::GetInstance()->OnDrawViewBorder(this))
	{
		Default();
	}
}

void Cform_view_print_previewView::OnContextMenu(CWnd*, CPoint point)
{
	if (CBCGPPopupMenu::GetSafeActivePopupMenu() != NULL)
	{
		return;
	}

	theApp.ShowPopupMenu(IDR_CONTEXT_MENU, point, this);
}
