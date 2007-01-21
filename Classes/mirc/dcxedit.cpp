/*!
* \file dcxedit.cpp
* \brief blah
*
* blah
*
* \author David Legault ( clickhere at scriptsdb dot org )
* \version 1.0
*
* \b Revisions
*
* � ScriptsDB.org - 2006
*/

#include "dcxedit.h"
#include "../dcxdialog.h"

/*!
* \brief Constructor
*
* \param ID Control ID
* \param p_Dialog Parent DcxDialog Object
* \param mParentHwnd Parent Window Handle
* \param rc Window Rectangle
* \param styles Window Style Tokenized List
*/

DcxEdit::DcxEdit(const UINT ID, DcxDialog *p_Dialog, const HWND mParentHwnd, const RECT *rc, TString &styles)
: DcxControl(ID, p_Dialog)
{
	LONG Styles = 0, ExStyles = 0;
	BOOL bNoTheme = FALSE;
	this->parseControlStyles(styles, &Styles, &ExStyles, &bNoTheme);

	this->m_Hwnd = CreateWindowEx(
		ExStyles | WS_EX_CLIENTEDGE, 
		"EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | Styles,
		rc->left, rc->top, rc->right - rc->left, rc->bottom - rc->top,
		mParentHwnd,
		(HMENU) ID,
		GetModuleHandle(NULL), 
		NULL);

	if (bNoTheme)
		dcxSetWindowTheme(this->m_Hwnd , L" ", L" ");

	Edit_LimitText(this->m_Hwnd, 0);
	this->m_tsText = "";

	if (p_Dialog->getToolTip() != NULL) {
		if (styles.istok("tooltips"," ")) {
			this->m_ToolTipHWND = p_Dialog->getToolTip();
			AddToolTipToolInfo(this->m_ToolTipHWND, this->m_Hwnd);
		}
	}

	this->setControlFont((HFONT) GetStockObject(DEFAULT_GUI_FONT), FALSE);
	this->registreDefaultWindowProc();
	SetProp(this->m_Hwnd, "dcx_cthis", (HANDLE) this);
	DragAcceptFiles(this->m_Hwnd, TRUE);
}

/*!
* \brief blah
*
* blah
*/
DcxEdit::~DcxEdit() {
	this->unregistreDefaultWindowProc();
}

/*!
* \brief blah
*
* blah
*/
void DcxEdit::parseControlStyles(TString &styles, LONG *Styles, LONG *ExStyles, BOOL *bNoTheme) {
	unsigned int i = 1, numtok = styles.numtok(" ");

	while (i <= numtok) {
		if (styles.gettok(i , " ") == "multi") 
			*Styles |= ES_MULTILINE;
		else if (styles.gettok(i , " ") == "center")
			*Styles |= ES_CENTER;
		else if (styles.gettok(i , " ") == "right")
			*Styles |= ES_RIGHT;
		else if (styles.gettok(i , " ") == "autohs")
			*Styles |= ES_AUTOHSCROLL;
		else if (styles.gettok(i , " ") == "autovs")
			*Styles |= ES_AUTOVSCROLL;
		else if (styles.gettok(i , " ") == "vsbar")
			*Styles |= WS_VSCROLL;
		else if (styles.gettok(i , " ") == "hsbar")
			*Styles |= WS_HSCROLL;
		else if (styles.gettok(i , " ") == "lowercase")
			*Styles |= ES_LOWERCASE;
		else if (styles.gettok(i , " ") == "number")
			*Styles |= ES_NUMBER;
		else if (styles.gettok(i , " ") == "password")
			*Styles |= ES_PASSWORD;
		else if (styles.gettok(i , " ") == "uppercase")
			*Styles |= ES_UPPERCASE;
		else if (styles.gettok(i , " ") == "return")
			*Styles |= ES_WANTRETURN;
		else if (styles.gettok(i , " ") == "readonly")
			*Styles |= ES_READONLY;
		else if ( styles.gettok( i , " " ) == "alpha" )
			this->m_bAlphaBlend = true;

		i++;
	}

	this->parseGeneralControlStyles(styles, Styles, ExStyles, bNoTheme);
}

