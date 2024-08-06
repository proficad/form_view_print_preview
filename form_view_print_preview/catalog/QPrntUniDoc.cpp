// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// QPrntUniDoc.cpp : implementation file
//

#include "../stdafx.h"
#include "QPrntUniDoc.h"


// QPrntUniDoc

IMPLEMENT_DYNCREATE(QPrntUniDoc, CDocument)

QPrntUniDoc::QPrntUniDoc()
{
}

BOOL QPrntUniDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

QPrntUniDoc::~QPrntUniDoc()
{
}


BEGIN_MESSAGE_MAP(QPrntUniDoc, CDocument)
END_MESSAGE_MAP()


// QPrntUniDoc diagnostics

#ifdef _DEBUG
void QPrntUniDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void QPrntUniDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// QPrntUniDoc serialization

void QPrntUniDoc::Serialize(CArchive& ar)
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


// QPrntUniDoc commands
