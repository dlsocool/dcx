/*!
 * \file xpopupmenu.cpp
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
#include "Classes/xpopup/xpopupmenu.h"
#include "Classes/xpopup/xmenubar.h"
#include "Dcx.h"



/*!
 * \brief Constructor
 *
 * blah
 */


XPopupMenu::XPopupMenu( const TString & tsMenuName, MenuStyle mStyle )
: m_tsMenuName( tsMenuName ), m_MenuStyle( mStyle ), m_MenuItemStyles(0), m_hImageList(NULL),
m_hBitmap(NULL), m_bRoundedSel(false), m_uiAlpha(255), m_bAttachedToMenuBar(false)
{

	this->m_hMenu = CreatePopupMenu( );

	this->m_MenuColors.m_clrBack = RGB( 255, 255, 255 );
	this->m_MenuColors.m_clrBox =  RGB( 184, 199, 146 );
	this->m_MenuColors.m_clrCheckBox = RGB( 255, 128, 0 );
	this->m_MenuColors.m_clrDisabledCheckBox = RGB( 200, 200, 200 );
	this->m_MenuColors.m_clrDisabledSelection = RGB( 255, 255, 255 );
	this->m_MenuColors.m_clrDisabledText = RGB( 128, 128, 128 );
	this->m_MenuColors.m_clrSelection = RGB( 255, 229, 179 );
	this->m_MenuColors.m_clrSelectionBorder = RGB( 0, 0, 0 );
	this->m_MenuColors.m_clrSeparatorLine = RGB( 128, 128, 128 );
	this->m_MenuColors.m_clrText = RGB( 0, 0, 0 );
	this->m_MenuColors.m_clrSelectedText = RGB( 0, 0, 0 );
}

/*!
 * \brief Constructor
 *
 * Default constructor for testing
 */

