#include "player.h"

Player::Player(PlayerT pt, QObject *battleship) : QObject(battleship)
{
	ptype = pt;
	fleet = new Fleet(ptype, battleship);
}

int Player::placeShip(int row, int col, int ali)
{
	if (checkBoxes(row, col, ali) == 0) {
		if (setBoxes(row, col, ali) == 0) {
            fleet->setStatus(fleet->getStatus()+1);
            if (fleet->getStatus() == 5) {
				mode = wait;
				field[row][col]->setPreview(none); //disable preview for the last ship (boat):
				emit sigFleetComplete();	//TO: battleship.slotPlayerReady()
			}
			if (ptype == human)
                emit sigPlaySound("clonk.wav");
			return 0;
		}
	}
	return 1;
}

Player::~Player()
{
	delete fleet;

}

void Player::slotPlaceFleet()
{
	mode = setup;
}

int Player::checkBoxes(int row, int col, int ali)
{
    if (ali == (int)h && (col+4-fleet->getStatus()) < 10)	{	//Ship horizontal and inside field
		int c=col;
        for (c = col; c < (col+5-fleet->getStatus()); c++) { //check if other ships are in the way
			if (field[row][c]->getCondition() != ocean)
				return 1;
		}
		return 0;
	}
    if (ali == (int)v && (row+4-fleet->getStatus()) < 10)	{	//Ship vertical and inside field
		int r=row;
        for (r = row; r < (row+5-fleet->getStatus()); r++) { // check if other ships are in the way
			if (field[r][col]->getCondition() != ocean)
				return 1;
		}
		return 0;
	}
	return 1;
}

int Player::setBoxes(int row, int col, int ali)
{
	int c=col, r=row, i=0;
	if (ali == (int)h)	{	//Ship horizontal and inside field
        for (c = col-1; c < (col+6-fleet->getStatus()); c++) { // set boxes on the field
            if (c >= col && c < (col+5-fleet->getStatus())) { //set boxes in this interval to ship
				field[row][c]->setCondition(ship);
				if (row+1 < 10)
					field[row+1][c]->setCondition(restricted);
				if (row-1 >= 0)
					field[row-1][c]->setCondition(restricted);
                field[row][c]->associatedShip = fleet->getShip(fleet->getStatus());
                fleet->getShip(fleet->getStatus())->box[i] = field[row][c];
				i++;
			} else if (c >= 0 && c < 10) {
				field[row][c]->setCondition(restricted);
				if (row+1 < 10)
					field[row+1][c]->setCondition(restricted);
				if (row-1 >= 0)
					field[row-1][c]->setCondition(restricted);
			}
		}
		return 0;
	}
	i=0;
	if (ali == (int)v)	{	//Ship vertical and inside field
        for (r = row-1; r < (row+6-fleet->getStatus()); r++) { // set boxes on the field
            if (r >= row && r < (row+5-fleet->getStatus())) { //set boxes in this interval to ship
				field[r][col]->setCondition(ship);
				if (col+1 < 10)
					field[r][col+1]->setCondition(restricted);
				if (col-1 >= 0)
					field[r][col-1]->setCondition(restricted);
                field[r][col]->associatedShip = fleet->getShip(fleet->getStatus());
                fleet->getShip(fleet->getStatus())->box[i] = field[r][col];
				i++;
			} else if (r >= 0 && r < 10) {
				field[r][col]->setCondition(restricted);
				if (col+1 < 10)
					field[r][col+1]->setCondition(restricted);
				if (col-1 >= 0)
					field[r][col-1]->setCondition(restricted);
			}
		}
		return 0;
	}
	return 1;
}

void Player::slotPlaceShip(int row, int col, int ali)
{
	placeShip(row, col, ali);
}

void Player::slotShotAt(int row, int col)	// Player gets shot
{
	ConditionT condi;
	if (row>=0 && row<10 && col>=0 && col<10) {
        condi = field[row][col]->onFire();
		emit sigFireFeedback(row, col, condi);
		if (condi == hit || condi == countersunk || condi == error) {
			if (condi == countersunk) {
                fleet->setStatus(fleet->getStatus()-1);
				//if (ptype == enemy) {
                    emit sigPlaySound("explosion.wav");
                    emit sigPlayDelayedSound("breaking.wav", 600);
				//}
			} else if (condi == hit/* && ptype == enemy*/) {
                emit sigPlaySound("explosion.wav");
			}
            if (fleet->getStatus() == 0) {
				mode = wait;
				emit sigGameOver(ptype); //ptype has lost the game
			} else {	// shoot again
				if (ptype == enemy) {
					emit sigDone(human);
				} else if (condi == error){ //ptype == human && condi == error  -> request new shot imediately
					emit sigEnemyTryAgain();
				} else {
					emit sigDone(enemy);
				}
			}
		} else if (condi == nohit){		// enemy may shoot now
			//if (ptype == enemy)
                emit sigPlaySound("watersplash.wav");
			emit sigDone(ptype);
		}
	} else
		emit sigPrint("ERROR!!! out of bounds");	// This can not happen ;-)
	return;
}

void Player::reset()
{
	int row, col;

	// Reset BoxButtons
	for (row=0; row<10; row++) {
		for (col=0; col<10; col++) {
			field[row][col]->setCondition(ocean);
			field[row][col]->associatedShip=NULL;
			field[row][col]->updateColor();
		}
	}

	fleet->reset();
}
