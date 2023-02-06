#include "myDataset.hpp"

myDataset::myDataset(const std::string & labels, const std::string & root)
{

}

void myDataset::readData(const std::string& path)
{
	//Stream to text file
	std::ifstream name_stream;
	name_stream.open(path);
	if (!name_stream.good()) {
		std::cout << "Could not open file: " << path << std::endl;
	}

	//load file names and labels to ram
	int* temp_idx = 0;
	while (name_stream.good())
	{
		std::string img_name;
		std::string label;
		int int_label;
		getline(name_stream, img_name, ';');
		getline(name_stream, label, '\n');
		int_label = std::stoi(label);
		data.push_back(make_tuple(img_name, int_label));
		temp_idx++;
	};
}

torch::optional<size_t> myDataset::size() const
{
	return data.size();
}

torch::data::Example<> myDataset::get(size_t index)
{
	cv::Mat in_img = cv::imread(std::get<0>(data[index]));
	cv::Mat img;

	cv::cvtColor(in_img, img, cv::COLOR_BGR2GRAY);
	img = img / 255.0;
	cv::Size size(128, 128);
	cv::resize(img, img, size);// set size to 128x128

	torch::Tensor tensor_image = torch::from_blob(img.data, { img.rows, img.cols,1}, at::kFloat);
	tensor_image = tensor_image.permute({ 2, 0, 1 });

	torch::Tensor label_tensor = torch::full({ 1 }, std::get<1>(data[index]));

	return { tensor_image, label_tensor };
}

myDataset::~myDataset()
{

}
