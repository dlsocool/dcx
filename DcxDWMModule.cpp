#include "DcxDWMModule.h"

DcxDWMModule::DcxDWMModule(void)
{
	m_bAero = false;
}

DcxDWMModule::~DcxDWMModule(void)
{
	if (isUseable()) unload();
}

bool DcxDWMModule::load(mIRCLinker &mIRCLink)
{
	BOOL bAero;
	if (isUseable()) return false;
	DcxModule::load(mIRCLink);
	mIRCLink.debug("LoadDLL", "Loading DWMAPI.DLL...");
	m_hModule = LoadLibrary("dwmapi.dll");
	if (m_hModule != NULL) {
		mIRCLink.debug("LoadDLL", "DWMAPI.DLL Loaded, Vista OS Assumed");

		DwmIsCompositionEnabledUx = (PFNDWMISCOMPOSITIONENABLED) GetProcAddress(m_hModule, "DwmIsCompositionEnabled"); // Vista ONLY!
		DwmGetWindowAttributeUx = (PFNDWMGETWINDOWATTRIBUTE) GetProcAddress(m_hModule, "DwmGetWindowAttribute"); // Vista ONLY!
		if (DwmIsCompositionEnabledUx != NULL) {
			mIRCLink.debug("LoadDLL", "Found Vista DWM Functions");
			DwmIsCompositionEnabledUx(&bAero);
		}
		if (bAero)
			m_bAero = true;
		else
			m_bAero = false;
	}
	return isUseable();
}

bool DcxDWMModule::unload(void) 
{
	if (m_hModule != NULL) {
		FreeLibrary(m_hModule);
		m_hModule = NULL;
		return true;
	}
	return false;
}

bool DcxDWMModule::refreshComposite() {
	BOOL bAero = FALSE;
	if (DwmIsCompositionEnabledUx != NULL) {
		DwmIsCompositionEnabledUx(&bAero);
	}

	if (bAero)
		m_bAero = true;
	else
		m_bAero = false;
	return m_bAero;
}

bool DcxDWMModule::isAero(void) {
	return m_bAero;
}
