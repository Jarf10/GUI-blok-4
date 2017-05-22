QT += widgets
CONFIG += c++11

HEADERS = \
   dialog.h \
    Led.h \
    Widgetwithbackground.h
    
SOURCES = \
   dialog.cpp \
   main.cpp \
   Led.cpp \
   Widgetwithbackground.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/layouts/basiclayouts
INSTALLS += target
