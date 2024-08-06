// form_view_print_previewDoc.cpp : implementation of the Cform_view_print_previewDoc class
//

#include "stdafx.h"
#include "form_view_print_preview.h"

#include "form_view_print_previewDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cform_view_print_previewDoc

IMPLEMENT_DYNCREATE(Cform_view_print_previewDoc, CDocument)

BEGIN_MESSAGE_MAP(Cform_view_print_previewDoc, CDocument)
END_MESSAGE_MAP()


// Cform_view_print_previewDoc construction/destruction

Cform_view_print_previewDoc::Cform_view_print_previewDoc()
{
	// TODO: add one-time construction code here

}

Cform_view_print_previewDoc::~Cform_view_print_previewDoc()
{
}

BOOL Cform_view_print_previewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

// Cform_view_print_previewDoc serialization

void Cform_view_print_previewDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// Cform_view_print_previewDoc diagnostics

#ifdef _DEBUG
void Cform_view_print_previewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cform_view_print_previewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Cform_view_print_previewDoc commands
