// SimpleAppComputerVisionFrameworkNative.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "ComputerVisionManager.h"


int _tmain(int argc, _TCHAR* argv[])
{
	
	cvf::ComputerVisionManager cm;
	cm.startVideoProcessor();

	cm.join();

	return 0;
}

