RayMini v0.1
Author: Tamy Boubekeur (tamy.boubekeur@telecom-paristech.fr)

RayMini is a minimal raytracer implmented in C++/OpenGL/Qt.

Compiling
----------
Requires GCC >v4, OpenGL, QT >v4.4 and libQGLViewer.
Edit the file raymini.pro to adapt it to your configuration (should work directly under standard linux installation).
The enter: 
 qmake raymini.pro
 make
 ./raymini


To compile on mac 
qmake -spec macx-g++ file.pro
to execute open exec

#Pour le multi thread il faut ajouter 
QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp
au .pro
Et j'ai ajouté dans le code une ligne  #pragma omp parallel for avant la boucle for des pixel