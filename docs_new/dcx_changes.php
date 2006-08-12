<?php
$CHANGES = array(
    'v1.3.5' => array(
        'DCX Changes' => array(
			'fixed bug that caused mIRC to crash when changing text in a listview when no progressbar exists',
			'fixed a bug where edit ctrl /xdid -o wouldnt accept 1 word',
			"added 'vertical' and 'verticalrev' styles to xpopup menus",
			'got calendar select date event working properly',
			'fixed a bug causing /xdid -Q not to update removal of bold and underline from treeview item',
			'added $xdid().mouseitem for toolbar',
			'changed the way /xdialog -g background image options work',
			'fixed crash on /dll -u when dcx dialogs open.',
			'fixed grid scroll redraw issue (flickers alot though)',
			'added $xdid().dname to dialog control to retrieve its original dialog name',
			'fixed ipaddress mouse click crash.',
			're-enabled ipaddress rclick & edit events.',
			'added sclick event to ipaddress controls.',
			'fixed corruption of toolbar button text when one is deleted (tooltip text still goes missing though)',
			'fixed button in tab crash.',
			'fixed edit control with text causing crash in tab & panel.',
			'added activate & deactivate events when dialog is activated & deactivated.',
			'keydown event no longer sends repeated keys (edit control)',
			'added arrow keys & caps lock to $dialog().key',
			'fixed GetTaskbarPos() bug where memory was never freed.',
			'added lbup event to image control',
			'removed same control checks from tab/panel, was causing a loop leading to stack overflow.',
			'fixed 2 memory leaks in calendar control.',
			'fixed xdid -U lockup, fixing this also solved many others.',
			"added 'rounded' style to box control.",
			'fixed webctrl activate crash bug.',
			'fixed comboex delete crashbug.',
			'/xdialog -d and /xdid -d (for panel/box) now removes control from internal list as well as destroying it.',
			'added mwheel event',
			'added /xdialog -j [id] support for individual control redraw',
			'added $xdialog().alias to retrieve alias function name',
			'added a check for existing alias upon marking',
			'made errors on marking more verbose',
			'fixed problem with listview extended styles being misapplied, causing listview to not appear when borderselect style is used',
			'added ability to set and retrieve tooltip background and text colors for toolbar.',
			'fixed toolbar bug that caused /xdid -c to always fail with invalid args error.',
			'added italics to treeview item styles',
			'added italic item support to listview',
			'fixed a bug with /xdid -k for richedit not applying background color to new text',
			'added balloon style to toolbar to be used with tooltips style to enable balloon tooltips.',
		),
        'DCX Project' => array(
			'removed "alias ttop" from dcx_demo.mrc (thanks TheShadowOne)',
			'general code reformatting in listview',
			'moved ExStyle to parseControlStyles for listview',
			'added function for grayscaling icons (incomplete)',
			'added dcx_VS2005.sln to compile under Visual Studio 2005',
			'added addtok() to tstring class',
			'added UNICODE listview declarations to define.h so there is no longer a need to edit internal Visual Studio files',
			'added sanity check to WindowProc for props existance.',
			'removed duplicate WS_CLIPCHILDREN style',
			'merged the 3 copies WM_MEARSUREITEM code into one.',
			'added sprintf function to TString.',
			'changed error responses to use TString.',
			'changed WM_DELETEITEM & WM_DRAWITEM messages to not use GetDlgItem().',
			'added check to panels WM_NOTIFY & WM_COMMAND messages to stop messages from itself.',
			'added code to attempt to get "mIRCN" mapfile when dll is loaded on mIRC V6.2+, otherwise old "mIRC" mapfile is used.',
			'removed alot of unneeded buffers used with callAliasEx().',
			'removed some commented out code.',
			'added checks for blocking messages.',
			'added code to add/remove WS_EX_CONTROLPARENT to parent controls as children are added/removed.',
			'starting to clean up code to make it more consistant',
			'fixed a few error message inconsistencies and typos',
			'removed some unecessary comments, includes, and variables',
			'added Ook to Version credits',
			'added an error message when /xdialog commands are invalid',
			'added invalid command message for /xdid',
			'changed some error messages to make them more consistant',
			'added check for WS_TABSTOP style in child before enabling WS_EX_CONTROLPARENT in parent control.',
			'moved listview extended styles parsing to its own function.',
			'fixed TBN_GETINFOTIP event in toolbar, was handled incorrectly.',
			'fixed TBN_DELETING event in toolbar, was deleting the wrong buttons data.',
			'removed a whole bunch of redundant assignments to variables to improve speed slightly',
			'removed some unreachable code',
			'added extra checks for uninitialised variables',
			'fixed a code flow bug in trackbar upon drawing the thumb when using bitmaps',
			'fixed bug in TString.istok() function which caused it to miss the last token.',
		),
        'DCX Doc' => array(
			'fixed a typo with /xdid -n for listview',
			'removed an unnecessary flag from /xpopup -i example in dcxdoc',
			'added daystate style and event to calendar control',
			"TODO: still a bug with dcxdoc where dialog events ID's are not 0",
			'added a few more people to the credits list',
			'added download.php',
			'included a reference to the version on changes.htm',
			'added an archive page',
			'incremented dcxdoc version to 1.3.5',
			'shifted some menu items for dcxdoc',
			'main download link now points to archive page',
			'added zipster to credits for testing',
			'changed the way some links worked for credits (tutorials)',
			"added link to EinsteinXXL's CLA tutorial",
			'added some comments at the end of long switch cases to make it easier to notice where they end',
			'fixed an error with /xpopup -x',
			'formatting of changes can now be structured to include categories',
			'added Ook to dcxdoc title',
			'script batch file now pauses to display output',
			'changed some credits titles',
			'updated screenshot for listview and treeview',
		),
	),
    'v1.3.4' => array(
		'modified dcx.mrc to include an image control which displayed an icon',
		'changed output of $xdid().hwnd from hex to decimal',
		'fixed a bug with bmp transparency for image control',
		'fixed a bug with background drawing for image control when no background color is set',
		'added update background image when dialog resized',
		'added $xdid().selrange to trackbar',
		'trackbar now flickers less',
		'added /xdid -g for trackbar to set images',
		'added /xdid -o for trackbar to set opacity color',
		"added 'transparent' style to text",
		'box now looks consistant with group box static controls',
		'(hopefully) fixed deletion of docked dialog bug causing mirc to crash (thanks HAPM)',
		"added 'none' style but removed 'squared' style for box control",
		'updated /xdid -C dcxdoc, +k flag no longer applies to box control border',
		'box control now draws text colors for enabled and disabled appropriately',
		'/xdid -k command for button control now only works for bitmap buttons to load bitmap images and set transparency color (Read function note for further details)',
		'moved some functionality of /xdid -k to /xdid -c for changing button control caption color',
		'fixed a bug causing toolbar separators not to apply hidden state when added',
		'added $dcx(IsThemedXP)',
		"added 'transparent' style to box control",
		'fixed bug with OpenDialog/SaveDialog functions returning error messages as values',
		'Added $xdialog(Name).ismarked to see if the name is marked already.',
		'fixed a richedit bug crashing on rapid doubleclicking',
		'fixed a bug with $xdialog().focusid when deleting a control with focus',
		'added lbdown, sclick, lbup, dclick and rclick events to box ctrl',
		'fixed tab focus into children of panel, rebar, box and docked dialog controls',
		'added event tracking to calendar (selchange, select, sclick)',
		'fixed bug to allow docked dialogs/@windows to be tabbed into as containers',
		'updated FontDialog dcxdoc to make more sense',
		'fixed a typo in dcxdoc /xdid -q incorrect, its meant to be /xdid -J for changing control cursors',
		'fixed grammatical errors with dcxdoc',
		'updated DCX vs MDX page (feel free to tell us when to change this, this page stands at a "super low never look at it until someone says something about it" priority)',
		'documented trackbar selrange features',
		'fixed dcxdoc typo for pbar',
		'added a note to dcxdoc stating the case sensitivity of script commands',
		'added missing example for sizing event on dialog dcxdoc',
		'fixed documentation for OpenDialog/SaveDialog Styles',
		'added note for dialog dcxdoc close event',
		'fixed error with dcxdoc for dialog events having wrong ID for example',
		'added /xdid -r to dcxdoc for comboex (missing)',
		'removed dclick event from calendar control (it just never occurred), and updated sclick event description',
	),
	'v1.3.3' => array(
		'added ability to change background color of trackbar (NOTE: there is a API bug to be aware of)',
		'implemented selchange and link events to richedit',
		'added /xdid -n to richedit to toggle automatic url hyperlinking',
		'added sclick and lbup events to richedit',
		'fixed a bug with richedit not accepting return keypresses when using multiline style',
		'fixed richedit $xdid().text bug not returning manually entered text',
		"added 'themechanged' event to dialog",
		'added /xdid -B to begin label editing mode on listview and treeview controls (NOTE: listview requires focus to begin editing)',
		'added progress bars to listview',
		'fixed dcxdoc errors (thanks dJabba, PYERO)',
		'fixed up events parameter values styling in dcxdoc',
		'minor adjustments to listview dcxdoc',
		'added dJabba and PYERO to dcxdoc credits',
	),
    'v1.3.2' => array(
		'Added /xdialog -t, and updated /xdialog -g to support background images',
		'Added /xdid -w to image control',
		'Added $xdid().font global function to retrieve the font in use with a control',
		'Fixed a bug causing FONTNAME to be an optional field with /xdid -f',
		'Fixed a bug causing /xdid -j to not work on edit ctrl',
		'Added $dcx(FontDialog)',
		'Added /xdid -t to panel',
		'Added link to old dcxdoc on \'latest changes\' description',
		'Changed /xdid -q to /xdid -Q for treeview item style changing command',
		'Implemented sclick event for treeview and listview when mouse clicked on no item',
		'Added quickfixes to ipaddress and comboex, to be drawn correctly when created with "disabled" style',
		'Added a quickfix for treeview icon 0 still showing first icon (will work as long as you dont use more than 10000 icons)',

		'Fixed typos, grammatical mistakes, inconsistancies, and missing features in dcxdoc with list ctrl dcxdoc (thanks elizio, dJabba, and MiSsInGnO)',
		'Added another tutorial link to cla page',
		'Fixed some styling',
		'Added /xdid -w to link control in dcxdoc, which was missing',
		'Fixed up example in /xdid -f dcxdoc to include CHARSET',
		'Readded Mpdreamz back to credits! oops! =P',
		'Changed contact irc network from IrcSuper to Americhat (stupid Shiek) =P',
		'Added a link to j0x\'s tutorial (french only)',
		'Fixed example with /xdid -C (rgb not showing)',
	),
    'v1.3.1' => array(
		'rewriting documentation, if you find any errors or inconsistancies with the old documentation, please post a message <a href="http://dcx.scriptsdb.org/forum/showthread.php?tid=171">here</a>',
		'fixed focus using tabbing on edit controls on dialog (box tabbing and focus still being researched)',
		'changed treeview and listview rclick events so it would fire even without an item being selected',
		'added a callback sclick when /xdid -c is called for comboex',
		'fixed a bug causing filters on Open/Save dialogs to be defaulted to "All Files"',
		'added /xdid -m switch to button control to allow text on bitmap buttons',
		'fixed a typo where /xdid -d wouldnt work for comboex',
		'added /xdid -o for pbar to make text vertical',
		'added/reimplemented dragbegin, dragfile, dragfinish events to comboex, dialog, listview, treeview, edit and listbox controls',
		'fixed a bug causing some listview items to ignore certain flags upon adding',
		'added GetTaskbarPos to retreive position of taskbar',
		'added /xdid -j to listview to change flags',
		'fixed box corner bug with colored background',
		'fixed bug that didnt let first toolbar button tooltip to be changed',
		'fixed a bug with /xdid -f not redrawing the control when the font is changed back to default',
	),
    "v1.3.0" => array(
		'fixed a display bug where text would be drawn off a button when too long',
		'added a pbar property $xdid().text',
		'added ability to set no text on a button using /xdid -t',
		'added keydown, keyup and return to richedit',
		'link font is now the system default GUI font',
		'fixed /xdid -C +k for box control not using the specified color',
		'added return and rclick event to richedit',
		'added /xdid -c to copy content to clipboard for edit and richedit ctrls',
		'added owner style to OpenDialog, SaveDialog and ColorDialog',
		'changed -C to -S for selecting text ranges in edit and richedit ctrls (this would of solved the coloring bug on these controls too)',
		'included a check on /udcx to see if it was called from a menu to prevent a crash on unload. please update your dcx_tools.mrc',
	),
	'v1.2.7 and v1.2.8 reimplementation' => array(
		'removed a debug output "Dialog WM_LBUTTONDOWN" when clicking on the dialog',
		'changed $dcx(GetSystemColor), please view documentation on changes to syntax',
		'added /xdid -o to overwrite a line for listbox ctrl',
		'added a style to the list control vsbar allowing it to be scrolled when overflowing',
		'added keydown and keyup events to edit ctrl',
		'added $dcx(ColorDialog), slightly changed syntax',
		'implemented $dcx(OpenDialog) and $dcx(SaveDialog)',
		'added selstart, selend, sel, seltext properties to edit ctrl',
		'added selstart, selend, sel, seltext properties to richedit ctrl',
		'fixed a bug in /xdid -d for tab ctrl where no page would be selected after deleting current page',
		'fixed a problem with box and link ctrls where cursor command /xdid -J wouldn\'t apply',
		'implemented /xdid -U for removing focus from a control. (will not work if there is only one control on the dialog)',
		'added nocut, nocopy and nopaste return values to prevent cut, copy and paste events for edit ctrl',
		'richedit editable by default',
		'added a style readonly to richedit',
		'added /xdid -Z for zooming richedit ctrls',
		'Please note that selchange (richedit) and dropfile events are missing.<br />
They will be reimplemented in the near future.',
	),

	'17/02/2006' => array(
		'Added /xdid -q and -m to the Listview for Group Support (XP+)',
		'Corrected the height of the colorcombo which is now the same as the comboex',
		'Fixed help file typos',
	),
	'16/02/2006' => array(
		'Added cursor stuff to the DLL via /xdialog -q and /xdid -J',
	),
	'15/02/2006' => array(
		'Added /xdialog -j',
		'Fixed richedit /xdid -k switch',
		'Fixed a drawing glitch on the box control',
	),
	'14/02/2006' => array(
		'Added the +ah flags to the /xdid -t command for listview headers',
		"Added /xdid -n to listview to resize header individually after they've been created",
		'Added $xdid().hwidth, .htext and .hicon to the listview',
		'Changed the range values of the trackbar to 32 bit values',
		'Fixed the fact that an undock dialog/@window was displayed when undocked even though it was hidden just before',
		'Fixed $xdid().tooltip on treeview that returned corrupted data',
	),
	'11/02/2006' => array(
		'Fixed a bug related to XPopup menus not showing properly after merger',
	),
	'02/02/2006' => array(
		'Merged XPopup to the DLL',
	),
	'01/02/2006' => array(
		'Added missing /xdid -d doc for the box control even though the function existed',
		'Added $xdid().tooltip to the toolbar control',
		'Fixed control deletion bug with "ghost" controls and invalid IDs, crashes, etc.',
		'Fixed potential problems with image lists on certain controls (not reported, but found by me)',
		'Fixed typos in the help file',
		'Fixed the TAB that made button text disappear bug',
		'Fixed the $xdid().icon treeview bug',
	),
	'31/01/2006' => array(
		'Added /xdid -o on the treeview to change the toltip text of an item',
		'Added the $xdid().mouseitem to the treeview control',
		'Added a Note to /xdid -p',
		'Added /xdid -k to richedit to change background color',
		'Added /xdialog -x which kills a dialog instead of triggering the close state',
		'Added the nosize return possibility in the sizing dialog event',
		'Fixed the $xdid().sel index being wrong on the comboex',
		'Fixed the link control refresh bug after /xdid -t',
		'Fixed $xdid().find in several controls generating a mIRC error when used with a $null value for matchtext',
		'Fixed /xdid -l for icon size not working for treeview',
		'Fixed /xdid -u not clearing selection in listview',
		'Fixed the header events not being sent when a listview was on a panel control (stupid API inconsistency here!)',
		'Modified the close event notice. A MUST READ',
	),
	'23/01/2006' => array(
		'Added /xdid -v to change a celle text on statusbar',
		'Added the dialog name in some error messages',
		'Changed the updown $xdid().pos to $xdid().value',
		'Fixed a typo in the scroll "vertical" style preventing is from working',
		'Corrected typos in the help file',
	),
	'11/01/2006' => array(
		'Added /xdialog -f to flash dialog windows',
		'Reduced the height of the colorcombo control',
	),
	'09/01/2006' => array(
		'Added $xdid()ispass to the edit control',
		'Added /xdid -j to the edit control to trigger password mode',
		'Fixed a toolbar icon list bug',
		'Fixed the ready state of the webctrl when created, it now browses to about:blank',
		'Fixed the rebar refresh problem linked to CLA',
	),
	'08/01/2006' => array(
		'Fixed the WebCtrl GPF Bug that afflicted it so hard only on certain machines',
		'Added scrollend event to the listview',
		'Added $xdid().tbitem to listview (Mpdreamz :P)',
		'Added $xdid().mouseitem to listview (Mpdreamz :P)',
		'Increased the maximum limit of text in the edit control',
		'Fixed typos in the help file and added docs on some features and styles',
	),
	'07/01/2006' => array(
		'Added $xdialog().id to retrieve the Nth used id in a dialog',
		'Added $xdid().type to retrieve the type of the control',
		'Added hrclick event for headers in the listview',
		'Added $xdid().inbox to the box control that gives the interior client area that clears the box border + text',
		'Added sclick, lbup, lbdown, lbdclick and dclick events to the panel',
		'Added /xdid -q to change the tooltip on a toolbar button',
		'Added the squared style to the box',
		'Added $xdid().childid on tab and rebar',
		'Added dialog docking on panel and box controls',
		'Added xdid -d on panel and box controls to delete child controls',
		'Replaced the noresize and noparentalign styles by noauto in the toolbar which combines both together',
		'Changed the box so that the text background color is now the line color and text color can be different from line',
		'Fixed a Richedit coloring bug',
		'Fixed xdid -t on the listview',
		'Fixed Image control refresh bug',
		'Fixed the /xdid -c and selection bug in the colorcombo',
		'Fixed a bug with the $xdid().find in the comboex',
		'Fixed a bug where header events were not triggered when the listview was on a divider',
		'Fixed the /xdid -j treeview bug',
		'Fixed typos in the help file',
	),
	'03/01/2006' => array(
		'Added /xdid -j on trackbar (Only works with XP themes disabled)',
		'Added $xdid().dpos giving position relative to dialog',
		'Changed $xdid().pos giving position relative to parent (which can also be the dialog)',
		'Fixed /xdid -f for the richedit',
		'Fixed $xdid().pid bug',
		'Fixed the Edit $xdid().text not returning correct value in the "edit" event',
		'Fixed CLA GPF bug',
	),
	'17/12/2005' => array(
		'Added ans extra parameter to the /xdid -j of the treeview for the selected icon',
		'Corrected the $xdid().seltext not working properly on the treeview',
	),
	'16/12/2005' => array(
		'Fixed Comboboxex edit control not supporting more than the combo width of characters.',
	),
	'15/12/2005' => array(
		'Rebuilt the box control to make it custom which reduces problems and makes it support colors for the line',
		'Changed the box style rjustify to right and added the bottom style',
		'Added $xdid().tooltip to treeview',
		'Added /xdid -i for the toolbar to change the button icon',
		'Fixed toolbar dropdown event bug',
	),
	'14/12/2005' => array(
		"Converted the box control to a CONTAINER control like the PANEL so people can use the CLA with it's controls inside",
		'Added $xdialog().key general property',
		'Added $xdid().pid general property',
		'Added lbup, lbdown, lbdblclk, rbup, rbdown, rbdblclk, mbup, mbdown, mbdblclk events to dialog',
	),
	'11/12/2005' => array(
		'Corrected the mIRC Controls not working properly when the dialog is marked bug',
	),
	'10/12/2005' => array(
		'Added sclick and rclick events on some controls where it was missing and useful.',
		'Added $xdialog().mouse and $xdid().mouse',
		'Added the W and H to the sizing dialog event',
		'Added $xdid().icon to Toolbar, ListView, TreeView and Tab controls',
	),
	'09/12/2005' => array(
		'Added /xdid -c to change button color/styles on toolbar',
	),
	'08/12/2005' => array(
		'Moved /xdid -l to /xdid -j on treeview',
		'Added /xdid -l to change icon size on treeview',
		'Added /xdid -g to change item height on treeview',
		'Added /xdid -u to change toolbar button size',
		'Added /xdid -v to change toolbar button text',
		'Corrected a bug in the /xdid -p no refreshing the child controls',
	),
	'07/12/2005' => array(
		'Corrected typos in the edit and richedit control help',
		'Corrected a bug in the toolbar /xdid -l that did not refresh the bar buttons',
	),
	'06/12/2005' => array(
		'Corrected the /xdid -x | /xdialog -b border bugs',
		'Corrected a bug in the /xdid -p not refreshing the control properly',
	),
	'05/12/2005' => array(
		'Added the $xdialog().mouseid which returns over which control ID the mouse is.',
		'Added the focus and focusout dialog events which indicate when a control has focus or when it loses it.',
		'Added the $xdialog().focusid which returns which control has the focus.',
		'Corrected the box control repainting child controls\' border bugs',
	),
	'04/12/2005' => array(
		'Added /xdid -Z vertical scrolling function that can be used in any control',
		'Added an extra parameter [CHARSET] to the /xdid -f font command',
		'Added font change support on the progressbar',
		'Added +es switched to a treeview item being added',
		'Added mouse events mouse, mouseenter and mouseleave',
		'Reverted the Image control to BMP only because of problems with the GDI+ lib, so only BMPs are supported now with a color for transparency',
		'Corrected a drawing bug with the Image control when it was resized using the CLA',
	),
	'03/12/2005' => array(
		'Added $xdialog().ismenu',
		'Added the /xdid -F focus on control',
		'Added error messages for commands that create other controls when the ID is already used : /xdialog -c : Control with ID "4" already exists',
		'Added /xdid -t/-u on the edit and richedit to load from/save to a file',
		'Corrected the $xdid().num and .state on the listview',
		'Corrected the box control repainting child controls bugs',
		'Corrected the $xdid().text from edit not returning the correct value',
	),
	'29/11/2005' => array(
		'Added $xdid().text property to the toolbar',
		"Corrected a bug with the @window not properly setting it's control ID when docked",
		'Added $xdid().hwnd general control property',
	),
	'28/11/2005' => array(
		'Added the Web control',
		'Added the DCX vs MDX comparison page',
	),
	'27/11/2005' => array(
		'Added @window docking support on the panel control',
		'Added omitted updown control styles from help',
	),
	'26/11/2005' => array(
		'Added the IP Adress control',
		'Added the Updown control',
		'Corrected a GPF in the Cell Layout Algorithm (CLA) when supplied a bad cell path: now issues an error message',
		'Corrected the transparency/flat toolbar bug when a child control of a panel',
	),
	'25/11/2005' => array(
		'Fixed panel child controls not returning events for some controls',
		'Fixed bug related to toolbar button click GPF',
		'Fixed icon bug on listview',
		'Added information on icon space and [INDENT] param in N.B.s in listview doc',
		'Modified list of accessible controls by tab and divider controls to generic resizeable controls to prevent problems',
		'Fixed hsclick/hdclick events in listview missing in tab/divider/rebar child listviews',
		'Fixed the stateclick state bug by returning the correct state value in the event',
		'Added size 24 icons to the toolbar icon size command',
	),
	'24/11/2005' => array(
		'Added tracking event on the trackbar',
		'Changed the sclick event of the toolbar',
		"Rebar's /xdid -q feature has been disabled until I find a way to achieve this if it's possible",
	),
	'23/11/2005' => array(
		'Added Regular Control: Image; with support for PNG, JPG, GIF, BMP and transparency.',
		'Added Edit Events: return, edit',
		'Added missing feature to get text of combo editbox in $xdid().text',
		'Added /xdid -v t the divider to set the bar position',
		'Fixed $xdialog().nextid bug',
		'Fixed the /xdid -p bug not working on docked @window and dialog',
		'Corrected typos in the help file',
	),
	'21/11/2005' => array(
		'Added Regular Control: Link',
		'Corrected typos in the help file',
	),
	'17/11/2005' => array(
		'Added Regular Control: Listbox',
		'Rewrote my test dialog separating each control into a single command for quick enabling/disabling of a particular control',
	),
	'16/11/2005' => array(
		'Resolved a listview /xdid -a where N=0 end insertion did not work for icon, smallicon and list styles',
	),
	'13/11/2005' => array(
		'Added Regular Control: scrollbar',
		'Added multiple ID support for /xdid',
		'Added /xdialog -g, /xdid -C color commands',
		'Corrected a treeview checkbox style bug preventing checkboxes to be used in the treeview',
	),
	'11/11/2005' => array(
		'Added Regular Controls: edit, text',
		'Corrected typos in help',
		'Removed some debug messages not used',
	),
	'10/11/2005' => array(
		'Fixed the panel control not being created properly and acting as a divider',
		'Added Regular controls : Line, Box, Radio and Check',
		'Corrected a bug in the toolbar/statusbar/rebar controls not being asserted their top/bottom/left/right automatic positions in the panel control',
		'Corrected rebar band release display bug',
	),
	'09/11/2005' => array(
		'Activated /xdid and $xdid for docked @windows and dialogs',
		'Added the default style for the button',
		'Added general control styles: tabstop, group, disabled',
		'Changed help files in styles section',
	),
	'02/11/2005' => array(
		'Added a notice for switches +mn of the /xdialog -b command',
	),
	'14/10/2005' => array(
		'Corrected a GPF bug when the DLL was unload via /dll -u and a DCX dialog is opened',
	),
	'10/10/2005' => array(
		'Changed labeltip to tooltip in Listview styles',
		'Added /xdid -f font command to the richedit control',
		'Added /xdid -M global control command linked with $xdid().mark to store additional information per control',
		'Added toolbar AutoStretch buttons feature linked with /xdid -m',
		'Added demo dialog which needs to be completed',
		'Added change rebar event',
		'Added an important note to /xdialog -l',
	),
	'09/10/2005' => array(
		'Added Tab Control',
		'Corrected Typos in help files',
	),
	'08/10/2005' => array(
		'Added Panel Control',
	),
	'07/10/2005' => array(
		'Relaxed compilation options hopefully to resolve the $dll unable to open dcx.dll problems',
		'Added the /xdialog -l command',
		'Added a new section - Cell Layout Algorithm',
	),
	'20/09/2005' => array(
		'Added fixedorder style to rebar control',
		'Fixed button /xdid -l and -t help file examples',
	),
	'20/09/2005' => array(
		'Added Event Management in the divider control for subcontrols',
		'Corrected the WIDTH param in the rebar not taken into account on band creation',
	),
	'19/09/2005' => array(
		'Added the custom made divider control (not fully functional yet, misses event handling of child controls)',
		'Corrected typos in the help file',
	),
	'17/09/2005' => array(
		'Added option to set separator width in toolbar in /xdid -a notes',
		'Corrected .selext & .text comboex bugs',
	),
	'16/09/2005' => array(
		'Corrected a bug in my TString support lib also related to the richedit bug',
		'Added multiline selection in listview + $xdid .selnum and modified .sel prop',
		'Added more listview optional control styles',
		'Added top, noresize, noparentalign statusbar styles',
		'Added dialog events, endsize, min, max, restore, beginmove, moving, endmove',
	),
	'14/09/2005' => array(
		'Added /xdid -l to ListView + TreeView to change icon',
		'Added /xdid -v to ListView',
		'Corrected explanation for the progressbar "digital mode"',
	),
	'13/09/2005' => array(
		'Corrected a treeview itempath bug',
	),
	'11/09/2005' => array(
		'Corrected typo in Mark Command',
	),
	'7/09/2005' => array(
		'Corrected a toolbar tooltip bug',
		'Corrected the toolbar font not being applied',
		'Correctd help typos',
		'Let me kwow if anyone has problems with the Release DLL',
	),
	'5/09/2005' => array(
		'Completed RichEdit control',
		'Added .isid and .nextid $xdialog properties',
		'Corrected typos in help file',
		'Help file now being translated into French, Swedish, Portuguese and Finnish. Looking for translators for Spanish and Italian.',
	),
	'4/09/2005' => array(
		'Added the Button control',
		'Documented help event in all controls',
		'Corrected a few typos in the help file',
	),
	'3/09/2005' => array(
		'Added $xdid .find prop to ListView',
		'Rebuilt the /xdid -z of TreeView with more sorting options',
		'/xdid -f Font change switch completed',
	),
	'2/09/2005' => array(
		'Added /xdid -g, -i and -z switches to ListView',
		'Added .tooltip prop to statusbar',
	),
	'1/09/2005' => array(
		'Added -v switch to treeview to change itemtext',
		'Finished code base adaptation',
	),
	'31/08/2005' => array(
		'Added -j switch on toolbar to set button min and max width',
	),
	'28/08/2005' => array(
		'Mark function parameters changed',
		'Added Text on the Progressbar control',
		'Added 3 events on progressbar, sclick, rclick and mousebar',
		'Typos in help files',
	),
	'25/08/2005' => array(
		'Recoded the whole base of the framework for better evolution in the futur',
		'Need to convert old code to new franework, not hard but time consuming',
	),
	'23/08/2005' => array(
		'Added Colorcombo control completed',
		'Started RichEdit control, but far from finished',
	),
	'21/08/2005' => array(
		'Major Changes',
		'DCXControl was transfered to /xdialog -c',
		'Added several /xdialog switches',
		'Moved Animate to /xdialog',
		'Added several Rebar /xdid switches',
		'Added rebar events',
		'Added COLOR support for rebar band text',
		'Corrected help file documentation and typos',
	),
	'18/08/2005' => array(
		'Added more child controls on rebar',
		'Activated events on child controls on rebar',
		'Added /xdid switches for rebar control',
	),
	'16/08/2005' => array(
		'Dialog events with beginsize and sizing',
		'Added rebar functionnality ( more to come )',
		'Corrected a toolbar GPF bug',
		'Added some event support for child controls on rebar',
	),
	'14/08/2005' => array(
		'Changed the pbar /xdid -mf switch to -mg',
		'Started Rebar Control (really incomplete)',
		'Corrected help file typos',
	),
	'13/08/2005' => array(
		'Added /xdialog and $xdialog functions',
		'Added -b switch to /xdialog for border/style mods on dialogs',
		'Added -x general switch to /xdid',
		'Finally resolved mIRCs trick in disabling dialog resizing, now functional without needing an extra control (hint: positioner).',
		'Added Item number returned in $4 in sclick, stateclick, rclick and dclick events of listview',
	),
	'06/08/2005' => array(
		'Added Trackbar control',
		'Added documentation warning in @window doc',
		'Updated DLL Documentation with HTML fixes and corrections of all kinds',
	),
	'02/08/2005' => array(
		'Bug Fixes',
	),
	'01/08/2005' => array(
		'Added @window docking',
		'Added Animate Dialog Function',
		'Added Toolbar Control',
		'Debugging/Cleaning of debug echos (If you see some more debug text, please let me know)',
	),
	'31/07/2005' => array(
		'Added ComboEx Control',
		'Added Listview more stuff',
	),
	'26/07/2005' => array(
		'Added ListView (really not finished)',
	),
	'24/07/2005' => array(
		'Added Statusbar control',
	),
	'17/07/2005' => array(
		'Added treeview /xdid switches',
	),
	'16/07/2005' => array(
		'Changed the progressbar /xdid -s switch to -u',
		'Added /xdid global switches, -behps',
		'Added $xdid() global props, .enabled, .visible, .pos',
		'Added treeview $xdid() properties',
	),
	'14/07/2005' => array(
		'Added all the treeview events',
		'Added a couple -X switches to the treeview control',
	),
	'13/07/2005' => array(
		'Changed the progressbar /xdid -b switch to -k',
		'Added start of treeview control (rest is coming)',
	)
);
?>
