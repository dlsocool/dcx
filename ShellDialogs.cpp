#include "defines.h"
#include "Dcx.h"



/*
 * Structure to store settings for use in BrowseFolderCallback.
 */
typedef struct {
	LPSTR initialFolder;
	UINT flags;
} XBROWSEDIALOGSETTINGS, *LPXBROWSEDIALOGSETTINGS;


/*!
* \brief DCX DLL ColorDialog Function
*
* Argument \b data contains -> (DEFAULT) [STYLES]
*/
// ColorDialog (DEFAULT) [STYLES]
mIRC(ColorDialog) {
	TString d(data);
	d.trim();

	BOOL retDefault = FALSE;
	CHOOSECOLOR	cc;
	static COLORREF clr[16] = {CLR_INVALID};
	COLORREF		sel = (COLORREF) d.gettok(1).to_num();
	DWORD			styles = CC_RGBINIT;

	ZeroMemory(&cc, sizeof(CHOOSECOLOR));

	// initial settings
	cc.lStructSize = sizeof(CHOOSECOLOR);
	cc.hwndOwner = mWnd;

	if (d.numtok() > 1) {
		for (unsigned int i = 1; i <= d.numtok(); i++) {
			if (d.gettok(i) == "anycolor")
				styles |= CC_ANYCOLOR;
			else if (d.gettok(i) == "fullopen")
				styles |= CC_FULLOPEN;
			else if (d.gettok(i) == "nofullopen")
				styles |= CC_PREVENTFULLOPEN;
			else if (d.gettok(i) == "solidonly")
				styles |= CC_SOLIDCOLOR;
			else if (d.gettok(i) == "owner")
				cc.hwndOwner = FindOwner(d, mWnd);
			else if (d.gettok(i) == "returndefault")
				retDefault = TRUE;
		}
	}

	cc.rgbResult = (COLORREF) sel;
	cc.Flags = styles;
	cc.lpCustColors = clr;

	// User clicked OK
	if (ChooseColor(&cc)) {
		wnsprintf(data, MIRC_BUFFER_SIZE_CCH, "%d", cc.rgbResult);
		return 3; //ret(data);
	}
	// User clicked cancel, return default color
	else if (retDefault) {
		wnsprintf(data, MIRC_BUFFER_SIZE_CCH, "%d", sel);
		return 3; //ret(data);
	}
	// User clicked cancel, dont bother with default color
	else
		ret("-1");
}


/*!
* \brief DCX DLL OpenDialog|SaveDialog Function
*
* Argument \b data contains -> (styles) [TAB] (file) [TAB] (filter)
*
* http://www.winprog.org/tutorial/app_two.html
* http://msdn.microsoft.com/library/default.asp?url=/library/en-us/winui/winui/windowsuserinterface/userinput/commondialogboxlibrary/commondialogboxreference/commondialogboxstructures/openfilename.asp
*/
// OpenDialog (styles) [TAB] (file) [TAB] (filter)
mIRC(OpenDialog) {
	TString d(data);
	d.trim();

	data[0] = 0;

	// count number of tab tokens
	if (d.numtok(TSTAB) != 3) {
		Dcx::error("$!dcx(OpenDialog)","Invalid parameters");
		return 0;
	}

	ret(FileDialog(d, "OPEN", mWnd).to_chr());
}

// SaveDialog (styles) [TAB] (file) [TAB] (filter)
mIRC(SaveDialog) {
	TString d(data);
	d.trim();

	data[0] = 0;

	// count number of tab tokens
	if (d.numtok(TSTAB) != 3) {
		Dcx::error("$!dcx(SaveDialog)","Invalid parameters");
		return 0;
	}

	ret(FileDialog(d, "SAVE", mWnd).to_chr());
}



