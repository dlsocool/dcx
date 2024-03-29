#pragma once
//#include "defines.h"
#include "mIRCLinker.h"
#include "DcxUXModule.h"
#include "DcxXPPlusModule.h"
#include "DcxGDIModule.h"
#include "DcxDWMModule.h"
#include "Classes/xpopup/XPopupMenuManager.h"
#include "Classes/xpopup/xmenubar.h"
#include "Classes/DcxDialog.h"
#include <sys/stat.h> 

// is it just me or is this class just a namespace?

class Dcx
{
	static TString m_sLastError;
	static BYTE m_iGhostDrag;
	static IClassFactory *m_pClassFactory;
	static bool m_bDX9Installed;

	static void setupOSCompatibility(void);
	static void freeOSCompatibility(void);
	Dcx(void);
	~Dcx(void);

public:



	static mIRCLinker mIRC;
	static DcxDialogCollection Dialogs;
	static DcxGDIModule GDIModule;
	static DcxXPPlusModule XPPlusModule;
	static DcxUXModule UXModule;
	static DcxDWMModule VistaModule;

	/* additions */
	static XPopupMenuManager XPopups;
	static XMenuBar XMenubar;
	
	
	static IClassFactory* getClassFactory();
	static const char * getLastError();
	static BYTE getGhostDrag();
	static bool setGhostDrag(const BYTE newAlpha);
	static bool isDX9Installed();
	static bool isUnloadSave();
	static bool isFile(const char* file);

	static void load(LOADINFO * lInfo);
	static void unload(void);
	static bool initDirectX();
	static bool initDirectX(char *dxResult, int dxSize);
#if DCX_DEBUG_OUTPUT
	static void debug(const char *cmd, const char *msg);
#endif
	static void error(const char *cmd, const char *msg);
	static void errorex(const char *cmd, const char *szFormat, ...);
	static int mark(char* data, const TString & tsDName, const TString & tsCallbackName);
	static LRESULT CALLBACK mIRCSubClassWinProc(HWND mHwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
};
