#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\..\VAS\ComputerVisionFrameworkNative\PathImprover.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace cvf;
using namespace cv;

namespace ComputerVisionFrameworkNativeTest
{		
	TEST_CLASS(PathImproverTests)
	{
	public:
		
		TEST_METHOD(PathImproverFourLinealIncrAndOneZero_Test)
		{
			PathImprover pi;
			
			pi.addPoint( Point2f(0,0), 0 );
			pi.addPoint( Point2f(1,1), 100 );
			pi.addPoint( Point2f(2,2), 200 );
			pi.addPoint( Point2f(3,3), 300 );
			pi.addPoint( Point2f(3,3), 400 );

			Point2f nextPt;

			pi.getNextPoint( 400, nextPt );

			Assert::AreEqual( nextPt.x, 3.25f, 0.0001f );
		}

	};
}