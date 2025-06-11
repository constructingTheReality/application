/**
 * \file
 *
 * \brief  Board Definition.
 *
 */


#ifndef _MYNARIC_BOARD_H_
#define _MYNARIC_BOARD_H_

#include "compiler.h"
#include "system_sam3x.h"
#include "exceptions.h"

#define BOARD_REV_A

/* ------------------------------------------------------------------------ */

/**
 *  \page sam3x_ek_opfreq "SAM3X-EK - Operating frequencies"
 *  This page lists several definition related to the board operating frequency
 *
 *  \section Definitions
 *  - \ref BOARD_FREQ_*
 *  - \ref BOARD_MCK
 */

/*! Board oscillator settings */
#define BOARD_FREQ_SLCK_XTAL            (32768U)
#define BOARD_FREQ_SLCK_BYPASS          (32768U)
#define BOARD_FREQ_MAINCK_XTAL          (8000000U)
#define BOARD_FREQ_MAINCK_BYPASS        (12000000U)

/*! Master clock frequency */
#define BOARD_MCK                       CHIP_FREQ_CPU_MAX

/** board main clock xtal startup time */
#define BOARD_OSC_STARTUP_US   15625


/* ------------------------------------------------------------------------ */

/**
 * \page sam3x_ek_board_info "SAM3X-EK - Board informations"
 * This page lists several definition related to the board description.
 *
 * \section Definitions
 * - \ref BOARD_NAME
 */

/*! Name of the board */
#define BOARD_NAME "MYNARIC_MK3"
/*! Board definition */
//#define sam3xek
/*! Family definition (already defined) */
#define sam3x
/*! Core definition */
#define cortexm3

/* ------------------------------------------------------------------------ */

/**
 * \page sam3x_ek_piodef "SAM3X-EK - PIO definitions"
 * This pages lists all the pio definitions. The constants
 * are named using the following convention: PIN_* for a constant which defines
 * a single Pin instance (but may include several PIOs sharing the same
 * controller), and PINS_* for a list of Pin instances.
 *
 */

/**
 * \file
 * ADC
 */

/*! ADC pin definition. */
#define PINS_ADC_TRIG  PIO_PA16_IDX
#define PINS_ADC_TRIG_FLAG  (PIO_PERIPH_B | PIO_DEFAULT)

#define PINS_ADC_TRIG1  PIO_PA24_IDX
#define PINS_ADC_TRIG_FLAG  (PIO_PERIPH_B | PIO_DEFAULT)
/**
 * \file
 * EBI
 * - \ref PIN_EBI_DATA_BUS
 * - \ref PIN_EBI_NRD
 * - \ref PIN_EBI_NWE
 * - \ref PIN_EBI_NCS0
 * - \ref PIN_EBI_PSRAM_ADDR_BUS
 * - \ref PIN_EBI_PSRAM_NBS
 * - \ref PIN_EBI_A1
 * - \ref PIN_EBI_NCS1
 * - \ref PIN_EBI_LCD_RS
 *
 */

/* ------------------------------------------------------------------------ */
/* EBI */
/* ------------------------------------------------------------------------ */
/*! EBI Data Bus pins */
/*#define PIN_EBI_DATA_BUS_D0       PIO_PC2_IDX
#define PIN_EBI_DATA_BUS_D1       PIO_PC3_IDX
#define PIN_EBI_DATA_BUS_D2       PIO_PC4_IDX
#define PIN_EBI_DATA_BUS_D3       PIO_PC5_IDX
#define PIN_EBI_DATA_BUS_D4       PIO_PC6_IDX
#define PIN_EBI_DATA_BUS_D5       PIO_PC7_IDX
#define PIN_EBI_DATA_BUS_D6       PIO_PC8_IDX
#define PIN_EBI_DATA_BUS_D7       PIO_PC9_IDX
#define PIN_EBI_DATA_BUS_D8       PIO_PC10_IDX
#define PIN_EBI_DATA_BUS_D9       PIO_PC11_IDX
#define PIN_EBI_DATA_BUS_D10      PIO_PC12_IDX
#define PIN_EBI_DATA_BUS_D11      PIO_PC13_IDX
#define PIN_EBI_DATA_BUS_D12      PIO_PC14_IDX
#define PIN_EBI_DATA_BUS_D13      PIO_PC15_IDX
#define PIN_EBI_DATA_BUS_D14      PIO_PC16_IDX
#define PIN_EBI_DATA_BUS_D15      PIO_PC17_IDX
#define PIN_EBI_DATA_BUS_FLAGS    (PIO_PERIPH_A | PIO_PULLUP)*/

/**
 * \file
 * LEDs
 * - \ref PIN_USER_LED1 
 * - \ref PIN_USER_LED2
 * - \ref PIN_USER_LED3
 * - \ref PIN_POWER_LED
 *
 */

/* ------------------------------------------------------------------------ */
/* LEDS                                                                     */
/* ------------------------------------------------------------------------ */
/*! LED #0 pin definition (BLUE). 
#define LED_0_NAME      "blue LED D2"
#define LED0_GPIO       (PIO_PA12_IDX)
#define LED0_FLAGS      (PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT)
#define LED0_ACTIVE_LEVEL 0

#define PIN_LED_0       {PIO_PA12, PIOA, ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}
#define PIN_LED_0_MASK  PIO_PA12
#define PIN_LED_0_PIO   PIOA
#define PIN_LED_0_ID    ID_PIOA
#define PIN_LED_0_TYPE  PIO_OUTPUT_1
#define PIN_LED_0_ATTR  PIO_DEFAULT

#define LED0_INACTIVE_LEVEL  IOPORT_PIN_LEVEL_HIGH*/

