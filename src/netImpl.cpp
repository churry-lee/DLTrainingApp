#include "netImpl.hpp"

NetImpl::NetImpl()
{
	this->conv1 = torch::nn::Conv2d(torch::nn::Conv2dOptions(1, 10, 5));
	this->conv2 = torch::nn::Conv2d(torch::nn::Conv2dOptions(10, 20, 5));
	this->conv2_drop = torch::nn::Dropout2d(torch::nn::Dropout2dOptions().p(0.4).inplace(true));

	this->fc1 = torch::nn::Linear(320, 50);
	this->fc2 = torch::nn::Linear(50, 10);

	register_module("conv1", conv1);
	register_module("conv2", conv2);
	register_module("conv2_drop", conv2_drop);
	register_module("fc1", fc1);
	register_module("fc2", fc2);
}

torch::Tensor NetImpl::Forward(torch::Tensor x)
{
	x = torch::max_pool2d(conv1->forward(x), {2, 2});
	x = torch::relu(x);

	x = torch::max_pool2d(conv2_drop->forward(conv2->forward(x)), {2, 2});
	x = torch::relu(x);

	x = x.view({-1, 320}); // reshape tensor, -1 means 'total_num / other dimension(320)' => torch.Size(1, 320), == x.view({1, 320})

	x = fc1->forward(x);
	x = torch::relu(x);

	x = torch::dropout(x, 0.5, is_training());

	x = fc2->forward(x);
	x = torch::softmax(x, 1);
	x = torch::log_softmax(x, 1);

	return x;
}
