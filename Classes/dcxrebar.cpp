/*!
 * \file dcxrebar.cpp
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
#include "Classes/dcxrebar.h"
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

DcxReBar::DcxReBar( const UINT ID, DcxDialog * p_Dialog, const HWND mParentHwnd, const RECT * rc, TString & styles ) 
: DcxControl( ID, p_Dialog ) 
, m_iClickedBand(-1)
, m_iRowLimit(0)
, m_iWidth(0)
, m_iHeight(0)
{
	LONG Styles = 0, ExStyles = 0;
	BOOL bNoTheme = FALSE;
	this->parseControlStyles( styles, &Styles, &ExStyles, &bNoTheme );

	this->m_Hwnd = CreateWindowEx(
		ExStyles | WS_EX_CONTROLPARENT,
		DCX_REBARCTRLCLASS,
		NULL,
		WS_CHILD | Styles,
		rc->left, rc->top, rc->right - rc->left, rc->bottom - rc->top,
		mParentHwnd,
		(HMENU) ID,
		GetModuleHandle(NULL),
		NULL);

	if (!IsWindow(this->m_Hwnd))
		throw "Unable To Create Window";

	if ( bNoTheme ) {
		//SendMessage( this->m_Hwnd, RB_SETWINDOWTHEME, NULL, L" ");
		Dcx::UXModule.dcxSetWindowTheme( this->m_Hwnd , L" ", L" " );
	}
	{
		this->setImageList( this->createImageList() );
		//REBARINFO rbi;
		//rbi.cbSize = sizeof(REBARINFO);
		//rbi.fMask = 0;
		//rbi.himl = NULL;
		//this->setBarInfo( &rbi );
	}
	this->setControlFont( GetStockFont( DEFAULT_GUI_FONT ), FALSE );
	this->registreDefaultWindowProc( );
	SetProp( this->m_Hwnd, "dcx_cthis", (HANDLE) this );
}

/*!
 * \brief Destructor
 *
 * blah
 */

DcxReBar::~DcxReBar( ) {

  this->resetContents( );

  ImageList_Destroy( this->getImageList( ) );

  this->unregistreDefaultWindowProc( );
}

TString DcxReBar::getStyles(void) {
	TString styles(__super::getStyles());
	DWORD Styles;
	Styles = GetWindowStyle(this->m_Hwnd);
	if (Styles & RBS_BANDBORDERS)
		styles.addtok("borders");
	if (Styles & RBS_DBLCLKTOGGLE)
		styles.addtok("dblclktoggle");
	if (Styles & RBS_FIXEDORDER)
		styles.addtok("fixedorder");
	if (Styles & RBS_VARHEIGHT)
		styles.addtok("varheight");
	if (Styles & RBS_TOOLTIPS)
		styles.addtok("tooltips");
	if (Styles & RBS_VERTICALGRIPPER)
		styles.addtok("verticalgrip");
	if (Styles & CCS_VERT)
		styles.addtok("vertical");
	if (Styles & CCS_RIGHT)
		styles.addtok("right");
	if (Styles & CCS_BOTTOM)
		styles.addtok("bottom");
	if (Styles & CCS_NORESIZE)
		styles.addtok("noresize");
	if (Styles & CCS_NOPARENTALIGN)
		styles.addtok("noparentalign");
	if (Styles & (CCS_NOPARENTALIGN | CCS_NORESIZE))
		styles.addtok("noauto");
	return styles;

}


void DcxReBar::toXml(TiXmlElement * xml) {
	__super::toXml(xml);
	int count = this->getBandCount( );
	TiXmlElement * subs;
	DcxControl * c;
	if (count > 0) {
		for (int i = 0; i < count; i++) {
			c = getControl(i);
			if (c) {
				subs = new TiXmlElement("control");
				c->toXml(subs);
				xml->LinkEndChild(subs);
			}
		}
	}
}

DcxControl * DcxReBar::getControl(const int index) {

    if ( index > -1 && index < this->getBandCount( ) ) {
      
      REBARBANDINFO rbBand;
      ZeroMemory( &rbBand, sizeof( REBARBANDINFO ) );
      rbBand.cbSize = sizeof( REBARBANDINFO );
      rbBand.fMask = RBBIM_CHILD;

      if ( this->getBandInfo( index, &rbBand ) != 0 )
        return this->m_pParentDialog->getControlByHWND( rbBand.hwndChild );

    }
	return NULL;
}

/*!
 * \brief blah
 *
 * blah
 */

