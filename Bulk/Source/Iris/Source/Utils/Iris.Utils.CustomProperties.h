/*************************************************************************
*
*   Iris
*__________________
*
* Iris.Utils.CustomProperties.h
*
* Clement Berthaud - Layl
* Please refer to LICENSE.TXT
*/

#pragma once

#define FORWARD_SIMPLE_QPROPERTY( iType, iName )                        \
    iType m##iName;                                                     \
    public: const  iType##& get##iName() { return m##iName; }           \
    public: void set##iName( const  iType##& iIn ) { m##iName = iIn; }  \
    private:
