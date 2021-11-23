QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    Effect/Effect.cpp \
    graphics.cpp \
    Handle/Decoration/Boat.cpp \
    Handle/Decoration/Campfire.cpp \
    Handle/Decoration/Decoration.cpp \
    Handle/Decoration/Door.cpp \
    Handle/Decoration/House.cpp \
    Handle/Decoration/Item_Handle.cpp \
    Handle/Decoration/Tree.cpp \
    Handle/Handle.cpp \
    Handle/Inventory/Item_Inventory.cpp \
    Handle/Unit/Ghost.cpp \
    Handle/Unit/Survivor.cpp \
    Handle/Unit/Unit.cpp \
    Item/Item.cpp \
    Item/key.cpp \
    Item/regen_instant_potion.cpp \
    Main.cpp \
    mainwindow.cpp \
    Map/Map.cpp \
    Map/Terrain.cpp \
    menuwindow.cpp

HEADERS += \
    Effect/Effect.h \
    graphics.h \
    Handle/Decoration/Boat.h \
    Handle/Decoration/Campfire.h \
    Handle/Decoration/Decoration.h \
    Handle/Decoration/Door.h \
    Handle/Decoration/House.h \
    Handle/Decoration/Item_Handle.h \
    Handle/Decoration/Tree.h \
    Handle/Handle.h \
    Handle/Inventory/Item_Inventory.h \
    Handle/Unit/Ghost.h \
    Handle/Unit/Survivor.h \
    Handle/Unit/Unit.h \
    Item/Item.h \
    Item/key.h \
    Item/regen_instant_potion.h \
    mainwindow.h \
    Map/Map.h \
    Map/Terrain.h \
    menuwindow.h \
    util.h

FORMS += \
    mainwindow.ui \
    menuwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