XPopupMenu::XPopupMenu(const TString tsName, HMENU hMenu )
: m_hMenu(hMenu), m_MenuItemStyles(0), m_MenuStyle(XPMS_OFFICE2003), m_hImageList(NULL), m_hBitmap(NULL)
, m_tsMenuName(tsName), m_bRoundedSel(false), m_uiAlpha(255), m_bAttachedToMenuBar(false)
{
	this->m_MenuColors.m_clrBack = RGB( 255, 255, 255 );
	this->m_MenuColors.m_clrBox =  RGB( 184, 199, 146 );
	this->m_MenuColors.m_clrCheckBox = RGB( 255, 128, 0 );
	this->m_MenuColors.m_clrDisabledCheckBox = RGB( 200, 200, 200 );
	this->m_MenuColors.m_clrDisabledSelection = RGB( 255, 255, 255 );
	this->m_MenuColors.m_clrDisabledText = RGB( 128, 128, 128 );
	this->m_MenuColors.m_clrSelection = RGB( 255, 229, 179 );
	this->m_MenuColors.m_clrSelectionBorder = RGB( 0, 0, 0 );
	this->m_MenuColors.m_clrSeparatorLine = RGB( 128, 128, 128 );
	this->m_MenuColors.m_clrText = RGB( 0, 0, 0 );
	this->m_MenuColors.m_clrSelectedText = RGB( 0, 0, 0 );

	/*

	XPopupMenuItem * p_Item = NULL;
	TString itemtext = "";

	// 
	this->m_hMenu = CreatePopupMenu( );
	MENUITEMINFO mii;
	ZeroMemory( &mii, sizeof( MENUITEMINFO ) );
	mii.cbSize = sizeof( MENUITEMINFO );

	mii.fMask = MIIM_DATA | MIIM_FTYPE;
	mii.fType = MFT_OWNERDRAW;
	itemtext = "Menu Item 1";
	p_Item = new XPopupMenuItem( this, itemtext, 0, FALSE );
	this->m_vpMenuItem.push_back( p_Item );
	mii.dwItemData = (ULONG_PTR) p_Item;
	InsertMenuItem( this->m_hMenu, 1, TRUE, &mii );

	mii.fMask = MIIM_SUBMENU | MIIM_DATA | MIIM_FTYPE | MIIM_STATE;
	mii.fType = MFT_OWNERDRAW;
	HMENU hMenu = CreatePopupMenu( );
	itemtext = "Menu Item 2";
	mii.hSubMenu = hMenu;
	p_Item = new XPopupMenuItem( this, itemtext, 0, TRUE );
	this->m_vpMenuItem.push_back( p_Item );
	mii.dwItemData = (ULONG_PTR) p_Item;
	InsertMenuItem( this->m_hMenu, 2, TRUE, &mii );

	mii.fMask = MIIM_DATA | MIIM_FTYPE | MIIM_STATE;
	mii.fType = MFT_OWNERDRAW;
	itemtext = "Menu Item 2 1";
	p_Item = new XPopupMenuItem( this, itemtext, 0, FALSE );
	this->m_vpMenuItem.push_back( p_Item );
	mii.dwItemData = (ULONG_PTR) p_Item;
	InsertMenuItem( hMenu, 1, TRUE, &mii );

	mii.fMask = MIIM_DATA | MIIM_FTYPE | MIIM_STATE;
	mii.fType = MFT_SEPARATOR | MFT_OWNERDRAW;
	p_Item = new XPopupMenuItem( this, TRUE );
	this->m_vpMenuItem.push_back( p_Item );
	mii.dwItemData = (ULONG_PTR) p_Item;
	InsertMenuItem( hMenu, 2, TRUE, &mii );

	mii.fMask = MIIM_DATA | MIIM_FTYPE | MIIM_STATE;
	mii.fType = MFT_OWNERDRAW;
	itemtext = "Menu Item 2 3";
	mii.fState = MFS_CHECKED;
	p_Item = new XPopupMenuItem( this, itemtext, 0, FALSE );
	this->m_vpMenuItem.push_back( p_Item );
	mii.dwItemData = (ULONG_PTR) p_Item;
	InsertMenuItem( hMenu, 2, TRUE, &mii );

	mii.fMask = MIIM_DATA | MIIM_FTYPE | MIIM_STATE;
	mii.fType = MFT_SEPARATOR | MFT_OWNERDRAW;
	mii.fState = 0;
	p_Item = new XPopupMenuItem( this, TRUE );
	this->m_vpMenuItem.push_back( p_Item );
	mii.dwItemData = (ULONG_PTR) p_Item;
	InsertMenuItem( this->m_hMenu, 3, TRUE, &mii );

	mii.fMask = MIIM_DATA | MIIM_FTYPE | MIIM_STATE;
	mii.fType = MFT_OWNERDRAW;
	itemtext = "Menu Item 4";
	mii.fState = 0;
	p_Item = new XPopupMenuItem( this, itemtext, 0, FALSE );
	this->m_vpMenuItem.push_back( p_Item );
	mii.dwItemData = (ULONG_PTR) p_Item;
	InsertMenuItem( this->m_hMenu, 4, TRUE, &mii );

	mii.fMask = MIIM_DATA | MIIM_FTYPE | MIIM_STATE;
	mii.fType = MFT_OWNERDRAW;
	mii.fState = MFS_CHECKED;
	itemtext = "Menu Item 5";
	p_Item = new XPopupMenuItem( this, itemtext, 0, FALSE );
	this->m_vpMenuItem.push_back( p_Item );
	mii.dwItemData = (ULONG_PTR) p_Item;
	InsertMenuItem( this->m_hMenu, 5, TRUE, &mii );

	mii.fMask = MIIM_DATA | MIIM_FTYPE | MIIM_STATE;
	mii.fType = MFT_OWNERDRAW;
	mii.fState = MFS_CHECKED | MFS_DISABLED;
	itemtext = "Menu Item 6";
	p_Item = new XPopupMenuItem( this, itemtext, 0, FALSE );
	this->m_vpMenuItem.push_back( p_Item );
	mii.dwItemData = (ULONG_PTR) p_Item;
	InsertMenuItem( this->m_hMenu, 6, TRUE, &mii );

	mii.fMask = MIIM_DATA | MIIM_FTYPE | MIIM_STATE;
	mii.fType = MFT_OWNERDRAW;
	mii.fState = MFS_DISABLED;
	itemtext = "Menu Item 7";
	p_Item = new XPopupMenuItem( this, itemtext, 0, FALSE );
	this->m_vpMenuItem.push_back( p_Item );
	mii.dwItemData = (ULONG_PTR) p_Item;
	InsertMenuItem( this->m_hMenu, 7, TRUE, &mii );
	*/
}

/*!
 * \brief Destructor
 *
 * blah
 */

XPopupMenu::~XPopupMenu( ) {
	if (this->m_bAttachedToMenuBar)
		this->detachFromMenuBar(NULL);

	this->clearAllMenuItems( );

	if ( this->m_hBitmap != NULL )
		DeleteBitmap( this->m_hBitmap );

	if ( this->m_hMenu != NULL && this->m_tsMenuName != "mircbar" && this->m_tsMenuName != "dialog")
		DestroyMenu( this->m_hMenu );
}

/*!
 * \brief blah
 *
 * blah
 */