void DcxReBar::parseControlStyles( TString & styles, LONG * Styles, LONG * ExStyles, BOOL * bNoTheme ) {

  *Styles |= RBS_AUTOSIZE;
  unsigned int i = 1, numtok = styles.numtok( );

	//*ExStyles |= WS_EX_CONTROLPARENT;

  while ( i <= numtok ) {

    if ( styles.gettok( i ) == "borders" ) 
      *Styles |= RBS_BANDBORDERS;
    else if ( styles.gettok( i ) == "dblclktoggle" ) 
      *Styles |= RBS_DBLCLKTOGGLE;
    else if ( styles.gettok( i ) == "fixedorder" ) 
      *Styles |= RBS_FIXEDORDER;
    else if ( styles.gettok( i ) == "varheight" ) 
      *Styles |= RBS_VARHEIGHT;
    else if ( styles.gettok( i ) == "tooltips" ) 
      *Styles |= RBS_TOOLTIPS;
    else if ( styles.gettok( i ) == "verticalgrip" ) 
      *Styles |= RBS_VERTICALGRIPPER;
    else if ( styles.gettok( i ) == "vertical" ) 
      *Styles |= CCS_VERT;
    else if ( styles.gettok( i ) == "right" ) 
      *Styles |= CCS_RIGHT;
    else if ( styles.gettok( i ) == "bottom" ) 
      *Styles |= CCS_BOTTOM;
    else if ( styles.gettok( i ) == "noresize" ) 
      *Styles |= CCS_NORESIZE;
    else if ( styles.gettok( i ) == "noparentalign" ) 
      *Styles |= CCS_NOPARENTALIGN ;
	else if ( styles.gettok( i ) == "noauto" )
      *Styles |= CCS_NOPARENTALIGN | CCS_NORESIZE;

    i++;
  }
  this->parseGeneralControlStyles( styles, Styles, ExStyles, bNoTheme );
}

/*!
 * \brief blah
 *
 * blah
 */

HIMAGELIST DcxReBar::getImageList( ) const {

  REBARINFO ri;
  ZeroMemory(&ri, sizeof(REBARINFO));
  ri.cbSize = sizeof(REBARINFO);
  ri.fMask = RBIM_IMAGELIST;
  this->getBarInfo( &ri );
  return ri.himl;
}

/*!
 * \brief blah
 *
 * blah
 */

void DcxReBar::setImageList( HIMAGELIST himl ) {

  REBARINFO ri;
  ZeroMemory( &ri, sizeof(REBARINFO) );
  ri.cbSize = sizeof(REBARINFO);
  ri.himl = himl;
  ri.fMask = RBIM_IMAGELIST;
  this->setBarInfo( &ri );
}

/*!
 * \brief blah
 *
 * blah
 */

HIMAGELIST DcxReBar::createImageList( ) {
  return ImageList_Create( 16, 16, ILC_COLOR32|ILC_MASK, 1, 0 );
}

/*!
 * \brief $xdid Parsing Function
 *
 * \param input [NAME] [ID] [PROP] (OPTIONS)
 * \param szReturnValue mIRC Data Container
 *
 * \return > void
 */

void DcxReBar::parseInfoRequest( TString & input, char * szReturnValue ) {

	int numtok = input.numtok( );

	TString prop(input.gettok( 3 ));

	if ( prop == "num" ) {

		wnsprintf( szReturnValue, MIRC_BUFFER_SIZE_CCH, "%d", this->getBandCount( ) );
		return;
	}
	// [NAME] [ID] [PROP] [N]
	else if ( prop == "text" && numtok > 3 ) {

		int nIndex = input.gettok( 4 ).to_int( ) - 1;

		if ( nIndex > -1 && nIndex < this->getBandCount( ) ) {

			REBARBANDINFO rbBand;
			ZeroMemory( &rbBand, sizeof( REBARBANDINFO ) );
			rbBand.cbSize = sizeof( REBARBANDINFO );
			rbBand.fMask = RBBIM_TEXT;
			rbBand.cch = MIRC_BUFFER_SIZE_CCH;
			rbBand.lpText = szReturnValue;
			if ( this->getBandInfo( nIndex, &rbBand ) != 0 )
				return;
		}
	}
	else if ( prop == "childid" && numtok > 3 ) {

		int nItem = input.gettok( 4 ).to_int( ) - 1;
		DcxControl * c = getControl(nItem);
		if ( c != NULL )
			wnsprintf( szReturnValue, MIRC_BUFFER_SIZE_CCH, "%d", c->getUserID( ) );

		return;
	}
	// $xdid([NAME], [ID], [N]).[PROP]
	else if (prop == "markeditem") {
		REBARBANDINFO rbi;
		LPDCXRBBAND pdcxrbb;
		int n = input.gettok(4).to_int();

		if (n < 1 || n > this->getBandCount()) {
			this->showErrorEx("markeditem", NULL, "Invalid band index: %d", n);
			return;
		}

		// Zero based index
		n--;

		ZeroMemory(&rbi, sizeof(REBARBANDINFO));
		rbi.cbSize = sizeof(REBARBANDINFO);
		rbi.fMask = RBBIM_LPARAM;
		this->getBandInfo(n, &rbi);
		pdcxrbb = (LPDCXRBBAND) rbi.lParam;

		//wnsprintf(szReturnValue, MIRC_BUFFER_SIZE_CCH, "%s", pdcxrbb->tsMarkText.to_chr());
		lstrcpyn(szReturnValue, pdcxrbb->tsMarkText.to_chr(), MIRC_BUFFER_SIZE_CCH);
		return;
	}
	else if ( this->parseGlobalInfoRequest( input, szReturnValue ) )
		return;

	szReturnValue[0] = 0;
}
/*!
* \brief blah
*
* \param input [NAME] [SWITCH] [ID] (OPTIONS)
*/

void DcxReBar::parseCommandRequest( TString & input ) {
	XSwitchFlags flags(input.gettok(3));
	int numtok = input.numtok();

	// xdid -a [NAME] [ID] [SWITCH] [N] [+FLAGS] [CX] [CY] [WIDTH] [ICON] [COLOR] [Item Text][TAB][ID] [CONTROL] [X] [Y] [W] [H] (OPTIONS)[TAB]Tooltip
	if ( flags['a'] && numtok > 9 ) {

		REBARBANDINFO rbBand;
		ZeroMemory( &rbBand, sizeof( REBARBANDINFO ) );
#ifdef DCX_USE_WINSDK
		if (Dcx::VistaModule.isUseable()) // NB: when rbBand.cbSize is set to the Vista size on XP the insertband will FAIL!! fucking MS!
			rbBand.cbSize = sizeof( REBARBANDINFO );
		else
			rbBand.cbSize = REBARBANDINFO_V6_SIZE;
#else
		rbBand.cbSize = sizeof( REBARBANDINFO );
#endif
		rbBand.fMask = RBBIM_STYLE | RBBIM_LPARAM;

		TString data(input.gettok(1, TSTAB).trim());
		TString control_data;

		if (input.numtok(TSTAB) > 1) {
			control_data = input.gettok(2, TSTAB).trim();
		}

		TString tooltip;
		if (input.numtok(TSTAB) > 2) {
			tooltip = input.gettok(3, TSTAB).trim();
		}

		int nIndex = data.gettok( 4 ).to_int( ) - 1;
		int cx = data.gettok( 6 ).to_int( );
		int cy = data.gettok( 7 ).to_int( );
		int width = data.gettok( 8 ).to_int( );
		int nIcon = data.gettok( 9 ).to_int( ) - 1;
		COLORREF clrText = (COLORREF)data.gettok( 10 ).to_num( );

		if (nIndex < -1)
			nIndex = -1;

		rbBand.cxMinChild = cx;
		rbBand.cyMinChild = cy;
		rbBand.cx = width;
		rbBand.cyIntegral = 1;
		rbBand.cyChild = cy;

		TString itemtext;
		if ( data.numtok( ) > 10 ) {
			itemtext = data.gettok(11, -1).trim();
			rbBand.fMask |= RBBIM_TEXT;
			rbBand.lpText = itemtext.to_chr( );
			//rbBand.cch = itemtext.len();
		}

		rbBand.fStyle = this->parseBandStyleFlags( data.gettok( 5 ) );

		// Tooltip Handling
		LPDCXRBBAND lpdcxrbb = new DCXRBBAND;

		if (lpdcxrbb == NULL) {
			this->showError(NULL, "-a", "Unable To Create Control, Unable to Allocate Memory");
			return;
		}

		if ( rbBand.fStyle & RBBS_UNDERLINE )
			lpdcxrbb->bUline = TRUE;
		else
			lpdcxrbb->bUline = FALSE;

		if ( rbBand.fStyle & RBBS_BOLD )
			lpdcxrbb->bBold = TRUE;
		else
			lpdcxrbb->bBold = FALSE;

		if ( rbBand.fStyle & RBBS_COLOR )
			lpdcxrbb->clrText = clrText;
		else
			lpdcxrbb->clrText = CLR_INVALID;

		if ( nIcon > -1 ) {
			rbBand.iImage = nIcon;
			rbBand.fMask |= RBBIM_IMAGE;
		}

		rbBand.lParam = (LPARAM) lpdcxrbb;

		DcxControl * p_Control = NULL;
		if ( control_data.numtok( ) > 5 ) {
			UINT ID = mIRC_ID_OFFSET + control_data.gettok( 1 ).to_int( );

			if ( ID > mIRC_ID_OFFSET - 1 && 
				!IsWindow( GetDlgItem( this->m_pParentDialog->getHwnd( ), ID ) ) && 
				this->m_pParentDialog->getControlByID( ID ) == NULL ) 
			{
				try {
					p_Control = DcxControl::controlFactory(this->m_pParentDialog,ID,control_data,2,
						CTLF_ALLOW_TRACKBAR |
						CTLF_ALLOW_PBAR |
						CTLF_ALLOW_COMBOEX |
						CTLF_ALLOW_TOOLBAR |
						CTLF_ALLOW_STATUSBAR |
						CTLF_ALLOW_TREEVIEW |
						CTLF_ALLOW_LISTVIEW |
						CTLF_ALLOW_COLORCOMBO |
						CTLF_ALLOW_BUTTON |
						CTLF_ALLOW_RICHEDIT |
						CTLF_ALLOW_DIVIDER |
						CTLF_ALLOW_PANEL |
						CTLF_ALLOW_TAB
						,this->m_Hwnd);
					if ( p_Control != NULL ) {
						if ((p_Control->getType() == "statusbar") || (p_Control->getType() == "toolbar"))
							p_Control->addStyle( CCS_NOPARENTALIGN | CCS_NORESIZE );
						this->m_pParentDialog->addControl( p_Control );
						rbBand.fMask |= RBBIM_CHILD | RBBIM_CHILDSIZE | RBBIM_SIZE | RBBIM_ID;
						rbBand.hwndChild = p_Control->getHwnd( );
						//rbBand.cxMinChild = cx;
						//rbBand.cyMinChild = cy;
						//rbBand.cx = width;
						//rbBand.cyIntegral = 1;
						//rbBand.cyChild = cy;
						rbBand.wID = ID;
					}
				}
				catch ( char *err ) {
					this->showErrorEx(NULL, "-a", "Unable To Create Control: %d (%s)", ID - mIRC_ID_OFFSET, err );
					delete lpdcxrbb;
					return;
				}
			}
			else {
				this->showErrorEx(NULL, "-a", "Control with ID \"%d\" already exists", ID - mIRC_ID_OFFSET );
				delete lpdcxrbb;
				return;
			}
		}

		//LRESULT lRes;
		//rbBand.cbSize = sizeof(REBARBANDINFO);
		//rbBand.fMask = RBBIM_LPARAM|RBBIM_TEXT;
		//rbBand.cch = itemtext.len();
		//rbBand.lpText = itemtext.to_chr();
		////this->insertBand( nIndex, &rbBand );
		//lRes = SendMessage(this->m_Hwnd, RB_INSERTBAND, (WPARAM)-1, (LPARAM)&rbBand);
		//mIRCDebug("res: %ld", lRes);
		if (this->insertBand( nIndex, &rbBand ) == 0L) { // 0L means failed.
			this->showError(NULL, "-a", "Unable To Add Band");
			if (p_Control != NULL) {
				this->m_pParentDialog->deleteControl(p_Control);
				DestroyWindow(rbBand.hwndChild);
			}
			delete lpdcxrbb;
		}
	}
	// xdid -A [NAME] [ID] [SWITCH] [N] (TEXT)
	else if (flags['A'] && numtok > 3) {
		REBARBANDINFO rbi;
		LPDCXRBBAND pdcxrbb;
		int n = input.gettok(4).to_int();

		if (n < 1 || n > this->getBandCount()) {
			this->showErrorEx(NULL, "-A", "Invalid band index: %d", n);
			return;
		}

		// Zero based index
		n--;

		ZeroMemory(&rbi, sizeof(REBARBANDINFO));
		rbi.cbSize = sizeof(REBARBANDINFO);
		rbi.fMask = RBBIM_LPARAM;
		this->getBandInfo(n, &rbi);
		pdcxrbb = (LPDCXRBBAND) rbi.lParam;
		pdcxrbb->tsMarkText = (numtok > 4 ? input.gettok(5, -1) : "");
	}
	// xdid -d [NAME] [ID] [SWITCH] [N]
	else if ( flags['d'] && numtok > 3 ) {

		int nIndex = input.gettok( 4 ).to_int( ) - 1;

		if ( nIndex > -1 && nIndex < this->getBandCount( ) ) {

			this->deleteBand( nIndex );
		}
	}
	// xdid -i [NAME] [ID] [SWITCH] [N]
	else if ( flags['i'] && numtok > 3 ) {

		int nIndex = input.gettok( 4 ).to_int( ) - 1;

		if ( nIndex > -1 && nIndex < this->getBandCount( ) ) {

			this->showBand( nIndex, FALSE );
		}
	}
	// xdid -j [NAME] [ID] [SWITCH] [N]
	else if ( flags['j'] && numtok > 3 ) {

		int nIndex = input.gettok( 4 ).to_int( ) - 1;

		if ( nIndex > -1 && nIndex < this->getBandCount( ) ) {

			this->showBand( nIndex, TRUE );
		}
	}
	// xdid -k [NAME] [ID] [SWITCH] [N] [ICON]
	else if ( flags['k'] && numtok > 4 ) {

		REBARBANDINFO rbBand;
		ZeroMemory( &rbBand, sizeof( REBARBANDINFO ) );
		rbBand.cbSize = sizeof( REBARBANDINFO );
		rbBand.fMask = RBBIM_IMAGE;

		int nIndex = input.gettok( 4 ).to_int( ) - 1;
		int nIcon = input.gettok( 5 ).to_int( ) - 1;
		if ( nIndex > -1 && nIndex < this->getBandCount( ) && nIcon > -2 ) {

			rbBand.iImage = nIcon;
			this->setBandInfo( nIndex, &rbBand );
		}
	}
	// xdid -l [NAME] [ID] [SWITCH] [N|ALL]
	else if ( flags['l'] && numtok > 3 ) {

		REBARBANDINFO rbBand;
		ZeroMemory( &rbBand, sizeof( REBARBANDINFO ) );
		rbBand.cbSize = sizeof( REBARBANDINFO );
		rbBand.fMask = RBBIM_STYLE;

		int nItems = this->getBandCount( );

		if ( input.gettok( 4 ) == "all" ) {

			int i = 0;

			while ( i < nItems ) {

				if ( this->getBandInfo( i, &rbBand ) != 0 ) {

					rbBand.fStyle |= RBBS_NOGRIPPER;
					this->setBandInfo( i, &rbBand );
				}
				i++;
			}
		}
		else {

			int nIndex = input.gettok( 4 ).to_int( ) - 1;

			if ( nIndex > -1 && nIndex < nItems && this->getBandInfo( nIndex, &rbBand ) != 0 ) {

				rbBand.fStyle |= RBBS_NOGRIPPER;
				this->setBandInfo( nIndex, &rbBand );
			}
		}
	}
	// xdid -m [NAME] [ID] [SWITCH] [N]
	else if ( flags['m'] && numtok > 3 ) {

		int nIndex = input.gettok( 4 ).to_int( ) - 1;

		if ( nIndex > -1 && nIndex < this->getBandCount( ) ) {

			this->maxBand( nIndex, FALSE );
		}
	}
	// xdid -n [NAME] [ID] [SWITCH] [N]
	else if ( flags['n'] && numtok > 3 ) {

		int nIndex = input.gettok( 4 ).to_int( ) - 1;

		if ( nIndex > -1 && nIndex < this->getBandCount( ) ) {

			this->minBand( nIndex, FALSE );
		}
	}
	// xdid -q [NAME] [ID] [SWITCH] [N]
	else if ( flags['q'] && numtok > 3 ) {

		int nRows = input.gettok( 4 ).to_int( );

		if ( nRows > -1 ) {

			this->m_iRowLimit = nRows;
		}
	}
	// xdid -t [NAME] [ID] [SWITCH] [N] [TEXT]
	else if ( flags['t'] && numtok > 3 ) {

		REBARBANDINFO rbBand;
		ZeroMemory( &rbBand, sizeof( REBARBANDINFO ) );
		rbBand.cbSize = sizeof( REBARBANDINFO );
		rbBand.fMask = RBBIM_TEXT;

		int nIndex = input.gettok( 4 ).to_int( ) - 1;
		if ( nIndex > -1 && nIndex < this->getBandCount( ) ) {

			TString itemtext;
			if ( numtok > 4 )
				itemtext = input.gettok(5, -1).trim();

			rbBand.lpText = itemtext.to_chr( );
			this->setBandInfo( nIndex, &rbBand );
		}
	}
	// xdid -u [NAME] [ID] [SWITCH] [N|ALL]
	else if ( flags['u'] && numtok > 3 ) {

		REBARBANDINFO rbBand;
		ZeroMemory( &rbBand, sizeof( REBARBANDINFO ) );
		rbBand.cbSize = sizeof( REBARBANDINFO );
		rbBand.fMask = RBBIM_STYLE;

		int nItems = this->getBandCount( );

		if ( input.gettok( 4 ) == "all" ) {

			int i = 0;

			while ( i < nItems ) {

				if ( this->getBandInfo( i, &rbBand ) != 0 ) {

					rbBand.fStyle &= ~RBBS_NOGRIPPER;
					this->setBandInfo( i, &rbBand );
				}
				i++;
			}
		}
		else {

			int nIndex = input.gettok( 4 ).to_int( ) - 1;

			if ( nIndex > -1 && nIndex < nItems && this->getBandInfo( nIndex, &rbBand ) != 0 ) {

				rbBand.fStyle &= ~RBBS_NOGRIPPER;
				this->setBandInfo( nIndex, &rbBand );
			}
		}
	}
	// xdid -v [NAME] [ID] [SWITCH] [NFrom] [NTo]
	else if ( flags['v'] && numtok > 4 ) {

		int nIndexFrom = input.gettok( 4 ).to_int( ) - 1;
		int nIndexTo = input.gettok( 4 ).to_int( ) - 1;
		int nItems = this->getBandCount( );

		if ( nIndexFrom > -1 && nIndexFrom < nItems && nIndexTo > -1 && nIndexTo < nItems ) {

			this->moveBand( nIndexFrom, nIndexTo );
		}
	}
	// xdid -w [NAME] [ID] [SWITCH] [+FLAGS] [INDEX] [FILENAME]
	else if (flags['w'] && numtok > 5) {
		HIMAGELIST himl;
		HICON icon;
		TString flag(input.gettok( 4 ));
		int index = input.gettok( 5 ).to_int();
		TString filename(input.gettok( 6, -1 ));

		if ((himl = this->getImageList()) == NULL) {
			himl = this->createImageList();

			if (himl)
				this->setImageList(himl);
		}

		icon = dcxLoadIcon(index, filename, false, flag);

		//if (flag.find('g', 0))
		//	icon = CreateGrayscaleIcon(icon);

		ImageList_AddIcon(himl, icon);
		DestroyIcon(icon);
	}
	// xdid -y [NAME] [ID] [SWITCH] [+FLAGS]
	else if ( flags['y'] ) {

		ImageList_Destroy( this->getImageList( ) );
	}
	else
		this->parseGlobalCommandRequest( input, flags );
}

