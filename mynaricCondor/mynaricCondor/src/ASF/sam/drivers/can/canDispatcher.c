/*
 * canDispatcher.c
 *
 * Created: 2/23/2023 2:30:15 PM
 *  Author: j.castano
 */ 
#include "canDispatcher.h"
#include "can.h"
#include "LaserData.h"
#include "lnaStateMachine.h"
#include "mpbLogEvent.h"
#include "TimeBaseManagement.h"
#include "BSPCan.h"
#include "BSPAdc.h"
#include "boosterStateMachine.h"
/* Private define ----------------------------------------------------------- */
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
/* Private functions -------------------------------------------------------- */
static void vGetLogInfo(void);
static void vSetterFactory(void);
static void vGetterFactory(void);
static eSequenceA_t eSequenceA = eSequenceA401;
static eSequenceB_t eSequenceB = eSequenceBInit;
static uint32_t  ulCounterSequenceA = 0;
static uint32_t  ulCounterSequenceB = 0;
static uint32_t ulCanTxSequence;

static eBool_t bUnitInDebugMode = eFalse;
/* Exported functions ------------------------------------------------------- */
static void vSendMpbFrame( uint8_t ucChannel);
static void vSendStateData( uint8_t eHpaState, uint8_t eLnaState, uint8_t eMainLoopState, uint8_t eHpaApcState);
static void vSendMpbStatusData( c428StatusDefinition_t *pc428StatusDefinition);
static void vSendRawData( uint8_t ucChannel);
static void vRunSequenceA(void);
static void vRunSequenceB(void);
static void testSend401(void);
static void testSend402(void);
static void testSend403(void);
static void testSend404(void);
static void testSend405(void);
static void testSend415(void);
static void testSend414(void);
static void testSend40A(void);
static void testSend411(void);
static void testSend423(void);


static void vSendMpbFrame( uint8_t ucChannel)
{
	CAN_FRAME				pCan;
	c428StatusDefinition_t c428StatusDefinition;
	eMpbError_t				eMpbError = eUnknownError;
	
	
	xAmplifierDescriptor_t *pxLaserBeamDescriptor;
	pxLaserBeamDescriptor = vGetxAmplifierDescriptor( );
	
	switch(ucChannel)
	{
		case 1:
		
		 eMpbError = eMpbCan428Encode( &(pxLaserBeamDescriptor->c428StatusDefinition) );
      				//vLaserDataGetCan405Info( &c405Definition );		 
		 getCan428( &pCan);
		 vCanDispatcherSendCanMessage( &pCan );
		
		break;
		
		default:
		break;
		
		
	}
	
	
}
/*-----------------------------------------------*/
static void vSendStateData( uint8_t eHpaState, uint8_t eLnaState, uint8_t eMainLoopState, uint8_t eHpaApcState)
{
	CAN_FRAME				pCan;
	c426StatusDefinition_t c426StatusDefinition;
	float fValue =0.0f;
	
	c426StatusDefinition.ucIndex = 0x99;
	c426StatusDefinition.usLnaState = eLnaState;
	c426StatusDefinition.usBoosterState = eHpaState;
	c426StatusDefinition.eHpaApcState = eHpaApcState;
	
	
	c426StatusDefinition.usCommonState = eMainLoopState;
	//c426StatusDefinition.usBoosterState = 0;
	
	eMpbCan426Encode( &c426StatusDefinition );
		
	getCan426( &pCan);
	vCanDispatcherSendCanMessage( &pCan );
	
}

