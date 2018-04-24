#include "IntensityImageStudent.h"

IntensityImageStudent::IntensityImageStudent() : IntensityImage() {
	pixels = new Intensity[0];
}

IntensityImageStudent::IntensityImageStudent(const IntensityImageStudent &copy) : IntensityImage{ copy.getWidth(), copy.getHeight() } {
	pixels = new Intensity[copy.getWidth() * copy.getHeight()];

	for (int i = 0; i < this->getWidth() * this->getHeight(); i++) 
		pixels[i] = copy.getPixel(i);
}

IntensityImageStudent::IntensityImageStudent(const IntensityImage &other) : IntensityImage{ other.getWidth(), other.getHeight() } {
	pixels = new Intensity[other.getWidth() * other.getHeight()];

	for (int i = 0; i < this->getWidth() * this->getHeight(); i++) 
		pixels[i] = other.getPixel(i);
}

IntensityImageStudent::IntensityImageStudent(const int width, const int height) : IntensityImage(width, height) {
	pixels = new Intensity[width * height]();
}

IntensityImageStudent::~IntensityImageStudent() {
	//int throwError = 0, e = 1 / throwError;
	//implement destructor
}

void IntensityImageStudent::set(const int width, const int height) {
	
	IntensityImage::set(width, height);
	pixels = new Intensity[width * height];
}

void IntensityImageStudent::set(const IntensityImageStudent &other) {
	IntensityImage::set(other.getWidth(), other.getHeight());

	for (int i = 0; i < this->getHeight()*this->getWidth(); i++) 
		pixels[i] = other.getPixel(i);
}

void IntensityImageStudent::setPixel(int x, int y, Intensity pixel) {
	if (!(x < 0 || x >= getWidth() || y < 0 || y >= getHeight()))
		pixels[y * this->getWidth() + x] = pixel;
}

void IntensityImageStudent::setPixel(int i, Intensity pixel) {
	if (!(i < 0 || i >= getHeight() * getWidth())) 
		pixels[i] = pixel;

}

Intensity IntensityImageStudent::getPixel(int x, int y) const {
	if (x < 0)
		x = 0;

	if (y < 0)
		y = 0;

	if (x >= getWidth())
		x = getWidth() - 1;
	
	if (y >= getHeight())
		y = getHeight() - 1;
	
	return pixels[y * this->getWidth() + x];
}

Intensity IntensityImageStudent::getPixel(int i) const {
	if (i < 0)
		i = 0;

	if (i >= getHeight() * getWidth())
		i = getHeight() * getWidth() - 1;
	
	return pixels[i];
}