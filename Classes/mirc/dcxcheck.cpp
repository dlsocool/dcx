/*!
 * \file dcxcheck.cpp
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
#include "defines.h"
#include "Classes/mirc/dcxcheck.h"
#include "Classes/dcxdialog.h"
#include "Dcx.h"



/*!
 * \brief Constructor
 *
 * \param ID Control ID
 * \param p_Dialog Parent DcxDialog Object
 * \param mParentHwnd Parent Window Handle
 * \param rc Window Rectangle
 * \param styles Window Style Tokenized List
 */

DcxCheck::DcxCheck( const UINT ID, DcxDialog * p_Dialog, const HWND mParentHwnd, const RECT * rc, TString & styles ) 
: DcxControl( ID, p_Dialog )
{
	LONG Styles = 0, ExStyles = 0;
	BOOL bNoTheme = FALSE;
	this->parseControlStyles( styles, &Styles, &ExStyles, &bNoTheme );

	this->m_Hwnd = CreateWindowEx(	
		ExStyles, 
		"BUTTON", 
		NULL,
		WS_CHILD | Styles,
		rc->left, rc->top, rc->right - rc->left, rc->bottom - rc->top,
		mParentHwnd,
		(HMENU) ID,
		GetModuleHandle(NULL),
		NULL);

	if (!IsWindow(this->m_Hwnd))
		throw "Unable To Create Window";

	if ( bNoTheme )
		Dcx::UXModule.dcxSetWindowTheme( this->m_Hwnd , L" ", L" " );

	this->m_bNoTheme = (bNoTheme ? true : false);

	if (p_Dialog->getToolTip() != NULL) {
		if (styles.istok("tooltips")) {

			this->m_ToolTipHWND = p_Dialog->getToolTip();

			AddToolTipToolInfo(this->m_ToolTipHWND, this->m_Hwnd);
		}
	}

	this->setControlFont( GetStockFont( DEFAULT_GUI_FONT ), FALSE );
	this->registreDefaultWindowProc( );
	SetProp( this->m_Hwnd, "dcx_cthis", (HANDLE) this );
}

/*!
 * \brief blah
 *
 * blah
 */

DcxCheck::~DcxCheck( ) {
	this->unregistreDefaultWindowProc( );
}


void DcxCheck::toXml(TiXmlElement * xml) {
	TString wtext;
	__super::toXml(xml);
	TGetWindowText(this->m_Hwnd, wtext);
	xml->SetAttribute("caption", wtext.to_chr());
}

TString DcxCheck::getStyles(void) {
	TString styles(__super::getStyles());
	const DWORD Styles = GetWindowStyle(this->m_Hwnd);

	if (Styles & BS_RIGHT)
		styles.addtok("rjustify");
	if (Styles & BS_CENTER)
		styles.addtok("center");
	if (Styles & BS_LEFT)
		styles.addtok("ljustify");
	if (Styles & BS_RIGHTBUTTON)
		styles.addtok("right");
	if (Styles & BS_PUSHLIKE)
		styles.addtok("pushlike");
	if (Styles & BS_AUTO3STATE)
		styles.addtok("3state");
	return styles;
}

/*!
 * \brief blah
 *
 * blah
 */

void DcxCheck::parseControlStyles( TString & styles, LONG * Styles, LONG * ExStyles, BOOL * bNoTheme ) {

	const UINT numtok = styles.numtok( );
	*Styles |= BS_AUTOCHECKBOX;

	for (UINT i = 1; i <= numtok; i++ )
	{
		if ( styles.gettok( i ) == "rjustify" )
			*Styles |= BS_RIGHT;
		else if ( styles.gettok( i ) == "center" )
			*Styles |= BS_CENTER;
		else if ( styles.gettok( i ) == "ljustify" )
			*Styles |= BS_LEFT;
		else if ( styles.gettok( i ) == "right" )
			*Styles |= BS_RIGHTBUTTON;
		else if ( styles.gettok( i ) == "pushlike" )
			*Styles |= BS_PUSHLIKE;
		else if ( styles.gettok( i ) == "3state" ) {
			*Styles &= ~BS_AUTOCHECKBOX;
			*Styles |= BS_AUTO3STATE;
		}
	}

	this->parseGeneralControlStyles( styles, Styles, ExStyles, bNoTheme );
}

/*!
 * \brief $xdid Parsing Function
 *
 * \param input [NAME] [ID] [PROP] (OPTIONS)
 * \param szReturnValue mIRC Data Container
 *
 * \return > void
 */

void DcxCheck::parseInfoRequest( TString & input, char * szReturnValue ) {

	const TString prop(input.gettok( 3 ));

	// [NAME] [ID] [PROP]
	if ( prop == "text" ) {

		GetWindowText( this->m_Hwnd, szReturnValue, MIRC_BUFFER_SIZE_CCH );
		return;
	}
	// [NAME] [ID] [PROP]
	else if ( prop == "state" ) {

		if ( Button_GetCheck( this->m_Hwnd ) & BST_INDETERMINATE )
			lstrcpy( szReturnValue, "2" );
		else if ( Button_GetCheck( this->m_Hwnd ) & BST_CHECKED )
			lstrcpy( szReturnValue, "1" );
		else
			lstrcpy( szReturnValue, "0" );

		return;
	}
	else if ( this->parseGlobalInfoRequest( input, szReturnValue ) )
		return;

	szReturnValue[0] = 0;
}

