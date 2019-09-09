/*************************************************************************
*
*   Iris
*__________________
*
* Iris.Window.MainContent.cpp
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#include "Iris.Window.MainContent.h"


#include <QPainter>
#include <QMouseEvent>


#include "Iris.Utils.Settings.h"
#include "Iris.Window.Content.h"


namespace  nWindow {


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


SMainContent::~SMainContent()
{
    Destroy();
}


SMainContent::SMainContent( QWidget*  parent )
    : tSuperClass( parent )
    , mContent( nullptr )
{
    Init();
    Build();
    Compose();
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- Event


void
SMainContent::resizeEvent( QResizeEvent* event )
{
    tSuperClass::resizeEvent( event );
    Compose();
}


void
SMainContent::paintEvent(  QPaintEvent*  event )
{
    tSuperClass::paintEvent( event );

    // Init painting
    QPainter painter(this);
    painter.setRenderHint( QPainter::Antialiasing, false );
    int w = width();
    int h = height();

    bool mUseBorders = !( topLevelWidget()->isMaximized() );

    if( mUseBorders )
    {
        //CHECK: C'est le bordel ici...
        painter.setBrush( Qt::NoBrush );
        painter.setPen( getBorderOutline() );
        painter.drawLine( 0, 0, 0, height() );
        painter.drawLine( width() - 1, 0, width() - 1, height() );
        painter.drawLine( 0, height() - 1, width() - 1, height() - 1 );

        painter.setBrush( getBorderBackground() );
        painter.setPen( Qt::NoPen );
        painter.drawRect( 1, 0, getBorderSize() - 2, height() - 1 );
        painter.drawRect( 1, height() - ( getBorderSize() - 1 ), width() - 2, getBorderSize() - 2 );
        painter.drawRect( width() - getBorderSize() + 1, 0, getBorderSize() - 2, height() - 1 );

        painter.setBrush( getBackgroundColor() );
        painter.setPen( getBorderOutline() );
        painter.drawRect( getBorderSize() - 1, 0, width() - getBorderSize() * 2 + 1, height() - getBorderSize() );

    }
    else
    {
        // Painting background
        painter.setBrush( getBackgroundColor() );
        painter.setPen( getBorderOutline() );
        // Notice: minus 1, else outline is drawn out of bounds for Right & Bottom
        painter.drawRect( 0, 0, width() - 1, height() - 1 );
    }
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------ GUI utilities


void
SMainContent::Init()
{
    mContent = new SContent( this );
}


void
SMainContent::Build()
{
    setObjectName( "SMainContent" );
}


void
SMainContent::Compose()
{
    int w = width();
    int h = height();

    bool useBorder = !( topLevelWidget()->isMaximized() );
    int p   = useBorder ? getBorderSize() : 1;
    int p2  = p * 2;

    mContent->setGeometry( p, 1, w - p2, h - p - 1 );
}


void
SMainContent::Destroy()
{
    delete  mContent;
}


} // namespace  nWindow

