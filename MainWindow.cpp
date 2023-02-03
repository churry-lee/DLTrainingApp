#include "MainWindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	// Load device lists
	if (torch::cuda::is_available())
		ui->comboBox_deviceLists->addItem("CUDA");
	else if (torch::hasMPS())
		ui->comboBox_deviceLists->addItem("MPS");
	ui->comboBox_deviceLists->addItem("CPU");

	layers.clear();

	connect(ui->pushButton_exitProgram, SIGNAL(clicked(bool)), this, SLOT(close()));
}

void MainWindow::on_pushButton_imgPath_clicked()
{
	QString searchLocation = QFileDialog::getExistingDirectory(this, "Set image data folder", QDir::currentPath(), QFileDialog::ShowDirsOnly);
	SPDLOG_INFO("Image Path: " + searchLocation.toStdString());

	// TODO: 이미지 파일 경로를 DataSet class에 전달
}

void MainWindow::on_pushButton_labelPath_clicked()
{
	QString searchLocation = QFileDialog::getExistingDirectory(this, "Set image data folder", QDir::currentPath(), QFileDialog::ShowDirsOnly);
	SPDLOG_INFO("Label Path: " + searchLocation.toStdString());
}

void MainWindow::on_pushButton_setDevice_clicked()
{
	torch::DeviceType device_type;

	if (std::strcmp(ui->comboBox_deviceLists->currentText().toStdString().c_str(), "CUDA") == 0)
		device_type = torch::kCUDA;
	else if (std::strcmp(ui->comboBox_deviceLists->currentText().toStdString().c_str(), "MPS") == 0)
		device_type = torch::kMPS;
	else
		device_type = torch::kCPU;

	device = device_type;
	SPDLOG_INFO("Device Type: " + device.str());
}

void MainWindow::on_pushButton_designModel_clicked()
{
	components = new LAYER_COMPONENTS;

	sub_model_widget = new subWidget("Design Model", 640, 480);

//	QPushButton * pushButton_componentsAdd = sub_model_widget->addPushButton("Add", 131, 10, 100, 32);
//	std::vector<QString> items{"Conv2d", "MaxPool2d", "Dropout2d", "Linear", "ReLu"};
//	QComboBox * comboBox_layerLists = sub_model_widget->addComboBox(items, 10, 10, 111, 32);
//	if (std::strcmp(comboBox_layerLists->currentText().toStdString().c_str(), items[0].toStdString().c_str()) == 0)
//		connect(pushButton_componentsAdd, SIGNAL(clicked(bool)), this, SLOT(addComponentConv()));

	QPushButton * pushButton_layerAdd = sub_model_widget->addPushButton("Layer add", 10, 10, 100, 32);
	connect(pushButton_layerAdd, SIGNAL(clicked(bool)), this, SLOT(addLayer()));

	QPushButton * pushButton_generate = sub_model_widget->addPushButton("Generate", 420, 438, 100, 32);
	connect(pushButton_generate, SIGNAL(clicked(bool)), this, SLOT(generateModel()));

	QPushButton * pushButton_close = sub_model_widget->addPushButton("Close", 530, 438, 100, 32);
	connect(pushButton_close, SIGNAL(clicked(bool)), this, SLOT(closeModelWidget()));

	sub_model_widget->showWidget();
}

void MainWindow::on_pushButton_train_clicked()
{
	SPDLOG_INFO("train model");
}
void MainWindow::closeModelWidget()
{
	SPDLOG_INFO("Widget closed");
	sub_model_widget->closeWidget();
}

