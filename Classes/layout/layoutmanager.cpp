/*!
 * \file layoutmanager.cpp
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

#include "layoutmanager.h"

/*!
 * \brief Constructor
 *
 * blah
 */

LayoutManager::LayoutManager( ) {

  this->m_pRoot = NULL;
  this->m_Hwnd = NULL;
}

/*!
 * \brief Constructor
 *
 * blah
 */

LayoutManager::LayoutManager( HWND mHwnd ) : m_Hwnd( mHwnd ) {

  this->m_pRoot = NULL;
}

/*!
 * \brief Destructor
 *
 * blah
 */

LayoutManager::~LayoutManager( ) {

}

/*!
 * \brief blah
 *
 * blah
 */

BOOL LayoutManager::updateLayout( RECT & rc ) {

  if ( this->m_pRoot != NULL ) {

    HDWP hdwp = BeginDeferWindowPos( 1 );

    this->m_pRoot->setRect( rc );
    this->m_pRoot->LayoutChild( );
    hdwp = this->m_pRoot->ExecuteLayout( hdwp );

    return EndDeferWindowPos( hdwp );
  }
	return FALSE;
}

/*!
 * \brief blah
 *
 * blah
 */

void LayoutManager::setRoot( LayoutCell * p_Root ) {

  // clean memory in case we use more than once
  if ( this->m_pRoot != NULL )
    delete this->m_pRoot;

  this->m_pRoot = p_Root;
}

/*!
 * \brief blah
 *
 * blah
 */

LayoutCell * LayoutManager::getRoot( ) const {

  return this->m_pRoot;
}

/*!
 * \brief blah
 *
 * blah
 */

LayoutCell * LayoutManager::getCell( const TString & path ) const {

  return this->parsePath( path, this->m_pRoot, 1 );
}

/*!
 * \brief blah
 *
 * blah
 */

LayoutCell * LayoutManager::parsePath( const TString & path, LayoutCell * hParent, const int depth ) {

  if ( hParent == NULL )
    return NULL;

  int n = path.numtok( ), i = 1;
  int k = path.gettok( depth ).to_int( );
  LayoutCell * hCurrentCell;

  //char data[50];

  hCurrentCell = hParent->getFirstChild( );

  if ( hCurrentCell == NULL )
    return NULL;
 
  do {

    if ( i == k ) {

      //MessageBox( hwnd, "i == k", "i == k", MB_OK );
      // finished tree search and found
      if ( depth == n )
       return hCurrentCell;

      return LayoutManager::parsePath( path, hCurrentCell, depth + 1 );
    }

    i++;

  } while ( ( hCurrentCell = hCurrentCell->getNextSibling( ) ) != NULL );

  return NULL;
}