/*!
 * \brief blah
 *
 * blah
 */

void DcxCheck::parseCommandRequest( TString & input ) {
	const XSwitchFlags flags(input.gettok(3));

	//xdid -c [NAME] [ID] [SWITCH]
	if (flags['c']) {
		// xdid -cu
		if (flags['u'])
			Button_SetCheck(this->m_Hwnd, BST_INDETERMINATE);
		else
			Button_SetCheck(this->m_Hwnd, BST_CHECKED);
	}
	//xdid -t [NAME] [ID] [SWITCH] ItemText
	else if (flags['t']) {
		SetWindowText(this->m_Hwnd, input.gettok(4, -1).trim().to_chr());
	}
	//xdid -u [NAME] [ID] [SWITCH]
	else if ( flags['u'] ) {

		Button_SetCheck( this->m_Hwnd, BST_UNCHECKED );
	}
	else
		this->parseGlobalCommandRequest( input, flags );
}

/*!
 * \brief blah
 *
 * blah
 */
LRESULT DcxCheck::ParentMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bParsed ) {
	switch (uMsg)
	{
	case WM_COMMAND:
		{
			switch (HIWORD(wParam))
			{
				// catch this so we can use $xdid(checkbox).state in sclick callback
			case BN_CLICKED:
				{
					if (this->m_pParentDialog->getEventMask() & DCX_EVENT_CLICK)
					{
						//this->execAliasEx("%s,%d", "sclick", this->getUserID());

						// /.timer repetitions delay alias dialog event id
						Dcx::mIRC.execex("/.timer 1 0 %s %s %s %d",
							this->m_pParentDialog->getAliasName().to_chr(),
							this->m_pParentDialog->getName().to_chr(),
							"sclick",
							this->getUserID());
					}

					break;
				}
			}

			break;
		}
	}

	return 0L;
}
LRESULT DcxCheck::PostMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bParsed ) {

	switch( uMsg ) {

		case WM_LBUTTONUP:
			{
				if (this->m_pParentDialog->getEventMask() & DCX_EVENT_CLICK)
					this->execAliasEx("%s,%d", "lbup", this->getUserID( ) );
			}
			break;

		case WM_ERASEBKGND:
			{
				bParsed = TRUE;
				return TRUE;
			}
			break;

		case WM_PRINTCLIENT:
			{
				this->DrawClientArea((HDC)wParam, uMsg, lParam);
				bParsed = TRUE;
			}
			break;
		case WM_PAINT:
			{
				bParsed = TRUE;
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint( this->m_Hwnd, &ps );

				this->DrawClientArea( hdc, uMsg, lParam);

				EndPaint( this->m_Hwnd, &ps );
			}
			break;

		case WM_DESTROY:
			{
				delete this;
				bParsed = TRUE;
			}
			break;

		default:
			return this->CommonMessage( uMsg, wParam, lParam, bParsed);
			break;
	}

	return 0L;
}

void DcxCheck::DrawClientArea(HDC hdc, const UINT uMsg, LPARAM lParam)
{
	// Setup alpha blend if any.
	LPALPHAINFO ai = this->SetupAlphaBlend(&hdc);

	if (this->m_bNoTheme || !Dcx::UXModule.dcxIsThemeActive()) {
		if (this->m_clrBackText != CLR_INVALID)
			SetBkColor(hdc, this->m_clrBackText);

		if (this->m_clrText != CLR_INVALID)
			SetTextColor(hdc, this->m_clrText);

		RECT rcClient;

		// get controls client area
		GetClientRect( this->m_Hwnd, &rcClient );

		BOOL bWasTransp = this->isExStyle(WS_EX_TRANSPARENT);

		// fill background.
		if (bWasTransp)
		{
			if (!this->m_bAlphaBlend)
				this->DrawParentsBackground(hdc,&rcClient);
		}
		else
			DcxControl::DrawCtrlBackground(hdc,this,&rcClient);

		// This is a workaround to allow our background to be seen under the control.
		if (!bWasTransp)
			AddStyles(this->m_Hwnd, GWL_EXSTYLE, WS_EX_TRANSPARENT);

		CallWindowProc( this->m_DefaultWindowProc, this->m_Hwnd, uMsg, (WPARAM) hdc, lParam );

		if (!bWasTransp)
			RemStyles(this->m_Hwnd, GWL_EXSTYLE, WS_EX_TRANSPARENT);
	}
	else
		CallWindowProc( this->m_DefaultWindowProc, this->m_Hwnd, uMsg, (WPARAM) hdc, lParam );

	this->FinishAlphaBlend(ai);
}