/*!
* \brief Shows CommonDialog for Open/Save
*
* Shows and returns the file selected
*
* \return > TString "" if cancelled
*         > TString Path+Filename
*/
TString FileDialog(const TString & data, const TString &method, const HWND pWnd) {
	DWORD style = OFN_EXPLORER;
	OPENFILENAME ofn;
	char szFilename[MIRC_BUFFER_SIZE_CCH];

	// seperate the tokenz
	const TString styles(data.gettok(1, TSTAB).trim());
	const TString file(data.gettok(2, TSTAB).trim());
	TString filter(data.gettok(3, TSTAB).trim());

	// Get Current dir for resetting later.
	const UINT tsBufSize = GetCurrentDirectory(0, NULL);
	TString tsCurrentDir((UINT)tsBufSize);
	GetCurrentDirectory(tsBufSize,tsCurrentDir.to_chr());

	// format the filter into the format WinAPI wants, with double NULL TERMINATOR at end
	if (filter == "")
		filter = "All Files (*.*)|*.*";

	filter += '\0';
	filter.replace('|', '\0');

	// set up the OFN struct
	ZeroMemory(&ofn, sizeof(ofn));
	lstrcpyn(szFilename, file.to_chr(), MIRC_BUFFER_SIZE_CCH);

	ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
	ofn.hwndOwner = pWnd;
	ofn.lpstrFilter = filter.to_chr();
	ofn.lpstrFile = szFilename;
	ofn.nMaxFile = MIRC_BUFFER_SIZE_CCH;
	ofn.lpstrDefExt = "";

	for (unsigned int i = 1; i <= styles.numtok( ); i++) {
		if (styles.gettok( i ) == "multisel")
			style |= OFN_ALLOWMULTISELECT;
		else if (styles.gettok( i ) == "createprompt")
			style |= OFN_CREATEPROMPT;
		// FIXME: explorer style resizable on default, cant get rid of that shit
		else if (styles.gettok( i ) == "enablesizing")
			style |= OFN_ENABLESIZING;
		else if (styles.gettok( i ) == "filemustexist")
			style |= OFN_FILEMUSTEXIST; // (open)
		else if (styles.gettok( i ) == "showhidden")
			style |= OFN_FORCESHOWHIDDEN; // 2k/xp
		else if (styles.gettok( i ) == "noreadonly")
			style |= OFN_HIDEREADONLY;
		else if (styles.gettok( i ) == "nochangedir")
			style |= OFN_NOCHANGEDIR; // (save)
		else if (styles.gettok( i ) == "getshortcuts")
			style |= OFN_NODEREFERENCELINKS;
		else if (styles.gettok( i ) == "nonetwork")
			style |= OFN_NONETWORKBUTTON;
		else if (styles.gettok( i ) == "novalidate")
			style |= OFN_NOVALIDATE;
		else if (styles.gettok( i ) == "norecent")
			style |= OFN_DONTADDTORECENT; // 2k/xp
		else if (styles.gettok( i ) == "overwriteprompt")
			style |= OFN_OVERWRITEPROMPT; // save
		else if (styles.gettok( i ) == "pathmustexist")
			style |= OFN_PATHMUSTEXIST;
		else if (styles.gettok( i ) == "owner")
			ofn.hwndOwner = FindOwner(styles, pWnd);
	}

	ofn.Flags = style;

	TString tsResult;

	if (method == "OPEN" && GetOpenFileName(&ofn)) {
		// if there are multiple files selected
		if (style & OFN_ALLOWMULTISELECT) {
			char *p = szFilename; 

			// process the file name at p since its null terminated
			while (*p != '\0') { 
				if (tsResult != "")
					tsResult += "|";

				tsResult += p;
				p += lstrlen(p)+1;
			} 
		}
		// copy the string directly
		else
			tsResult = szFilename;
	}
	else if (method == "SAVE" && GetSaveFileName(&ofn))
		tsResult = szFilename;

	// Reset current dir.
	if (tsCurrentDir.len() > 0)
		SetCurrentDirectory(tsCurrentDir.to_chr());

	return tsResult;
}



