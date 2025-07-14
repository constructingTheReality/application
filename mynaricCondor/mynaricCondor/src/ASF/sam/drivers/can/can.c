/**
 * \file
 *
 * \brief Controller Area Network (CAN) driver module for SAM.
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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

#include "can.h"

/** @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/** @endcond */

/** Define the timemark mask. */
#define TIMEMARK_MASK              0x0000ffff

/* CAN timeout for synchronization. */
#define CAN_TIMEOUT                100000

/** The max value for CAN baudrate prescale. */
#define CAN_BAUDRATE_MAX_DIV       128

/** Define the scope for TQ. */
#define CAN_MIN_TQ_NUM             8
#define CAN_MAX_TQ_NUM             25

/** Define the fixed bit time value. */
#define CAN_BIT_SYNC               1
#define CAN_BIT_IPT                2

#define SIZE_RX_BUFFER	32 //RX incoming ring buffer is this big
#define SIZE_TX_BUFFER	16 //TX ring buffer is this big


volatile CAN_FRAME rx_frame_buff[SIZE_RX_BUFFER];
volatile CAN_FRAME tx_frame_buff[SIZE_TX_BUFFER];

volatile uint16_t rx_buffer_head, rx_buffer_tail;
volatile uint16_t tx_buffer_head, tx_buffer_tail;
	
static CanBusStatusRegisterBitAssignment_t CanBusStatusRegisterBitAssignment;	
typedef struct {
	uint8_t uc_tq;      /**< CAN_BIT_SYNC + uc_prog + uc_phase1 + uc_phase2
	                       = uc_tq, 8 <= uc_tq <= 25. */
	uint8_t uc_prog;    /**< Propagation segment, (3-bits + 1), 1~8; */
	uint8_t uc_phase1;  /**< Phase segment 1, (3-bits + 1), 1~8; */
	uint8_t uc_phase2;  /**< Phase segment 2, (3-bits + 1), 1~8, CAN_BIT_IPT
	                       <= uc_phase2; */
	uint8_t uc_sjw;     /**< Resynchronization jump width, (2-bits + 1),
	                       min(uc_phase1, 4); */
	uint8_t uc_sp;      /**< Sample point value, 0~100 in percent. */
} can_bit_timing_t;

/** Values of bit time register for different baudrates, Sample point =
 * ((1 + uc_prog + uc_phase1) / uc_tq) * 100%. */
const can_bit_timing_t can_bit_time[] = {
	{ 8, (2 + 1), (1 + 1), (1 + 1), (2 + 1), 75},
	{ 9, (1 + 1), (2 + 1), (2 + 1), (1 + 1), 67},
	{10, (2 + 1), (2 + 1), (2 + 1), (2 + 1), 70},
	{11, (3 + 1), (2 + 1), (2 + 1), (3 + 1), 72},
	{12, (2 + 1), (3 + 1), (3 + 1), (3 + 1), 67},
	{13, (3 + 1), (3 + 1), (3 + 1), (3 + 1), 77},
	{14, (3 + 1), (3 + 1), (4 + 1), (3 + 1), 64},
	{15, (3 + 1), (4 + 1), (4 + 1), (3 + 1), 67},
	{16, (4 + 1), (4 + 1), (4 + 1), (3 + 1), 69},
	{17, (5 + 1), (4 + 1), (4 + 1), (3 + 1), 71},
	{18, (4 + 1), (5 + 1), (5 + 1), (3 + 1), 67},
	{19, (5 + 1), (5 + 1), (5 + 1), (3 + 1), 68},
	{20, (6 + 1), (5 + 1), (5 + 1), (3 + 1), 70},
	{21, (7 + 1), (5 + 1), (5 + 1), (3 + 1), 71},
	{22, (6 + 1), (6 + 1), (6 + 1), (3 + 1), 68},
	{23, (7 + 1), (7 + 1), (6 + 1), (3 + 1), 70},
	{24, (6 + 1), (7 + 1), (7 + 1), (3 + 1), 67},
	{25, (7 + 1), (7 + 1), (7 + 1), (3 + 1), 68}
};

/**
 * \brief Configure CAN baudrate.
 *
 * \param p_can       Pointer to a CAN peripheral instance.
 * \param ul_mck      The input main clock for the CAN module.
 * \param ul_baudrate Baudrate value (kB/s), allowed values:
 *                    1000, 800, 500, 250, 125, 50, 25, 10, 5.
 *
 * \retval Set the baudrate successfully or not.
 */
static uint32_t can_set_baudrate(Can *p_can, uint32_t ul_mck,
		uint32_t ul_baudrate)
{
	uint8_t uc_tq;
	uint8_t uc_prescale;
	uint32_t ul_mod;
	uint32_t ul_cur_mod;
	can_bit_timing_t *p_bit_time;

	/* Check whether the baudrate prescale will be greater than the max
	 * divide value. */
	if (((ul_mck + (ul_baudrate * CAN_MAX_TQ_NUM * 1000 - 1)) /
			(ul_baudrate * CAN_MAX_TQ_NUM * 1000)) >
			CAN_BAUDRATE_MAX_DIV) {
		return 0;
	}

	/* Check whether the input MCK is too small. */
	if ((ul_mck / 2)  < ul_baudrate * CAN_MIN_TQ_NUM * 1000) {
		return 0;
	}

	/* Initialize it as the minimum Time Quantum. */
	uc_tq = CAN_MIN_TQ_NUM;

	/* Initialize the remainder as the max value. When the remainder is 0,
	 *get the right TQ number. */
	ul_mod = 0xffffffff;
	/* Find out the approximate Time Quantum according to the baudrate. */
	for (uint8_t i = CAN_MIN_TQ_NUM; i <= CAN_MAX_TQ_NUM; i++) {
		if ((ul_mck / (ul_baudrate * i * 1000)) <=
				CAN_BAUDRATE_MAX_DIV) {
			ul_cur_mod = ul_mck % (ul_baudrate * i * 1000);
			if (ul_cur_mod < ul_mod) {
				ul_mod = ul_cur_mod;
				uc_tq = i;
				if (!ul_mod) {
					break;
				}
			}
		}
	}

	/* Calculate the baudrate prescale value. */
	uc_prescale = ul_mck / (ul_baudrate * uc_tq * 1000);
	if (uc_prescale < 2) {
		return 0;
	}

	/* Get the right CAN BIT Timing group. */
	p_bit_time = (can_bit_timing_t *)&can_bit_time[uc_tq - CAN_MIN_TQ_NUM];

	/* Before modifying the CANBR register, disable the CAN controller. */
	can_disable(p_can);

	/* Write into the CAN baudrate register. */
	p_can->CAN_BR = CAN_BR_PHASE2(p_bit_time->uc_phase2 - 1) |
			CAN_BR_PHASE1(p_bit_time->uc_phase1 - 1) |
			CAN_BR_PROPAG(p_bit_time->uc_prog - 1) |
			CAN_BR_SJW(p_bit_time->uc_sjw - 1) |
			CAN_BR_BRP(uc_prescale - 1);
	return 1;
}

/**
 * \brief Initialize CAN controller.
 *
 * \param p_can  Pointer to a CAN peripheral instance.
 * \param ul_mck CAN module input clock.
 * \param ul_baudrate CAN communication baudrate in kbs.
 *
 * \retval 0 If failed to initialize the CAN module; otherwise successful.
 *
 * \note PMC clock for CAN peripheral should be enabled before calling this
 *function.
 */
uint32_t can_init(Can *p_can, uint32_t ul_mck, uint32_t ul_baudrate)
{
	uint32_t ul_flag;
	uint32_t ul_tick;


	//initialize all function pointers to null
	for (int i = 0; i < 9; i++) cbCANFrame[i] = 0;

	/* Initialize the baudrate for CAN module. */
	ul_flag = can_set_baudrate(p_can, ul_mck, ul_baudrate);
	if (ul_flag == 0) {
		return 0;
	}

	/* Reset the CAN eight message mailbox. */
	can_reset_all_mailbox(p_can);

	/* Enable the CAN controller. */
	can_enable(p_can);

	/* Wait until the CAN is synchronized with the bus activity. */
	ul_flag = 0;
	ul_tick = 0;
	while (!(ul_flag & CAN_SR_WAKEUP) && (ul_tick < CAN_TIMEOUT)) {
		ul_flag = can_get_status(p_can);
		ul_tick++;
	}

	/* Timeout or the CAN module has been synchronized with the bus. */
	if (CAN_TIMEOUT == ul_tick) {
		return 0;
	} else {
		return 1;
	}
}

/**
 * \brief Enable CAN Controller.
 *
 * \param p_can  Pointer to a CAN peripheral instance.
 */
void can_enable(Can *p_can)
{
	p_can->CAN_MR |= CAN_MR_CANEN;
}

/**
 * \brief Disable CAN Controller.
 *
 * \param p_can  Pointer to a CAN peripheral instance.
 */
void can_disable(Can *p_can)
{
	p_can->CAN_MR &= ~CAN_MR_CANEN;
}

/**
 * \brief Disable CAN Controller low power mode.
 *
 * \param p_can  Pointer to a CAN peripheral instance.
 */
void can_disable_low_power_mode(Can *p_can)
{
	p_can->CAN_MR &= ~CAN_MR_LPM;
}

/**
 * \brief Enable CAN Controller low power mode.
 *
 * \param p_can  Pointer to a CAN peripheral instance.
 */
void can_enable_low_power_mode(Can *p_can)
{
	p_can->CAN_MR |= CAN_MR_LPM;
}

/**
 * \brief Disable CAN Controller autobaud/listen mode.
 *
 * \param p_can  Pointer to a CAN peripheral instance.
 */
void can_disable_autobaud_listen_mode(Can *p_can)
{
	p_can->CAN_MR &= ~CAN_MR_ABM;
}

/**
 * \brief Enable CAN Controller autobaud/listen mode.
 *
 * \param p_can  Pointer to a CAN peripheral instance.
 */
void can_enable_autobaud_listen_mode(Can *p_can)
{
	p_can->CAN_MR |= CAN_MR_ABM;
}

/**
 * \brief CAN Controller won't generate overload frame.
 *
 * \param p_can  Pointer to a CAN peripheral instance.
 */
void can_disable_overload_frame(Can *p_can)
{
	p_can->CAN_MR &= ~CAN_MR_OVL;
}

/**
 * \brief CAN Controller will generate an overload frame after each successful
 *        reception for mailboxes configured in Receive mode, Producer and
 *        Consumer.
 *
 * \param p_can  Pointer to a CAN peripheral instance.
 */
void can_enable_overload_frame(Can *p_can)
{
	p_can->CAN_MR |= CAN_MR_OVL;
}

/**
 * \brief Configure the timestamp capture point, at the start or the end of
 *        frame.
 *
 * \param p_can   Pointer to a CAN peripheral instance.
 * \param ul_flag 0: Timestamp is captured at each start of frame;
 *                1: Timestamp is captured at each end of frame.
 */
void can_set_timestamp_capture_point(Can *p_can, uint32_t ul_flag)
{
	if (ul_flag) {
		p_can->CAN_MR |= CAN_MR_TEOF;
	} else {
		p_can->CAN_MR &= ~CAN_MR_TEOF;
	}
}

/**
 * \brief Disable CAN Controller time triggered mode.
 *
 * \param p_can  Pointer to a CAN peripheral instance.
 */
void can_disable_time_triggered_mode(Can *p_can)
{
	p_can->CAN_MR &= ~CAN_MR_TTM;
}

/**
 * \brief Enable CAN Controller time triggered mode.
 *
 * \param p_can  Pointer to a CAN peripheral instance.
 */
void can_enable_time_triggered_mode(Can *p_can)
{
	p_can->CAN_MR |= CAN_MR_TTM;
}

/**
 * \brief Disable CAN Controller timer freeze.
 *
 * \param p_can  Pointer to a CAN peripheral instance.
 */
void can_disable_timer_freeze(Can *p_can)
{
	p_can->CAN_MR &= ~CAN_MR_TIMFRZ;
}

/**
 * \brief Enable CAN Controller timer freeze.
 *
 * \param p_can  Pointer to a CAN peripheral instance.
 */
void can_enable_timer_freeze(Can *p_can)
{
	p_can->CAN_MR |= CAN_MR_TIMFRZ;
}

/**
 * \brief Disable CAN Controller transmit repeat function.
 *
 * \param p_can  Pointer to a CAN peripheral instance.
 */
void can_disable_tx_repeat(Can *p_can)
{
	p_can->CAN_MR |= CAN_MR_DRPT;
}

/**
 * \brief Enable CAN Controller transmit repeat function.
 *
 * \param p_can  Pointer to a CAN peripheral instance.
 */
void can_enable_tx_repeat(Can *p_can)
{
	p_can->CAN_MR &= ~CAN_MR_DRPT;
}

#if !(SAM4E)

/**
 * \brief Configure CAN Controller reception synchronization stage.
 *
 * \param p_can    Pointer to a CAN peripheral instance.
 * \param ul_stage The reception stage to be configured.
 *
 * \note This is just for debug purpose only.
 */
void can_set_rx_sync_stage(Can *p_can, uint32_t ul_stage)
{
	p_can->CAN_MR = (p_can->CAN_MR & ~CAN_MR_RXSYNC_Msk) | ul_stage;
}

#endif

/**
 * \brief Enable CAN interrupt.
 *
 * \param p_can  Pointer to a CAN peripheral instance.
 * \param dw_mask Interrupt to be enabled.
 */
void can_enable_interrupt(Can *p_can, uint32_t dw_mask)
{
	p_can->CAN_IER = dw_mask;
}

/**
 * \brief Disable CAN interrupt.
 *
 * \param p_can  Pointer to a CAN peripheral instance.
 * \param dw_mask Interrupt to be disabled.
 */
void can_disable_interrupt(Can *p_can, uint32_t dw_mask)
{
	p_can->CAN_IDR = dw_mask;
}

/**
 * \brief Get CAN Interrupt Mask.
 *
 * \param p_can Pointer to a CAN peripheral instance.
 *
 * \retval CAN interrupt mask.
 */
uint32_t can_get_interrupt_mask(Can *p_can)
{
	return (p_can->CAN_IMR);
}

/**
 * \brief Get CAN status.
 *
 * \param p_can Pointer to a CAN peripheral instance.
 *
 * \retval CAN status.
 */
uint32_t can_get_status(Can *p_can)
{
	return (p_can->CAN_SR);
}