static void vSendMpbStatusData( c428StatusDefinition_t *pc428StatusDefinition)
{
	CAN_FRAME				pCan;
	c426StatusDefinition_t c426StatusDefinition;
	
	typedef union
	{
		MpbAlarmsAndStatusRegisterBitAssignment_t MpbAlarmsAndStatusRegisterBitAssignment;
		uint8_t ucMpbData[8];
		uint64_t ucValue;
	}MyMpbStatusData_t;
	
	MyMpbStatusData_t MyMpbStatusData;
	MyConversionData_t MyConversionData;
	
	MyMpbStatusData.MpbAlarmsAndStatusRegisterBitAssignment = pc428StatusDefinition->MpbAlarmsAndStatusRegisterBitAssignment;
	
	MyConversionData.ucValue[0] = MyMpbStatusData.ucMpbData[0];
	MyConversionData.ucValue[1] = MyMpbStatusData.ucMpbData[1];
	MyConversionData.ucValue[2] = MyMpbStatusData.ucMpbData[2];
	MyConversionData.ucValue[3] = MyMpbStatusData.ucMpbData[3];
	
	c426StatusDefinition.fRawData = MyConversionData.fValue;
	c426StatusDefinition.ucIndex = 0x98;
	
	c426StatusDefinition.usCommonState		= MyMpbStatusData.ucMpbData[4];
	c426StatusDefinition.usLnaState	= MyMpbStatusData.ucMpbData[5];
	c426StatusDefinition.usBoosterState = MyMpbStatusData.ucMpbData[6];
	
	
	
	
	/*typedef union
	{
		float fValue;
		uint8_t ucValue[4];
	}MyConversionData_t;*/
	
		
	
	float fValue =0.0f;
	
	
	
	
	//c426StatusDefinition.usLnaState = eLnaState;
	//c426StatusDefinition.usCommonState = eMainLoopState;
	//c426StatusDefinition.usBoosterState = 0;
	
	eMpbCan426Encode( &c426StatusDefinition );
	
	getCan426( &pCan);
	vCanDispatcherSendCanMessage( &pCan );
	
}
/*-----------------------------------------------*/
static void vSendRawData( uint8_t ucChannel)
{
	CAN_FRAME				pCan;
	c426StatusDefinition_t c426StatusDefinition;
	float fValue =0.0f;
	
	xAmplifierDescriptor_t *pxLaserBeamDescriptor;
	pxLaserBeamDescriptor = vGetxAmplifierDescriptor( );
	
	c426StatusDefinition.ucIndex = ucChannel;
	c426StatusDefinition.usLnaState = 0x55;
	c426StatusDefinition.usCommonState = 0x55;
	c426StatusDefinition.usBoosterState = 0x55;
	
	
//	ucChannel = eAdcExHpaSmld_Bfm ;
//	ucChannel =  eAdcExPd_Ref2 ; 
	
	if( ucChannel  == eAdcExLna_Inm)
	{
		fValue = pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExLna_Inm_raw;
	}
	else if( ucChannel  == eAdcExLna_OutM1 )
	{
		fValue = pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExLna_OutM1_raw;
	}
	else if( ucChannel  == eAdcExLna_OutM2)
	{
		fValue = pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExLna_OutM2_raw;
	}
	else if( ucChannel  == eAdcExHpa_Inm)
	{
		fValue = pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExHpa_Inm_raw;
	}
	else if( ucChannel  == eAdcExHpa_OutLm)
	{
		fValue = pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExHpa_OutL_raw;
	}
	else if( ucChannel  == eAdcExHpa_OutHm)
	{
		fValue = pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExHpa_OutHm_raw;
	}	
	else if( ucChannel  == eAdcExPd_Ref1)
	{
		fValue = pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExPd_Ref1_raw;
	}	
	else if( ucChannel  == eAdcExLnaSmld_Bfm)
	{
		fValue = pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExLnaSmld_Bfm_raw;
	}	
	else if( ucChannel  == eAdcExLnaSmldCurrentMonitor)
	{
		fValue = pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExLnaSmldCurrentMonitor_raw;
	}	
	else if( ucChannel  == eAdcExHpaSmld_CurrentMonitor)
	{
		fValue = pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExHpaSmld_CurrentMonitor_raw;
	}
	else if( ucChannel  == eAdcExHpaMmld_CurrentMonitor1)
	{
		fValue = pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor1_raw;
	}	
	else if( ucChannel  == eAdcExHpaMmld_CurrentMonitor2)
	{
		fValue = pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExHpaMmld_CurrentMonitor2_raw;
	}	
	else if( ucChannel  == eAdcExLnaSmld_Thermistor)
	{
		fValue = pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExLnaSmld_Thermistor_raw;
	}	
	else if( ucChannel  == eAdcExHpaSmld_Thermistor)
	{
		fValue = pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExHpaSmld_Thermistor_raw;
	}
	else if( ucChannel  == eAdcExHpaMMld_Thermistor1)
	{
		fValue = pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExHpaMMld_Thermistor1_raw;
	}	
	else if( ucChannel  == eAdcExHpaMMld_Thermistor2)
	{
		fValue = pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExHpaMMld_Thermistor2_raw;
	}
	else if( ucChannel  == eAdcExHpaMMld_Thermistor3)
	{
		fValue = pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExHpaMMld_Thermistor3_raw;
	}
	else if( ucChannel  == eAdcExHpaMMld_Thermistor4)
	{
		fValue = pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExHpaMMld_Thermistor4_raw;
	}
	else if( ucChannel  == eAdcExCaseThermistor1)
	{
		fValue = pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExCaseThermistor1_raw;
	}
	else if( ucChannel  == eAdcExHpaSmld_Bfm)
	{
		fValue = pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExHpaSmld_Bfm_raw;
	}
	
	else if( ucChannel  == eAdcExPd_Ref2)
	{
		fValue = pxLaserBeamDescriptor->xExternalAdcChannlesRaw.usAdcExPd_Ref2_raw;
	}	
	
	else if( ucChannel  == TEMPERATURE_LNA_TH)
	{
		fValue = pxLaserBeamDescriptor->xExternalAnalogThermistorsInputs.fExternalThermistorLnaSmLd;
	}

	else if( ucChannel  == TEMPERATURE_HPA_SM_TH)
	{
		fValue = pxLaserBeamDescriptor->xExternalAnalogThermistorsInputs.fExternalThermistorHpaSmLd;
	}	
	
	else if( ucChannel  == TEMPERATURE_HPA_MM_1_TH)
	{
		fValue = pxLaserBeamDescriptor->xExternalAnalogThermistorsInputs.fExternalThermistorHpaMmLd1;
	}
	
	else if( ucChannel  == TEMPERATURE_HPA_MM_2_TH)
	{
		fValue = pxLaserBeamDescriptor->xExternalAnalogThermistorsInputs.fExternalThermistorHpaMmLd2;
	}
	
	else if( ucChannel  == TEMPERATURE_HPA_MM_3_TH)
	{
		fValue = pxLaserBeamDescriptor->xExternalAnalogThermistorsInputs.fExternalThermistorHpaMmLd3;
	}	

	else if( ucChannel  == TEMPERATURE_HPA_MM_4_TH)
	{
		fValue = pxLaserBeamDescriptor->xExternalAnalogThermistorsInputs.fExternalThermistorHpaMmLd4;
	}
	else if( ucChannel  == LNA_INPUT_POWER_MW)
	{
		fValue = pxLaserBeamDescriptor->xPowersInMiliWats.fExternalLnaOpticalInputtPower;
	}
	
	else if( ucChannel  == LNA_OUTPUT_POWER_MW)
	{
		fValue = pxLaserBeamDescriptor->xPowersInMiliWats.fInternalLnaOpticalOutputMonitor1;
	}
	else if( ucChannel  == LNA_SP_IND_DBM)
	{
			fValue = pxLaserBeamDescriptor->xPowersIndBM.fLnaSetpointInApcIndbm;
	}
	else if( ucChannel  == HPA_SM_BACKFACET_IN_MA)
	{
		fValue = pxLaserBeamDescriptor->xAnalogInputs.fExtern_LnaSmPowerBackFacetMonitor;
		
	}
	else if( ucChannel  == HPA_OUTPUT_MONITOR_LH_IN_MW)
	{
		fValue = pxLaserBeamDescriptor->xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Lm ;
		
	}
	else if( ucChannel  == HPA_OUTPUT_MONITOR_HH_IN_MW)
	{
		fValue = pxLaserBeamDescriptor->xPowersInMiliWats.fExternalHpaOpticalOutputMonitor_Hm ;
	
	}	
	
	
	
	
	c426StatusDefinition.fRawData = fValue;
	
	eMpbCan426Encode( &c426StatusDefinition );
	
	getCan426( &pCan);
	vCanDispatcherSendCanMessage( &pCan );
	
	
	
}


