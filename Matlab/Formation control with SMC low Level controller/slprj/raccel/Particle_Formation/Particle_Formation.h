#ifndef Particle_Formation_h_
#define Particle_Formation_h_
#ifndef Particle_Formation_COMMON_INCLUDES_
#define Particle_Formation_COMMON_INCLUDES_
#include <stdio.h>
#include <stdlib.h>
#include "sl_AsyncioQueue/AsyncioQueueCAPI.h"
#include "rtwtypes.h"
#include "sigstream_rtw.h"
#include "simtarget/slSimTgtSigstreamRTW.h"
#include "simtarget/slSimTgtSlioCoreRTW.h"
#include "simtarget/slSimTgtSlioClientsRTW.h"
#include "simtarget/slSimTgtSlioSdiRTW.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "raccel.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "rt_logging_simtarget.h"
#include "rt_nonfinite.h"
#include "math.h"
#include "dt_info.h"
#include "ext_work.h"
#endif
#include "Particle_Formation_types.h"
#include <stddef.h>
#include "rtw_modelmap_simtarget.h"
#include "rt_defines.h"
#include <string.h>
#include "rtGetInf.h"
#define MODEL_NAME Particle_Formation
#define NSAMPLE_TIMES (2) 
#define NINPUTS (0)       
#define NOUTPUTS (0)     
#define NBLOCKIO (18) 
#define NUM_ZC_EVENTS (0) 
#ifndef NCSTATES
#define NCSTATES (9)   
#elif NCSTATES != 9
#error Invalid specification of NCSTATES defined in compiler command
#endif
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm) (*rt_dataMapInfoPtr)
#endif
#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val) (rt_dataMapInfoPtr = &val)
#endif
#ifndef IN_RACCEL_MAIN
#endif
typedef struct { real_T fjb04try4d ; real_T e2zzue3dqs ; real_T a533om0agu ;
real_T ipinknkdjw ; real_T g5esbnluar ; real_T me0wxpghb2 ; real_T ctvsr11p5w
; real_T hnh4jhnugu ; real_T ptphzuvop1 ; real_T pp2geatnp3 ; real_T
nywxolg44y ; real_T biejfirm0b ; real_T cmxuw1zmtj ; real_T n1ycoq2c4c ;
real_T a1qv0n5lch ; real_T dsvgxjjkad ; real_T a20mrpkyci ; real_T cdsmzpyna0
; } B ; typedef struct { struct { real_T modelTStart ; } prbv25b4a4 ; struct
{ real_T modelTStart ; } ntedjwdf1h ; struct { real_T modelTStart ; }
e5gujoeptl ; struct { void * AQHandles ; } nciphwtgmu ; struct { void *
AQHandles ; } atgnxzwsfi ; struct { void * AQHandles ; } e5segooeqn ; struct
{ void * TUbufferPtrs [ 2 ] ; } jsieubeqtv ; struct { void * TUbufferPtrs [ 2
] ; } lpdyzycrq1 ; struct { void * TUbufferPtrs [ 2 ] ; } mnepvfp0ps ; struct
{ int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } ijsewem34h ; struct { int_T Tail ; int_T Head ; int_T Last
; int_T CircularBufSize ; int_T MaxNewBufSize ; } enah0kmzof ; struct { int_T
Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize
; } o04jm0syzv ; int_T hqmlfpsniu ; int_T foctzw0ndr ; int_T ftu2djce5m ; }
DW ; typedef struct { real_T dyvc0i15qx ; real_T jcj4ib11ty ; real_T
gpfyhy3ruq ; real_T mbrvobjcrk [ 2 ] ; real_T kzy22patnd [ 2 ] ; real_T
dw1alq3vli [ 2 ] ; } X ; typedef struct { real_T dyvc0i15qx ; real_T
jcj4ib11ty ; real_T gpfyhy3ruq ; real_T mbrvobjcrk [ 2 ] ; real_T kzy22patnd
[ 2 ] ; real_T dw1alq3vli [ 2 ] ; } XDot ; typedef struct { boolean_T
dyvc0i15qx ; boolean_T jcj4ib11ty ; boolean_T gpfyhy3ruq ; boolean_T
mbrvobjcrk [ 2 ] ; boolean_T kzy22patnd [ 2 ] ; boolean_T dw1alq3vli [ 2 ] ;
} XDis ; typedef struct { real_T dyvc0i15qx ; real_T jcj4ib11ty ; real_T
gpfyhy3ruq ; real_T mbrvobjcrk [ 2 ] ; real_T kzy22patnd [ 2 ] ; real_T
dw1alq3vli [ 2 ] ; } CStateAbsTol ; typedef struct { real_T dyvc0i15qx ;
real_T jcj4ib11ty ; real_T gpfyhy3ruq ; real_T mbrvobjcrk [ 2 ] ; real_T
kzy22patnd [ 2 ] ; real_T dw1alq3vli [ 2 ] ; } CXPtMin ; typedef struct {
real_T dyvc0i15qx ; real_T jcj4ib11ty ; real_T gpfyhy3ruq ; real_T mbrvobjcrk
[ 2 ] ; real_T kzy22patnd [ 2 ] ; real_T dw1alq3vli [ 2 ] ; } CXPtMax ;
typedef struct { real_T p2x5zq3ylo ; real_T d1kecvqtqw ; real_T gx2uanechy ;
} ZCV ; typedef struct { rtwCAPI_ModelMappingInfo mmi ; } DataMapInfo ;
struct P_ { real_T particle2_IC ; real_T particle1_IC ; real_T Gain1_Gain ;
real_T particle3_IC ; real_T Gain2_Gain ; real_T Gain_Gain ; real_T
SineWave_Amp ; real_T SineWave_Bias ; real_T SineWave_Freq ; real_T
SineWave_Phase ; real_T SineWave1_Amp ; real_T SineWave1_Bias ; real_T
SineWave1_Freq ; real_T SineWave1_Phase ; real_T SineWave2_Amp ; real_T
SineWave2_Bias ; real_T SineWave2_Freq ; real_T SineWave2_Phase ; real_T
TransportDelay2_Delay ; real_T TransportDelay2_InitOutput ; real_T
Tpadeaprox_A [ 2 ] ; real_T Tpadeaprox_C [ 2 ] ; real_T Tpadeaprox_D ; real_T
TransportDelay_Delay ; real_T TransportDelay_InitOutput ; real_T
TransportDelay1_Delay ; real_T TransportDelay1_InitOutput ; real_T
padeaprox_A [ 2 ] ; real_T padeaprox_C [ 2 ] ; real_T padeaprox_D ; real_T
padeaproxx_A [ 2 ] ; real_T padeaproxx_C [ 2 ] ; real_T padeaproxx_D ; } ;
extern const char_T * RT_MEMORY_ALLOCATION_ERROR ; extern B rtB ; extern X
rtX ; extern DW rtDW ; extern P rtP ; extern mxArray *
mr_Particle_Formation_GetDWork ( ) ; extern void
mr_Particle_Formation_SetDWork ( const mxArray * ssDW ) ; extern mxArray *
mr_Particle_Formation_GetSimStateDisallowedBlocks ( ) ; extern const
rtwCAPI_ModelMappingStaticInfo * Particle_Formation_GetCAPIStaticMap ( void )
; extern SimStruct * const rtS ; extern DataMapInfo * rt_dataMapInfoPtr ;
extern rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr ; void MdlOutputs ( int_T
tid ) ; void MdlOutputsParameterSampleTime ( int_T tid ) ; void MdlUpdate ( int_T tid ) ; void MdlTerminate ( void ) ; void MdlInitializeSizes ( void ) ; void MdlInitializeSampleTimes ( void ) ; SimStruct * raccel_register_model ( ssExecutionInfo * executionInfo ) ;
#endif
