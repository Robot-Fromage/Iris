/*************************************************************************
*
*   Iris
*__________________
*
* Iris.Utils.Settings.cpp
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#include "Iris.Utils.Settings.h"


#include "Iris.Utils.SettingsKeys.h"


#include <QSettings>


//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------- Utility Defines


#define  RESOURCE_FILE  "Resources/settings.ini"


namespace  nUtils {


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


cSettings::~cSettings()
{
    delete  mData;
}


cSettings::cSettings() :
    mData( NULL )
{
    mData = new  QSettings( RESOURCE_FILE, QSettings::IniFormat);
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------ Static Singleton accessor


//static
cSettings*
cSettings::Get()
{
    static  cSettings*  gSettings = NULL;
    if( !gSettings )
        gSettings = new cSettings();

    return gSettings;
}


//static
void
cSettings::Exit()
{
    cSettings* gSettings = cSettings::Get();
    gSettings->Data().sync();
    delete  gSettings;
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------- Getters / Setters


QSettings&
cSettings::Data()  const
{
    return  *mData;
}


QString
cSettings::BaseUrl()  const
{
    return   mData->value( SK_URL, SK_DVAL_URL ).toString();
}


} // namespace  nUtils