/*! LED #0 "L" pin definition (ORANGE).*/
/*! Power LED pin definition (ORANGE). L */
//#define PIN_POWER_LED   {PIO_PB27, PIOB, ID_PIOB, PIO_OUTPUT_1, PIO_DEFAULT}
/*! LED #1 pin definition */
//#define PIN_USER_LED1   {PIO_PC21, PIOC, ID_PIOC, PIO_OUTPUT_1, PIO_DEFAULT}
/*! LED #2 pin definition */
//#define PIN_USER_LED2   {PIO_PC22, PIOC, ID_PIOC, PIO_OUTPUT_1, PIO_DEFAULT}
/*! LED #3 pin definition */
//#define PIN_USER_LED3   {PIO_PC23, PIOC, ID_PIOC, PIO_OUTPUT_1, PIO_DEFAULT}

/*! List of all LEDs definitions. */
//#define PINS_LEDS   PIN_USER_LED1, PIN_USER_LED2, PIN_USER_LED3, PIN_POWER_LED
/*
#define LED_0_NAME      "Orange_LED"
#define LED0_GPIO       (PIO_PB27_IDX)
#define LED0_FLAGS      (PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT)
#define LED0_ACTIVE_LEVEL 0*/

/*#define PIN_LED_0       {1 << 27, PIOB, ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT}
#define PIN_LED_0_MASK  (1 << 27)
#define PIN_LED_0_PIO   PIOB
#define PIN_LED_0_ID    ID_PIOB
#define PIN_LED_0_TYPE  PIO_OUTPUT_0
#define PIN_LED_0_ATTR  PIO_DEFAULT*/

/*---*/
#define LNA_LDD_ENA_GPIO		( PIO_PC12_IDX )
#define LNA_LDD_ENA_FLAGS		( PIO_TYPE_PIO_OUTPUT_0 | PIO_DEFAULT  )
#define LNA_LDD_ENA_PORT		PIOC

#define HPA_SM_LDD_ENA_GPIO		( PIO_PC13_IDX )
#define HPA_SM_LDD_ENA_FLAGS	( PIO_TYPE_PIO_OUTPUT_0 | PIO_DEFAULT  )
#define HPA_SM_LDD_ENA_PORT		PIOC

/*#define HPA_SM_LDD_ENA2_GPIO	( PIO_PC14_IDX )
#define HPA_SM_LDD_ENA2_FLAGS	( PIO_TYPE_PIO_OUTPUT_0 | PIO_DEFAULT  )
#define HPA_SM_LDD_ENA2_PORT		PIOC*/

#define HPA_MM_LDD_ENA1_GPIO	( PIO_PC15_IDX )
#define HPA_MM_LDD_ENA1_FLAGS	( PIO_TYPE_PIO_OUTPUT_0 | PIO_PULLUP  )
#define HPA_MM_LDD_ENA1_PORT		PIOC

#define HPA_MM_LDD_ENA2_GPIO	( PIO_PC16_IDX )
#define HPA_MM_LDD_ENA2_FLAGS	( PIO_TYPE_PIO_OUTPUT_0 | PIO_PULLUP  )
#define HPA_MM_LDD_ENA2_PORT		PIOC


#define FRAM_PWR_ENA_GPIO		( PIO_PC17_IDX ) 
#define FRAM_PWR_ENA_FLAGS		( PIO_TYPE_PIO_OUTPUT_0 | PIO_DEFAULT  )  //( PIO_TYPE_PIO_OUTPUT_0 | PIO_PULLUP  )
#define FRAM_PWR_ENA_PORT		PIOC



#define OUT_28V_PWR_DIS1_GPIO		( PIO_PC26_IDX )
#define OUT_28V_PWR_DIS1_FLAGS		( PIO_TYPE_PIO_OUTPUT_0 | PIO_PULLUP  )
#define OUT_28V_PWR_DIS1_PORT		PIOC






#define OUT_28V_PWR_DIS2_GPIO		( PIO_PC27_IDX )
#define OUT_28V_PWR_DIS2_FLAGS		( PIO_TYPE_PIO_OUTPUT_0 | PIO_PULLUP  )
#define OUT_28V_PWR_DIS2_PORT		PIOC


#define OUT_3V_PWR_ENA1_GPIO		( PIO_PC24_IDX )
#define OUT_3V_PWR_ENA1_FLAGS		( PIO_TYPE_PIO_OUTPUT_0 | PIO_PULLUP  )
#define OUT_3V_PWR_ENA1_PORT		PIOC

#define OUT_3V_PWR_ENA2_GPIO		( PIO_PC25_IDX )
#define OUT_3V_PWR_ENA2_FLAGS		( PIO_TYPE_PIO_OUTPUT_0 | PIO_PULLUP  )
#define OUT_3V_PWR_ENA2_PORT		PIOC

#define ADC_PWR_ENA_GPIO		( PIO_PC28_IDX ) //( PIO_PC9_IDX ) //
#define ADC_PWR_ENA_FLAGS		( PIO_TYPE_PIO_OUTPUT_0 | PIO_DEFAULT  )
#define ADC_PWR_ENA_PORT		PIOC



#define CAN_PWR_ENA1_GPIO		( PIO_PC29_IDX )
#define CAN_PWR_ENA1_FLAGS		( PIO_TYPE_PIO_OUTPUT_0 | PIO_PULLUP  )
#define CAN_PWR_ENA1_PORT		PIOC