/*!
* \brief blah
*
* blah
*/

void DcxReBar::resetContents( ) {

	int nItems = this->getBandCount( );

	while ( nItems-- )
		this->deleteBand( nItems );
}

/*!
* \brief blah
 *
 * blah
 */

UINT DcxReBar::parseBandStyleFlags( const TString & flags ) {

  INT i = 1, len = flags.len( ), iFlags = 0;

  // no +sign, missing params
  if ( flags[0] != '+' ) 
    return iFlags;

  while ( i < len ) {

    if ( flags[i] == 'b' )
      iFlags |= RBBS_BOLD;
    else if ( flags[i] == 'c' )
      iFlags |= RBBS_COLOR;
    else if ( flags[i] == 'e' )
      iFlags |= RBBS_CHILDEDGE;
    else if ( flags[i] == 'f' )
      iFlags |= RBBS_FIXEDSIZE;
    else if ( flags[i] == 'g' )
      iFlags |= RBBS_GRIPPERALWAYS;
    else if ( flags[i] == 'h' )
      iFlags |= RBBS_HIDDEN;
    else if ( flags[i] == 'n' )
      iFlags |= RBBS_NOGRIPPER;
    else if ( flags[i] == 'o' )
      iFlags |= RBBS_USECHEVRON;
    else if ( flags[i] == 'u' )
      iFlags |= RBBS_UNDERLINE;
    else if ( flags[i] == 'v' )
      iFlags |= RBBS_VARIABLEHEIGHT;
    else if ( flags[i] == 'w' )
      iFlags |= RBBS_BREAK;

    ++i;
  }
  return iFlags;
}

/*!
 * \brief blah
 *
 * blah
 */

LRESULT DcxReBar::insertBand(const int uIndex, LPREBARBANDINFO lprbbi ) {
  return SendMessage(this->m_Hwnd, RB_INSERTBAND, (WPARAM) uIndex, (LPARAM) lprbbi ); 
}

/*!
 * \brief blah
 *
 * blah
 */

LRESULT DcxReBar::deleteBand( const UINT uIndex ) {
  return SendMessage( this->m_Hwnd, RB_DELETEBAND, (WPARAM) uIndex, (LPARAM) 0 ); 
}

/*!
 * \brief blah
 *
 * blah
 */

LRESULT DcxReBar::getBandInfo( const UINT uBand, LPREBARBANDINFO lprbbi ) const {
  return SendMessage( this->m_Hwnd, RB_GETBANDINFO, (WPARAM) uBand, (LPARAM) lprbbi ); 
}

/*!
 * \brief blah
 *
 * blah
 */

LRESULT DcxReBar::setBandInfo( const UINT uBand, LPREBARBANDINFO lprbbi ) {
  return SendMessage( this->m_Hwnd, RB_SETBANDINFO, (WPARAM) uBand, (LPARAM) lprbbi ); 
}

/*!
 * \brief blah
 *
 * blah
 */

