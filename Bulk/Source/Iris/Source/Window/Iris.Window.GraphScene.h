/*************************************************************************
*
*   Iris
*__________________
*
* Iris.Window.GraphScene.h
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#pragma once


#include <QGraphicsScene>


#include "Iris.Utils.CustomProperties.h"


namespace nWindow {


class SGraphScene : public QGraphicsScene
{
    Q_OBJECT

    typedef  QGraphicsScene tSuperClass;
    typedef  SGraphScene    tSelf;

public:
    // Construction / Destruction
    virtual  ~SGraphScene();
    SGraphScene( QObject* iParent = NULL );

};


} // namespace nWindow