/*!
* \brief Shows CommonDialog for Selecting Folders/Directories
*
* Shows and returns the folder selected
*
* \return > TString "" if cancelled
*         > TString [SELECTED_ITEM]
*/
mIRC(BrowseDialog) {
	// seperate the tokens (by tabs)
	TString input(data);
	input.trim();

	TString displayPath((UINT) MAX_PATH);
	BROWSEINFO bi;
	XBROWSEDIALOGSETTINGS extra;

	// set up the BI structure
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	ZeroMemory(&extra, sizeof(XBROWSEDIALOGSETTINGS));
	bi.hwndOwner = mWnd;                                             // Default owner: mIRC main window
	bi.lpfn = BrowseFolderCallback;
	bi.pszDisplayName = displayPath.to_chr();
	bi.ulFlags = BIF_VALIDATE;
	bi.lParam = (LPARAM) &extra;

	// Parse styles
	TString param(input.gettok(1, TSTAB));
	const int count = param.numtok();
	bool bInitialFolder = false;
	bool bDialogText = false;
	LPITEMIDLIST pidlRoot = NULL;

	for (int i = 1; i <= count; i++) {
		/*
		style1 style2 style3 $chr(9) initial folder

		//clear | echo -a Selected: $dcx(BrowseDialog, hello asd $chr(9) C:\Windows $chr(9) mr t says select something fool! ) | /udcx

		http://msdn2.microsoft.com/en-us/library/bb773205.aspx
		*/

		const TString flag(param.gettok(i));

		if (flag == "advanced")
			bi.ulFlags |= BIF_USENEWUI;
		else if (flag == "edit")
			bi.ulFlags |= BIF_EDITBOX;
		else if (flag == "newstyle")
			bi.ulFlags |= BIF_NEWDIALOGSTYLE;

		else if (flag == "nonew")
			bi.ulFlags |= BIF_NONEWFOLDERBUTTON;
		else if (flag == "files")
			bi.ulFlags |= BIF_BROWSEINCLUDEFILES;
		else if (flag == "title")
			bDialogText = true;
		else if (flag == "initfolder")
			bInitialFolder = true;

		else if (flag == "computers") {
			// NOTE: do not use with "advanced"
			bi.ulFlags |= BIF_BROWSEFORCOMPUTER;
			pidlRoot = GetFolderFromCSIDL(CSIDL_NETWORK);
		}
		else if (flag == "printers") {
			// NOTE: do not use with "advanced"
			bi.ulFlags |= BIF_BROWSEFORPRINTER;
			pidlRoot = GetFolderFromCSIDL(CSIDL_PRINTERS);
		}
		else if (flag == "nonetwork")
			bi.ulFlags |= BIF_DONTGOBELOWDOMAIN;
		else if (flag == "shortcut")
			bi.ulFlags |= BIF_NOTRANSLATETARGETS;

		// owner
		else if (flag == "owner")
			bi.hwndOwner = FindOwner(param, mWnd);
	}

	int currentParam = 1;
	TString initPath((UINT) MAX_PATH);

	// Set initial folder
	if (bInitialFolder && (pidlRoot == NULL)) {
		currentParam++;
		initPath = input.gettok(currentParam, TSTAB).trim();

		extra.initialFolder = initPath.to_chr();
	}

	// Set title text.
	if (bDialogText) {
		currentParam++;
		param = input.gettok(currentParam, TSTAB).trim();

		bi.lpszTitle = param.to_chr();
	}

	// Set root folder
	if (pidlRoot != NULL)
		bi.pidlRoot = pidlRoot;

	extra.flags = bi.ulFlags;
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

	// User cancelled
	if (pidl == NULL) {
		CoTaskMemFree(pidlRoot);
		ret("");
	}

	// If we were searching for a computer ...
	if (bi.ulFlags & BIF_BROWSEFORCOMPUTER)
		wnsprintf(data, MIRC_BUFFER_SIZE_CCH, "//%s", displayPath.to_chr());
	else {
		SHGetPathFromIDList(pidl, initPath.to_chr());
		lstrcpyn(data, initPath.to_chr(), MIRC_BUFFER_SIZE_CCH);
	}

	CoTaskMemFree(pidl);
	CoTaskMemFree(pidlRoot);

	return 3;
}

/*
// Some useful stuff for resolving CSIDL information.
// http://www.codeguru.com/cpp/w-p/files/browserfunctionsdialogs/article.php/c4443/

// List of CSIDL ids
// http://msdn2.microsoft.com/en-us/library/bb762494(VS.85).aspx

// TODO: make this accept CSIDL stuff as initial folder.
*/
LPITEMIDLIST GetFolderFromCSIDL(const int nCsidl) {
	LPITEMIDLIST pidlRoot;

	if (S_OK == SHGetFolderLocation(NULL, nCsidl, NULL, 0, &pidlRoot))
		return pidlRoot;

	return NULL;                // Caller assumes responsibility
}


