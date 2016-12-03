TEMPLATE = app
TARGET = battleship
DEPENDPATH += .
INCLUDEPATH += .
QT += widgets gui multimedia
# Input
HEADERS += ai.h \
           battleship.h \
           boxbutton.h \
           extra_t.h \
           fleet.h \
           human.h \
           imagedialog.h \
           infodialog.h \
           player.h \
           ship.h
FORMS += battleship.ui
SOURCES += ai.cpp \
           battleship.cpp \
           boxbutton.cpp \
           fleet.cpp \
           human.cpp \
           imagedialog.cpp \
           infodialog.cpp \
           main.cpp \
           player.cpp \
           ship.cpp

RESOURCES += \
    resources.qrc