/**
 * \brief Get the 16-bit free-running internal timer count.
 *
 * \param p_can Pointer to a CAN peripheral instance.
 *
 * \retval The internal CAN free-running timer counter.
 */
uint32_t can_get_internal_timer_value(Can *p_can)
{
	return (p_can->CAN_TIM);
}

/**
 * \brief Get CAN timestamp register value.
 *
 * \param p_can Pointer to a CAN peripheral instance.
 *
 * \retval The timestamp value.
 */
uint32_t can_get_timestamp_value(Can *p_can)
{
	return (p_can->CAN_TIMESTP);
}

/**
 * \brief Get CAN transmit error counter.
 *
 * \param p_can Pointer to a CAN peripheral instance.
 *
 * \retval Transmit error counter.
 */
uint8_t can_get_tx_error_cnt(Can *p_can)
{
	return (uint8_t)(p_can->CAN_ECR >> CAN_ECR_TEC_Pos);
}

/**
 * \brief Get CAN receive error counter.
 *
 * \param p_can Pointer to a CAN peripheral instance.
 *
 * \retval Receive error counter.
 */
uint8_t can_get_rx_error_cnt(Can *p_can)
{
	return (uint8_t)(p_can->CAN_ECR >> CAN_ECR_REC_Pos);
}

/**
 * \brief Reset the internal free-running 16-bit timer.
 *
 * \param p_can Pointer to a CAN peripheral instance.
 *
 * \note If the internal timer counter is frozen, this function automatically
 * re-enables it.
 */
void can_reset_internal_timer(Can *p_can)
{
	p_can->CAN_TCR |= CAN_TCR_TIMRST;
}

/**
 * \brief Send global transfer request.
 *
 * \param p_can   Pointer to a CAN peripheral instance.
 * \param uc_mask Mask for mailboxes that are requested to transfer.
 */
void can_global_send_transfer_cmd(Can *p_can, uint8_t uc_mask)
{
	uint32_t ul_reg;

	ul_reg = p_can->CAN_TCR & ((uint32_t) ~GLOBAL_MAILBOX_MASK);
	p_can->CAN_TCR = ul_reg | uc_mask;
}

/**
 * \brief Send global abort request.
 *
 * \param p_can   Pointer to a CAN peripheral instance.
 * \param uc_mask Mask for mailboxes that are requested to abort.
 */
void can_global_send_abort_cmd(Can *p_can, uint8_t uc_mask)
{
	uint32_t ul_reg;

	ul_reg = p_can->CAN_ACR & ((uint32_t) ~GLOBAL_MAILBOX_MASK);
	p_can->CAN_ACR = ul_reg | uc_mask;
}

/**
 * \brief Configure the timemark for the mailbox.
 *
 * \param p_can    Pointer to a CAN peripheral instance.
 * \param uc_index Indicate which mailbox is to be configured.
 * \param us_cnt   The timemark to be set.
 *
 * \note The timemark is active in Time Triggered mode only.
 */
void can_mailbox_set_timemark(Can *p_can, uint8_t uc_index, uint16_t us_cnt)
{
	uint32_t ul_reg;

	ul_reg = p_can->CAN_MB[uc_index].CAN_MMR & ((uint32_t) ~TIMEMARK_MASK);
	p_can->CAN_MB[uc_index].CAN_MMR = ul_reg | us_cnt;
}

/**
 * \brief Get status of the mailbox.
 *
 * \param p_can    Pointer to a CAN peripheral instance.
 * \param uc_index Indicate which mailbox is to be read.
 *
 * \retval The mailbox status.
 */
uint32_t can_mailbox_get_status(Can *p_can, uint8_t uc_index)
{
	return (p_can->CAN_MB[uc_index].CAN_MSR);
}

/**
 * \brief Send single mailbox transfer request.
 *
 * \param p_can   Pointer to a CAN peripheral instance.
 * \param p_mailbox Pointer to a CAN mailbox instance.
 */
void can_mailbox_send_transfer_cmd(Can *p_can, can_mb_conf_t *p_mailbox)
{
	uint8_t uc_index;

	uc_index = (uint8_t)p_mailbox->ul_mb_idx;

	p_can->CAN_MB[uc_index].CAN_MCR = CAN_MCR_MTCR |
			CAN_MCR_MDLC(p_mailbox->uc_length);;
}

/**
 * \brief Send single mailbox abort request.
 *
 * \param p_can    Pointer to a CAN peripheral instance.
 * \param p_mailbox Pointer to a CAN mailbox instance.
 */
void can_mailbox_send_abort_cmd(Can *p_can, can_mb_conf_t *p_mailbox)
{
	uint8_t uc_index;

	uc_index = (uint8_t)p_mailbox->ul_mb_idx;

	p_can->CAN_MB[uc_index].CAN_MCR = CAN_MCR_MACR |
			CAN_MCR_MDLC(p_mailbox->uc_length);;
}

/**
 * \brief Initialize the mailbox in different mode and set up related
 *        configuration.
 *
 * \param p_can    Pointer to a CAN peripheral instance.
 * \param p_mailbox Pointer to a CAN mailbox instance.
 */
void can_mailbox_init(Can *p_can, can_mb_conf_t *p_mailbox)
{
	uint8_t uc_index;

	uc_index = (uint8_t)p_mailbox->ul_mb_idx;
	/* Check the object type of the mailbox. If it's used to disable the
	 * mailbox, reset the whole mailbox. */
	if (!p_mailbox->uc_obj_type) {
		p_can->CAN_MB[uc_index].CAN_MMR = 0;
		p_can->CAN_MB[uc_index].CAN_MAM = 0;
		p_can->CAN_MB[uc_index].CAN_MID = 0;
		p_can->CAN_MB[uc_index].CAN_MDL = 0;
		p_can->CAN_MB[uc_index].CAN_MDH = 0;
		p_can->CAN_MB[uc_index].CAN_MCR = 0;
		return;
	}

	/* Set the priority in Transmit mode. */
	p_can->CAN_MB[uc_index].CAN_MMR = (p_can->CAN_MB[uc_index].CAN_MMR &
			~CAN_MMR_PRIOR_Msk) |
			(p_mailbox->uc_tx_prio << CAN_MMR_PRIOR_Pos);

	/* Set the message ID and message acceptance mask for the mailbox in
	 * other modes. */
	if (p_mailbox->uc_id_ver) {
		p_can->CAN_MB[uc_index].CAN_MAM = p_mailbox->ul_id_msk |
				CAN_MAM_MIDE;
		p_can->CAN_MB[uc_index].CAN_MID = p_mailbox->ul_id |
				CAN_MAM_MIDE;
	} else {
		p_can->CAN_MB[uc_index].CAN_MAM = p_mailbox->ul_id_msk;
		p_can->CAN_MB[uc_index].CAN_MID = p_mailbox->ul_id;
	}

	/* Set up mailbox in one of the five different modes. */
	p_can->CAN_MB[uc_index].CAN_MMR = (p_can->CAN_MB[uc_index].CAN_MMR &
			~CAN_MMR_MOT_Msk) |
			(p_mailbox->uc_obj_type << CAN_MMR_MOT_Pos);
}

/**
 * \brief Read receive information for the mailbox.
 *
 * \param p_can     Pointer to a CAN peripheral instance.
 * \param p_mailbox Pointer to a CAN mailbox instance.
 *
 * \retval Different CAN mailbox transfer status.
 *
 * \note Read the mailbox status before calling this function.
 */
