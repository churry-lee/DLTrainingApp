#ifndef _NETIMPL_HPP_
#define _NETIMPL_HPP_

#include "torch/torch.h"

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
	torch::Tensor Forward(torch::Tensor input);

};

#endif //_NETIMPL_HPP_
