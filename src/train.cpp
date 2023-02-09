#include "train.hpp"

TrainModel::TrainModel(int epoch, NetImpl & model, torch::Device device, myDataset & dataset)
{
	SPDLOG_INFO("Make TrainModel object");

	size_t dataset_size = dataset.data.size();

	torch::optim::SGD optimizer(model.parameters(), torch::optim::SGDOptions(0.01).momentum(0.5));

	this->train(epoch, model, device, dataset, optimizer, dataset_size);
}

void TrainModel::train(int epoch, NetImpl & model, torch::Device device, myDataset & dataset, torch::optim::Optimizer & optimizer, size_t dataset_size)
{
	SPDLOG_INFO("TRAINING!!!!!!!!!!!!!!!!!!!");
	model.train();
	size_t batch_index = 0;

	auto data_loader = torch::data::make_data_loader<torch::data::samplers::SequentialSampler>(std::move(dataset), 1);

	for (auto & batch : *data_loader)
	{
		auto data = batch.data()->data.to(device);
		auto targets = batch.data()->target.to(device);
		optimizer.zero_grad();

		auto output = model.Forward(data);
		auto loss = torch::nll_loss(output, targets);
		AT_ASSERT(!std::isnan(loss.template item<float>()));

		loss.backward();
		optimizer.step();

		if (batch_index++ % LOG_INTERVAL == 0)
			printf("\rTrain Epoch: %d [%5ld/%5zu] Loss: %.4f", epoch, long(batch_index * batch.data()->data.size(0)), dataset_size, loss.template item<float>());
	}
}

TrainModel::~TrainModel()
{
}

//int train()
//{
//	try
//	{
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
