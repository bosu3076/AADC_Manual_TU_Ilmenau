/*********************************************************************
Copyright (c) 2018
Audi Autonomous Driving Cup. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
3.  All advertising materials mentioning features or use of this software must display the following acknowledgement: ?This product includes software developed by the Audi AG and its contributors for Audi Autonomous Driving Cup.?
4.  Neither the name of Audi nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY AUDI AG AND CONTRIBUTORS AS IS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL AUDI AG OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

**********************************************************************/

#pragma once

#include "stdafx.h"
#include "aadc_structs.h"
//#include "header file"

//*************************************************************************************************
#define CID_TEMPLATEFILTER_DATA_TRIGGERED_FILTER "template_filter.filter.user.aadc.cid"

using namespace adtf_util;
using namespace ddl;
using namespace adtf::ucom;
using namespace adtf::base;
using namespace adtf::streaming;
using namespace adtf::mediadescription;
using namespace adtf::filter;
using namespace std;

typedef struct _TEMPLATE_STRUCT
{
    float value_1;
    int value_2;
}TEMPLATE_STRUCT;

class cOptIlm_TemplateFilter : public cTriggerFunction
{
private:
    /*! Media Descriptions. */
    struct tTemplateDataId
    {
        tSize timeStamp;
        tSize Valuename_1;
        //If more arguments are needed, you can set more like:
        //tSize Valuename2 
    } m_ddlTemplateDataId;


    /*! The template data sample factory */
    adtf::mediadescription::cSampleCodecFactory m_templateDataSampleFactory;

    /*! The template filter property */
    property_variable<tFloat32> m_property = 0.0f;

    /*! Reader of an InPin. */
    cPinReader m_oReader_1;
    //If multi-inpins
    //cPinReader m_oReader_2;

    /*! Writer to an OutPin. */
    cPinWriter m_oWriter_1;
    //if multi-outpins
    //cPinWriter m_oWriter_2

public:

    /*! Default constructor. */
    cOptIlm_TemplateFilter();

    /*! Destructor. */
    virtual ~cOptIlm_TemplateFilter() = default;

    /**
    * Overwrites the Configure
    * This is to Read Properties prepare your Trigger Function
    */
    tResult Configure() override;
    /**
    * Overwrites the Process
    * You need to implement the Reading and Writing of Samples within this function
    * MIND: Do Reading until the Readers queues are empty or use the IPinReader::GetLastSample()
    * This Function will be called if the Run() of the TriggerFunction was called.
    */
    tResult Process(tTimeStamp tmTimeOfTrigger) override;
    /**
    * Overwrites the GetValue
    * This is to get value from reader
    */
    tResult GetValue(void);
    /**
    * Overwrites the SendValue
    * This is to send value to writer
    */
    tResult SendValue(float template_value);



};


//*************************************************************************************************
