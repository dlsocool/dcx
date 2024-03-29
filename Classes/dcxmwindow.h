/*!
 * \file dcxmwindow.h
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

#ifndef _DCXMWINDOW_H_
#define _DCXMWINDOW_H_

#include "defines.h"
#include "Classes/dcxcontrol.h"

class DcxDialog;

/*!
 * \brief blah
 *
 * blah
 */

class DcxMWindow : public DcxControl {

public:

  DcxMWindow( const HWND cHwnd, const HWND pHwnd, const UINT ID, DcxDialog * p_Dialog, RECT * rc, TString & styles );
  virtual ~DcxMWindow( );

  LRESULT PostMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bParsed );
  LRESULT ParentMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bParsed );

  void parseInfoRequest( TString & input, char * szReturnValue );
  void parseCommandRequest( TString & input );
  void parseControlStyles(TString &styles, LONG *Styles, LONG *ExStyles, BOOL *bNoTheme);

  inline TString getType( ) { return TString( "window" ); };

protected:

  LONG m_OrigStyles;      //!< Window Original Styles
  LONG m_OrigExStyles;    //!< Window Original Extended Styles
  HWND m_OrigParentHwnd;  //!< Window Original Parent Handle
  UINT m_OrigID;          //!< Window Original Control ID
  TString m_OrigName;     //!< Dialog Original Name
};

#endif // _DCXMWINDOW_H_
