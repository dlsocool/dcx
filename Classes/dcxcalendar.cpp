/*!
TODO: monthchange event
http://msdn.microsoft.com/library/default.asp?url=/library/en-us/shellcc/platform/commctls/monthcal/structures/nmdaystate.asp

MCHT_TITLEBTNNEXT
    The given point was over the button at the top right corner of the control. If the user clicks here, the month calendar will scroll its display to the next month or set of months.
MCHT_TITLEBTNPREV
    The given point was over the button at the top left corner of the control. If the user clicks here, the month calendar will scroll its display to the previous month or set of months.

 * \file dcxcalendar.cpp
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
#include "Classes/dcxcalendar.h"
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

DcxCalendar::DcxCalendar( const UINT ID, DcxDialog * p_Dialog, const HWND mParentHwnd, const RECT * rc, TString & styles ) 
: DcxControl( ID, p_Dialog )
{
	LONG Styles = 0, ExStyles = 0;
	BOOL bNoTheme = FALSE;
	this->parseControlStyles( styles, &Styles, &ExStyles, &bNoTheme );

	this->m_Hwnd = CreateWindowEx(	
		ExStyles | WS_EX_CLIENTEDGE, 
		DCX_CALENDARCLASS, 
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

	this->setControlFont( GetStockFont( DEFAULT_GUI_FONT ), FALSE );
	this->registreDefaultWindowProc( );
	SetProp( this->m_Hwnd, "dcx_cthis", (HANDLE) this );
}

/*!
 * \brief blah
 *
 * blah
 */

DcxCalendar::~DcxCalendar( ) {

  this->unregistreDefaultWindowProc( );
}

void DcxCalendar::toXml(TiXmlElement * xml) {
	__super::toXml(xml);
	xml->SetAttribute("caption", getValue().to_chr());
}

TString DcxCalendar::getStyles(void) {
	TString styles(__super::getStyles());
	const DWORD Styles = GetWindowStyle(this->m_Hwnd);

	if (Styles & MCS_MULTISELECT)
		styles.addtok("multi");
	if (Styles & MCS_NOTODAY)
		styles.addtok("notoday");
	if (Styles & MCS_NOTODAYCIRCLE)
		styles.addtok("notodaycircle");
	if (Styles & MCS_WEEKNUMBERS)
		styles.addtok("weeknum");
	if (Styles & MCS_DAYSTATE)
		styles.addtok("daystate");

	return styles;
}

TString DcxCalendar::getValue(void)
{
	long start, end;
	char buf[128];

	if (isStyle(MCS_MULTISELECT)) {
		SYSTEMTIME st[2];
		ZeroMemory(st, sizeof(SYSTEMTIME) *2);
		MonthCal_GetSelRange(this->m_Hwnd, st);

		start = SystemTimeToMircTime(&(st[0]));
		end = SystemTimeToMircTime(&(st[1]));
	}
	else {
		SYSTEMTIME st;

		ZeroMemory(&st, sizeof(SYSTEMTIME));
		MonthCal_GetCurSel(this->m_Hwnd, &st);

		st.wHour = 0;
		st.wMinute = 0;
		st.wSecond = 0;
		st.wMilliseconds = 0;

		start = SystemTimeToMircTime(&st);
		end = start;
	}

	wnsprintf(buf, 128, "%ld %ld", start, end);
	return buf;
}

/*!
 * \brief blah
 *
 * blah
 */

