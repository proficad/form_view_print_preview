// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// QPrntSymDoc.cpp : implementation file
//

#include "../stdafx.h"
#include "QPrntSymDoc.h"
//#include "../../common/QTranslator.h"

// QPrntSymDoc

IMPLEMENT_DYNCREATE(QPrntSymDoc, CDocument)

QPrntSymDoc::QPrntSymDoc()
{
}

BOOL QPrntSymDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	//ids_print_library

	return TRUE;
}

QPrntSymDoc::~QPrntSymDoc()
{
}


BEGIN_MESSAGE_MAP(QPrntSymDoc, CDocument)
END_MESSAGE_MAP()


// QPrntSymDoc diagnostics

#ifdef _DEBUG
void QPrntSymDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void QPrntSymDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// QPrntSymDoc serialization

void QPrntSymDoc::Serialize(CArchive& ar)
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
#endif


// QPrntSymDoc commands
