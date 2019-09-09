/*************************************************************************
*
*   Iris
*__________________
*
* Iris.Window.Content.h
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#pragma once


#include <QWidget>


#include "Iris.Utils.CustomProperties.h"


namespace  Rivet { class TabArea; }
class QStackedWidget;

namespace  nWindow {


class SContent :
    public QWidget
{
    Q_OBJECT

    typedef QWidget         tSuperClass;
    typedef SContent        tSelf;

public:
    // Construction / Destruction
    virtual  ~SContent();
    SContent( QWidget*  parent = NULL );

protected:
    // Event
    virtual  void  resizeEvent( QResizeEvent*   event )  override;

private:
    // GUI utilities
    void  Init();
    void  Build();
    void  Compose();
    void  Destroy();

private:
    // Private Data Members
    ::Rivet::TabArea* mTabArea;
    QStackedWidget* mStack;
    QWidget* mWidget2D;
    QWidget* mWidget3D;
};


} // namespace  nWindow

