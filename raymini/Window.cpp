#include "Window.h"

#include <vector>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

#include <QDockWidget>
#include <QGroupBox>
#include <QButtonGroup>
#include <QMenuBar>
#include <QApplication>
#include <QLayout>
#include <QLabel>
#include <QProgressBar>
#include <QCheckBox>
#include <QRadioButton>
#include <QColorDialog>
#include <QLCDNumber>
#include <QPixmap>
#include <QFrame>
#include <QSplitter>
#include <QMenu>
#include <QScrollArea>
#include <QCoreApplication>
#include <QFont>
#include <QSizePolicy>
#include <QImageReader>
#include <QStatusBar>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QListWidget>
#include <QScrollArea>

#include "RayTracer.h"

using namespace std;


Window::Window () : QMainWindow (NULL) {
    try {
        viewer = new GLViewer;
    } catch (GLViewer::Exception e) {
        cerr << e.getMessage () << endl;
        exit (1);
    }
    QGroupBox * renderingGroupBox = new QGroupBox (this);
    QHBoxLayout * renderingLayout = new QHBoxLayout (renderingGroupBox);
    
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole (QPalette::Base);
    imageLabel->setSizePolicy (QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents (true);
    imageLabel->setPixmap (QPixmap::fromImage (rayImage));

    renderingLayout->addWidget (viewer);
    renderingLayout->addWidget (imageLabel);

    setCentralWidget (renderingGroupBox);
    
    QDockWidget * controlDockWidget = new QDockWidget (this);
    initControlWidget ();
    
    controlDockWidget->setWidget (controlWidget);
    controlDockWidget->adjustSize ();
    addDockWidget (Qt::RightDockWidgetArea, controlDockWidget);
    controlDockWidget->setFeatures (QDockWidget::AllDockWidgetFeatures);

    setMinimumWidth (800);
    setMinimumHeight (400);
}

Window::~Window () {

}

void Window::renderRayImage () {
    qglviewer::Camera * cam = viewer->camera ();
    RayTracer * rayTracer = RayTracer::getInstance ();
    //mauvais! si on l'ajoute on a recalculer tout pour changer la saturation!!!
//    param->set_renderdone(false);
    rayTracer->setParametres(param);
    rayTracer->setRayButton(rayButton);
    qglviewer::Vec p = cam->position ();
    qglviewer::Vec d = cam->viewDirection ();
    qglviewer::Vec u = cam->upVector ();
    qglviewer::Vec r = cam->rightVector ();
    Vec3Df camPos (p[0], p[1], p[2]);
    Vec3Df viewDirection (d[0], d[1], d[2]);
    Vec3Df upVector (u[0], u[1], u[2]);
    Vec3Df rightVector (r[0], r[1], r[2]);
    float fieldOfView = cam->horizontalFieldOfView ();
    float aspectRatio = cam->aspectRatio ();
    unsigned int screenWidth = cam->screenWidth ();
    unsigned int screenHeight = cam->screenHeight ();
    rayImage = rayTracer->render (camPos, viewDirection, upVector, rightVector,
                                  fieldOfView, aspectRatio, screenWidth, screenHeight);
    imageLabel->setPixmap (QPixmap::fromImage (rayImage));
    
}

void Window::setBGColor () {
    QColor c = QColorDialog::getColor (QColor (133, 152, 181), this);
    if (c.isValid () == true) {
        cout << c.red () << endl;
        RayTracer::getInstance ()->setBackgroundColor (Vec3Df (c.red (), c.green (), c.blue ()));
        viewer->setBackgroundColor (c);
        viewer->updateGL ();
    }
}

void Window::exportGLImage () {
    viewer->saveSnapshot (false, false);
}

void Window::exportRayImage () {
    QString filename = QFileDialog::getSaveFileName (this,
                                                     "Save ray-traced image",
                                                     ".",
                                                     "*.jpg *.bmp *.png");
    if (!filename.isNull () && !filename.isEmpty ()) {
        rayImage.save (filename);
    }
}

void Window::about () {
    
    QMessageBox::about (this, 
                        "About This Program", 
                        "<b>RayMini</b> <br> by <i>Tamy Boubekeur</i>.");
}

void Window::initControlWidget () {
    controlWidget = new QGroupBox ();
    QVBoxLayout * layout = new QVBoxLayout(controlWidget);

    /* PREVIEW */

    QGroupBox * previewGroupBox = new QGroupBox ("Preview", controlWidget);
    QVBoxLayout * previewLayout = new QVBoxLayout (previewGroupBox);
    
    QCheckBox * wireframeCheckBox = new QCheckBox ("Wireframe", previewGroupBox);
    connect (wireframeCheckBox, SIGNAL (toggled (bool)), viewer, SLOT (setWireframe (bool)));
    previewLayout->addWidget (wireframeCheckBox);

    QCheckBox * smoothCheckBox = new QCheckBox ("Smooth", previewGroupBox);
    smoothCheckBox->setChecked((bool)viewer->getRenderingMode());
    connect (smoothCheckBox, SIGNAL (toggled (bool)), viewer, SLOT (setRenderingMode (bool)));
    previewLayout->addWidget (smoothCheckBox);

    QPushButton * snapshotButton  = new QPushButton ("Save preview", previewGroupBox);
    connect (snapshotButton, SIGNAL (clicked ()) , this, SLOT (exportGLImage ()));
    previewLayout->addWidget (snapshotButton);

    layout->addWidget (previewGroupBox);


    /* PARAMETRES */

    param = new Parametres();

    QGroupBox * paramGroupBox = new QGroupBox ("Parameters", controlWidget);
    QVBoxLayout * paramLayout = new QVBoxLayout (paramGroupBox);
    QTabWidget * paramTab = new QTabWidget(paramGroupBox);

    /* RAYS */

    QGroupBox * raysGroupBox = new QGroupBox ("Rays");
    QVBoxLayout * raysLayout = new QVBoxLayout (raysGroupBox);
    paramTab->addTab(raysGroupBox, "Rays");

        //pix_grille
        QLabel * pixgrilleLabel = new QLabel("Rays per pixel");
        raysLayout->addWidget(pixgrilleLabel);

        QSpinBox * pixgrilleSpinBox = new QSpinBox();
        pixgrilleSpinBox->setValue(param->get_pixgrille());
        connect (pixgrilleSpinBox, SIGNAL (valueChanged (int)), param, SLOT(set_pixgrille(int)));
        raysLayout->addWidget(pixgrilleSpinBox);

        //brillance
        QLabel * brillanceLabel = new QLabel("brillance");
        raysLayout->addWidget(brillanceLabel);
        QDoubleSpinBox * brillanceSpinBox = new QDoubleSpinBox();
        brillanceSpinBox->setRange(1,100);
        brillanceSpinBox->setSingleStep(0.1);
        brillanceSpinBox->setValue(param->get_brillance());
        connect (brillanceSpinBox, SIGNAL (valueChanged (double)), param, SLOT(set_brillance(double)));
        raysLayout->addWidget(brillanceSpinBox);

        //AmbiantLight
        QLabel * ambiantLightLabel = new QLabel("ambiant Light");
        raysLayout->addWidget(ambiantLightLabel);
        QDoubleSpinBox * ambiantLSpinBox = new QDoubleSpinBox();
        ambiantLSpinBox->setRange(0.,2.);
        ambiantLSpinBox->setSingleStep(0.1);
        ambiantLSpinBox->setValue(param->get_ambiantLight());
        connect (ambiantLSpinBox, SIGNAL (valueChanged (double)), param, SLOT(set_ambiantLight(double)));
        raysLayout->addWidget(ambiantLSpinBox);

        //saturation
        QLabel * saturationLabel = new QLabel("saturation");
        raysLayout->addWidget(saturationLabel);
        QDoubleSpinBox * saturationSpinBox = new QDoubleSpinBox();
        saturationSpinBox->setRange(0,100);
        saturationSpinBox->setSingleStep(1);
        saturationSpinBox->setValue(param->get_saturation());
        saturationSpinBox->setDecimals(10);
        connect (saturationSpinBox, SIGNAL (valueChanged (double)), this, SLOT(set_saturation(double)));
        raysLayout->addWidget(saturationSpinBox);

        //material_active
        QCheckBox * materialCheckBox = new QCheckBox ("Material", paramGroupBox);
        materialCheckBox->setChecked(param->get_materialactive());
        connect (materialCheckBox, SIGNAL (toggled (bool)), param, SLOT (set_materialactive (bool)));
        raysLayout->addWidget (materialCheckBox);

        //BRDF_active
        QCheckBox * BRDFCheckBox = new QCheckBox ("BRDF", paramGroupBox);
        BRDFCheckBox->setChecked(param->get_BRDFactive());
        param->set_BRDFcheckbox(BRDFCheckBox);
        connect (BRDFCheckBox, SIGNAL (toggled (bool)), param, SLOT (set_BRDFactive (bool)));
        raysLayout->addWidget (BRDFCheckBox);

        //diff
        QCheckBox * diffCheckBox = new QCheckBox ("Diffuse reflect", paramGroupBox);
        diffCheckBox->setChecked(param->get_diffactive());
        connect (diffCheckBox, SIGNAL (toggled (bool)), param, SLOT (set_diffactive (bool)));
        raysLayout->addWidget (diffCheckBox);

        //spec
        QCheckBox * specCheckBox = new QCheckBox ("Specular reflect", paramGroupBox);
        specCheckBox->setChecked(param->get_specactive());
        connect (specCheckBox, SIGNAL (toggled (bool)), param, SLOT (set_specactive (bool)));
        raysLayout->addWidget (specCheckBox);


    /* SHADOWS, OMBRES */

    QGroupBox * shadowsGroupBox = new QGroupBox ("Shadows");
    QVBoxLayout * shadowsLayout = new QVBoxLayout (shadowsGroupBox);
    paramTab->addTab(shadowsGroupBox, "Shadows");

        //active
        QCheckBox * ombresCheckBox = new QCheckBox ("Shadows", paramGroupBox);
        ombresCheckBox->setChecked(param->get_ombresactive());
        param->set_ombrescheckbox(ombresCheckBox);
        connect (ombresCheckBox, SIGNAL (toggled (bool)), param, SLOT (set_ombresactive (bool)));
        shadowsLayout->addWidget (ombresCheckBox);

        //douces
        QCheckBox * ombresdoucesCheckBox = new QCheckBox ("Soft", paramGroupBox);
        ombresdoucesCheckBox->setChecked(param->get_ombresdouces());
        connect (ombresdoucesCheckBox, SIGNAL (toggled (bool)), param, SLOT (set_ombresdouces (bool)));
        shadowsLayout->addWidget (ombresdoucesCheckBox);

        //numr
        QLabel * ombresnumrLabel = new QLabel("nombres de points par rayon");
        shadowsLayout->addWidget(ombresnumrLabel);
        QSpinBox * ombresnumrSpinBox = new QSpinBox();
        ombresnumrSpinBox->setValue(param->get_ombresnumr());
        connect (ombresnumrSpinBox, SIGNAL (valueChanged (int)), param, SLOT(set_ombresnumr(int)));
        shadowsLayout->addWidget(ombresnumrSpinBox);

        //numa
        QLabel * ombresnumaLabel = new QLabel("nombres de points par angle");
        shadowsLayout->addWidget(ombresnumaLabel);
        QSpinBox * ombresnumaSpinBox = new QSpinBox();
        ombresnumaSpinBox->setValue(param->get_ombresnuma());
        connect (ombresnumaSpinBox, SIGNAL (valueChanged (int)), param, SLOT(set_ombresnuma(int)));
        shadowsLayout->addWidget(ombresnumaSpinBox);

    /* AMBOCC */

    QGroupBox * amboccGroupBox = new QGroupBox ("Ambient Occlusion");
    QVBoxLayout * amboccLayout = new QVBoxLayout (amboccGroupBox);
    paramTab->addTab(amboccGroupBox, "Amb Occ");

        //active
        QCheckBox * amboccCheckBox = new QCheckBox ("Ambient Oclusion", paramGroupBox);
        amboccCheckBox->setChecked(param->get_amboccactive());
        connect (amboccCheckBox, SIGNAL (toggled (bool)), param, SLOT (set_amboccactive (bool)));
        amboccLayout->addWidget (amboccCheckBox);

        //numr
        QLabel * amboccnumrLabel = new QLabel("nray 1");
        amboccLayout->addWidget(amboccnumrLabel);
        QSpinBox * amboccnumrSpinBox = new QSpinBox();
        amboccnumrSpinBox->setValue(param->get_amboccnumr());
        amboccnumrSpinBox->setRange(1,1000);
        connect (amboccnumrSpinBox, SIGNAL (valueChanged (int)), param, SLOT(set_amboccnumr(int)));
        amboccLayout->addWidget(amboccnumrSpinBox);

        //numa
        QLabel * amboccnumaLabel = new QLabel("nray 2");
        amboccLayout->addWidget(amboccnumaLabel);
        QSpinBox * amboccnumaSpinBox = new QSpinBox();
        amboccnumaSpinBox->setValue(param->get_amboccnuma());
        amboccnumaSpinBox->setRange(1,1000);
        connect (amboccnumaSpinBox, SIGNAL (valueChanged (int)), param, SLOT(set_amboccnuma(int)));
        amboccLayout->addWidget(amboccnumaSpinBox);

        //theta
        QLabel * amboccthetaLabel = new QLabel("angle du cone");
        amboccLayout->addWidget(amboccthetaLabel);
        QDoubleSpinBox * amboccthetaSpinBox = new QDoubleSpinBox();
        amboccthetaSpinBox->setRange(0,90);
        amboccthetaSpinBox->setValue(param->get_ambocctheta());
        connect (amboccthetaSpinBox, SIGNAL (valueChanged (double)), param, SLOT(set_ambocctheta(double)));
        amboccLayout->addWidget(amboccthetaSpinBox);

        //rayon
        QLabel * amboccrayonLabel = new QLabel("rayon relatif");
        amboccLayout->addWidget(amboccrayonLabel);
        QDoubleSpinBox * amboccrayonSpinBox = new QDoubleSpinBox();
        amboccrayonSpinBox->setValue(param->get_amboccrayon());
        amboccrayonSpinBox->setRange(0,1);
        amboccrayonSpinBox->setSingleStep(0.05);
        connect (amboccrayonSpinBox, SIGNAL (valueChanged (double)), param, SLOT(set_amboccrayon(double)));
        amboccLayout->addWidget(amboccrayonSpinBox);


    /* KDTREE */

    QGroupBox * kdGroupBox = new QGroupBox ("kdTree");
    QVBoxLayout * kdLayout = new QVBoxLayout (kdGroupBox);
    paramTab->addTab(kdGroupBox, "kdTree");

        //propdeep
        QLabel * kdpropdeepLabel = new QLabel("% of triangles per box");
        kdLayout->addWidget(kdpropdeepLabel);
        QDoubleSpinBox * kdpropdeepSpinBox = new QDoubleSpinBox();
        kdpropdeepSpinBox->setRange(0,1);
        kdpropdeepSpinBox->setSingleStep(0.01);
        kdpropdeepSpinBox->setValue(param->get_kdpropdeep());
        connect (kdpropdeepSpinBox, SIGNAL (valueChanged (double)), param, SLOT(set_kdpropdeep(double)));
        kdLayout->addWidget(kdpropdeepSpinBox);


    /* PATH TRACING */

    QGroupBox * pathGroupBox = new QGroupBox ("Path Tracing");
    QVBoxLayout * pathLayout = new QVBoxLayout (pathGroupBox);
    paramTab->addTab(pathGroupBox,"Path Tracing");

        //active
        QCheckBox * pathCheckBox = new QCheckBox ("Path Tracing", paramGroupBox);
        pathCheckBox->setChecked(param->get_pathactive());
        connect (pathCheckBox, SIGNAL (toggled (bool)), param, SLOT (set_pathactive (bool)));
        pathLayout->addWidget (pathCheckBox);

        //theta
        QLabel * paththetaLabel = new QLabel("angle du cone");
        pathLayout->addWidget(paththetaLabel);
        QDoubleSpinBox * paththetaSpinBox = new QDoubleSpinBox();
        paththetaSpinBox->setRange(0,90);
        paththetaSpinBox->setSingleStep(1);
        paththetaSpinBox->setValue(param->get_paththeta());
        connect (paththetaSpinBox, SIGNAL (valueChanged (double)), param, SLOT(set_paththeta(double)));
        pathLayout->addWidget(paththetaSpinBox);

        //numr
        QLabel * pathnumrLabel = new QLabel("nray 1");
        pathLayout->addWidget(pathnumrLabel);
        QSpinBox * pathnumrSpinBox = new QSpinBox();
        pathnumrSpinBox->setValue(param->get_pathnumr());
        pathnumrSpinBox->setRange(1,1000);
        connect (pathnumrSpinBox, SIGNAL (valueChanged (int)), param, SLOT(set_pathnumr(int)));
        pathLayout->addWidget(pathnumrSpinBox);

        //numa
        QLabel * pathnumaLabel = new QLabel("nray 2");
        pathLayout->addWidget(pathnumaLabel);
        QSpinBox * pathnumaSpinBox = new QSpinBox();
        pathnumaSpinBox->setValue(param->get_pathnuma());
        pathnumaSpinBox->setRange(1,1000);
        connect (pathnumaSpinBox, SIGNAL (valueChanged (int)), param, SLOT(set_pathnuma(int)));
        pathLayout->addWidget(pathnumaSpinBox);

        //maxdeep
        QLabel * pathmaxdeepLabel = new QLabel("max reflexions");
        pathLayout->addWidget(pathmaxdeepLabel);
        QSpinBox * pathmaxdeepSpinBox = new QSpinBox();
        pathmaxdeepSpinBox->setMinimum(1);
        pathmaxdeepSpinBox->setValue(param->get_pathmaxdeep());
        connect (pathmaxdeepSpinBox, SIGNAL (valueChanged (int)), param, SLOT(set_pathmaxdeep(int)));
        pathLayout->addWidget(pathmaxdeepSpinBox);

    paramLayout->addWidget(paramTab);
    layout->addWidget(paramGroupBox);

    /* RAY TRACING */
    
    QGroupBox * rayGroupBox = new QGroupBox ("Ray Tracing", controlWidget);
    QVBoxLayout * rayLayout = new QVBoxLayout (rayGroupBox);
    rayButton = new QPushButton ("Render", rayGroupBox);
    rayLayout->addWidget (rayButton);
    connect (rayButton, SIGNAL (clicked ()), this, SLOT (renderRayImage ()));
    QPushButton * saveButton  = new QPushButton ("Save", rayGroupBox);
    connect (saveButton, SIGNAL (clicked ()) , this, SLOT (exportRayImage ()));
    rayLayout->addWidget (saveButton);

    layout->addWidget (rayGroupBox);

    /* GLOBAL */
    
    QGroupBox * globalGroupBox = new QGroupBox ("Global Settings", controlWidget);
    QVBoxLayout * globalLayout = new QVBoxLayout (globalGroupBox);
    
    QPushButton * bgColorButton  = new QPushButton ("Background Color", globalGroupBox);
    connect (bgColorButton, SIGNAL (clicked()) , this, SLOT (setBGColor()));
    globalLayout->addWidget (bgColorButton);

    QPushButton * aboutButton  = new QPushButton ("About", globalGroupBox);
    connect (aboutButton, SIGNAL (clicked()) , this, SLOT (about()));
    globalLayout->addWidget (aboutButton);
    
    QPushButton * quitButton  = new QPushButton ("Quit", globalGroupBox);
    connect (quitButton, SIGNAL (clicked()) , qApp, SLOT (closeAllWindows()));
    globalLayout->addWidget (quitButton);

    layout->addWidget (globalGroupBox);

    layout->addStretch (0);

}

void Window::set_saturation(double saturation){
    param->set_saturation(saturation);
    param->set_renderdone(true);
    renderRayImage();
    param->set_renderdone(false);
}
