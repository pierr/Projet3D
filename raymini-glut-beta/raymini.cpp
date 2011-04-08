// -------------------------------------------
// RayMini : a minimal OpenGL/GLUT Ray Tracer.
// Copyright (C) 2010 Tamy Boubekeur
// All rights reserved.
// -------------------------------------------

// -------------------------------------------
// Disclaimer: this code is dirty in the
// meaning that there is no attention paid to
// proper class attribute access, memory
// management or optimisation of any kind. It
// is designed for quick-and-dirty testing
// purpose.
// -------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>

#include <algorithm>
#include <GL/glut.h>
#include <Vec3D.h>
#include "RayTracer.h"
#include "Camera.h"
#include "Scene.h"
#include "Image.h"

using namespace std;

// -------------------------------------------
// OpenGL/GLUT application code.
// -------------------------------------------
static const GLuint OpenGLLightID[] =
    {GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7};
typedef enum {Flat=0, Smooth=1} RenderingMode;
static GLint window;
static const unsigned int SCREENWIDTH = 600;
static const unsigned int SCREENHEIGHT = 400;
static Camera camera;
static bool mouseRotatePressed = false;
static bool mouseMovePressed = false;
static bool mouseZoomPressed = false;
static int lastX=0, lastY=0, lastZoom=0;
RenderingMode renderingMode; 
bool wireframe;

Image rayImage (SCREENWIDTH, SCREENHEIGHT);; // Ray Tracer output

void printUsage () {
    cerr << endl 
         << "RayMini: A Minimal OpenGL/GLUT RayTracer" << endl
         << "Author : Tamy Boubekeur" << endl << endl
         << "Usage : ./raymini" << endl
         << "Keyboard commands" << endl 
         << "------------------" << endl
         << " ?: Print help" << endl 
         << " w: Toggle Wireframe Mode" << endl 
         << " g: Toggle Gouraud Shading Mode" << endl
         << " <space>: ray trace." << endl
         << " s: Save ray traced image as rayimage.ppm" << endl
         << " <drag>+<left button>: rotate model" << endl 
         << " <drag>+<right button>: move model" << endl
         << " <drag>+<middle button>: zoom" << endl
         << " q, <esc>: Quit" << endl << endl; 
}

void usage () {
    printUsage ();
    exit (EXIT_FAILURE);
}

void init () {
    glClearColor (0.f, 0.f, 0.f, 0.0);
    glCullFace (GL_BACK);
    glEnable (GL_CULL_FACE);
    glDepthFunc (GL_LEQUAL);
    glEnable (GL_DEPTH_TEST);
    glHint (GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable (GL_POINT_SMOOTH);
    wireframe = false;
    renderingMode = Smooth;
    
    Scene * scene = Scene::getInstance ();
    
    glLoadIdentity ();
    
    glEnable (GL_LIGHTING);
    for (unsigned int i = 0; i < scene->getLights ().size () && i < 8; i++) {
        GLuint glID = OpenGLLightID[i];
        glEnable (glID);
        const Light light = scene->getLights() [i];
        const Vec3Df & p = light.getPos ();
        float intensity = light.getIntensity ();
        const Vec3Df & c = intensity * light.getColor ();
        GLfloat glPos[4] = {p[0], p[1], p[2], 0};
        GLfloat glColor[4] = {c[0], c[1], c[2], 0};
        glLightfv (glID, GL_POSITION, glPos);
        glLightfv (glID, GL_DIFFUSE, glColor);
    }
    
    const BoundingBox & sceneBBox = scene->getBoundingBox ();
    Vec3Df c = sceneBBox.getCenter ();
    float r = sceneBBox.getRadius ();
    camera.showScene (c, r);
}

void clear () {
  
}

void renderGL () {
    Scene * scene = Scene::getInstance ();
    for (unsigned int i = 0; i < scene->getObjects ().size (); i++) {
        const Object & o = scene->getObjects ()[i];
        const Material & mat = o.getMaterial ();
        const Vec3Df & color = mat.getColor ();
        float dif = mat.getDiffuse ();
        float spec = mat.getSpecular ();
        static GLfloat glMatDiff[4]; 
        static GLfloat glMatSpec[4];
        static const GLfloat glMatAmb[4] = {0.f, 0.f, 0.f, 1.f};
        for (unsigned int j = 0; j < 3; j++) {
            glMatDiff[j] = dif*color[j];
            glMatSpec[j] = spec;
        }
        glMatDiff[3] = 1.0f;
        glMatSpec[3] = 1.0f;

        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glMatDiff);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glMatSpec);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glMatAmb);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);
        glDisable (GL_COLOR_MATERIAL);
        o.getMesh ().renderGL (renderingMode == Flat);
    }
}

