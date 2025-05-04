QT       += core gui network designer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/src/ \
               $$PWD/src/core \
               $$PWD/src/widget \
               $$PWD/src/widget/collapsable \
               $$PWD/src/widget/hexspinbox \
               $$PWD/src/widget/dial \

SOURCES += $$files(src/*.cpp) \
           $$files(src/core/*.cpp) \
           $$files(src/widget/*.cpp) \
           $$files(src/widget/collapsable/*.cpp) \
           $$files(src/widget/hexspinbox/*.cpp) \
           $$files(src/widget/dial/*.cpp)


HEADERS += $$files(src/*.h) \
           $$files(src/core/*.h) \
           $$files(src/widget/*.h) \
           $$files(src/widget/collapsable/*.h) \
           $$files(src/widget/hexspinbox/*.h) \
           $$files(src/widget/dial/*.h)

FORMS += $$files(src/ui/*.ui) \
         $$files(src/widget/*.ui) \
         $$files(src/widget/collapsable/*.ui) \
         $$files(src/widget/hexspinbox/*.ui) \
         $$files(src/widget/dial/*.ui)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
