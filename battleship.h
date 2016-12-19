#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include "ui_battleship.h"
#include "extra_t.h"
#include "boxbutton.h"
#include "player.h"
#include "human.h"
#include "ai.h"
#include "infodialog.h"
#include "imagedialog.h"


class Battleship : public QMainWindow, private Ui::Battleship
{
    Q_OBJECT
private:
	AI *enemyPlayer;
	int round;
	QString delayedSoundFile;
    Human *humanPlayer;
    AlignmentT alignment;
    bool soundAvailable;
    bool soundOn;

public:
    Battleship(QWidget *parent = NULL);
    ~Battleship();

    Human* getHumanPlayer() { return humanPlayer; }
    AlignmentT getAlignment() { return alignment; }
    bool isSoundAvailable() { return soundAvailable; }
    bool isSoundOn() { return soundOn; }

	void setupField(Player *player);


public slots:
	void slotClickOnField(PlayerT pt, int row, int col);	//FROM: User_>click->Box.sigRelayClick
	void slotStartGame();
	void slotSetEwoMode(bool checked);
	void slotPlayerReady();	//after setup, all ships placed

	void slotPlayerTurn(PlayerT pt);

	void slotPrintToConsole(QString text);
	void slotGameOver(PlayerT pt);
	void slotRequestShotNow();
	void slotPlaySound(QString wavFile);
	void slotPlayDelayedSound(QString wavFile, int msecs);
    void slotPlayDelayedSoundNow();
	void slotSoundOn();


signals:
	void sigPlaceFleet();
	void sigHumanPlaceShip(int row, int col, int ali);

	void sigShotAtEnemy(int row, int col);
	void sigRequestShotFromEnemy();

protected:
	PlayerT turn;
	bool eventFilter(QObject *obj, QEvent *ev);
	InfoDialog *infoDialog;
	ImageDialog *imageDialog;
	QLabel *labelStatus;


	void toggleAlignment();
	void blockBoxSignals(bool block);
};

#endif
