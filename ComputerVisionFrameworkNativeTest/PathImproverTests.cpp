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
		
		TEST_METHOD(PathImproverFourLinealIncr_Test)
		{
			PathImprover pi;
			
			pi.addPoint( Point2f(0,0), 0 );
			pi.addPoint( Point2f(1,1), 100 );
			pi.addPoint( Point2f(2,2), 200 );
			pi.addPoint( Point2f(3,3), 300 );

			Point2f nextPt;

			pi.getNextPoint( 400, nextPt );

			Assert::AreEqual( nextPt.x, 4.0f, 0.0001f );
		}


		TEST_METHOD(PathImproverTwoNonLinealIncr_Test)
		{
			PathImprover pi;
			
			pi.addPoint( Point2f(0,0), 0 );
			pi.addPoint( Point2f(3,3), 300 );

			Point2f nextPt;

			pi.getNextPoint( 400, nextPt );

			Assert::AreEqual( nextPt.x, 4.0f, 0.0001f );
		}


	};
}