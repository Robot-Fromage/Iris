/*************************************************************************
*
*   Iris
*__________________
*
* Iris.Window.MainContent.h
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#pragma once


#include <QWidget>


#include "Iris.Utils.CustomProperties.h"


namespace  nWindow { class SContent; }


namespace  nWindow {


class SMainContent :
    public QWidget
{
    Q_OBJECT

    Q_PROPERTY( QColor BackgroundColor READ getBackgroundColor WRITE setBackgroundColor )
    Q_PROPERTY( QColor BorderBackground READ getBorderBackground WRITE setBorderBackground )
    Q_PROPERTY( QColor BorderOutline READ getBorderOutline WRITE setBorderOutline )
    Q_PROPERTY( int BorderSize READ getBorderSize WRITE setBorderSize )

    FORWARD_SIMPLE_QPROPERTY( QColor, BackgroundColor )
    FORWARD_SIMPLE_QPROPERTY( QColor, BorderBackground )
    FORWARD_SIMPLE_QPROPERTY( QColor, BorderOutline )
    FORWARD_SIMPLE_QPROPERTY( int, BorderSize )

    typedef QWidget         tSuperClass;
    typedef SMainContent    tSelf;

public:
    // Construction / Destruction
    virtual  ~SMainContent();
    SMainContent( QWidget*  parent = NULL );

protected:
    // Event
    virtual  void  resizeEvent( QResizeEvent*   event )  override;
    virtual  void  paintEvent(  QPaintEvent*  event )  override;

private:
    // GUI utilities
    void  Init();
    void  Build();
    void  Compose();
    void  Destroy();

private:
    // Private Data Members
    SContent* mContent;
};


} // namespace  nWindow

