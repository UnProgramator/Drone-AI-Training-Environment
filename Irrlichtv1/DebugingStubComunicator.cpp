#include "DebugingStubComunicator.h"
#include <string.h>
#include <iostream>
#include <conio.h>

void DebugingStubComunicator::init_parser(int elementCount)
{
}

void DebugingStubComunicator::parse_double(const char* name, const double value)
{
	if (!strcmp(name, "altimeter"))
		y = value;
	else if (!strcmp(name, "duration"))
		read_time = value;
	else if (!strcmp(name, "distance-f")) {
		if (for_dist > value)
			for_dist = value;
	}
	else if (!strcmp(name, "distance-fl")) {
		if (for_dist > value)
			for_dist = value;
	}
	else if (!strcmp(name, "distance-fr")) {
		if (for_dist > value)
			for_dist = value;
	}
}

void DebugingStubComunicator::parse_double_array(const char* name, const std::vector<double>& value)
{
	
	if (!strcmp(name, "gps")) {
		x = value[1];
		z = -value[0];
	}
	else if (!strcmp(name, "destinantion")) {
		xd = value[0];
		yd = value[1];
		zd = value[2];
	}
}

using namespace irr;
using namespace core;

default_ReturnedValueFromStript DebugingStubComunicator::call()
{
	default_ReturnedValueFromStript rv = { 0,0,0 };
	vector3df desired = vector3df(xd - x, 0, zd - z).normalize();
	vector3df forward = comandedDrone->getForwardVector().normalize();

#define cos_5 0.99619469809174553229501040247389

	if (abs(x - xd) < 10 && abs(z - zd) < 10) { // i treat if it reach destination
		if (y - yd > 10.f) {
			rv.up = -1;
		}
		else if (y - yd < -10.f) {
			rv.up = 1;
		}
		return rv;
	}

	// if i am at an angle bigger then 5 degree than i turn, else i walk
	// if cos(dir,desired)<cos(5 degree) => angle(desired, dir)>5 degree
	float cos_angle = desired.dotProduct(forward);
	if (! (cos_angle > cos_5)) {
		float val = desired.crossProduct(forward).Y;
		std::cout << val;
		if (val <= 0)
			rv.rotation_angle = 1;
		else
			rv.rotation_angle = -1;
		return rv;
	}

	if (for_dist < 5.f) {
		crt_time = 0.5f;
		rv.up = 1;
		for_dist = 10000000.f;
	}
	else if (crt_time > 0.01) {
		crt_time -= read_time;
		rv.up = 1;
	}
	else
		rv.forward = 1;

	return rv;
}

void DebugingStubComunicator::give_feedback(const default_FeedbackType& newParams)
{
}