void XPopupMenu::parseXPopCommand( const TString & input ) {
	const XSwitchFlags flags(input.gettok(2));
	const TString path(input.gettok(1, TSTAB).gettok(3, -1).trim());

	HMENU hMenu;
	if ( path.numtok( ) == 1 )
		hMenu = this->m_hMenu;
	else {
		hMenu = this->parsePath( path.gettok( 1, path.numtok( ) - 1 ), this->m_hMenu );

		if ( hMenu == NULL ) {
			Dcx::error("/xpop","Invalid Menu Item Path" );
			return;
		}
	}

	const UINT numtok = input.numtok( );

	// xpop -a - [MENU] [SWITCH] [PATH] [TAB] [+FLAGS] [ID] [ICON] ItemText (: Command)
	if ( flags['a'] && input.numtok( TSTAB ) > 1 && input.gettok( 2, TSTAB ).numtok( ) > 3 ) {
		const TString itemdata(input.gettok( 2, -1, TSTAB ).trim());
		TString itemcom;

		if ( input.numtok(":") > 1 )
			itemcom = input.gettok(2, ":").trim();

		int nPos = path.gettok( path.numtok( ) ).to_int( ) - 1;
		const int mID = itemdata.gettok( 2 ).to_int( );
		const int nIcon = itemdata.gettok( 3 ).to_int( ) - 1;

		const XSwitchFlags xflag(itemdata.gettok( 1 ));
		const TString itemtext(itemdata.gettok( 4, -1 ));

		if ( nPos == -1 )
			nPos += GetMenuItemCount( hMenu ) + 1;

		MENUITEMINFO mii;
		ZeroMemory( &mii, sizeof( MENUITEMINFO ) );
		mii.cbSize = sizeof( MENUITEMINFO );

		XPopupMenuItem * p_Item = NULL;

		if ( itemtext == "-" ) {
			mii.fMask = MIIM_DATA | MIIM_FTYPE | MIIM_STATE;
			mii.fType = MFT_OWNERDRAW | MFT_SEPARATOR;

			p_Item = new XPopupMenuItem( this, TRUE );
		}
		else {
			mii.fMask = MIIM_DATA | MIIM_FTYPE | MIIM_STATE | MIIM_ID;
			mii.fType = MFT_OWNERDRAW;
			mii.wID = mID;

			if ( xflag['+'] ) {
				// submenu
				if ( xflag['s'] ) {
					mii.fMask |= MIIM_SUBMENU;
					if ( mii.hSubMenu != NULL )
						DestroyMenu( mii.hSubMenu );

					mii.hSubMenu = CreatePopupMenu( );
				}
				if ( xflag['c'] )
					mii.fState |= MFS_CHECKED;
				if ( xflag['g'] )
					mii.fState |= MFS_GRAYED;
			}
			p_Item = new XPopupMenuItem( this, itemtext, nIcon, mii.hSubMenu!=NULL?TRUE:FALSE );
		}

		this->m_vpMenuItem.push_back( p_Item );
		mii.dwItemData = (ULONG_PTR) p_Item;
		InsertMenuItem( hMenu, nPos, TRUE, &mii );
	}
	// xpop -c - [MENU] [SWITCH] [PATH]
	else if ( flags['c'] && numtok > 2 ) {
		const int nPos = path.gettok( path.numtok( ) ).to_int( ) - 1;
		if ( nPos > -1 ) {
			MENUITEMINFO mii;
			ZeroMemory( &mii, sizeof( MENUITEMINFO ) );
			mii.cbSize = sizeof( MENUITEMINFO );
			mii.fMask = MIIM_SUBMENU | MIIM_DATA;

			GetMenuItemInfo( hMenu, nPos, TRUE, &mii );

			if ( mii.hSubMenu != NULL ) {
				this->deleteAllItemData( mii.hSubMenu );
				DestroyMenu( mii.hSubMenu );
			}

			mii.hSubMenu = CreatePopupMenu( );

			XPopupMenuItem * p_Item = (XPopupMenuItem *) mii.dwItemData;
			if ( p_Item != NULL )
				p_Item->setSubMenu( TRUE );

			mii.fMask = MIIM_SUBMENU;

			SetMenuItemInfo( hMenu, nPos, TRUE, &mii );
		}
	}
	// xpop -d - [MENU] [SWITCH] [PATH]
	else if ( flags['d'] && numtok > 2 ) {

		const int nPos = path.gettok( path.numtok( ) ).to_int( ) - 1;
		if ( nPos > -1 ) {

			MENUITEMINFO mii;
			ZeroMemory( &mii, sizeof( MENUITEMINFO ) );
			mii.cbSize = sizeof( MENUITEMINFO );
			mii.fMask = MIIM_SUBMENU | MIIM_DATA;

			GetMenuItemInfo( hMenu, nPos, TRUE, &mii );

			if ( mii.hSubMenu != NULL ) {
				this->deleteAllItemData( mii.hSubMenu );
				DestroyMenu( mii.hSubMenu );
			}

			XPopupMenuItem * p_Item = (XPopupMenuItem *) mii.dwItemData;
			if ( p_Item != NULL )
				p_Item->setSubMenu( FALSE );

			mii.hSubMenu = NULL;
			mii.fMask = MIIM_SUBMENU;

			SetMenuItemInfo( hMenu, nPos, TRUE, &mii );
		}
	}
	// xpop -f - [MENU] [SWITCH] [PATH]
	else if ( flags['f'] && numtok > 2 ) {

		const int nPos = path.gettok( path.numtok( ) ).to_int( ) - 1;
		if ( nPos > -1 ) {

			MENUITEMINFO mii;
			ZeroMemory( &mii, sizeof( MENUITEMINFO ) );
			mii.cbSize = sizeof( MENUITEMINFO );
			mii.fMask = MIIM_SUBMENU | MIIM_DATA;

			GetMenuItemInfo( hMenu, nPos, TRUE, &mii );

			if ( mii.hSubMenu != NULL ) {
				this->deleteAllItemData( mii.hSubMenu );
				DestroyMenu( mii.hSubMenu );
			}

			XPopupMenuItem * p_Item = (XPopupMenuItem *) mii.dwItemData;
			if ( p_Item != NULL )
				this->deleteMenuItemData( p_Item, NULL );

			DeleteMenu( hMenu, nPos, MF_BYPOSITION );
		}
	}
	// xpop -i - [MENU] [SWITCH] [PATH] [TAB] [ICON]
	else if ( flags['i'] && input.numtok( TSTAB ) > 1 && input.gettok( 2, TSTAB ).numtok( ) > 0 ) {

		const int nPos = path.gettok( path.numtok( ) ).to_int( ) - 1;
		const int nIcon = input.gettok( 2, TSTAB ).to_int( );

		if ( nPos > -1 ) {

			MENUITEMINFO mii;
			ZeroMemory( &mii, sizeof( MENUITEMINFO ) );
			mii.cbSize = sizeof( MENUITEMINFO );
			mii.fMask = MIIM_DATA;

			GetMenuItemInfo( hMenu, nPos, TRUE, &mii );

			XPopupMenuItem * p_Item = (XPopupMenuItem *) mii.dwItemData;
			if ( p_Item != NULL )
				p_Item->setItemIcon( nIcon );
		}
	}
	// xpop -s - [MENU] [SWITCH] [PATH] [TAB] [+FLAGS]
	else if ( flags['s'] && input.numtok( TSTAB ) > 1 && input.gettok( 2, TSTAB ).numtok( ) > 0 ) {

		const int nPos = path.gettok( path.numtok( ) ).to_int( ) - 1;
		const XSwitchFlags xflags(input.gettok(2, TSTAB).trim());

		if ( nPos > -1 ) {
			MENUITEMINFO mii;
			ZeroMemory( &mii, sizeof( MENUITEMINFO ) );
			mii.cbSize = sizeof( MENUITEMINFO );
			mii.fMask = MIIM_STATE;

			if ( xflags['+'] ) {
				if ( xflags['c'] )
					mii.fState |= MFS_CHECKED;
				else if ( xflags['g'] )
					mii.fState |= MFS_GRAYED;
			}

			SetMenuItemInfo( hMenu, nPos, TRUE, &mii );
		}
	}
	// xpop -t - [MENU] [SWITCH] [PATH] [TAB] Itemtext
	else if ( flags['t'] && input.numtok( TSTAB ) > 1 && input.gettok( 2, TSTAB ).numtok( ) > 0 ) {
		const int nPos = path.gettok( path.numtok( ) ).to_int( ) - 1;
		const TString itemtext(input.gettok(2, TSTAB).trim());

		if ( nPos > -1 ) {
			MENUITEMINFO mii;
			ZeroMemory( &mii, sizeof( MENUITEMINFO ) );
			mii.cbSize = sizeof( MENUITEMINFO );
			mii.fMask = MIIM_DATA | MIIM_STATE | MIIM_SUBMENU | MIIM_FTYPE | MIIM_ID;

			GetMenuItemInfo( hMenu, nPos, TRUE, &mii );

			XPopupMenuItem * p_Item = (XPopupMenuItem *) mii.dwItemData;
			if ( p_Item != NULL )
				p_Item->setItemText( itemtext );

			// this is to make sure system resets the measurement of the itemwidth on next display
			DeleteMenu( hMenu, nPos, MF_BYPOSITION );
			InsertMenuItem( hMenu, nPos, TRUE, &mii );
		}
	}
}

