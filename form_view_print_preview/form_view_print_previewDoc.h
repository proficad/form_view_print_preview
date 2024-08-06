// form_view_print_previewDoc.h : interface of the Cform_view_print_previewDoc class
//


#pragma once


class Cform_view_print_previewDoc : public CDocument
{
protected: // create from serialization only
	Cform_view_print_previewDoc();
	DECLARE_DYNCREATE(Cform_view_print_previewDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~Cform_view_print_previewDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


