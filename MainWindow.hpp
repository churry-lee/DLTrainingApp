#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <spdlog/spdlog.h>

#include <QMainWindow>
#include <QKeyEvent>
#include <QEvent>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>

#undef slots
#include "torch/torch.h"
#include "torch/jit.h"
#include "torch/nn.h"
#include "torch/script.h"
#define slots Q_SLOTS


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

private slots:
	void on_pushButton_imgPath_clicked();
	void on_pushButton_labelPath_clicked();

	void on_pushButton_setDevice_clicked();
};
#endif // MAINWINDOW_HPP
