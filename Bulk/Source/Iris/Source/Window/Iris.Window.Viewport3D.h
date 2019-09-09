/*************************************************************************
*
*   Iris
*__________________
*
* Iris.Window.Viewport3D.h
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <QOpenGLWidget>
#include <BokuRaw>

#include "Iris.Utils.CustomProperties.h"

class QTimer;
class QElapsedTimer;
class QGamepad;

namespace nWindow {

/////////////////////////////////////////////////////
// SCanvas
class SCanvas : public QOpenGLWidget
{
    Q_OBJECT

    typedef QOpenGLWidget   tSuperClass;
    typedef SCanvas         tSelf;

public:
    // Construction / Destruction
    virtual  ~SCanvas();
    SCanvas( QWidget*  parent = nullptr );

protected:
    // GL
    virtual  void initializeGL()  override;
    virtual  void resizeGL( int w, int h )  override;
    virtual  void paintGL()  override;

protected:
    // Events
    //virtual void keyPressEvent(QKeyEvent *event) override;
    //virtual void showEvent( QShowEvent* event ) override;

private:
    // Private Data Members
    ::Boku::FInfiniteGridFloor* mFloor;
    ::Boku::FRawBitVolume* mVolume;
    ::Boku::FCamera mCamera;

    QTimer* mTimer;
    QGamepad* mGamepad;
};

} // namespace nWindow

