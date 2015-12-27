/*
 * hello.cpp
 */

#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	// normal
	//QLabel *label = new QLabel("Hello Qt!");

	// use css style sheet
	QLabel *label = new QLabel("<h1><i>Hello</i> <font color=red>Qt!</font></h1>");

	label->show();

	return app.exec();
}