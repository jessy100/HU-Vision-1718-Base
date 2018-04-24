#include "RGBImageStudent.h"

RGBImageStudent::RGBImageStudent() : RGBImage() {
	pixels = new RGB[0];
}

RGBImageStudent::RGBImageStudent(const RGBImageStudent &other) : RGBImage{ other.getWidth(), other.getHeight() } {
	pixels = new RGB[this->getWidth() * this->getHeight()];

	for (int i = 0; i < this->getHeight() * this->getWidth(); i++)
		pixels[i] = other.getPixel(i);
}

RGBImageStudent::RGBImageStudent(const int width, const int height) : RGBImage(width, height) {
	pixels = new RGB[width * height];
}

RGBImageStudent::~RGBImageStudent() {
	//implenteer destructor........
}

void RGBImageStudent::set(const int width, const int height) {
	RGBImage::set(width, height);
	pixels = new RGB[width * height];
}

void RGBImageStudent::set(const RGBImageStudent &other) {

	RGBImage::set(other.getWidth(), other.getHeight());

	for (int i = 0; i < this->getHeight() * this->getWidth(); i++)
		pixels[i] = other.getPixel(i);
}

void RGBImageStudent::setPixel(int x, int y, RGB pixel) {
	if (!(x < 0 || x >= getWidth() || y < 0 || y >= getHeight()))
		pixels[y * this->getWidth() + x] = pixel;
}

void RGBImageStudent::setPixel(int i, RGB pixel) {
	if (!(i < 0 || i >= getHeight() * getWidth()))
		pixels[i] = pixel;
}

RGB RGBImageStudent::getPixel(int x, int y) const {
	if (x < 0)
		x = 0;

	if (y < 0)
		y = 0;

	if (x >= getWidth())
		x = getWidth() - 1;

	if (y >= getHeight())
		y = getHeight() - 1;

	return pixels[y*this->getWidth() + x];
}

RGB RGBImageStudent::getPixel(int i) const {
	if (i < 0)
		i = 0;

	if (i >= getHeight() * getWidth())
		i = getHeight() * getWidth() - 1;

	return pixels[i];
}