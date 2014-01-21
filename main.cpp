#include <stdio.h>
#include <iostream>
#include <node.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <string>
 
using namespace v8;
 
// This function returns a JavaScript number that is either 0 or 1.
Handle<Value> buildInformation(const Arguments& args)
{
	// At the top of every function that uses anything about v8, include a
	// definition like this. It ensures that any v8 handles you create in that
	// function are properly cleaned up. If you see memory rising in your
	// application, chances are that a scope isn't properly cleaned up.
	HandleScope scope;
 
	// When returning a value from a function, make sure to wrap it in
	// scope.Close(). This ensures that the handle stays valid after the current
	// scope (declared with the previous statement) is cleaned up.
	// std::cout << String::New(cv::getBuildInformation().c_str())
	printf("    c++: %s\n", "test");
	printf("    C++: number of CPUs: %i\n", cv::getNumberOfCPUs());

	return scope.Close
	(
		// Creating a new JavaScript integer is as simple as passing a C int
		// (technically a int32_t) to this function.
		String::New(cv::getBuildInformation().c_str())
		// String::New("test")
		// String::NewSymbol("hello");
	);
}

// Test arguments
Handle<Value> Add(const Arguments& args)
{
	HandleScope scope;
 
	if (args.Length() < 2) {
	  ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
	  return scope.Close(Undefined());
	}

	if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
	  ThrowException(Exception::TypeError(String::New("Wrong arguments")));
	  return scope.Close(Undefined());
	}

	Local<Number> num = Number::New(args[0]->NumberValue() +
	    args[1]->NumberValue());
	return scope.Close(num);
}

// call houghLines("filein.png", "fileout.png")
Handle<Value> HoughLines(const Arguments& args)
{
	HandleScope scope;

	cv::Mat src = cv::imread(*v8::String::Utf8Value(args[0]->ToString()), 0);

	cv::Mat dst, cdst;
	cv::Canny(src, dst, 50, 200, 3);
	// cv::cvtColor(dst, cdst, cv::CV_GRAY2BGR, 1);
	cdst = dst;

	#if 0
	 std::vector<Vec2f> lines;
	 cv::HoughLines(dst, lines, 1, CV_PI/180, 100, 0, 0 );

	 for( size_t i = 0; i < lines.size(); i++ )
	 {
	    float rho = lines[i][0], theta = lines[i][1];
	    Point pt1, pt2;
	    double a = cos(theta), b = sin(theta);
	    double x0 = a*rho, y0 = b*rho;
	    pt1.x = cvRound(x0 + 1000*(-b));
	    pt1.y = cvRound(y0 + 1000*(a));
	    pt2.x = cvRound(x0 - 1000*(-b));
	    pt2.y = cvRound(y0 - 1000*(a));
	    line( cdst, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
	 }
	#else
	 std::vector<cv::Vec4i> lines;
	 cv::HoughLinesP(dst, lines, 1, CV_PI/180, 50, 50, 10 );
	 for( size_t i = 0; i < lines.size(); i++ )
	 {
	   cv::Vec4i l = lines[i];
	   cv::line( cdst, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0,0,255), 3, CV_AA);
	 }
	#endif
	// cv::imshow("source", src);
	// cv::imshow("detected lines", cdst);

	// cv::waitKey();

	cv::imwrite(*v8::String::Utf8Value(args[1]->ToString()), cdst);

	return scope.Close(String::New(*v8::String::Utf8Value(args[1]->ToString())));
}

void RegisterModule(Handle<Object> target)
{
	// target is the module object you see when require()ing the .node file.
	target->Set(String::NewSymbol("buildInformation"), FunctionTemplate::New(buildInformation)->GetFunction());
	target->Set(String::NewSymbol("add"), FunctionTemplate::New(Add)->GetFunction());
	target->Set(String::NewSymbol("houghLines"), FunctionTemplate::New(HoughLines)->GetFunction());
}
 
NODE_MODULE(nodebotcv, RegisterModule);