static void testSend405(void)
{
	uint8_t ucCompanyId = 0;
	CAN_FRAME				pCan;
	
	c405Definition_t c405Definition;


	vLaserDataGetCan405Info( &c405Definition );
	

	eMpbCan405Encode( &c405Definition );

	getCan405( &pCan);
	vCanDispatcherSendCanMessage( &pCan );
	
	
}
/*--------------------------------------------------------------------*/
static void testSend404(void)
{
	CAN_FRAME				pCan;
	c404StatusDefinition_t c404StatusDefinition;
	
	/* retrieve the data 404 from the database */
	vLaserDataGetCan404Info( &c404StatusDefinition );
	
	/*prepare the CAN packet 404 and set the CAN image */
	eMpbCan404Encode( &c404StatusDefinition);

	/* get the 404 CAN image */
	getCan404( &pCan);

	/* send it*/
	vCanDispatcherSendCanMessage( &pCan );
	
}
/*--------------------------------------------------------------------*/
static void testSend403(void)
{
	CAN_FRAME				pCan;
	c403StatusDefinition_t c403StatusDefinition;
	
	vLaserDataGetCan403Info( &c403StatusDefinition );
	
	/*prepare the CAN packet 402 and set the CAN image */
	eMpbCan403Encode( &c403StatusDefinition);

	/* get the 403 CAN image */
	getCan403( &pCan);

	/* send it*/
	vCanDispatcherSendCanMessage( &pCan );
	
}
/*--------------------------------------------------------------------*/
static void testSend402(void)
{
	CAN_FRAME				pCan;
	c402StatusDefinition_t *pc402StatusDefinition;
	c406PacketControlDefinition_t *pc406PacketControlDefinition;
	
	pc402StatusDefinition = vLaserDataGetData402( );
	pc406PacketControlDefinition = vLaserDataGetData406();
	
	/*pc402StatusDefinition->xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterEnableLaserDriver1Status = pc406PacketControlDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucBoosterEnablePumpLaser1;
	pc402StatusDefinition->xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaEnableLaserDriverStatus = pc406PacketControlDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucLnaEnablePumpLaser4;
	pc402StatusDefinition->xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterMode = pc406PacketControlDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucSetBoosterControlMode;
	pc402StatusDefinition->xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaMode = pc406PacketControlDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucSetLnaControlMode;
	
	pc402StatusDefinition->xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bRxLnaChannelSelection = pc406PacketControlDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucSetRxChannelOnLna;
	pc402StatusDefinition->xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bTxBoostChannelSelection = pc406PacketControlDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucSetTxChannelOnBooster;
	*/
	/*prepare the CAN packet 402 and set the CAN image */
	eMpbCan402Encode( pc402StatusDefinition);

	/* get the 402 CAN image */
	getCan402( &pCan);

	/* send it*/
	vCanDispatcherSendCanMessage( &pCan );
	
}
/*--------------------------------------------------------------------*/
static void testSend401(void)
{
	CAN_FRAME				pCan;
	c401StatusDefinition_t c401StatusDefinition;
	vLaserDataGetCan401Info( &c401StatusDefinition );
	
	/*prepare the CAN packet 401 and set the CAN image */
	eMpbCan401Encode( &c401StatusDefinition );
	
	
	
	/* get the 401 CAN image */
	getCan401( &pCan);
	
	/* send it*/
	vCanDispatcherSendCanMessage( &pCan );
	
//	memset( &c401StatusDefinition, 0, sizeof( c401StatusDefinition_t)  );
		
//	eMpbCan401Decode( &c401StatusDefinition );
}
/*--------------------------------------------------------------------*/
static void testSend414(void)
{
	CAN_FRAME				pCan;
	c414StatusDefinition_t *pc414StatusDefinition= NULL;
	c406PacketControlDefinition_t *pc406PacketControlDefinition;
	
	eBool_t bBoosterIsDisable = eFalse;
	eBool_t bLnaIsDisable = eFalse;
	
	//vLaserDataGetCan414Info( &c414StatusDefinition );
	pc414StatusDefinition = pLaserDataGetCan414Info();
	
	xAmplifierDescriptor_t *pxLaserBeamDescriptor;
	pxLaserBeamDescriptor = vGetxAmplifierDescriptor( );
	
	pc406PacketControlDefinition = vLaserDataGetData406();
	
	
	bBoosterIsDisable = (pc406PacketControlDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucBoosterEnablePumpLaser1 == 1)? eFalse : eTrue;
//	bLnaIsDisable = (pxLaserBeamDescriptor->eLnaState == 0)? eTrue : eFalse  ;
	bLnaIsDisable = ( eLnaReportState() == 0)? eTrue : eFalse  ;
	
	
	//(pc406PacketControlDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucLnaEnablePumpLaser4 == 1)? eFalse : eTrue;
	
	/*prepare the CAN packet 401 and set the CAN image */
	eMpbCan414Encode( pc414StatusDefinition ,  bBoosterIsDisable,  bLnaIsDisable );
	
	
	
	/* get the 401 CAN image */
	getCan414( &pCan);
	
	/* send it*/
	vCanDispatcherSendCanMessage( &pCan );
	
//	memset( &c414StatusDefinition, 0, sizeof( c414StatusDefinition_t)  );
	
//	eMpbCan414Decode( &c414StatusDefinition );
	
	
}
/*--------------------------------------------------------------------*/
static void testSend415(void)
{
	CAN_FRAME				pCan;
	c415StatusDefinition_t *pc415StatusDefinition;
	c409StatusDefinition_t c409StatusDefinition;
	
	//xBoosterParameters_t *pxBoosterParameters= NULL;
	//pxBoosterParameters = vGetpxBoosterParameters( );
	
	xAmplifierDescriptor_t *pxLaserBeamDescriptor;
	pxLaserBeamDescriptor = vGetxAmplifierDescriptor( );
	
	pc415StatusDefinition = pLaserDataGetCan415Info(  );
	
	
	vLaserDataGetCan409Info( &c409StatusDefinition );
	
	pc415StatusDefinition->fUnitBaseTemperatureLowAlarmLimit  =  pxLaserBeamDescriptor->xPumpTemperaturesLimits.fUnitBaseTemperatureLowAlarmLimit; 
	pc415StatusDefinition->fUnitBaseTemperatureHighAlarmLimit =  pxLaserBeamDescriptor->xPumpTemperaturesLimits.fUnitBaseTemperatureHighAlarmLimit; 
	
	
	pc415StatusDefinition->fPumpTemperatureLowAlarmLimit  = pxLaserBeamDescriptor->xPumpTemperaturesLimits.fPumpTemperatureLowAlarmLimit; 
	pc415StatusDefinition->fPumpTemperatureHighAlarmLimit = pxLaserBeamDescriptor->xPumpTemperaturesLimits.fPumpTemperatureHighAlarmLimit;
	
	pc415StatusDefinition->fPumpTemperatureVeryLowAlarmLimit  = pxLaserBeamDescriptor->xPumpTemperaturesLimits.fPumpTemperatureVeryLowAlarmLimit; 
	pc415StatusDefinition->fPumpTemperatureVeryHighAlarmLimit =  pxLaserBeamDescriptor->xPumpTemperaturesLimits.fPumpTemperatureVeryHighAlarmLimit;
	
	
	
	
	/*prepare the CAN packet 401 and set the CAN image */
	eMpbCan415Encode( pc415StatusDefinition );
	
	
	
	/* get the 401 CAN image */
	getCan415( &pCan);
	
	/* send it*/
	vCanDispatcherSendCanMessage( &pCan );
	
//	memset( &c415StatusDefinition, 0, sizeof( c415StatusDefinition_t)  );
	
//	eMpbCan415Decode( &c415StatusDefinition );
	
	
}
/*--------------------------------------------------------------------*/
static void testSend40A(void)
{
	CAN_FRAME				pCan;
	c40AStatusDefinition_t *pc40AStatusDefinition;
	c409StatusDefinition_t c409StatusDefinition;
	
	pc40AStatusDefinition = vLaserDataGetCan40AInfo(  );
	
	vLaserDataGetCan409Info( &c409StatusDefinition );
	
	
	/* fill the info */
	
	pc40AStatusDefinition->fBoosterDriver2CurrentLowAlarmLimit = c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump;
	pc40AStatusDefinition->fBoosterDriver2CurrentHighAlarmLimit = c409StatusDefinition.fSetBoosterAlarmHighLimitForCurrentFirstPump;
	pc40AStatusDefinition->fBoosterDriver3CurrentLowAlarmLimit = c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump;
	pc40AStatusDefinition->fBoosterDriver3CurrentLowAlarmLimit = c409StatusDefinition.fSetBoosterAlarmLowLimitForCurrenFirstPump;
	
		
	/*prepare the CAN packet 40a and set the CAN image */
	eMpbCan40AEncode( pc40AStatusDefinition );
	
	
	
	/* get the 40a CAN image */
	getCan40A( &pCan);
	
	/* send it*/
	vCanDispatcherSendCanMessage( &pCan );
	
	//memset( &c40AStatusDefinition, 0, sizeof( c40AStatusDefinition_t)  );
	
	//eMpbCan40ADecode( &c40AStatusDefinition );
	
	
}
/*--------------------------------------------------------------------*/
static void testSend411(void)
{
	CAN_FRAME				pCan;
	c411StatusDefinition_t c411StatusDefinition;
	
	vLaserDataGetCan411Info( &c411StatusDefinition );
	
	
	
	/*prepare the CAN packet 40a and set the CAN image */
	eMpbCan411Encode( &c411StatusDefinition );
	
	
	
	/* get the 411 CAN image */
	getCan411( &pCan);
	
	/* send it*/
	vCanDispatcherSendCanMessage( &pCan );
	
	//memset( &c411StatusDefinition, 0, sizeof( c411StatusDefinition_t)  );
	
//	eMpbCan411Decode( &c411StatusDefinition );
	
	
}

