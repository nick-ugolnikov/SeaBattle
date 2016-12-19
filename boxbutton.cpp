#include "boxbutton.h"
#include "battleship.h"

BoxButton::BoxButton(PlayerT p, Battleship *battleship, QWidget *parent)  : QPushButton(parent)
{
	playert = p;
	condition = ocean;
	preview = none;
	ewoMode = false;
	associatedShip = NULL;
	updateColor();
	connect(this, SIGNAL(clicked()), this, SLOT(slotOnClick()));
	connect(this, SIGNAL(sigRelayClick(PlayerT, int, int)), battleship, SLOT(slotClickOnField(PlayerT, int, int)));
    if (playert == human) {
        connect(this, SIGNAL(sigPreview(int, int)), battleship->getHumanPlayer(), SLOT(slotPreviewShip(int, int)));
        connect(this, SIGNAL(sigUnPreview(int, int)), battleship->getHumanPlayer(), SLOT(slotUnPreviewShip(int, int)));
	}
}

ConditionT BoxButton::onFire() {
	switch (condition) {
		case ocean: condition = nohit; break;
		case restricted: condition = nohit; break;
		case ship: associatedShip->onFire(this); break;
		default: return error;
	}
	updateColor();
	return condition;
}

ConditionT BoxButton::getCondition()
{
	return condition;
}

ConditionT BoxButton::setCondition(ConditionT c)
{
	condition = c;
	updateColor();
	return condition;
}

PreviewT BoxButton::setPreview(PreviewT p)
{
	preview = p;
	updateColor();
	return preview;
}

PreviewT BoxButton::getPreview()
{
	return preview;
}

void BoxButton::slotOnClick()
{
	emit sigRelayClick(playert, position[0], position[1]);	//TO: battleship.slotClickOnField(pt, row, col)
	return;
}

void BoxButton::updateColor()
{
    if (preview != none) {
		if (preview == ok)
			setPalette(QPalette(Qt::green));
		else
			setPalette(QPalette(Qt::red));
	} else {
		switch (condition) {
			case ocean: setPalette(QPalette(Qt::blue)); break;
			case restricted: setPalette(QPalette(Qt::blue)); break;
			case hit: setPalette(QPalette(Qt::yellow)); break;
			case nohit: setPalette(QPalette(Qt::darkBlue)); break;
			case countersunk: setPalette(QPalette(Qt::red)); break;
			case ship:
				if (playert == human)
					setPalette(QPalette(Qt::green));
				else if (playert == enemy && ewoMode == true)
					setPalette(QPalette(Qt::cyan));
				else
					setPalette(QPalette(Qt::blue));
				break;
			default: setPalette(QPalette(Qt::white)); break;
		}
    }
}

void BoxButton::enterEvent(QEvent *)
{
	if (playert == human)
		emit sigPreview(position[0], position[1]); //To: human.slotPreviewShip(row, col);
	return;
}

void BoxButton::leaveEvent(QEvent *)
{
	if (playert == human)
		emit sigUnPreview(position[0], position[1]); //To: human.slotUnPreviewShip(row, col);
	return;
}
