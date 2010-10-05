<?php
function get_intro_webctrl() {
	echo "Web HTML control.";
}




function get_xdid_webctrl(&$XDID) {
	$XDID = array(
	    'g' => array(
	        '__desc' => 'This command is like hitting the Home button in IE.',
		),
		'i' => array(
	        '__desc' => 'This command is like hitting the Forward button in IE.',
		),
		'j' => array(
	        '__desc' => 'This command lets you execute some javascript code.',
	        '__cmd' => '[JAVASCRIPT CODE]',
	        '__eg' => "alert('Hello')",
		),
		'k' => array(
	        '__desc' => 'This command is like hitting the Back button in IE.',
		),
		'n' => array(
	        '__desc' => 'This command lets you navigate to an url.',
	        '__cmd' => '[URL]',
	        '__eg' => "http://dcx.scriptsdb.org",
		),
		'r' => array(
	        '__desc' => 'This command is like hitting the Refresh button in IE.',
		),
		't' => array(
	        '__desc' => 'This command is like hitting the Stop button in IE.',
		),
	);
}

function get_xdidprops_webctrl(&$XDIDPROPS) {
	$XDIDPROPS = array(
		"url" => array(
		    '__desc' => "This property lets you retreive the current loaded url.",
		),
		"ready" => array(
		    '__desc' => 'This property lets you retreive the ready state. If it is [v]$true[/v] the control is ready for another command, else you should wait.',
		),
	);
}

function get_events_webctrl(&$EVENTS) {
	$EVENTS = array(
	    "nav_begin" => array(
			'__desc' => "When the text is clicked.",
			'__cmd' => 'URL',
			'__eg' => 'http://dcx.scriptsdb.org/',
			'__return' => "[r]cancel[/r] return this value to block the navigation."
		),
		"nav_complete" => array(
			'__desc' => "When the control is finished navigating to the URL.",
			'__cmd' => 'URL',
			'__eg' => 'http://dcx.scriptsdb.org/',
		),
		"doc_complete" => array(
			'__desc' => "When the document has been downloaded.",
			'__cmd' => 'URL',
			'__eg' => 'http://dcx.scriptsdb.org/',
		),
		"dl_begin" => "When downloading is about to begin.",
		"dl_progress" => array(
			'__desc' => "Downloading progress update.",
			'__cmd' => 'CURRENT TOTAL',
			'__eg' => '259700 1000000',
			'__params' => array(
				'CURRENT' => 'Current dowload position.',
				'TOTAL' => 'Maximum download position.'
			),
			'__notes' => array(
				'[p]CURRENT[/p] can be [v]-1[/v]. If anyone knows why this occurs, please let us know <a href="http://dcx.scriptsdb.org/bug/?do=details&id=447">here</a>.',
				'[p]TOTAL[/p] can be [v]0[/v], so make sure to check this before performing any calculation with it.',
				'It is advised you use the values provided by [p]CURRENT[/p] and [p]TOTAL[/p] to display progress as these values may change with later revisions of Internet Explorer.',
			),
		),
		"dl_complete" => "When the downloading is complete.",
		"win_open" => array(
			'__desc' => "When a new window is attempted to be opened.",
			'__return' => "[r]cancel[/r] Return this value to block the new window from opening.",
		),
		"status" => array(
			'__desc' => "When the statusbar text changes.",
			'__cmd' => 'NEW_TEXT',
			'__eg' => 'New statusbar text',
		),
		"title" => array(
			'__desc' => "when the title changes.",
			'__cmd' => 'NEW_TEXT',
			'__eg' => 'The other page title',
		),
		"forward" => array(
			'__desc' => 'When the state of the forward button changes.',
			'__cmd' => 'ENABLED',
			'__eg' => '$false',
			'__notes' => '[p]ENABLED[/p] can be either [v]$true[/v] or [v]$false[/v] to indiciate the enabled state of the forward button.',
		),
		"back" => array(
			'__desc' => 'When the state of the back button changes.',
			'__cmd' => 'ENABLED',
			'__eg' => '$true',
			'__notes' => '[p]ENABLED[/p] can be either [v]$true[/v] or [v]$false[/v] to indicate the enabled state of the back button.',
		),
		"help" => "Launched when you click on a control using the [s]?[/s] contexthelp button.",
	);
}
?>
