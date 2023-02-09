#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <spdlog/spdlog.h>

#include <QMainWindow>
#include <QWidget>
#include <QBoxLayout>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QEvent>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QInputDialog>
#include <QLabel>
#include <QComboBox>

#undef slots
#include <torch/torch.h>
//#include "torch/jit.h"
//#include "torch/nn.h"
//#include "torch/script.h"
#define slots Q_SLOTS

#include "subWidget.hpp"
#include "netImpl.hpp"
#include "train.hpp"
#include "myDataset.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
	//////////////////////////////////////////////////////////
	subWidget * sub_model_widget;
	subWidget * sub_components_widget;
	//////////////////////////////////////////////////////////
	QLineEdit * lineEdit_in_channels;
	QLineEdit * lineEdit_out_channels;
	QLineEdit * lineEdit_kernel;
	QLineEdit * lineEdit_stride;
	QLineEdit * lineEdit_padding;
	QLineEdit * lineEdit_maxpool;
	QLineEdit * lineEdit_dropout;
	//////////////////////////////////////////////////////////
	std::string image_data_dir;
	std::string label_file_dir;
	//////////////////////////////////////////////////////////
	torch::Device device = torch::Device(torch::kCPU);
	//////////////////////////////////////////////////////////
	LAYER_COMPONENTS * components;
	std::vector<torch::nn::Sequential> layers;
	int in_channels{0};
	int out_channels{0};
	int kernel{0};
	int stride{0};
	int padding{0};
	int maxpool{0};
	float dropout{0.0};

	NetImpl * net;
	//////////////////////////////////////////////////////////
	myDataset * dataset;

private slots:
	void on_pushButton_imgPath_clicked();
	void on_pushButton_labelPath_clicked();
	void on_pushButton_dataLoad_clicked();

	void on_pushButton_setDevice_clicked();

	void on_pushButton_designModel_clicked();

	void on_pushButton_train_clicked();
	//////////////////////////////////////////////////////////
//	void addComponentConv();
	void addLayer();
	void generateModel();
	void closeModelWidget();

	void okLayerWidget();
	void closeLayerWidget();
};
#endif // MAINWINDOW_HPP