/*!
 * \brief blah
 *
 * blah
 */

void XPopupMenu::parseXPopIdentifier( const TString & input, char * szReturnValue ) {

  const int numtok = input.numtok( );
  const TString prop(input.gettok( 2 ));

  // [NAME] [ID] [PROP] [PATH]
  if ( prop == "num" && numtok > 2 ) {

    const TString path(input.gettok( 3, -1 ));

    HMENU hMenu;
    if ( path == "root" )
      hMenu = this->m_hMenu;
    else
      hMenu = this->parsePath( path, this->m_hMenu );

    if ( hMenu != NULL ) {
      wnsprintf( szReturnValue, MIRC_BUFFER_SIZE_CCH, "%d", GetMenuItemCount( hMenu ) );
      return;
    }
  }
  else if ( ( prop == "text" || prop == "icon" ) && numtok > 2 ) {

    const TString path(input.gettok( 3, -1 ));

    HMENU hMenu;
      
    if ( path.numtok( ) == 1 )
      hMenu = this->m_hMenu;
    else
      hMenu = this->parsePath( path.gettok( 1, path.numtok( ) - 1 ), this->m_hMenu );

    const int nPos = path.gettok( path.numtok( ) ).to_int( ) - 1;

    if ( hMenu != NULL ) {

      MENUITEMINFO mii;
      ZeroMemory( &mii, sizeof( MENUITEMINFO ) );
      mii.cbSize = sizeof( MENUITEMINFO );
      mii.fMask = MIIM_DATA;

      if ( GetMenuItemInfo( hMenu, nPos, TRUE, &mii ) == TRUE ) {

        XPopupMenuItem * p_Item = (XPopupMenuItem *) mii.dwItemData;
        if ( p_Item != NULL ) {

          if ( prop == "text" ) 
            lstrcpy( szReturnValue, p_Item->getItemText( )->to_chr( ) );
          else if ( prop == "icon" )
            wnsprintf( szReturnValue, MIRC_BUFFER_SIZE_CCH, "%d", p_Item->getItemIcon( ) + 1 );
          return;
        }
      }
    }
  }
  else if ( ( prop == "checked" || prop == "enabled" ) && numtok > 2 ) {

    const TString path(input.gettok( 3, -1 ));

    HMENU hMenu;
      
    if ( path.numtok( ) == 1 )
      hMenu = this->m_hMenu;
    else
      hMenu = this->parsePath( path.gettok( 1, path.numtok( ) - 1 ), this->m_hMenu );

    const int nPos = path.gettok( path.numtok( ) ).to_int( ) - 1;

    if ( hMenu != NULL ) {

      MENUITEMINFO mii;
      ZeroMemory( &mii, sizeof( MENUITEMINFO ) );
      mii.cbSize = sizeof( MENUITEMINFO );
      mii.fMask = MIIM_STATE;

      if ( GetMenuItemInfo( hMenu, nPos, TRUE, &mii ) == TRUE ) {

        if ( prop == "checked" ) 
          lstrcpy( szReturnValue, mii.fState & MFS_CHECKED?"$true":"$false" );
        else if ( prop == "enabled" )
          lstrcpy( szReturnValue, !(mii.fState & MFS_GRAYED)?"$true":"$false" );
        return;
      }
    }
  }
  else if ( prop == "submenu" && numtok > 2 ) {

    const TString path(input.gettok( 3, -1 ));

    HMENU hMenu;
      
    if ( path.numtok( ) == 1 )
      hMenu = this->m_hMenu;
    else
      hMenu = this->parsePath( path.gettok( 1, path.numtok( ) - 1 ), this->m_hMenu );

    const int nPos = path.gettok( path.numtok( ) ).to_int( ) - 1;

    if ( hMenu != NULL ) {

      MENUITEMINFO mii;
      ZeroMemory( &mii, sizeof( MENUITEMINFO ) );
      mii.cbSize = sizeof( MENUITEMINFO );
      mii.fMask = MIIM_SUBMENU;

      if ( GetMenuItemInfo( hMenu, nPos, TRUE, &mii ) == TRUE ) {

        if ( mii.hSubMenu == NULL )
          lstrcpy( szReturnValue, "0" );
        else
          lstrcpy( szReturnValue, "1" );

        return;
      }
    }
  }

  szReturnValue[0] = 0;
}

