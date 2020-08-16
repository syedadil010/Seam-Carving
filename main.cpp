// p2new.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;




// horizontl trivial seam is a seam through the center of the image
bool reduce_horizontal_seam_trivial(Mat& in_image, Mat& out_image) {

	// retrieve the dimensions of the new image
	int rows = in_image.rows - 1;
	int cols = in_image.cols;

	// create an image slighly smaller
	out_image = Mat(rows, cols, CV_8UC3);

	//populate the image
	int middle = in_image.rows / 2;

	for (int i = 0; i <= middle; ++i)
		for (int j = 0; j < cols; ++j) {
			Vec3b pixel = in_image.at<Vec3b>(i, j);

			/* at operator is r/w
			pixel[0] = 255;
			pixel[1] =255;
			pixel[2]=255;
			*/



			out_image.at<Vec3b>(i, j) = pixel;
		}

	for (int i = middle + 1; i < rows; ++i)
		for (int j = 0; j < cols; ++j) {
			Vec3b pixel = in_image.at<Vec3b>(i + 1, j);

			/* at operator is r/w
			 pixel[0] --> red
			 pixel[1] --> green
			 pixel[2] --> blue
			 */


			out_image.at<Vec3b>(i, j) = pixel;
		}

	return true;
}

// vertical trivial seam is a seam through the center of the image
bool reduce_vertical_seam_trivial(Mat& in_image, Mat& out_image) {
	// retrieve the dimensions of the new image
	int rows = in_image.rows;
	int cols = in_image.cols - 1;

	// create an image slighly smaller
	out_image = Mat(rows, cols, CV_8UC3);

	//populate the image
	int middle = in_image.cols / 2;

	for (int i = 0; i < rows; ++i)
		for (int j = 0; j <= middle; ++j) {
			Vec3b pixel = in_image.at<Vec3b>(i, j);

			/* at operator is r/w
			 pixel[0] --> red
			 pixel[1] --> green
			 pixel[2] --> blue
			 */


			out_image.at<Vec3b>(i, j) = pixel;
		}

	for (int i = 0; i < rows; ++i)
		for (int j = middle + 1; j < cols; ++j) {
			Vec3b pixel = in_image.at<Vec3b>(i, j + 1);

			/* at operator is r/w
			 pixel[0] --> red
			 pixel[1] --> green
			 pixel[2] --> blue
			 */


			out_image.at<Vec3b>(i, j) = pixel;
		}

	return true;
}

int calcenergy(Vec3b up, Vec3b down, Vec3b left, Vec3b right)
{
	int x = (down[0] - up[0]) * (down[0] - up[0]) + (down[1] - up[1]) * (down[1] - up[1]) + (down[2] - up[2]) * (down[2] - up[2]);
	int y = (left[0] - right[0]) * (left[0] - right[0]) + (left[1] - right[1]) * (left[1] - right[1]) + (left[2] - right[2]) * (left[2] - right[2]);
	return x + y;
}

