#pragma once



// QPrntSymView form view

class QFontCollection;
struct PositionAspect;

class QPrntSymView : public CBCGPFormView
{
	DECLARE_DYNCREATE(QPrntSymView)

protected:
	QPrntSymView();           // protected constructor used by dynamic creation
	virtual ~QPrntSymView();


	enum { IDD = IDD_QPRNTSYMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnInitialUpdate();


afx_msg LRESULT OnCheckbox(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()




public:
	void OnPrintPreview(void);
	void OnPrint(CDC* pDC, CPrintInfo* pInfo);
//	void OnPrintTemp(CDC* pDC, CPrintInfo* pInfo);

	afx_msg void OnBnClickedButton1();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

//	void CheckTreeItems(const HTREEITEM l_itemRoot, BOOL ab_check);


private:
	CBCGPTreeCtrlEx  m_wndTree;
	CStringArray m_listGroups;
	int m_counter;

	CStatic m_ctrl_echo;
	CSliderCtrl m_ctrl_density;
	CStatic m_ctrl_number_of_pages;
	CBrush m_brushBackground;
	COLORREF m_colorBackground;

	void AddFoldersToTreeViewItem(const CString & as_libPath, HTREEITEM a_item, CString as_path, CString as_path2Select);

	void BuildList();
	void BuildList(HTREEITEM hItem);

	CString GetItemPath( HTREEITEM hItem );
	BOOL GetItemPath(CBCGPTreeCtrlEx& a_tree, HTREEITEM hItem, CStringArray& sa, CPtrArray& items);


	static int AddItemsToList(const CString & as_pathLib, const CString & as_pathCurrent, CStringArray & a_listGroups);
	void PrintPageFooter(CDC *pDC, int pagewidth, int pagebottom, UINT pageno);
	void PrintPageHeader(CDC *pDC, int leftedge, int pagetop);
	void CalcCellSize(CDC *pDC);


	void PrintSymbol(CDC * pDC, CString as_miniPath, int x, int y, CRect a_rect);

	void DrawLabel(CDC * pDC, CString ls_temp, CRect a_rect) const;

	void CalcScaleAndPrepareMapMode(CSize &a_size, CRect &a_rect, CDC * pDC, int a_x, int a_y, int li_topoffset, PositionAspect & a_pa);

	static void CreateFont(CFont & a_font);
	void FillTree();
	int CalcNumberOfPages();
	void RefreshEchoNumberOfPages();

	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);


	UINT	m_nPDCount;//count of the PD being printed
	CSize	m_PrintCell;//cell of the printed PD
	UINT	m_nPDPointer;//number of the PD being printed
	int		m_numOfCellsShorterSide;
	int		m_heightOfHeader;
	int		m_heightOfFooter;
	int		m_sideMargin;
	CRect	m_rectDraw;
	CString m_libPath;
	QFontCollection* m_fontCollection;


	int		m_cellsinrow;
	int		m_cellsincolumn;
	int		m_cellsinpage;


	
	void ExpandTreeItem(CBCGPTreeCtrlEx& tree, HTREEITEM hItem, UINT nCode);
	BOOL Check_Children_And_Parent(LPARAM a_lp);
	static bool Is_Checked(CBCGPTreeCtrlEx& a_wndTree, HTREEITEM a_hItem);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CButton m_btn_preview;
	afx_msg void OnBnClickedButtonClose();
};