/*--------------------------------------------------------------------*/
static void testSend423(void)
{
	CAN_FRAME				pCan;
	c423StatusDefinition_t c423StatusDefinition;
	
	
	vLaserDataGetCan423Info( &c423StatusDefinition );
	
	
	/*prepare the CAN packet 40a and set the CAN image */
	eMpbCan423Encode( &c423StatusDefinition );
	
	
	
	/* get the 40a CAN image */
	getCan423( &pCan);
	
	/* send it*/
	vCanDispatcherSendCanMessage( &pCan );
	
	//memset( &c40AStatusDefinition, 0, sizeof( c40AStatusDefinition_t)  );
	
	//eMpbCan40ADecode( &c40AStatusDefinition );
	
	
}

/*--------------------------------------------------------------------*/
static void vRunSequenceA(void)
{
	ulCounterSequenceA++;
	
	if( eSequenceA == eSequenceA401 )
	{
		if(ulCounterSequenceA >= DEF_DELAY_SEQUENCE_A)
		{
			testSend401();
			ulCounterSequenceA = 0;
			eSequenceA = eSequenceA402;
		}
	}
	else if( eSequenceA == eSequenceA402 )
	{
		if(ulCounterSequenceA >= DEF_DELAY_SEQUENCE_A)
		{
			testSend402();
			ulCounterSequenceA = 0;
			eSequenceA = eSequenceA414;
		}
	}
	else if( eSequenceA == eSequenceA414 )
	{
		if(ulCounterSequenceA >= DEF_DELAY_SEQUENCE_A)
		{	
			testSend414();		
			ulCounterSequenceA = 0;
			eSequenceA = eSequenceA414a;
	//		ulCounterSequenceB++;
	//		vRunSequenceB();
			
		}
		
	}	
	else if( eSequenceA == eSequenceA414a )
	{
		if(ulCounterSequenceA >= DEF_DELAY_SEQUENCE_A)
		{	
			//testSend414();		
			ulCounterSequenceA = 0;
			eSequenceA = eSequenceA401;
			ulCounterSequenceB++;
			vRunSequenceB();
	
			
		}
		
	}

		
}
/*--------------------------------------------------------------------*/
static void vRunSequenceB(void)
{
	//ulCounterSequenceB++;
	
	if( eSequenceB == eSequenceBInit )
	{
		  if(ulCounterSequenceB >= DEF_DELAY_SEQUENCE_B)
		  {
			  	testSend403();
			  //testSend411();
			  ulCounterSequenceB = 0;
			  eSequenceB = eSequenceB403;
		  }
	  }
  else if( eSequenceB == eSequenceB403 )
	{
		if(ulCounterSequenceB >= DEF_DELAY_SEQUENCE_B)
		{
			testSend404();
		//testSend411();
			ulCounterSequenceB = 0;
			eSequenceB = eSequenceB404;
		}
	}
	else if( eSequenceB == eSequenceB404 )
	{
		if(ulCounterSequenceB >= DEF_DELAY_SEQUENCE_B)
		{
			testSend405();
			//testSend414();
		//	testSend40A();
			//testSend415();
			ulCounterSequenceB = 0;
			eSequenceB = eSequenceB405;						
		}
		
	}	else if( eSequenceB == eSequenceB405 )
	{
		if(ulCounterSequenceB >= DEF_DELAY_SEQUENCE_B)
		{
			testSend40A();
			ulCounterSequenceB = 0;
			eSequenceB = eSequenceB40A;						
		}
		
	}
	else if( eSequenceB == eSequenceB40A )
	{
		if(ulCounterSequenceB >= DEF_DELAY_SEQUENCE_B)
		{
			testSend411();
			ulCounterSequenceB = 0;
			eSequenceB = eSequenceB411;						
		}
		
	}
	else if( eSequenceB == eSequenceB411 )
	{
		if(ulCounterSequenceB >= DEF_DELAY_SEQUENCE_B)
		{
			testSend415();
			ulCounterSequenceB = 0;
			bUnitInDebugMode = eTrue;
			if( bUnitInDebugMode == eTrue)
			{
				eSequenceB = eSequenceB423;						
			}
			else
			{
				eSequenceB = eSequenceBInit;							
			}
			
			
		}
		
	}
	else if( eSequenceB == eSequenceB423 )
	{
		if(ulCounterSequenceB >= DEF_DELAY_SEQUENCE_B)
		{
			testSend423();
			ulCounterSequenceB = 0;
			
			eSequenceB = eSequenceBInit;						
		}
		
	}
}
/*--------------------------------------------------------------------*/
static void vGetLogInfo(void)
{
	uint16_t						usSizeLogPacket = 0;
	CAN_FRAME						pCan;
	mpbFtaLowPowerBitAssignment_t	mpbFtaLowPowerBitAssignment;
	eErrorCodes_t					eErrorCode = eCommandAccepted ;
	xLaserLogEventDescriptor_t		*pxLaserLogEventDescriptor;
	
	pxLaserLogEventDescriptor = eMpbGetLogEvent( index );
	
	typedef union
	{
		mpbFmeaMode_t mpbFmeaMode;
		uint8_t ucFmeaValue;
	}MyfmeaConversionData_t;
	MyfmeaConversionData_t MyfmeaConversionData;
	MyfmeaConversionData.mpbFmeaMode = (pxLaserLogEventDescriptor->mpbFmeaMode);
	
	typedef union
	{
		mpbFtaLowTempBitAssignment_t mpbFtaLowTempBitAssignment;
		uint8_t ucFtaLowTempValue[2];
		uint16_t ucFtaLValue;
	}MyftaLowTempConversionData_t;
	MyftaLowTempConversionData_t MyftaLowTempConversionData;
	MyftaLowTempConversionData.mpbFtaLowTempBitAssignment = (pxLaserLogEventDescriptor->mpbFtaLowTempBitAssignment);
	//MyftaLowTempConversionData.ucFtaLValue = MyftaLowTempConversionData.ucFtaLValue + index * 1.3;
	
		typedef union
	{
		mpbFtaLowPowerBitAssignment_t mpbFtaLowPowerBitAssignment;
		uint8_t ucFtaLowPowerValue[2];
		uint16_t ucFtaLValue;
	}mpbFtaLowPower_t;
	mpbFtaLowPower_t mpbFtaLowPowerConversion ;
	mpbFtaLowPowerConversion.mpbFtaLowPowerBitAssignment = (pxLaserLogEventDescriptor->mpbFtaLowPowerBitAssignment);
	
	typedef union
	{
		uint32_t ulmpbLogEventTime;
		uint8_t ucValue[4];
	}MyConversionShortData_t;
	MyConversionShortData_t MyConversionShortTimeLog;
	MyConversionShortTimeLog.ulmpbLogEventTime = (pxLaserLogEventDescriptor->usmpbLogEventTime) ;
	
	typedef union
	{
		xAlarmRegister_t ullmpbAlarms;
		uint8_t ucAlarmsValue[8];
		uint64_t ullal;
	}MyConversionAlarmsData_t;
	
	MyConversionAlarmsData_t MyConversionAlarmsData;
	MyConversionAlarmsData.ullmpbAlarms = pxLaserLogEventDescriptor->xAlarmRegister;

	

	

	usSizeLogPacket = sizeof(xLaserLogEventDescriptor_t); //size in bytes
	usSizeLogPacket = usSizeLogPacket / 7; //size of CAN packets
	
	for(uint8_t ucI=0; ucI<usSizeLogPacket; ucI++)
	{
			
		//*pxLaserLogEventDescriptor++  	
		/* send it*/
		//vCanDispatcherSendCanMessage( &pCan );
			
	}

}
/*--------------------------------------------------------------------*/
void vCanDispatcherSequence(void)
{
	vTimeBaseManagementGetTick( eCanTest, &ulCanTxSequence );
	if( ulCanTxSequence > DEF_DELAY_2_MS)
	{						
		vRunSequenceA();
	//	vRunSequenceB();
		vTimeBaseManagementResetTick( eCanTest );
	}
		
}
/*--------------------------------------------------------------------*/
void vCanDispatcherSendCanMessage( CAN_FRAME *pCan )
{
	Can tp_can;	
	eBool_t bPort1Selected	=  eFalse;

	bPort1Selected =  bCanPort1IsSelected();
	pCan->extended = false;
	pCan->priority = 10; //0-15 lower is higher priority
	pCan->length = 8;
	
	if( bPort1Selected == eFalse)
	{
		mailbox_set_mode( CAN0, MAILBOX_CAN_TX, CAN_MB_TX_MODE);
		sendFrame(CAN0, pCan);
	}
	else
	{
		mailbox_set_mode( CAN1, MAILBOX_CAN1_TX, CAN_MB_TX_MODE);
		sendFrame(CAN1, pCan);
	}
}
/*------------------------------------------------------------------*/
void vCanDispatcherSendFactoryCanMessage( CAN_FRAME *pCan )
{
	Can tp_can;	
	eBool_t bPort1Selected	=  eFalse;

	bPort1Selected =  bCanPort1IsSelected();
	pCan->extended = false;
	pCan->priority = 10; //0-15 lower is higher priority
	pCan->length = 8;
	
	if( bPort1Selected == eFalse)
	{
		mailbox_set_mode( CAN0, MAILBOX_CAN_FACTORY_TX, CAN_MB_TX_MODE);
		sendFrame(CAN0, pCan);
	}
	else
	{
		mailbox_set_mode( CAN1, MAILBOX_CAN_FACTORY_TX, CAN_MB_TX_MODE);
		sendFrame(CAN1, pCan);
	}
}

