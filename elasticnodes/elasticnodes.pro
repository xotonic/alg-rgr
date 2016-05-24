QT += widgets

HEADERS += \
        graphwidget.h \
    edge_view.h \
    node_view.h \
    dialog.h

SOURCES += \
        main.cpp \
        graphwidget.cpp \
    node_view.cpp \
    edge_view.cpp \
    graph.cpp \
    vertex_and_edge.cpp \
    dialog.cpp \
    task1.cpp \
    task2.cpp \
    task22.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/graphicsview/elasticnodes
INSTALLS += target
CONFIG += console

FORMS += \
    dialog.ui
QMAKE_CXXFLAGS += -std=c++11
