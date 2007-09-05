#pragma once

/*
	* SubClass mIRC windows for docking with new layout engine.
*/

#include "../../defines.h"

#define DOCK_TYPE_SWITCH	0x00
#define DOCK_TYPE_TOOL		0x01
#define DOCK_TYPE_TREE		0x02
#define DOCK_TYPE_MDI			0x03

#define DOCKF_NORMAL	0x01	//!< No special flags.
#define DOCKF_AUTOH		0x02	//!< Auto Horizontal size.
#define DOCKF_AUTOV		0x04	//!< Auto Vertical size.
#define DOCKF_SIZE		0x08	//!< Auto Horizontal & Vertical size.
#define DOCKF_LEFT		0x10  //!< Dock to left. (UltraDock)
#define DOCKF_RIGHT		0x20	//!< Dock to right. (UltraDock)
#define DOCKF_TOP			0x40	//!< Dock to top. (UltraDock)
#define DOCKF_BOTTOM	0x80	//!< Dock to bottom. (UltraDock)
#define DOCKF_NOSCROLLBARS	0x100	//!< Disable parenst scrollbars.

#define TREEBAR_COLOUR_SELECTED				0
#define TREEBAR_COLOUR_SELECTED_BKG		1
#define TREEBAR_COLOUR_MESSAGE				2
#define TREEBAR_COLOUR_MESSAGE_BKG		3
#define TREEBAR_COLOUR_EVENT					4
#define TREEBAR_COLOUR_EVENT_BKG			5
#define TREEBAR_COLOUR_HIGHLIGHT			6
#define TREEBAR_COLOUR_HIGHLIGHT_BKG	7
#define TREEBAR_COLOUR_MAX						7

typedef struct tagDCXULTRADOCK {
	HWND hwnd;
	DWORD flags;
	DWORD old_styles;
	DWORD old_exstyles;
	RECT rc;
} DCXULTRADOCK, *LPDCXULTRADOCK;

typedef std::vector<LPDCXULTRADOCK> VectorOfDocks;

class DcxDock
{
public:
	DcxDock(HWND refHwnd, HWND dockHwnd, int dockType);
	virtual ~DcxDock(void);

	virtual bool DockWindow(HWND hwnd, const TString &flag);
	virtual void UnDockWindow(HWND hwnd);
	void UpdateLayout(void) const { SendMessage(this->m_hParent,WM_SIZE,NULL,NULL); };
	bool FindDock(const HWND hwnd);
	bool isDocked(const HWND hwnd);
	LPDCXULTRADOCK GetDock(const HWND hwnd);
	virtual void AdjustRect(WINDOWPOS *wp);
	void RedrawRef(void);

	// Statusbar Functions.
	static bool InitStatusbar(const TString &styles);
	static void UnInitStatusbar(void);
	static bool IsStatusbar(void);
	static void status_parseControlStyles( const TString & styles, LONG * Styles, LONG * ExStyles, BOOL * bNoTheme );
	static void status_getRect(LPRECT rc);
	static void status_setBkColor(const COLORREF clr);
	static void status_setParts( const int nParts, const LPINT aWidths );
	static LRESULT status_getParts( const int nParts, LPINT aWidths );
	static void status_setText( const int iPart, const int Style, const LPSTR lpstr );
	static LRESULT status_getText( const int iPart, LPSTR lpstr );
	static UINT status_getTextLength( const int iPart );
	static void status_setTipText( const int iPart, const LPSTR lpstr );
	static void status_getTipText( const int iPart, const int nSize, LPSTR lpstr );
	static void status_getRect( const int iPart, LPRECT lprc );
	static void status_setIcon( const int iPart, const HICON hIcon );
	static HICON status_getIcon( const int iPart );
	static HIMAGELIST status_getImageList(void);
	static void status_setImageList( HIMAGELIST himl );
	static HIMAGELIST status_createImageList(void);
	static UINT status_parseItemFlags( TString & flags );
	static void status_cleanPartIcons( );
	static LRESULT status_getBorders( LPINT aWidths );
	static void status_updateParts(void);
	//
	static int getPos(int x, int y, int w, int h);
	//
	static void getTreebarItemType(TString &tsType, LPARAM lParam);

protected:
	static LRESULT CALLBACK mIRCRefWinProc(HWND mHwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK mIRCDockWinProc(HWND mHwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	VectorOfDocks m_VectorDocks; //!< list of windows docked here.
	//static VectorOfDocks g_VectorAllDocks; //!< list of all docked windows.
	WNDPROC m_OldRefWndProc; //!< The Windows Old WndProc.
	WNDPROC m_OldDockWndProc; //!< The Windows Old WndProc.
	HWND m_RefHwnd; //!< The HWND that windows are docked around, usually the main child window. This window is subclassed.
	HWND m_hParent; //!< The HWND that docked windows are docked too. This window is subclassed.
	int m_iType; //!< The dock type.
public:
	static HWND g_StatusBar; //!< The Statusbar for the main mIRC window.
	static HIMAGELIST g_hImageList; //!< The Statusbar's image list.
	static INT g_iDynamicParts[256];
	static INT g_iFixedParts[256];
	static bool g_bTakeOverTreebar; //!< take over the drawing of the treebar from mIRC.
	// 0 = selected, 1 = selected bkg, 2 = message, 3 = message bkg
	// 4 = event, 5 = event bkg, 6 = highlight, 7 = highlight bkg
	static COLORREF g_clrTreebarColours[8];
};

