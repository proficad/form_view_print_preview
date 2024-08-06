// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// QPrntSymView.cpp : implementation file
//

#include "../stdafx.h"
#include "../resource.h"
#include "QPrntSymView.h"


#define TREE_VIEW_CHECK_STATE_CHANGE (WM_USER + 100)

// QPrntSymView

IMPLEMENT_DYNCREATE(QPrntSymView, CBCGPFormView)

QPrntSymView::QPrntSymView()
	: CBCGPFormView(QPrntSymView::IDD),
	m_nPDCount(0),
	m_nPDPointer(0)
{
	m_PrintCell.cx = 1400;
	m_PrintCell.cy = 1400;

	m_numOfCellsShorterSide = 3;
	m_heightOfHeader = 100;
	m_heightOfFooter = 100;
	m_sideMargin = 100;

	m_cellsinrow = 1;
	m_cellsincolumn = 1;
	m_cellsinpage = 1;





	//COLORREF l_color(RGB(201,223,255));
	m_colorBackground = RGB(201,223,255);
	m_brushBackground.CreateSolidBrush(m_colorBackground);

}



QPrntSymView::~QPrntSymView()
{


}


void QPrntSymView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPFormView::DoDataExchange(pDX);
	
	//	DDX_Control(pDX, IDC_LIST1, m_ctrl_list);
	DDX_Control(pDX, IDC_ECHO, m_ctrl_echo);
	DDX_Control(pDX, IDC_SLIDER_DENSITY, m_ctrl_density);
	DDX_Control(pDX, IDC_NUMBER_PAGES, m_ctrl_number_of_pages);
	DDX_Control(pDX, ID_FILE_PRINT_PREVIEW, m_btn_preview);
}

BEGIN_MESSAGE_MAP(QPrntSymView, CBCGPFormView)

	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnPrintPreview)
	//ON_REGISTERED_MESSAGE(WM_XHTMLTREE_CHECKBOX_CLICKED, OnCheckbox)
	ON_REGISTERED_MESSAGE(BCGM_GRID_ROW_CHECKBOX_CLICK, OnCheckbox)
	ON_WM_HSCROLL()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &QPrntSymView::OnBnClickedButtonClose)
END_MESSAGE_MAP()


// QPrntSymView diagnostics

#ifdef _DEBUG
void QPrntSymView::AssertValid() const
{
	CBCGPFormView::AssertValid();
}

