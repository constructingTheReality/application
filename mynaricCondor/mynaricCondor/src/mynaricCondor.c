#include <stdio.h>
#include <string.h>
#include "sysclk.h"
#include "exceptions.h"
#include "wdt.h"
#include "pmc.h"
#include "ioport.h"
#include "can.h"
#include "pwm.h"
#include "tc.h"
//#include "sn65hvd234.h"
#include "ControlAlarm.h"
#include "CurrentSensors.h"
#include "mpbSamplingTime.h"
#include "accControl.h"
#include "controlLaserPID.h"
#include "temperature.h"
#include "PowerSensors.h"
#include "BSPAdc.h"
#include "BSPCan.h"
#include "BSPPwm.h"
#include "BSPSpi.h"
#include "mainStateMachine.h"
#include "BSPGpio.h"
#include "currentControl.h"
#include "enableControl.h"
#include "conf_board.h"
#include "conf_clock.h"
#include "laserData.h"
#include "TimeBaseManagement.h"
#include "canDictionary.h"
#include "binaryInput.h"
#include "flash_efc.h"
#include "pdc.h"
#include "canDispatcher.h"
#include "mpbLogEvent.h"
#include "nvMemory.h"
#include "usart_spi.h"
#include "mpbLosDetector.h"

#define CAN_MSG_TOGGLE_LED_0        0x11223344
#define CAN_MSG_TOGGLE_LED_1        0xAABBCCDD
#define CAN_MSG_DUMMY_DATA          0x55AAAA55
#define SAMPLING_TIME_FOR_LOOP_CONTROL_IN_MS  10		/* ms */
#define MILISECONDS_FOR_1_SECOND  1000		/* ms */
/** USART PDC transfer type definition. */
#define PDC_TRANSFER        1
/** Timer counter frequency in Hz. */
#define TC_FREQ             1000
/** Watchdog period 3000ms */
#define WDT_PERIOD                        3000
/** Watchdog restart 2000ms */
#define WDT_RESTART_PERIOD                2000
#define EEFC_FKEY 0x5A
//Defines so the device can do a self reset
#define SYSRESETREQ    (1<<2)
#define VECTKEY        (0x05fa0000UL)
#define VECTKEY_MASK   (0x0000ffffUL)
#define AIRCR          (*(uint32_t*)0xe000ed0cUL) // fixed arch-defined address
#define REQUEST_EXTERNAL_RESET (AIRCR=(AIRCR&VECTKEY_MASK)|VECTKEY|SYSRESETREQ)

#define EFC_FCMD_CGPB   0x0C //Clear GPNVM Bit
#define 	EFC_FCMD_SGPB   0x0B //Set GPNVM Bit.
#define 	EFC_FCMD_GGPB   0x0D  //Get GPNVM Bit

#define CHIP_FLASH_IAP_ADDRESS (IROM_ADDR + 8)

/** Receive status */
volatile uint32_t g_ul_recv_status = 0;
static uint32_t ulOscilator = 0;

static uint8_t countForWdgReset = 0;
//static bool bSent401 = false;
//static bool bSent402 = false;
//static uint8_t errorCAN0Rx = 0;
//static uint8_t errorCAN0Tx = 0;
//static uint8_t errorCAN1Rx = 0; 
//static uint8_t errorCAN1Tx = 0; 
static CanSequence_t myCanSequence; 
volatile uint32_t g_ul_ms_ticks = 0;
static uint32_t ulLedHeartbeat, ulFmeaLoggerTimer, ulCanSequence;
static uint32_t ulData;
static uint16_t cmd;

	struct usart_spi_device USART_SPI_DEVICE_EXAMPLE = {
		/* Board specific select ID. */
		.id = USART_SPI_DEVICE_EXAMPLE_ID
	};
	
static void vprvReadCriticalSensors(void);

