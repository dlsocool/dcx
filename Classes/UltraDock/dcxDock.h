#pragma once

/*
	* SubClass mIRC windows for docking with new layout engine.
*/

#include "../../defines.h"

#define DOCK_TYPE_MDI		0x01
#define DOCK_TYPE_TREE	0x02

class DcxDock
{
public:
	DcxDock(HWND refHwnd, HWND dockHwnd, int dockType);
	virtual ~DcxDock(void);

	virtual bool DockWindow(HWND hwnd, TString &flag);
	virtual void UnDockWindow(HWND hwnd);
	void UpdateLayout(void) const { SendMessage(this->m_hParent,WM_SIZE,NULL,NULL); };
	bool FindDock(const HWND hwnd);
	bool isDocked(const HWND hwnd);
	LPDCXULTRADOCK GetDock(const HWND hwnd);
	virtual void AdjustRect(WINDOWPOS *wp);
	// Statusbar Functions.
	static bool InitStatusbar(void);
	static void UnInitStatusbar(void);
	static bool IsStatusbar(void);
	static void status_getRect(LPRECT rc);
	static void status_setBkColor(const COLORREF clr);
	static void status_setParts( const int nParts, const LPINT aWidths );
	static LRESULT status_getParts( const int nParts, LPINT aWidths );
	static void status_setText( const int iPart, const int Style, const LPSTR lpstr );
	static LRESULT status_getText( const int iPart, LPSTR lpstr );
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
	static HWND g_StatusBar; //!< The Statusbar for the main mIRC window.
	static HIMAGELIST g_hImageList; //!< The Statusbar's image list.
};

