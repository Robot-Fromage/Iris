/*************************************************************************
*
*   Iris
*__________________
*
* Iris.Utils.SettingsKeys.h
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#pragma once


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------- Default Key Values


#define  SK_URL             "sk_url"
#define  SK_NAME            "sk_name"
#define  SK_WIDTH           "sk_width"
#define  SK_HEIGHT          "sk_height"
#define  SK_POSX            "sk_posx"
#define  SK_POSY            "sk_posy"
#define  SK_MAXIMIZED       "sk_maximized"


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------- Default Key Values


#define  SK_DVAL_URL        "https://praxinos.coop/dev/doc/"
#define  SK_DVAL_NAME       "Iris"
#define  SK_DVAL_WIDTH      1000
#define  SK_DVAL_HEIGHT     500
#define  SK_DVAL_POSX       -1
#define  SK_DVAL_POSY       -1
#define  SK_DVAL_MAXIMIZED  false

//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------- Simple accessor


#define SK_VAL( iKey )              ::nUtils::cSettings::Get()->Data().value( SK_##iKey, SK_DVAL_##iKey )
#define SK_SETVAL( iKey, iVal )     ::nUtils::cSettings::Get()->Data().setValue( SK_##iKey, iVal )