vector<vector<int> > generateEnergy(Mat &in_image)
{
	int prows = in_image.rows;
	int pcolumns = in_image.cols;
	vector<vector<int> > PixelEnergy(prows, vector<int>(pcolumns));
	for (int i = 0; i < prows; i++)
	{
		for (int j = 0; j < pcolumns; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					PixelEnergy[i][j] = calcenergy(in_image.at<Vec3b>(prows - 1, j), in_image.at<Vec3b>(i + 1, j), in_image.at<Vec3b>(i, pcolumns - 1), in_image.at<Vec3b>(i, j + 1));

				}
				else if (j == pcolumns - 1)
				{
					PixelEnergy[i][j] = calcenergy(in_image.at<Vec3b>(prows - 1, j), in_image.at<Vec3b>(i + 1, j), in_image.at<Vec3b>(i, j - 1), in_image.at<Vec3b>(i, 0));
				}
				else
				{
					PixelEnergy[i][j] = calcenergy(in_image.at<Vec3b>(prows - 1, j), in_image.at<Vec3b>(i + 1, j), in_image.at<Vec3b>(i, j - 1), in_image.at<Vec3b>(i, j + 1));
				}
			}
			else if (i == prows - 1)
			{
				if (j == 0)
				{
					PixelEnergy[i][j] = calcenergy(in_image.at<Vec3b>(i - 1, j), in_image.at<Vec3b>(0, j), in_image.at<Vec3b>(i, pcolumns - 1), in_image.at<Vec3b>(i, j + 1));

				}
				else if (j == pcolumns - 1)
				{
					PixelEnergy[i][j] = calcenergy(in_image.at<Vec3b>(prows - 1, j), in_image.at<Vec3b>(0, j), in_image.at<Vec3b>(i, j - 1), in_image.at<Vec3b>(i, 0));
				}
				else
				{
					PixelEnergy[i][j] = calcenergy(in_image.at<Vec3b>(i - 1, j), in_image.at<Vec3b>(0, j), in_image.at<Vec3b>(i, j - 1), in_image.at<Vec3b>(i, j + 1));
				}
			}
			else
			{
				if (j == 0)
				{
					PixelEnergy[i][j] = calcenergy(in_image.at<Vec3b>(i - 1, j), in_image.at<Vec3b>(i + 1, j), in_image.at<Vec3b>(i, pcolumns - 1), in_image.at<Vec3b>(i, j + 1));
				}
				if (j == pcolumns - 1)
				{
					PixelEnergy[i][j] = calcenergy(in_image.at<Vec3b>(i - 1, j), in_image.at<Vec3b>(i + 1, j), in_image.at<Vec3b>(i, j - 1), in_image.at<Vec3b>(i, 0));
				}
				else
				{
					PixelEnergy[i][j] = calcenergy(in_image.at<Vec3b>(i - 1, j), in_image.at<Vec3b>(i + 1, j), in_image.at<Vec3b>(i, j - 1), in_image.at<Vec3b>(i, j + 1));
				}
			}

		}
	}
	return PixelEnergy;
}


// seam carves by removing trivial seams
bool seam_carving_trivial(Mat& in_image, int new_width, int new_height, Mat& out_image) {

	int prows = in_image.rows;
	int pcolumns = in_image.cols;
	//vector<vector<int>> PixelEnergy(prows,vector<int>(pcolumns));
	vector<vector<int>> PixelEnergy = generateEnergy(in_image);
	Mat iimage = in_image.clone();
	Mat oimage = in_image.clone();
	while (iimage.rows != new_height || iimage.cols != new_width) {
		// horizontal seam if needed
		if (iimage.rows > new_height) {
			reduce_horizontal_seam_trivial(iimage, oimage);
			iimage = oimage.clone();
		}

		if (iimage.cols > new_width) {
			reduce_vertical_seam_trivial(iimage, oimage);
			iimage = oimage.clone();
		}
	}

	out_image = oimage.clone();
	return true;
}



bool seam_carving(Mat& in_image, int new_width, int new_height, Mat& out_image) {

	// some sanity checks
	// Check 1 -> new_width <= in_image.cols
	if (new_width > in_image.cols) {
		cout << "Invalid request!!! new_width has to be smaller than the current size!" << endl;
		return false;
	}
	if (new_height > in_image.rows) {
		cout << "Invalid request!!! ne_height has to be smaller than the current size!" << endl;
		return false;
	}

	if (new_width <= 0) {
		cout << "Invalid request!!! new_width has to be positive!" << endl;
		return false;

	}

	if (new_height <= 0) {
		cout << "Invalid request!!! new_height has to be positive!" << endl;
		return false;

	}


	return seam_carving_trivial(in_image, new_width, new_height, out_image);

}
int main(int argc, char** argv)
{
	if (argc != 5)
	{
		cout << "Usage: ../sc input_image new_width new_height output_image" << endl;
		return -1;
	}

	// Load the input image
	// the image should be a 3 channel image by default but we will double check that in teh seam_carving
	Mat in_image;
	in_image = imread(argv[1]/*, CV_LOAD_IMAGE_COLOR*/);

	if (!in_image.data)
	{
		cout << "Could not load input image!!!" << endl;
		return -1;
	}

	if (in_image.channels() != 3) {
		cout << "Image does not have 3 channels!!! " << in_image.depth() << endl;
		return -1;
	}

	// get the new dimensions from the argument list
	int new_width = atoi(argv[2]);
	int new_height = atoi(argv[3]);

	// the output image
	Mat out_image;

	if (!seam_carving(in_image, new_width, new_height, out_image)) {
		return -1;
	}

	// write it on disk
	imwrite(argv[4], out_image);

	// also display them both

	namedWindow("Original image", WINDOW_AUTOSIZE);
	namedWindow("Seam Carved Image", WINDOW_AUTOSIZE);
	imshow("Original image", in_image);
	imshow("Seam Carved Image", out_image);
	waitKey(0);
	return 0;
}