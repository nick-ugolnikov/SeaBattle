#include "human.h"
#include "battleship.h"

Human::Human(PlayerT pt, Battleship *battleship) : Player(pt, battleship)
{
	mode = wait;
    bship = battleship;
}

Human::~Human()
{
    int row, col;
    for (row=0; row<10; row++) {
        for (col=0; col<10; col++) {
            delete field[row][col];		// deleting the dynamically created BoxButtons
        }
    }
}

void Human::slotPlaceShip(int row, int col, int ali)
{
	fleet->createShip();
	if(!placeShip(row, col, ali)) {	//print messages if ship placement was possible
        switch (fleet->getStatus()) {
            case 1: emit sigPrint("Миноносец [4 клетки]\n"); break;
            case 2: emit sigPrint("Крейсер [3 клетки]\n"); break;
            case 3: emit sigPrint("Подводная лодка [2 клетки]\n"); break;
            case 4: emit sigPrint("Лодка [1 клетка]\n"); break;
			default: break;
		} 
	}
	return;
}

void Human::slotPreviewShip(int row, int col)
{
	if (mode == setup) {
		int i;
        if (bship->getAlignment() == h) {
			if (checkBoxes(row, col, 0) == 0) {
                for (i = col; i < (col+5-fleet->getStatus()); i++) {
					field[row][i]->setPreview(ok);
				}
			} else {	
                for (i = col; (i < (col+5-fleet->getStatus())) && (i < 10); i++) {
					field[row][i]->setPreview(moep);
				}
			}
		} else {
			if (checkBoxes(row, col, 1) == 0) {
                for (i = row; i < (row+5-fleet->getStatus()); i++) {
					field[i][col]->setPreview(ok);
				}
			} else {
                for (i = row; (i < (row+5-fleet->getStatus())) && (i < 10); i++) {
					field[i][col]->setPreview(moep);
				}
			}
		}
	}
	return;
}

void Human::slotUnPreviewShip(int row, int col)
{
	if (mode == setup) {
		int i;
        if (bship->getAlignment() == h) {
            for (i = col; (i < (col+6-fleet->getStatus())) && (i < 10); i++) {
				field[row][i]->setPreview(none);
			}
		} else {
            for (i = row; (i < (row+6-fleet->getStatus())) && (i < 10); i++) {
				field[i][col]->setPreview(none);
			}
		}
	}
	return;
}