LRESULT DcxReBar::setBarInfo( LPREBARINFO lprbi ) {
  return SendMessage( this->m_Hwnd, RB_SETBARINFO, (WPARAM) 0, (LPARAM) lprbi ); 
}

/*!
 * \brief blah
 *
 * blah
 */

LRESULT DcxReBar::getBarInfo( LPREBARINFO lprbi ) const {
  return SendMessage( this->m_Hwnd, RB_GETBARINFO, (WPARAM) 0, (LPARAM) lprbi ); 
}

/*!
 * \brief blah
 *
 * blah
 */

LRESULT DcxReBar::getRowCount( ) const {
  return SendMessage( this->m_Hwnd, RB_GETROWCOUNT, (WPARAM) 0, (LPARAM) 0 ); 
}

/*!
 * \brief blah
 *
 * blah
 */

LRESULT DcxReBar::hitTest( LPRBHITTESTINFO lprbht ) {
  return SendMessage( this->m_Hwnd, RB_HITTEST, (WPARAM) 0, (LPARAM) lprbht ); 
}

/*!
 * \brief blah
 *
 * blah
 */

LRESULT DcxReBar::getToolTips( ) const {
  return SendMessage( this->m_Hwnd, RB_GETTOOLTIPS, (WPARAM) 0, (LPARAM) 0 ); 
}