#define CAN_PWR_ENA2_GPIO		( PIO_PC30_IDX )
#define CAN_PWR_ENA2_FLAGS		( PIO_TYPE_PIO_OUTPUT_0 | PIO_PULLUP  )
#define CAN_PWR_ENA2_PORT		PIOC



//#define ADC_CS0_PORT (IOPORT_PIOA)
//#define ADC_CS0_MASK (PIO_PA27 )// | PIO_PB12)

//#define ADC_CS1_PORT (IOPORT_PIOA)
//#define ADC_CS1_MASK (PIO_PA28 )// | PIO_PB12)
//#define ADC_CS2_PORT (IOPORT_PIOA)
//#define ADC_CS2_MASK (PIO_PA29 )// | PIO_PB12)

/*
#define FRAM_CS_GPIO       (PIO_PB25_IDX)  //(PIO_PA29_IDX)
#define FRAM_CS_FLAGS	   (PIO_TYPE_PIO_OUTPUT_0 | PIO_DEFAULT)
#define FRAM_CS_PORT		PIOB*/


#define FRAM_WP_GPIO       (PIO_PA12_IDX)  
#define FRAM_WP_FLAGS	   (PIO_TYPE_PIO_OUTPUT_0 | PIO_PULLUP)
#define FRAM_WP_PORT		PIOA


#define ADC_CS0_GPIO      (PIO_PA28_IDX)
#define ADC_CS0_FLAGS      (PIO_TYPE_PIO_OUTPUT_0 | PIO_PULLUP)
#define ADC_CS0_PORT		PIOA


#define ADC_CS1_GPIO       (PIO_PA29_IDX)
#define ADC_CS1_FLAGS	   (PIO_TYPE_PIO_OUTPUT_0 | PIO_PULLUP)
#define ADC_CS1_PORT		PIOA

#define ADC_CS2_GPIO       (PIO_PB23_IDX)
#define ADC_CS2_FLAGS	  (PIO_TYPE_PIO_OUTPUT_0 | PIO_PULLUP)
#define ADC_CS2_PORT		PIOB


#define ADC_VOLT_GPIO       (PIO_PC28_IDX) //(PIO_PB23_IDX)
#define ADC_VOLT_FLAGS		(PIO_TYPE_PIO_OUTPUT_0 | PIO_DEFAULT)
#define ADC_VOLT_PORT		PIOC

// LED #2 pin detection 
/*#define LED2_GPIO       (PIO_PC22_IDX)
#define LED2_FLAGS      (PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT)
#define LED2_ACTIVE_LEVEL 0

#define PIN_LED_2       {1 << 22, PIOC, ID_PIOC, PIO_OUTPUT_1, PIO_DEFAULT}
#define PIN_LED_2_MASK  (1 << 22)
#define PIN_LED_2_PIO   PIOC
#define PIN_LED_2_ID    ID_PIOC
#define PIN_LED_2_TYPE  PIO_OUTPUT_1
#define PIN_LED_2_ATTR  PIO_DEFAULT*/

// LED #3 pin detection 
/*#define LED3_GPIO       (PIO_PC23_IDX)
#define LED3_FLAGS      (PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT)
#define LED3_ACTIVE_LEVEL 1

#define BOARD_NUM_OF_LED 4
#define PIN_LED_3       {1 << 23, PIOC, ID_PIOC, PIO_OUTPUT_1, PIO_DEFAULT}
#define PIN_LED_3_MASK  (1 << 23)
#define PIN_LED_3_PIO   PIOC
#define PIN_LED_3_ID    ID_PIOC
#define PIN_LED_3_TYPE  PIO_OUTPUT_1
#define PIN_LED_3_ATTR  PIO_DEFAULT*/

//! LED #1 pin definition (GREEN). 
/*#define LED_1_NAME      "green LED D4"
#define LED1_GPIO       (PIO_PB13_IDX)
#define LED1_FLAGS      (PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT)
#define LED1_ACTIVE_LEVEL 0

#define PIN_LED_1       {PIO_PB13, PIOB, ID_PIOB, PIO_OUTPUT_1, PIO_DEFAULT}
#define PIN_LED_1_MASK  PIO_PB13
#define PIN_LED_1_PIO   PIOB
#define PIN_LED_1_ID    ID_PIOB
#define PIN_LED_1_TYPE  PIO_OUTPUT_1
#define PIN_LED_1_ATTR  PIO_DEFAULT*/

/*#define LED1_INACTIVE_LEVEL  IOPORT_PIN_LEVEL_HIGH

//! LED #2 pin detection (AMBER). 
#define LED2_GPIO       (PIO_PB12_IDX)
#define LED2_FLAGS      (PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT)
#define LED2_ACTIVE_LEVEL 0

#define PIN_LED_2_MASK   PIO_PB12
#define PIN_LED_2_PIO    PIOB
#define PIN_LED_2_ID     ID_PIOB
#define PIN_LED_2_TYPE   PIO_OUTPUT_1
#define PIN_LED_2_ATTR   PIO_DEFAULT

#define LED2_INACTIVE_LEVEL  IOPORT_PIN_LEVEL_HIGH

//! LED #3 pin detection (power) 
#define LED3_GPIO       (PIO_PA13_IDX)
#define LED3_FLAGS      (PIO_TYPE_PIO_OUTPUT_0 | PIO_DEFAULT)
#define LED3_ACTIVE_LEVEL 1

#define PIN_LED_3_MASK   PIO_PA13
#define PIN_LED_3_PIO    PIOA
#define PIN_LED_3_ID     ID_PIOA
#define PIN_LED_3_TYPE   PIO_OUTPUT_1
#define PIN_LED_3_ATTR   PIO_DEFAULT

#define LED3_INACTIVE_LEVEL  IOPORT_PIN_LEVEL_HIGH

//#define BOARD_NUM_OF_LED 4*/

