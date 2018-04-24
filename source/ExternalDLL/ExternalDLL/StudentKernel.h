#include <vector>
#include "IntensityImageStudent.h"

#pragma once
class StudentKernel
{
public:
	StudentKernel(int width, int height, int shift, double factor, std::vector<std::vector<double>>);
	~StudentKernel();
	IntensityImageStudent convolute(IntensityImageStudent *image);


private:
	std::vector<std::vector<double>> kernel;
	int width =0, height=0, shift=0;
	double factor = 0;
};

