/*************************************************************************
*
*   Iris
*__________________
*
* Iris.Window.Graph.h
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#pragma once



#include <QWidget>


namespace nWindow { class SGraphView; }
namespace nWindow { class SGraphScene; }


namespace nWindow {


class SGraph : public QWidget
{
    Q_OBJECT

    typedef  QWidget    tSuperClass;
    typedef  SGraph      tSelf;

public:
    // Construction / Destruction
    virtual  ~SGraph();
    SGraph( QWidget* iParent = NULL );

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
    SGraphView*     mView;
    SGraphScene*    mScene;

};


} // namespace  nWindow
