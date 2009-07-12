#pragma once

class mIRCLinker
{
	HANDLE		m_hFileMap; //!< Handle to the mIRC DLL File Map
	LPSTR		m_pData;    //!< Pointer to a character buffer of size 900 to send mIRC custom commands
	HWND		m_mIRCHWND; //!< mIRC Window Handle
	DWORD		m_dwVersion;
	int			m_iMapCnt;  //!< MapFile counter.
	bool		m_bDebug;    //!< is mIRC is using /debug upon DCX LoadDLL().
	HWND		m_hSwitchbar; //!< The Switchbars HWND
	HWND		m_hToolbar; //!< The Toolbars HWND
	HWND		m_hMDI; //!< The MDIClients HWND
	HWND		m_hTreebar; //!< The Treebars HWND
	HWND		m_hTreeview; //!< The TreeView control child of the Treebar.
	HFONT		m_hTreeFont; //!< The Treebars original font.
	HIMAGELIST  m_hTreeImages; //!< The Treebars original image list.
	TString		m_sLastError;
	WNDPROC		m_wpmIRCDefaultWndProc;
	
	void initMapFile();

public:
	mIRCLinker(void);
	~mIRCLinker(void);
	HWND getSwitchbar();
	HWND getToolbar();
	HWND getTreebar();
	HWND getTreeview();
	HIMAGELIST getTreeImages();
	HFONT getTreeFont();
	HWND getMDIClient();
	HWND getHWND();
	DWORD getVersion();
	WORD getMainVersion();
	WORD getSubVersion();
	TString & getLastError();
	bool setTreeFont(HFONT newFont);
	bool isOrNewerVersion(WORD main, WORD sub);
	bool isVersion(WORD main, WORD sub);
	bool isAero();
	bool isVista();
	bool isDebug();
	bool isDXInstalled9();
	bool isAlias(const char * aliasName);

	void load(LOADINFO * lInfo);
	void unload(void);

	void hookWindowProc(WNDPROC newProc);
	void resetWindowProc(void);
	LRESULT callDefaultWindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

	bool eval(char *res, const int maxlen, const char *data);
	bool evalex(char *res, const int maxlen, const char *szFormat, ...);
	bool exec(const char *data);
	bool execex(const char *szFormat, ...);
	void signal(char *msg);
	void signalex(bool allow, const char *szFormat, ...);
	void echo(const char *data);
#if DCX_DEBUG_OUTPUT
	void debug(const char *cmd, const char *msg);
#endif
};