/* ------------------------------------------------------------------------ */
/* PUSHBUTTONS                                                              */
/* ------------------------------------------------------------------------ */
/** Push button #0 definition.
 *  Attributes = pull-up + debounce + interrupt on rising edge. */
/*#define PUSHBUTTON_1_NAME    "LEFT CLICK"
#define GPIO_PUSH_BUTTON_1           (PIO_PE7_IDX)
#define GPIO_PUSH_BUTTON_1_FLAGS\
	(PIO_INPUT | PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE)

#define PIN_PUSHBUTTON_1    {PIO_PE7, PIOE, ID_PIOE, PIO_INPUT,\
	PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_FALL_EDGE}
#define PIN_PUSHBUTTON_1_MASK PIO_PE7
#define PIN_PUSHBUTTON_1_PIO PIOE
#define PIN_PUSHBUTTON_1_ID ID_PIOE
#define PIN_PUSHBUTTON_1_TYPE PIO_INPUT
#define PIN_PUSHBUTTON_1_ATTR (PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE)*/

/** Push button #1 definition.
 *  Attributes = pull-up + debounce + interrupt on falling edge. */
/*#define PUSHBUTTON_2_NAME    "RIGHT CLICK"
#define GPIO_PUSH_BUTTON_2           (PIO_PB23_IDX)
#define GPIO_PUSH_BUTTON_2_FLAGS\
	(PIO_INPUT | PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_FALL_EDGE)

#define PIN_PUSHBUTTON_2    {PIO_PB23, PIOB, ID_PIOB, PIO_INPUT,\
	PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_FALL_EDGE}
#define PIN_PUSHBUTTON_2_MASK PIO_PB23
#define PIN_PUSHBUTTON_2_PIO PIOB
#define PIN_PUSHBUTTON_2_ID ID_PIOB
#define PIN_PUSHBUTTON_2_TYPE PIO_INPUT
#define PIN_PUSHBUTTON_2_ATTR (PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_FALL_EDGE)*/

#define PIN_TC0_TIOA0           (PIO_PB16_IDX)
#define PIN_TC0_TIOA0_MUX       (IOPORT_MODE_MUX_B)
#define PIN_TC0_TIOA0_FLAGS     (PIO_PERIPH_B | PIO_DEFAULT)

#define PIN_TC0_TIOA1           (PIO_PB24_IDX)
#define PIN_TC0_TIOA1_MUX       (IOPORT_MODE_MUX_B)
#define PIN_TC0_TIOA1_FLAGS     (PIO_PERIPH_B | PIO_DEFAULT)


//#define PIN_TC0_TIOA1           (PIO_PA2_IDX)
//#define PIN_TC0_TIOA1_MUX       (IOPORT_MODE_MUX_A)
//#define PIN_TC0_TIOA1_FLAGS     (PIO_PERIPH_A | PIO_DEFAULT)

#define PIN_TC0_TIOA1_PIO     PIOA
#define PIN_TC0_TIOA1_MASK    PIO_PA2
#define PIN_TC0_TIOA1_ID      ID_PIOA
#define PIN_TC0_TIOA1_TYPE    PIO_PERIPH_A
#define PIN_TC0_TIOA1_ATTR    PIO_DEFAULT

#define PIN_TC0_TIOA2         (PIO_PA5_IDX)
#define PIN_TC0_TIOA2_MUX     (IOPORT_MODE_MUX_A)
#define PIN_TC0_TIOA2_FLAGS   (PIO_INPUT | PIO_DEFAULT)

#define PIN_TC0_TIOA2_PIO     PIOA
#define PIN_TC0_TIOA2_MASK    PIO_PA5
#define PIN_TC0_TIOA2_ID      ID_PIOA
#define PIN_TC0_TIOA2_TYPE    PIO_INPUT
#define PIN_TC0_TIOA2_ATTR    PIO_DEFAULT

/**
 * \file
 * PWMC
 * - \ref PIN_PWMC_PWMH0
 * - \ref PIN_PWMC_PWML0
 * - \ref PIN_PWMC_PWMH1
 * - \ref PIN_PWMC_PWML1
 * - \ref PIN_PWMC_PWMH2
 * - \ref PIN_PWMC_PWML2
 * - \ref PIN_PWMC_PWMH3
 * - \ref PIN_PWMC_PWML3
 * - \ref PIN_PWM_LED0
 * - \ref PIN_PWM_LED1
 * - \ref PIN_PWM_LED2
 *
 */

/* ------------------------------------------------------------------------ */
/* PWM                                                                      */
/* ------------------------------------------------------------------------ */			
	#define PIN_PWMC_PWML0\
	{PIO_PC2B_PWML0, PIOC, ID_PIOC, PIO_PERIPH_C, PIO_DEFAULT}						

	#define PIN_PWMC_PWML1\
	{PIO_PC4B_PWML1, PIOC, ID_PIOC, PIO_PERIPH_C, PIO_DEFAULT}

	#define PIN_PWMC_PWML2\
	{PIO_PC6B_PWML2, PIOC, ID_PIOC, PIO_PERIPH_C, PIO_DEFAULT}			
			
	#define PIN_PWMC_PWML3\
	{PIO_PC8B_PWML3, PIOC, ID_PIOC, PIO_PERIPH_C, PIO_DEFAULT}		
			
	#define PIN_PWMC_PWML4\
	{PIO_PC21B_PWML4, PIOC, ID_PIOC, PIO_PERIPH_C, PIO_DEFAULT}		
			
	#define PIN_PWMC_PWML5\
	{PIO_PC22B_PWML5, PIOC, ID_PIOC, PIO_PERIPH_C, PIO_DEFAULT}					

	#define PIN_PWMC_PWMH5\
	{PIO_PC19B_PWMH5, PIOC, ID_PIOC, PIO_PERIPH_C, PIO_DEFAULT}
									


