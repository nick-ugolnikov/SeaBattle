#include "imagedialog.h"

ImageDialog::ImageDialog(QWidget *parent) : QDialog(parent) 
{
	setModal(true);
    resize(300, 200);
	gridLayout = new QGridLayout(this);
	imageLabel = new QLabel;
        imageLabel->setBackgroundRole(QPalette::Base);
	gridLayout->addWidget(imageLabel, 0, 0, 1, 3);	
    pushButtonClose = new QPushButton(QString::fromUtf8("Закрыть"), this);
	connect(pushButtonClose, SIGNAL(clicked()), this, SLOT(accept()));
	gridLayout->addWidget(pushButtonClose, 1, 1, 1, 1);
	spacerItemLeft = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	gridLayout->addItem(spacerItemLeft, 1, 0, 1, 1);
	spacerItemRight = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	gridLayout->addItem(spacerItemRight, 1, 2, 1, 1);
}

void ImageDialog::slotYouWon()
{
    setWindowTitle(QString::fromUtf8("Великолепная победа!"));
    QString path(":/pictures/winner.gif");
	QMovie *movie = new QMovie(path);
	imageLabel->setMovie(movie);
	imageLabel->adjustSize();
	movie->start();
	show();
	return;
}

void ImageDialog::slotYouLost()
{
    setWindowTitle(QString::fromUtf8("Неудачник! Возвращайся домой..."));
    QString path(":/pictures/loser.gif");
	QMovie *movie = new QMovie(path);
	imageLabel->setMovie(movie);
	imageLabel->adjustSize();
	movie->start();
	show();
	return;
}