/*!
 * \brief blah
 *
 * blah
 */

LRESULT DcxReBar::setToolTips( const HWND hwndToolTip ) {
  return SendMessage( this->m_Hwnd, RB_SETTOOLTIPS, (WPARAM) hwndToolTip, (LPARAM) 0 ); 
}

/*!
 * \brief blah
 *
 * blah
 */

LRESULT DcxReBar::getIDToIndex( const UINT uBandID ) const {
  return SendMessage( this->m_Hwnd, RB_IDTOINDEX, (WPARAM) uBandID, (LPARAM) 0 );
}

/*!
 * \brief blah
 *
 * blah
 */

LRESULT DcxReBar::getBandCount( ) const {
  return SendMessage( this->m_Hwnd, RB_GETBANDCOUNT, (WPARAM) 0, (LPARAM) 0 );
}

/*!
 * \brief blah
 *
 * blah
 */

LRESULT DcxReBar::setReDraw( const BOOL uState ) {
  return SendMessage( this->m_Hwnd, WM_SETREDRAW, (WPARAM) uState, (LPARAM) uState );
}

/*!
 * \brief blah
 *
 * blah
 */

LRESULT DcxReBar::showBand( const UINT uBand, const BOOL fShow ) {
  return SendMessage( this->m_Hwnd, RB_SHOWBAND, (WPARAM) uBand, (LPARAM) fShow );
}

/*!
 * \brief blah
 *
 * blah
 */

LRESULT DcxReBar::moveBand( const UINT iFrom, const UINT iTo ) {
  return SendMessage( this->m_Hwnd, RB_MOVEBAND, (WPARAM) iFrom, (LPARAM) iTo );
}

/*!
 * \brief blah
 *
 * blah
 */

LRESULT DcxReBar::maxBand( const UINT uBand, const BOOL fIdeal ) {
  return SendMessage( this->m_Hwnd, RB_MAXIMIZEBAND, (WPARAM) uBand, (LPARAM) fIdeal );
}

/*!
 * \brief blah
 *
 * blah
 */

LRESULT DcxReBar::minBand( const UINT uBand, const BOOL fIdeal ) {
  return SendMessage( this->m_Hwnd, RB_MINIMIZEBAND, (WPARAM) uBand, (LPARAM) fIdeal );
}

/*!
 * \brief blah
 *
 * blah
 */
LRESULT DcxReBar::ParentMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bParsed ) {
  switch( uMsg ) {

    case WM_NOTIFY:
      {
        LPNMHDR hdr = (LPNMHDR) lParam;

        if (!hdr)
          break;

					switch( hdr->code ) {
						case NM_CUSTOMDRAW:
							{
								LPNMCUSTOMDRAW lpncd = (LPNMCUSTOMDRAW) lParam;

								bParsed = TRUE;

								switch( lpncd->dwDrawStage ) {
									case CDDS_PREPAINT:
										return (CDRF_NOTIFYPOSTPAINT | CDRF_NOTIFYITEMDRAW);
									case CDDS_ITEMPREPAINT:
										{
											LPDCXRBBAND lpdcxrbb = (LPDCXRBBAND) lpncd->lItemlParam;

											if ( lpdcxrbb == NULL )
												return CDRF_DODEFAULT;

											if ( lpdcxrbb->clrText != -1 )
												SetTextColor( lpncd->hdc, lpdcxrbb->clrText );
										}
										return (CDRF_NOTIFYPOSTPAINT | CDRF_NEWFONT);
									case CDDS_ITEMPOSTPAINT:
										return CDRF_DODEFAULT;
									default:
										return CDRF_DODEFAULT;
								}
							} // NM_CUSTOMDRAW
							break;

						case RBN_HEIGHTCHANGE:
							{
								bParsed = TRUE;
								RECT rc;
								GetWindowRect( this->m_Hwnd, &rc );
								UINT width = rc.right - rc.left;
								UINT height = rc.bottom - rc.top;

								if ( this->m_iWidth != width || this->m_iHeight != height ) {

									this->execAliasEx("%s,%d,%d,%d", "change", this->getUserID( ),
										width, height );

									this->m_iWidth = width;
									this->m_iHeight = height;
								}
							}
							break;

						case RBN_ENDDRAG:
							{
								bParsed = TRUE;
								this->redrawWindow( );
							}
							break;

						case RBN_DELETINGBAND:
							{
								bParsed = TRUE;
	              
								LPNMREBAR lpnmrb = (LPNMREBAR) lParam;

								REBARBANDINFO rbBand;
								ZeroMemory( &rbBand, sizeof( REBARBANDINFO ) );
								rbBand.cbSize = sizeof( REBARBANDINFO );
								rbBand.fMask = RBBIM_CHILD;

								if ( this->getBandInfo( lpnmrb->uBand, &rbBand ) != 0 ) {

									if ( IsWindow( rbBand.hwndChild ) ) {

										DcxControl * p_delControl = this->m_pParentDialog->getControlByHWND( rbBand.hwndChild );
										this->m_pParentDialog->deleteControl( p_delControl );
									}

									LPDCXRBBAND lpdcxrbb = (LPDCXRBBAND) lpnmrb->lParam;
									if ( lpdcxrbb != NULL )
										delete lpdcxrbb;
								}
							}
							break;
						} // switch
      }
      break;
	}

	return 0L;
}