int CALLBACK BrowseFolderCallback(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData) {
	LPXBROWSEDIALOGSETTINGS extra = (LPXBROWSEDIALOGSETTINGS) lpData;

	switch (uMsg) {
		// User typed invalid name (non-existant folder) into editbox.
		// This must return non-zero, otherwise it will close the dialog.
		case BFFM_VALIDATEFAILED:
			return TRUE;

		case BFFM_INITIALIZED:
			// Sets initial folder if it is specified.
			if (lpData != NULL)
				SendMessage(hwnd, BFFM_SETSELECTION, TRUE, (LPARAM) extra->initialFolder);
			else
				// Disable OK button.
				SendMessage(hwnd, BFFM_ENABLEOK, TRUE, FALSE);

			break;

		case BFFM_SELCHANGED:
		{
			// Dont check for COMPUTER or PRINTER browsing
			if ((extra->flags & BIF_BROWSEFORCOMPUTER) ||
				(extra->flags & BIF_BROWSEFORPRINTER))
				break;

			TString path((UINT) MAX_PATH);

			if (SHGetPathFromIDList((LPITEMIDLIST) lParam, path.to_chr())) {
				SendMessage(hwnd, BFFM_ENABLEOK, TRUE, TRUE);
				SendMessage(hwnd, BFFM_SETSTATUSTEXT, 0, (LPARAM) path.to_chr());
			}
			else {
				SendMessage(hwnd, BFFM_ENABLEOK, TRUE, FALSE);
				SendMessage(hwnd, BFFM_SETSTATUSTEXT, 0, NULL);
			}

			break;
		}

		default:
			break;
	}

	// Return 0 by default.
	return 0L;
}



/*!
* \brief Shows CommonDialog for Selecting Fonts
*
* Shows and returns the file selected
*
* \return > TString "" if cancelled
*         > TString +flags charset size fontname
*/
mIRC(FontDialog) {
	DWORD style = CF_INITTOLOGFONTSTRUCT | CF_FORCEFONTEXIST | CF_LIMITSIZE;
	CHOOSEFONT cf;
	LOGFONT lf;

	// seperate the tokens (by tabs)
	TString input(data);
	input.trim();

	// set up the LF structure
	ZeroMemory(&lf, sizeof(LOGFONT));
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);

	// set up the CF struct
	ZeroMemory(&cf, sizeof(CHOOSEFONT));
	cf.lStructSize = sizeof(CHOOSEFONT);
	cf.hwndOwner = mWnd;
	cf.lpLogFont = &lf;
	cf.nSizeMin = 8;
	cf.nSizeMax = 72;

	for (unsigned int i = 1; i <= input.numtok(TSTAB); i++) {
		const TString option(input.gettok(i, TSTAB).trim());
		const int numtok = option.numtok( );

		/*
		default +flags(ibsua) charset size fontname
		flags +etc
		color rgb
		minmaxsize min max (Ranges from 8 to 72, if "D" is used 5 to 30)
		owner hwnd

		+flag to use mirc colors
		palette col...16...col

		//clear | echo -a $dcx(FontDialog, hello asd $chr(9) flags +abcdef $chr(9) color 255 $chr(9) owner dcxtest_1146984371 $chr(9) default + default 10 Verdana) | /udcx

		http://msdn.microsoft.com/library/default.asp?url=/library/en-us/winui/winui/windowsuserinterface/userinput/commondialogboxlibrary/commondialogboxreference/commondialogboxstructures/choosefont.asp
		*/

		// flags +
		if (option.gettok( 1 ) == "flags" && numtok > 1) {
			const XSwitchFlags xflag(option.gettok( 2 ));
			if (xflag['a'])
				style |= CF_NOFACESEL;
			if (xflag['b'])
				style |= CF_SCRIPTSONLY;
			if (xflag['c'])
				style |= CF_SCALABLEONLY;// (Scalable fonts include vector fonts, scalable printer fonts, TrueType fonts, and fonts scaled by other technologies.)
			if (xflag['e'])
				style |= CF_EFFECTS;
			if (xflag['f'])
				style |= CF_FORCEFONTEXIST;
			if (xflag['h'])
				style |= CF_NOSCRIPTSEL;
			if (xflag['i'])
				style |= CF_NOSIMULATIONS;
			if (xflag['m'])
				style |= CF_SELECTSCRIPT;
			if (xflag['n'])
				style |= CF_PRINTERFONTS;
			if (xflag['p'])
				style |= CF_FIXEDPITCHONLY;
			if (xflag['r'])
				style |= CF_NOVERTFONTS;
			if (xflag['s'])
				style |= CF_SCREENFONTS;
			if (xflag['t'])
				style |= CF_TTONLY;
			if (xflag['v'])
				style |= CF_NOVECTORFONTS;
			if (xflag['w'])
				style |= CF_WYSIWYG;
			if (xflag['y'])
				style |= CF_NOSTYLESEL;
			if (xflag['z'])
				style |= CF_NOSIZESEL;

		}
		// defaults +flags(ibsua) charset size fontname
		else if (option.gettok( 1 ) == "default" && numtok > 4)
			ParseCommandToLogfont(option.gettok(2, -1), &lf);
		// color rgb
		else if (option.gettok( 1 ) == "color" && numtok > 1)
			cf.rgbColors = (COLORREF) option.gettok( 2 ).to_num();
		// minmaxsize min max
		else if (option.gettok( 1 ) == "minmaxsize" && numtok > 2) {
			cf.nSizeMin = option.gettok( 2 ).to_int();
			cf.nSizeMax = option.gettok( 3 ).to_int();
		}
		// owner
		else if (option.gettok( 1 ) == "owner" && numtok > 1)
			cf.hwndOwner = FindOwner(option, mWnd);
	}

	// check that at least some fonts are showing
	if (!(style & CF_PRINTERFONTS) && !(style & CF_SCREENFONTS))
		style |= CF_SCREENFONTS;

	cf.Flags = style;
	cf.iPointSize = lf.lfHeight * 10;

	// show the dialog
	if (ChooseFont(&cf)) {
		const TString fntflags(ParseLogfontToCommand(&lf));

		// color flags font info
		wnsprintf(data, MIRC_BUFFER_SIZE_CCH, "%d %s", cf.rgbColors, fntflags.to_chr());
		return 3;
	}
	else
		ret("");
}



