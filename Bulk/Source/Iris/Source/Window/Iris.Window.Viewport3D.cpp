/*************************************************************************
*
*   Iris
*__________________
*
* Iris.Window.Viewport3D.cpp
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#include "Iris.Window.Viewport3D.h"

#include <QTimer>
#include <QGamepad>
#include <QEvent>
#include <QKeyEvent>
#include <QGamepadKeyNavigation>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace nWindow {
/////////////////////////////////////////////////////
// SCanvas
//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction
SCanvas::~SCanvas()
{
    delete  mFloor;
    delete  mVolume;
    delete  mTimer;
    delete  mGamepad;
}


SCanvas::SCanvas( QWidget*  parent )
    : QOpenGLWidget( parent )
    , mFloor( nullptr )
    , mVolume( nullptr )
    , mCamera( ::Boku::FCamera() )
    , mTimer( nullptr )
    , mGamepad( nullptr )
{
    auto gamepads = QGamepadManager::instance()->connectedGamepads();
    if( !gamepads.isEmpty() ) {
        mGamepad = new QGamepad(*gamepads.begin(), this);
    }
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------- GL
void
SCanvas::initializeGL()
{
    glewInit();
    glClearColor( 0.8, 0.8, 0.8, 1.0 );
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //glCullFace( GL_FRONT );

    printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));

    mFloor = new ::Boku::FInfiniteGridFloor( "Resources/Assets/Textures/GridTex0.png" );
    mFloor->Load();

    QImage* img = new QImage( "Resources/Assets/Textures/height_sand.png" );
    int height = 100;
    int w = img->width();
    int h = img->height();
    int hw = w / 2;
    int hh = h / 2;
    int pad = 10;
    float scale = 25;
    mVolume = new ::Boku::FRawBitVolume( w, height, h );
    for( int i = 0; i < w; ++i )
    {
        for( int j = 0; j < h; ++j )
        {
            float val = img->pixelColor( i, j ).redF();
            int elevation = pad + val * scale;
            for( int k = 0; k < elevation; ++k )
            {
                mVolume->SetElement( 1, i, k, j );
            }

            if( i > 20 && i < 40 && j > 20 && j < 40 )
            {
                for( int k = 0; k < height; ++k )
                    mVolume->SetElement( 1, i, k, j );
            }
        }
    }

    mVolume->Load();
    mVolume->BuildVBO();
    //mVolume->Transformation().SetPivot( hw, 0, hh );
    delete img;

    /*
    mVolume = new ::Boku::FRawBitVolume( 5, 5, 5 );
    for( int i = 0; i < 5; ++i )
        for( int j = 0; j < 4; ++j )
            for( int k = 0; k < 5; ++k )
                mVolume->SetElement( 1, i, j, k );

    mVolume->Load();
    mVolume->BuildVBO();
    mVolume->Transformation().SetPivot( 2, 2, 2 );
    mVolume->Transformation().SetTranslationY( 5 );
    mVolume->ComputeNormal( 2, 3, 2 );
    */
    mVolume->Transformation().Translate( 10, 0, 10 );

    mCamera.SetNear( 5.f );
    mCamera.SetFar( 10000.f );
    mCamera.SetFov( ::Boku::kPIf / 3 );
    //mCamera.Transformation().Translate( 0, 0, 300 );
    //mCamera.Transformation().Translate( 300, 200, 300 );
    //mCamera.Transformation().Target( mVolume->Transformation().Translation() );

    mTimer = new QTimer();
    mTimer->setInterval( 1000.0 / 60.0 );
    QObject::connect( mTimer, SIGNAL( timeout() ), this, SLOT( update() ) );
    mTimer->start();

}


void
SCanvas::resizeGL( int w, int h )
{
    mCamera.SetViewportSize( w, h );
}


void
SCanvas::paintGL()
{
    if( mGamepad )
    {
        if( mGamepad->buttonL1() )
            mCamera.Transformation().MoveForward( 3 );

        if( mGamepad->buttonR1() )
            mCamera.Transformation().MoveForward( -3 );

        mCamera.Transformation().Nutate( -mGamepad->axisRightY() / 30 );
        mCamera.Transformation().Precess( -mGamepad->axisRightX() / 30 );
        mCamera.Transformation().MoveRight( mGamepad->axisLeftX() * 2 );
        mCamera.Transformation().MoveUp( -mGamepad->axisLeftY() * 2 );

        if( mGamepad->buttonL2() )
            mCamera.Transformation().Roll( +0.01 );

        if( mGamepad->buttonR2() )
            mCamera.Transformation().Roll( -0.01 );
    }

    if( mCamera.Transformation().Translation().y < 10 )
        mCamera.Transformation().SetTranslationY( 10 );

    //mCamera.Transformation().Target( glm::vec3( 0, 100, 0 ) );
    //mCamera.Transformation().MoveRight( 2 );

    // Update
    //mVolume->Transformation().Yaw( -0.001 );
    //mVolume->Transformation().Pitch( 0.002 );
    //mVolume->Transformation().Roll( 0.02 );

    // Clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mVolume->Render( mCamera );
    mFloor->Render( mCamera );
    glUseProgram( 0 );
}

//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------- Events

} // namespace nWindow
