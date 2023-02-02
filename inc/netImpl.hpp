#ifndef _NETIMPL_HPP_
#define _NETIMPL_HPP_

#include <vector>
#include <torch/torch.h>

struct LAYER
{
	torch::nn::Conv2d conv{ nullptr };
	torch::nn::BatchNorm2d batch_norm{ nullptr };
	torch::nn::MaxPool2d maxpool{ nullptr };
	torch::nn::AvgPool2d avgpool{ nullptr };
	torch::nn::Dropout2d dropout{ nullptr };
	torch::nn::Linear fc{ nullptr };
	torch::nn::ReLU relu{ nullptr };
	torch::nn::LeakyReLU leakyrelu{ nullptr };
	torch::nn::Softmax softmax{ nullptr };
};

class NetImpl :  public torch::nn::Module
{
private:
	torch::nn::Conv2d conv1{ nullptr };
	torch::nn::Conv2d conv2{ nullptr };     // convolution
	torch::nn::Dropout2d conv2_drop{ nullptr };    // dropout
	torch::nn::Linear fc1{ nullptr };         // fully connect
	torch::nn::Linear fc2{ nullptr };         // fully connect

public:
	NetImpl();
	NetImpl(std::vector<LAYER *> &layers);
	torch::Tensor Forward(torch::Tensor input);

};

#endif //_NETIMPL_HPP_
