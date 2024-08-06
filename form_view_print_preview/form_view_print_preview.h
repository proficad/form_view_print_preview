// form_view_print_preview.h : main header file for the form_view_print_preview application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// Cform_view_print_previewApp:
// See form_view_print_preview.cpp for the implementation of this class
//

class Cform_view_print_previewApp : public CBCGPWinApp
{
public:
	Cform_view_print_previewApp();

	// Override from CBCGPWorkspace
	virtual void PreLoadState();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	virtual BOOL SaveAllModified();


// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Cform_view_print_previewApp theApp;
