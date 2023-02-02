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

void MainWindow::closeWidget()
{
	SPDLOG_INFO("Widget closed");
	p_model_widget->close();

	delete comboBox_layerLists;
	delete pushButton_add;
	delete pushButton_generate;
	delete pushButton_close;
	delete p_model_widget;
}

void MainWindow::addLayer()
{
	layer = new LAYER;
	layer->conv = torch::nn::Conv2d(torch::nn::Conv2dOptions(1, 10, 5));
//	layer->maxpool = torch::nn::MaxPool2d();
	layers.push_back(layer);
}

void MainWindow::on_pushButton_designModel_clicked()
{
	int widget_width = 640;
	int widget_height = 480;
	int icon_width = 100;
	int icon_height = 32;


	p_model_widget = new QWidget();// Container widget for customComboClass widget object. Holds elements of inheriting class.
	p_model_widget->setFixedSize(widget_width, widget_height);
	p_model_widget->setWindowTitle("Design Model");

	comboBox_layerLists = new QComboBox(p_model_widget);
	comboBox_layerLists->setGeometry(10, 10, 111, 32);
	comboBox_layerLists->addItem("conv2d");

	pushButton_add = new QPushButton(p_model_widget);
	pushButton_add->setText("Add");
	pushButton_add->setGeometry(10 + 111 + 10, 10, 100, 32);
	connect(pushButton_add, SIGNAL(clicked(bool)), this, SLOT(addLayer()));

	pushButton_generate = new QPushButton(p_model_widget);
	pushButton_generate->setText("Generate");
	pushButton_generate->setGeometry(widget_width - 10 - icon_width - 10 - icon_width, widget_height - icon_height - 10, icon_width, icon_height);
	connect(pushButton_generate, SIGNAL(clicked(bool)), this, SLOT(generateModel()));

	pushButton_close = new QPushButton(p_model_widget);
	pushButton_close->setText("Close");
	pushButton_close->setGeometry(widget_width - icon_width - 10, widget_height - icon_height - 10, icon_width, icon_height);
//	connect(pushButton_close, SIGNAL(clicked(bool)), p_model_widget, SLOT(close()));
	connect(pushButton_close, SIGNAL(clicked(bool)), this, SLOT(closeWidget()));

	p_model_widget->show();
}

void MainWindow::generateModel()
{
	NetImpl * net = new NetImpl(layers);
	std::cout << *net << std::endl;
}

MainWindow::~MainWindow()
{
	delete ui;
}
