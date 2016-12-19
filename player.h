#ifndef PLAYER_H
#define PLAYER_H

#include <QtCore/QString>
#include "extra_t.h"
#include "fleet.h"
#include "boxbutton.h"

class Player : public QObject
{
	Q_OBJECT

private:
    Battleship* battleship_parent;
    int setBoxes(int row, int col, int ali);

protected:
    PlayerT ptype;
    BoxButton *field[10][10];
    Fleet *fleet;
    GameModeT mode;	//Game Mode (setup, shot, wait)

public:
    Player(PlayerT pt, Battleship *battleship);	// constructor
	~Player();		// destructor

    BoxButton* getBBAt(int row, int col) { return field[row][col]; }
    void createBBAt(int row, int col);
    PlayerT getPlayerType() { return ptype; }
    GameModeT getMode() { return mode; }
    void setMode(GameModeT mmode) { mode = mmode; }
	int placeShip(int row, int col, int ali);
	int checkBoxes(int row, int col, int ali);
	void reset();

public slots:
	void slotPlaceFleet();
	void slotPlaceShip(int row, int col, int ali);
	void slotShotAt(int row, int col);

signals:
	void sigFleetComplete();

	void sigDone(PlayerT ptype);
	void sigEnemyTryAgain();

	void sigPrint(QString  text);
	void sigGameOver(PlayerT pt);
	void sigPlaySound(QString wavFile);
	void sigPlayDelayedSound(QString wavFile, int msecs);
	void sigFireFeedback(int row, int col, ConditionT condi);

};

#endif