/*!
* \brief $xdid Parsing Function
*
* \param input [NAME] [ID] [PROP] (OPTIONS)
* \param szReturnValue mIRC Data Container
*
* \return > void
*/
void DcxEdit::parseInfoRequest(TString &input, char *szReturnValue) {
	int numtok = input.numtok(" ");

	// [NAME] [ID] [PROP] [N]
	if (input.gettok(3, " ") == "text") {
		if (this->isStyle(ES_MULTILINE)) {
			if (numtok > 3) {
				int nLine = input.gettok(4, " ").to_int();

				if (nLine > 0 && nLine <= this->m_tsText.numtok("\r\n")) {
					lstrcpyn(szReturnValue, this->m_tsText.gettok(nLine, "\r\n").to_chr(), 900);
					return;
				}
			}
		}
		else {
			lstrcpyn(szReturnValue, this->m_tsText.to_chr(), 900);
			return;
		}
	}
	// [NAME] [ID] [PROP]
	else if (input.gettok(3, " ") == "num") {
		if (this->isStyle(ES_MULTILINE))
			wsprintf(szReturnValue, "%d", this->m_tsText.numtok("\r\n"));
		else
			lstrcpy(szReturnValue,"1");	// single line control so always 1 line.
		return;
	}
	// [NAME] [ID] [PROP]
	else if (input.gettok(3, " ") == "ispass") {
		if (this->isStyle(ES_PASSWORD))
			lstrcpy(szReturnValue, "$true");
		else
			lstrcpy(szReturnValue, "$false");

		return;
	}
	// [NAME] [ID] [PROP]
	else if (input.gettok(3, " ") == "caretpos") {
		DWORD dwAbsoluteStartSelPos = 0;

		// caret startsel position
		SendMessage(this->m_Hwnd, EM_GETSEL, (WPARAM) &dwAbsoluteStartSelPos, NULL);

		if (this->isStyle(ES_MULTILINE)) {
			int iLinePos = 0;
			int iAbsoluteCharPos = 0;

			// current line
			iLinePos = SendMessage(this->m_Hwnd, EM_LINEFROMCHAR, -1, NULL);
			// line offset
			iAbsoluteCharPos = (int) SendMessage(this->m_Hwnd, EM_LINEINDEX, -1, NULL);

			wsprintf(szReturnValue, "%d %d", iLinePos +1, dwAbsoluteStartSelPos - iAbsoluteCharPos);
		}
		else {
			// return selstart
			wsprintf(szReturnValue, "%d %d", 1, dwAbsoluteStartSelPos);
		}

		return;
	}
	else if (input.gettok(3, " ") == "selstart") {
		DWORD dwSelStart = 0; // selection range starting position

		SendMessage(this->m_Hwnd, EM_GETSEL, (WPARAM) &dwSelStart, NULL);
		wsprintf(szReturnValue, "%d", dwSelStart);
		return;
	}
	else if (input.gettok(3, " ") == "selend") {
		DWORD dwSelEnd = 0;   // selection range ending position

		SendMessage(this->m_Hwnd, EM_GETSEL, NULL, (LPARAM) &dwSelEnd);
		wsprintf(szReturnValue, "%d", dwSelEnd);
		return;
	}
	else if (input.gettok(3, " ") == "sel") {
		DWORD dwSelStart = 0; // selection range starting position
		DWORD dwSelEnd = 0;   // selection range ending position

		SendMessage(this->m_Hwnd, EM_GETSEL, (WPARAM) &dwSelStart, (LPARAM) &dwSelEnd);
		wsprintf(szReturnValue, "%d %d", dwSelStart, dwSelEnd);
		return;
	}
	else if (input.gettok(3, " ") == "seltext") {
		DWORD dwSelStart = 0; // selection range starting position
		DWORD dwSelEnd = 0;   // selection range ending position

		SendMessage(this->m_Hwnd, EM_GETSEL, (WPARAM) &dwSelStart, (LPARAM) &dwSelEnd);
		lstrcpyn(szReturnValue, this->m_tsText.mid(dwSelStart, dwSelEnd - dwSelStart).to_chr(), 900);
		return;
	}
	else if (input.gettok(3, " ") == "cue") {
		if (this->m_tsCue.len())
			lstrcpyn(szReturnValue, this->m_tsCue.to_chr(), 900);
		return;
	}
	else if (this->parseGlobalInfoRequest(input, szReturnValue)) {
		return;
	}

	szReturnValue[0] = 0;
}

