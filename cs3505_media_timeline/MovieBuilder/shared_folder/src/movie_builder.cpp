#include <filesystem>
#include <vector>
#include <fstream>
#include "background_image_splicer.h"
#include "spliced_image_movie_generator.h"


using namespace std;
using namespace movie_builder;

int main(int argc, char *argv[])
{
	ofstream output_file;
	output_file.open(("./output/movie_builder_output_information.txt"));

	if(argc != 4)
	{
		output_file << "Command should have an ending command line argument in MMddyy format to specify day to generate the movie for that specific day" << endl;
		output_file.close();
		return 0;
	}
	string input_directory = string(argv[1]);
	string output_directory = string(argv[2]);
	string date_target = string(argv[3]);
	if(date_target.length() != 6)
	{
		output_file << "Command should have an ending command line argument in MMddyy format to specify day to generate the movie for that specific day" << endl;
		output_file.close();
		return 0;
	}
	vector<string> images_to_splice;
	for (const auto & entry : filesystem::directory_iterator(input_directory))
	{
		string current_path = entry.path();
		string current_filename = filesystem::path(current_path).filename();
		if(date_target != current_filename.substr(0,6))
		{
			continue;
		}

		images_to_splice.push_back(current_path);
	}

	if(images_to_splice.size() == 0)
	{
		output_file << "There were no images for the specified day " << date_target << endl;
		output_file.close();
		return 0;
	}

	try
	{
		string background_image = "./test_images/background.jpg";
		string target_temp_spliced_image = "./test_images/out.jpg";
		background_image_splicer splicer = background_image_splicer(720, 3600, background_image, images_to_splice);
		const AVFrame *spliced_background_image = splicer.splice_background_and_images(target_temp_spliced_image);
		spliced_image_movie_generator movie_maker(spliced_background_image);
		movie_maker.make_movie(1440);
		output_file << "Movie successfully created" << endl;
	}
	catch(...)
	{
		output_file.close();
		return 0;
	}
	
	output_file.close();
	return 0;
}


