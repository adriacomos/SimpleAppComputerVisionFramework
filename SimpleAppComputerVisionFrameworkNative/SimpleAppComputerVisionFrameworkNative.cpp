// SimpleAppComputerVisionFrameworkNative.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "ComputerVisionManager.h"

#include <memory>

using namespace std;
using namespace cvf;

#include "StrongCornersFeatureTrackerGPU.h"
#include "UserInterfaceSimpleAnchor.h"
#include "SingleFeatureTrackerCtrl.h"
#include "SURFFeatureTrackerCPU.h"



int _tmain(int argc, _TCHAR* argv[])
{
	//shared_ptr<SURFFeatureStaticMaskTracker> ptrFrame = make_shared<SURFFeatureStaticMaskTracker>( cv::Rect(350,100,75,75), 3 );
	shared_ptr<SURFFeatureTrackerCPU> ptrFrame = make_shared<SURFFeatureTrackerCPU>( cv::Rect(350,100,75,75), 3 );
	//shared_ptr<StrongCornersFeatureTrackerGPU> ptrFrame = make_shared<StrongCornersFeatureTrackerGPU>( cv::Rect(350,100,75,75), 3 );
	shared_ptr<UserInterfaceSimpleAnchor> ui = make_shared<UserInterfaceSimpleAnchor>( ptrFrame );
	shared_ptr<SingleFeatureTrackerCtrl> singleFeatureTrackerCtrl = make_shared<SingleFeatureTrackerCtrl>( ptrFrame, ui );
	
	cvf::ComputerVisionManager cm;

	cm.setFrameProcessorCtrl( singleFeatureTrackerCtrl );

	cm.startVideoProcessorFromFile("MotoGPSlowMotion.avi");

	cm.join();

	return 0;
}

