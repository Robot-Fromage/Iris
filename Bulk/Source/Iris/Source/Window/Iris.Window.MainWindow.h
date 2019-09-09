/*************************************************************************
*
*   Iris
*__________________
*
* Iris.Window.MainWindow.h
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#pragma once


#include <RivetCustomMainWindow>


#include "Iris.Utils.CustomProperties.h"


namespace  nWindow { class SMainCaption; }
namespace  nWindow { class SMainContent; }


namespace  nWindow {


class SMainWindow :
    public ::Rivet::CustomMainWindow
{
    Q_OBJECT

    Q_PROPERTY( int CustomCaptionHeight READ getCustomCaptionHeight WRITE setCustomCaptionHeight )
    FORWARD_SIMPLE_QPROPERTY( int, CustomCaptionHeight )

    typedef ::Rivet::CustomMainWindow   tSuperClass;
    typedef SMainWindow                 tSelf;

public:
    // Construction / Destruction
    virtual  ~SMainWindow();
    SMainWindow( QWidget*  parent = NULL );

protected:
    // Protected Qt event overrides
    virtual  void  showEvent( QShowEvent*  event )  override;

private:
    // GUI utilities
    void  Init();
    void  Build();

private:
    SMainCaption* mMainCaptionWidget;
    SMainContent* mMainContentWidget;

};


} // namespace  nWindow