static void vprvReadCriticalSensors(void)
{
	eBool_t bLnaCurrentAlarm = eFalse ;
	eBool_t bInternalCurrentAlarm = eFalse ;
	eBool_t bHpaCurrentAlarm = eFalse;
	
	eBool_t bLnaPowerCriticalAlarm = eFalse ;
	eBool_t bHpaLnaPowerLosAlarm = eFalse ;
	eBool_t bBoosterPowerCriticalAlarm = eFalse ;
	
	eBool_t bBoosterIsStucked = eFalse ;
		
	eCurrentSensorUpdate(&bHpaCurrentAlarm, &bLnaCurrentAlarm, &bInternalCurrentAlarm);
//	vLaserSetCurrentAlarm( bLnaCurrentAlarm);
	
	if( bLnaCurrentAlarm == eTrue )
	{
//		vSetAlarmCurrentInLna();	
	}
	else
	{
		vClearAlarmCurrentInLna();	
	}
	
	if( bInternalCurrentAlarm == eTrue )
	{		
//		vSetAlarmCriticalError();
	}
				
		
	ePowerSensorUpdate(&bHpaLnaPowerLosAlarm, &bLnaPowerCriticalAlarm, &bBoosterPowerCriticalAlarm);
	
	
	#ifndef DEMO_VERSION
	if( (bBoosterPowerCriticalAlarm == eTrue ) )// || (bBoosterPowerCriticalAlarm == eTrue) )
	{
		vSetAlarmCriticalError();
	}
	#endif
	
	if ( eTrue ==  bMainFsmHpaGetStuckCondition() )
	{
		//vSetAlarmCriticalError();
	}
	
	
}
/**
 * \brief Configure Timer Counter 0 (TC0) to generate an interrupt every 200ms.
 */
static void configure_tc(void)
{
	uint32_t ul_div;
	uint32_t ul_tcclks;
	static uint32_t ul_sysclk;

	/* Get system clock. */
	ul_sysclk = sysclk_get_cpu_hz();

	/* Configure PMC. */
	pmc_enable_periph_clk(ID_TC0);

	/* Configure TC for a 50Hz frequency and trigger on RC compare. */
	tc_find_mck_divisor(TC_FREQ, ul_sysclk, &ul_div, &ul_tcclks, ul_sysclk);
	tc_init(TC0, 0, ul_tcclks | TC_CMR_CPCTRG);
	tc_write_rc(TC0, 0, (ul_sysclk / ul_div) / TC_FREQ);

	/* Configure and enable interrupt on RC compare. */
	NVIC_EnableIRQ((IRQn_Type)ID_TC0);
	tc_enable_interrupt(TC0, 0, TC_IER_CPCS);
}

/**
 * \brief Interrupt handler for TC0. Record the number of bytes received,
 * and then restart a read transfer on the USART if the transfer was stopped.
 */
void TC0_Handler(void)
{
	uint32_t ul_status;
	eMpbError_t eMpbError = eSuccess;
	
	vBSPAdcUpdateChannels();
	eMpbError = eBSPExternalAdcChannels();
	if( eMpbError != eSuccess)
	{
		vIncreaseSpiAdcErrors();
	}


	vTimeBaseManagementTick();
	/* Read TC0 Status. */
	ul_status = tc_get_status(TC0, 0);
}