#define LNA_PWM_STP			PIN_PWMC_PWML0
#define HPA_SM_PWM_STP1		PIN_PWMC_PWML1
#define HPA_SM_PWM_STP2		PIN_PWMC_PWML2
#define HPA_MM_PWM_STP1		PIN_PWMC_PWML3
#define HPA_MM_PWM_STP2		PIN_PWMC_PWML4
#define HPA_MM_CLK1			PIN_PWMC_PWMH5
#define HPA_MM_CLK2			PIN_PWMC_PWML5
/*! PWM "PWM7" CONTROL0 pin definitions.*/
#define PIN_PWM_LNA_PWM_STP_GPIO		PIO_PC2_IDX
#define PIN_PWM_LNA_PWM_STP_FLAGS		(PIO_PERIPH_B | PIO_DEFAULT)
#define PIN_PWM_LNA_PWM_STP_CHANNEL		PWM_CHANNEL_0

#define PIN_PWM_HPA_SM_PWM_STP1_GPIO		PIO_PC4_IDX
#define PIN_PWM_HPA_SM_PWM_STP1_FLAGS		(PIO_PERIPH_B | PIO_DEFAULT)
#define PIN_PWM_HPA_SM_PWM_STP1_CHANNEL		PWM_CHANNEL_1


#define PIN_PWM_HPA_SM_PWM_STP2_GPIO		PIO_PC6_IDX
#define PIN_PWM_HPA_SM_PWM_STP2_FLAGS		(PIO_PERIPH_B | PIO_DEFAULT)
#define PIN_PWM_HPA_SM_PWM_STP2_CHANNEL		PWM_CHANNEL_2

#define PIN_PWM_HPA_MM_PWM_STP1_GPIO		PIO_PC8_IDX
#define PIN_PWM_HPA_MM_PWM_STP1_FLAGS		(PIO_PERIPH_B | PIO_DEFAULT)
#define PIN_PWM_HPA_MM_PWM_STP1_CHANNEL		PWM_CHANNEL_3

#define PIN_PWM_HPA_MM_PWM_STP2_GPIO		PIO_PC21_IDX
#define PIN_PWM_HPA_MM_PWM_STP2_FLAGS		(PIO_PERIPH_B | PIO_DEFAULT)
#define PIN_PWM_HPA_MM_PWM_STP2_CHANNEL		PWM_CHANNEL_4

#define PIN_PWM_HPA_MM_CLK1_GPIO		PIO_PC19_IDX
#define PIN_PWM_HPA_MM_CLK1_FLAGS		(PIO_PERIPH_B | PIO_DEFAULT)
#define PIN_PWM_HPA_MM_CLK1_CHANNEL		PWM_CHANNEL_5

#define PIN_PWM_HPA_MM_CLK2_GPIO		PIO_PC22_IDX
#define PIN_PWM_HPA_MM_CLK2_FLAGS		(PIO_PERIPH_B | PIO_DEFAULT)
#define PIN_PWM_HPA_MM_CLK2_CHANNEL		PWM_CHANNEL_5

/**
 * \file
 * SPI
 *
 */

/* ------------------------------------------------------------------------ */
/* SPI                                                                      */
/* ------------------------------------------------------------------------ */
/*! SPI0 MISO pin definition. */
#define SPI0_MISO_GPIO        (PIO_PA25_IDX)
#define SPI0_MISO_FLAGS       (PIO_PERIPH_A | PIO_DEFAULT)
/*! SPI0 MOSI pin definition. */
#define SPI0_MOSI_GPIO        (PIO_PA26_IDX)
#define SPI0_MOSI_FLAGS       (PIO_PERIPH_A | PIO_DEFAULT)
/*! SPI0 SPCK pin definition. */
#define SPI0_SPCK_GPIO        (PIO_PA27_IDX)
#define SPI0_SPCK_FLAGS       (PIO_PERIPH_A | PIO_DEFAULT)

/*! SPI0 chip select 0 pin definition. (Only one configuration is possible) */
//#define SPI0_NPCS0_GPIO            (PIO_PB26_IDX)
//#define SPI0_NPCS0_FLAGS           (PIO_PERIPH_B | PIO_DEFAULT)
#define SPI0_NPCS0_GPIO            (PIO_PA28_IDX)
#define SPI0_NPCS0_FLAGS           (PIO_PERIPH_A | PIO_DEFAULT)

/*! SPI0 chip select 1 pin definition. (multiple configurations are possible) */

#define SPI0_NPCS1_GPIO       (PIO_PA29_IDX)
#define SPI0_NPCS1_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
//#define SPI0_NPCS1_PB20_GPIO       (PIO_PB20_IDX)
//#define SPI0_NPCS1_PB20_FLAGS      (PIO_PERIPH_B | PIO_DEFAULT)
/*! SPI0 chip select 2 pin definition. (multiple configurations are possible) */
//#define SPI0_NPCS2_PA30_GPIO       (PIO_PA30_IDX)
//#define SPI0_NPCS2_PA30_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
//#define SPI0_NPCS2_PB21_GPIO       (PIO_PB21_IDX)
//#define SPI0_NPCS2_PB21_FLAGS      (PIO_PERIPH_B | PIO_DEFAULT)
/*! SPI0 chip select 3 pin definition. (multiple configurations are possible) */
//#define SPI0_NPCS3_PA31_GPIO       (PIO_PA31_IDX)
//#define SPI0_NPCS3_PA31_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
#define SPI0_NPCS3_PB23_GPIO       (PIO_PB23_IDX)
#define SPI0_NPCS3_PB23_FLAGS      (PIO_PERIPH_B | PIO_DEFAULT)


