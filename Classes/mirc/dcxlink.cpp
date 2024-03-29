/*!
 * \file dcxlink.cpp
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
#include "Classes/mirc/dcxlink.h"
#include "Classes/dcxdialog.h"

/*!
 * \brief Constructor
 *
 * \param ID Control ID
 * \param p_Dialog Parent DcxDialog Object
 * \param mParentHwnd Parent Window Handle
 * \param rc Window Rectangle
 * \param styles Window Style Tokenized List
 */

DcxLink::DcxLink( const UINT ID, DcxDialog * p_Dialog, const HWND mParentHwnd, const RECT * rc, TString & styles ) 
: DcxControl( ID, p_Dialog )
{
	LONG Styles = 0, ExStyles = 0;
	BOOL bNoTheme = FALSE;
	this->parseControlStyles( styles, &Styles, &ExStyles, &bNoTheme );

	this->m_Hwnd = CreateWindowEx(	
		ExStyles, 
		"STATIC", 
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

	this->m_hIcon = NULL;
	this->m_aColors[0] = RGB( 0, 0, 255 );
	this->m_aColors[1] = RGB( 255, 0, 0 );
	this->m_aColors[2] = RGB( 0, 0, 255 );
	this->m_aColors[3] = RGB( 128, 128, 128 );
	this->m_bHover = FALSE;
	this->m_bTracking = FALSE;
	this->m_bVisited = FALSE;

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

DcxLink::~DcxLink( ) {

	if ( this->m_hIcon != NULL )
		DestroyIcon( this->m_hIcon );

	this->unregistreDefaultWindowProc( );
}


void DcxLink::toXml(TiXmlElement * xml) {
	TString buf;
	__super::toXml(xml);
    TGetWindowText( this->m_Hwnd, buf );
	xml->SetAttribute("caption", buf.to_chr());
}

/*!
 * \brief blah
 *
 * blah
 */

void DcxLink::parseControlStyles(TString &styles, LONG *Styles, LONG *ExStyles, BOOL *bNoTheme) {
	*Styles |= SS_NOTIFY;

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

void DcxLink::parseInfoRequest( TString & input, char * szReturnValue ) {

	// [NAME] [ID] [PROP]
	if ( input.gettok( 3 ) == "text" ) {

		GetWindowText( this->m_Hwnd, szReturnValue, MIRC_BUFFER_SIZE_CCH );
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

void DcxLink::parseCommandRequest( TString & input ) {
	const XSwitchFlags flags(input.gettok(3));

	const UINT numtok = input.numtok( );

	// xdid -l [NAME] [ID] [SWITCH] [N] [COLOR]
	if ( flags['l'] && numtok > 4 ) {

		const int nColor = (input.gettok( 4 ).to_int( ) - 1);

		if ( nColor > -1 && nColor < 4 )
			this->m_aColors[nColor] = (COLORREF)input.gettok( 5 ).to_num( );
	}
	// xdid -q [NAME] [ID] [SWITCH] [COLOR1] ... [COLOR4]
	else if ( flags['q'] && numtok > 3 ) {

		const UINT len = input.gettok( 4, -1 ).numtok( );
		for (UINT i = 0; (i < len && i < 4); i++ )
			this->m_aColors[i] = (COLORREF)input.gettok( 4 + i ).to_num( );
	}
	//xdid -t [NAME] [ID] [SWITCH] (TEXT)
	else if ( flags['t'] ) {

		const TString text(input.gettok( 4, -1 ));
		//text.trim( );
		SetWindowText( this->m_Hwnd, text.to_chr( ) );
		this->redrawWindow( );
	}
	// xdid -w [NAME] [ID] [SWITCH] [+FLAGS] [INDEX] [FILENAME]
	else if (flags['w'] && numtok > 5) {
		const TString flag(input.gettok( 4 ));
		const int index = input.gettok( 5 ).to_int();
		TString filename(input.gettok(6, -1));

		if (this->m_hIcon != NULL)
			DestroyIcon(this->m_hIcon);

		this->m_hIcon = dcxLoadIcon(index, filename, false, flag);

		this->redrawWindow();
	}
	else
		this->parseGlobalCommandRequest( input, flags );
}

/*!
 * \brief blah
 *
 * blah
 */
LRESULT DcxLink::ParentMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bParsed ) {
	return 0L;
}

LRESULT DcxLink::PostMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bParsed ) {

	switch( uMsg ) {

	case WM_MOUSEMOVE:
		{
			this->m_pParentDialog->setMouseControl( this->getUserID( ) );

			if ( !this->m_bTracking ) {

				TRACKMOUSEEVENT tme;
				tme.cbSize = sizeof(TRACKMOUSEEVENT);
				tme.hwndTrack = this->m_Hwnd;
				tme.dwFlags = TME_LEAVE | TME_HOVER;
				tme.dwHoverTime = HOVER_DEFAULT; // was 1
				this->m_bTracking = (BOOL) _TrackMouseEvent( &tme );		
			}
		}
		break;

	case WM_MOUSEHOVER:
		{
			if ( !this->m_bHover && this->m_bTracking ) {
				this->m_bHover = TRUE;
				InvalidateRect( this->m_Hwnd, NULL, FALSE );
			}
		}
		break;

	case WM_MOUSELEAVE:
		{
			if ( this->m_bTracking ) {
				this->m_bHover = FALSE;
				this->m_bTracking = FALSE;
				InvalidateRect( this->m_Hwnd, NULL, FALSE );
			}
		}
		break;

	case WM_LBUTTONDOWN:
		{
			if ( this->m_bVisited == FALSE ) {
				this->m_bVisited = TRUE;
				InvalidateRect( this->m_Hwnd, NULL, FALSE );
			}
			if (this->m_pParentDialog->getEventMask() & DCX_EVENT_CLICK)
				this->execAliasEx("%s,%d", "lbdown", this->getUserID( ) );
		}
		break;

	case WM_ENABLE:
		{
			InvalidateRect( this->m_Hwnd, NULL, FALSE );
		}
		break;

	case WM_SETCURSOR:
		{
			if (this->m_hCursor) {
				if (GetCursor() != this->m_hCursor)
					SetCursor( this->m_hCursor );
				bParsed = TRUE;
				return TRUE;
			}
			else if ( LOWORD( lParam ) == HTCLIENT && (HWND) wParam == this->m_Hwnd ) {
				HCURSOR hCursor = LoadCursor( NULL, IDC_HAND );
				if (GetCursor() != hCursor)
					SetCursor( hCursor );
				bParsed = TRUE;
				return TRUE;
			}
		}
		break;

	case WM_ERASEBKGND:
		{
			if (this->isExStyle(WS_EX_TRANSPARENT)) {
				bParsed = TRUE;
				return TRUE;
			}
			break;
		}

	case WM_PRINTCLIENT:
		{
			this->DrawClientArea((HDC)wParam);
			bParsed = TRUE;
		}
		break;
	case WM_PAINT:
		{
			bParsed = TRUE;
			PAINTSTRUCT ps;
			HDC hdc;

			hdc = BeginPaint( this->m_Hwnd, &ps );

			this->DrawClientArea(hdc);

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
//static const char HEX2DEC[256] = 
//{
//    /*       0  1  2  3   4  5  6  7   8  9  A  B   C  D  E  F */
//    /* 0 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
//    /* 1 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
//    /* 2 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
//    /* 3 */  0, 1, 2, 3,  4, 5, 6, 7,  8, 9,-1,-1, -1,-1,-1,-1,
//    
//    /* 4 */ -1,10,11,12, 13,14,15,-1, -1,-1,-1,-1, -1,-1,-1,-1,
//    /* 5 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
//    /* 6 */ -1,10,11,12, 13,14,15,-1, -1,-1,-1,-1, -1,-1,-1,-1,
//    /* 7 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
//    
//    /* 8 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
//    /* 9 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
//    /* A */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
//    /* B */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
//    
//    /* C */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
//    /* D */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
//    /* E */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
//    /* F */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1
//};
//    
//TString DcxLink::UriDecode(const TString & sSrc)
//{
//	// Note from RFC1630:  "Sequences which start with a percent sign
//	// but are not followed by two hexadecimal characters (0-9, A-F) are reserved
//	// for future extension"
//
//	const unsigned char * pSrc = (const unsigned char *)sSrc.to_chr();
//	const int SRC_LEN = sSrc.len();
//	const unsigned char * const SRC_END = pSrc + SRC_LEN;
//	const unsigned char * const SRC_LAST_DEC = SRC_END - 2;   // last decodable '%' 
//
//	char * const pStart = new char[SRC_LEN];
//	char * pEnd = pStart;
//
//	while (pSrc < SRC_LAST_DEC)
//	{
//		if (*pSrc == '%')
//		{
//			char dec1, dec2;
//			if (-1 != (dec1 = HEX2DEC[*(pSrc + 1)])
//				&& -1 != (dec2 = HEX2DEC[*(pSrc + 2)]))
//			{
//				*pEnd++ = (dec1 << 4) + dec2;
//				pSrc += 3;
//				continue;
//			}
//		}
//
//		*pEnd++ = *pSrc++;
//	}
//
//	// the last 2- chars
//	while (pSrc < SRC_END)
//		*pEnd++ = *pSrc++;
//
//	TString sResult(pStart, pEnd);
//	delete [] pStart;
//	return sResult;
//}
//
//// Only alphanum is safe.
//static const char SAFE[256] =
//{
//    /*      0 1 2 3  4 5 6 7  8 9 A B  C D E F */
//    /* 0 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
//    /* 1 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
//    /* 2 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
//    /* 3 */ 1,1,1,1, 1,1,1,1, 1,1,0,0, 0,0,0,0,
//    
//    /* 4 */ 0,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,
//    /* 5 */ 1,1,1,1, 1,1,1,1, 1,1,1,0, 0,0,0,0,
//    /* 6 */ 0,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,
//    /* 7 */ 1,1,1,1, 1,1,1,1, 1,1,1,0, 0,0,0,0,
//    
//    /* 8 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
//    /* 9 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
//    /* A */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
//    /* B */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
//    
//    /* C */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
//    /* D */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
//    /* E */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
//    /* F */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0
//};
//
//TString DcxLink::UriEncode(const TString & sSrc)
//{
//	const char DEC2HEX[16 + 1] = "0123456789ABCDEF";
//	const unsigned char * pSrc = (const unsigned char *)sSrc.to_chr();
//	const int SRC_LEN = sSrc.len();
//	unsigned char * const pStart = new unsigned char[SRC_LEN * 3];
//	unsigned char * pEnd = pStart;
//	const unsigned char * const SRC_END = pSrc + SRC_LEN;
//
//	for (; pSrc < SRC_END; ++pSrc)
//	{
//		if (SAFE[*pSrc]) 
//			*pEnd++ = *pSrc;
//		else
//		{
//			// escape this char
//			*pEnd++ = '%';
//			*pEnd++ = DEC2HEX[*pSrc >> 4];
//			*pEnd++ = DEC2HEX[*pSrc & 0x0F];
//		}
//	}
//
//	TString sResult((char *)pStart, (char *)pEnd);
//	delete [] pStart;
//	return sResult;
//}

void DcxLink::DrawClientArea(HDC hdc)
{
	// Setup alpha blend if any.
	LPALPHAINFO ai = this->SetupAlphaBlend(&hdc);

	RECT rect;
	GetClientRect( this->m_Hwnd, &rect );

	// fill background.
	DcxControl::DrawCtrlBackground(hdc,this,&rect);

	HFONT hFont = this->m_hFont;

	if (hFont == NULL)
		hFont = GetStockFont( DEFAULT_GUI_FONT /*SYSTEM_FONT*/ );

	LOGFONT lf;
	GetObject( hFont, sizeof( LOGFONT ), &lf );

	lf.lfUnderline = TRUE;

	HFONT hNewFont = CreateFontIndirect( &lf );
	HFONT hOldFont = SelectFont( hdc, hNewFont );

	const int oldMode = SetBkMode( hdc, TRANSPARENT );

	if ( this->m_hIcon != NULL ) {

		const int y = ( rect.top + rect.bottom - 16 ) / 2;
		DrawIconEx( hdc, rect.left, y, this->m_hIcon, 0, 0, NULL, NULL, DI_NORMAL );

		OffsetRect( &rect, 20, 0 );
	}

	if ( IsWindowEnabled( this->m_Hwnd ) == FALSE )
		this->m_clrText = this->m_aColors[3];
	else if ( this->m_bHover )
		this->m_clrText = this->m_aColors[1];
	else if ( this->m_bVisited )
		this->m_clrText = this->m_aColors[2];
	else
		this->m_clrText = this->m_aColors[0];

	TString wtext;

	TGetWindowText(this->m_Hwnd, wtext);
	this->ctrlDrawText(hdc, wtext, &rect, DT_LEFT | DT_NOPREFIX | DT_SINGLELINE | DT_VCENTER);
	//int nText = TGetWindowText(this->m_Hwnd, wtext);

	//if (!this->m_bCtrlCodeText) {
	//	if (this->m_bShadowText) { // could cause problems with pre-XP as this is commctrl v6+
	//		dcxDrawShadowText(hdc,wtext.to_wchr(this->m_bUseUTF8), wtext.wlen(), &rect,
	//			DT_LEFT | DT_NOPREFIX | DT_SINGLELINE | DT_VCENTER, this->m_clrText, 0, 5, 5);
	//	}
	//	else {
	//		SetTextColor( hdc, this->m_clrText );
	//		DrawTextW( hdc, wtext.to_wchr(this->m_bUseUTF8), nText, &rect, DT_LEFT | DT_NOPREFIX | DT_SINGLELINE | DT_VCENTER );
	//	}
	//}
	//else
	//	mIRC_DrawText(hdc, wtext, &rect, DT_LEFT | DT_NOPREFIX | DT_SINGLELINE | DT_VCENTER, this->m_bShadowText, this->m_bUseUTF8);

	SetBkMode(hdc, oldMode);
	SelectFont( hdc, hOldFont );
	DeleteFont( hNewFont );

	this->FinishAlphaBlend(ai);
}