#ifndef _WIN32_WCE
void QPrntSymView::Dump(CDumpContext& dc) const
{
	CBCGPFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// QPrntSymView message handlers


void QPrntSymView::OnPrintPreview(void)
{
	m_numOfCellsShorterSide = m_ctrl_density.GetPos();
	CBCGPFormView::OnFilePrintPreview();
}


void QPrntSymView::OnBnClickedButton1()
{
	OnPrintPreview();
}

BOOL QPrntSymView::OnPreparePrinting(CPrintInfo* pInfo)
{



	int	li_pagesinreport = CalcNumberOfPages();

	pInfo->SetMinPage(1);
	pInfo->SetMaxPage(li_pagesinreport);

	// default preparation
	return DoPreparePrinting(pInfo);
}

int QPrntSymView::CalcNumberOfPages()
{

	CPrintDialog dlg(FALSE);

	// Retrieve the current printer defaults from the Windows .ini file
	// as necessary, or uses the last printer configuration set by the
	// user in Print Setup.
	CWinApp* app = AfxGetApp();
	if (!app->GetPrinterDeviceDefaults(&dlg.m_pd))
	{
		// Fails to create a printer device context for printing because
		// no printer is being installed. Bring up dialog box to alert the
		// users that they need to install a printer.  This step is optional.
		if (app->DoPrintDialog(&dlg) != IDOK)
			return 0;
	}

	// Creates a printer DC from the DEVMODE and DEVNAMES structures.
	if (dlg.CreatePrinterDC() == NULL)
		return 0;

	// A printer device context (DC) has been created.
	// Attach it to a CDC object. The DC is deleted when the CDC
	// object goes out of scope.
	CDC dc;
	dc.Attach(dlg.m_pd.hDC);

	dc.SetMapMode(MM_ANISOTROPIC);
	dc.SetViewportExt(dc.GetDeviceCaps(LOGPIXELSX),	dc.GetDeviceCaps(LOGPIXELSY));
	int xx = 250;
	dc.SetWindowExt(xx, xx);


	m_nPDPointer = 1;//points to the 1st PD
	m_nPDCount = m_listGroups.GetSize();

	CalcCellSize(&dc);

	m_cellsinrow		= m_rectDraw.Width()/m_PrintCell.cx;
	m_cellsincolumn		= m_rectDraw.Height()/m_PrintCell.cy;
	m_cellsinpage		= m_cellsinrow * m_cellsincolumn;
	int	li_pagesinreport	= m_nPDCount / m_cellsinpage; if ((m_nPDCount % m_cellsinpage) > 0) ++ li_pagesinreport;
	return li_pagesinreport;
}


void QPrntSymView::OnPrint(CDC *pDC, CPrintInfo *pInfo)
{
	m_numOfCellsShorterSide = m_ctrl_density.GetPos();

	
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetViewportExt(pDC->GetDeviceCaps(LOGPIXELSX),	pDC->GetDeviceCaps(LOGPIXELSY));
	int xx = 250;
	pDC->SetWindowExt(xx, xx);


	int li_leftoffset = m_sideMargin;
	int	li_topoffset = m_heightOfHeader;
	CRect	l_rect;

	m_nPDPointer = 1 + (m_cellsinpage * (pInfo->m_nCurPage - 1));


	//draw the cell for the current page
	for(int y = 1; y <= m_cellsincolumn; y++)
	for(int x = 1; x <= m_cellsinrow; x++)
	if (m_nPDPointer <= m_nPDCount)
	{
		CString ls_path = m_listGroups[m_nPDPointer - 1];

		l_rect.SetRect((x - 1) * m_PrintCell.cx , (y - 1) * m_PrintCell.cy, x * m_PrintCell.cx + 1,	y * m_PrintCell.cy + 1);

		l_rect.OffsetRect(li_leftoffset, li_topoffset);
		pDC->Rectangle(l_rect);
		//===========================
		PrintSymbol(pDC, ls_path, x, y, l_rect);
		//===========================
		++ m_nPDPointer;
	}

	PrintPageHeader(pDC, li_leftoffset, li_topoffset);
	PrintPageFooter(pDC, m_rectDraw.Width(), m_rectDraw.bottom, pInfo->m_nCurPage);
}



void QPrntSymView::PrintPageHeader(CDC *pDC, int leftedge, int pagetop)
{


	CFont l_font; CreateFont(l_font);
	pDC->SelectObject(&l_font);

	CSize size = pDC->GetTextExtent(m_libPath);
	//	int li_pos_x = (pagewidth - size.cx)/2;
	pDC->TextOut(leftedge, pagetop - size.cy - 10, m_libPath);
}


void QPrntSymView::PrintPageFooter(CDC *pDC, int pagewidth, int pagebottom, UINT pageno)
{

	
	CFont l_font; CreateFont(l_font);
	pDC->SelectObject(&l_font);



	CString ls_page = L"ids_page";

	CString	ls_footer;
	ls_footer = ls_page + _T(" ?");
	CSize size = pDC->GetTextExtent(ls_footer);
	int li_pos_x = (pagewidth - size.cx)/2;
	pDC->TextOut(li_pos_x, pagebottom + 20, ls_footer);
}


void QPrntSymView::OnInitialUpdate()
{
	CBCGPFormView::OnInitialUpdate();

	UINT nTreeStyles = WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | TVS_LINESATROOT | TVS_SHOWSELALWAYS | TVS_CHECKBOXES | TVS_HASBUTTONS;

	m_wndTree.CreateOnPlaceHolder(this, IDC_TREE, 0, nTreeStyles);

	m_ctrl_echo.ShowWindow(SW_HIDE);
	m_ctrl_number_of_pages.ShowWindow(SW_HIDE);

	ASSERT(::IsWindow(m_wndTree.GetSafeHwnd()));

	m_wndTree.EnableTreeLines(TRUE);
	m_wndTree.EnableTreeButtons(TRUE);// needs TVS_HASBUTTONS



	FillTree();

	if (IsVisualManagerStyle())
	{
		m_wndTree.SetVisualManagerColorTheme();
	}


	m_ctrl_density.SetRange(3, 6);
	
	m_numOfCellsShorterSide = m_ctrl_density.GetPos();


}


void QPrntSymView::FillTree()
{
	const CString ls_rootLabel = L"World";
	const HTREEITEM l_itemRoot = m_wndTree.InsertItem(ls_rootLabel, TVI_ROOT, TVI_SORT);

	// First remove the checkbox style
	m_wndTree.ModifyStyle(TVS_CHECKBOXES, 0);
	// Then explicitly set it
	m_wndTree.ModifyStyle(0, TVS_CHECKBOXES);


	//path to the library
	const CString ls_libPath = L"haha";

	AddFoldersToTreeViewItem(ls_libPath, l_itemRoot, ls_libPath, _T(""));

	m_wndTree.Expand(l_itemRoot, TVE_EXPAND);
	m_wndTree.AdjustLayout();
}



void QPrntSymView::AddFoldersToTreeViewItem(const CString & as_libPath, HTREEITEM a_item, CString as_path, CString as_path2Select )
{
	if(as_path.Right(1) != "\\"){
		as_path += "\\";
	}

	WIN32_FIND_DATA fd;
	HANDLE hFind;

	hFind = ::FindFirstFile(as_path + "*.*", &fd);
	if(hFind != INVALID_HANDLE_VALUE){
		do{
			if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
				const CString ls_name = fd.cFileName;
				if((ls_name != ".")&&(ls_name != "..")&&(ls_name.Left(1) != "_")){
					const HTREEITEM l_item = m_wndTree.InsertItem(ls_name, a_item, TVI_SORT);

					if (l_item != NULL) //2009-11-29
					{
						if (as_libPath + "\\" + as_path2Select == as_path + ls_name)
						{
//							a_tree.Select(l_item, TVGN_CARET);
						}

						AddFoldersToTreeViewItem(as_libPath, l_item, as_path + ls_name, as_path2Select);
					}
				}
			}
		}
		while(::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
}


LRESULT QPrntSymView::OnCheckbox(WPARAM, LPARAM a_lp)
{
	Check_Children_And_Parent(a_lp);

	BuildList();
	RefreshEchoNumberOfPages();
	return TRUE;
}



void QPrntSymView::BuildList()
{

}


void QPrntSymView::BuildList(HTREEITEM a_hItem)
{

	CString ls_pathCurrent = GetItemPath(a_hItem);
	

	if (Is_Checked(m_wndTree, a_hItem))
	{
		m_counter += AddItemsToList(m_libPath, ls_pathCurrent, m_listGroups);
	}


	if (const HTREEITEM hItemChild = m_wndTree.GetChildItem(a_hItem))
	{
		BuildList(hItemChild);
	}

	if(const HTREEITEM hItemNext = m_wndTree.GetNextSiblingItem(a_hItem))
	{
		BuildList(hItemNext);
	}
}


CString QPrntSymView::GetItemPath( HTREEITEM hItem )
{
	CStringArray l_arrayGroups;
	CPtrArray l_arrayItems;
	CString ls_result;
	
	if(GetItemPath(m_wndTree, hItem, l_arrayGroups, l_arrayItems))
	{
		const int li_size = l_arrayGroups.GetSize();

		//skip the 0th item because that is the "all" item
		for (int li_i = 1; li_i < li_size; li_i ++)
		{
			ls_result += (l_arrayGroups[li_i] + _T("\\"));
		}
	}
	
	return ls_result;
}

BOOL QPrntSymView::GetItemPath(CBCGPTreeCtrlEx& a_tree, HTREEITEM hItem, CStringArray& sa, CPtrArray& items)
{
	BOOL rc = FALSE;

	sa.RemoveAll();
	items.RemoveAll();

	if (hItem == NULL)
		hItem = a_tree.GetRootItem();

	if (hItem)
	{
		CStringArray path;
		CPtrArray htreeitems;

		// get the path in reverse order
		while (hItem)
		{
			CString strText = a_tree.GetItemText(hItem);

#ifdef XHTMLHTML
			// remove html tags
			CXHtmlDraw hd;
			TCHAR s[200];
			hd.GetPlainText(strText, s, sizeof(s) / sizeof(TCHAR) - 1);
			strText = s;
#endif // XHTMLHTML
			path.Add(strText);
			htreeitems.Add(hItem);
			hItem = a_tree.GetParentItem(hItem);
		}

		int n = (int)path.GetSize();
		if (n)
		{
			// return path in correct order
			for (int i = n - 1; i >= 0; i--)
			{
				sa.Add(path[i]);
				items.Add(htreeitems[i]);
			}

			rc = TRUE;
		}
	}

	return rc;
}

int QPrntSymView::AddItemsToList(const CString & as_pathLib, const CString & as_pathCurrent, CStringArray & a_listGroups)
{
	return 0;
}


void QPrntSymView::CalcCellSize(CDC* pDC)
{
	//calculate the numbers of cells per page
	m_rectDraw.left = 0;
	m_rectDraw.top = 0;

	m_rectDraw.right = pDC->GetDeviceCaps(HORZRES);
	m_rectDraw.bottom = pDC->GetDeviceCaps(VERTRES);

	pDC->DPtoLP(m_rectDraw);

	//pDC->Rectangle(m_rectDraw);

	m_rectDraw.top += m_heightOfHeader;
	m_rectDraw.bottom -= m_heightOfFooter;
	m_rectDraw.left += m_sideMargin;
	m_rectDraw.right -= m_sideMargin;

	//pDC->Rectangle(m_rectDraw);

	int li_shorterSize = min(m_rectDraw.Width(), m_rectDraw.Height());

	//for now only square shaped cells
	int li_cellWidth = li_shorterSize / m_numOfCellsShorterSide;

	m_PrintCell.cx = li_cellWidth;
	m_PrintCell.cy = li_cellWidth;
}


void QPrntSymView::PrintSymbol(CDC * pDC, CString as_miniPath,  int a_x, int a_y, CRect a_rect)
{


}

void QPrntSymView::CreateFont(CFont & a_font)
{
	a_font.CreateFont(-24, 0, 0, 0, 600, FALSE, FALSE,
		0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_MODERN, _T("Arial"));
}


void QPrntSymView::CalcScaleAndPrepareMapMode(CSize &a_size, CRect &a_rect, CDC * pDC, int a_x, int a_y, int li_topoffset, PositionAspect & a_pa)
{

}

void QPrntSymView::DrawLabel( CDC * pDC, CString as_temp, CRect a_rect) const
{
	const double li_scale = (m_numOfCellsShorterSide / 3.0);

	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetViewportExt(pDC->GetDeviceCaps(LOGPIXELSX),	pDC->GetDeviceCaps(LOGPIXELSY));
	int xx = (int)(li_scale * 250);
	pDC->SetWindowExt(xx, xx);

#pragma warning(push)
#pragma warning(disable : 4244)
	a_rect.left *= li_scale;
	a_rect.top *= li_scale;
	a_rect.right *= li_scale;
	a_rect.bottom *= li_scale;
#pragma warning(pop)

	CRect l_rect = a_rect;
	pDC->DrawText(as_temp, l_rect, DT_CALCRECT | DT_WORDBREAK);
	a_rect.top += l_rect.Height();
	a_rect.bottom -= l_rect.Height();
	pDC->DrawText(as_temp, l_rect, DT_WORDBREAK);
}


void QPrntSymView::OnHScroll(UINT /*nSBCode*/, UINT /*nPos*/, CScrollBar* /*pScrollBar*/)
{
	m_numOfCellsShorterSide = m_ctrl_density.GetPos();
	RefreshEchoNumberOfPages();
}

void QPrntSymView::RefreshEchoNumberOfPages()
{
	
}



BOOL QPrntSymView::OnEraseBkgnd(CDC* pDC)
{
	CRect l_rect;
	GetClientRect(&l_rect);
	pDC->FillRect(&l_rect, &m_brushBackground);
	return TRUE;
	
	//return CBCGPFormView::OnEraseBkgnd(pDC);
}


HBRUSH QPrntSymView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	
	HBRUSH hbr = CBCGPFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	TCHAR classname[MAX_PATH];
	if(::GetClassName(pWnd->m_hWnd, classname, MAX_PATH) == 0)
		return hbr;
	if(_tcsicmp(classname, _T("EDIT")) == 0)
		return hbr;
	if(_tcsicmp(classname, _T("COMBOBOX")) == 0)
		return hbr;
	if(_tcsicmp(classname, _T("COMBOLBOX")) == 0)
		return hbr;
	if(_tcsicmp(classname, _T("LISTBOX")) == 0)
		return hbr;
	if(_tcsicmp(classname, WC_TREEVIEW) == 0)
		return hbr;


	pDC->SetBkColor(m_colorBackground);
	
	return (HBRUSH) m_brushBackground;
	
}



void QPrntSymView::ExpandTreeItem(CBCGPTreeCtrlEx& tree, HTREEITEM hItem, UINT nCode)
{
	HTREEITEM hChild;

	if (tree.ItemHasChildren(hItem))
	{
		tree.Expand(hItem, nCode);
		hChild = tree.GetChildItem(hItem);

		while (hChild)
		{
			ExpandTreeItem(tree, hChild, nCode);
			hChild = tree.GetNextItem(hChild, TVGN_NEXT);
		}
	}
}

BOOL QPrntSymView::Check_Children_And_Parent(LPARAM a_lp)
{
	CBCGPGridRow* pRow = (CBCGPGridRow*)a_lp;
	if (pRow == NULL)
	{
		return 0;
	}

	ASSERT_VALID(pRow);

	if (pRow->HasCheckBox())
	{
		BOOL bChecked = pRow->GetCheck();

		// check the row
		pRow->SetCheck(!bChecked);

		// check the subitems
		pRow->CheckSubItems(!bChecked);

		// update parent items
		pRow->UpdateParentCheckbox(TRUE/* use 3 state checkboxes */);

		// update the header control
		m_wndTree.UpdateHeaderCheckbox(TRUE /* bDisplayIntermediateState */);
	}

	return TRUE; // disable the default implementation
}

bool QPrntSymView::Is_Checked(CBCGPTreeCtrlEx& a_wndTree, HTREEITEM a_hItem)
{
	// Use TVITEM to get the item's state
	TVITEM tvItem;
	tvItem.mask = TVIF_HANDLE | TVIF_STATE;
	tvItem.hItem = a_hItem;
	a_wndTree.GetItem(&tvItem);

	if (tvItem.state & TVIS_STATEIMAGEMASK)
	{
		CString strItemText = a_wndTree.GetItemText(a_hItem);
		int imageIndex = (tvItem.state & TVIS_STATEIMAGEMASK) >> 12;
		if (imageIndex == 2) // Assuming 2 is the checked state image index
		{
			return true;
			// ... process the checked item text (strItemText) here ...
		}
	}

	return false;
}

void QPrntSymView::OnBnClickedButtonClose()
{
	 GetParentFrame()->PostMessage(WM_CLOSE);
}
