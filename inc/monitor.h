#pragma once

#include <vector>

#include <windows.h>
#include <PhysicalMonitorEnumerationAPI.h>
#include <lowlevelmonitorconfigurationapi.h>

#include "physicalMonitor.h"

class Monitor{
public:
	static std::vector<Monitor*> s_monitors;
	static void initMonitors();
	static void print();
	
	PhysicalMonitor* getPhysical( int index );
private:
	Monitor( HMONITOR handle, int width, int height );
	~Monitor();

	HMONITOR m_handle;
	int m_width, m_height;
	std::vector<PhysicalMonitor*> m_physicalMonitors;

	LPPHYSICAL_MONITOR m_pPhysicalMonitors;
	friend BOOL CALLBACK MonitorEnumProc(
		_In_ HMONITOR hMonitor,
		_In_ HDC      hdcMonitor,
		_In_ LPRECT   lprcMonitor,
		_In_ LPARAM   dwData	
	);
};