/*--------------------------------------------------------------------*/
/*406 ->401*/
void vCanDispatcherMessagesMB0( CAN_FRAME *frame )
{
	eBool_t					bCommandReset = eFalse;
	CAN_FRAME				pCan;
	c401StatusDefinition_t c401Status1Definition;
	c406PacketControlDefinition_t *pc406PacketControlDefinition;

	
	c402StatusDefinition_t  * pc402Status1Definition = NULL; 
	pc402Status1Definition =  pLaserDataGetCan402Pointer();
	

	/*update the CAN image */
	setCan406( frame );
		
	/*update the info present in the data base */
	
	pc406PacketControlDefinition = vLaserDataGetData406();
	eMpbCan406Decode( pc406PacketControlDefinition);	
	//vLaserDataSetCan406Info( pc406PacketControlDefinition );
	
	pc402Status1Definition->xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bRxLnaChannelSelection = pc406PacketControlDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucSetRxChannelOnLna;
	
	pc402Status1Definition->xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bTxBoostChannelSelection = pc406PacketControlDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucSetTxChannelOnBooster;
	//pc402Status1Definition->xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaEnableLaserDriverStatus = pc406PacketControlDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucLnaEnablePumpLaser4;
	//pc402Status1Definition->xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bLnaMode = pc406PacketControlDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucSetLnaControlMode;
	pc402Status1Definition->xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterMode = pc406PacketControlDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucSetBoosterControlMode;
	
	pc402Status1Definition->xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterEnableLaserSingleModeStatus = pc406PacketControlDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucBoosterEnablePumpLaser1;
	pc402Status1Definition->xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterEnableLaserMultiMode1Status = pc406PacketControlDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucBoosterEnablePumpLaser2;
	pc402Status1Definition->xAlarmAndStatusRegister.AlarmsAndStatusRegisterBitAssignment.bBoosterEnableLaserMultiMode2Status = pc406PacketControlDefinition->Status_406_Register.Status_406_RegisterBitAssignment.ucBoosterEnablePumpLaser3;
	
	
	
	
}
/*------------------------------------------------------------------*/
/*407->402*/
void vCanDispatcherMessagesMB1( CAN_FRAME *frame )
{
	CAN_FRAME				pCan;
	c402StatusDefinition_t c402StatusDefinition;
	c407PacketControlDefinition_t *pc407PacketControlDefinition;
	
	/*update the CAN image */
	setCan407( frame );
	
	/*update the info present in the data base */
	pc407PacketControlDefinition = vLaserDataGetData407();
	eMpbCan407Decode( pc407PacketControlDefinition );
	
	if( pc407PacketControlDefinition->bSaveSettingsInNvm == eTrue )
	{
		vSetUpdateMemoryWriteNeeded(eTrue);
	}
	else
	{
		vSetUpdateMemoryWriteNeeded(eFalse);
	}

}
/*------------------------------------------------------------------*/
/* 408 -> 403*/
void vCanDispatcherMessagesMB2( CAN_FRAME *frame )
{
		CAN_FRAME				pCan;
		c403StatusDefinition_t *pc403StatusDefinition = NULL;
		c408StatusDefinition_t  c408StatusDefinition;
		c408StatusDefinition_t *pc408StatusDefinition;
		xAmplifierDescriptor_t* pxAmplifierDescriptor;
			
			
		pxAmplifierDescriptor 	= vGetxAmplifierDescriptor( );
		
		pc403StatusDefinition = vLaserDataGetData403();
		/*update the CAN image */
		setCan408( frame );
		/*update the info present in the data base */
		pc408StatusDefinition = vLaserDataGetData408();
		
		eMpbCan408Decode( pc408StatusDefinition );
		
		
		pc403StatusDefinition->fLnaPowerInputAlarmLowLimit = pc408StatusDefinition->fLnaSetStatusAlarmLowLimitForPowerInput;
		pc403StatusDefinition->fLnaPowerInputAlarmHighLimit = pc408StatusDefinition->fLnaSetStatusAlarmHighLimitForPowerInput;
		
		pc403StatusDefinition->fLnaPowerOutputAlarmLowLimit = pc408StatusDefinition->fLnaSetStatusAlarmLowLimitForPowerOutput;
		pc403StatusDefinition->fLnaPowerOutputAlarmHighLimit = pc408StatusDefinition->fLnaSetStatusAlarmHighLimitForPowerOutput;
		
		
		pc403StatusDefinition->fBoosterPowerInputAlarmLowLimit = pc408StatusDefinition->fBoosterSetStatusAlarmLowLimitForPowerInput;
		pc403StatusDefinition->fBoosterPowerInputAlarmHighLimit = pc408StatusDefinition->fBoosterSetStatusAlarmHighLimitForPowerInput;
		
		pc403StatusDefinition->fBoosterPowerOutputAlarmLowLimit = pc408StatusDefinition->fBoosterSetStatusAlarmLowLimitForPowerOutput;
		pc403StatusDefinition->fBoosterPowerOutputAlarmHighLimit = pc408StatusDefinition->fBoosterSetStatusAlarmHighLimitForPowerOutput;
		
		/*prepare the CAN packet 403 and set the CAN image */
		eMpbCan403Encode( &(pxAmplifierDescriptor->c403StatusDefinition) );
		
		/* get the 403 CAN image */
	//	getCan403( &pCan);
		
		/* send it*/
	//	vCanDispatcherSendCanMessage( &pCan );
	
}
/*------------------------------------------------------------------*/
/*409 -> 404 */
void vCanDispatcherMessagesMB3( CAN_FRAME *frame )
{
	//	CAN_FRAME				pCan;
		c404StatusDefinition_t *pc404StatusDefinition;
		//c409StatusDefinition_t c409StatusDefinition;
		c409StatusDefinition_t *pc409StatusDefinition;
		//xAmplifierDescriptor_t* pxAmplifierDescriptor;
		xAmplifierDescriptor_t* pxAmplifierDescriptor;
		pxAmplifierDescriptor 	= vGetxAmplifierDescriptor( );
		
		/*update the CAN image */
		setCan409( frame );
		
		/*update the info present in the data base */
		pc409StatusDefinition = vLaserDataGetData409();
		eMpbCan409Decode( pc409StatusDefinition );
		pxAmplifierDescriptor->xPumpTemperaturesLimits.fUnitBaseTemperatureLowAlarmLimit = pc409StatusDefinition->fSetTemperatureAlarmLowLimitForUnitBase;
		pxAmplifierDescriptor->xPumpTemperaturesLimits.fUnitBaseTemperatureHighAlarmLimit = pc409StatusDefinition->fSetTemperatureAlarmHighLimitForUnitBase;
		
		pc404StatusDefinition =  vLaserDataGetData404();
		
		pc404StatusDefinition->fLnaLowLimitCurrentAlarm = ( pc409StatusDefinition->fSetLnaAlarmLowLimitForCurrentPump );//)  * X2_401_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE) / 100;
		pc404StatusDefinition->fLnaHighLimitCurrentAlarm = ( pc409StatusDefinition->fSetLnaAlarmHighLimitForCurrentPump );// * X2_401_LASER_PUM4_CURRENT_LNA_LINEAR_APROX_ENCODE) / 100;
		
		pc404StatusDefinition->fBoostLowLimitCurrentAlarm = pc409StatusDefinition->fSetBoosterAlarmLowLimitForCurrenFirstPump;
		pc404StatusDefinition->fBoostHighLimitCurrentAlarm = pc409StatusDefinition->fSetBoosterAlarmHighLimitForCurrentFirstPump;

		/*prepare the CAN packet 404 and set the CAN image */
		eMpbCan404Encode( pc404StatusDefinition);
		
		/* get the 404 CAN image */
		//	getCan404( &pCan);
		
		/* send it*/
		//	vCanDispatcherSendCanMessage( &pCan );
	
	}
