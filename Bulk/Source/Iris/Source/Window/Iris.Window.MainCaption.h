/*************************************************************************
*
*   Iris
*__________________
*
* Iris.Window.MainCaption.h
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#pragma once


#include <RivetCustomCaption>
#include <RivetCustomButton>
#include <RivetTabArea>


#include "Iris.Utils.CustomProperties.h"


class  QPixmap;
class  QLabel;


namespace  nWindow {


class SMainCaption :
    public ::Rivet::CustomCaption
{
    Q_OBJECT
    Q_PROPERTY( QColor BackgroundGradientStart READ getBackgroundGradientStart WRITE setBackgroundGradientStart )
    Q_PROPERTY( QColor BackgroundGradientStop READ getBackgroundGradientStop WRITE setBackgroundGradientStop )
    Q_PROPERTY( QColor BorderColor READ getBorderColor WRITE setBorderColor )
    Q_PROPERTY( QColor OutlineColor READ getOutlineColor WRITE setOutlineColor )
    Q_PROPERTY( int ButtonShapeSize READ getButtonShapeSize WRITE setButtonShapeSize )
    Q_PROPERTY( QColor ButtonColor READ getButtonColor WRITE setButtonColor )
    Q_PROPERTY( QColor ButtonHoveredBackgroundColor READ getButtonHoveredBackgroundColor WRITE setButtonHoveredBackgroundColor )
    Q_PROPERTY( QColor CloseButtonHoveredBackgroundColor READ getCloseButtonHoveredBackgroundColor WRITE setCloseButtonHoveredBackgroundColor )
    Q_PROPERTY( QColor ButtonPressedBackgroundColor READ getButtonPressedBackgroundColor WRITE setButtonPressedBackgroundColor )
    Q_PROPERTY( QColor CloseButtonPressedBackgroundColor READ getCloseButtonPressedBackgroundColor WRITE setCloseButtonPressedBackgroundColor )

    FORWARD_SIMPLE_QPROPERTY( QColor, BackgroundGradientStart )
    FORWARD_SIMPLE_QPROPERTY( QColor, BackgroundGradientStop )
    FORWARD_SIMPLE_QPROPERTY( QColor, BorderColor )
    FORWARD_SIMPLE_QPROPERTY( QColor, OutlineColor )
    FORWARD_SIMPLE_QPROPERTY( int, ButtonShapeSize )
    FORWARD_SIMPLE_QPROPERTY( QColor, ButtonColor )
    FORWARD_SIMPLE_QPROPERTY( QColor, ButtonHoveredBackgroundColor )
    FORWARD_SIMPLE_QPROPERTY( QColor, CloseButtonHoveredBackgroundColor )
    FORWARD_SIMPLE_QPROPERTY( QColor, ButtonPressedBackgroundColor )
    FORWARD_SIMPLE_QPROPERTY( QColor, CloseButtonPressedBackgroundColor )

    typedef ::Rivet::CustomCaption  tSuperClass;
    typedef SMainCaption            tSelf;

public:
    struct cAccessibleChildren
    {
        ::Rivet::CustomButton*  mCloseButton;
        ::Rivet::CustomButton*  mMaximizeButton;
        ::Rivet::CustomButton*  mMinimizeButton;
    };

public:
    // Construction / Destruction
    virtual  ~SMainCaption();
    SMainCaption( QWidget*  parent = NULL );

public:
    // Accessible Children
    cAccessibleChildren  AccessibleChildren()  const;

public:
    // HitTest override
    virtual  bool  HitEmptySpace( long iX, long iY )  override;

protected:
    // Protected Qt event overrides
    virtual  void  resizeEvent( QResizeEvent*   event )  override;
    virtual  void  paintEvent(  QPaintEvent*  event )  override;
    virtual  void  showEvent(  QShowEvent*  event )  override;

private:
    // GUI utilities
    void  Init();
    void  Build();
    void  Compose();
    void  Destroy();

private:
    // Private Data Members
    ::Rivet::CustomButton*  mCloseButton;
    ::Rivet::CustomButton*  mMaximizeButton;
    ::Rivet::CustomButton*  mMinimizeButton;

    QPushButton*            mFaviconButton;

    ::Rivet::TabArea*  mTabArea;
};


} // namespace  nWindow

