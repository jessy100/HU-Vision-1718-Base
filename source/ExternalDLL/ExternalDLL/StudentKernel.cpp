#include "StudentKernel.h"

StudentKernel::StudentKernel(int width,int height, int shift, double factor, std::vector<std::vector<double>> kernel)
{
	this->width = width;
	this->height = height;
	this->kernel = kernel;
	this->shift = shift;
	this->factor = factor;
}

StudentKernel::~StudentKernel()
{
}

IntensityImageStudent StudentKernel::convolute(IntensityImageStudent * image)
{
	IntensityImageStudent tempImg{ *image };

	//for1
	for (int y = 0; y < tempImg.getHeight(); y++) 
	{
		//for2
		for (int x = 0; x < tempImg.getWidth(); x++) 
		{
			double temp = 0;
			//for3
			for (int yKernel = 0; yKernel < kernel.size(); yKernel++) 
			{
				//for4
				for (int xKernel = 0; xKernel < kernel.at(yKernel).size(); xKernel++) {
					int dx = xKernel - (this->width / 2);
					int dy = yKernel - (this->height / 2);

					Intensity pixelValue = image->getPixel(x + dx, y + dy);
					temp += (pixelValue * kernel.at(yKernel).at(xKernel));
				}
			}
			temp = (temp*factor + shift);
			tempImg.setPixel(x, y, temp);
		}
	}
	return tempImg;
}



