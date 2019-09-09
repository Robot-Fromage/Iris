/*************************************************************************
*
*   Iris
*__________________
*
* Iris.Utils.Settings.h
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#pragma once


#include <QSettings>


#include "Iris.Utils.SettingsKeys.h"


namespace  nUtils {


class cSettings
{
    typedef cSettings   tSelf;

private:
    // Construction / Destruction
    virtual  ~cSettings();
    cSettings();

public:
    // Static Singleton accessor
    static  cSettings*  Get();
    static  void        Exit();

public:
    // Getters / Setters
    QSettings&  Data()      const;
    QString     BaseUrl()   const;

private:
    QSettings*  mData;
};


} // namespace  nUtils

