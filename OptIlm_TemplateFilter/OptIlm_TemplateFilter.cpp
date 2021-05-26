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

#include "OptIlm_TemplateFilter.h"

TEMPLATE_STRUCT *template_value;

ADTF_TRIGGER_FUNCTION_FILTER_PLUGIN(CID_TEMPLATEFILTER_DATA_TRIGGERED_FILTER,
    "OptIlm_TemplateDataFilter",
    cOptIlm_TemplateFilter,
    adtf::filter::pin_trigger({"input_name"})); // Filter triggered by certain input signal
    //adtf::filter::timer_trigger(200000)); // Or triggered with time
    //adtf::filter::thread_trigger(true));// Or with thread trigger

cOptIlm_TemplateFilter::cOptIlm_TemplateFilter()
{
    //DO NOT FORGET TO LOAD MEDIA DESCRIPTION SERVICE IN ADTF3 AND CHOOSE aadc.description
    object_ptr<IStreamType> pTypeTemplateData;
    if IS_OK(adtf::mediadescription::ant::create_adtf_default_stream_type_from_service("tTemplateData", pTypeTemplateData, m_templateDataSampleFactory))
    {
        (adtf_ddl::access_element::find_index(m_SignalValueSampleFactory, cString("ui32ArduinoTimestamp"), m_ddlSignalValueId.timeStamp));
        (adtf_ddl::access_element::find_index(m_templateDataSampleFactory, cString("f32Value"), m_ddlTemplateDataId.f32Value));    
    }
    else
    {
        LOG_WARNING("No mediadescription for tTemplateData found!");
    }

    Register(m_oReader_1, "input_name" , pTypeTemplateData);
    Register(m_oWriter_1, "output_name", pTypeTemplateData);
}
//implement the Configure function to read ALL Properties
tResult cOptIlm_TemplateFilter::Configure()
{
    //Register Properties 
    RegisterPropertyVariable("template_property", m_property);
    RETURN_NOERROR;
}

tResult cOptIlm_TemplateFilter::Process(tTimeStamp tmTimeOfTrigger)
{
    GetValue();
    //some calculation like:
    template_value->value_1 = template_value->value_1 + 10.0f;
    template_value->value_2 = 2;

    SendValue(template_value->value_1);
}

tResult cOptIlm_TemplateFilter::GetValue(void)
{
    object_ptr<const ISample> pReadSample;

    //tFloat32 inputData;

    if (IS_OK(m_oReader_1.GetLastSample(pReadSample)))
    {
        auto oDecoder = m_templateDataSampleFactory.MakeDecoderFor(*pReadSample);

        RETURN_IF_FAILED(oDecoder.IsValid());

        // retrieve the values (using convenience methods that return a variant)
        RETURN_IF_FAILED(oDecoder.GetElementValue(m_ddlTemplateDataId.f32Value, &template_value->value_1));

    }
    RETURN_NOERROR;
}
tResult cOptIlm_TemplateFilter::SendValue(float template_value)
{
    object_ptr<ISample> pWriteSample;

    if (IS_OK(alloc_sample(pWriteSample)))
    {

        auto oCodec = m_templateDataSampleFactory.MakeCodecFor(pWriteSample);

        RETURN_IF_FAILED(oCodec.SetElementValue(m_ddlTemplateDataId.f32Value, template_value));

    }
    m_oWriter_1 << pWriteSample << flush << trigger;
    
    RETURN_NOERROR;
}