/*------------------------------------------------------------------*/
/* 010 */
void vCanDispatcherMessagesMB4( CAN_FRAME *frame )
{
	//SelectPort_010_t SelectPort_010;
	
//	eMpbCan010Decode( &SelectPort_010 );
			
//	vSetCanPort1( SelectPort_010.bPortSelected );
}
/*------------------------------------------------------------------*/
static void vSetterFactory(void)
{
	/*CAN_FRAME				pCan;
	c40AStatusDefinition_t c40AStatusDefinition;
	xPidValues_t *xPidValuesLna;
	floatUnion  fMyValue;
	
	getCan40A( &pCan);
	
	eMpbCan40ADecode( &c40AStatusDefinition );
	
	fMyValue.bytes[0] = c40AStatusDefinition.ucParameter1;
	fMyValue.bytes[1] = c40AStatusDefinition.ucParameter2;
	fMyValue.bytes[2] = c40AStatusDefinition.ucParameter3;
	fMyValue.bytes[3] = c40AStatusDefinition.ucParameter4;
	
	if(c40AStatusDefinition.ucIndexCommand == DEF_FACTORY_INDEX_LNA_PROPORTIONAL )
	{
		setLnaPidProportionalValue( fMyValue.fValue);
	}
	else if(c40AStatusDefinition.ucIndexCommand == DEF_FACTORY_INDEX_LNA_INTEGRAL  )
	{
		setLnaPidIntegralValue( fMyValue.fValue);
	}
	else if(c40AStatusDefinition.ucIndexCommand ==  DEF_FACTORY_INDEX_LNA_DERIVATIVE )
	{
		setLnaPidDerivativeValue( fMyValue.fValue);
	}
	//analog input 0 
	else if(c40AStatusDefinition.ucIndexCommand ==  DEF_COMMAND_40A_ADC12VPWR_CM_CH1_SLOPE )
	{
		
	    setCurrentSlopeScalingValues(fMyValue.fValue,eHandleAdc12VPwrCurrentMonitorCH1 );
	}
	else if(c40AStatusDefinition.ucIndexCommand ==  DEF_COMMAND_40A_ADC12VPWR_CM_CH1_INTERCEPT )
	{
		setCurrentInterceptScalingValues(fMyValue.fValue,eHandleAdc12VPwrCurrentMonitorCH1 );
	}
	// analog input 1 
	else if(c40AStatusDefinition.ucIndexCommand ==  DEF_COMMAND_40A_ADC12VPWR_CM_CH2_SLOPE )
	{
		setCurrentSlopeScalingValues(fMyValue.fValue, eHandleAdc12VPwrCurrentMonitorCH2);
	}
	else if(c40AStatusDefinition.ucIndexCommand ==  DEF_COMMAND_40A_ADC12VPWR_CM_CH2_INTERCEPT )
	{
		setCurrentInterceptScalingValues(fMyValue.fValue,eHandleAdc12VPwrCurrentMonitorCH2 );
	}

	getCan40A( &pCan);
	
	vCanDispatcherSendFactoryCanMessage( &pCan );*/
	
}
/*------------------------------------------------------------------*/
static void vGetterFactory(void)
{
	CAN_FRAME				pCan;
	c40AStatusDefinition_t c40AStatusDefinition;
	xPidValues_t *xPidValuesLna;
	uint8_t ucDataCounter = 0;
	float  fMyValue;
	//float* pfloat;
	//xInternalAnalogInputsCpu_t * xpInternalAnalogInputsCpu;
	
	MyCANData_t MyCANData;
	MyCANData.fValue = 0.0f;
	
	typedef union{
	CanBusStatusRegisterBitAssignment_t xCANData;
	uint16_t usData;	
	}canUnion_t;
	canUnion_t canUnion;
	
	getCan40A( &pCan);
	
	eMpbCan40ADecode( &c40AStatusDefinition );
	
	
	//xPidValuesLna = getLnaPidValues();
	/*if(c40AStatusDefinition.ucIndexCommand == DEF_FACTORY_INDEX_RESET)
	{
		vSendFactory();
	}
	else if(c40AStatusDefinition.ucIndexCommand == DEF_FACTORY_INDEX_LOG)
	{
		vGetLogInfo();
	}*/
/*	if(c40AStatusDefinition.ucIndexCommand == DEF_FACTORY_INDEX_RESET )
	{
		uint8_t resetOrigin = cGetresetCause();
		c40AStatusDefinition.ucIsWriting = resetOrigin;
		eMpbCan40AEncode( &c40AStatusDefinition, 0.0f );
		
	}
	else if(c40AStatusDefinition.ucIndexCommand == DEF_FACTORY_INDEX_LNA_PROPORTIONAL )
	{		
			eMpbCan40AEncode( &c40AStatusDefinition, xPidValuesLna->fPGain );
		
	}else if(c40AStatusDefinition.ucIndexCommand == DEF_FACTORY_INDEX_LNA_INTEGRAL )
	{		
			eMpbCan40AEncode( &c40AStatusDefinition, xPidValuesLna->fIGain );
		
	}else if(c40AStatusDefinition.ucIndexCommand == DEF_FACTORY_INDEX_LNA_DERIVATIVE )
	{
			eMpbCan40AEncode( &c40AStatusDefinition, xPidValuesLna->fDGain );		
	}
	else if(c40AStatusDefinition.ucIndexCommand ==  DEF_COMMAND_40A_ADC12VPWR_CM_CH1_INTERCEPT )
	{
		getCurrentInterceptScalingValues (&fMyValue, eHandleAdc12VPwrCurrentMonitorCH1 );
		eMpbCan40AEncode( &c40AStatusDefinition, fMyValue );
	}
	else if(c40AStatusDefinition.ucIndexCommand == DEF_COMMAND_40A_ADC12VPWR_CM_CH1_SLOPE  )
	{
		getCurrentSlopeScalingValues ( &fMyValue, eHandleAdc12VPwrCurrentMonitorCH1 );
		eMpbCan40AEncode( &c40AStatusDefinition, fMyValue );
	}
	// analog input 1 
	else if(c40AStatusDefinition.ucIndexCommand ==  DEF_COMMAND_40A_ADC12VPWR_CM_CH2_SLOPE )
	{
		getCurrentSlopeScalingValues (&fMyValue, eHandleAdc12VPwrCurrentMonitorCH2 );
		eMpbCan40AEncode( &c40AStatusDefinition, fMyValue );
	}
	else if(c40AStatusDefinition.ucIndexCommand == DEF_COMMAND_40A_ADC12VPWR_CM_CH2_INTERCEPT  )
	{
		getCurrentInterceptScalingValues ( &fMyValue, eHandleAdc12VPwrCurrentMonitorCH2 );
		eMpbCan40AEncode( &c40AStatusDefinition, fMyValue );
	}
	// analog input 2 
	
	// read analog internal channels 
	else if(c40AStatusDefinition.ucIndexCommand == DEF_READ_INTERNAL_ADC  )
	{
		
		ucDataCounter = c40AStatusDefinition.ucIsWriting ;
		
		xpInternalAnalogInputsCpu = vpGetInternalAnalogInputs();
				
		if(ucDataCounter ==0)
		{
			fMyValue = xpInternalAnalogInputsCpu->f12V_PwrCurrentMonitor_Ch1;
			
		}
		else if(ucDataCounter ==1)
		{
			fMyValue = xpInternalAnalogInputsCpu->f12V_PwrCurrentMonitor_Ch2;
		}
		else if(ucDataCounter ==2)
		{
			fMyValue = xpInternalAnalogInputsCpu->f12V_PwrVoltageMonitor_Ch1;
		}
		else if(ucDataCounter ==3)
		{
			fMyValue = xpInternalAnalogInputsCpu->f12V_PwrVoltageMonitor_Ch2;
		}
		else if(ucDataCounter ==4)
		{
			fMyValue = xpInternalAnalogInputsCpu->f7V_PwrVoltageMonitor_Ch1;
		}	
		else if(ucDataCounter == 5)
		{
			fMyValue = xpInternalAnalogInputsCpu->f7V_PwrVoltageMonitor_Ch2;
		}
		else if(ucDataCounter == 6)
		{
			fMyValue = xpInternalAnalogInputsCpu->f3_3V_PwrVoltageMonitor;
		}
		else if(ucDataCounter == 7)
		{
			fMyValue = xpInternalAnalogInputsCpu->f3V_ld_PwrVoltageMonitor;
		}					
		else if(ucDataCounter == 8)
		{
			fMyValue = xpInternalAnalogInputsCpu->fAdcPwrCurrentMonitor;
		}
		else if(ucDataCounter == 9)
		{
			fMyValue = xpInternalAnalogInputsCpu->fCanPwrCurrentMonitor1;
		}
		else if(ucDataCounter == 10)
		{
			fMyValue = xpInternalAnalogInputsCpu->fCanPwrCurrentMonitor2;
		}
		else if(ucDataCounter == 11)
		{
			fMyValue = xpInternalAnalogInputsCpu->fPd_Ref;
		}
		else if(ucDataCounter == 12)
		{
			fMyValue = xpInternalAnalogInputsCpu->fLnaPdInput;
		}								
		
		eMpbCan40AEncode( &c40AStatusDefinition, fMyValue );
	}	
	else if( c40AStatusDefinition.ucIndexCommand == DEF_READ_CAN_STATUS)
	{
		if(c40AStatusDefinition.ucIsWriting == 0 )
		{
			canUnion.xCANData = getCANStatus();
			MyCANData.usValue[0] = canUnion.usData;
			MyCANData.usValue[1] = 0;
			fMyValue = MyCANData.fValue;
			
				
			c40AStatusDefinition.ucParameter3 =  can_get_rx_error_cnt(CAN0);								
			c40AStatusDefinition.ucParameter4 =  can_get_tx_error_cnt(CAN0);
			c40AStatusDefinition.ucParameter5 =  can_get_rx_error_cnt(CAN1);
			c40AStatusDefinition.ucParameter6 =  can_get_tx_error_cnt(CAN1);
								
			eMpbCan40AEncode( &c40AStatusDefinition, fMyValue );
		}
		else
		{
			resetCANStatus();
			vBSPCanInitAndStart();
		}
		
	}
	
	getCan40A( &pCan);
	
	vCanDispatcherSendFactoryCanMessage( &pCan );
	*/
	
	
}
/*------------------------------------------------------------------*/
/* 0x41x */
void vCanDispatcherMessagesMB5( CAN_FRAME *frame )
{
		//CAN_FRAME				pCan;
		eBool_t					bPasswordValide = eFalse;
		
		/*update the CAN image */
		if(frame->id == 0x412)
		{
			c412StatusDefinition_t *pc412StatusDefinition;
			c413StatusDefinition_t *pc413StatusDefinition;
			
			setCan412( frame );
		
			/*update the info present in the data base */
			pc412StatusDefinition = vLaserDataGetData412();
			pc413StatusDefinition = vLaserDataGetData413();
			
			eMpbCan412Decode( pc412StatusDefinition);	
			bPasswordValide = bValidatePassword( pc412StatusDefinition,  pc413StatusDefinition);
			
			
		}
		else if(frame->id == 0x410)
		{
			//CAN_FRAME				pCan;			
			c410StatusDefinition_t *pc410StatusDefinition;
			xAmplifierDescriptor_t *pxAmplifierDescriptor;
			
			pxAmplifierDescriptor 	= vGetxAmplifierDescriptor( );			
			
			/*update the CAN image */
			setCan410( frame );
	
			/*update the info present in the data base */
			pc410StatusDefinition = vLaserDataGetData410();
			eMpbCan410Decode( pc410StatusDefinition );
			
			if( pc410StatusDefinition->usNumberCoefficient == RESET_ALARMS)
			{
				vResetHpaAlarms();
			}
			else
			{
				vUpdateConfigInfo();
			}
			//if(pxAmplifierDescriptor->bPasswordIsCorrect == eTrue)
			//{
				
			//}
			/*if( pc410StatusDefinition->CoeficientOperation == WRITE_COEFFICIENT_TO_RAM )
			{
				kk
			}
			
			else if( pc410StatusDefinition->CoeficientOperation == )
			
			
			WRITE_COEFFICIENT_TO_RAM = 1,
			READ_COEFFICIENT_TO_RAM = 2,
			READ_COEFFICIENT_TO_NVM = 3*/
			
			
			//
			//vUpdateNvm(eTrue);
			
		}
		else if(frame->id == 0x413)
		{
			//CAN_FRAME				pCan;
			c413StatusDefinition_t *pc413StatusDefinition;
			c412StatusDefinition_t *pc412StatusDefinition;
	
			/*update the CAN image */
			setCan413( frame );
			
			/*update the info present in the data base */
			pc413StatusDefinition = vLaserDataGetData413();
			pc412StatusDefinition = vLaserDataGetData412();

			eMpbCan413Decode( pc413StatusDefinition );
			
			bValidatePassword( pc412StatusDefinition,  pc413StatusDefinition);
			
			
		}
		
		
		
/*	CAN_FRAME				pCan;
	c405Definition_t c405Definition;
	xPidValues_t xPidValuesLna;
	//uSerialNumber_t uSerialNumber1 ;
	//uSerialNumber1.usSerialNumber = 15400;
	c40AStatusDefinition_t c40AStatusDefinition;
	
	//update the CAN image 
	setCan40A( frame );
	
	eMpbCan40ADecode( &c40AStatusDefinition );
	
	//check mpb indexes fro 40A 
	
	if( (c40AStatusDefinition.ucIndexCommand == DEF_READ_INTERNAL_ADC) ||
		(c40AStatusDefinition.ucIndexCommand == DEF_READ_CAN_STATUS) ||
	    (c40AStatusDefinition.ucIndexCommand == DEF_FACTORY_INDEX_RESET) )
	{
		vGetterFactory();
	}
	
	if(c40AStatusDefinition.ucIsWriting == DEF_YES )
	{
		vSetterFactory();
	}
	
	
			
	
	

//	vSetSerialNumber( uSerialNumber1);
//	uSerialNumber_t uSerialNumber;

//	vGetSerialNumber( &uSerialNumber);

	uint8_t ucCompanyId = 3;
	vSetCompanyId(ucCompanyId);

	ucCompanyId = 0;

	vGetCompanyId(&ucCompanyId);
	
	c405Definition.ucIdCompany = ucCompanyId;
//	c405Definition.ucSerial1 = uSerialNumber.ucSerialNumber[0];
//	c405Definition.ucSerial2 = uSerialNumber.ucSerialNumber[1];
	eMpbCan405Encode( &c405Definition );

	vSetSendConfig();
	
	getCan405( &pCan);
	vCanDispatcherSendCanMessage( &pCan );*/
	
		
}

