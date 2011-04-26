TEMPLATE = app
TARGET   = raymini
CONFIG  += qt opengl warn_on release thread

HEADERS = Window.h \
          GLViewer.h \
          QTUtils.h \
          Vertex.h \
          Triangle.h \
          Mesh.h \
          BoundingBox.h \
          Material.h \
          Object.h \
          Light.h \
          Scene.h \
          RayTracer.h \
          Ray.h \
          kdtree.h \
          kdnode.h \
          kdleaf.h \
Parametres.h

SOURCES = Window.cpp \
          GLViewer.cpp \
          QTUtils.cpp \
          Vertex.cpp \
          Triangle.cpp \
          Mesh.cpp \
          BoundingBox.cpp \
          Material.cpp \
          Object.cpp \
          Light.cpp \
          Scene.cpp \
          RayTracer.cpp \
          Ray.cpp \
          Main.cpp \
          kdtree.cpp\
          kdnode.cpp\
          kdleaf.cpp
          
DESTDIR = .
          
DESTDIR = .

QT_VERSION=$$[QT_VERSION]

LIBS += -lqglviewer-qt4 



  release:QMAKE_CFLAGS_RELEASE -= -g
  release:QMAKE_CXXFLAGS_RELEASE -= -g
  release:QMAKE_CXXFLAGS_RELEASE += -O3 -mfpmath=sse -msse2
  release:QMAKE_CFLAGS_RELEASE += -O3 -mfpmath=sse -msse2

  MOC_DIR = .moc
  OBJECTS_DIR = .obj
