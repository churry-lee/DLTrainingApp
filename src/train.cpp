#include "train.hpp"

template <typename DataLoader>
Train::Train(size_t epoch, NetImpl & model, torch::Device device, DataLoader & data_loader, torch::optim::Optimizer & optimizer, size_t dataset_size)
{
	this->train(epoch, model, device, data_loader, dataset_size);
}

Train::~Train()
{

}

template <typename DataLoader>
void Train::train(size_t epoch, NetImpl & model, torch::Device device, DataLoader & data_loader, torch::optim::Optimizer & optimizer, size_t dataset_size)
{
	model.train();
	size_t batch_index = 0;

	for (auto & batch : data_loader)
	{
		auto data = batch.data.to(device);
		auto targets = batch.target.to(device);
		optimizer.zero_grad();

		auto output = model.Forward(data);
		auto loss = torch::nll_loss(output, targets);
		AT_ASSERT(!std::isnan(loss.template item<float>()));

		loss.backward();
		optimizer.step();

		if (batch_index++ % LOG_INTERVAL == 0)
			printf("\rTrain Epoch: %ld [%5ld/%5ld] Loss: %.4f", epoch, long(batch_index * batch.data.size(0)), dataset_size, loss.template item<float>());
	}
}

//template <typename DataLoader>
//void test(NetImpl & model, torch::Device device, DataLoader & data_loader, size_t dataset_size)
//{
//	torch::NoGradGuard no_grad;
//	model.eval();
//
//	double test_loss = 0;
//	int32_t correct = 0;
//	for (const auto & batch : data_loader)
//	{
//		auto data = batch.data.to(device);
//		auto targets = batch.target.to(device);
//		auto output = model.Forward(data);
//
//		test_loss += torch::nll_loss(output, targets, {}, torch::Reduction::Sum).template item<float>();
//		auto pred = output.argmax(1);
//		correct += pred.eq(targets).sum().template item<int64_t>();
//	}
//
//	test_loss /= dataset_size;
//	printf("\nTest set: Average loss: %.4f | Accuracy: %.3f\n", test_loss, static_cast<double>(correct) / dataset_size);
//}


//int train()
//{
//	try
//	{
//		torch::manual_seed(1);
//
//		torch::DeviceType device_type;
//		if (torch::cuda::is_available())
//		{
//			std::cout << "CUDA available! Training on GPU." << std::endl;
//			device_type = torch::kCUDA;
//		}
//		else if (torch::hasMPS())
//		{
//			std::cout << "MPS available! Training on MPS." << std::endl;
//			device_type = torch::kMPS;
//		}
//		else
//		{
//			std::cout << "Training on CPU." << std::endl;
//			device_type = torch::kCPU;
//		}
//		torch::Device device(torch::kCPU);
//
//		NetImpl model;
//		cout << model << endl;
//		model.to(device);
//
//		auto train_dataset = torch::data::datasets::MNIST(DATA_ROOT).map(torch::data::transforms::Normalize<>(0.1307, 0.3081))
//																	.map(torch::data::transforms::Stack<>());
//		const size_t train_dataset_size = train_dataset.size().value();
//		auto train_loader = torch::data::make_data_loader<torch::data::samplers::SequentialSampler>( std::move(train_dataset), TRAIN_BATCH_SIZE);
//
//		auto test_dataset = torch::data::datasets::MNIST(DATA_ROOT, torch::data::datasets::MNIST::Mode::kTest).map(torch::data::transforms::Normalize<>(0.1307, 0.3081))
//																											  .map(torch::data::transforms::Stack<>());
//		const size_t test_dataset_size = test_dataset.size().value();
//		auto test_loader = torch::data::make_data_loader(std::move(test_dataset), TEST_BATCH_SIZE);
//
//		torch::optim::SGD optimizer(model.parameters(), torch::optim::SGDOptions(0.01).momentum(0.5));
//
//		for (size_t epoch = 1; epoch <= NUMBER_OF_EPOCHS; ++epoch)
//		{
//			train(epoch, model, device, *train_loader, optimizer, train_dataset_size);
//			test(model, device, *test_loader, test_dataset_size);
//		}
//	}
//	catch (const c10::Error &e)
//	{
//		std::cerr << "error loading the model\n";
//	}
//
//	return 0;
//}