#define USART_SPI_EXAMPLE                   USART0
#define USART_SPI_DEVICE_EXAMPLE_ID         1
#define USART_SPI_EXAMPLE_BAUDRATE          500000




/*! SPI1 MISO pin definition. */
//#define SPI1_MISO_GPIO             (PIO_PE28_IDX)
//#define SPI1_MISO_FLAGS            (PIO_PERIPH_A | PIO_DEFAULT)
/*! SPI1 MOSI pin definition. */
//#define SPI1_MOSI_GPIO             (PIO_PE29_IDX)
//#define SPI1_MOSI_FLAGS            (PIO_PERIPH_A | PIO_DEFAULT)
/*! SPI1 SPCK pin definition. */
//#define SPI1_SPCK_GPIO             (PIO_PE30_IDX)
//#define SPI1_SPCK_FLAGS            (PIO_PERIPH_A | PIO_DEFAULT)
/*! SPI1 chip select 0 pin definition. (Only one configuration is possible) */
//#define SPI1_NPCS0_GPIO            (PIO_PE31_IDX)
//#define SPI1_NPCS0_FLAGS           (PIO_PERIPH_A | PIO_DEFAULT)
/*! SPI1 chip select 1 pin definition. (Only one configuration is possible) */
//#define SPI1_NPCS1_GPIO            (PIO_PF0_IDX)
//#define SPI1_NPCS1_FLAGS           (PIO_PERIPH_A | PIO_DEFAULT)
/*! SPI1 chip select 2 pin definition. (Only one configuration is possible) */
//#define SPI1_NPCS2_GPIO            (PIO_PF1_IDX)
//#define SPI1_NPCS2_FLAGS           (PIO_PERIPH_A | PIO_DEFAULT)
/*! SPI1 chip select 3 pin definition. (Only one configuration is possible) */
//#define SPI1_NPCS3_GPIO            (PIO_PF2_IDX)
//#define SPI1_NPCS3_FLAGS           (PIO_PERIPH_A | PIO_DEFAULT)

/**
 * \file
 * SSC
 * - \ref PIN_SSC_TD
 * - \ref PIN_SSC_TK
 * - \ref PIN_SSC_TF
 * - \ref PIN_SSC_RD
 * - \ref PIN_SSC_RK
 * - \ref PIN_SSC_RF
 *
 */

/* ------------------------------------------------------------------------ */
/* SSC                                                                      */
/* ------------------------------------------------------------------------ */
/** SSC pin Transmitter Data (TD) */
//#define PIN_SSC_TD        (PIO_PA16_IDX)
//#define PIN_SSC_TD_FLAGS  (PIO_PERIPH_B | PIO_DEFAULT)
/** SSC pin Transmitter Clock (TK) */
//#define PIN_SSC_TK        (PIO_PA14_IDX)
//#define PIN_SSC_TK_FLAGS  (PIO_PERIPH_B | PIO_DEFAULT)
/** SSC pin Transmitter FrameSync (TF) */
//#define PIN_SSC_TF        (PIO_PA15_IDX)
//#define PIN_SSC_TF_FLAGS  (PIO_PERIPH_B | PIO_DEFAULT)
/** SSC pin Receiver Data (RD) */
//#define PIN_SSC_RD        (PIO_PB18_IDX)
//#define PIN_SSC_RD_FLAGS  (PIO_PERIPH_A | PIO_DEFAULT)
/** SSC pin Receiver Clock (RK) */
//#define PIN_SSC_RK        (PIO_PB19_IDX)
//#define PIN_SSC_RK_FLAGS  (PIO_PERIPH_A | PIO_DEFAULT)
/** SSC pin Receiver FrameSync (RF) */
//#define PIN_SSC_RF        (PIO_PB17_IDX)
//#define PIN_SSC_RF_FLAGS  (PIO_PERIPH_A | PIO_DEFAULT)

/**
 * \file
 * PCK0
 * - \ref PIN_PCK0
 *
 */

/* ------------------------------------------------------------------------ */
/* PCK                                                                      */
/* ------------------------------------------------------------------------ */
/*! PCK0 */
/*#define PIN_PCK0        (PIO_PB22_IDX)
#define PIN_PCK0_MUX    (IOPORT_MODE_MUX_B)
#define PIN_PCK0_FLAGS  (PIO_PERIPH_B | PIO_DEFAULT)

#define PIN_PCK_0_MASK  PIO_PB22
#define PIN_PCK_0_PIO   PIOB
#define PIN_PCK_0_ID    ID_PIOB
#define PIN_PCK_0_TYPE  PIO_PERIPH_B
#define PIN_PCK_0_ATTR  PIO_DEFAULT*/

/**
 * \file
 * HSMCI
 * - \ref PINS_HSMCI
 *
 */


/** SD/MMC card detect pin definition. */
/*#define PIN_HSMCI_CD {PIO_PE6, PIOE, ID_PIOE, PIO_INPUT, PIO_PULLUP}
#define SD_MMC_0_CD_GPIO            (PIO_PE6_IDX)
#define SD_MMC_0_CD_PIO_ID          ID_PIOE
#define SD_MMC_0_CD_FLAGS           (PIO_INPUT | PIO_PULLUP)
#define SD_MMC_0_CD_DETECT_VALUE    0*/

