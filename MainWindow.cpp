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


MainWindow::~MainWindow()
{
	delete ui;
}
