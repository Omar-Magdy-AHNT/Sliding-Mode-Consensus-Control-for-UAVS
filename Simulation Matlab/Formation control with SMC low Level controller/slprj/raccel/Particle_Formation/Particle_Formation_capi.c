#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "Particle_Formation_capi_host.h"
#define sizeof(...) ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el) ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s) (s)
#ifndef SS_UINT64
#define SS_UINT64 17
#endif
#ifndef SS_INT64
#define SS_INT64 18
#endif
#else
#include "builtin_typeid_types.h"
#include "Particle_Formation.h"
#include "Particle_Formation_capi.h"
#include "Particle_Formation_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST
#define TARGET_STRING(s)               ((NULL))
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif
static const rtwCAPI_Signals rtBlockSignals [ ] = { { 0 , 0 , TARGET_STRING ( "Particle_Formation/Gain" ) , TARGET_STRING ( "Particle 1" ) , 0 , 0 , 0 , 0 , 0 } , { 1 , 0 , TARGET_STRING ( "Particle_Formation/Gain1" ) , TARGET_STRING ( "Particle 2" ) , 0 , 0 , 0 , 0 , 0 } , { 2 , 0 , TARGET_STRING ( "Particle_Formation/Gain2" ) , TARGET_STRING ( "Particel 3" ) , 0 , 0 , 0 , 0 , 0 } , { 3 , 0 , TARGET_STRING ( "Particle_Formation/particle 1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 4 , 0 , TARGET_STRING ( "Particle_Formation/particle 2" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 5 , 0 , TARGET_STRING ( "Particle_Formation/particle 3" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 6 , 0 , TARGET_STRING ( "Particle_Formation/Add" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 7 , 0 , TARGET_STRING ( "Particle_Formation/Add3" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 8 , 0 , TARGET_STRING ( "Particle_Formation/Add4" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 9 , 0 , TARGET_STRING ( "Particle_Formation/Sum" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 10 , 0 , TARGET_STRING ( "Particle_Formation/Sum1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 11 , 0 , TARGET_STRING ( "Particle_Formation/Sum2" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 12 , 0 , TARGET_STRING ( "Particle_Formation/Tpade aprox" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 13 , 0 , TARGET_STRING ( "Particle_Formation/pade aprox" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 14 , 0 , TARGET_STRING ( "Particle_Formation/pade aproxx" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 15 , 0 , TARGET_STRING ( "Particle_Formation/Transport Delay" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 16 , 0 , TARGET_STRING ( "Particle_Formation/Transport Delay1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 17 , 0 , TARGET_STRING ( "Particle_Formation/Transport Delay2" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 , 0 , 0 } } ; static const rtwCAPI_BlockParameters rtBlockParameters [ ] = { { 18 , TARGET_STRING ( "Particle_Formation/Gain" ) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 19 , TARGET_STRING ( "Particle_Formation/Gain1" ) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 20 , TARGET_STRING ( "Particle_Formation/Gain2" ) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 21 , TARGET_STRING ( "Particle_Formation/particle 1" ) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 22 , TARGET_STRING ( "Particle_Formation/particle 2" ) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 23 , TARGET_STRING ( "Particle_Formation/particle 3" ) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 24 , TARGET_STRING ( "Particle_Formation/Sine Wave" ) , TARGET_STRING ( "Amplitude" ) , 0 , 0 , 0 } , { 25 , TARGET_STRING ( "Particle_Formation/Sine Wave" ) , TARGET_STRING ( "Bias" ) , 0 , 0 , 0 } , { 26 , TARGET_STRING ( "Particle_Formation/Sine Wave" ) , TARGET_STRING ( "Frequency" ) , 0 , 0 , 0 } , { 27 , TARGET_STRING ( "Particle_Formation/Sine Wave" ) , TARGET_STRING ( "Phase" ) , 0 , 0 , 0 } , { 28 , TARGET_STRING ( "Particle_Formation/Sine Wave1" ) , TARGET_STRING ( "Amplitude" ) , 0 , 0 , 0 } , { 29 , TARGET_STRING ( "Particle_Formation/Sine Wave1" ) , TARGET_STRING ( "Bias" ) , 0 , 0 , 0 } , { 30 , TARGET_STRING ( "Particle_Formation/Sine Wave1" ) , TARGET_STRING ( "Frequency" ) , 0 , 0 , 0 } , { 31 , TARGET_STRING ( "Particle_Formation/Sine Wave1" ) , TARGET_STRING ( "Phase" ) , 0 , 0 , 0 } , { 32 , TARGET_STRING ( "Particle_Formation/Sine Wave2" ) , TARGET_STRING ( "Amplitude" ) , 0 , 0 , 0 } , { 33 , TARGET_STRING ( "Particle_Formation/Sine Wave2" ) , TARGET_STRING ( "Bias" ) , 0 , 0 , 0 } , { 34 , TARGET_STRING ( "Particle_Formation/Sine Wave2" ) , TARGET_STRING ( "Frequency" ) , 0 , 0 , 0 } , { 35 , TARGET_STRING ( "Particle_Formation/Sine Wave2" ) , TARGET_STRING ( "Phase" ) , 0 , 0 , 0 } , { 36 , TARGET_STRING ( "Particle_Formation/Tpade aprox" ) , TARGET_STRING ( "A" ) , 0 , 1 , 0 } , { 37 , TARGET_STRING ( "Particle_Formation/Tpade aprox" ) , TARGET_STRING ( "C" ) , 0 , 2 , 0 } , { 38 , TARGET_STRING ( "Particle_Formation/Tpade aprox" ) , TARGET_STRING ( "D" ) , 0 , 0 , 0 } , { 39 , TARGET_STRING ( "Particle_Formation/pade aprox" ) , TARGET_STRING ( "A" ) , 0 , 1 , 0 } , { 40 , TARGET_STRING ( "Particle_Formation/pade aprox" ) , TARGET_STRING ( "C" ) , 0 , 2 , 0 } , { 41 , TARGET_STRING ( "Particle_Formation/pade aprox" ) , TARGET_STRING ( "D" ) , 0 , 0 , 0 } , { 42 , TARGET_STRING ( "Particle_Formation/pade aproxx" ) , TARGET_STRING ( "A" ) , 0 , 1 , 0 } , { 43 , TARGET_STRING ( "Particle_Formation/pade aproxx" ) , TARGET_STRING ( "C" ) , 0 , 2 , 0 } , { 44 , TARGET_STRING ( "Particle_Formation/pade aproxx" ) , TARGET_STRING ( "D" ) , 0 , 0 , 0 } , { 45 , TARGET_STRING ( "Particle_Formation/Transport Delay" ) , TARGET_STRING ( "DelayTime" ) , 0 , 0 , 0 } , { 46 , TARGET_STRING ( "Particle_Formation/Transport Delay" ) , TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 47 , TARGET_STRING ( "Particle_Formation/Transport Delay1" ) , TARGET_STRING ( "DelayTime" ) , 0 , 0 , 0 } , { 48 , TARGET_STRING ( "Particle_Formation/Transport Delay1" ) , TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 49 , TARGET_STRING ( "Particle_Formation/Transport Delay2" ) , TARGET_STRING ( "DelayTime" ) , 0 , 0 , 0 } , { 50 , TARGET_STRING ( "Particle_Formation/Transport Delay2" ) , TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 } } ; static int_T rt_LoggedStateIdxList [ ] = { - 1 } ; static const rtwCAPI_Signals rtRootInputs [ ] = { { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 , 0 , 0 } } ; static const rtwCAPI_Signals rtRootOutputs [ ] = { { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 , 0 , 0 } } ; static const rtwCAPI_ModelParameters rtModelParameters [ ] = { { 0 , ( NULL ) , 0 , 0 , 0 } } ;
#ifndef HOST_CAPI_BUILD
static void * rtDataAddrMap [ ] = { & rtB . ptphzuvop1 , & rtB . ipinknkdjw ,
& rtB . ctvsr11p5w , & rtB . e2zzue3dqs , & rtB . fjb04try4d , & rtB .
g5esbnluar , & rtB . hnh4jhnugu , & rtB . a533om0agu , & rtB . me0wxpghb2 , &
rtB . pp2geatnp3 , & rtB . nywxolg44y , & rtB . biejfirm0b , & rtB .
n1ycoq2c4c , & rtB . a20mrpkyci , & rtB . cdsmzpyna0 , & rtB . a1qv0n5lch , &
rtB . dsvgxjjkad , & rtB . cmxuw1zmtj , & rtP . Gain_Gain , & rtP .
Gain1_Gain , & rtP . Gain2_Gain , & rtP . particle1_IC , & rtP . particle2_IC
, & rtP . particle3_IC , & rtP . SineWave_Amp , & rtP . SineWave_Bias , & rtP
. SineWave_Freq , & rtP . SineWave_Phase , & rtP . SineWave1_Amp , & rtP .
SineWave1_Bias , & rtP . SineWave1_Freq , & rtP . SineWave1_Phase , & rtP .
SineWave2_Amp , & rtP . SineWave2_Bias , & rtP . SineWave2_Freq , & rtP .
SineWave2_Phase , & rtP . Tpadeaprox_A [ 0 ] , & rtP . Tpadeaprox_C [ 0 ] , &
rtP . Tpadeaprox_D , & rtP . padeaprox_A [ 0 ] , & rtP . padeaprox_C [ 0 ] ,
& rtP . padeaprox_D , & rtP . padeaproxx_A [ 0 ] , & rtP . padeaproxx_C [ 0 ]
, & rtP . padeaproxx_D , & rtP . TransportDelay_Delay , & rtP .
TransportDelay_InitOutput , & rtP . TransportDelay1_Delay , & rtP .
TransportDelay1_InitOutput , & rtP . TransportDelay2_Delay , & rtP .
TransportDelay2_InitOutput , } ; static int32_T * rtVarDimsAddrMap [ ] = { ( NULL ) } ;
#endif
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap [ ] = { { "double" ,
"real_T" , 0 , 0 , sizeof ( real_T ) , ( uint8_T ) SS_DOUBLE , 0 , 0 , 0 } }
;
#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif
static TARGET_CONST rtwCAPI_ElementMap rtElementMap [ ] = { { ( NULL ) , 0 ,
0 , 0 , 0 } , } ; static const rtwCAPI_DimensionMap rtDimensionMap [ ] = { {
rtwCAPI_SCALAR , 0 , 2 , 0 } , { rtwCAPI_VECTOR , 2 , 2 , 0 } , {
rtwCAPI_VECTOR , 4 , 2 , 0 } } ; static const uint_T rtDimensionArray [ ] = {
1 , 1 , 2 , 1 , 1 , 2 } ; static const real_T rtcapiStoredFloats [ ] = { 0.0
, 1.0 } ; static const rtwCAPI_FixPtMap rtFixPtMap [ ] = { { ( NULL ) , ( NULL
) , rtwCAPI_FIX_RESERVED , 0 , 0 , ( boolean_T ) 0 } , } ; static const
rtwCAPI_SampleTimeMap rtSampleTimeMap [ ] = { { ( const void * ) &
rtcapiStoredFloats [ 0 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] , ( int8_T ) 1 , ( uint8_T ) 0 } , { ( const void * ) & rtcapiStoredFloats [ 0 ] , ( const void * ) & rtcapiStoredFloats [ 0 ] , ( int8_T ) 0 , ( uint8_T ) 0 } } ; static rtwCAPI_ModelMappingStaticInfo mmiStatic = { { rtBlockSignals , 18 , rtRootInputs , 0 , rtRootOutputs , 0 } , { rtBlockParameters , 33 , rtModelParameters , 0 } , { ( NULL ) , 0 } , { rtDataTypeMap , rtDimensionMap , rtFixPtMap , rtElementMap , rtSampleTimeMap , rtDimensionArray } , "float" , { 308571330U , 3659227219U , 1697557035U , 3822737628U } , ( NULL ) , 0 , ( boolean_T ) 0 , rt_LoggedStateIdxList } ; const rtwCAPI_ModelMappingStaticInfo * Particle_Formation_GetCAPIStaticMap ( void ) { return & mmiStatic ; }
#ifndef HOST_CAPI_BUILD
void Particle_Formation_InitializeDataMapInfo ( void ) { rtwCAPI_SetVersion ( ( * rt_dataMapInfoPtr ) . mmi , 1 ) ; rtwCAPI_SetStaticMap ( ( * rt_dataMapInfoPtr ) . mmi , & mmiStatic ) ; rtwCAPI_SetLoggingStaticMap ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ; rtwCAPI_SetDataAddressMap ( ( * rt_dataMapInfoPtr ) . mmi , rtDataAddrMap ) ; rtwCAPI_SetVarDimsAddressMap ( ( * rt_dataMapInfoPtr ) . mmi , rtVarDimsAddrMap ) ; rtwCAPI_SetInstanceLoggingInfo ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ; rtwCAPI_SetChildMMIArray ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ; rtwCAPI_SetChildMMIArrayLen ( ( * rt_dataMapInfoPtr ) . mmi , 0 ) ; }
#else
#ifdef __cplusplus
extern "C" {
#endif
void Particle_Formation_host_InitializeDataMapInfo ( Particle_Formation_host_DataMapInfo_T * dataMap , const char * path ) { rtwCAPI_SetVersion ( dataMap -> mmi , 1 ) ; rtwCAPI_SetStaticMap ( dataMap -> mmi , & mmiStatic ) ; rtwCAPI_SetDataAddressMap ( dataMap -> mmi , ( NULL ) ) ; rtwCAPI_SetVarDimsAddressMap ( dataMap -> mmi , ( NULL ) ) ; rtwCAPI_SetPath ( dataMap -> mmi , path ) ; rtwCAPI_SetFullPath ( dataMap -> mmi , ( NULL ) ) ; rtwCAPI_SetChildMMIArray ( dataMap -> mmi , ( NULL ) ) ; rtwCAPI_SetChildMMIArrayLen ( dataMap -> mmi , 0 ) ; }
#ifdef __cplusplus
}
#endif
#endif
