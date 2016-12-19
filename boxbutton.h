#ifndef BOX_BUTTON_H
#define BOX_BUTTON_H

#include <QPushButton>
#include <QtCore/QEvent>
#include "extra_t.h"
#include "ship.h"
class Battleship;

class BoxButton : public QPushButton {
   Q_OBJECT

public:
	BoxButton(PlayerT p, Battleship *battleship, QWidget *parent=NULL);	// constructor
	
    Ship* getAssociatedShip() { return associatedShip; }
    void setAssociatedShip(Ship *ship) { associatedShip = ship; }
    bool isEasyWin() { return ewoMode; }
    void enableEasyWin(bool flag) { ewoMode = flag; }
    int* getPosition() { return position; }
	ConditionT onFire();
	ConditionT getCondition();
	ConditionT setCondition(ConditionT c);
	PreviewT setPreview(PreviewT p);
	PreviewT getPreview();
	void updateColor();

protected:
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);

private:
	ConditionT condition;
	PreviewT preview;
	PlayerT playert;			//to which player it belongs
    int position[2];			 //[0]=row  [1]=col
    Ship *associatedShip;	//to which ship it belongs
    bool ewoMode;
		   
public slots:
	void slotOnClick();

signals:
	void sigRelayClick(PlayerT pt, int row, int col); // TO: Battleship.slotClickOnField
	void sigPreview(int row, int col); //To: human.slotPreviewShip(row, col);
	void sigUnPreview(int row, int col); //To: human.slotUnPreviewShip(row, col);
};

#endif