uint32_t can_mailbox_read(Can *p_can, can_mb_conf_t *p_mailbox)
{
	uint32_t ul_status;
	uint8_t uc_index;
	uint32_t ul_retval;

	ul_retval = 0;
	uc_index = (uint8_t)p_mailbox->ul_mb_idx;
	ul_status = p_mailbox->ul_status;

	/* Check whether there is overwriting happening in Receive with
	 * Overwrite mode,
	 * or there're messages lost in Receive mode. */
	if ((ul_status & CAN_MSR_MRDY) && (ul_status & CAN_MSR_MMI)) {
		ul_retval = CAN_MAILBOX_RX_OVER;
	}

	/* Read the message family ID. */
	p_mailbox->ul_fid = p_can->CAN_MB[uc_index].CAN_MFID &
			CAN_MFID_MFID_Msk;

	/* Read received data length. */
	p_mailbox->uc_length
		= (ul_status & CAN_MSR_MDLC_Msk) >> CAN_MSR_MDLC_Pos;

	/* Read received data. */
	p_mailbox->ul_datal = p_can->CAN_MB[uc_index].CAN_MDL;
	if (p_mailbox->uc_length > 4) {
		p_mailbox->ul_datah = p_can->CAN_MB[uc_index].CAN_MDH;
	}

	/* Read the mailbox status again to check whether the software needs to
	 * re-read mailbox data register. */
	p_mailbox->ul_status = p_can->CAN_MB[uc_index].CAN_MSR;
	ul_status = p_mailbox->ul_status;
	if (ul_status & CAN_MSR_MMI) {
		ul_retval |= CAN_MAILBOX_RX_NEED_RD_AGAIN;
	} else {
		ul_retval |= CAN_MAILBOX_TRANSFER_OK;
	}

	/* Enable next receive process. */
	can_mailbox_send_transfer_cmd(p_can, p_mailbox);

	return ul_retval;
}

/**
 * \brief Prepare transmit information and write them into the mailbox.
 *
 * \param p_can     Pointer to a CAN peripheral instance.
 * \param p_mailbox Pointer to a CAN mailbox instance.
 *
 * \retval CAN_MAILBOX_NOT_READY: Failed because mailbox isn't ready.
 *       CAN_MAILBOX_TRANSFER_OK: Successfully write message into mailbox.
 *
 * \note After calling this function, the mailbox message won't be sent out
 *until
 * can_mailbox_send_transfer_cmd() is called.
 */
uint32_t can_mailbox_write(Can *p_can, can_mb_conf_t *p_mailbox)
{
	uint32_t ul_status;
	uint8_t uc_index;

	uc_index = (uint8_t)p_mailbox->ul_mb_idx;
	/* Read the mailbox status firstly to check whether the mailbox is ready
	 *or not. */
	p_mailbox->ul_status = can_mailbox_get_status(p_can, uc_index);
	ul_status = p_mailbox->ul_status;
	if (!(ul_status & CAN_MSR_MRDY)) {
		return CAN_MAILBOX_NOT_READY;
	}

	/* Write transmit identifier. */
	if (p_mailbox->uc_id_ver) {
		p_can->CAN_MB[uc_index].CAN_MID = p_mailbox->ul_id |
				CAN_MAM_MIDE;
	} else {
		p_can->CAN_MB[uc_index].CAN_MID = p_mailbox->ul_id;
	}

	/* Write transmit data into mailbox data register. */
	p_can->CAN_MB[uc_index].CAN_MDL = p_mailbox->ul_datal;
	if (p_mailbox->uc_length > 4) {
		p_can->CAN_MB[uc_index].CAN_MDH = p_mailbox->ul_datah;
	}

	/* Write transmit data length into mailbox control register. */
	p_can->CAN_MB[uc_index].CAN_MCR = CAN_MCR_MDLC(p_mailbox->uc_length);

	return CAN_MAILBOX_TRANSFER_OK;
}

/**
 * \brief Require to send out a remote frame.
 *
 * \param p_can    Pointer to a CAN peripheral instance.
 * \param p_mailbox Pointer to a CAN mailbox instance.
 *
 * \retval CAN_MAILBOX_NOT_READY: Failed because mailbox isn't ready for
 *transmitting message.
 *       CAN_MAILBOX_TRANSFER_OK: Successfully send out a remote frame.
 */
uint32_t can_mailbox_tx_remote_frame(Can *p_can, can_mb_conf_t *p_mailbox)
{
	uint32_t ul_status;
	uint8_t uc_index;

	uc_index = (uint8_t)p_mailbox->ul_mb_idx;
	/* Read the mailbox status firstly to check whether the mailbox is ready
	 *or not. */
	p_mailbox->ul_status = p_can->CAN_MB[uc_index].CAN_MSR;
	ul_status = p_mailbox->ul_status;
	if (!(ul_status & CAN_MSR_MRDY)) {
		return CAN_MAILBOX_NOT_READY;
	}

	/* Write transmit identifier. */
	if (p_mailbox->uc_id_ver) {
		p_can->CAN_MB[uc_index].CAN_MID = p_mailbox->ul_id |
				CAN_MAM_MIDE;
	} else {
		p_can->CAN_MB[uc_index].CAN_MID = p_mailbox->ul_id;
	}

	/* Set the RTR bit in the sent frame. */
	p_can->CAN_MB[uc_index].CAN_MCR = CAN_MCR_MRTR |
			CAN_MCR_MDLC(p_mailbox->uc_length);

	/* Set the MBx bit in the Transfer Command Register to send out the
	 *remote frame. */
	can_global_send_transfer_cmd(p_can, (1 << uc_index));

	return CAN_MAILBOX_TRANSFER_OK;
}

/**
 * \brief Reset the eight mailboxes.
 *
 * \param p_can Pointer to a CAN peripheral instance.
 */
void can_reset_all_mailbox(Can *p_can)
{
	can_mb_conf_t mb_config_t;

	/* Set the mailbox object type parameter to disable the mailbox. */
	mb_config_t.uc_obj_type = CAN_MB_DISABLE_MODE;

	for (uint8_t i = 0; i < CANMB_NUMBER; i++) {
		mb_config_t.ul_mb_idx = i;
		can_mailbox_init(p_can, &mb_config_t);
	}
}


/*-------------------------------------*/

/**
 * \brief Send single mailbox transfer request.
 *
 * \param uc_index Indicate which mailbox is to be configured.
 */
void mailbox_send_transfer_cmd(Can *p_can, uint8_t uc_index)
{
	if (uc_index > CANMB_NUMBER-1) uc_index = CANMB_NUMBER-1;
	p_can->CAN_MB[uc_index].CAN_MCR |= CAN_MCR_MTCR;
}
/**
 * \brief Read a frame from out of the mailbox and into a software buffer
 *
 * \param uc_index which mailbox to read
 * \param rxframe Pointer to a receive frame structure which we'll fill out
 *
 * \retval Different CAN mailbox transfer status.
 *
 */