/*!
 * \brief blah
 *
 * blah
 */

HIMAGELIST XPopupMenu::getImageList( ) {

  if ( this->m_hImageList == NULL )
    this->m_hImageList = ImageList_Create( 16, 16, ILC_COLOR32|ILC_MASK, 1, 0 );

  return this->m_hImageList;
}

/*!
 * \brief blah
 *
 * blah
 */

void XPopupMenu::destroyImageList( ) {

  if ( this->m_hImageList != NULL )
    ImageList_Destroy( this->m_hImageList );

  this->m_hImageList = NULL;
}

/*!
 * \brief blah
 *
 * blah
 */

XPopupMenu::MenuStyle XPopupMenu::getStyle( ) const {

  return this->m_MenuStyle;
}

/*!
 * \brief blah
 *
 * blah
 */

void XPopupMenu::setStyle( MenuStyle style ) {

  this->m_MenuStyle = style;
}

/*!
 * \brief blah
 *
 * blah
 */

UINT XPopupMenu::getItemStyle( ) const {

  return this->m_MenuItemStyles;
}

/*!
 * \brief blah
 *
 * blah
 */

void XPopupMenu::setItemStyle( const UINT iExStyles ) {

  this->m_MenuItemStyles = iExStyles;
}

/*!
 * \brief blah
 *
 * blah
 */

const TString &XPopupMenu::getName( ) const {

  return this->m_tsMenuName;
}

/*!
 * \brief blah
 *
 * blah
 */

LPXPMENUCOLORS XPopupMenu::getColors( ) const {

  return (LPXPMENUCOLORS) &m_MenuColors;
}

/*!
 * \brief blah
 *
 * blah
 */

