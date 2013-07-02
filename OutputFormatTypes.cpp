#include "OutputFormatTypes.h"

// Point:
OutputFeaturePoint::OutputFeaturePoint() {
	this->X = -1;
	this->Y = -1;
	this->Z = -1;
}


OutputFeaturePoint::OutputFeaturePoint(double x, double y, double z) {
	this->X = x;
	this->Y = y;
	this->Z = z;
}

void OutputFeaturePoint::set(double x, double y, double z) {
	this->X = x;
	this->Y = y;
	this->Z = z;
}

double OutputFeaturePoint::get_X() {
	return this->X;
}

double OutputFeaturePoint::get_Y() {
	return this->Y;
}

double OutputFeaturePoint::get_Z() {
	return this->Z;
}

// Line:
OutputFeatureLine::OutputFeatureLine() {
	this->X1 = this->X2 = -1;
	this->Y1 = this->Y2 = -1;
	this->Z1 = this->Z2 = -1;
}


OutputFeatureLine::OutputFeatureLine(double x1, double y1, double z1, double x2, double y2, double z2) {
	this->X1 = x1;
	this->Y1 = y1;
	this->Z1 = z1;
	this->X2 = x2;
	this->Y2 = y2;
	this->Z2 = z2;
}

void OutputFeatureLine::set(double x1, double y1, double z1, double x2, double y2, double z2) {
	this->X1 = x1;
	this->Y1 = y1;
	this->Z1 = z1;
	this->X2 = x2;
	this->Y2 = y2;
	this->Z2 = z2;
}

double OutputFeatureLine::get_X1() {
	return this->X1;
}

double OutputFeatureLine::get_Y1() {
	return this->Y1;
}

double OutputFeatureLine::get_Z1() {
	return this->Z1;
}

double OutputFeatureLine::get_X2() {
	return this->X2;
}

double OutputFeatureLine::get_Y2() {
	return this->Y2;
}

double OutputFeatureLine::get_Z2() {
	return this->Z2;
}