void raytrace () {
    Vec3Df eye = camera.getEye ();
    Vec3Df viewDirection = camera.getViewDirection ();
    Vec3Df upVector = camera.getUpVector ();
    Vec3Df rightVector = camera.getRightVector ();
    rayImage = RayTracer::getInstance ()->render (eye, viewDirection,
                                                  -upVector, /// BEWARE : Image generated upside-down for GL Drawing
                                                  rightVector,
                                                  camera.getFovAngle (), camera.getAspectRatio (),
                                                  SCREENWIDTH, SCREENHEIGHT);
}

void renderRay () {
      glDrawPixels (rayImage.getWidth (), rayImage.getHeight (), GL_RGB, GL_FLOAT, rayImage.getData ());
      glutSwapBuffers ();
}

void savePPM (const string & filename) {
    ofstream out (filename.c_str ());
    out << "P3" << endl;
    out << SCREENWIDTH << " " << SCREENHEIGHT << endl;
    out << 255 << endl;
    for (int j = rayImage.getHeight () - 1; j > 0; j--) /// BEWARE : Image generated upside-down for GL Drawing
        for (unsigned int i = 0; i < rayImage.getWidth (); i++)  {
            Vec3Df c = rayImage.get (i, j);
            for (unsigned int k = 0 ; k < 3; k++) 
                out << int (255*c[k]) << " ";
            out << endl;
        }
    out << flush;
    out.close ();
}

void display () {
    glLoadIdentity ();
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera.apply ();
    renderGL ();
    glFlush ();
    glutSwapBuffers ();
}

void key (unsigned char keyPressed, int x, int y) {
    switch (keyPressed) {
    case 'q':
    case 27:
        clear ();
        exit (0);
        break;
    case 'w':
        glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
        glutPostRedisplay ();
        break;
    case 'g':
        glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
        glutPostRedisplay ();
        break;
    case ' ':
        raytrace ();
        renderRay ();
        break;
    case 's':
        savePPM ("rayimage.ppm");
        break;
    default:
        printUsage ();
        break;
    }
}

void mouse (int button, int state, int x, int y) {
    if (state == GLUT_UP) {
        mouseMovePressed = false;
        mouseRotatePressed = false;
        mouseZoomPressed = false;
    } else {
        lastX = x;
        lastY = y;
        if (button == GLUT_LEFT_BUTTON) 
            mouseRotatePressed = true;
        else if (button == GLUT_RIGHT_BUTTON) 
            mouseMovePressed = true;
        else if (button == GLUT_MIDDLE_BUTTON) {
            mouseZoomPressed = true;
            lastZoom = y;
        }
        glutPostRedisplay ();
    }
}

void motion (int x, int y) {
    if (mouseRotatePressed == true) {
        camera.rotate (float(x-lastX) / SCREENWIDTH,
                       float(lastY-y) / SCREENHEIGHT);
        lastX = x;
        lastY = y;
    }
    else if (mouseMovePressed == true) {
        camera.move (Vec3Df ((x-lastX)/static_cast<float>(SCREENWIDTH),
                             (lastY-y)/static_cast<float>(SCREENHEIGHT),
                             0.0));
        lastX = x;
        lastY = y;
    }
    else if (mouseZoomPressed == true) {
        camera.zoom (1.f + float (y-lastZoom)/SCREENHEIGHT);
        lastZoom = y;
    }
    glutPostRedisplay ();
}


void reshape(int w, int h) {
    camera.resize (w, h);
    glutPostRedisplay ();
}


int main (int argc, char ** argv) {
    if (argc != 1) {
        printUsage ();
        exit (EXIT_FAILURE);
    }
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize (SCREENWIDTH, SCREENHEIGHT);
    window = glutCreateWindow ("RayMini");
  
    init ();
    glutDisplayFunc (display);
    glutKeyboardFunc (key);
    glutReshapeFunc (reshape);
    glutMotionFunc (motion);
    glutMouseFunc (mouse);
    key ('?', 0, 0);   
    glutMainLoop ();
    return EXIT_SUCCESS;
}

