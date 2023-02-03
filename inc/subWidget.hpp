#ifndef _SUBWIDGET_HPP_
#define _SUBWIDGET_HPP_

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>

class subWidget
{
public:
	subWidget(QString name, int width, int height);
	~subWidget();

	void showWidget();
	void closeWidget();
	QPushButton * addPushButton(QString name, int x, int y, int width, int height);
	QComboBox * addComboBox(std::vector<QString> items, int x, int y, int width, int height);
	QLineEdit * addLabel(QString name, int x, int y, int width, int height);
private:
	QWidget * sub_widget;

};

#endif //_SUBWIDGET_HPP_
