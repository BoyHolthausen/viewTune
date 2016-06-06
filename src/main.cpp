#include "monitor.h"
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

//#include <iostream>

int main(int argc, char* argv[] ){
	//std::cout << "The name used to start the program: " << argv[ 0 ]
	//	<< "\nArguments are:\n";
	//for (int n = 1; n < argc; n++)
	//	std::cout << n << ": " << argv[ n ] << '\n';

	if( argc > 1 ){
		Monitor::initMonitors();
		if( strcmp( argv[1], "setBrightness" ) == 0 ){
			if( argc == 5 ){
				unsigned int monitorIndex = atoi( argv[2] );
				unsigned int physicalIndex = atoi( argv[3] );
				unsigned int newBrightness = atoi( argv[4] );
				Monitor* pMonitor = nullptr;
				if( monitorIndex <= Monitor::s_monitors.size() ){
					pMonitor = Monitor::s_monitors[monitorIndex];
				}
				if( pMonitor ){
					PhysicalMonitor* pPhysical = pMonitor->getPhysical( physicalIndex );
					if( pPhysical ){
						pPhysical->setBrightness( newBrightness );
					}
				}
			}
		}else if( strcmp( argv[1], "print" ) == 0 ){
			Monitor::print();
		}
	}

	return 0;
}