/*!
 * \file dcxml.cpp
 * \brief blah
 *
 * TODO: rename all variables to use the same convention (camelCase)
 *
 * \author Martijn Laarman ( Mpdreamz at mirc dot net )
 * \version 2.2
 *
 * \b Revisions
 *        -Completely rewrote DCXML to be more OOP
 *		  -
 *
 * � ScriptsDB.org - 2006
 */
#include "defines.h"
#include "dcxmlincludes.h"
#include "dcxml.h"
#include "dcxmlparser.h"

DcxmlParser *Dcxml::Parser;

Dcxml::Dcxml() {

}
/*
 * /dcxml -[SWITCH] [?NAME] [DATASET] [PARMS]
 *
 * -d = [DNAME] [DATASET] [FILENAME]
 * -p = [PNAME] [DATASET] [FILENAME]
 */
mIRC(dcxml) {
#ifndef UNICODE
    TString input(data);
	XSwitchFlags flags(input.gettok(1));
    int numtok = input.numtok();
    
    if (numtok < 3) {
        Dcx::error(TEXT("/dcxml"), TEXT("Insuffient parameters"));
        return 0;
    }


	// Parse XDialog XML.
    if (flags[TEXT('d')]) {
		TString tsFilename(input.gettok( 4, -1 ).trim());
		if (!IsFile(tsFilename)) {
			Dcx::errorex(TEXT("/dcxml -d"), TEXT("Unable To Access File: %s"), tsFilename.to_chr());
			return 0;
		}
		// NEEDS FIXED!
		//Dcxml::Parser = new DcxmlParser( 
		//	tsFilename.to_chr()
		//	,input.gettok(2).to_chr()
		//	,input.gettok(3).to_chr()
		//	,(flags[TEXT('v')])
		//	,(flags[TEXT('x')])
		//);
		//return (Dcxml::Parser->loadSuccess) ? 1 : 0;
		return 0;
    }
	// Parse XPopup DCXML.
	/*
	else if (flags[TEXT('p')]) {
		TiXmlElement *popups = doc.FirstChildElement("dcxml")->FirstChildElement("popups");
		TiXmlElement *popup = NULL;
		TString popupName(input.gettok(2));
		TString popupDataset(input.gettok(3));
        
		if ((popupName == TEXT("mircbar")) || (popupName == TEXT("mirc")) || (popupName == TEXT("scriptpopup"))) {
			Dcx::errorex(TEXT("/dcxml"), TEXT("Menu name TEXT('%s') is reserved."), popupName.to_chr());
			return 0;
		}

		// Couldnt find popups group.
        if (!popups) { 
            Dcx::error(TEXT("/dcxml"), TEXT("No TEXT('popups') Group"));
            return 0;
        }

		XPopupMenuManager::LoadPopupsFromXML(popups, popup, popupName, popupDataset);
		return 1;
	}
	*/
	// Unknown flags.
	else
		Dcx::errorex(TEXT("/dcxml"), TEXT("Unknown flag %s"), input.gettok(1).to_chr());
#endif
	return 0;
}
mIRC(_dcxml)
{
	TString d(data);
	d.trim();

	data[0] = 0;
#ifndef UNICODE
	if (d.numtok( ) != 1) {
		lstrcpy(data, TEXT("D_ERROR Invalid Args: A prop is required."));
		return 3;
	}

	if (d.gettok( 1 ) == TEXT("Loaded"))
	{
		lstrcpy(data, (Dcxml::Parser->loadSuccess) ? TEXT("$true") : TEXT("$false"));
	}
#endif
	return 3;
	
}