uint32_t mailbox_read(Can *p_can, uint8_t uc_index, volatile CAN_FRAME *rxframe)
{
	uint32_t ul_status;
	uint32_t ul_retval;
	uint32_t ul_id;
	uint32_t ul_datal, ul_datah;

	if (uc_index > CANMB_NUMBER-1) uc_index = CANMB_NUMBER-1;

	ul_retval = 0;
	ul_status = p_can->CAN_MB[uc_index].CAN_MSR;

	/* Check whether there is overwriting happening in Receive with Overwrite mode,
	   or there're messages lost in Receive mode. */
	if ((ul_status & CAN_MSR_MRDY) && (ul_status & CAN_MSR_MMI)) {
		ul_retval = CAN_MAILBOX_RX_OVER;
	}

	ul_id = p_can->CAN_MB[uc_index].CAN_MID;
	if ((ul_id & CAN_MID_MIDE) == CAN_MID_MIDE) { //extended id
		rxframe->id = ul_id & 0x1FFFFFFFu;
		rxframe->extended = true;
	}
	else { //standard ID
		rxframe->id = (ul_id  >> CAN_MID_MIDvA_Pos) & 0x7ffu;
		rxframe->extended = false;
	}
	rxframe->fid = p_can->CAN_MB[uc_index].CAN_MFID;
	rxframe->length = (ul_status & CAN_MSR_MDLC_Msk) >> CAN_MSR_MDLC_Pos;
	ul_datal = p_can->CAN_MB[uc_index].CAN_MDL;
	ul_datah = p_can->CAN_MB[uc_index].CAN_MDH;

	rxframe->data.high = ul_datah;
	rxframe->data.low = ul_datal;

	/* Read the mailbox status again to check whether the software needs to re-read mailbox data register. */
	ul_status = p_can->CAN_MB[uc_index].CAN_MSR;	
	if (ul_status & CAN_MSR_MMI) {
		ul_retval |= CAN_MAILBOX_RX_NEED_RD_AGAIN;
	} else {
		ul_retval |= CAN_MAILBOX_TRANSFER_OK;
	}

	/* Enable next receive process. */
	mailbox_send_transfer_cmd(p_can, uc_index);

	return ul_retval;
}


/**
* \brief Handle all interrupt reasons
*/
void vInterruptHandler(Can *p_can)
{

	uint32_t ul_status = p_can->CAN_SR; //get status of interrupts

	if (ul_status & CAN_SR_MB0) { //mailbox 0 event
		mailbox_int_handler(p_can, 0, ul_status);
	}
	if (ul_status & CAN_SR_MB1) { //mailbox 1 event
		mailbox_int_handler(p_can, 1, ul_status);
	}
	if (ul_status & CAN_SR_MB2) { //mailbox 2 event
		mailbox_int_handler(p_can, 2, ul_status);
	}
	if (ul_status & CAN_SR_MB3) { //mailbox 3 event
		mailbox_int_handler(p_can, 3, ul_status);
	}
	if (ul_status & CAN_SR_MB4) { //mailbox 4 event
		mailbox_int_handler(p_can, 4, ul_status);
	}
	if (ul_status & CAN_SR_MB5) { //mailbox 5 event
		mailbox_int_handler(p_can, 5, ul_status);
	}
	if (ul_status & CAN_SR_MB6) { //mailbox 6 event
		mailbox_int_handler(p_can, 6, ul_status);
	}
	if (ul_status & CAN_SR_MB7) { //mailbox 7 event
		mailbox_int_handler(p_can, 7, ul_status);
	}
	
	if (ul_status & CAN_SR_ERRA) { //error active
		CanBusStatusRegisterBitAssignment.bBitErrorActive = 1;
		disable_interrupt(CAN0, CAN_IDR_ERRA );		
		disable_interrupt(CAN1, CAN_IDR_ERRA );
	}
	else
	{
		CanBusStatusRegisterBitAssignment.bBitErrorActive = 0;
	}
	
	
/*---*/		
	if (ul_status & CAN_SR_WARN) { //warning limit
		CanBusStatusRegisterBitAssignment.bwarningLimit = 1;
		disable_interrupt(CAN0, CAN_IDR_WARN );
		disable_interrupt(CAN1, CAN_IDR_WARN );
	}
	else
	{
		CanBusStatusRegisterBitAssignment.bwarningLimit = 0;
	}
/*---*/	
	if (ul_status & CAN_SR_ERRP) { //error passive
		
		CanBusStatusRegisterBitAssignment.bErrorPassive = 1;
		
		disable_interrupt(CAN0, CAN_IDR_ERRP );
		disable_interrupt(CAN1, CAN_IDR_ERRP );
	}
	else
	{
		CanBusStatusRegisterBitAssignment.bErrorPassive = 0;
	}

/*---*/	
	if (ul_status & CAN_SR_BOFF) { //bus off
		CanBusStatusRegisterBitAssignment.bBusOff = 1;
		disable_interrupt(CAN0, CAN_SR_BOFF );
		disable_interrupt(CAN1, CAN_SR_BOFF );
	}
	else
	{
		CanBusStatusRegisterBitAssignment.bBusOff = 0;
	}
/*---*/	
	if (ul_status & CAN_SR_SLEEP) { //controller in sleep mode
		CanBusStatusRegisterBitAssignment.bControllerInSleepMode = 1;
				disable_interrupt(CAN0, CAN_SR_SLEEP );
		disable_interrupt(CAN1, CAN_SR_SLEEP );
	}
	else
	{
		CanBusStatusRegisterBitAssignment.bControllerInSleepMode = 0;		
	}
	//if (ul_status & CAN_SR_WAKEUP) { //controller woke up
	//	CanBusStatusRegisterBitAssignment.bErrorPassive = 1;
//	}
/*---*/
	if (ul_status & CAN_SR_TOVF) { //timer overflow
		CanBusStatusRegisterBitAssignment.bTimerOverflow = 1;
		disable_interrupt(CAN0, CAN_SR_TOVF );
		disable_interrupt(CAN1, CAN_SR_TOVF );
	}
	else
	{
		CanBusStatusRegisterBitAssignment.bTimerOverflow = 0;
	}
	
	//if (ul_status & CAN_SR_TSTP) { //timestamp - start or end of frame
		//CanBusStatusRegisterBitAssignment.bErrorPassive = 1;
	//}
	
/*---*/		
	if (ul_status & CAN_SR_CERR) { //CRC error in mailbox
		CanBusStatusRegisterBitAssignment.bCrcErrorInMailbox = 1;
		disable_interrupt(CAN0, CAN_SR_CERR );
		disable_interrupt(CAN1, CAN_SR_CERR );
		
	}
	else
	{
		CanBusStatusRegisterBitAssignment.bCrcErrorInMailbox = 0;
	}
		
/*---*/			
	if (ul_status & CAN_SR_SERR) { //stuffing error in mailbox
		CanBusStatusRegisterBitAssignment.bStuffingErrorInMailbox = 1;
		disable_interrupt(CAN0, CAN_SR_SERR );
		disable_interrupt(CAN1, CAN_SR_SERR );
		
	}
	else
	{
		CanBusStatusRegisterBitAssignment.bStuffingErrorInMailbox = 0;
	}
		
/*---*/	
	if (ul_status & CAN_SR_AERR) { //ack error
		CanBusStatusRegisterBitAssignment.bAckError = 1;
		disable_interrupt(CAN0, CAN_SR_AERR );
		disable_interrupt(CAN1, CAN_SR_AERR );
		
	}else
	{
		CanBusStatusRegisterBitAssignment.bAckError = 0;
	}
/*---*/
	if (ul_status & CAN_SR_FERR) { //form error
		CanBusStatusRegisterBitAssignment.bFormError = 1;
		disable_interrupt(CAN0, CAN_SR_FERR );
		disable_interrupt(CAN1, CAN_SR_FERR );
		
	}
	else
	{
		CanBusStatusRegisterBitAssignment.bFormError = 0;
	}
/*---*/	
	
	if (ul_status & CAN_SR_BERR) { //bit error
		CanBusStatusRegisterBitAssignment.bBitError = 1;
		disable_interrupt(CAN0, CAN_SR_BERR );
		disable_interrupt(CAN1, CAN_SR_BERR );		
		
	}
	else
	{
			CanBusStatusRegisterBitAssignment.bBitError = 0;
	}
}