/**
 * \file
 * UART
 * - \ref PINS_UART
 *
 */

/* ------------------------------------------------------------------------ */
/* UART                                                                     */
/* ------------------------------------------------------------------------ */

/*! UART pins (UTXD0 and URXD0) definitions, PA8,9. */
/*#define PINS_UART        (PIO_PA8A_URXD | PIO_PA9A_UTXD)
#define PINS_UART_FLAGS  (PIO_PERIPH_A | PIO_DEFAULT)

#define PINS_UART_MASK (PIO_PA8A_URXD | PIO_PA9A_UTXD)
#define PINS_UART_PIO  PIOA
#define PINS_UART_ID   ID_PIOA
#define PINS_UART_TYPE PIO_PERIPH_A
#define PINS_UART_ATTR PIO_DEFAULT

#define PINS_UART0        PINS_UART
#define PINS_UART0_PORT   IOPORT_PIOA
#define PINS_UART0_MASK   PINS_UART_MASK*/

/**
 * \file
 * USART0
 * - \ref PIN_USART0_RXD
 * - \ref PIN_USART0_TXD
 * - \ref PIN_USART0_CTS
 * - \ref PIN_USART0_RTS
 * - \ref PIN_USART0_SCK
 *
 * - \ref PIN_USART0_EN
 */

/* ------------------------------------------------------------------------ */
/* USART0                                                                   */
/* ------------------------------------------------------------------------ */
/*! USART0 pin RX */
#define PIN_USART0_RXD \ {PIO_PA10A_RXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_RXD_IDX        (PIO_PA10_IDX)
#define PIN_USART0_RXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/*! USART0 pin TX */
#define PIN_USART0_TXD \ {PIO_PA11A_TXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
	
