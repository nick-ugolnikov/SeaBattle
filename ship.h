#ifndef SHIP_H
#define SHIP_H

#include <QtCore/QObject>
#include "extra_t.h"
#include <QString>
class BoxButton;

class Ship : public QObject
{
	Q_OBJECT
			
private:
	QString  player;
	int alignment;	//0: horizontal; 1: vertical
	int status;		// number of undestroyed ship parts (BoxButtons)
    ShipT stype;
    BoxButton **box; // Array of pointers, pointing at the associated BoxButtons

public:
	Ship(PlayerT pt, ShipT t, QObject *parent = NULL);	// constructor
	~Ship();	// destructor

    void setBBForShipAt(int i, BoxButton* bb) { box[i] = bb; }
    BoxButton* getBBForShipAt(int i) { return box[i]; }
	
	void onFire(BoxButton *hitBox);

signals:
	void sigPrint(QString text);	
};


#endif
