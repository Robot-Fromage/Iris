/*************************************************************************
*
*   Iris
*__________________
*
* Iris.Window.Graph.cpp
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#include "Iris.Window.Graph.h"


#include "Iris.Window.GraphScene.h"
#include "Iris.Window.GraphView.h"
#include "Iris.Config.h"


#ifdef IRIS_GRAPH_WITH_QOPENGLWIDGET
#include <QOpenGLWidget>
#endif


namespace nWindow {


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


SGraph::~SGraph()
{
    Destroy();
}


SGraph::SGraph( QWidget* iParent ) :
    tSuperClass( iParent ),
    mView(  NULL ),
    mScene( NULL )
{
    Init();
    Build();
    Compose();
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- Event


void
SGraph::resizeEvent( QResizeEvent* event )
{
    tSuperClass::resizeEvent( event );
    Compose();
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------ GUI utilities


void
SGraph::Init()
{
    mView   = new SGraphView();
    mScene  = new SGraphScene();
}


void
SGraph::Build()
{
    setObjectName( "SGraph" );

#ifdef IRIS_GRAPH_WITH_QOPENGLWIDGET
    mView->update();
    QOpenGLWidget* gl = new QOpenGLWidget;
    QSurfaceFormat fmt;
    fmt.setSamples( 8 );
    gl->setFormat(fmt);
    mView->setViewport(gl);
    mView->setViewportUpdateMode( QGraphicsView::SmartViewportUpdate );
    mView->setRenderHint(QPainter::Antialiasing);
    mView->setAttribute(Qt::WA_OpaquePaintEvent);
    mView->setAttribute(Qt::WA_NoSystemBackground);
    mView->viewport()->setAttribute(Qt::WA_OpaquePaintEvent);
    mView->viewport()->setAttribute(Qt::WA_NoSystemBackground);
#endif

    mView->setParent( this );
    mView->setScene( mScene );
    mView->InitScroller();

    /*
    // TMP LEAK NODE
    auto testnode = new ::DraftsmanGUI::Node();
    testnode->setPos( mView->sceneRect().center() );
    mScene->addItem( testnode );
    */
}


void
SGraph::Compose()
{
    int w = width();
    int h = height();
    mView->resize( w, h );
}


void
SGraph::Destroy()
{
    delete mScene;
    delete mView;
}


} // namespace  nWindow
