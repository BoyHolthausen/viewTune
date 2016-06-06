#include "monitor.h"
#include <cassert>
#include <iostream>


std::vector<Monitor*> Monitor::s_monitors;

BOOL CALLBACK MonitorEnumProc(
	_In_ HMONITOR hMonitor,
	_In_ HDC      hdcMonitor,
	_In_ LPRECT   lprcMonitor,
	_In_ LPARAM   dwData	
){
	int width = lprcMonitor->right - lprcMonitor->left;
	int height= lprcMonitor->bottom - lprcMonitor->top;
	Monitor* pMonitor = new Monitor( hMonitor, width, height );
	Monitor::s_monitors.push_back( pMonitor );
	return true;
}

void Monitor::initMonitors(){
	EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (LPARAM)nullptr );
}

void Monitor::print(){
	for( size_t i=0; i<s_monitors.size(); ++i ){

		std::cout<< "Monitor[" << i << "]" << std::endl;
		int j = 0;
		for( auto pPhysicalMonitor : s_monitors[i]->m_physicalMonitors ){
			std::cout<< "PhysicalMonitor[" << j++ << "]" << std::endl;
			pPhysicalMonitor->print();
		}
		std::cout<<"----------------------------------"<<std::endl;
	}
}

Monitor::Monitor( HMONITOR handle, int width, int height ): m_handle( handle ), m_width( width), m_height( height ){
	m_pPhysicalMonitors = nullptr;

	DWORD numPhyicalMonitors = 0;
	BOOL bSuccess = GetNumberOfPhysicalMonitorsFromHMONITOR( m_handle, &numPhyicalMonitors );

	if( bSuccess ){
		m_pPhysicalMonitors = (LPPHYSICAL_MONITOR)malloc( numPhyicalMonitors * sizeof(PHYSICAL_MONITOR));
		if( m_pPhysicalMonitors != NULL ){
			bSuccess = GetPhysicalMonitorsFromHMONITOR( m_handle, numPhyicalMonitors, m_pPhysicalMonitors );
			if( bSuccess ){
				for( size_t i=0; i<numPhyicalMonitors; ++i ){
					PhysicalMonitor* pPhysicalMonitor = new PhysicalMonitor( m_pPhysicalMonitors + i );
					m_physicalMonitors.push_back( pPhysicalMonitor );
				}
			}
		}
	}
}

Monitor::~Monitor(){
	size_t physicalMonitorCount = m_physicalMonitors.size();
	for( auto physicalMonitor : m_physicalMonitors ){
		delete physicalMonitor;
	}
	BOOL bSuccess = DestroyPhysicalMonitors( (DWORD)physicalMonitorCount, m_pPhysicalMonitors );
	assert( bSuccess );//use getLastError if fail
	free( m_pPhysicalMonitors );
}

PhysicalMonitor* Monitor::getPhysical( int index ){
	PhysicalMonitor* pRetVal = nullptr;
	if( (size_t)index <= m_physicalMonitors.size() ){
		pRetVal = m_physicalMonitors[index];
	}
	return pRetVal;
}