/**
* \brief Handle a mailbox interrupt event
* \param mb which mailbox generated this event
* \param ul_status The status register of the canbus hardware
*
*/
void mailbox_int_handler(Can *p_can, uint8_t mb, uint32_t ul_status) 
{
	CAN_FRAME tempFrame;
	bool caughtFrame = false;
	//CANListener *thisListener;
	if (mb > 7) mb = 7;
	if (p_can->CAN_MB[mb].CAN_MSR & CAN_MSR_MRDY) 
	{ //mailbox signals it is ready
		switch(((p_can->CAN_MB[mb].CAN_MMR >> 24) & 7)) { //what sort of mailbox is it?
			case 1: //receive
			case 2: //receive w/ overwrite
			case 4: //consumer - technically still a receive buffer
			mailbox_read(p_can, mb, &tempFrame);
			//First, try to send a callback. If no callback registered then buffer the frame.
			

					

			if( p_can == CAN0)
			{
				if (cbCANFrame[mb])
				{
					caughtFrame = true;
					(*cbCANFrame[mb])(&tempFrame);
				}
			}
			else
			{	
			
				if (cbCANFrame_1[mb])
				{
					caughtFrame = true;
					(*cbCANFrame_1[mb])(&tempFrame);
				}
			}
			/*else if (cbCANFrame[8])
			{
				caughtFrame = true;
				(*cbCANFrame[8])(&tempFrame);
			}
			else
			{
				for (int listenerPos = 0; listenerPos < SIZE_LISTENERS; listenerPos++)
				{
					thisListener = listener[listenerPos];
					if (thisListener != NULL)
					{
						if (thisListener->callbacksActive & (1 << mb))
						{
							caughtFrame = true;
							thisListener->gotFrame(&tempFrame, mb);
						}
						else if (thisListener->callbacksActive & 256)
						{
							caughtFrame = true;
							thisListener->gotFrame(&tempFrame, -1);
						}
					}
				}
			}*/
			if (!caughtFrame) //if none of the callback types caught this frame then queue it in the buffer
			{
				uint8_t temp = (rx_buffer_head + 1) % SIZE_RX_BUFFER;
				if (temp != rx_buffer_tail)
				{
					memcpy((void *)&rx_frame_buff[rx_buffer_head], &tempFrame, sizeof(CAN_FRAME));
					rx_buffer_head = temp;
				}
			}
			break;
			case 3: //transmit
			if (tx_buffer_head != tx_buffer_tail)
			{ //if there is a frame in the queue to send
				mailbox_set_id(p_can, mb, tx_frame_buff[tx_buffer_head].id, tx_frame_buff[tx_buffer_head].extended);
				mailbox_set_datalen(p_can, mb, tx_frame_buff[tx_buffer_head].length);
				mailbox_set_priority(p_can, mb, tx_frame_buff[tx_buffer_head].priority);
				for (uint8_t cnt = 0; cnt < 8; cnt++)
				mailbox_set_databyte(p_can,mb, cnt, tx_frame_buff[tx_buffer_head].data.bytes[cnt]);
				global_send_transfer_cmd(p_can,(0x1u << mb));
				tx_buffer_head = (tx_buffer_head + 1) % SIZE_TX_BUFFER;
			}
			else {
				disable_interrupt(p_can, (0x01 << mb) );
			}
			break;
			case 5: //producer - technically still a transmit buffer
			break;
		}
	}
}


/**
 * \brief Set mask for RX on the given mailbox
 *
 * \param uc_index The mailbox to use
 * \param mask The mask to set
 * \param ext Whether this should be an extended mask or not
 *
 */
void mailbox_set_accept_mask(Can *p_can, uint8_t uc_index, uint32_t mask, bool ext)
{
	if (uc_index > CANMB_NUMBER-1) uc_index = CANMB_NUMBER-1;
	if (ext) {
		p_can->CAN_MB[uc_index].CAN_MAM = mask | CAN_MAM_MIDE;
		p_can->CAN_MB[uc_index].CAN_MID |= CAN_MAM_MIDE;
	} else {
		p_can->CAN_MB[uc_index].CAN_MAM = CAN_MAM_MIDvA(mask);
		p_can->CAN_MB[uc_index].CAN_MID &= ~CAN_MAM_MIDE;
	}
}


/**
 * \brief Sets the ID portion of the given mailbox
 *
 * \param uc_index The mailbox to set (0-7)
 * \param id The ID to set (11 or 29 bit)
 * \param extended Boolean indicating if this ID should be designated as extended
 *
 */
void mailbox_set_id(Can *p_can, uint8_t uc_index, uint32_t id, bool extended) 
{
	if (uc_index > CANMB_NUMBER-1) uc_index = CANMB_NUMBER-1;
	if (extended) {
		p_can->CAN_MB[uc_index].CAN_MID = id | CAN_MID_MIDE;
	}
	else {
		p_can->CAN_MB[uc_index].CAN_MID = CAN_MID_MIDvA(id);
	}
}

/**
 * \brief Set the mode of the given mailbox
 *
 * \param uc_index Which mailbox to set (0-7)
 * \param mode The mode to set mailbox to 
 *
 * \Note Modes: 0 = Disabled, 1 = RX, 2 = RX with overwrite
 * 3 = TX, 4 = consumer 5 = producer
 */
void mailbox_set_mode(Can *p_can, uint8_t uc_index, uint8_t mode) 
{
	if (uc_index > CANMB_NUMBER-1) uc_index = CANMB_NUMBER-1;
	if (mode > 5) mode = 0; //set disabled on invalid mode
	p_can->CAN_MB[uc_index].CAN_MMR = (p_can->CAN_MB[uc_index].CAN_MMR &
		~CAN_MMR_MOT_Msk) | (mode << CAN_MMR_MOT_Pos);
}

/**
 * \brief Get current mode of given mailbox
 *
 * \param uc_index Which mailbox to retrieve mode from (0-7)
 *
 * \retval Mode of mailbox
 *
 */
uint8_t mailbox_get_mode(Can *p_can, uint8_t uc_index) 
{
	if (uc_index > CANMB_NUMBER-1) uc_index = CANMB_NUMBER-1;
	return (uint8_t)(p_can->CAN_MB[uc_index].CAN_MMR >> CAN_MMR_MOT_Pos) & 0x7;
}


/**
 * \brief Disable CAN Controller transmit repeat function.
 *
 */
void disable_tx_repeat(Can *p_can)
{
	p_can->CAN_MR |= CAN_MR_DRPT;
}

