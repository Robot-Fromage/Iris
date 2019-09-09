/*************************************************************************
*
*   Iris
*__________________
*
* Iris.main.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <assert.h>

#include <QApplication>
#include <QDir>
#include <QDesktopWidget>
#include <QFontDatabase>
#include <QWidget>

#include <ULIS_CORE>

#include "Iris.Utils.Settings.h"
#include "Iris.Window.MainWindow.h"


int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );

    // Global Data Initialisation
    {
        // Reading and applying style sheet.
        QFile  file( "Resources/media/css/style.qss" );
        if( file.open( QFile::ReadOnly ) )
        {
            QString  qss = QLatin1String( file.readAll() );
            app.setStyle( "plastique" );
            app.setStyleSheet( qss );
            file.close();
        }

        // Reading and loading embedded fonts
        QString fontDirPath = "Resources/media/font";
        QStringList filter = QStringList() << "*.ttf";
        QDir fontDir( fontDirPath );
        QStringList fontFiles = fontDir.entryList( filter );
        for( auto it : fontFiles ) {
            auto fontPath = fontDirPath + "/" + it;
            int id = QFontDatabase::addApplicationFont ( fontPath );
            assert( id > -1 );
        }
    }

    // Main Window settings
    bool    maximized = SK_VAL( MAXIMIZED ).toBool();
    bool    centered = false;
    int     w = maximized ? SK_DVAL_WIDTH   : SK_VAL( WIDTH ).toInt();
    int     h = maximized ? SK_DVAL_HEIGHT  : SK_VAL( HEIGHT ).toInt();
    int     x = maximized ? SK_DVAL_POSX    : SK_VAL( POSX ).toInt();
    int     y = maximized ? SK_DVAL_POSY    : SK_VAL( POSY ).toInt();

    if( x == SK_DVAL_POSX && y == SK_DVAL_POSY )
        centered = true;

    // Main Window initialisation
    auto mwd = new ::nWindow::SMainWindow();
    mwd->resize( w, h );

    if( centered )
        mwd->move( qApp->desktop()->availableGeometry( mwd ).center() - mwd->rect().center() );
    else
        mwd->move( x, y );

    if( maximized )
        mwd->showMaximized();
    else
        mwd->show();

    // Qt Event Loop
    int exit_code = app.exec();

    // Settings sync
    SK_SETVAL( URL, SK_VAL( URL ) );
    SK_SETVAL( WIDTH, mwd->width() );
    SK_SETVAL( HEIGHT, mwd->height() );
    SK_SETVAL( POSX, mwd->x() );
    SK_SETVAL( POSY, mwd->y() );
    SK_SETVAL( MAXIMIZED, mwd->CheckCustomWindowMaximizedState() );
    ::nUtils::cSettings::Exit();

    // Data Cleanup
    delete mwd;

    // Exit
    return exit_code;
}

