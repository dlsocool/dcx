/*!
 * \file dcxlist.h
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

#ifndef _DCXLIST_H_
#define _DCXLIST_H_

#include "defines.h"
#include "Classes/dcxcontrol.h"

class DcxDialog;

/*!
 * \brief blah
 *
 * blah
 */

class DcxList : public DcxControl {

public:

	DcxList( UINT ID, DcxDialog * p_Dialog, HWND mParentHwnd, RECT * rc, TString & styles );
	virtual ~DcxList( );

	LRESULT PostMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bParsed );
	LRESULT ParentMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bParsed );

	void parseInfoRequest( TString & input, char * szReturnValue );
	void parseCommandRequest( TString & input );
	void parseControlStyles( TString & styles, LONG * Styles, LONG * ExStyles, BOOL * bNoTheme );

	inline TString getType( ) { return TString( "list" ); };
	inline UINT getDragListId() const { return m_iDragList; };
	TString getStyles(void);

	static void registerClass(void);

protected:
	enum SearchTypes { LBSEARCH_W = 1, LBSEARCH_R };

	void DrawDragLine(const int location);
	BOOL matchItemText( const int nItem, const TString * search, const UINT SearchType );

	UINT m_iDragList;
	int m_iLastDrawnLine;
	BOOL m_bUseDrawInsert;
};

#endif // _DCXLIST_H_
