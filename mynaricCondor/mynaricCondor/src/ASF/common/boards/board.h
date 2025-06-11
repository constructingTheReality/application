/**
 * \file
 *
 * \brief Standard board header file.
 *
 * This file includes the appropriate board header file according to the
 * defined board (parameter BOARD).
 *
 * Copyright (c) 2009-2020 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef _BOARD_H_
#define _BOARD_H_

/**
 * \defgroup group_common_boards Generic board support
 *
 * The generic board support module includes board-specific definitions
 * and function prototypes, such as the board initialization function.
 *
 * \{
 */

#include "compiler.h"

#ifdef __cplusplus
extern "C" {
#endif


/*! \name Base Boards
 */
//! @{
#define EVK1100                     1  //!< AT32UC3A EVK1100 board.
#define EVK1101                     2  //!< AT32UC3B EVK1101 board.
#define UC3C_EK                     3  //!< AT32UC3C UC3C-EK board.
#define EVK1104                     4  //!< AT32UC3A3 EVK1104 board.
#define EVK1105                     5  //!< AT32UC3A EVK1105 board.
#define STK600_RCUC3L0              6  //!< STK600 RCUC3L0 board.
#define UC3L_EK                     7  //!< AT32UC3L-EK board.
#define XPLAIN                      8  //!< ATxmega128A1 Xplain board.
#define STK600_RC064X              10  //!< ATxmega256A3 STK600 board.
#define STK600_RC100X              11  //!< ATxmega128A1 STK600 board.
#define UC3_A3_XPLAINED            13  //!< ATUC3A3 UC3-A3 Xplained board.
#define UC3_L0_XPLAINED            15  //!< ATUC3L0 UC3-L0 Xplained board.
#define STK600_RCUC3D              16  //!< STK600 RCUC3D board.
#define STK600_RCUC3C0             17  //!< STK600 RCUC3C board.
#define XMEGA_B1_XPLAINED          18  //!< ATxmega128B1 Xplained board.
#define XMEGA_A1_XPLAINED          19  //!< ATxmega128A1 Xplain-A1 board.
#define XMEGA_A1U_XPLAINED_PRO     20  //!< ATxmega128A1U XMEGA-A1U Xplained Pro board.
#define STK600_RCUC3L4             21  //!< ATUCL4 STK600 board.
#define UC3_L0_XPLAINED_BC         22  //!< ATUC3L0 UC3-L0 Xplained board controller board.
#define MEGA1284P_XPLAINED_BC      23  //!< ATmega1284P-Xplained board controller board.
#define STK600_RC044X              24  //!< STK600 with RC044X routing card board.
#define STK600_RCUC3B0             25  //!< STK600 RCUC3B0 board.
#define UC3_L0_QT600               26  //!< QT600 UC3L0 MCU board.
#define XMEGA_A3BU_XPLAINED        27  //!< ATxmega256A3BU Xplained board.
#define STK600_RC064X_LCDX         28  //!< XMEGAB3 STK600 RC064X LCDX board.
#define STK600_RC100X_LCDX         29  //!< XMEGAB1 STK600 RC100X LCDX board.
#define UC3B_BOARD_CONTROLLER      30  //!< AT32UC3B1 board controller for Atmel boards.
#define RZ600                      31  //!< AT32UC3A RZ600 MCU board.
#define SAM3S_EK                   32  //!< SAM3S-EK board.
#define SAM3U_EK                   33  //!< SAM3U-EK board.
#define SAM3X_EK                   34  //!< SAM3X-EK board.


#define SAM3N_EK                   35  //!< SAM3N-EK board.
#define SAM3S_EK2                  36  //!< SAM3S-EK2 board.
#define SAM4S_EK                   37  //!< SAM4S-EK board.
#define STK600_RCUC3A0             38  //!< STK600 RCUC3A0 board.
#define STK600_MEGA                39  //!< STK600 MEGA board.
#define MEGA_1284P_XPLAINED        40  //!< ATmega1284P Xplained board.
#define SAM4S_XPLAINED             41  //!< SAM4S Xplained board.
#define ATXMEGA128A1_QT600         42  //!< QT600 ATXMEGA128A1 MCU board.
#define ARDUINO_DUE_X              43  //!< Arduino Due/X board.
#define STK600_RCUC3L3             44  //!< ATUCL3 STK600 board.
#define SAM4L_EK                   45  //!< SAM4L-EK board.
#define STK600_MEGA_RF             46  //!< STK600 MEGA RF EVK board.
#define XMEGA_C3_XPLAINED          47  //!< ATxmega384C3 Xplained board.
#define STK600_RC032X              48  //!< STK600 with RC032X routing card board.
#define SAM4S_EK2                  49  //!< SAM4S-EK2 board.
#define XMEGA_E5_XPLAINED          50  //!< ATxmega32E5 Xplained board.
#define SAM4E_EK                   51  //!< SAM4E-EK board.
#define ATMEGA256RFR2_XPLAINED_PRO 52  //!< ATmega256RFR2 Xplained Pro board.
#define SAM4S_XPLAINED_PRO         53  //!< SAM4S Xplained Pro board.
#define SAM4L_XPLAINED_PRO         54  //!< SAM4L Xplained Pro board.
#define ATMEGA256RFR2_ZIGBIT       55  //!< ATmega256RFR2 zigbit.
#define XMEGA_RF233_ZIGBIT         56  //!< ATxmega256A3U with AT86RF233 Zigbit.
#define XMEGA_RF212B_ZIGBIT        57  //!< ATxmega256A3U with AT86RF212B Zigbit.
#define SAM4S_WPIR_RD              58  //!< SAM4S-WPIR-RD board.
#define SAMD20_XPLAINED_PRO        59  //!< SAM D20 Xplained Pro board.
#define SAM4L8_XPLAINED_PRO        60  //!< SAM4L8 Xplained Pro board.
#define SAM4N_XPLAINED_PRO         61  //!< SAM4N Xplained Pro board.
#define XMEGA_A3_REB_CBB           62  //!< XMEGA REB Controller Base board.
#define ATMEGARFX_RCB              63  //!< RFR2 & RFA1 RCB.
#define SAM4C_EK                   64  //!< SAM4C-EK board.
#define RCB256RFR2_XPRO            65  //!< RFR2 RCB Xplained Pro board.
#define SAMG53_XPLAINED_PRO        66  //!< SAMG53 Xplained Pro board.
#define SAM4CP16BMB                67  //!< SAM4CP16BMB board.
#define SAM4E_XPLAINED_PRO         68  //!< SAM4E Xplained Pro board.
#define SAMD21_XPLAINED_PRO        69  //!< SAM D21 Xplained Pro board.
#define SAMR21_XPLAINED_PRO        70  //!< SAM R21 Xplained Pro board.
#define SAM4CMP_DB                 71  //!< SAM4CMP demo board.
#define SAM4CMS_DB                 72  //!< SAM4CMS demo board.
#define ATPL230AMB                 73  //!< ATPL230AMB board.
#define SAMD11_XPLAINED_PRO        74  //!< SAM D11 Xplained Pro board.
#define SAMG55_XPLAINED_PRO        75  //!< SAMG55 Xplained Pro board.
#define SAML21_XPLAINED_PRO        76  //!< SAM L21 Xplained Pro board.
#define SAMD10_XPLAINED_MINI       77  //!< SAM D10 Xplained Mini board.
#define SAMDA1_XPLAINED_PRO        78  //!< SAM DA1 Xplained Pro board.
#define SAMW25_XPLAINED_PRO        79  //!< SAMW25 Xplained Pro board.
#define SAMC21_XPLAINED_PRO        80  //!< SAM C21 Xplained Pro board.
#define SAMV71_XPLAINED_ULTRA      81  //!< SAMV71 Xplained Ultra board.
#define ATMEGA328P_XPLAINED_MINI   82  //!< ATMEGA328P Xplained MINI board.
#define ATMEGA328PB_XPLAINED_MINI  83  //!< ATMEGA328PB Xplained MINI board.
#define SAMB11_XPLAINED_PRO        84  //!< SAM B11 Xplained Pro board.
#define SAME70_XPLAINED            85  //!< SAME70 Xplained board.
#define SAML22_XPLAINED_PRO        86  //!< SAM L22 Xplained Pro board.
#define SAML22_XPLAINED_PRO_B      87  //!< SAM L22 Xplained Pro board.
#define SAMR21ZLL_EK               88  //!< SAMR21ZLL-EK board.
#define ATMEGA168PB_XPLAINED_MINI  89  //!< ATMEGA168PB Xplained MINI board.
#define ATMEGA324PB_XPLAINED_PRO   90  //!< ATMEGA324PB Xplained Pro board.
#define SAMB11ZR_XPLAINED_PRO      92  //!< SAM B11 ZR Xplained Pro board.
#define SAMR30_XPLAINED_PRO        93  //!< SAM R30 Xplained Pro board.
#define SAMHA1G16A_XPLAINED_PRO    94  //!< SAM HA1G16A Xplained Pro board.
#define SAMR34_XPLAINED_PRO        95  //!< SAM R34 Xplained Pro board.
#define SIMULATOR_XMEGA_A1         97  //!< Simulator for XMEGA A1 devices.
#define AVR_SIMULATOR_UC3          98  //!< Simulator for the AVR UC3 device family.
#define USER_BOARD                 99  //!< User-reserved board (if any).
#define DUMMY_BOARD                100 //!< Dummy board to support board-independent applications (e.g. bootloader).
#define SAMB11ZR_SENSOR_TAG        101 //!< SAMB11ZR sensor tag board
#define SAMR30_MODULE_XPLAINED_PRO 102 //!< SAM R30 Module Xplained Pro board.
#define SAMR21G18_MODULE           103 //!< SAMR21G18-MR210UA Module.
#define SAMR21B18_MODULE           104 //!< SAMR21B18-MZ210PA Module.
#define WLR089_XPLAINED_PRO        105 //!< WLR089_XPLAINED_PRO board.
//! @}

/*! \name Extension Boards
 */
//! @{
#define EXT1102                      1  //!< AT32UC3B EXT1102 board
#define MC300                        2  //!< AT32UC3 MC300 board
#define SENSORS_XPLAINED_INERTIAL_1  3  //!< Xplained inertial sensor board 1
#define SENSORS_XPLAINED_INERTIAL_2  4  //!< Xplained inertial sensor board 2
#define SENSORS_XPLAINED_PRESSURE_1  5  //!< Xplained pressure sensor board
#define SENSORS_XPLAINED_LIGHTPROX_1 6  //!< Xplained light & proximity sensor board
#define SENSORS_XPLAINED_INERTIAL_A1 7  //!< Xplained inertial sensor board "A"
#define RZ600_AT86RF231              8  //!< AT86RF231 RF board in RZ600
#define RZ600_AT86RF230B             9  //!< AT86RF230B RF board in RZ600
#define RZ600_AT86RF212             10  //!< AT86RF212 RF board in RZ600
#define SENSORS_XPLAINED_BREADBOARD 11  //!< Xplained sensor development breadboard
#define SECURITY_XPLAINED           12  //!< Xplained ATSHA204 board
#define USER_EXT_BOARD              99  //!< User-reserved extension board (if any).
//! @}

//#if BOARD == SAM3X_EK
#  include "mynaric_board/mynaricBoard.h" // sam3x_ek.h"
#  include "system_sam3x.h"
  /*No header-file to include*/
//#elif BOARD == ARDUINO_DUE_X
//#  include "arduino_due_x/arduino_due_x.h"
//#  include "system_sam3x.h"

//#else
//#  error No known Atmel board defined
//#endif

#if (defined EXT_BOARD)
#  if EXT_BOARD == MC300
#    include "mc300/mc300.h"
#  elif (EXT_BOARD == SENSORS_XPLAINED_INERTIAL_1)  || \
        (EXT_BOARD == SENSORS_XPLAINED_INERTIAL_2)  || \
        (EXT_BOARD == SENSORS_XPLAINED_INERTIAL_A1) || \
        (EXT_BOARD == SENSORS_XPLAINED_PRESSURE_1)  || \
        (EXT_BOARD == SENSORS_XPLAINED_LIGHTPROX_1) || \
        (EXT_BOARD == SENSORS_XPLAINED_BREADBOARD)
#    include "sensors_xplained/sensors_xplained.h"
#  elif EXT_BOARD == RZ600_AT86RF231
#     include "at86rf231/at86rf231.h"
#  elif EXT_BOARD == RZ600_AT86RF230B
#    include "at86rf230b/at86rf230b.h"
#  elif EXT_BOARD == RZ600_AT86RF212
#    include "at86rf212/at86rf212.h"
#  elif EXT_BOARD == SECURITY_XPLAINED
#    include "security_xplained.h"
#  elif EXT_BOARD == USER_EXT_BOARD
    // User-reserved area: #include the header file of your extension board here
    // (if any).
#  endif
#endif


#if (defined(__GNUC__) && defined(__AVR32__)) || (defined(__ICCAVR32__) || defined(__AAVR32__))
#ifdef __AVR32_ABI_COMPILER__ // Automatically defined when compiling for AVR32, not when assembling.

/*! \brief This function initializes the board target resources
 *
 * This function should be called to ensure proper initialization of the target
 * board hardware connected to the part.
 */
extern void board_init(void);

#endif  // #ifdef __AVR32_ABI_COMPILER__
#else
/*! \brief This function initializes the board target resources
 *
 * This function should be called to ensure proper initialization of the target
 * board hardware connected to the part.
 */
extern void board_init(void);
#endif


#ifdef __cplusplus
}
#endif

/**
 * \}
 */

#endif  // _BOARD_H_