/*!
* \brief blah
*
* blah
*/
void DcxEdit::parseCommandRequest(TString &input) {
	XSwitchFlags flags;
	ZeroMemory((void*) &flags, sizeof(XSwitchFlags));
	this->parseSwitchFlags(input.gettok(3, " "), &flags);

	int numtok = input.numtok(" ");

	// xdid -r [NAME] [ID] [SWITCH]
	if (flags.switch_flags[17]) {
		this->m_tsText = "";
		SetWindowText(this->m_Hwnd, "");
	}

	// xdid -a [NAME] [ID] [SWITCH] [TEXT]
	if (flags.switch_flags[0] && numtok > 3) {
		this->m_tsText += input.gettok(4, -1, " ");
		SetWindowText(this->m_Hwnd, this->m_tsText.to_chr());
	}
	// xdid -c [NAME] [ID] [SWITCH]
	else if (flags.switch_flags[2] && numtok > 2) {
		CopyToClipboard(this->m_Hwnd, this->m_tsText);
	}
	// xdid -d [NAME] [ID] [SWITCH] [N]
	else if (flags.switch_flags[3] && numtok > 3) {
		if (this->isStyle(ES_MULTILINE)) {
			int nLine = input.gettok(4, " ").to_int();
			this->m_tsText.deltok(nLine, "\r\n");
			SetWindowText(this->m_Hwnd, this->m_tsText.to_chr());
		}
	}
	// xdid -i [NAME] [ID] [SWITCH] [N] [TEXT]
	else if (flags.switch_flags[8] && numtok > 4) {
		if (this->isStyle(ES_MULTILINE)) {
			int nLine = input.gettok(4, " ").to_int();
			this->m_tsText.instok(input.gettok(5, -1, " ").to_chr(), nLine, "\r\n");
		}
		else {
			this->m_tsText = input.gettok(5, -1, " ");
		}
		SetWindowText(this->m_Hwnd, this->m_tsText.to_chr());
	}
	// xdid -j [NAME] [ID] [SWITCH] [0|1]
	else if (flags.switch_flags[9] && numtok > 3) {
		int i = input.gettok(4, " ").to_int();

		if (i) {
			char c = Edit_GetPasswordChar(this->m_Hwnd);
			this->addStyle(ES_PASSWORD);

			if (!c)
				c = '*'; //(isXP() ? '�' : '*');

			Edit_SetPasswordChar(this->m_Hwnd, c);
		}
		else {
			this->removeStyle(ES_PASSWORD);
			Edit_SetPasswordChar(this->m_Hwnd, 0);
		}

		this->redrawWindow();
	}
	// xdid -o [NAME] [ID] [SWITCH] [N] [TEXT]
	else if (flags.switch_flags[14] && numtok > 3) {
		if (this->isStyle(ES_MULTILINE)) {
			int nLine = input.gettok(4, " ").to_int();
			this->m_tsText.puttok(input.gettok(5, -1, " ").to_chr(), nLine, "\r\n");
		}
		else {
			this->m_tsText = input.gettok(4, -1, " ");
		}
		SetWindowText(this->m_Hwnd, this->m_tsText.to_chr());
	}
	// xdid -P [NAME] [ID]
	else if (flags.switch_cap_flags[15] && numtok > 1) {
		SendMessage(this->getHwnd(),WM_PASTE,NULL,NULL);
	}
	// xdid -q [NAME] [ID] [SWITCH] [SIZE]
	else if (flags.switch_flags[16] && numtok > 3) {
		int N = input.gettok(4, " ").to_int();

		if (N > -1) {
			Edit_LimitText(this->m_Hwnd, N);
		}
	}
	// xdid -r [NAME] [ID] [SWITCH]
	else if (flags.switch_flags[17]) {
	}
	// xdid -t [NAME] [ID] [SWITCH] [FILENAME]
	else if (flags.switch_flags[19] && numtok > 3) {
		char *contents = readFile(input.gettok(4, -1, " ").to_chr());

		if (contents != NULL) {
			this->m_tsText = contents;
			SetWindowText(this->m_Hwnd, contents);
			delete [] contents;
		}
	}
	// xdid -u [NAME] [ID] [SWITCH] [FILENAME]
	else if (flags.switch_flags[20] && numtok > 3) {
		FILE *file = fopen(input.gettok(4, -1, " ").to_chr(), "wb");

		if (file != NULL) {
			fwrite(this->m_tsText.to_chr(), sizeof(char), this->m_tsText.len(), file);
			fflush(file);
			fclose(file);
		}
	}
	// xdid -S [NAME] [ID] [SWITCH] [START] [END]
	else if (flags.switch_cap_flags[18] && numtok > 3) {
		int istart = input.gettok(4, " ").to_int();
		int iend;
		
		if (numtok > 4)
			iend = input.gettok(5, " ").to_int();
		else
			iend = istart;

		SendMessage(this->m_Hwnd, EM_SETSEL, istart, iend);
	}
	// xdid -E [NAME] [ID] [SWITCH] [CUE TEXT]
	else if (flags.switch_cap_flags[4] && numtok > 3) {
		TString cue(input.gettok(4, -1, " "));
		//int widelen = MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,cue.to_chr(),-1, NULL, 0);
		//WCHAR *wcue = new WCHAR[widelen+1];
		//MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,cue.to_chr(),-1, wcue, widelen);
		//Edit_SetCueBannerText(this->m_Hwnd,wcue);
		Edit_SetCueBannerText(this->m_Hwnd,cue.to_wchr());
		this->m_tsCue = cue;
		//delete [] wcue;
	}
	else
		this->parseGlobalCommandRequest(input, flags);
}

