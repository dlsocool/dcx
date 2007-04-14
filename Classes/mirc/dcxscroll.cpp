/*!
 * \file dcxscroll.cpp
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

#include "dcxscroll.h"
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

DcxScroll::DcxScroll( UINT ID, DcxDialog * p_Dialog, HWND mParentHwnd, RECT * rc, TString & styles ) 
: DcxControl( ID, p_Dialog )
, m_nPage(5)
, m_nLine(1)
{
	LONG Styles = 0, ExStyles = 0;
	BOOL bNoTheme = FALSE;
	this->parseControlStyles( styles, &Styles, &ExStyles, &bNoTheme );

	this->m_Hwnd = CreateWindowEx(	
		ExStyles, 
		"SCROLLBAR", 
		NULL,
		WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | Styles, 
		rc->left, rc->top, rc->right - rc->left, rc->bottom - rc->top,
		mParentHwnd,
		(HMENU) ID,
		GetModuleHandle(NULL), 
		NULL);

	if ( bNoTheme )
		dcxSetWindowTheme( this->m_Hwnd , L" ", L" " );

	SCROLLINFO si;
	si.cbSize = sizeof( SCROLLINFO );
	si.fMask = SIF_POS | SIF_RANGE;
	si.nPos = 0;
	si.nMin = 0;
	si.nMax = 100;
	SetScrollInfo( this->m_Hwnd, SB_CTL, &si, TRUE );

	this->registreDefaultWindowProc( );
	SetProp( this->m_Hwnd, "dcx_cthis", (HANDLE) this );
}

/*!
 * \brief blah
 *
 * blah
 */

DcxScroll::~DcxScroll( ) {

	this->unregistreDefaultWindowProc( );
}

/*!
 * \brief blah
 *
 * blah
 */