/**
 * \brief Enable CAN Controller transmit repeat function.
 *
 */
void enable_tx_repeat(Can *p_can )
{
	p_can->CAN_MR &= ~CAN_MR_DRPT;
}


/**
 * \brief Get status of the mailbox.
 *
 * \param uc_index Indicate which mailbox is to be read.
 *
 * \retval The mailbox status.
 */
uint32_t mailbox_get_status(Can *p_can , uint8_t uc_index)
{
	if (uc_index > CANMB_NUMBER-1) uc_index = CANMB_NUMBER-1;
	return (p_can->CAN_MB[uc_index].CAN_MSR);
}

/**
 * \brief Get ID currently associated with a given mailbox
 *
 * \param uc_index The mailbox to get the ID from (0-7)
 *
 * \retval The ID associated with the mailbox
 *
 */
uint32_t mailbox_get_id( Can *p_can , uint8_t uc_index)
 {
	if (uc_index > CANMB_NUMBER-1) uc_index = CANMB_NUMBER-1;
	if (p_can->CAN_MB[uc_index].CAN_MID & CAN_MID_MIDE) {
		return p_can->CAN_MB[uc_index].CAN_MID;
	}
	else {
		return (p_can->CAN_MB[uc_index].CAN_MID >> CAN_MID_MIDvA_Pos) & 0x7ffu;
	}
}


/**
 * \brief Set value of one byte of data for mailbox
 *
 * \param uc_index Which mailbox (0-7)
 * \param bytepos Which byte to set (0-7)
 * \param val The byte value to set
 *
 */
void mailbox_set_databyte(Can *p_can  , uint8_t uc_index, uint8_t bytepos, uint8_t val)
{
	uint8_t shift; //how many bits to shift
	uint32_t working;  //working copy of the relevant data int
	if (uc_index > CANMB_NUMBER-1) uc_index = CANMB_NUMBER-1;
	if (bytepos > 7) bytepos = 7;
	shift = 8 * (bytepos & 3); //how many bytes to shift up into position
	if (bytepos < 4) { //low data block
		working = p_can->CAN_MB[uc_index].CAN_MDL & ~(255 << shift); //mask out where we have to be
		working |= (val << shift);
		p_can->CAN_MB[uc_index].CAN_MDL = working;
	}
	else { //high data block
		working = p_can->CAN_MB[uc_index].CAN_MDH & ~(255 << shift); //mask out where we have to be
		working |= (val << shift);
		p_can->CAN_MB[uc_index].CAN_MDH = working;
	}
}


/**
 * \brief Retrieve a frame from the RX buffer
 *
 * \param buffer Reference to the frame structure to fill out
 *
 * \retval 0 no frames waiting to be received, 1 if a frame was returned
 */

uint32_t get_rx_buff(CAN_FRAME* buffer) 
{
	if (rx_buffer_head == rx_buffer_tail) return 0;
	
	buffer->id = rx_frame_buff[rx_buffer_tail].id;
	buffer->extended = rx_frame_buff[rx_buffer_tail].extended;
	buffer->length = rx_frame_buff[rx_buffer_tail].length;
	buffer->data.value = rx_frame_buff[rx_buffer_tail].data.value;
	rx_buffer_tail = (rx_buffer_tail + 1) % SIZE_RX_BUFFER;
	return 1;
}

/**
* \brief Find unused RX mailbox and return its number
*/
int findFreeRXMailbox(Can *p_can  ) 
{
	for (int c = 0; c < 8; c++) {
		if (mailbox_get_mode(p_can, c) == CAN_MB_RX_MODE) {
			if (mailbox_get_id(p_can,c) == 0) {
				return c;
			}
		}
	}
	return -1;
}

/*
 * Get the IER (interrupt mask) for the specified mailbox index.
 *
 * \param mailbox - the index of the mailbox to get the IER for
 * \retval the IER of the specified mailbox
 */
uint32_t getMailboxIer(int8_t mailbox) 
{
	switch (mailbox) {
	case 0:
		return CAN_IER_MB0;
	case 1:
		return CAN_IER_MB1;
	case 2:
		return CAN_IER_MB2;
	case 3:
		return CAN_IER_MB3;
	case 4:
		return CAN_IER_MB4;
	case 5:
		return CAN_IER_MB5;
	case 6:
		return CAN_IER_MB6;
	case 7:
		return CAN_IER_MB7;
	}
	return 0;
}

/**
* \brief Set up an RX mailbox (first free) for the given parameters.
*
* \param id - the post mask ID to match against
* \param mask - the mask to use for this filter
* \param extended - whether to use 29 bit filter
*
* \ret number of mailbox we just used (or -1 if there are no free boxes to use)
*/
int setRXFilter(Can *p_can  , uint32_t id, uint32_t mask, bool extended) 
{
	int c = findFreeRXMailbox(p_can);
	if (c < 0) return -1;

	mailbox_set_accept_mask(p_can, c, mask, extended);
	mailbox_set_id(p_can, c, id, extended);
	can_enable_interrupt(p_can, getMailboxIer(c));

	return c;
}

/**
* \brief Check whether there are received canbus frames in the buffer
*
* \retval true if there are frames waiting in buffer, otherwise false
*/
bool rx_available(void) 
{
	return (rx_buffer_head != rx_buffer_tail)?true:false;
}



/**
 * \brief Get the 16-bit free-running internal timer count.
 *
 *
 * \retval The internal CAN free-running timer counter.
 */
uint32_t get_internal_timer_value(Can *p_can  )
{
	return (p_can->CAN_TIM);
}

/**
 * \brief Get CAN timestamp register value.
 *
 *
 * \retval The timestamp value.
 */
uint32_t get_timestamp_value(Can *p_can  )
{
	return (p_can->CAN_TIMESTP);
}

/**
 * \brief Get CAN transmit error counter.
 *
 *
 * \retval Transmit error counter.
 */
uint8_t get_tx_error_cnt(Can *p_can  )
{
	return (uint8_t) ( p_can->CAN_ECR >> CAN_ECR_TEC_Pos);
}

/**
 * \brief Get CAN receive error counter.
 *
 *
 * \retval Receive error counter.
 */
uint8_t get_rx_error_cnt(Can *p_can )
{
	return (uint8_t) (p_can->CAN_ECR >> CAN_ECR_REC_Pos);
}

/**
 * \brief Initialize the mailbox to a default, known state.
 *
 * \param p_mailbox Pointer to a CAN mailbox instance.
 */
void mailbox_init(Can *p_can, uint8_t uc_index)
{
	if (uc_index > CANMB_NUMBER-1) uc_index = CANMB_NUMBER-1;
	p_can->CAN_MB[uc_index].CAN_MMR = 0;
	p_can->CAN_MB[uc_index].CAN_MAM = 0;
	p_can->CAN_MB[uc_index].CAN_MID = 0;
	p_can->CAN_MB[uc_index].CAN_MDL = 0;
	p_can->CAN_MB[uc_index].CAN_MDH = 0;
	p_can->CAN_MB[uc_index].CAN_MCR = 0;
}

/**
 * \brief Reset the eight mailboxes.
 *
 * \param m_pCan Pointer to a CAN peripheral instance.
 */
void reset_all_mailbox(Can *p_can)
{
	for (uint8_t i = 0; i < CANMB_NUMBER; i++) {		
		mailbox_init(p_can, i);
	}
}


