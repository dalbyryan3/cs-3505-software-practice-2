#include <iostream>
#include <string>
#include <vector>
// Can include background_image_splicer if needed to test
// #include "background_image_splicer.h"
#include "spliced_image_movie_generator.h"

using namespace std;
using namespace movie_builder;

int main()
{
	spliced_image_movie_generator movie_maker(NULL);
	cout << "spliced_image_movie_generator main completed" << endl;
	return 0;
}