/* 0x42x */
void vCanDispatcherMessagesMB6( CAN_FRAME *frame )
{
	//CAN_FRAME				pCan;
	uint8_t					ucIndexForMpbFrameResponse = 0;
	uint8_t					eLnaState ;
	uint8_t					eHpaState ;
	uint8_t					eHpaApcState ;
	uint8_t					eMainLoopState ;
	
	xAmplifierDescriptor_t *pxAmplifierDescriptor;
	pxAmplifierDescriptor 	= vGetxAmplifierDescriptor( );
	
	/*update the CAN image */
	if(frame->id == 0x420)
	{
		ucIndexForMpbFrameResponse = frame->data.byte[0];
		
		vSendMpbFrame(ucIndexForMpbFrameResponse);
		
		
	}else if(frame->id == 0x427)
	{		
		if(frame->data.byte[0] == 0x99)
		{
			eLnaState  = pxAmplifierDescriptor->eLnaState;
			eHpaState  = pxAmplifierDescriptor->eHpaState;
			eMainLoopState = pxAmplifierDescriptor->eMainLoopState;
			eHpaApcState = pxAmplifierDescriptor->eHpaApcState; 
			
			 
			vSendStateData( eHpaState, eLnaState, eMainLoopState, eHpaApcState);
			
		}
		else if(frame->data.byte[0] == 0x98)
		{
			//eLnaState  = pxAmplifierDescriptor->eLnaState;
			//eMainLoopState = pxAmplifierDescriptor->eMainLoopState;
			
			vSendMpbStatusData( &(pxAmplifierDescriptor->c428StatusDefinition) );
					
			
					
		}
		else
		{
			vSendRawData( frame->data.byte[0] );		//index for the raw data	
		}
		
	}
	
	
}