void DcxScroll::parseControlStyles( TString & styles, LONG * Styles, LONG * ExStyles, BOOL * bNoTheme ) {

  unsigned int i = 1, numtok = styles.numtok( );
  
  while ( i <= numtok ) {

    if ( styles.gettok( i ) == "vertical" )
      *Styles |= SBS_VERT;
		else if ( styles.gettok( i ) == "alpha" )
			this->m_bAlphaBlend = true;

    i++;
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

void DcxScroll::parseInfoRequest( TString & input, char * szReturnValue ) {

//  int numtok = input.numtok( );

	TString prop(input.gettok( 3 ));

  // [NAME] [ID] [PROP]
  if ( prop == "value" ) {

    SCROLLINFO si;
    si.cbSize = sizeof( SCROLLINFO );
    si.fMask = SIF_POS;
    GetScrollInfo( this->m_Hwnd, SB_CTL, &si );

    wsprintf( szReturnValue, "%d", si.nPos );
    return;
  }
  // [NAME] [ID] [PROP]
  else if ( prop == "range" ) {

    SCROLLINFO si;
    si.cbSize = sizeof( SCROLLINFO );
    si.fMask = SIF_RANGE;
    GetScrollInfo( this->m_Hwnd, SB_CTL, &si );
    wsprintf( szReturnValue, "%d %d", si.nMin, si.nMax );
    return;
  }
  // [NAME] [ID] [PROP]
  else if ( prop == "line" ) {

    wsprintf( szReturnValue, "%d %d", this->m_nLine );
    return;
  }
  // [NAME] [ID] [PROP]
  else if ( prop == "page" ) {

    wsprintf( szReturnValue, "%d", this->m_nPage );
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

void DcxScroll::parseCommandRequest( TString & input ) {

  XSwitchFlags flags;
  ZeroMemory( (void*)&flags, sizeof( XSwitchFlags ) );
  this->parseSwitchFlags( input.gettok( 3 ), &flags );

  int numtok = input.numtok( );

  //xdid -l [NAME] [ID] [SWITCH] [N]
  if ( flags.switch_flags[11] && numtok > 3 ) {

    int nLine = input.gettok( 4 ).to_int( );

    if ( nLine > 0 )
      this->m_nLine = nLine;
  }
  //xdid -m [NAME] [ID] [SWITCH] [N]
  else if ( flags.switch_flags[12] && numtok > 3 ) {

    int nPage = input.gettok( 4 ).to_int( );

    if ( nPage > 0 )
      this->m_nPage = nPage;
  }
  //xdid -r [NAME] [ID] [SWITCH] [L] [R]
  else if ( flags.switch_flags[17] && numtok > 4 ) {

    INT L = input.gettok( 4 ).to_int( );
    INT R = input.gettok( 5 ).to_int( );

    SCROLLINFO si;
    si.cbSize = sizeof( SCROLLINFO );
    si.fMask = SIF_RANGE;
    si.nMin = L;
    si.nMax = R;
    SetScrollInfo( this->m_Hwnd, SB_CTL, &si, TRUE );
  }
  //xdid -v [NAME] [ID] [SWITCH] [VALUE]
  else if ( flags.switch_flags[21] && numtok > 3 ) {

    int pos = input.gettok( 4 ).to_int( );

    SCROLLINFO si;
    si.cbSize = sizeof( SCROLLINFO );
    si.fMask = SIF_POS;
    si.nPos = pos;
    SetScrollInfo( this->m_Hwnd, SB_CTL, &si, TRUE );
  }
  else
    this->parseGlobalCommandRequest( input, flags );
}

/*!
 * \brief blah
 *
 * blah
 */
LRESULT DcxScroll::ParentMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bParsed) {
	switch (uMsg) {
		case WM_HSCROLL: 
		{
			SCROLLINFO si;
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_PAGE | SIF_POS | SIF_RANGE | SIF_TRACKPOS;
			GetScrollInfo(this->m_Hwnd, SB_CTL, &si);

			switch (LOWORD(wParam)) {
				case SB_TOP:
				{
					si.nPos = si.nMin;
					this->callAliasEx( NULL, "%s,%d,%d", "top", this->getUserID( ), si.nPos );
					break;
				}

				case SB_BOTTOM:
				{
					si.nPos = si.nMax;
					this->callAliasEx( NULL, "%s,%d,%d", "bottom", this->getUserID( ), si.nPos );
					break;
				}

				//case SB_ENDTRACK:
				//  CallAliasEx( p_Dialog, ret, "%s,%d,%d", "sclick", 
				//               this->getUserID( ), p_DcxTrackBar->getPos( ) );
				//  break;

				case SB_PAGEUP:
				{
					if ((si.nPos - this->m_nPage) >= si.nMin)
						si.nPos -= this->m_nPage;
					else
						si.nPos = si.nMin;

					this->callAliasEx(NULL, "%s,%d,%d", "pageup", this->getUserID(), si.nPos);
					break;
				}

				case SB_PAGEDOWN:
				{
					if (si.nPos + this->m_nPage <= si.nMax)
						si.nPos += this->m_nPage;
					else
						si.nPos = si.nMax;

					this->callAliasEx(NULL, "%s,%d,%d", "pagedown", this->getUserID(), si.nPos);
					break;
				}

				case SB_LINEUP:
				{
					if (si.nPos - this->m_nLine >= si.nMin)
						si.nPos -= this->m_nLine;
					else
						si.nPos = si.nMin;

					this->callAliasEx( NULL, "%s,%d,%d", "lineup", this->getUserID( ), si.nPos );
					break;
				}

				case SB_LINEDOWN:
				{
					if (si.nPos + this->m_nLine <= si.nMax)
						si.nPos += this->m_nLine;
					else
						si.nPos = si.nMax;

					this->callAliasEx(NULL, "%s,%d,%d", "linedown", this->getUserID(), si.nPos);
					break;
				}

				case SB_THUMBPOSITION:
				{
					this->callAliasEx(NULL, "%s,%d,%d", "trackend", this->getUserID(), si.nPos);
					break;
				}

				case SB_THUMBTRACK:
				{
					si.nPos = si.nTrackPos;
					this->callAliasEx(NULL, "%s,%d,%d", "tracking", this->getUserID(), si.nTrackPos);
					break;
				}
			}

			bParsed = TRUE;
			si.fMask = SIF_POS;
			SetScrollInfo(this->m_Hwnd, SB_CTL, &si, TRUE);
			break;
		}

		case WM_VSCROLL:
		{
			SCROLLINFO si;
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_PAGE | SIF_POS | SIF_RANGE | SIF_TRACKPOS;
			GetScrollInfo(this->m_Hwnd, SB_CTL, &si);

			switch (LOWORD(wParam)) {
				case SB_TOP:
				{
					si.nPos = si.nMin;
					this->callAliasEx(NULL, "%s,%d,%d", "top", this->getUserID(), si.nPos);
					break;
				}

				case SB_BOTTOM:
				{
					si.nPos = si.nMax;
					this->callAliasEx(NULL, "%s,%d,%d", "bottom", this->getUserID(), si.nPos);
					break;
				}

				//case SB_ENDTRACK:
				//  CallAliasEx( p_Dialog, ret, "%s,%d,%d", "sclick", 
				//               this->getUserID( ), p_DcxTrackBar->getPos( ) );
				//  break;

				case SB_PAGEUP:
				{
					if (si.nPos - this->m_nPage >= si.nMin)
						si.nPos -= this->m_nPage;
					else
						si.nPos = si.nMin;

					this->callAliasEx(NULL, "%s,%d,%d", "pageup", this->getUserID(), si.nPos);
					break;
				}
				
				case SB_PAGEDOWN:
				{
					if (si.nPos + this->m_nPage <= si.nMax)
						si.nPos += this->m_nPage;
					else
						si.nPos = si.nMax;

					this->callAliasEx(NULL, "%s,%d,%d", "pagedown", this->getUserID(), si.nPos);
					break;
				}
				
				case SB_LINEUP:
				{
					if (si.nPos - this->m_nLine >= si.nMin)
						si.nPos -= this->m_nLine;
					else
						si.nPos = si.nMin;

					this->callAliasEx(NULL, "%s,%d,%d", "lineup", this->getUserID(), si.nPos);
					break;
				}

				case SB_LINEDOWN:
				{
					if ( si.nPos + this->m_nLine <= si.nMax )
						si.nPos += this->m_nLine;
					else
						si.nPos = si.nMax;

					this->callAliasEx( NULL, "%s,%d,%d", "linedown", this->getUserID( ), si.nPos );
					break;
				}

				case SB_THUMBPOSITION:
				{
					this->callAliasEx(NULL, "%s,%d,%d", "trackend", this->getUserID(), si.nPos);
					break;
				}

				case SB_THUMBTRACK:
				{
					si.nPos = si.nTrackPos;
					this->callAliasEx(NULL, "%s,%d,%d", "tracking", this->getUserID(), si.nTrackPos);
					break;
				}
			}

			bParsed = TRUE;
			si.fMask = SIF_POS;
			SetScrollInfo(this->m_Hwnd, SB_CTL, &si, TRUE);
			break;
		}
	}

	return 0L;
}

LRESULT DcxScroll::PostMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bParsed ) {

  switch( uMsg ) {

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
      }
      break;

    default:
			return this->CommonMessage( uMsg, wParam, lParam, bParsed);
      break;
  }

  return 0L;
}