LRESULT DcxReBar::PostMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bParsed ) {

	LRESULT lRes = 0L;
  switch( uMsg ) {

    case WM_NOTIFY:
      {
        LPNMHDR hdr = (LPNMHDR) lParam;

        if (!hdr)
          break;

				if (IsWindow(hdr->hwndFrom)) {
					DcxControl *c_this = (DcxControl *) GetProp(hdr->hwndFrom,"dcx_cthis");
					if (c_this != NULL) {
						lRes = c_this->ParentMessage(uMsg, wParam, lParam, bParsed);
					}
				}
      }
      break;

    case WM_HSCROLL:
    case WM_VSCROLL:
    case WM_COMMAND:
      {
				if (IsWindow((HWND) lParam)) {
					DcxControl *c_this = (DcxControl *) GetProp((HWND) lParam,"dcx_cthis");
					if (c_this != NULL) {
						lRes = c_this->ParentMessage(uMsg, wParam, lParam, bParsed);
					}
				}
      }
      break;

    case WM_DELETEITEM:
      {
				DELETEITEMSTRUCT *idata = (DELETEITEMSTRUCT *)lParam;
				if ((idata != NULL) && (IsWindow(idata->hwndItem))) {
					DcxControl *c_this = (DcxControl *) GetProp(idata->hwndItem,"dcx_cthis");
					if (c_this != NULL) {
						lRes = c_this->ParentMessage(uMsg, wParam, lParam, bParsed);
					}
				}
      }
      break;

    case WM_MEASUREITEM:
      {
				HWND cHwnd = GetDlgItem(this->m_Hwnd, wParam);
				if (IsWindow(cHwnd)) {
					DcxControl *c_this = (DcxControl *) GetProp(cHwnd,"dcx_cthis");
					if (c_this != NULL) {
						lRes = c_this->ParentMessage(uMsg, wParam, lParam, bParsed);
					}
				}
      }
      break;

    case WM_DRAWITEM:
      {
				DRAWITEMSTRUCT *idata = (DRAWITEMSTRUCT *)lParam;
				if ((idata != NULL) && (IsWindow(idata->hwndItem))) {
					DcxControl *c_this = (DcxControl *) GetProp(idata->hwndItem,"dcx_cthis");
					if (c_this != NULL) {
						lRes = c_this->ParentMessage(uMsg, wParam, lParam, bParsed);
					}
				}
      }
     break;

    case WM_LBUTTONUP:
      {
		  RBHITTESTINFO rbhi = {0};
		  GetCursorPos( &rbhi.pt );
		  MapWindowPoints(NULL, this->m_Hwnd, &rbhi.pt, 1 );
		  int band = this->hitTest( &rbhi );

		  if ( ( rbhi.flags & RBHT_GRABBER || rbhi.flags & RBHT_CAPTION ) && band != -1 ) {

			  this->m_iClickedBand = band;

			  if (this->m_pParentDialog->getEventMask() & DCX_EVENT_CLICK)
				  this->execAliasEx("%s,%d,%d", "sclick", this->getUserID( ), band + 1 );
		  }
      }
      break;

    case WM_CONTEXTMENU:
      {
		  if (this->m_pParentDialog->getEventMask() & DCX_EVENT_CLICK) {
			  RBHITTESTINFO rbhi;
			  GetCursorPos( &rbhi.pt );
			  MapWindowPoints(NULL, this->m_Hwnd, &rbhi.pt, 1 );
			  int band = this->hitTest( &rbhi );

			  if ( band != -1 )
				  this->execAliasEx("%s,%d,%d", "rclick", this->getUserID( ), band + 1 );
		  }
      }
      break;

    case WM_SIZE:
      {
        InvalidateRect( this->m_Hwnd, NULL, TRUE );
      }
      break;

    case WM_DESTROY:
      {
        delete this;
        bParsed = TRUE;
      }
      break;

    default:
			lRes = this->CommonMessage( uMsg, wParam, lParam, bParsed);
      break;
  }

  return lRes;
}
