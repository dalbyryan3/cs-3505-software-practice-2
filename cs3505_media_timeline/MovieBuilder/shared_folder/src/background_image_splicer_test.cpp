#include <iostream>
#include <string>
#include <vector>
#include "background_image_splicer.h"

using namespace std;
using namespace movie_builder;

int main()
{
	string background_image = "./test_images/background.jpg";
	vector<string> images{"./test_images/120520_Coco (feat. DaBaby).jpg","./test_images/120520_Wonder.jpg","./test_images/120420_MSFTTimeSeriesStockData.png"};
	string target_image = "./test_images/output.jpg";
	background_image_splicer splicer = background_image_splicer(720,2880,background_image, images);
	splicer.splice_background_and_images(target_image);

	cout << "background_image_splicer main completed" << endl;
	return 0;
}
