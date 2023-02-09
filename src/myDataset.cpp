#include "myDataset.hpp"

myDataset::myDataset(const std::string & label_path, const std::string & img_path)
{
	SPDLOG_INFO("Make custom Dataset object");
	this->m_label_path = label_path;
	this->m_img_path = img_path;

	data.clear();
	readData(m_label_path);
}

void myDataset::readData(const std::string& path)
{
	std::ifstream fin;
	std::string file_name, label;

	fin.open(path, std::ios::in);
	if (!fin.good())
		SPDLOG_ERROR("Could not open file: " + path);

	while (!fin.eof())
	{
		getline(fin, file_name, ',');
		getline(fin, label, ',');
		getline(fin, label, ',');
		getline(fin, label, ',');
		getline(fin, label, '\n');

		data.push_back({file_name, std::stoi(label)});
	};
	data.erase(data.end()-1);
}

torch::optional<size_t> myDataset::size() const
{
	return data.size();
}

torch::data::Example<> myDataset::get(size_t index)
{
	cv::Mat in_img = cv::imread(m_img_path + std::get<0>(data[index]) + ".jpg");
	cv::Mat img;

	cv::cvtColor(in_img, img, cv::COLOR_BGR2GRAY);
	img = img / 255.0;
	cv::Size size(128, 128);
	cv::resize(img, img, size);// set size to 128x128

	torch::Tensor tensor_image = torch::from_blob(img.data, {img.rows, img.cols, 1}, at::kFloat);
	tensor_image = tensor_image.permute({ 2, 0, 1 });

	torch::Tensor label_tensor = torch::full({ 1 }, std::get<1>(data[index]));

	return { tensor_image, label_tensor };
}

myDataset::~myDataset()
{

}
