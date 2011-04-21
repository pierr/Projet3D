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
          Ray.h

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
          Main.cpp 
          
DESTDIR = .

QT_VERSION=$$[QT_VERSION]


# -------------------------------------

contains( QT_VERSION, "^4\..*" ) {
  QT *= xml opengl
} else {
  CONFIG *= thread
}

unix {
  isEmpty( PREFIX ) {
    PREFIX=/usr
  }

  # INCLUDE_DIR
  isEmpty( INCLUDE_DIR ) {
    INCLUDE_DIR = $${PREFIX}/include 


    !exists( $${INCLUDE_DIR}/QGLViewer/qglviewer.h ) {
      exists( ../../QGLViewer/qglviewer.h ) {
        message( Using ../.. as INCLUDE_DIR )
        INCLUDE_DIR = ../..
      }
    }
  }

  !exists( $${INCLUDE_DIR}/QGLViewer/qglviewer.h ) {
    message( Unable to find QGLViewer/qglviewer.h in $${INCLUDE_DIR} )
    error( Use qmake INCLUDE_DIR=Path/To/QGLViewerHeaderFiles )
  }

  # LIB_NAME
  LIB_NAME = libQGLViewer*.so*
  macx|darwin-g++ {
    LIB_NAME = libQGLViewer*.$${QMAKE_EXTENSION_SHLIB}
  }
  hpux {
    LIB_NAME = libQGLViewer*.sl*
  }

  !isEmpty( QGLVIEWER_STATIC ) {
    LIB_NAME = libQGLViewer*.a
  }

  # LIB_DIR
  isEmpty( LIB_DIR ) {
    LIB_DIR = $${PREFIX}/lib 

    !exists( $${LIB_DIR}/$${LIB_NAME} ) {
      exists( ../../QGLViewer/$${LIB_NAME} ) {
        message( Using ../../QGLViewer as LIB_DIR )
        macx|darwin-g++ {
          message( You should add the path to "../../QGLViewer" to your DYLD_LIBRARY_PATH variable )
        } else {
          message( You should add the path to "../../QGLViewer" to your LD_LIBRARY_PATH variable )
        }
        message( See the "Compilation" section in doc/examples/index.html for details )
        LIB_DIR = ../../QGLViewer
      }
    }
  }

  !exists( $${LIB_DIR}/$${LIB_NAME} ) {
    message( Unable to find $${LIB_NAME} in $${LIB_DIR} )
    error( You should run qmake LIB_DIR=Path/To/$${LIB_NAME} )
  }

  INCLUDEPATH *= $${INCLUDE_DIR}
  DEPENDPATH  *= $${INCLUDE_DIR}
  isEmpty( QGLVIEWER_STATIC ) {
    LIBS *= -L$${LIB_DIR} -lQGLViewer 
  } else {
    LIBS *= $${LIB_DIR}/$${LIB_NAME}
  }

  macx {
    LIBS *= -lobjc
    CONFIG -= thread
  }


  release:QMAKE_CFLAGS_RELEASE -= -g
  release:QMAKE_CXXFLAGS_RELEASE -= -g
  release:QMAKE_CXXFLAGS_RELEASE += -O3 -mfpmath=sse -msse2
  release:QMAKE_CFLAGS_RELEASE += -O3 -mfpmath=sse -msse2

  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}


#                    Windows configuration.
win32 {
  release:QMAKE_CXXFLAGS_RELEASE += -O3 -mfpmath=sse -msse2
  release:QMAKE_CFLAGS_RELEASE += -O3 -mfpmath=sse -msse2

  !win32-g++ {
    QMAKE_CXXFLAGS = -TP -G6 -GR -Zi
    win32-msvc {
      QMAKE_CXXFLAGS *= -GX
    } else {
      QMAKE_CXXFLAGS *= -EHs
    }
  }

  DEFINES *= QT_DLL QT_THREAD_SUPPORT

  !isEmpty( QGLVIEWER_STATIC ) {
    DEFINES *= QGLVIEWER_STATIC
  }

  win32-g++ {
    LIB_FILE = libQGLViewer*2.a
  } else {
    LIB_FILE = QGLViewer*.lib
  }
  prefix=../../../../../Dev/libQGLViewer-2.2.6-3

  exists( $${prefix}/QGLViewer ) {
    exists( $${prefix}/QGLViewer/qglviewer.h ) {
      INCLUDEPATH *= $${prefix}
    }

    exists( $${prefix}/QGLViewer/Debug ) {
      exists( $${prefix}/QGLViewer/Debug/$${LIB_FILE} ) {
        LIB_PATH = $${prefix}/QGLViewer/Debug
      }
    }

    exists( $${prefix}/QGLViewer/Release ) {
      exists( $${prefix}/QGLViewer/Release/$${LIB_FILE} ) {
        LIB_PATH = $${prefix}/QGLViewer/Release
      }
    }

    exists( $${prefix}/QGLViewer/$${LIB_FILE} ) {
      LIB_PATH = $${prefix}/QGLViewer
    }
  }

  exists( $${LIB_PATH}/QGLViewer226.lib ) {
    LIBS *= $${LIB_PATH}/QGLViewer226.lib
  } else {
    exists( $${LIB_PATH}/QGLViewer2.lib ) {
      LIBS *= $${LIB_PATH}/QGLViewer2.lib
    } else {
      exists( $${LIB_PATH}/QGLViewer.lib ) {
        LIBS *= $${LIB_PATH}/QGLViewer.lib
      } else {
        exists( $${LIB_PATH}/libQGLViewer2.a ) {
          LIBS *= -L$${LIB_PATH} -lQGLViewer2
        } else {
          exists( $${LIB_PATH}/libQGLViewerd2.a ) {
            LIBS *= -L$${LIB_PATH} -lQGLViewerd2
          } else {
            error( Unable to find $${LIB_FILE}. )
	  }
	}
      }
    }
  }
}