/*!
 * \brief blah
 *
 * blah
 */
LRESULT DcxEdit::ParentMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bParsed) {
	switch (uMsg) {
		case WM_COMMAND:
		{
			switch ( HIWORD( wParam ) ) {
				case EN_CHANGE:
				{
					int n = GetWindowTextLength(this->m_Hwnd);
					char *text = new char[n +2];

					GetWindowText(this->m_Hwnd, text, n +1);
					this->m_tsText = text;
					if (this->m_pParentDialog->getEventMask() & DCX_EVENT_EDIT)
						this->callAliasEx(NULL, "%s,%d", "edit", this->getUserID());

					delete []text;
				}

				break;
			}

			break;
		} // WM_COMMAND
	}

	return 0L;
}

LRESULT DcxEdit::PostMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bParsed) {
	switch (uMsg) {
		case WM_HELP:
		{
			if (this->m_pParentDialog->getEventMask() & DCX_EVENT_HELP)
				this->callAliasEx(NULL, "%s,%d", "help", this->getUserID());
			break;
		}

			// disabled this to fix the tabbing problem
			//case WM_GETDLGCODE:
			//    {
			//		if (!this->isStyle(WS_TABSTOP)) {
			//			bParsed = TRUE;
			//			return DLGC_WANTALLKEYS;
			//		}
			//    }
			//    break;

		case WM_NOTIFY:
		{
			LPNMHDR hdr = (LPNMHDR) lParam;

			if (!hdr)
				break;

			switch (hdr->code) {
				case TTN_GETDISPINFO:
				{
					LPNMTTDISPINFO di = (LPNMTTDISPINFO)lParam;
					di->lpszText = this->m_tsToolTip.to_chr();
					di->hinst = NULL;
					bParsed = TRUE;
					break;
				}
				case TTN_LINKCLICK:
				{
					bParsed = TRUE;
					this->callAliasEx(NULL, "%s,%d", "tooltiplink", this->getUserID());
					break;
				}
			}

			break;
		} // WM_NOTIFY
		case WM_KEYDOWN:
		{
			//if (wParam == VK_ESCAPE)
			//	bParsed = TRUE; // prevents parent window closing.
			if (this->m_pParentDialog->getEventMask() & DCX_EVENT_EDIT) {
				if (wParam == VK_RETURN)
					this->callAliasEx(NULL, "%s,%d", "return", this->getUserID());

				if (lParam & 0x40000000)
					break; // ignore repeats.

				this->callAliasEx(NULL, "%s,%d,%d", "keydown", this->getUserID(), wParam);
			}
			/*
			// CTRL+A, select text and return so control doesnt beep
			if ((wParam == 65) &&
			(GetKeyState(VK_CONTROL) & 0x8000))
			{
			this->callAliasEx(ret, "%s,%d", "select", this->getUserID());
			//			bParsed = TRUE;
			//			return TRUE;
			}
			*/

			break;
		}
		case WM_COPY:
		{
			if (this->m_pParentDialog->getEventMask() & DCX_EVENT_EDIT) {
				char ret[256];

				this->callAliasEx(ret, "%s,%d", "copy", this->getUserID());

				if (lstrcmp("nocopy", ret) == 0) {
					bParsed = TRUE;
					return 0L;
				}
			}
			break;
		}
		case WM_CUT:
		{
			if (this->m_pParentDialog->getEventMask() & DCX_EVENT_EDIT) {
				char ret[256];

				this->callAliasEx(ret, "%s,%d", "cut", this->getUserID());

				if (lstrcmp("nocut", ret) == 0) {
					bParsed = TRUE;
					return 0L;
				}
			}
			break;
		}
		case WM_PASTE:
		{
			if (this->m_pParentDialog->getEventMask() & DCX_EVENT_EDIT) {
				char ret[256];

				this->callAliasEx(ret, "%s,%d", "paste", this->getUserID());

				if (lstrcmp("nopaste", ret) == 0) {
					bParsed = TRUE;
					return 0L;
				}
			}
			break;
		}
		case WM_KEYUP:
		{
			if (this->m_pParentDialog->getEventMask() & DCX_EVENT_EDIT)
				this->callAliasEx(NULL, "%s,%d,%d", "keyup", this->getUserID(), wParam);
			break;
		}
		case WM_MOUSEMOVE:
		{
			this->m_pParentDialog->setMouseControl(this->getUserID());
			break;
		}
		case WM_SETFOCUS:
		{
			this->m_pParentDialog->setFocusControl(this->getUserID());
			break;
		}
		case WM_SETCURSOR:
		{
			if ((LOWORD(lParam) == HTCLIENT) &&
				((HWND) wParam == this->m_Hwnd) &&
				(this->m_hCursor != NULL))
			{
				SetCursor(this->m_hCursor);
				bParsed = TRUE;
				return TRUE;
			}

			break;
		}
		case WM_DROPFILES:
		{
			HDROP files = (HDROP) wParam;
			char filename[500];
			int count = DragQueryFile(files, 0xFFFFFFFF,  filename, 500);

			if (count) {
				if (this->m_pParentDialog->getEventMask() & DCX_EVENT_DRAG) {
					char ret[20];

					this->callAliasEx(ret, "%s,%d,%d", "dragbegin", this->getUserID(), count);

					// cancel drag drop event
					if (lstrcmpi(ret, "cancel") == 0) {
						DragFinish(files);
						return 0L;
					}

					// for each file, send callback message
					for (int i = 0; i < count; i++) {
						if (DragQueryFile(files, i, filename, 500))
							this->callAliasEx(NULL, "%s,%d,%s", "dragfile", this->getUserID(), filename);
					}

					this->callAliasEx(NULL, "%s,%d", "dragfinish", this->getUserID());
				}
			}

			DragFinish(files);
			break;
		}
		case WM_PAINT:
			{
				if (!this->m_bAlphaBlend)
					break;
        PAINTSTRUCT ps;
        HDC hdc;

        hdc = BeginPaint( this->m_Hwnd, &ps );

				LRESULT res = 0L;
				bParsed = TRUE;

				// Setup alpha blend if any.
				LPALPHAINFO ai = this->SetupAlphaBlend(&hdc);

				res = CallWindowProc( this->m_DefaultWindowProc, this->m_Hwnd, uMsg, (WPARAM) hdc, lParam );

				this->FinishAlphaBlend(ai);

				EndPaint( this->m_Hwnd, &ps );
				return res;
			}
			break;

		case WM_DESTROY:
		{
			delete this;
			bParsed = TRUE;
			break;
		}
		default:
			break;
	}

	return 0L;
}