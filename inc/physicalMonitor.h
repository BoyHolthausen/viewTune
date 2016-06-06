#pragma once
#include <string>

#include <windows.h>
#include <PhysicalMonitorEnumerationAPI.h>
#include <lowlevelmonitorconfigurationapi.h>

class PhysicalMonitor{
public:
	void print();
	void setBrightness( int brightness );

private:
	PhysicalMonitor( LPPHYSICAL_MONITOR pPhysicalMonitor );
	~PhysicalMonitor();

	friend class Monitor;

	LPPHYSICAL_MONITOR m_pPhysicalMonitor;
	std::string m_name;
};
