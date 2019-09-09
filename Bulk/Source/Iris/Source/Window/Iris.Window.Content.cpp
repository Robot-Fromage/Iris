/*************************************************************************
*
*   Iris
*__________________
*
* Iris.Window.Content.cpp
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#include "Iris.Window.Content.h"


#include <QPainter>
#include <QMouseEvent>
#include <QStackedWidget>
#include <QTextEdit>

#include <RivetTabArea>
#include <RivetDockingManager>
#include <RivetDockingCallbackLibrary>

#include "Iris.Utils.Settings.h"
#include "Iris.Window.Graph.h"


namespace  nWindow {


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


SContent::~SContent()
{
    Destroy();
}


SContent::SContent( QWidget*  parent )
    : tSuperClass( parent )
    , mStack( nullptr )
    , mWidget2D( nullptr )
    , mWidget3D( nullptr )
{
    Init();
    Build();
    Compose();
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- Event


void
SContent::resizeEvent( QResizeEvent* event )
{
    tSuperClass::resizeEvent( event );
    Compose();
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------ GUI utilities


void
SContent::Init()
{
    mTabArea = new  ::Rivet::TabArea( this );
    mStack = new QStackedWidget( this );
    mWidget2D = new  SGraph();
    mWidget3D = new  QTextEdit();

}


void
SContent::Build()
{
    setObjectName( "SContent" );
    mTabArea->SetOverlap( 10 );
    mTabArea->SetTabsShapeStyle( ::Rivet::Tab::eShapeStyle::kLine );
    mTabArea->SetTabsClosable( false );
    mTabArea->SetTabsLiftable( false );
    mTabArea->SetLinkedStack( mStack );

    ::Rivet::Tab* tab2D = new ::Rivet::Tab();
    tab2D->SetTitle( "Chromaticity 2D" );
    tab2D->SetClosable( false );
    tab2D->SetColor( QColor( 255, 127, 0 ) );
    tab2D->SetLinkWidget( mWidget2D );

    ::Rivet::Tab* tab3D = new ::Rivet::Tab();
    tab3D->SetTitle( "Chromaticity 3D" );
    tab3D->SetClosable( false );
    tab3D->SetColor( QColor( 0, 127, 255 ) );
    tab3D->SetLinkWidget( mWidget3D );

    mTabArea->ManualAddNewTab( tab2D );
    mTabArea->ManualAddNewTab( tab3D );
    mTabArea->SetCurrentTab( tab2D );
}


void
SContent::Compose()
{
    int w = width();
    int h = height();

    mTabArea->resize( w, 28 );

    mStack->resize( w, h-28 );
    mStack->move( 0, 28 );
}


void
SContent::Destroy()
{
    delete  mWidget2D;
    delete  mWidget3D;
    delete  mTabArea;
    delete  mStack;
}


} // namespace  nWindow