/*
 * /dcx MsgBox [STYLES] [TAB] [TITLE] [TAB] [MSG]
 * http://msdn.microsoft.com/library/default.asp?url=/library/en-us/winui/winui/windowsuserinterface/windowing/dialogboxes/dialogboxreference/dialogboxfunctions/messagebox.asp
 */
mIRC(MsgBox) {
	TString d(data);
	d.trim();

	if (d.numtok(TSTAB) < 3)
		ret("D_ERROR MessageBox: invalid parameters");

	DWORD   style     = MB_DEFBUTTON1;
	const TString strStyles(d.gettok(1, TSTAB).trim());
	const TString strTitle(d.gettok(2, TSTAB).trim());
	const TString strMsg(d.gettok(3, -1, TSTAB).trim());
	const int n = strStyles.numtok( );
	HWND owner = aWnd;

	for (int i = 1; i <= n; i++) {
//		MB_ABORTRETRYIGNORE
//		MB_CANCELTRYCONTINUE && Dcx::XPPlusModule.isUseable()

		if (strStyles.gettok( i ) == "ok")
			style |= MB_OK;
		else if (strStyles.gettok( i ) == "okcancel")
			style |= MB_OKCANCEL;
		else if (strStyles.gettok( i ) == "retrycancel")
			style |= MB_RETRYCANCEL;
		else if (strStyles.gettok( i ) == "yesno")
			style |= MB_YESNO;
		else if (strStyles.gettok( i ) == "yesnocancel")
			style |= MB_YESNOCANCEL;
		else if (strStyles.gettok( i ) == "exclamation")
			style |= MB_ICONEXCLAMATION;
		else if (strStyles.gettok( i ) == "warning")
			style |= MB_ICONWARNING;
		else if (strStyles.gettok( i ) == "information")
			style |= MB_ICONINFORMATION;
		else if (strStyles.gettok( i ) == "asterisk")
			style |= MB_ICONASTERISK;
		else if (strStyles.gettok( i ) == "question")
			style |= MB_ICONQUESTION;
		else if (strStyles.gettok( i ) == "stop")
			style |= MB_ICONSTOP;
		else if (strStyles.gettok( i ) == "error")
			style |= MB_ICONERROR;
		else if (strStyles.gettok( i ) == "hand")
			style |= MB_ICONHAND;
		//else if (strStyles.gettok( i ) == "help")
		//	style |= MB_HELP;
		else if (strStyles.gettok( i ) == "defbutton2")
			style |= MB_DEFBUTTON2;
		else if (strStyles.gettok( i ) == "defbutton3")
			style |= MB_DEFBUTTON3;
		else if (strStyles.gettok( i ) == "defbutton4")
			style |= MB_DEFBUTTON4;
		else if (strStyles.gettok( i ) == "modal")
			style |= MB_APPLMODAL;
		else if (strStyles.gettok( i ) == "sysmodal")
			style |= MB_SYSTEMMODAL;
		else if (strStyles.gettok( i ) == "taskmodal")
			style |= MB_TASKMODAL;
		else if (strStyles.gettok( i ) == "right")
			style |= MB_RIGHT;
		else if (strStyles.gettok( i ) == "rtl")
			style |= MB_RTLREADING;
		else if (strStyles.gettok( i ) == "foreground")
			style |= MB_SETFOREGROUND;
		else if (strStyles.gettok( i ) == "topmost")
			style |= MB_TOPMOST;
		else if (strStyles.gettok( i ) == "owner")
			owner = FindOwner(strStyles, mWnd);
	}

	// if task modal, send in null to block app
	if (style & MB_TASKMODAL)
		owner = NULL;

	switch (MessageBox(owner, strMsg.to_chr(), strTitle.to_chr(), style)) {
		case IDABORT:
			ret("abort");
			break;
		case IDCANCEL:
			ret("cancel");
			break;
		case IDCONTINUE:
			ret("continue");
			break;
		case IDIGNORE:
			ret("ignore");
			break;
		case IDNO:
			ret("no");
			break;
		case IDOK:
			ret("ok");
			break;
		case IDRETRY:
			ret("retry");
			break;
		case IDTRYAGAIN:
			ret("tryagain");
			break;
		case IDYES:
			ret("yes");
			break;
		default:
			ret("");
			break;
	}
}



