// SimpleAppComputerVisionFrameworkNative.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "ComputerVisionManager.h"

#include <memory>
#include <iostream>
#include <string>

using namespace std;
using namespace cvf;

#include "StrongCornersFeatureTrackerGPU.h"
#include "UserInterfaceSimpleAnchor.h"
#include "SingleFeatureTrackerCtrl.h"
#include "SURFFeatureTrackerCPU.h"
#include "HistShotBoundaryDetector.h"



int _tmain(int argc, _TCHAR* argv[])
{
	int device = 0;
	string fileName = "MotoGPSlowMotion.avi";
	bool bFromFile = true;;

	for (int i = 0; i < argc; i++) {
		std::wstring ws = argv[i];
		if (ws == _T("-d"))
		{
			bFromFile = false;
			i++;
			if (i < argc) {
				ws = argv[i];
				device = stoi(ws);
			}
		}

		if (ws == _T("-f"))
		{
			i++;
			if (i < argc) {
				ws = argv[i];
				fileName.assign( ws.begin(), ws.end());
			}
		}

	}


	//shared_ptr<HistShotBoundaryDetector> ptrFrame = make_shared<HistShotBoundaryDetector>( cv::Rect(350,100,75,75) );
	shared_ptr<SURFFeatureTrackerCPU> ptrFrame = make_shared<SURFFeatureTrackerCPU>( cv::Rect(350,100,75,75), 3 );
	//shared_ptr<StrongCornersFeatureTrackerGPU> ptrFrame = make_shared<StrongCornersFeatureTrackerGPU>( cv::Rect(350,100,75,75), 3 );
	shared_ptr<UserInterfaceSimpleAnchor> ui = make_shared<UserInterfaceSimpleAnchor>( ptrFrame );
	shared_ptr<SingleFeatureTrackerCtrl> singleFeatureTrackerCtrl = make_shared<SingleFeatureTrackerCtrl>( ptrFrame, ui );
	
	
	cvf::ComputerVisionManager cm;

	cm.setFrameProcessorCtrl( singleFeatureTrackerCtrl );

	if (bFromFile) {
		cm.startVideoProcessorFromFile(fileName);
	}
	else {
		cm.startVideoProcessorFromDevice(device);
	}
	
	cm.join();

	return 0;
}

