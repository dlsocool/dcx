#include "defines.h"
#include "DcxXPPlusModule.h"

DcxXPPlusModule::DcxXPPlusModule(void)
{
}

DcxXPPlusModule::~DcxXPPlusModule(void)
{
}

bool DcxXPPlusModule::load(mIRCLinker &mIRCLink)
{
	if (isUseable())
		return false;

	OSVERSIONINFO osvi;

	ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	GetVersionEx(&osvi);

	const bool bIsWindowsXPorLater = ( (osvi.dwMajorVersion > 5) || ( (osvi.dwMajorVersion == 5) && (osvi.dwMinorVersion >= 1) ));

	if (bIsWindowsXPorLater)
		m_hModule = (HMODULE)1;

	return isUseable();
}