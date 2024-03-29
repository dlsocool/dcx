/*!
 * \file dcxdirectshow.h
 * \brief blah
 *
 * blah
 *
 * \author Ook
 * \version 1.0
 *
 * \b Revisions
 *
 * � ScriptsDB.org - 2006
 */

#ifndef _DCXDIRECTSHOW_H_
#define _DCXDIRECTSHOW_H_

#include "defines.h"

#ifdef DCX_USE_DXSDK
#include "Classes/dcxcontrol.h"
#include <dshow.h>
#include <initguid.h>
#include <qnetwork.h>
#include <d3d9.h>
#include <vmr9.h>

class DcxDialog;

/*!
 * \brief blah
 *
 * blah
 */

class DcxDirectshow : public DcxControl {

public:

  DcxDirectshow( const UINT ID, DcxDialog * p_Dialog, const HWND mParentHwnd, const RECT * rc, TString & styles );
  virtual ~DcxDirectshow( );

  LRESULT PostMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bParsed );
  LRESULT ParentMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bParsed );

  void parseInfoRequest( TString & input, char * szReturnValue );
  void parseCommandRequest( TString & input );
  void parseControlStyles( TString & styles, LONG * Styles, LONG * ExStyles, BOOL * bNoTheme );

  inline TString getType( ) { return TString( "directshow" ); };
  TString getStyles(void);

protected:
	HRESULT InitWindowlessVMR(const HWND hwndApp, IGraphBuilder* pGraph, IVMRWindowlessControl9** ppWc);
	HRESULT SetVideoPos(void);
	void ReleaseAll(void);
	enum Properties { PROP_AUTHOR = 0, PROP_TITLE, PROP_RATING, PROP_DESCRIPTION };
	HRESULT getProperty(char *prop, const int type) const;
	HRESULT setAlpha(float alpha);
	HRESULT setVideo(const TString flags, const float brightness, const float contrast, const float hue, const float saturation);
	HRESULT getVideo(VMR9ProcAmpControl *amc) const;
	HRESULT getVideoRange(VMR9ProcAmpControlFlags prop, VMR9ProcAmpControlRange *acr) const;
	UINT64 getPosition(void) const; //!< gets video position within stream
	HRESULT setPosition(const UINT64 pos); //!< sets the video position to x .
	UINT64 getDuration(void) const; //!< gets video duration.
	DWORD CheckSeekCapabilities(DWORD dwCaps) const;
	HRESULT setVolume(const float vol);
	float getVolume(void) const;

#define WM_GRAPHNOTIFY  WM_APP + 1

	IGraphBuilder					 *m_pGraph;
	IMediaControl					 *m_pControl;
	IMediaEventEx					 *m_pEvent;
	IMediaSeeking					 *m_pSeek;
	IVMRWindowlessControl9 *m_pWc;
	bool										m_bKeepRatio;
	bool										m_bLoop;
	TString									m_tsFilename;
};

#pragma comment(lib, "Strmiids.lib")
#endif // DCX_USE_DXSDK

#endif // _DCXDIRECTSHOW_H_