/*
	$dcx(PickIcon,index filename)
*/
mIRC(PickIcon) {
	TString d(data);
	d.trim();

	if (d.numtok( ) < 2)
		ret("D_ERROR PickIcon: invalid parameters");

	int index = d.gettok( 1 ).to_int();
	TString filename(d.gettok( 2, -1 ));

	if (!IsFile(filename))
		ret("D_ERROR PickIcon: Invalid Filename");

#if !DCX_FOR_XP_ONLY
	if (PickIconDlgUx == NULL)
		ret("D_ERROR PickIcon: Function Not Available");
#endif

	WCHAR iconPath[MAX_PATH+1];
#if DCX_FOR_XP_ONLY
	GetFullPathNameW(filename.to_wchr(), MAX_PATH, iconPath, NULL);
#else
	if (GetFullPathNameWUx != NULL)
		GetFullPathNameWUx(filename.to_wchr(), MAX_PATH, iconPath, NULL);
	else
		lstrcpynW(iconPath, filename.to_wchr(), MAX_PATH);
#endif
	if (dcxPickIconDlg(aWnd,iconPath,MAX_PATH,&index))
		wnsprintf(data, MIRC_BUFFER_SIZE_CCH, "D_OK %d %S", index, iconPath);
	else
		wnsprintf(data, MIRC_BUFFER_SIZE_CCH, "D_ERROR %d %S", index, iconPath);
	return 3;
}

/*
* Icon Picker for WinXP SP2 & Win 2k3 (Others may or may not support it)
*/
int dcxPickIconDlg(HWND hwnd, LPWSTR pszIconPath, UINT cchIconPath, int *piIconIndex)
{
#if DCX_FOR_XP_ONLY
	return PickIconDlg(hwnd, pszIconPath, cchIconPath, piIconIndex);
#else
	if (!PickIconDlgUx)
		return 0;
	return PickIconDlgUx(hwnd, pszIconPath, cchIconPath, piIconIndex);
#endif
}
