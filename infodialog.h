#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QtCore/QVariant>
#include <QtCore/QObject>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QGridLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QTextEdit>
#include <QTextDocument>
#include <QWidget>
#include <QDialog>

class InfoDialog : public QDialog 
{
	Q_OBJECT
public:
	InfoDialog(QWidget *parent=NULL);
	
public slots:
	void slotLoadAbout();
    void slotLoadTutorial();

private:
	QPushButton *pushButtonClose;
	QGridLayout *gridLayout;
	QSpacerItem *spacerItemRight, *spacerItemLeft;
	QTextEdit *textEdit;
};

#endif
