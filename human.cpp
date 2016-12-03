#include "human.h"
#include "battleship.h"

Human::Human(PlayerT pt, Battleship *battleship) : Player(pt, (QObject*)battleship)
{
	mode = wait;
	bship = battleship;
}

void Human::slotPlaceShip(int row, int col, int ali)
{
	fleet->createShip();
	if(!placeShip(row, col, ali)) {	//print messages if ship placement was possible
		switch (fleet->status) {
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
		if (bship->alignment == h) {
			if (checkBoxes(row, col, 0) == 0) {
				for (i = col; i < (col+5-fleet->status); i++) {
					field[row][i]->setPreview(ok);
				}
			} else {	
				for (i = col; (i < (col+5-fleet->status)) && (i < 10); i++) {
					field[row][i]->setPreview(moep);
				}
			}
		} else {
			if (checkBoxes(row, col, 1) == 0) {
				for (i = row; i < (row+5-fleet->status); i++) {
					field[i][col]->setPreview(ok);
				}
			} else {
				for (i = row; (i < (row+5-fleet->status)) && (i < 10); i++) {
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
		if (bship->alignment == h) {
			for (i = col; (i < (col+6-fleet->status)) && (i < 10); i++) {
				field[row][i]->setPreview(none);
			}
		} else {
			for (i = row; (i < (row+6-fleet->status)) && (i < 10); i++) {
				field[i][col]->setPreview(none);
			}
		}
	}
	return;
}
