#include "ship.h"
#include "boxbutton.h"

Ship::Ship(PlayerT pt, ShipT st, QObject *parent) : QObject(parent)
{
	stype = st;
    if (pt == human) {
        player = "Наш";
        if ((int)stype < 3)
            player = "Наша";
    }
    else {
        player = "Чужой";
        if ((int)stype < 3)
            player = "Чужая";
    }
	status = (int) stype;
	alignment = (int)h;
	box = new BoxButton*[(int)stype];
	
	connect(this, SIGNAL(sigPrint(QString)), parent, SLOT(slotPrintToConsole(QString)));
}

Ship::~Ship()
{
	delete box;
}

void Ship::onFire(BoxButton *hitBox)
{
	int i;
	QString  tmp(player);
	status--;	// decrease status if ship is hit
	if (status == 0) {	// ship is destroyed
		for (i=0; i<(int)stype; i++)
			box[i]->setCondition(countersunk);
		switch (stype) {
            case 5: emit sigPrint(tmp.append(" Эсминец уничтожен\n")); break;
            case 4: emit sigPrint(tmp.append(" Миноносец уничтожен\n")); break;
            case 3: emit sigPrint(tmp.append(" Крейсер уничтожен\n")); break;
            case 2: emit sigPrint(tmp.append(" Подводная лодка уничтожена\n")); break;
            case 1: emit sigPrint(tmp.append(" Лодка уничтожена\n")); break;
			default: break;
		}
	}
	else
		hitBox->setCondition(hit);
}
