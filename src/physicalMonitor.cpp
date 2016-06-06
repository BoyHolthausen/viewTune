#include "physicalMonitor.h"
#include "HighLevelMonitorConfigurationAPI.h"

#include <iostream>

std::string win32_to_utf8(const wchar_t* buffer){
	int nChars = ::WideCharToMultiByte(
		CP_UTF8,
		0,
		buffer,
		-1,
		NULL,
		0,
		NULL,
		NULL);
	if (nChars == 0) return "";

	std::string newbuffer;
	newbuffer.resize(nChars) ;
	::WideCharToMultiByte(
		CP_UTF8,
		0,
		buffer,
		-1,
		const_cast< char* >(newbuffer.c_str()),
		nChars,
		NULL,
		NULL); 

	return newbuffer;
}

PhysicalMonitor::PhysicalMonitor( LPPHYSICAL_MONITOR pPhysicalMonitor ): m_pPhysicalMonitor( pPhysicalMonitor ){
	m_name = win32_to_utf8( m_pPhysicalMonitor->szPhysicalMonitorDescription );
}

PhysicalMonitor::~PhysicalMonitor(){

}

void PhysicalMonitor::print(){
	BOOL bSuccess = 0;

	std::cout<< "- Name: " << m_name << std::endl;
	
	DWORD minBrightness = 0;
	DWORD curBrightness = 0;
	DWORD maxBrightness = 0;
	bSuccess = GetMonitorBrightness( m_pPhysicalMonitor->hPhysicalMonitor, &minBrightness, &curBrightness, &maxBrightness );
	if( bSuccess ){
		std::cout<< "- Brightness: current[" << curBrightness << "] min[" << minBrightness << "] max[" << maxBrightness << "]" <<  std::endl;
	}

	std::cout<< "- Capabilities: " << std::endl;
	DWORD dwStringLength = 0;
	bSuccess = GetCapabilitiesStringLength( m_pPhysicalMonitor->hPhysicalMonitor, &dwStringLength );
	if( bSuccess ){
		LPSTR pCapabilitiesString = (LPSTR)malloc(dwStringLength);
		if( pCapabilitiesString ){
			bSuccess = CapabilitiesRequestAndCapabilitiesReply( m_pPhysicalMonitor->hPhysicalMonitor, pCapabilitiesString, dwStringLength );
			if( bSuccess ){
				std::string strCapabilities = pCapabilitiesString;
				std::cout<< strCapabilities << std::endl << std::endl;
			}
			free( pCapabilitiesString );
		}
	}
}

void PhysicalMonitor::setBrightness( int brightness ){
	SetMonitorBrightness( m_pPhysicalMonitor->hPhysicalMonitor, brightness );
}