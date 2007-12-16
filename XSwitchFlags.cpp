#include ".\defines.h"

// Constructor
XSwitchFlags::XSwitchFlags(TString switches) {
	// no - sign, invalid syntax
	if ((switches)[0] != '-')
		return;

	unsigned int i = 1;
	unsigned int len = switches.len();
	char c;

	ZeroMemory(flags, sizeof(bool) * 26);
	ZeroMemory(flags_cap, sizeof(bool) * 26);

	// Parse the switches
	while (i < len) {
		c = switches[i];

		// Check if its in the right range
		if (c >= 'a' && c <= 'z')
			flags[(int) (c - 'a')] = true;
		else if (c >= 'A' && (c <= 'Z'))
			flags_cap[(int) (c - 'A')] = true;

		i++;
	}
}

// Destructor
XSwitchFlags::~XSwitchFlags(void) {
}

// Checks if flags are set.
bool XSwitchFlags::isSet(const char c) {
	// Lower-case
	if ((c >= 'a') && (c <= 'z'))
		return flags[(int) (c - 'a')];
	// Upper-case
	else if ((c >= 'A') && (c <= 'Z'))
		return flags_cap[(int) (c - 'A')];

	return false;
}

// Wrapper for isSet()
bool XSwitchFlags::operator[](const char c) {
	return this->isSet(c);
}