/*------------------------------------------------------------------*/
void vSendFactory(void)
{
	//CAN_FRAME				pCan;
	c40AStatusDefinition_t c40AStatusDefinition;
	xPidValues_t *xPidValuesLna;
	
	/*getCan40A( &pCan);
	
	eMpbCan40ADecode( &c40AStatusDefinition );
	
	xPidValuesLna = getLnaPidValues();
	if(c40AStatusDefinition.ucIndexCommand == DEF_FACTORY_INDEX_RESET )
	{
		uint8_t resetOrigin = cGetresetCause();
		c40AStatusDefinition.ucIsWriting = resetOrigin;
		eMpbCan40AEncode( &c40AStatusDefinition, 0.0f );
		
	}else if(c40AStatusDefinition.ucIndexCommand == DEF_FACTORY_INDEX_LNA_PROPORTIONAL )
	{
		if(c40AStatusDefinition.ucIsWriting == DEF_NO )
		{
			eMpbCan40AEncode( &c40AStatusDefinition, xPidValuesLna->fPGain );
		}
	}else if(c40AStatusDefinition.ucIndexCommand == DEF_FACTORY_INDEX_LNA_INTEGRAL )
	{
		if(c40AStatusDefinition.ucIsWriting == DEF_NO )
		{
			eMpbCan40AEncode( &c40AStatusDefinition, xPidValuesLna->fIGain );
		}
	}else if(c40AStatusDefinition.ucIndexCommand == DEF_FACTORY_INDEX_LNA_DERIVATIVE )
	{
		if(c40AStatusDefinition.ucIsWriting == DEF_NO )
		{
			eMpbCan40AEncode( &c40AStatusDefinition, xPidValuesLna->fDGain );
		}
	}

	
	getCan40A( &pCan);
	
	vCanDispatcherSendFactoryCanMessage( &pCan );*/
	
}
/*------------------------------------------------------------------*/