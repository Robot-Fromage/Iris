/*************************************************************************
*
*   Iris
*__________________
*
* Iris.Window.MainCaption.cpp
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#include "Iris.Window.MainCaption.h"


#include <RivetDockingCallbackLibrary>


#include <QLabel>
#include <QPainter>
#include <QPixmap>


#include "Iris.Utils.Settings.h"


namespace  nWindow {


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


SMainCaption::~SMainCaption()
{
    tSelf::Destroy();
}


SMainCaption::SMainCaption( QWidget*  parent ) :
    tSuperClass( parent ),
    mCloseButton(       NULL ),
    mMaximizeButton(    NULL ),
    mMinimizeButton(    NULL ),
    mFaviconButton(     NULL ),
    mTabArea(           NULL )
{
    tSelf::Init();
    tSelf::Build();
    tSelf::Compose();
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------ Accessible Children


SMainCaption::cAccessibleChildren
SMainCaption::AccessibleChildren()  const
{
    return  cAccessibleChildren{
                mCloseButton,
                mMaximizeButton,
                mMinimizeButton,
            };
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------- HitTest override


bool
SMainCaption::HitEmptySpace( long iX, long iY )
{
    QPoint local = mapFromParent( QPoint( iX, iY ) );
    bool result = true;

    QList< QWidget* > list = this->findChildren< QWidget* >();

    // If a direct child contains our mouse coordinates, we refute.
    for each( QWidget* w in list ) {
        QRect g = w->geometry();
        if( g.contains( local ) && w->parent() == this )
        {
            result = false;
        }
    }

    //OBSOLETE:
    // But if it is the tab area, we ask it for more details.
    if( result == false && mTabArea->geometry().contains( local ) )
        result = mTabArea->HitEmptySpace( local.x(), local.y() );

    return  result;
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------- Protected Qt event overrides


void
SMainCaption::resizeEvent( QResizeEvent *event )
{
    tSuperClass::resizeEvent(event);
    Compose();
}

void
SMainCaption::paintEvent(  QPaintEvent*  event )
{
    // Init painting
    QPainter painter(this);
    painter.setRenderHint( QPainter::Antialiasing, false );
    int w = width();
    int h = height();

    QLinearGradient vertical_gradient( 0, 0, 0, h );
    vertical_gradient.setColorAt(0.0, getBackgroundGradientStart() );
    vertical_gradient.setColorAt(1.0, getBackgroundGradientStop() );

    // Painting background
    painter.setBrush( vertical_gradient );
    painter.setPen( getBorderColor() );
    // Notice: minus 1, else outline is drawn out of bounds for Right & Bottom
    painter.drawRect( 0, 0, width() - 1, height() - 1 );

    painter.setBrush( Qt::NoBrush );
    painter.setPen( getBackgroundGradientStop() );
    painter.drawLine( 1, height() - 1, width() - 2, height() - 1 );

    painter.setBrush( Qt::NoBrush );
    painter.setPen( getOutlineColor() );
    painter.drawLine( 1, 1, width() - 2, 1 );
};


void
SMainCaption::showEvent(  QShowEvent*  event )
{
    mCloseButton->SetSize( getButtonShapeSize() );
    mMaximizeButton->SetSize( getButtonShapeSize() );
    mMinimizeButton->SetSize( getButtonShapeSize() );

    #define UTIL_SETCOLOR( iBtn, iColor )   \
    iBtn->SetColor( iColor );               \
    iBtn->SetHoveredColor( iColor );        \
    iBtn->SetPressedColor( iColor );

    UTIL_SETCOLOR( mCloseButton, getButtonColor() );
    UTIL_SETCOLOR( mMaximizeButton, getButtonColor() );
    UTIL_SETCOLOR( mMinimizeButton, getButtonColor() );

    #undef UTIL_SETCOLOR

    mCloseButton->SetHoveredBackgroundColor( getCloseButtonHoveredBackgroundColor() );
    mMaximizeButton->SetHoveredBackgroundColor( getButtonHoveredBackgroundColor() );
    mMinimizeButton->SetHoveredBackgroundColor( getButtonHoveredBackgroundColor() );

    mCloseButton->SetPressedBackgroundColor( getCloseButtonPressedBackgroundColor() );
    mMaximizeButton->SetPressedBackgroundColor( getButtonPressedBackgroundColor() );
    mMinimizeButton->SetPressedBackgroundColor( getButtonPressedBackgroundColor() );
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------ GUI utilities


void
SMainCaption::Init()
{
    if( !mCloseButton )     mCloseButton    = new  ::Rivet::CustomButton( this );
    if( !mMaximizeButton )  mMaximizeButton = new  ::Rivet::CustomButton( this );
    if( !mMinimizeButton )  mMinimizeButton = new  ::Rivet::CustomButton( this );

    //HARDCODED:
    if( !mFaviconButton )   mFaviconButton  = new QPushButton( this );

    if( !mTabArea )         mTabArea        = new ::Rivet::TabArea( this );
}


void
SMainCaption::Build()
{
    setObjectName( "SMainCaption" );

    mCloseButton->SetShape( ::Rivet::CustomButton::eShape::kClose );
    mMaximizeButton->SetShape( ::Rivet::CustomButton::eShape::kMaximize );
    mMinimizeButton->SetShape( ::Rivet::CustomButton::eShape::kMinimize );

    QObject::connect( mCloseButton, SIGNAL( clicked() ), this, SLOT( ProcessCloseClicked() ) );
    QObject::connect( mMaximizeButton, SIGNAL( clicked() ), this, SLOT( ProcessMaximizeClicked() ) );
    QObject::connect( mMinimizeButton, SIGNAL( clicked() ), this, SLOT( ProcessMinimizeClicked() ) );

    // prevent trigger by press space
    mMinimizeButton->setFocusPolicy( Qt::NoFocus );
    mMaximizeButton->setFocusPolicy( Qt::NoFocus );
    mCloseButton->setFocusPolicy( Qt::NoFocus );

    mFaviconButton->setObjectName( "capButton" );
    QPixmap faviconPixmap("Resources/media/img/favicon.png");
    QIcon faviconIcon( faviconPixmap );
    mFaviconButton->setIcon( faviconIcon );
    mFaviconButton->setCursor( Qt::PointingHandCursor );

    auto tab = new ::Rivet::Tab();
    tab->SetTitle( SK_VAL( NAME ).toString() );
    mTabArea->SetTabsLiftable( false );
    mTabArea->SetTabsClosable( false );
    tab->SetClosable( false );
    mTabArea->SetOnTabDroppedOutCB( ::Rivet::OnTabDroppedOutCB_RevertBack );
    mTabArea->ManualAddNewTab( tab );
}


void
SMainCaption::Compose()
{
    int w = width();
    int h = height();

    float buttonRatio   = 1.5f;
    int buttonHeight    = h;
    int buttonWidth     = buttonHeight * buttonRatio;

    QSize buttonSize( buttonWidth, buttonHeight - 2 );
    mCloseButton->resize( buttonSize );
    mMaximizeButton->resize( buttonSize );
    mMinimizeButton->resize( buttonSize );

    int n = 0;
    mCloseButton->move(     w - 1 - buttonWidth * ++n, 1 );
    mMaximizeButton->move(  w - 1 - buttonWidth * ++n, 1 );
    mMinimizeButton->move(  w - 1 - buttonWidth * ++n, 1 );

    // LOGO
    mFaviconButton->resize( h - 10 , h - 10 );
    mFaviconButton->move( 5, 5 );

    // TAB
    mTabArea->resize( w - 1 - buttonWidth * ++n, h - 2 );
    mTabArea->move( h, 2 );
}


void
SMainCaption::Destroy()
{
    delete  mCloseButton;
    delete  mMaximizeButton;
    delete  mMinimizeButton;

    delete  mFaviconButton;

    delete  mTabArea;
}


} // namespace  nWindow