/**
 * \brief Send a frame out of this canbus port
 *
 * \param txFrame The filled out frame structure to use for sending
 *
 * \note Will do one of two things - 1. Send the given frame out of the first available mailbox
 * or 2. queue the frame for sending later via interrupt. Automatically turns on TX interrupt
 * if necessary.
 * 
 * Returns whether sending/queueing succeeded. Will not smash the queue if it gets full.
 */
bool sendFrame(Can *p_can, CAN_FRAME* txFrame) 
{
	//void disable_interrupt(Can *p_can, uint32_t dw_mask);
	
	for (int i = 0; i < 8; i++) {
		if (((p_can->CAN_MB[i].CAN_MMR >> 24) & 7) == CAN_MB_TX_MODE)
		{//is this mailbox set up as a TX box?
			if (p_can->CAN_MB[i].CAN_MSR & CAN_MSR_MRDY) 
			{//is it also available (not sending anything?)
				mailbox_set_id(p_can, i, txFrame->id, txFrame->extended);
				mailbox_set_datalen(p_can,i, txFrame->length);
				mailbox_set_priority(p_can,i, txFrame->priority);
				for (uint8_t cnt = 0; cnt < 8; cnt++)
				{    
					mailbox_set_databyte(p_can, i, cnt, txFrame->data.bytes[cnt]);
				}       
				enable_interrupt(p_can, 0x01u << i); //enable the TX interrupt for this box
				global_send_transfer_cmd(p_can, (0x1u << i));
				return true; //we've sent it. mission accomplished.
			}
		}
    }
	
    //if execution got to this point then no free mailbox was found above
    //so, queue the frame if possible. But, don't increment the 
	//tail if it would smash into the head and kill the queue.
	uint8_t temp;
	temp = (tx_buffer_tail + 1) % SIZE_TX_BUFFER;
	if (temp == tx_buffer_head) return false;
    tx_frame_buff[tx_buffer_tail].id = txFrame->id;
    tx_frame_buff[tx_buffer_tail].extended = txFrame->extended;
    tx_frame_buff[tx_buffer_tail].length = txFrame->length;
    tx_frame_buff[tx_buffer_tail].data.value = txFrame->data.value;
    tx_buffer_tail = temp;
	return true;
}

/**
 * \brief Set # of data bytes for given mailbox
 *
 * \param uc_index Which mailbox? (0-7)
 * \param dlen The number of data bytes to use (0-8)
 *
 */
void mailbox_set_datalen(Can *p_can, uint8_t uc_index, uint8_t dlen)
{
	if (uc_index > CANMB_NUMBER-1) uc_index = CANMB_NUMBER-1;
	if (dlen > 8) dlen = 8;
	p_can->CAN_MB[uc_index].CAN_MCR = (p_can->CAN_MB[uc_index].CAN_MCR &
			~CAN_MCR_MDLC_Msk) | CAN_MCR_MDLC(dlen);
}

/**
 * \brief Set the transmission priority for given mailbox
 *
 * \param uc_index The mailbox to use
 * \param pri The priority to set (0-15 in descending priority)
 *
 */
void mailbox_set_priority(Can *p_can, uint8_t uc_index, uint8_t pri) 
{
	if (uc_index > CANMB_NUMBER-1) uc_index = CANMB_NUMBER-1;
	p_can->CAN_MB[uc_index].CAN_MMR = (p_can->CAN_MB[uc_index].CAN_MMR & ~CAN_MMR_PRIOR_Msk) | (pri << CAN_MMR_PRIOR_Pos);
}


/**
 * \brief Enable CAN interrupt.
 *
 * \param dw_mask Interrupt to be enabled.
 */
void enable_interrupt(Can *p_can, uint32_t dw_mask)
{
	p_can->CAN_IER = dw_mask;
}


/**
 * \brief Disable CAN interrupt.
 *
 * \param dw_mask Interrupt to be disabled.
 */
void disable_interrupt(Can *p_can, uint32_t dw_mask)
{
	p_can->CAN_IDR = dw_mask;
}

/**
 * \brief Send global transfer request.
 *
 * \param uc_mask Mask for mailboxes that are requested to transfer.
 */
void global_send_transfer_cmd(Can *p_can, uint8_t uc_mask)
{
	
		uint32_t ul_reg;

	ul_reg = p_can->CAN_TCR & ((uint32_t) ~GLOBAL_MAILBOX_MASK);
	p_can->CAN_TCR = ul_reg | uc_mask;
	
	//p_can->CAN_TCR = uc_mask & GLOBAL_MAILBOX_MASK;
}


/**
 * \brief Set up a callback function for given mailbox
 *
 * \param mailbox Which mailbox (0-7) to assign callback to.
 * \param cb A function pointer to a function with prototype "void functionname(CAN_FRAME *frame);"
 *
 */
void setCallback(int mailbox, void (*cb)(CAN_FRAME *))
{
	if ((mailbox < 0) || (mailbox > 7)) return;
	cbCANFrame[mailbox] = cb;
}


void setCallbackCan1(int mailbox, void (*cb)(CAN_FRAME *))
{
	if ((mailbox < 0) || (mailbox > 7)) return;
	cbCANFrame_1[mailbox] = cb;
}

bool canErrorDetected(void)
{
	bool bErrorDetected = false;
	if ( (CanBusStatusRegisterBitAssignment.bAckError == 1 ) ||		 
	     (CanBusStatusRegisterBitAssignment.bFormError == 1 ) ||		 
		 (CanBusStatusRegisterBitAssignment.bErrorPassive == 1 ) ||		 
		 (CanBusStatusRegisterBitAssignment.bBusOff == 1 ) ||		 
		 (CanBusStatusRegisterBitAssignment.bStuffingErrorInMailbox == 1 ) ||		 
		 (CanBusStatusRegisterBitAssignment.bCrcErrorInMailbox == 1 ) ||		 
		 (CanBusStatusRegisterBitAssignment.bBitError == 1 ) 	)	 
		 {
			bErrorDetected = true ;		 
		 }
	
	
	return bErrorDetected;
}

CanBusStatusRegisterBitAssignment_t getCANStatus(void)
{
	return CanBusStatusRegisterBitAssignment;
}

void resetCANStatus(void)
{
	CanBusStatusRegisterBitAssignment.bAckError = 0;
	CanBusStatusRegisterBitAssignment.bBitError = 0;
	CanBusStatusRegisterBitAssignment.bBitErrorActive = 0;
	CanBusStatusRegisterBitAssignment.bBusOff = 0;
	CanBusStatusRegisterBitAssignment.bControllerInSleepMode = 0;
	CanBusStatusRegisterBitAssignment.bControllerWokeUp = 0;
	CanBusStatusRegisterBitAssignment.bCrcErrorInMailbox = 0;
	CanBusStatusRegisterBitAssignment.bErrorPassive = 0;
	CanBusStatusRegisterBitAssignment.bFormError = 0;
	CanBusStatusRegisterBitAssignment.bStuffingErrorInMailbox = 0;
	CanBusStatusRegisterBitAssignment.bTimerOverflow = 0;
	CanBusStatusRegisterBitAssignment.bTimestamp = 0;
	CanBusStatusRegisterBitAssignment.bwarningLimit = 0;
	
}
/** @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/** @endcond */
