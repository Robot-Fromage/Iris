/*************************************************************************
*
*   Iris
*__________________
*
* Iris.Window.GraphScene.cpp
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#include "Iris.Window.GraphScene.h"


#include <QPainter>


namespace nWindow {


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


SGraphScene::~SGraphScene()
{
}


SGraphScene::SGraphScene( QObject* iParent ) :
    tSuperClass( iParent )
{
    setObjectName( "SGraphScene" );
}


} // namespace nWindow

