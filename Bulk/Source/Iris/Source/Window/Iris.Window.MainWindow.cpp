/*************************************************************************
*
*   Iris
*__________________
*
* Iris.Window.MainWindow.cpp
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#include "Iris.Window.MainWindow.h"


#include "Iris.Window.MainCaption.h"
#include "Iris.Window.MainContent.h"


namespace  nWindow {


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


SMainWindow::~SMainWindow()
{
}


SMainWindow::SMainWindow( QWidget*  parent ) :
    tSuperClass( parent ),
    mMainCaptionWidget( NULL ),
    mMainContentWidget( NULL )
{
    tSelf::Init();
    tSelf::Build();
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------- Protected Qt event overrides


void
SMainWindow::showEvent( QShowEvent*  event )
{
    tSuperClass::showEvent( event );
    tSuperClass::SetCaptionHeight( getCustomCaptionHeight() );
    tSuperClass::Recompose();
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------ GUI utilities


void
SMainWindow::Init()
{
    mMainCaptionWidget = new SMainCaption( NULL );
    mMainContentWidget = new SMainContent( NULL );
}


void
SMainWindow::Build()
{
    setObjectName( "SMainWindow" );
    setWindowIcon( QIcon( "Resources/media/img/favicon.png" ) );
    tSuperClass::SetCaptionWidget( mMainCaptionWidget );
    tSuperClass::SetCenterWidget( mMainContentWidget );
}


} // namespace  nWindow

