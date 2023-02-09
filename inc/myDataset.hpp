#ifndef _MYDATASET_HPP_
#define _MYDATASET_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <tuple>

#include <spdlog/spdlog.h>

#include <torch/torch.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class myDataset : public torch::data::Dataset<myDataset>
{
public:
	myDataset(const std::string & label_path, const std::string & img_path);
	~myDataset() override;

	void readData(const std::string & path);

	torch::data::Example<> get(size_t index) override;
	torch::optional<size_t> size() const override;
	std::vector<std::tuple<std::string, int>> data;
private:
	std::string m_label_path;
	std::string m_img_path;

};

#endif //_MYDATASET_HPP_
