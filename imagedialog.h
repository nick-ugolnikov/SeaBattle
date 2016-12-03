#ifndef IMAGEDIALOG_H
#define IMAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtCore/QObject>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpacerItem>
#include <QWidget>
#include <QDialog>
#include <QMovie>
#include <QPixmap>

class ImageDialog : public QDialog 
{
	Q_OBJECT
public:
	ImageDialog(QWidget *parent=NULL);
	
public slots:
	void slotYouLost();
	void slotYouWon();

private:
	QPushButton *pushButtonClose;
	QGridLayout *gridLayout;
	QSpacerItem *spacerItemRight, *spacerItemLeft;
	QLabel *imageLabel;
};

#endif