void XPopupMenu::setColor( const int nColor, const COLORREF clrColor ) {

  switch ( nColor ) {

    case XPMC_BACKGROUND:
      this->m_MenuColors.m_clrBack = clrColor;
      break;

    case XPMC_ICONBOX:
      this->m_MenuColors.m_clrBox = clrColor;
      break;

    case XPMC_CHECKBOX:
      this->m_MenuColors.m_clrCheckBox = clrColor;
      break;

    case XPMC_CHECKBOX_DISABLED:
      this->m_MenuColors.m_clrDisabledCheckBox = clrColor;
      break;

    case XPMC_SELECTIONBOX_DISABLED:
      this->m_MenuColors.m_clrDisabledSelection = clrColor;
      break;

    case XPMC_TEXT_DISABLED:
      this->m_MenuColors.m_clrDisabledText = clrColor;
      break;

    case XPMC_SELECTIONBOX:
      this->m_MenuColors.m_clrSelection = clrColor;
      break;

    case XPMC_SELECTIONBOX_BORDER:
      this->m_MenuColors.m_clrSelectionBorder = clrColor;
      break;

    case XPMC_SEPARATOR:
      this->m_MenuColors.m_clrSeparatorLine = clrColor;
      break;

    case XPMC_TEXT:
      this->m_MenuColors.m_clrText = clrColor;
      break;

    case XPMC_SELECTEDTEXT:
      this->m_MenuColors.m_clrSelectedText = clrColor;
      break;

    default:
      break;
  }
}

/*!
 * \brief blah
 *
 * blah
 */

COLORREF XPopupMenu::getColor(const int nColor ) const {

	switch ( nColor ) {

	case XPMC_BACKGROUND:
		return this->m_MenuColors.m_clrBack;

	case XPMC_ICONBOX:
		return this->m_MenuColors.m_clrBox;

	case XPMC_CHECKBOX:
		return this->m_MenuColors.m_clrCheckBox;

	case XPMC_CHECKBOX_DISABLED:
		return this->m_MenuColors.m_clrDisabledCheckBox;

	case XPMC_SELECTIONBOX_DISABLED:
		return this->m_MenuColors.m_clrDisabledSelection;

	case XPMC_TEXT_DISABLED:
		return this->m_MenuColors.m_clrDisabledText;

	case XPMC_SELECTIONBOX:
		return this->m_MenuColors.m_clrSelection;

	case XPMC_SELECTIONBOX_BORDER:
		return this->m_MenuColors.m_clrSelectionBorder;

	case XPMC_SEPARATOR:
		return this->m_MenuColors.m_clrSeparatorLine;

	case XPMC_TEXT:
		return this->m_MenuColors.m_clrText;

	case XPMC_SELECTEDTEXT:
		return this->m_MenuColors.m_clrSelectedText;

	default:
		return 0;
	}
}

void XPopupMenu::setDefaultColor(const int nColor ) {

	switch ( nColor ) {

		case XPMC_BACKGROUND:
			this->m_MenuColors.m_clrBack = RGB( 255, 255, 255 );
			break;

		case XPMC_ICONBOX:
			this->m_MenuColors.m_clrBox = RGB( 184, 199, 146 );
			break;

		case XPMC_CHECKBOX:
			this->m_MenuColors.m_clrCheckBox = RGB( 255, 128, 0 );
			break;

		case XPMC_CHECKBOX_DISABLED:
			this->m_MenuColors.m_clrDisabledCheckBox = RGB( 200, 200, 200 );
			break;

		case XPMC_SELECTIONBOX_DISABLED:
			this->m_MenuColors.m_clrDisabledSelection = RGB( 255, 255, 255 );
			break;

		case XPMC_TEXT_DISABLED:
			this->m_MenuColors.m_clrDisabledText = RGB( 128, 128, 128 );
			break;

		case XPMC_SELECTIONBOX:
			this->m_MenuColors.m_clrSelection = RGB( 255, 229, 179 );
			break;

		case XPMC_SELECTIONBOX_BORDER:
			this->m_MenuColors.m_clrSelectionBorder = RGB( 0, 0, 0 );
			break;

		case XPMC_SEPARATOR:
			this->m_MenuColors.m_clrSeparatorLine = RGB( 128, 128, 128 );
			break;

		case XPMC_TEXT:
			this->m_MenuColors.m_clrText = RGB( 0, 0, 0 );
			break;

		case XPMC_SELECTEDTEXT:
			this->m_MenuColors.m_clrSelectedText = RGB( 0, 0, 0 );
			break;

		default:
			break;
	}
}

/*!
 * \brief blah
 *
 * blah
 */

HMENU XPopupMenu::parsePath( const TString & path, const HMENU hParent, const unsigned int depth ) {

  const int iItem = path.gettok( depth ).to_int( ) - 1;

  if ( depth == path.numtok( ) )
    return GetSubMenu( hParent, iItem );
  else if ( GetSubMenu( hParent, iItem ) != NULL )
    return XPopupMenu::parsePath( path, GetSubMenu( hParent, iItem ), depth + 1 );

  return NULL;
}

/*!
 * \brief blah
 *
 * blah
 */

void XPopupMenu::deleteMenuItemData( XPopupMenuItem * p_Item, LPMENUITEMINFO mii ) {

  VectorOfXPopupMenuItem::iterator itStart = this->m_vpMenuItem.begin( );
  VectorOfXPopupMenuItem::iterator itEnd = this->m_vpMenuItem.end( );

  while ( itStart != itEnd ) {

    if ( *itStart == p_Item ) {
      if (mii != NULL)
		mii->dwItemData = (*itStart)->getItemDataBackup();
      delete *itStart;
      this->m_vpMenuItem.erase( itStart );
      return;
    }

    ++itStart;
  }
}

/*!
 * \brief blah
 *
 * blah
 */

void XPopupMenu::deleteAllItemData( HMENU hMenu ) {

	//mIRCError( "Deleting Data" );
	MENUITEMINFO mii;
	ZeroMemory( &mii, sizeof( MENUITEMINFO ) );
	mii.cbSize = sizeof( MENUITEMINFO );
	mii.fMask = MIIM_SUBMENU | MIIM_DATA;

	const int n = GetMenuItemCount( hMenu );

	for (int i = 0; i < n; i++ )
	{

		if ( GetMenuItemInfo( hMenu, i, TRUE, &mii ) == TRUE ) {

			XPopupMenuItem * p_Item = (XPopupMenuItem *) mii.dwItemData;
			if ( p_Item != NULL ) {
				// load the old dwItemData value back to make mIRC happy
				this->deleteMenuItemData( p_Item, &mii );
				mii.fMask = MIIM_DATA;
				SetMenuItemInfo(hMenu, i, TRUE, &mii);
			}

			if ( mii.hSubMenu != NULL )
				this->deleteAllItemData( mii.hSubMenu );

		}
	}
}

/*!
 * \brief blah
 *
 * blah
 */

LRESULT CALLBACK XPopupMenu::XPopupWinProc( HWND mHwnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {

	switch ( uMsg )
	{
//#if DCX_DEBUG_OUTPUT
//	case WM_INITMENU:
//		{
//			TString msg;
//			msg.sprintf("called: %d", mHwnd);
//			Dcx::debug("WM_INITMENU",msg.to_chr());
//		}
//		break;
//	case WM_INITMENUPOPUP:
//		{
//			TString msg;
//			msg.sprintf("called: %d", mHwnd);
//			Dcx::debug("WM_INITMENUPOPUP",msg.to_chr());
//		}
//		break;
//	case WM_PARENTNOTIFY:
//		{
//			TString msg;
//			msg.sprintf("called: %d", mHwnd);
//			Dcx::debug("WM_PARENTNOTIFY",msg.to_chr());
//		}
//		break;
//#endif
	case WM_MEASUREITEM:
		{
			LPMEASUREITEMSTRUCT lpms = (LPMEASUREITEMSTRUCT) lParam;
			if ( lpms->CtlType == ODT_MENU ) {
				OnMeasureItem( mHwnd, lpms );
				return TRUE; 
			}
		}
		break;

	case WM_DRAWITEM:
		{
			LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam;
			if ( lpdis->CtlType == ODT_MENU ) {
				OnDrawItem( mHwnd, lpdis ); 
				return TRUE; 
			}
		}
		break;
	}

	return DefWindowProc( mHwnd, uMsg, wParam, lParam );
}

/*!
 * \brief blah
 *
 * blah
 */

LRESULT XPopupMenu::OnMeasureItem( const HWND mHwnd, LPMEASUREITEMSTRUCT lpmis )
{
	XPopupMenuItem * p_Item = (XPopupMenuItem *) lpmis->itemData;

	if ( p_Item != NULL ) {
		const SIZE size = p_Item->getItemSize( mHwnd );
		lpmis->itemWidth = size.cx;
		lpmis->itemHeight = size.cy;
	}

	return TRUE;
}

/*!
 * \brief blah
 *
 * blah
 */

LRESULT XPopupMenu::OnDrawItem( const HWND mHwnd, LPDRAWITEMSTRUCT lpdis )
{
	XPopupMenuItem * p_Item = (XPopupMenuItem *) lpdis->itemData;

	if ( p_Item != NULL )
		p_Item->DrawItem( lpdis );

	return TRUE;
}

/*!
 * \brief blah
 *
 * blah
 */

void XPopupMenu::convertMenu( HMENU hMenu, const BOOL bForce )
{
	MENUITEMINFO mii;
	ZeroMemory( &mii, sizeof( MENUITEMINFO ) );
	mii.cbSize = sizeof( MENUITEMINFO );
	mii.fMask = MIIM_SUBMENU | MIIM_DATA | MIIM_FTYPE | MIIM_STRING;

	//int k = 0;
	const int n = GetMenuItemCount( hMenu );

	for (int i = 0; i < n; i++ )
	{
		char string[500];
		mii.dwTypeData = string;
		mii.cch = 499;

		if ( GetMenuItemInfo( hMenu, i, TRUE, &mii ) == TRUE ) {

			if ( !( mii.fType & MFT_OWNERDRAW ) || bForce == TRUE ) {

				mii.fType |= MFT_OWNERDRAW;
				XPopupMenuItem * p_Item;
				TString tsItem(string);

				// fixes identifiers in the dialog menu not being resolved. 
				// TODO Needs testing to see if it causes any other issues, like double eval's)
				if (bForce && this->getName() == "dialog")
					Dcx::mIRC.tsEval(tsItem, tsItem.to_chr()); // we can use tsItem for both args as the second arg is copied & used before the first arg is set with the return value.

				if ( mii.fType & MFT_SEPARATOR )
					p_Item = new XPopupMenuItem( this, TRUE, mii.dwItemData );
				else
					p_Item = new XPopupMenuItem( this, tsItem, -1, mii.hSubMenu!=NULL?TRUE:FALSE, mii.dwItemData );

				this->m_vpMenuItem.push_back( p_Item );
				mii.dwItemData = (ULONG_PTR) p_Item;
				SetMenuItemInfo( hMenu, i, TRUE, &mii );

				//++k;
			}
		}
	}
}

/*!
 * \brief blah
 *
 * blah
 */

void XPopupMenu::cleanMenu( HMENU hMenu )
{
	MENUITEMINFO mii;
	ZeroMemory( &mii, sizeof( MENUITEMINFO ) );
	mii.cbSize = sizeof( MENUITEMINFO );
	mii.fMask = MIIM_SUBMENU | MIIM_DATA | MIIM_FTYPE;

	const int n = GetMenuItemCount( hMenu );

	for (int i = 0; i < n; i++ )
	{
		if ( GetMenuItemInfo( hMenu, i, TRUE, &mii ) == TRUE ) {

			if ( mii.hSubMenu != NULL )
				this->cleanMenu( mii.hSubMenu );

			if ( mii.fType & MFT_OWNERDRAW ) {

				mii.fType &= ~MFT_OWNERDRAW;
				mii.dwItemData = NULL;
				SetMenuItemInfo( hMenu, i, TRUE, &mii );
			}
		}
	}
}

/*!
 * \brief blah
 *
 * blah
 */

void XPopupMenu::clearAllMenuItems( ) {
  
  VectorOfXPopupMenuItem::iterator itStart = this->m_vpMenuItem.begin( );
  VectorOfXPopupMenuItem::iterator itEnd = this->m_vpMenuItem.end( );

  while ( itStart != itEnd ) {

    if ( *itStart != NULL )
      delete *itStart;

    ++itStart;
  }

  this->m_vpMenuItem.clear( );
}

/*!
 * \brief blah
 *
 * blah
 */

HBITMAP XPopupMenu::getBackBitmap( ) const {

	return this->m_hBitmap;
}

/*!
 * \brief blah
 *
 * blah
 */

void XPopupMenu::setBackBitmap( HBITMAP hBitmap ) {

	if ( this->m_hBitmap != NULL )
		DeleteBitmap(this->m_hBitmap );

	this->m_hBitmap = hBitmap;
}

/**
 * Attaches the XPopupMenu to the mIRC MenuBar.
 */
bool XPopupMenu::attachToMenuBar(HMENU menubar, const TString &label) {
	// Already attached
	if (this->m_bAttachedToMenuBar)
		return false;

	// Add the menu to the mIRC window menubar
	this->m_bAttachedToMenuBar = Dcx::XMenubar.addToMenuBar(menubar, this, label);
	return this->m_bAttachedToMenuBar;
}

/**
 * Detaches the XPopupMenu from the mIRC MenuBar.
 */
void XPopupMenu::detachFromMenuBar(HMENU menubar) {
	// Not attached, dont bother
	if (!this->m_bAttachedToMenuBar)
		return;

	Dcx::XMenubar.removeFromMenuBar(menubar, this);
	this->m_bAttachedToMenuBar = false;
}

/**
 * Methods to access marked text.
 */
void XPopupMenu::setMarkedText(const TString &text) {
	this->m_tsMarkedText = text;
}

const TString &XPopupMenu::getMarkedText() const {
	return this->m_tsMarkedText;
}

/*
 * Parses a string to a menu style.
 */
XPopupMenu::MenuStyle XPopupMenu::parseStyle(const TString &tsStyle) {
	XPopupMenu::MenuStyle style = XPopupMenu::XPMS_OFFICE2003;

	if (tsStyle == "office2003rev")
		style = XPopupMenu::XPMS_OFFICE2003_REV;
	else if (tsStyle == "officexp")
		style = XPopupMenu::XPMS_OFFICEXP;
	else if (tsStyle == "icy")
		style = XPopupMenu::XPMS_ICY;
	else if (tsStyle == "icyrev")
		style = XPopupMenu::XPMS_ICY_REV;
	else if (tsStyle == "grade")
		style = XPopupMenu::XPMS_GRADE;
	else if (tsStyle == "graderev")
		style = XPopupMenu::XPMS_GRADE_REV;
	else if (tsStyle == "vertical")
		style = XPopupMenu::XPMS_VERTICAL;
	else if (tsStyle == "verticalrev")
		style = XPopupMenu::XPMS_VERTICAL_REV;
	else if (tsStyle == "normal")
		style = XPopupMenu::XPMS_NORMAL;
	else if (tsStyle == "custom")
		style = XPopupMenu::XPMS_CUSTOM;

	return style;
}
