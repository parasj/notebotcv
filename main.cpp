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

Handle<Value> ReadImage(const Arguments& args)
{
	HandleScope scope;
 
	if (args.Length() < 1) {
	  ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
	  return scope.Close(Undefined());
	}

	// if (!args[0]->IsString()) {
	//   ThrowException(Exception::TypeError(String::New("Wrong arguments")));
	//   return scope.Close(Undefined());
	// }


	cv::Mat image = cv::imread(*v8::String::Utf8Value(args[0]->ToString()), CV_LOAD_IMAGE_GRAYSCALE);
	// image = image > 128;

	cv::imwrite(*v8::String::Utf8Value(args[1]->ToString()), image );

	cv::namedWindow( "Image", CV_WINDOW_AUTOSIZE );
	cv::namedWindow( "GrayImage", CV_WINDOW_AUTOSIZE );
	cv::imshow( "Image", image );
	cv::imshow( "GrayImage", image > 50 );

	cv::waitKey(0);

	return scope.Close(String::New(*v8::String::Utf8Value(args[1]->ToString())));
}

void RegisterModule(Handle<Object> target)
{
	// target is the module object you see when require()ing the .node file.
	target->Set(String::NewSymbol("buildInformation"), FunctionTemplate::New(buildInformation)->GetFunction());
	target->Set(String::NewSymbol("add"), FunctionTemplate::New(Add)->GetFunction());
	target->Set(String::NewSymbol("readImage"), FunctionTemplate::New(ReadImage)->GetFunction());
}
 
NODE_MODULE(nodebotcv, RegisterModule);