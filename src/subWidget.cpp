#include "subWidget.hpp"

subWidget::subWidget(QString name, int width, int height)
{
	sub_widget = new QWidget();
	sub_widget->setFixedSize(width, height);
	sub_widget->setWindowTitle(name);
}

void subWidget::showWidget()
{
	sub_widget->show();
}

QPushButton * subWidget::addPushButton(QString name, int x, int y, int width, int height)
{
	QPushButton * pushButton = new QPushButton(sub_widget);
	pushButton->setText(name);
	pushButton->setGeometry(x, y, width, height);

	return pushButton;
}

QComboBox * subWidget::addComboBox(std::vector<QString> items, int x, int y, int width, int height)
{
	QComboBox * comboBox = new QComboBox(sub_widget);
	comboBox->setGeometry(x, y, width, height);

	for (auto & item : items)
		comboBox->addItem(item);

	return comboBox;
}

QLineEdit * subWidget::addLabel(QString name, int x, int y, int width, int height)
{
	QLabel * label = new QLabel(sub_widget);
	label->setText(name);
	label->setGeometry(x, y, width, height);

	QLineEdit * lineEdit = new QLineEdit(sub_widget);
	lineEdit->setGeometry(x + width + 10, y, 50, height);

	return lineEdit;
}

void subWidget::closeWidget()
{
	sub_widget->close();
}

subWidget::~subWidget()
{
	delete sub_widget;
}