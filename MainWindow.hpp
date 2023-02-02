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

#include "netImpl.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

	torch::Device device = torch::Device(torch::kCPU);

private:
    Ui::MainWindow *ui;

	//////////////////////////////////////////////////////////
	QWidget * p_model_widget;
	QComboBox * comboBox_layerLists;
	QPushButton * pushButton_add;
	QPushButton * pushButton_generate;
	QPushButton * pushButton_close;

	LAYER * layer;
	std::vector<LAYER *> layers;
private slots:
	void on_pushButton_imgPath_clicked();
	void on_pushButton_labelPath_clicked();

	void on_pushButton_setDevice_clicked();

	void on_pushButton_designModel_clicked();
	//////////////////////////////////////////////////////////
	void addLayer();
	void generateModel();
	void closeWidget();
};
#endif // MAINWINDOW_HPP
