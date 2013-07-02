#ifndef OUTPUTFORMATTYPES_H
#define OUTPUTFORMATTYPES_H

class OutputFeaturePoint {
	public:
		OutputFeaturePoint();
		OutputFeaturePoint(double x, double y, double z);
		void set(double x, double y, double z);
		double get_X();
		double get_Y();
		double get_Z();
	private:
		double X;
		double Y;
		double Z;
};

class OutputFeatureLine {
	public:
		OutputFeatureLine();
		OutputFeatureLine(double x1, double y1, double z1, double x2, double y2, double z2);
		void set(double x1, double y1, double z1, double x2, double y2, double z2);
		double get_X1();
		double get_Y1();
		double get_Z1();
		double get_X2();
		double get_Y2();
		double get_Z2();
	private:
		double X1;
		double Y1;
		double X2;
		double Y2;
		double Z1;
		double Z2;
};

#endif
