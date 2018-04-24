#include "StudentPreProcessing.h"
#include "StudentKernel.h"
#include "ImageFactory.h"
#include "math.h"

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImageStudent threshold(const IntensityImageStudent *image, Intensity threshold) {

	IntensityImageStudent copy{ *image };

	for (int y = 0; y < copy.getHeight(); y++)
	{
		for (int x = 0; x < copy.getWidth(); x++)
		{
			int magnitude = (copy.getPixel(x, y) - 128);
			if (magnitude > 5) {
				copy.setPixel(x, y, 255);
			}
			else if (magnitude > 0) {
				copy.setPixel(x, y, magnitude * 20);
			}
			else {
				copy.setPixel(x, y, 0);
			}
			

		}
	}

	return copy;
}


IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {

	IntensityImageStudent copy{ image };
	std::vector<std::vector<double>> meanFilter = {
		std::vector<double> {1,1,1},
		std::vector<double> {1,1,1},
		std::vector<double> {1,1,1}
	};


	std::vector<std::vector<double>> Gaussian = {
		std::vector<double> {1,4,7,4,1},
		std::vector<double> {4,16,26,16,4},
		std::vector<double> {7,26,41,26,7},
		std::vector<double> {4,16,26,16,4},
		std::vector<double> {1,4,7,4,1},
	};

	StudentKernel kernelGaussian(Gaussian.size(), Gaussian.size(), 0, 0.00366300366, Gaussian);
	StudentKernel kernelMean(meanFilter.size(), meanFilter.size(), 0, 0.111, meanFilter);

	std::vector<std::vector<double>> Laplacian = {
		std::vector<double> {0,0,1,0,0},
		std::vector<double> {0,1,2,1,0},
		std::vector<double> {1,2,-16,2,1},
		std::vector<double> {0,1,2,1,0},
		std::vector<double> {0,0,1,0,0},
	};



	std::vector<std::vector<double>> Edge = {
		std::vector<double> {1, 1, 1},
		std::vector<double> {1, -8, 1},
		std::vector<double> {1 ,1 , 1}
	};
	
	StudentKernel kernelLap(Laplacian.size(), Laplacian.size(), 127, 1, Laplacian);
	StudentKernel kernelEdge(Edge.size(), Edge.size(), 127, 1, Edge);
	
	return ImageFactory::newIntensityImage(threshold(&kernelMean.convolute(&kernelEdge.convolute(&kernelGaussian.convolute(&kernelMean.convolute(&copy)))), 10));
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	return nullptr;
}


IntensityImageStudent StudentPreProcessing::zeroCrossings(const IntensityImageStudent *image) const
{

	IntensityImageStudent copy{ *image };

	int deltaValues[4][2] = {
		{ 1, 0 },
		{ 0, 1 },
		{ -1, 0 },
		{ 0, -1 }
	};

	for (int y = 0; y < copy.getHeight(); y++)
	{
		for (int x = 0; x < copy.getWidth(); x++)
		{
			std::vector<int> inverted;
			Intensity currentPixel = copy.getPixel(x, y);
			int Tpixel = currentPixel - 127;


			for (auto delta : deltaValues) 
			{
				int tx = x + delta[0];
				int ty = y + delta[1];

				if (x < 0 || y < 0 || x >= copy.getWidth() || y >= copy.getHeight()) continue;

				Intensity currentNeighbour = copy.getPixel(tx, ty);
				int TNeightbour = currentNeighbour - 127;

				if ((TNeightbour >= 0) && (Tpixel >= 0)) continue;
				
				if (TNeightbour < 0 && Tpixel < 0) continue;

				///////signing ongelijk
				
				inverted.push_back(abs(TNeightbour));

			}
			if (inverted.size() > 0) 
			{
				bool smallest = true;
				for (auto values : inverted) 
				{
					if (abs(Tpixel) > values)
					{
						smallest = false;
					}
				}

				if (smallest) 
				{
					copy.setPixel(x, y, 255);
				}
				else {
					copy.setPixel(x, y, 0);
				}
			}
			else {
				copy.setPixel(x, y, 0);
			}
		}
	}

	return IntensityImageStudent{ copy };
}