int main(void)
{
	
	uint32_t wdt_mode, timeout_value;
	hal_status_t hal_status;
	//eMpbError_t eMpbError;
	eBool_t bEnable1 = eFalse;
	
	vTimeBaseManagementInit( );
	
	/* Initialize the SAM system. */
	sysclk_init();
	board_init();
	
	
	//vCurrentSensorsInit();
	vCurrentSensorsInitInternalChannels();
	
	//vCurrentControlInit();
	//vPowerSensorsInit();
	vLaserDataInit();

	vTemperatureInit();
	eMpbLogEventInit();
//	vBinaryOutInit();
	vBSPAdcInitAndStart(); /* internal adc */
//	vBSPDacInitAndStart();

	/* Configure TC. */
	configure_tc();

	/* Enable CAN0 & CAN1 clock. */
	pmc_enable_periph_clk(ID_CAN0);
	pmc_enable_periph_clk(ID_CAN1);
	pmc_enable_periph_clk(ID_PWM);
	
	vBSPPwmInitAndStart();

	NVIC_DisableIRQ(PWM_IRQn);
	NVIC_ClearPendingIRQ(PWM_IRQn);
	
	//ul_sysclk = sysclk_get_cpu_hz();
	
	/* Get timeout value. */
	timeout_value = wdt_get_timeout_value(WDT_PERIOD * 1000,BOARD_FREQ_SLCK_XTAL);
	
			/* Configure WDT to trigger an interrupt (or reset). */
	wdt_mode =	//WDT_MR_WDFIEN |  /* Enable WDT fault interrupt. */
				WDT_MR_WDRPROC   |  /* WDT fault resets processor only. */
				WDT_MR_WDRSTEN;   //|
				WDT_MR_WDDBGHLT  |  /* WDT stops in debug state. */
				WDT_MR_WDIDLEHLT;   /* WDT stops in idle state. */
			
	/* Initialize WDT with the given parameters. */
	//wdt_init(WDT, wdt_mode, timeout_value, timeout_value);
	
			
	if (timeout_value == WDT_INVALID_ARGUMENT) {
		while (1) {
			/* Invalid timeout value, error. */
		}
	}
	
	
		
	vBSPCanInitAndStart();
	vMainStateMachineInit();
	vControlAlarmInitAlarms();
	vBSPSpiMasterInitAndStart();
	//eBSPSpiFRamInit();
	vBinaryOtputSetState( eOutputFramPwrEna, eTrue );
		
		
		

		usart_spi_init(USART_SPI_EXAMPLE);
		usart_spi_setup_device(USART_SPI_EXAMPLE, &USART_SPI_DEVICE_EXAMPLE, SPI_MODE_0, USART_SPI_EXAMPLE_BAUDRATE, 0);
		usart_spi_enable(USART_SPI_EXAMPLE);
		
		usart_spi_deselect_device(USART_SPI_EXAMPLE, &USART_SPI_DEVICE_EXAMPLE);
		usart_spi_select_device(USART_SPI_EXAMPLE, &USART_SPI_DEVICE_EXAMPLE);
		usart_spi_deselect_device(USART_SPI_EXAMPLE, &USART_SPI_DEVICE_EXAMPLE);
	
	uint32_t resetValue = REG_RSTC_SR;
				
	resetValue = resetValue & RSTC_SR_RSTTYP_Msk;
	resetValue = resetValue >> 8;
				
	
	
	/* demo data */
	//xAmplifierDescriptor_t* xAmplifierDescriptor  = vGetLaserBeams( );
	
	
//	Rstc resetValue;
	//xAmplifierDescriptor->cResetCause = resetValue;
	
      	ulOscilator = sysclk_get_cpu_hz() ;
	
	/*vBinaryOtputSetState( eOutputAdcCs0, eTrue );
	vBinaryOtputSetState( eOutputAdcCs1, eTrue );
	vBinaryOtputSetState( eOutputAdcCs2, eTrue );*/

//	vBinaryOtputSetState( eOutputFramCs, eFalse );
	

	vBinaryOtputSetState( eOutputFramPwrEna, eTrue );
	

	vBinaryOtputSetState( eOutputAdcPwrEna, eTrue );
	
	vBinaryOtputSetState( eOutput28vPwrDis1, eFalse );
	vBinaryOtputSetState( eOutput28vPwrDis1, eTrue );
	vBinaryOtputSetState( eOutput28vPwrDis1, eFalse );
	
	vBinaryOtputSetState( eOutput28vPwrDis2, eFalse );
	vBinaryOtputSetState( eOutput28vPwrDis2, eTrue );
	vBinaryOtputSetState( eOutput28vPwrDis2, eFalse );
	
	vBinaryOtputSetState( eOutputCanPwrEna1, eTrue);
	vBinaryOtputSetState( eOutputCanPwrEna2, eTrue);
	
	
	//vBinaryOtputSetState( eOutputAdcPwrEna, eFalse );
	//vBinaryOtputSetState( eOutputAdcCs0, eFalse );
	
	
	vBinaryOtputSetState( eOutputAdcCs0, eTrue );
	vBinaryOtputSetState( eOutputAdcCs1, eTrue );
	vBinaryOtputSetState( eOutputAdcCs2, eTrue );
	
	//vBinaryOtputSetState( eOutputFramCs, eFalse );
	vBinaryOtputSetState( eOutputFramWp, eTrue );
	vBinaryOtputSetState( eOutputFramWp, eFalse );
	vBinaryOtputSetState( eOutputFramWp, eTrue );
	vBinaryOtputSetState( eOutputFramPwrEna, eTrue );
	
	
	vBinaryOtputSetState( eOutput3vPwrEna1, eTrue );
	vBinaryOtputSetState( eOutput3vPwrEna1, eFalse );
			vBinaryOtputSetState( eOutput3vPwrEna1, eTrue );
			
	vBinaryOtputSetState( eOutput3vPwrEna2, eTrue );
	vBinaryOtputSetState( eOutput3vPwrEna2, eFalse );
	vBinaryOtputSetState( eOutput3vPwrEna2, eTrue );
	
	
	
	//vBinaryOtputSetState( eOutputAdcCs1, eFalse );
	
	//vBinaryOtputSetState( eOutputAdcCs2, eFalse );
	
	vControlLinesLaserInit();
	//vInitLosDetection();
	
	
	tc_start(TC0, 0);
	//ioport_set_pin_level(ADC_PWR_ENA_GPIO, false );
//	vLaserBeamsFactoryDefaultValues();

	//read nvm paramters

	if(eTrue == bInitCommonMemoryImageFromNvm() )
	{ 
		vCopyImageCommonNvm();	
	}
	else
	{
		
		//vCommonThermistorFactoryInitChannels();
	}
	
	
						
	if( eTrue == bInitLnaMemoryImageFromNvm() )
	{
		vCopyImageLnaNvm();	
	}
	else
	{
		vCurrentSensorsFactoryInitLnaChannels();
		ePowerSensorsFactoryInitLnaChannels();
		//vLnaThermistorFactoryInitChannels();
		vLnaCurrentControlInit( );		
		vSetLnaPidDefaultValues();
		
		
	}
	
	
						
			if( eTrue == bInitBoostMemoryImageFromNvm() )
	{
		vCopyImageBoosterNvm();  
//		vSetHpaPidNvmValues();
	}
	else
	{
	//	vCurrentSensorsFactoryInitBoosterChannels();
		ePowerSensorsFactoryInitBoosterChannels();
		//vBoosterThermistorFactoryInitChannels();
		vBoosterCurrentControlInit(  );
		vSetHpaPidDefaultValues();
		vCopyImageBoosterNvm();
		//vSetBoosterPidDefaultValues();
	}
	
		vLaserDataInit();		
		vCopyImageCommonNvm();	
		vCopyImageLnaNvm();	
		vCopyImageBoosterNvm();
	
/*	vCommonThermistorFactoryInitChannels();
	vLaserDataInit();	
	vCopyImageCommonNvm();
	
	bInitCommonMemoryImageFromNvm();
	vCopyImageCommonNvm();
	
	
	vUpdateCommonNvmMemory();
						
	bInitCommonMemoryImageFromNvm();*/
						
	
	
	while (1) 
	{

			

				//uint8_t timer;
				//static uint32_t test = 0;
		//		vControlAlarmSetCriticalAlarms();
				
				/* refresh timers */
				vTimeBaseManagementGetTick( eLEDStatusTimeBase, &ulLedHeartbeat );
				if( ulLedHeartbeat > 2 )
				{					
					
					//vControlLinesLaserUpdate();
					//flash_clear_gpnvm(1);
					//if(test == 4) 
					uint32_t addr = 3;
				//	REQUEST_EXTERNAL_RESET;
				//	wdt_restart(WDT);	

					//vBinaryOtputSetState( eOutputAdcPwrEna, eTrue );
					

			//		static uint32_t pulData = 0;
			

					
					
					//#define CMD_TEST     0x10101010
			//		cmd = ADC108S102_CMD(2);
//					vBSPSpiMasterTransfer(&cmd, sizeof(cmd));
//					vBinaryOtputSetState( eOutputAdcCs0, eTrue );
					//ioport_set_pin_level(ADC_PWR_ENA_GPIO, true ); 
					//vBinaryOtputSetState( eOutputAdcCs1, eTrue );
					//vBinaryOtputSetState( eOutputAdcCs2, eTrue );
					
			//		ioport_set_port_level(ADC_CS0_PORT, ADC_CS0_MASK,IOPORT_PIN_LEVEL_LOW);
			//		ioport_toggle_port_level(ADC_CS0_PORT, ADC_CS0_MASK);
			//		eMpbError = eMpbLogEventRun( vGetxAmplifierDescriptor() );
					
					if( bGetSendConfig() == eTrue ) 
					{
						vResetSendConfig();
						vSendFactory();
					}
					vprvReadCriticalSensors();		
							
					
				
					vTimeBaseManagementResetTick( eLEDStatusTimeBase );
				}
				
				vTimeBaseManagementGetTick( eFmeaLoggerTimeBase, &ulFmeaLoggerTimer );
				if( ulFmeaLoggerTimer > 10 )
				{
							
					//ioport_toggle_pin_level(LED0_GPIO);
				//	bEnable1 = (bEnable1 == eFalse)? eTrue: eFalse;
					
				//	vBinaryOtputSetState( eOutputLnaLddEna, bEnable1 );
				//	countForWdgReset++;
					
				//	vUpdateNvmMemory();
					
					vMainStateMachineUpdate( );	
					//vprvDetectdStuckCondition();
					if(countForWdgReset  > 10)
					{
						
					//	REQUEST_EXTERNAL_RESET; just for testing
					
					}
					vTemperatureUpdate();
					
					//eMpbLogEventRun( vGetxAmplifierDescriptor() );
							
					vTimeBaseManagementResetTick( eFmeaLoggerTimeBase );
				}
				
				
				if( true == canErrorDetected() )
				{
					//TODO : toggle pin power CAN driver
 				//	vBSPCanInitAndStart();
				}
					
				vCanDispatcherSequence();	
				
				/* update info from nvm because a reset command */
				
				
				if( eTrue == vGetUpdateMemoryWriteNeeded() ) 
				{
					
					vSetUpdateMemoryWriteNeeded(eFalse);
					vUpdateCommonNvmMemory();
				//	vSetUpdateCommonMemoryWriteNeeded(eFalse);
				//	bInitCommonMemoryImageFromNvm(); //
				//	vCopyImageCommonNvm();
					
					vUpdateLnaNvmMemory();
				//	vSetUpdateLnaMemoryWriteNeeded(eFalse);
				//	bInitLnaMemoryImageFromNvm(); //
				//	vCopyImageLnaNvm();	
					
					vUpdateBoostNvmMemory();
				//	vSetUpdateBoosterMemoryWriteNeeded(eFalse);
				//	bInitBoostMemoryImageFromNvm();    //tests
				//	vCopyImageBoosterNvm();				
					
				}

				if( eTrue == bResetIsDemanded() )
				{
	//				vSetResetState();
				}
			/*	else if( eTrue == vGetUpdateLnaMemoryWriteNeeded() ) 
				{
					vUpdateLnaNvmMemory();
					vSetUpdateLnaMemoryWriteNeeded(eFalse);
					bInitLnaMemoryImageFromNvm();
					vCopyImageLnaNvm();
				} 
				else if( eTrue == vGetUpdateBoosterMemoryWriteNeeded() ) 
				{
					vUpdateBoostNvmMemory();
					vSetUpdateBoosterMemoryWriteNeeded(eFalse);
					bInitBoostMemoryImageFromNvm();
					vCopyImageBoosterNvm();
					
				}*/


		

		//	if ( g_ul_recv_status == 1)
		//	{
				/*errorCAN0Rx =  can_get_rx_error_cnt(CAN0);
				errorCAN1Rx =  can_get_rx_error_cnt(CAN1);
				errorCAN0Tx =  can_get_tx_error_cnt(CAN0);
				errorCAN1Tx =  can_get_tx_error_cnt(CAN1);
				*/
			//	uint32_t velid =  get_rx_buff(&buffer) ;
		//		g_ul_recv_status = 0;
		//	}
			
			
	}
}
