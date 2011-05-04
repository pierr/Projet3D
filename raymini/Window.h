#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QToolBar>
#include <QCheckBox>
#include <QGroupBox>
#include <QComboBox>
#include <QSlider>
#include <QLCDNumber>
#include <QSpinBox>
#include <QImage>
#include <QLabel>
#include <QPushButton>

#include <vector>
#include <string>

#include "QTUtils.h"
#include "GLViewer.h"

#include "Parametres.h"

class Window : public QMainWindow {
    Q_OBJECT
public:
    Window();
    virtual ~Window();

    static void showStatusMessage (const QString & msg);  
    
public slots :
    void renderRayImage ();
    void setBGColor ();
    void exportGLImage ();
    void exportRayImage ();
    void about ();
    void set_saturation(double saturation);
    
private :
    
    void initControlWidget ();
        
    QActionGroup * actionGroup;
    QGroupBox * controlWidget;
    QString currentDirectory;

    GLViewer * viewer;
    QLabel * imageLabel;
    QImage rayImage;

    Parametres * param;
    QPushButton * rayButton;
};

#endif // WINDOW_H


// Some Emacs-Hints -- please don't remove:
//
//  Local Variables:
//  mode:C++
//  tab-width:4
//  End:
