// form_view_print_previewView.h : interface of the Cform_view_print_previewView class
//


#pragma once


class Cform_view_print_previewView : public CView
{
protected: // create from serialization only
	Cform_view_print_previewView();
	DECLARE_DYNCREATE(Cform_view_print_previewView)

// Attributes
public:
	Cform_view_print_previewDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~Cform_view_print_previewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnNcPaint();
	afx_msg void OnFilePrintPreview();
	afx_msg LRESULT OnPrintClient(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in form_view_print_previewView.cpp
inline Cform_view_print_previewDoc* Cform_view_print_previewView::GetDocument() const
	{ return reinterpret_cast<Cform_view_print_previewDoc*>(m_pDocument); }
#endif