#define PIN_USART0_TXD_IDX        (PIO_PA11_IDX)
#define PIN_USART0_TXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/*! USART0 pin CTS 
#define PIN_USART0_CTS\
{PIO_PB26A_CTS0, PIOB, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_CTS_IDX        (PIO_PB26_IDX)
#define PIN_USART0_CTS_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)*/
/*! USART0 pin RTS */
#define PIN_USART0_RTS \ {PIO_PB25A_RTS0, PIOB, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_RTS_IDX        (PIO_PB25_IDX)
#define PIN_USART0_RTS_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/*! USART0 pin SCK */
#define PIN_USART0_SCK \ {PIO_PA17B_SCK0, PIOA, ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_USART0_SCK_IDX        (PIO_PA17_IDX)
#define PIN_USART0_SCK_FLAGS      (PIO_PERIPH_B | PIO_DEFAULT)
/*
//! USART0 pin RX 
#define PIN_USART0_RXD\
	{PIO_PA10A_RXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_RXD_IDX        (PIO_PA10_IDX)
#define PIN_USART0_RXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
//! USART0 pin TX 
#define PIN_USART0_TXD\
	{PIO_PA11A_TXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_TXD_IDX        (PIO_PA11_IDX)
#define PIN_USART0_TXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
//! USART0 pin CTS 
#define PIN_USART0_CTS\
	{PIO_PB26A_CTS0, PIOB, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_CTS_IDX        (PIO_PB26_IDX)
#define PIN_USART0_CTS_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
//! USART0 pin RTS 
#define PIN_USART0_RTS\
	{PIO_PB25A_RTS0, PIOB, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_RTS_IDX        (PIO_PB25_IDX)
#define PIN_USART0_RTS_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
//! USART0 pin SCK 
#define PIN_USART0_SCK\
	{PIO_PA17B_SCK0, PIOA, ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_USART0_SCK_IDX        (PIO_PA17_IDX)
#define PIN_USART0_SCK_FLAGS      (PIO_PERIPH_B | PIO_DEFAULT)

//! USART0 pin ENABLE 
#define PIN_USART0_EN\
	{PIO_PE14, PIOE, ID_PIOE, PIO_OUTPUT_0, PIO_DEFAULT}
#define PIN_USART0_EN_IDX         (PIO_PE14_IDX)
#define PIN_USART0_EN_FLAGS       (PIO_OUTPUT_0 | PIO_DEFAULT)
*/



/**
 * \file
 * CAN
 * \ref PIN_CAN0_TRANSCEIVER_RXEN
 * \ref PIN_CAN0_TRANSCEIVER_RS
 * \ref PIN_CAN0_TXD
 * \ref PIN_CAN0_RXD
 * \ref PINS_CAN0
 *
 * \ref PIN_CAN1_TRANSCEIVER_RXEN
 * \ref PIN_CAN1_TRANSCEIVER_RS
 * \ref PIN_CAN1_TXD
 * \ref PIN_CAN1_RXD
 * \ref PINS_CAN1
 */

/* ------------------------------------------------------------------------ */
/* CAN                                                                      */
/* ------------------------------------------------------------------------ */
/** CAN0 transceiver PIN RS. */
//#define PIN_CAN0_TR_RS_IDX        PIO_PB20_IDX
//#define PIN_CAN0_TR_RS_FLAGS      (PIO_TYPE_PIO_OUTPUT_0 | PIO_DEFAULT)

/** CAN0 transceiver PIN EN. */
//#define PIN_CAN0_TR_EN_IDX        PIO_PB21_IDX
//#define PIN_CAN0_TR_EN_FLAGS      (PIO_TYPE_PIO_OUTPUT_0 | PIO_DEFAULT)

/** CAN0 PIN RX. */
#define PIN_CAN0_RX_IDX           (PIO_PA1_IDX)
#define PIN_CAN0_RX_FLAGS         (PIO_PERIPH_A | PIO_DEFAULT)

/** CAN0 PIN TX. */
#define PIN_CAN0_TX_IDX           (PIO_PA0_IDX)
#define PIN_CAN0_TX_FLAGS         (PIO_PERIPH_A | PIO_DEFAULT)

/** CAN1 transceiver PIN RS. */
//#define PIN_CAN1_TR_RS_IDX        PIO_PE15_IDX
//#define PIN_CAN1_TR_RS_FLAGS      (PIO_TYPE_PIO_OUTPUT_0 | PIO_DEFAULT)

/** CAN1 transceiver PIN EN. */
//#define PIN_CAN1_TR_EN_IDX        PIO_PE16_IDX
//#define PIN_CAN1_TR_EN_FLAGS      (PIO_TYPE_PIO_OUTPUT_0 | PIO_DEFAULT)

/** CAN1 PIN RX. */
#define PIN_CAN1_RX_IDX           (PIO_PB15_IDX)
#define PIN_CAN1_RX_FLAGS         (PIO_PERIPH_A | PIO_DEFAULT)

/** CAN1 PIN TX. */
#define PIN_CAN1_TX_IDX           (PIO_PB14_IDX)
#define PIN_CAN1_TX_FLAGS         (PIO_PERIPH_A | PIO_DEFAULT)



/* ------------------------------------------------------------------------ */

/**
 * \page sam3x_ek_mem "SAM3X-EK - Memories"
 * This page lists definitions related to internal & external on-board memories.
 *
 *
 */

/**
 * \file
 * NandFlash
 * - \ref PIN_EBI_NANDOE
 * - \ref PIN_EBI_NANDWE
 * - \ref PIN_EBI_NANDCLE
 * - \ref PIN_EBI_NANDALE
 * - \ref PIN_EBI_NANDIO
 * - \ref BOARD_NF_CE_PIN
 * - \ref BOARD_NF_RB_PIN
 * - \ref PINS_NANDFLASH
 *
 */

/* ------------------------------------------------------------------------ */
/* NAND FLASH                                                               */
/* ------------------------------------------------------------------------ */
/** NandFlash pins definition: OE. */
//#define PIN_EBI_NANDOE    (PIO_PC19_IDX)
//#define PIN_EBI_NANDOE_FLAGS    (PIO_PERIPH_A | PIO_PULLUP)

/** NandFlash pins definition: WE. */
//#define PIN_EBI_NANDWE    (PIO_PC20_IDX)
//#define PIN_EBI_NANDWE_FLAGS    (PIO_PERIPH_A | PIO_PULLUP)

/** NandFlash pins definition: CLE. */
//#define PIN_EBI_NANDCLE    (PIO_PD9_IDX)
//#define PIN_EBI_NANDCLE_FLAGS    (PIO_PERIPH_A | PIO_PULLUP)

/** NandFlash pins definition: ALE. */
//#define PIN_EBI_NANDALE    (PIO_PD8_IDX)
//#define PIN_EBI_NANDALE_FLAGS    (PIO_PERIPH_A | PIO_PULLUP)

/** NandFlash pins definition: DATA. */
/*#define PIN_EBI_NANDIO_0    (PIO_PC2_IDX)
#define PIN_EBI_NANDIO_0_FLAGS    (PIO_PERIPH_A | PIO_PULLUP)

#define PIN_EBI_NANDIO_1    (PIO_PC3_IDX)
#define PIN_EBI_NANDIO_1_FLAGS    (PIO_PERIPH_A | PIO_PULLUP)

#define PIN_EBI_NANDIO_2    (PIO_PC4_IDX)
#define PIN_EBI_NANDIO_2_FLAGS    (PIO_PERIPH_A | PIO_PULLUP)

#define PIN_EBI_NANDIO_3    (PIO_PC5_IDX)
#define PIN_EBI_NANDIO_3_FLAGS    (PIO_PERIPH_A | PIO_PULLUP)

#define PIN_EBI_NANDIO_4    (PIO_PC6_IDX)
#define PIN_EBI_NANDIO_4_FLAGS    (PIO_PERIPH_A | PIO_PULLUP)

#define PIN_EBI_NANDIO_5    (PIO_PC7_IDX)
#define PIN_EBI_NANDIO_5_FLAGS    (PIO_PERIPH_A | PIO_PULLUP)

#define PIN_EBI_NANDIO_6    (PIO_PC8_IDX)
#define PIN_EBI_NANDIO_6_FLAGS    (PIO_PERIPH_A | PIO_PULLUP)

#define PIN_EBI_NANDIO_7    (PIO_PC9_IDX)
#define PIN_EBI_NANDIO_7_FLAGS    (PIO_PERIPH_A | PIO_PULLUP)*/

/** Nandflash chip enable pin definition. */
//#define PIN_NF_CE_IDX    (PIO_PA6_IDX)
//#define PIN_NF_CE_FLAGS    (PIO_PERIPH_B | PIO_PULLUP)

/** Nandflash ready/busy pin definition. */
//#define PIN_NF_RB_IDX    (PIO_PA2_IDX)
//#define PIN_NF_RB_FLAGS    (PIO_PERIPH_B | PIO_PULLUP)

/* Chip select number for nand */
//#define BOARD_NAND_CS      0

/*
 * \addtopage sam3x_ek_mem
 * \section NandFlash
 * - \ref BOARD_NF_COMMAND_ADDR
 * - \ref BOARD_NF_ADDRESS_ADDR
 * - \ref BOARD_NF_DATA_ADDR
 *
 */




#endif  
