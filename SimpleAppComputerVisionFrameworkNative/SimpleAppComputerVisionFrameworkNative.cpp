// SimpleAppComputerVisionFrameworkNative.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "ComputerVisionManager.h"

#include <memory>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
using namespace cvf;

#include "StrongCornersFeatureTrackerGPU.h"
#include "UserInterfaceSimpleAnchor.h"
#include "SingleFeatureTrackerCtrl.h"
#include "SingleFeatureTrackerSBDCtrl.h"
#include "SURFFeatureTrackerCPU.h"
#include "HistShotBoundaryDetector.h"


void initSingleTracker( cvf::ComputerVisionManager &cm )
{
	shared_ptr<SURFFeatureTrackerCPU> ptrFrame = make_shared<SURFFeatureTrackerCPU>( cv::Rect(350,100,75,75), 3 );
	//shared_ptr<StrongCornersFeatureTrackerGPU> ptrFrame = make_shared<StrongCornersFeatureTrackerGPU>( cv::Rect(350,100,75,75), 3 );
	shared_ptr<SingleFeatureTrackerCtrl> singleFeatureTrackerCtrl = make_shared<SingleFeatureTrackerCtrl>( ptrFrame );
	shared_ptr<UserInterfaceSimpleAnchor> ui = make_shared<UserInterfaceSimpleAnchor>( singleFeatureTrackerCtrl );
	singleFeatureTrackerCtrl->setInterface(ui),

	cm.setFrameProcessorCtrl( singleFeatureTrackerCtrl );

	cout << "SBD inactive" << endl;
}

void initSingleTrackerWSBD( cvf::ComputerVisionManager &cm, double changeShotThreshold )
{
	shared_ptr<SURFFeatureTrackerCPU> ptrFrame = make_shared<SURFFeatureTrackerCPU>( cv::Rect(350,100,75,75), 3 );
	//shared_ptr<StrongCornersFeatureTrackerGPU> ptrFrame = make_shared<StrongCornersFeatureTrackerGPU>( cv::Rect(350,100,75,75), 3 );
	shared_ptr<SingleFeatureTrackerSBDCtrl> singleFeatureTrackerCtrl = make_shared<SingleFeatureTrackerSBDCtrl>( ptrFrame, changeShotThreshold );
	shared_ptr<UserInterfaceSimpleAnchor> ui = make_shared<UserInterfaceSimpleAnchor>( singleFeatureTrackerCtrl );
	singleFeatureTrackerCtrl->setInterface(ui),
		
	cm.setFrameProcessorCtrl( singleFeatureTrackerCtrl );

	cout << "SBD Active with threshold: " << fixed << setprecision(2) << changeShotThreshold << endl;

}




int _tmain(int argc, _TCHAR* argv[])
{
	int device = 0;
	string fileName = "MotoGPSlowMotion.avi";
	bool bFromFile = true;
	bool bSBD = false;
	double SBDThreshold = 0.2;

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

		if (ws == _T("-sbd"))		{
			bSBD = true;

			i++;
			if (i < argc) {
				ws = argv[i];
				SBDThreshold = stod( ws );
			}
		}
	}

	cvf::ComputerVisionManager cm;

	if (bSBD)
		initSingleTrackerWSBD( cm, SBDThreshold );
	else
		initSingleTracker( cm );

	
	
	if (bFromFile) {
		cm.startVideoProcessorFromFile(fileName);
	}
	else {
		cm.startVideoProcessorFromDevice(device);
	}
	
	cm.join();

	return 0;
}

