#ifndef _MYDATASET_HPP_
#define _MYDATASET_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <tuple>

#include <torch/torch.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class myDataset : public torch::data::Dataset<myDataset>
{
public:
	myDataset(const std::string & labels, const std::string & root);
	~myDataset() override;

	void readData(const std::string & path);

	torch::data::Example<> get(size_t index) override;
	[[nodiscard]] torch::optional<size_t> size() const override;
private:
	std::vector<std::tuple<std::string, int>> data;

};

#endif //_MYDATASET_HPP_