void DcxCalendar::parseControlStyles(TString & styles, LONG * Styles, LONG * ExStyles, BOOL * bNoTheme) {
	const UINT numtok = styles.numtok();

	for (UINT i = 1; i <= numtok; i++)
	{
		if (styles.gettok(i) == "multi")
			*Styles |= MCS_MULTISELECT;
		else if (styles.gettok(i) == "notoday")
			*Styles |= MCS_NOTODAY;
		else if (styles.gettok(i) == "notodaycircle")
			*Styles |= MCS_NOTODAYCIRCLE;
		else if (styles.gettok(i) == "weeknum")
			*Styles |= MCS_WEEKNUMBERS;
		else if (styles.gettok(i) == "daystate")
			*Styles |= MCS_DAYSTATE;
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

void DcxCalendar::parseInfoRequest(TString &input, char *szReturnValue) {

	const TString prop(input.gettok( 3 ));

	// [NAME] [ID] [PROP]
	if (prop == "value") {
		lstrcpyn(szReturnValue,this->getValue().to_chr(), MIRC_BUFFER_SIZE_CCH);
		return;
	}
	else if (prop == "range") {
		SYSTEMTIME st[2];
		TString dmin("nolimit");
		TString dmax("nolimit");

		ZeroMemory(st, sizeof(SYSTEMTIME) *2);

		const DWORD val = MonthCal_GetRange(this->m_Hwnd, st);

		if (val & GDTR_MIN)
			dmin.tsprintf("%ld", SystemTimeToMircTime(&(st[0])));

		if (val & GDTR_MAX)
			dmax.tsprintf("%ld", SystemTimeToMircTime(&(st[1])));

		wnsprintf(szReturnValue, MIRC_BUFFER_SIZE_CCH, "%s %s", dmin.to_chr(), dmax.to_chr()); // going to be within MIRC_BUFFER_SIZE_CCH limit anyway.
		return;
	}
	else if (prop == "today") {
		SYSTEMTIME st;

		ZeroMemory(&st, sizeof(SYSTEMTIME));

		MonthCal_GetToday(this->m_Hwnd, &st);
		wnsprintf(szReturnValue, MIRC_BUFFER_SIZE_CCH, "%ld", SystemTimeToMircTime(&st));
		return;
	}
	else if (prop == "selcount") {
		wnsprintf(szReturnValue, MIRC_BUFFER_SIZE_CCH, "%d", MonthCal_GetMaxSelCount(this->m_Hwnd));
		return;
	}
	else if (this->parseGlobalInfoRequest(input, szReturnValue))
		return;

	szReturnValue[0] = 0;
}

/*!
 * \brief blah
 *
 * blah
 */
void DcxCalendar::parseCommandRequest(TString &input) {
	const XSwitchFlags flags(input.gettok(3));

//SetDayState

	const UINT numtok = input.numtok();

	// xdid -k [NAME] [ID] [SWITCH] [+FLAGS] [$RGB]
	if (flags['k'] && numtok > 4) {
		const XSwitchFlags xflags(input.gettok(4));
		const COLORREF col = (COLORREF) input.gettok(5).to_int();

		// Set the background color displayed between months.
		if (xflags[TEXT('b')])
			MonthCal_SetColor(this->m_Hwnd, MCSC_BACKGROUND, col);

		// Set the background color displayed within the month.
		if (xflags[TEXT('g')])
			MonthCal_SetColor(this->m_Hwnd, MCSC_MONTHBK, col);

		// Set the color used to display text within a month.
		if (xflags[TEXT('t')])
			MonthCal_SetColor(this->m_Hwnd, MCSC_TEXT, col);

		// Set the background color displayed in the calendar's title and selection color.
		if (xflags[TEXT('i')])
			MonthCal_SetColor(this->m_Hwnd, MCSC_TITLEBK, col);

		// Set the color used to display text within the calendar's title.
		if (xflags[TEXT('a')])
			MonthCal_SetColor(this->m_Hwnd, MCSC_TITLETEXT, col);

		// Set the color used to display header day and trailing day text. Header and trailing days are the days from the previous and following months that appear on the current month calendar.
		if (xflags[TEXT('r')])
			MonthCal_SetColor(this->m_Hwnd, MCSC_TRAILINGTEXT, col);
	}
	//xdid -m [NAME] [ID] [SWITCH] [MAX]
	else if (flags['m'] && numtok > 3) {
		const int max = input.gettok(4).to_int();

		MonthCal_SetMaxSelCount(this->m_Hwnd, max);
	}
	//xdid -r [NAME] [ID] [SWITCH] [MIN] [MAX]
	else if (flags['r'] && numtok > 4) {
		DWORD dflags = 0;
		SYSTEMTIME range[2];

		ZeroMemory(range, sizeof(SYSTEMTIME) *2);

		if (input.gettok(4) != "nolimit") {
			range[0] = MircTimeToSystemTime((long) input.gettok(4).to_num());
			dflags |= GDTR_MIN;
		}

		if (input.gettok(5) != "nolimit") {
			range[1] = MircTimeToSystemTime((long) input.gettok(5).to_num());
			dflags |= GDTR_MAX;
		}

		MonthCal_SetRange(this->m_Hwnd, dflags, range);
	}
	//xdid -s [NAME] [ID] [SWITCH] [MIN] (MAX)
	else if (flags['s'] && numtok > 3) {
		const long min = (long) input.gettok(4).to_num();
		long max = 0;
		SYSTEMTIME range[2];

		ZeroMemory(range, sizeof(SYSTEMTIME) *2);
		range[0] = MircTimeToSystemTime(min);

		if (isStyle(MCS_MULTISELECT)) {
			// if only one date specified, select the same date
			if (numtok < 5)
				range[1] = range[0];
			else {
				max = (long) input.gettok(5).to_num();
				range[1] = MircTimeToSystemTime(max);
			}

			MonthCal_SetSelRange(this->m_Hwnd, range);
		}
		else {
			MonthCal_SetCurSel(this->m_Hwnd, &(range[0]));
		}
	}
	//xdid -t [NAME] [ID] [SWITCH] [TIMESTAMP]
	else if (flags['t'] && numtok > 3) {
		const long mircTime = (long) input.gettok(4).to_num();
		const SYSTEMTIME sysTime = MircTimeToSystemTime(mircTime);

		MonthCal_SetToday(this->m_Hwnd, &sysTime);
	}
	else
		this->parseGlobalCommandRequest( input, flags );
}

/*!
 * \brief blah
 *
 * blah
 */
LRESULT DcxCalendar::ParentMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bParsed) {
	switch (uMsg) {
		case WM_NOTIFY: {
			LPNMHDR hdr = (LPNMHDR) lParam;

			if (!hdr)
				break;

			switch(hdr->code) {
				case MCN_GETDAYSTATE: {
					LPNMDAYSTATE lpNMDayState = (LPNMDAYSTATE) lParam;
					MONTHDAYSTATE mds[12];

					const int iMax = lpNMDayState->cDayState;
					char eval[100];

					for (int i = 0; i < iMax; i++) {
						// daystate ctrlid startdate
						this->evalAliasEx(eval, 100, "%s,%d,%d", "daystate", this->getUserID(),
							SystemTimeToMircTime(&(lpNMDayState->stStart)));
						mds[i] = (MONTHDAYSTATE) 0;

						TString strDays(eval);
						strDays.trim();

						for (UINT x = 1; x <= strDays.numtok(TSCOMMA); x++)
							BOLDDAY(mds[i], strDays.gettok(x, TSCOMMA).trim().to_int());

						// increment the month so we get a proper offset
						lpNMDayState->stStart.wMonth++;

						if (lpNMDayState->stStart.wMonth > 12) {
							lpNMDayState->stStart.wMonth = 1;
							lpNMDayState->stStart.wYear++;
						}
					}

					lpNMDayState->prgDayState = mds;
					bParsed = TRUE;
					return FALSE;
				}

				case MCN_SELCHANGE: {
					this->execAliasEx("%s,%d", "selchange", this->getUserID());
					break;
				}
				case MCN_SELECT: {
					// specific code to handle multiselect dates
					if (this->isStyle(MCS_MULTISELECT)) {
						// get the selected range
						SYSTEMTIME selrange[2];

						MonthCal_GetSelRange(this->m_Hwnd, selrange);

						// send event to callback
						this->execAliasEx("%s,%d,%d,%d", "select", this->getUserID(),
							SystemTimeToMircTime(&(selrange[0])),
							SystemTimeToMircTime(&(selrange[1])));
					}
					// code to handle single selected dates
					else {
						SYSTEMTIME st;

						ZeroMemory(&st, sizeof(SYSTEMTIME));
						MonthCal_GetCurSel(this->m_Hwnd, &st);

						st.wHour = 0;
						st.wMinute = 0;
						st.wSecond = 0;
						st.wMilliseconds = 0;

						// send event to callback
						this->execAliasEx("%s,%d,%d", "select", this->getUserID(), SystemTimeToMircTime(&st));
					}

					break;
				}
				case NM_RELEASEDCAPTURE: {
					if (this->m_pParentDialog->getEventMask() & DCX_EVENT_CLICK)
						this->execAliasEx("%s,%d", "sclick", this->getUserID());
					break;
				}
				default:
					break;
			} // end switch
		}
	}
	return 0L;
}

LRESULT DcxCalendar::PostMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bParsed) {
	switch (uMsg) {

    case WM_LBUTTONUP:
      {
				if (this->m_pParentDialog->getEventMask() & DCX_EVENT_CLICK)
	        this->execAliasEx("%s,%d", "lbup", this->getUserID( ) );
      }
      break;

		//case WM_GETDLGCODE:
		//{
		//	return DLGC_WANTARROWS;
		//	break;
		//}

		case WM_DESTROY: {
			delete this;
			bParsed = TRUE;
			break;
		}

		default:
			return this->CommonMessage( uMsg, wParam, lParam, bParsed);
			break;
	}

	return 0L;
}