void MainWindow::okLayerWidget()
{
	SPDLOG_INFO("OK");
	in_channels = lineEdit_in_channels->text().toInt();
	out_channels = lineEdit_out_channels->text().toInt();
	kernel = lineEdit_kernel->text().toInt();
	stride = lineEdit_stride->text().toInt();
	padding = lineEdit_padding->text().toInt();
	maxpool = lineEdit_maxpool->text().toInt();
	dropout = lineEdit_dropout->text().toFloat();

	SPDLOG_INFO("in_channels : " + std::to_string(in_channels));
	SPDLOG_INFO("out_channels: " + std::to_string(out_channels));
	SPDLOG_INFO("kernel      : " + std::to_string(kernel));
	SPDLOG_INFO("stride      : " + std::to_string(stride));
	SPDLOG_INFO("padding     : " + std::to_string(padding));
	SPDLOG_INFO("maxpool     : " + std::to_string(maxpool));
	SPDLOG_INFO("dropout     : " + std::to_string(dropout));

	components->conv = torch::nn::Conv2d(torch::nn::Conv2dOptions(in_channels, out_channels, kernel).stride(stride).padding(padding));
	components->maxpool = torch::nn::MaxPool2d(maxpool);
	components->relu = torch::nn::ReLU();
	components->dropout = torch::nn::Dropout2d(dropout);
	torch::nn::Sequential layer{components->conv, components->maxpool, components->relu, components->dropout};
	layers.push_back(layer);
	sub_components_widget->closeWidget();
}

void MainWindow::closeLayerWidget()
{
	sub_components_widget->closeWidget();
}

//void MainWindow::addComponentConv()
//{
//	sub_components_widget = new subWidget("Add Components", 300, 200);
//
//	lineEdit_in_channels = sub_components_widget->addLabel("In channels", 20, 10, 100, 32);
//	lineEdit_out_channels = sub_components_widget->addLabel("Out channels", 20, 30, 100, 32);
//	lineEdit_kernel = sub_components_widget->addLabel("Kernel", 20, 50, 100, 32);
//	lineEdit_stride = sub_components_widget->addLabel("Stride", 20, 70, 100, 32);
//	lineEdit_padding = sub_components_widget->addLabel("Padding", 20, 90, 100, 32);
//
//	QPushButton * pushButton_ok = sub_components_widget->addPushButton("OK", 80, 158, 100, 32);
//	connect(pushButton_ok, SIGNAL(clicked(bool)), this, SLOT(okComponentsWidget()));
//
//	QPushButton * pushButton_cancel = sub_components_widget->addPushButton("Cancel", 190, 158, 100, 32);
//	connect(pushButton_cancel, SIGNAL(clicked(bool)), this, SLOT(closeComponentsWidget()));
//
//	sub_components_widget->showWidget();
//}

void MainWindow::addLayer()
{
	int x, y, width, height;
	width = 250;
	height = 900;
	x = 20;
	y = 10;
	int icon_width = 100; int icon_height = 32;

	sub_components_widget = new subWidget("Add Components", width, height);

	lineEdit_in_channels = sub_components_widget->addLabel("In channels", x, y, icon_width, icon_height);
	lineEdit_out_channels = sub_components_widget->addLabel("Out channels", x, y+=42, icon_width, icon_height);
	lineEdit_kernel = sub_components_widget->addLabel("Kernel", x, y+=42, icon_width, icon_height);
	lineEdit_stride = sub_components_widget->addLabel("Stride", x, y+=42, icon_width, icon_height);
	lineEdit_padding = sub_components_widget->addLabel("Padding", x, y+=42, icon_width, icon_height);
	lineEdit_maxpool = sub_components_widget->addLabel("MaxPooling", x, y+=42, icon_width, icon_height);
	lineEdit_dropout = sub_components_widget->addLabel("Dropout", x, y+=42, icon_width, icon_height);

	QPushButton * pushButton_ok = sub_components_widget->addPushButton("OK", 30, height-42, icon_width, icon_height);
	connect(pushButton_ok, SIGNAL(clicked(bool)), this, SLOT(okLayerWidget()));

	QPushButton * pushButton_cancel = sub_components_widget->addPushButton("Cancel", 140, height-42, icon_width, icon_height);
	connect(pushButton_cancel, SIGNAL(clicked(bool)), this, SLOT(closeLayerWidget()));

	sub_components_widget->showWidget();
}

void MainWindow::generateModel()
{
	NetImpl * net = new NetImpl(layers);
	SPDLOG_INFO("Model Implement\n");
	std::cout << *net << std::endl;
}

MainWindow::~MainWindow()
{
	delete ui;
}
