QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    credit.cpp \
    deposit.cpp \
    main.cpp \
    mainwindow.cpp \
    ../modules/calculation.cpp \
    ../modules/credit_calc.cpp \
    ../modules/deposit_calc.cpp \
    ../modules/parcer.cpp \
    ../modules/polish_notation.cpp \
    ../modules/validator.cpp \
    ../s21_smart_calc.cpp \
    plot.cpp

HEADERS += \
    credit.h \
    deposit.h \
    mainwindow.h \
    ../s21_smart_calc.h \
    plot.h

FORMS += \
    credit.ui \
    deposit.ui \
    mainwindow.ui \
    plot.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc
