/**
  ******************************************************************************
  * @file    rf_driver_ll_radio_2g4.h
  * @author  RF Application Team
  * @brief   This file contains all the functions prototypes for the radio firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
  
  /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef RF_DRIVER_LL_RADIO_H
#define RF_DRIVER_LL_RADIO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "bluenrg_lpx.h"
#include "system_BlueNRG_LP.h"

/** @addtogroup RF_DRIVER_LL_Driver
  * @{
  */

/** @addtogroup RADIO
  * @{
  */


/** @defgroup RADIO_Exported_Macros RADIO Exported Macros
* @{
  */

#define BLUEGLOB_BASE               (_MEMORY_RAM_BEGIN_ + 0xC0U)
#define blueglob                    ((GLOBALSTATMACH_TypeDef*) BLUEGLOB_BASE)
#define blueglobWord                ((GLOBALSTATMACH_WORD_TypeDef*) BLUEGLOB_BASE)
#define bluedata                    ((STATMACH_TypeDef*) (BLUEGLOB_BASE+sizeof(GLOBALSTATMACH_TypeDef)))
#define bluedataWord                ((STATMACH_WORD_TypeDef*) (BLUEGLOB_BASE+sizeof(GLOBALSTATMACH_WORD_TypeDef)))
#define BlueTransStruct             TXRXPACK_TypeDef

#define BLUE_DATA_PTR_CAST(PTR) (((uint32_t)(uintptr_t)(PTR)))
#define BLUE_STRUCT_PTR_CAST(PTR) (((uint32_t)(uintptr_t)(PTR)))

/**
  * @}
  */


/** @defgroup RADIO_Exported_Constants RADIO Exported Constants
* @{
  */

    
/* Hot table size */
#define HOT_TABLE_SIZE 31

/* RRM register address for the hot table */
#define RRM_CBIAS1_ANA_ENG      (0x5E)
#define RRM_CBIAS0_ANA_ENG      (0x5D)
#define RRM_RXADC_ANA_USR       (0x52)
#define RRM_AFC1_DIG_ENG        (0x12)
#define RRM_CR0_DIG_ENG         (0x15)
#define RRM_CR0_LR              (0x1A)
#define RRM_LR_RSSI_THR_DIG_ENG (0x22)
#define RRM_LR_PD_THR_DIG_ENG   (0x21)
#define RRM_LR_AAC_THR_DIG_ENG  (0x23)
#define RRM_VIT_CONF_DIG_ENG    (0x1B)
  
   
   
/** @defgroup GlobalStatmach_Masks GlobalStatmach Masks
  * @{
  */
#define GLOBAL_WORD0_RADIOCONFIGPTR_Pos                                    (0UL)
#define GLOBAL_WORD0_RADIOCONFIGPTR_Msk                                    (0xffffffffUL)
#define GLOBAL_WORD0_RADIOCONFIGPTR                                        GLOBAL_WORD0_RADIOCONFIGPTR_Msk
#define GLOBAL_WORD1_CURSTMACHNUM_Pos                                      (0UL)
#define GLOBAL_WORD1_CURSTMACHNUM_Msk                                      (0x7fUL)
#define GLOBAL_WORD1_CURSTMACHNUM                                          GLOBAL_WORD1_CURSTMACHNUM_Msk
#define GLOBAL_WORD1_ACTIVE_Pos                                            (7UL)
#define GLOBAL_WORD1_ACTIVE_Msk                                            (0x80UL)
#define GLOBAL_WORD1_ACTIVE                                                GLOBAL_WORD1_ACTIVE_Msk
#define GLOBAL_WORD1_WAKEUPINITDELAY_Pos                                   (8UL)                              
#define GLOBAL_WORD1_WAKEUPINITDELAY_Msk                                   (0xff00UL)                              
#define GLOBAL_WORD1_WAKEUPINITDELAY                                       GLOBAL_WORD1_WAKEUPINITDELAY_Msk
#define GLOBAL_WORD1_TIMER12INITDELAYCAL_Pos                               (16UL)                            
#define GLOBAL_WORD1_TIMER12INITDELAYCAL_Msk                               (0xff0000UL)                            
#define GLOBAL_WORD1_TIMER12INITDELAYCAL                                   GLOBAL_WORD1_TIMER12INITDELAYCAL_Msk
#define GLOBAL_WORD1_TIMER2INITDELAYNOCAL_Pos                              (24UL)
#define GLOBAL_WORD1_TIMER2INITDELAYNOCAL_Msk                              (0xff000000UL)
#define GLOBAL_WORD1_TIMER2INITDELAYNOCAL                                  GLOBAL_WORD1_TIMER2INITDELAYNOCAL_Msk 
#define GLOBAL_WORD2_TRANSMITCALDELAYCHK_Pos                               (0UL)                               
#define GLOBAL_WORD2_TRANSMITCALDELAYCHK_Msk                               (0xffUL)                               
#define GLOBAL_WORD2_TRANSMITCALDELAYCHK                                   GLOBAL_WORD2_TRANSMITCALDELAYCHK_Msk
#define GLOBAL_WORD2_TRANSMITNOCALDELAYCHK_Pos                             (8UL)
#define GLOBAL_WORD2_TRANSMITNOCALDELAYCHK_Msk                             (0xff00UL)                           
#define GLOBAL_WORD2_TRANSMITNOCALDELAYCHK                                 GLOBAL_WORD2_TRANSMITNOCALDELAYCHK_Msk
#define GLOBAL_WORD2_RECEIVECALDELAYCHK_Pos                                (16UL)                           
#define GLOBAL_WORD2_RECEIVECALDELAYCHK_Msk                                (0xff0000UL)                           
#define GLOBAL_WORD2_RECEIVECALDELAYCHK                                    GLOBAL_WORD2_RECEIVECALDELAYCHK_Msk
#define GLOBAL_WORD2_RECEIVENOCALDELAYCHK_Pos                              (24UL)
#define GLOBAL_WORD2_RECEIVENOCALDELAYCHK_Msk                              (0xff000000UL)
#define GLOBAL_WORD2_RECEIVENOCALDELAYCHK                                  GLOBAL_WORD2_RECEIVENOCALDELAYCHK_Msk
#define GLOBAL_WORD3_CONFIGENDDURATION_Pos                                 (0UL)   
#define GLOBAL_WORD3_CONFIGENDDURATION_Msk                                 (0xffUL)
#define GLOBAL_WORD3_CONFIGENDDURATION                                     GLOBAL_WORD3_CONFIGENDDURATION_Msk
#define GLOBAL_WORD3_TXDATAREADYCHECK_Pos                                  (8UL)
#define GLOBAL_WORD3_TXDATAREADYCHECK_Msk                                  (0xff00UL)
#define GLOBAL_WORD3_TXDATAREADYCHECK                                      GLOBAL_WORD3_TXDATAREADYCHECK_Msk
#define GLOBAL_WORD3_TXDELAYSTART_Pos                                      (16UL)
#define GLOBAL_WORD3_TXDELAYSTART_Msk                                      (0xff0000UL)
#define GLOBAL_WORD3_TXDELAYSTART                                          GLOBAL_WORD3_TXDELAYSTART_Msk
#define GLOBAL_WORD3_TXDELAYEND_Pos                                        (24UL)
#define GLOBAL_WORD3_TXDELAYEND_Msk                                        (0x3f000000UL)
#define GLOBAL_WORD3_TXDELAYEND                                            GLOBAL_WORD3_TXDELAYEND_Msk
#define GLOBAL_WORD3_TIMECAPTURESEL_Pos                                    (30UL)
#define GLOBAL_WORD3_TIMECAPTURESEL_Msk                                    (0x40000000UL)
#define GLOBAL_WORD3_TIMECAPTURESEL                                        GLOBAL_WORD3_TIMECAPTURESEL_Msk
#define GLOBAL_WORD3_TIMECAPTURE_Pos                                       (31UL)
#define GLOBAL_WORD3_TIMECAPTURE_Msk                                       (0x80000000UL)
#define GLOBAL_WORD3_TIMECAPTURE                                           GLOBAL_WORD3_TIMECAPTURE_Msk  
#define GLOBAL_WORD4_TXREADYTIMEOUT_Pos                                    (0UL)   
#define GLOBAL_WORD4_TXREADYTIMEOUT_Msk                                    (0xffUL)
#define GLOBAL_WORD4_TXREADYTIMEOUT                                        GLOBAL_WORD4_TXREADYTIMEOUT_Msk
#define GLOBAL_WORD4_RCVTIMEOUT_Pos                                        (8UL)
#define GLOBAL_WORD4_RCVTIMEOUT_Msk                                        (0xfffff00UL)
#define GLOBAL_WORD4_RCVTIMEOUT                                            GLOBAL_WORD4_RCVTIMEOUT_Msk
#define GLOBAL_WORD5_CHKFLAGAUTOCLEARENA_Pos                               (2UL)
#define GLOBAL_WORD5_CHKFLAGAUTOCLEARENA_Msk                               (0x4UL)
#define GLOBAL_WORD5_CHKFLAGAUTOCLEARENA                                   GLOBAL_WORD5_CHKFLAGAUTOCLEARENA_Msk
#define GLOBAL_WORD5_INTNOACTIVELERROR_Pos                                 (23UL)
#define GLOBAL_WORD5_INTNOACTIVELERROR_Msk                                 (0x800000UL)
#define GLOBAL_WORD5_INTNOACTIVELERROR                                     GLOBAL_WORD5_INTNOACTIVELERROR_Msk
#define GLOBAL_WORD5_INTACTIVE2ERR_Pos                                     (30UL)
#define GLOBAL_WORD5_INTACTIVE2ERR_Msk                                     (0x40000000UL)
#define GLOBAL_WORD5_INTACTIVE2ERR                                         GLOBAL_WORD5_INTACTIVE2ERR_Msk

#define GLOBAL_BYTE4_CURSTMACHNUM_Msk                                      (0x7F)
#define GLOBAL_BYTE4_ACTIVE_Msk                                            (0x80)

#define GLOBAL_BYTE15_TXDELAYEND_Msk                                       (0x3F)
#define GLOBAL_BYTE15_TIMECAPTURESEL_Msk                                   (0x40)
#define GLOBAL_BYTE15_TIMECAPTURE_Msk                                      (0x80)

#define GLOBAL_BYTE20_AUTOTXRXSKIPEN_Msk                                   (0x01)
#define GLOBAL_BYTE20_CHKFLAGAUTOCLEARENA_Msk                              (0x04)

#define GLOBAL_BYTE21_INTSEQERROR_Msk                                      (0x3F)

#define GLOBAL_BYTE22_INTADDPOINTERROR_Msk                                 (0x10)
#define GLOBAL_BYTE22_INTALLTABLEREADYERROR_Msk                            (0x20)
#define GLOBAL_BYTE22_INTTXDATAREADYERROR_Msk                              (0x40)
#define GLOBAL_BYTE22_INTNOACTIVELERROR_Msk                                (0x80)

#define GLOBAL_BYTE23_INTRCVLENGTHERROR_Msk                                (0x02)
#define GLOBAL_BYTE23_INTSEMATIMEOUTERROR_Msk                              (0x04)
#define GLOBAL_BYTE23_INTSEMAWASPREEMPT_Msk                                (0x08)
#define GLOBAL_BYTE23_INTSEQDONE_Msk                                       (0x10)
#define GLOBAL_BYTE23_INTTXRXSKIP_Msk                                      (0x20)
#define GLOBAL_BYTE23_INTACTIVE2ERR_Msk                                    (0x40)
#define GLOBAL_BYTE23_INTCONFIGERROR_Msk                                   (0x80)


/**
* @}
*/


/** @defgroup Statmach_Masks Statmach Masks
* @{
  */
#define STATEMACH_WORD0_UCHAN_Pos                                          (0UL)
#define STATEMACH_WORD0_UCHAN_Msk                                          (0x3fUL)
#define STATEMACH_WORD0_UCHAN                                              STATEMACH_WORD0_UCHAN_Msk
#define STATEMACH_WORD0_RADIOCOMLISTENA_Pos                                (6UL)
#define STATEMACH_WORD0_RADIOCOMLISTENA_Msk                                (0x40UL)
#define STATEMACH_WORD0_RADIOCOMLISTENA                                    STATEMACH_WORD0_RADIOCOMLISTENA_Msk
#define STATEMACH_WORD0_TXMODE_Pos                                         (7UL)
#define STATEMACH_WORD0_TXMODE_Msk                                         (0x80UL)
#define STATEMACH_WORD0_TXMODE                                             STATEMACH_WORD0_TXMODE_Msk
#define STATEMACH_WORD0_REMAP_CHAN_Pos                                     (8UL)
#define STATEMACH_WORD0_REMAP_CHAN_Msk                                     (0x3f00UL)
#define STATEMACH_WORD0_REMAP_CHAN                                         STATEMACH_WORD0_REMAP_CHAN_Msk
#define STATEMACH_WORD0_SN_Pos                                             (14UL)
#define STATEMACH_WORD0_SN_Msk                                             (0x4000UL)
#define STATEMACH_WORD0_SN                                                 STATEMACH_WORD0_SN_Msk
#define STATEMACH_WORD0_NESN_Pos                                           (15UL)
#define STATEMACH_WORD0_NESN_Msk                                           (0x8000UL)
#define STATEMACH_WORD0_NESN                                               STATEMACH_WORD0_NESN_Msk
#define STATEMACH_WORD0_ENCRYPTON_Pos                                      (21UL)
#define STATEMACH_WORD0_ENCRYPTON_Msk                                      (0x200000UL)
#define STATEMACH_WORD0_ENCRYPTON                                          STATEMACH_WORD0_ENCRYPTON_Msk
#define STATEMACH_WORD0_TXPHY_Pos                                          (24UL)
#define STATEMACH_WORD0_TXPHY_Msk                                          (0x7000000UL)
#define STATEMACH_WORD0_TXPHY                                              STATEMACH_WORD0_TXPHY_Msk
#define STATEMACH_WORD0_RXPHY_Pos                                          (28UL)
#define STATEMACH_WORD0_RXPHY_Msk                                          (0x70000000UL)
#define STATEMACH_WORD0_RXPHY                                              STATEMACH_WORD0_RXPHY_Msk
#define STATEMACH_WORD1_TXPOINT_Pos                                        (0UL)
#define STATEMACH_WORD1_TXPOINT_Msk                                        (0xffffffffUL)
#define STATEMACH_WORD1_TXPOINT                                            STATEMACH_WORD1_TXPOINT_Msk
#define STATEMACH_WORD2_RCVPOINT_Pos                                       (0UL)
#define STATEMACH_WORD2_RCVPOINT_Msk                                       (0xffffffffUL)
#define STATEMACH_WORD2_RCVPOINT                                           STATEMACH_WORD2_RCVPOINT_Msk
#define STATEMACH_WORD3_TXPOINTPREV_Pos                                    (0UL)
#define STATEMACH_WORD3_TXPOINTPREV_Msk                                    (0xffffffffUL)
#define STATEMACH_WORD3_TXPOINTPREV                                        STATEMACH_WORD3_TXPOINTPREV_Msk
#define STATEMACH_WORD4_RCVPOINTPREV_Pos                                   (0UL)
#define STATEMACH_WORD4_RCVPOINTPREV_Msk                                   (0xffffffffUL)
#define STATEMACH_WORD4_RCVPOINTPREV                                       STATEMACH_WORD4_RCVPOINTPREV_Msk
#define STATEMACH_WORD6_PCNTTX_31_0_Pos                                    (0UL)
#define STATEMACH_WORD6_PCNTTX_31_0_Msk                                    (0xffffffffUL)
#define STATEMACH_WORD6_PCNTTX_31_0                                        STATEMACH_WORD6_PCNTTX_31_0_Msk 
#define STATEMACH_WORD7_PCNTTX_39_32_Pos                                   (0UL)
#define STATEMACH_WORD7_PCNTTX_39_32_Msk                                   (0xffUL)
#define STATEMACH_WORD7_PCNTTX_39_32                                       STATEMACH_WORD7_PCNTTX_39_32_Msk
#define STATEMACH_WORD7_PCNTRCV_23_0_Pos                                   (8UL)
#define STATEMACH_WORD7_PCNTRCV_23_0_Msk                                   (0xffffff00UL)
#define STATEMACH_WORD7_PCNTRCV_23_0                                       STATEMACH_WORD7_PCNTRCV_23_0_Msk
#define STATEMACH_WORD8_PCNTRCV_39_24_Pos                                  (0UL)
#define STATEMACH_WORD8_PCNTRCV_39_24_Msk                                  (0xffffUL)
#define STATEMACH_WORD8_PCNTRCV_39_24                                      STATEMACH_WORD8_PCNTRCV_39_24_Msk
#define STATEMACH_WORD8_INTENCERROR_Pos                                    (29UL)
#define STATEMACH_WORD8_INTENCERROR_Msk                                    (0x20000000UL)
#define STATEMACH_WORD8_INTENCERROR                                        STATEMACH_WORD8_INTENCERROR_Msk
#define STATEMACH_WORD9_ACCADDR_Pos                                        (0UL)
#define STATEMACH_WORD9_ACCADDR_Msk                                        (0xffffffffUL)
#define STATEMACH_WORD9_ACCADDR                                            STATEMACH_WORD9_ACCADDR_Msk
#define STATEMACH_WORDA_CRCINIT_Pos                                        (0UL)
#define STATEMACH_WORDA_CRCINIT_Msk                                        (0xffffffUL)
#define STATEMACH_WORDA_CRCINIT                                            STATEMACH_WORDA_CRCINIT_Msk
#define STATEMACH_WORDA_MAXRECEIVEDLENGTH_Pos                              (24UL)
#define STATEMACH_WORDA_MAXRECEIVEDLENGTH_Msk                              (0xff000000UL)
#define STATEMACH_WORDA_MAXRECEIVEDLENGTH                                  STATEMACH_WORDA_MAXRECEIVEDLENGTH_Msk
#define STATEMACH_WORDB_PAPOWER_Pos                                        (0UL)
#define STATEMACH_WORDB_PAPOWER_Msk                                        (0x1fUL)
#define STATEMACH_WORDB_PAPOWER                                            STATEMACH_WORDB_PAPOWER_Msk
#define STATEMACH_WORDB_HOPINCR_Pos                                        (8UL)
#define STATEMACH_WORDB_HOPINCR_Msk                                        (0x3f00UL)
#define STATEMACH_WORDB_HOPINCR                                            STATEMACH_WORDB_HOPINCR_Msk
#define STATEMACH_WORDB_USEDCHANNELFLAGS_15_0_Pos                          (16UL)
#define STATEMACH_WORDB_USEDCHANNELFLAGS_15_0_Msk                          (0xffff0000UL)
#define STATEMACH_WORDB_USEDCHANNELFLAGS_15_0                              STATEMACH_WORDB_USEDCHANNELFLAGS_15_0_Msk
#define STATEMACH_WORDC_USEDCHANNELFLAGS_36_16_Pos                         (0UL)
#define STATEMACH_WORDC_USEDCHANNELFLAGS_36_16_Msk                         (0x3fffffUL)
#define STATEMACH_WORDC_USEDCHANNELFLAGS_36_16                             STATEMACH_WORDC_USEDCHANNELFLAGS_36_16_Msk
#define STATEMACH_WORDE_ENCRYPTIV_0_31_Pos                                 (0UL)
#define STATEMACH_WORDE_ENCRYPTIV_0_31_Msk                                 (0xffffffffUL)
#define STATEMACH_WORDE_ENCRYPTIV_0_31                                     STATEMACH_WORDE_ENCRYPTIV_0_31_Msk
   
   
#define STATEMACH_BYTE0_UCHAN_Msk                                          (0x3F)
#define STATEMACH_BYTE0_RADIOCOMLISTENA_Msk                                (0x40)
#define STATEMACH_BYTE0_TXMODE_Msk                                         (0x80)

#define STATEMACH_BYTE1_REMAP_CHAN_Msk                                     (0x3F)
#define STATEMACH_BYTE1_SN_Msk                                             (0x40)
#define STATEMACH_BYTE1_NESN_Msk                                           (0x80)

#define STATEMACH_BYTE2_SEMAPRIO_Msk                                       (0x07)
#define STATEMACH_BYTE2_SEMAPREEMPT_Msk                                    (0x08)
#define STATEMACH_BYTE2_BUFFER_FULL_Msk                                    (0x10)
#define STATEMACH_BYTE2_ENCRYPTON_Msk                                      (0x20)
#define STATEMACH_BYTE2_TXENC_Msk                                          (0x40)
#define STATEMACH_BYTE2_RCVENC_Msk                                         (0x80)

#define STATEMACH_BYTE3_TXPHY_Msk                                          (0x07)


#define STATEMACH_BYTE3_RXPHY_Msk                                          (0x70)

#define STATEMACH_BYTE34_PREAMBLEREP_Msk                                   (0x0F)
#define STATEMACH_BYTE34_ENAPREAMBLEREP_Msk                                (0x10)
#define STATEMACH_BYTE34_DISABLECRC_Msk                                    (0x20)
#define STATEMACH_BYTE34_MSBFIRST_Msk                                      (0x40)
#define STATEMACH_BYTE34_RXMICDBG_Msk                                      (0x80)

#define STATEMACH_BYTE35_INTTXERROR_Msk                                    (0x1F)
#define STATEMACH_BYTE35_INTENCERROR_Msk                                   (0x20)
#define STATEMACH_BYTE35_INTRXOVERFLOWERROR_Msk                            (0x40)
#define STATEMACH_BYTE35_RXDEBUGCRC_Msk                                    (0x80)


/**
* @}
*/

/** @defgroup TxRxPack_Masks TxRxPack Masks
* @{
  */

#define TXRXPACK_WORD0_NEXTPTR_Pos                                         (0UL)
#define TXRXPACK_WORD0_NEXTPTR_Msk                                         (0xffffffffUL)
#define TXRXPACK_WORD0_NEXTPTR                                             TXRXPACK_WORD0_NEXTPTR_Msk   
#define TXRXPACK_WORD1_CALREQ_Pos                                          (0UL)
#define TXRXPACK_WORD1_CALREQ_Msk                                          (0x1UL)
#define TXRXPACK_WORD1_CALREQ                                              TXRXPACK_WORD1_CALREQ_Msk
#define TXRXPACK_WORD1_KEEPSEMAREQ_Pos                                     (2UL)
#define TXRXPACK_WORD1_KEEPSEMAREQ_Msk                                     (0x4UL)
#define TXRXPACK_WORD1_KEEPSEMAREQ                                         TXRXPACK_WORD1_KEEPSEMAREQ_Msk
#define TXRXPACK_WORD1_SUPPENA_Pos                                        (3UL)
#define TXRXPACK_WORD1_SUPPENA_Msk                                        (0x8UL)
#define TXRXPACK_WORD1_SUPPENA                                            TXRXPACK_WORD1_SUPPENA_Msk
#define TXRXPACK_WORD1_CRCINITSEL_Pos                                      (4UL)
#define TXRXPACK_WORD1_CRCINITSEL_Msk                                      (0x10UL)
#define TXRXPACK_WORD1_CRCINITSEL                                          TXRXPACK_WORD1_CRCINITSEL_Msk
#define TXRXPACK_WORD1_ADVERTISE_Pos                                       (5UL)
#define TXRXPACK_WORD1_ADVERTISE_Msk                                       (0x20UL)
#define TXRXPACK_WORD1_ADVERTISE                                           TXRXPACK_WORD1_ADVERTISE_Msk
#define TXRXPACK_WORD1_SN_EN_Pos                                           (6UL)
#define TXRXPACK_WORD1_SN_EN_Msk                                           (0x40UL)
#define TXRXPACK_WORD1_SN_EN                                               TXRXPACK_WORD1_SN_EN_Msk
#define TXRXPACK_WORD1_INCCHAN_Pos                                         (7UL)
#define TXRXPACK_WORD1_INCCHAN_Msk                                         (0x80UL)
#define TXRXPACK_WORD1_INCCHAN                                             TXRXPACK_WORD1_INCCHAN_Msk
#define TXRXPACK_WORD1_NEXTTXMODE_Pos                                      (8UL)
#define TXRXPACK_WORD1_NEXTTXMODE_Msk                                      (0x100UL)
#define TXRXPACK_WORD1_NEXTTXMODE                                          TXRXPACK_WORD1_NEXTTXMODE_Msk
#define TXRXPACK_WORD1_ALLTABLEREADY_Pos                                   (9UL)
#define TXRXPACK_WORD1_ALLTABLEREADY_Msk                                   (0x200UL)
#define TXRXPACK_WORD1_ALLTABLEREADY                                       TXRXPACK_WORD1_ALLTABLEREADY_Msk
#define TXRXPACK_WORD1_TXDATAREADY_Pos                                     (10UL)
#define TXRXPACK_WORD1_TXDATAREADY_Msk                                     (0x400UL)
#define TXRXPACK_WORD1_TXDATAREADY                                         TXRXPACK_WORD1_TXDATAREADY_Msk
#define TXRXPACK_WORD1_DISABLEWHITENING_Pos                                (12UL)
#define TXRXPACK_WORD1_DISABLEWHITENING_Msk                                (0x1000UL)
#define TXRXPACK_WORD1_DISABLEWHITENING                                    TXRXPACK_WORD1_DISABLEWHITENING_Msk
#define TXRXPACK_WORD2_DATAPTR_Pos                                         (0UL)
#define TXRXPACK_WORD2_DATAPTR_Msk                                         (0xffffffffUL)
#define TXRXPACK_WORD2_DATAPTR                                             TXRXPACK_WORD2_DATAPTR_Msk
#define TXRXPACK_WORD3_TIMER2_Pos                                          (0UL)
#define TXRXPACK_WORD3_TIMER2_Msk                                          (0xfffffUL)
#define TXRXPACK_WORD3_TIMER2                                              TXRXPACK_WORD3_TIMER2_Msk
#define TXRXPACK_WORD3_TIMER2EN_Pos                                        (20UL)
#define TXRXPACK_WORD3_TIMER2EN_Msk                                        (0x100000UL)
#define TXRXPACK_WORD3_TIMER2EN                                            TXRXPACK_WORD3_TIMER2EN_Msk
#define TXRXPACK_WORD3_TRIGRCV_Pos                                         (22UL)
#define TXRXPACK_WORD3_TRIGRCV_Msk                                         (0x400000UL)
#define TXRXPACK_WORD3_TRIGRCV                                             TXRXPACK_WORD3_TRIGRCV_Msk
#define TXRXPACK_WORD3_TRIGDONE_Pos                                        (23UL)
#define TXRXPACK_WORD3_TRIGDONE_Msk                                        (0x800000UL)
#define TXRXPACK_WORD3_TRIGDONE                                            TXRXPACK_WORD3_TRIGDONE_Msk
#define TXRXPACK_WORD3_INTTXOK_Pos                                         (24UL)
#define TXRXPACK_WORD3_INTTXOK_Msk                                         (0x1000000UL)
#define TXRXPACK_WORD3_INTTXOK                                             TXRXPACK_WORD3_INTTXOK_Msk
#define TXRXPACK_WORD3_INTDONE_Pos                                         (25UL)
#define TXRXPACK_WORD3_INTDONE_Msk                                         (0x2000000UL)
#define TXRXPACK_WORD3_INTDONE                                             TXRXPACK_WORD3_INTDONE_Msk
#define TXRXPACK_WORD3_INTRCVTIMEOUT_Pos                                   (26UL)
#define TXRXPACK_WORD3_INTRCVTIMEOUT_Msk                                   (0x4000000UL)
#define TXRXPACK_WORD3_INTRCVTIMEOUT                                       TXRXPACK_WORD3_INTRCVTIMEOUT_Msk
#define TXRXPACK_WORD3_INTTIMECAPTURE_Pos                                  (29UL)
#define TXRXPACK_WORD3_INTTIMECAPTURE_Msk                                  (0x20000000UL)
#define TXRXPACK_WORD3_INTTIMECAPTURE                                      TXRXPACK_WORD3_INTTIMECAPTURE_Msk
#define TXRXPACK_WORD3_INTRCVCRCERR_Pos                                    (30UL)
#define TXRXPACK_WORD3_INTRCVCRCERR_Msk                                    (0x40000000UL)
#define TXRXPACK_WORD3_INTRCVCRCERR                                        TXRXPACK_WORD3_INTRCVCRCERR_Msk
#define TXRXPACK_WORD3_INTRCVOK_Pos                                        (31UL)
#define TXRXPACK_WORD3_INTRCVOK_Msk                                        (0x80000000UL)
#define TXRXPACK_WORD3_INTRCVOK                                            TXRXPACK_WORD3_INTRCVOK_Msk

#define TXRXPACK_BYTE4_CALREQ_Msk                                          (0x01)
#define TXRXPACK_BYTE4_CHANALGO2SEL_Msk                                    (0x02)
#define TXRXPACK_BYTE4_KEEPSEMAREQ_Msk                                     (0x04)
#define TXRXPACK_BYTE4_SUPPENA_Msk                                         (0x08)
#define TXRXPACK_BYTE4_CRCINITSEL_Msk                                      (0x10)
#define TXRXPACK_BYTE4_ADVERTISE_Msk                                       (0x20)
#define TXRXPACK_BYTE4_SN_EN_Msk                                           (0x40)
#define TXRXPACK_BYTE4_INCCHAN_Msk                                         (0x80)

#define TXRXPACK_BYTE5_NEXTTXMODE_Msk                                      (0x01)
#define TXRXPACK_BYTE5_ALLTABLEREADY_Msk                                   (0x02)
#define TXRXPACK_BYTE5_TXDATAREADY_Msk                                     (0x04)
#define TXRXPACK_BYTE5_DATAREADYSEL_Msk                                    (0x08)
#define TXRXPACK_BYTE5_DISABLEWHITENING_Msk                                (0x10)
#define TXRXPACK_BYTE5_TESTPACKET_Msk                                      (0x20)


#define TXRXPACK_BYTE14_TIMER2_19_16_Msk                                   (0x0F)
#define TXRXPACK_BYTE14_TIMER2EN_Msk                                       (0x10)
#define TXRXPACK_BYTE14_TRIGRCV_Msk                                        (0x40)
#define TXRXPACK_BYTE14_TRIGDONE_Msk                                       (0x80)

#define TXRXPACK_BYTE15_INTTXOK_Msk                                        (0x01)
#define TXRXPACK_BYTE15_INTDONE_Msk                                        (0x02)
#define TXRXPACK_BYTE15_INTRCVTIMEOUT_Msk                                  (0x04)
#define TXRXPACK_BYTE15_INTRCVNOMD_Msk                                     (0x08)
#define TXRXPACK_BYTE15_INTRCVCMD_Msk                                      (0x10)
#define TXRXPACK_BYTE15_INTRCVTRIG_Msk                                     (0x20)
#define TXRXPACK_BYTE15_INTRCVCRCERR_Msk                                   (0x40)
#define TXRXPACK_BYTE15_INTRCVOK_Msk                                       (0x80)
#define TXRXPACK_BYTE15_INT_EN_Msk                                         (0xFF)

/**
* @}
*/   


#define MAX_LL_PACKET_LENGTH    255 /* Maximum Link Layer Packet Length (user_payload + MIC)*/
#define MAX_OUTPUT_RF_POWER     0x1F
    
#define HEADER_LENGTH           2
#define MAX_PACKET_LENGTH       (MAX_LL_PACKET_LENGTH+HEADER_LENGTH)
#define MIC_FIELD_LENGTH        4
#define SUCCESS_0               0
#define INVALID_PARAMETER_C0    0xC0
#define RADIO_BUSY_C4           0xC4
#define NULL_0                  0
#define BLUE_IDLE_0             0  
#define TIMESTAMP_POSITION_ACCESSADDRESS    0x40 
#define TIMESTAMP_POSITION_LASTBIT          0x80   
#define BACK_TO_BACK_TIME       150 /* BLE IFS equal to 150 micro second */

#define STATEMACHINE_COUNT   8

/** @defgroup PHY PHY selection
* @{
*/

#define PHY_1M 0x00
#define PHY_2M 0x01
#define PHY_CODED_S_8 0x04
#define PHY_CODED_S_2 0x06

/**
  * @}
  */


/** @defgroup ActionTag_BitMask ActionTag BitMask
* @{
*/

/* This bit activates the radio frequency PLL calibration.
 * 0: Radio frequency calibration disabled.
 * 1: Radio frequency calibration enabled.
*/
#define PLL_TRIG                    0x01
    
/* This bit determines if the action is an RX action or a TX action.
 * 1: TX
 * 0: RX
*/
#define TXRX                        0x02
    
/* The bit determines if the action (RX or TX) is going to be executed based on the back-to-back time or based on the WakeupTime.
 * 0: Based on the back-to-back time (default 150 �s).
 * 1: Based on the WakeupTime.
*/
#define TIMER_WAKEUP                0x04

/* The bit determines if whitening is disabled or not.
 *0: The whitening is enabled in the transmit block and in the receive block.
 *1: The whitening is disabled in the transmit block and in the receive block.
*/
#define WHITENING_DISABLE           0x10
    
/* It determines if the WakeupTime field of the ActionPacket is considered as absolute time or relative time to the current.
 * 0: Absolute
 * 1: Relative
*/
#define RELATIVE                    0x20
    
/* This bit sets where the position of time stamp is taken, the beginning of the packet or the end of it. RX only.
 * 0: End of the Packet
 * 1: Beginning of the packet
 */
#define TIMESTAMP_POSITION          0x40

/* This bit activates automatic channel increment. The API RADIO_SetChannel sets the value of the increment.
 * 0: No increment
 * 1: Automatic increment
*/
#define INC_CHAN                    0x80


/**
  * @}
  */

/**
  * @}
  */

/** @defgroup RADIO_Exported_Types RADIO Exported Types
* @{
*/

/**
  * @brief Radio Global State Machine Word oriented description
  */

typedef struct {
    volatile uint32_t  WORD0;
    volatile uint32_t  WORD1;
    volatile uint32_t  WORD2;
    volatile uint32_t  WORD3;
    volatile uint32_t  WORD4;
    volatile uint32_t  WORD5;
    volatile uint32_t  WORD6;
} GLOBALSTATMACH_WORD_TypeDef;



/**
  * @brief Radio Link State Machine Word oriented description
  */
  typedef struct {
    volatile uint32_t  WORD0;
    volatile uint32_t  WORD1;
    volatile uint32_t  WORD2;
    volatile uint32_t  WORD3;
    volatile uint32_t  WORD4;
    volatile uint32_t  WORD5;
    volatile uint32_t  WORD6;
    volatile uint32_t  WORD7;
    volatile uint32_t  WORD8;
    volatile uint32_t  WORD9;
    volatile uint32_t  WORDA;
    volatile uint32_t  WORDB;
    volatile uint32_t  WORDC;
    volatile uint32_t  WORDD;
    volatile uint32_t  WORDE;
    volatile uint32_t  WORDF;
    volatile uint32_t WORD10;
    volatile uint32_t WORD11;
    volatile uint32_t WORD12;
    volatile uint32_t WORD13;
} STATMACH_WORD_TypeDef;



/**
  * @brief Radio TxRxPack Word oriented description
  */
typedef struct {
    volatile uint32_t WORD0;
    volatile uint32_t WORD1;
    volatile uint32_t WORD2;
    volatile uint32_t WORD3;
    volatile uint32_t WORD4;
} TXRXPACK_WORD_TypeDef;   
   
   
/**
  * @brief Radio Global State Machine description
  */

typedef struct {
    volatile uint32_t RADIOCONFIGPTR;
    volatile uint8_t BYTE4;
    volatile uint8_t WAKEUPINITDELAY;
    volatile uint8_t TIMER12INITDELAYCAL;
    volatile uint8_t TIMER2INITDELAYNOCAL;
    volatile uint8_t TRANSMITCALDELAYCHK;
    volatile uint8_t TRANSMITNOCALDELAYCHK;
    volatile uint8_t RECEIVECALDELAYCHK;
    volatile uint8_t RECEIVENOCALDELAYCHK;
    volatile uint8_t CONFIGENDDURATION;
    volatile uint8_t TXDATAREADYCHECK;
    volatile uint8_t TXDELAYSTART;
    volatile uint8_t BYTE15;
    volatile uint8_t TXREADYTIMEOUT;
    volatile uint8_t RCVTIMEOUT[3];
    volatile uint8_t BYTE20;
    volatile uint8_t BYTE21;
    volatile uint8_t BYTE22;
    volatile uint8_t BYTE23;
    volatile uint32_t RESERVED; 
} GLOBALSTATMACH_TypeDef;

/**
  * @brief Radio Link State Machine description
  */

typedef struct {
    volatile uint8_t BYTE0;
    volatile uint8_t BYTE1;
    volatile uint8_t BYTE2;
    volatile uint8_t BYTE3;
    volatile uint32_t TXPOINT;
    volatile uint32_t RCVPOINT;
    volatile uint32_t TXPOINTPREV;
    volatile uint32_t RCVPOINTPREV;
    volatile uint32_t TXPOINTNEXT;
    volatile uint8_t PCNTTX[5];
    volatile uint8_t PCNTRCV[5];
    volatile uint8_t BYTE34;
    volatile uint8_t BYTE35;
    volatile uint32_t ACCADDR;
    volatile uint8_t CRCINIT[3];
    volatile uint8_t MAXRECEIVEDLENGTH;
    volatile uint8_t PAPOWER;
    volatile uint8_t HOPINCR;
    volatile uint8_t USEDCHANNELFLAGS[5];
    volatile uint8_t RESERVED;
    volatile uint16_t CONNEVENTCOUNTER;
    volatile uint16_t PAEVENTCOUNTER;
    volatile uint8_t ENCRYPTIV[8];
    volatile uint8_t ENCRYPTK[16];
} STATMACH_TypeDef;

/**
  * @brief Radio TxRxPack description
  */

typedef struct {
    volatile uint32_t NEXTPTR;
    volatile uint8_t  BYTE4;
    volatile uint8_t  BYTE5;
    volatile uint16_t RESERVED;
    volatile uint32_t DATAPTR;
    volatile uint8_t TIMER2[2];
    volatile uint8_t BYTE14;
    volatile uint8_t BYTE15;
    volatile uint32_t SUPPLEMENTPTR;
} TXRXPACK_TypeDef;

typedef enum {
  STATE_MACHINE_0 = 0,
  STATE_MACHINE_1,
  STATE_MACHINE_2,
  STATE_MACHINE_3,
  STATE_MACHINE_4,
  STATE_MACHINE_5,
  STATE_MACHINE_6,
  STATE_MACHINE_7,
} StateMachine_t; 

typedef struct ActionPacket ActionPacket;


typedef struct {
    uint32_t back2backTime;
    uint8_t tone_start_stop_flag;
    ActionPacket* current_action_packet;    
}RadioGlobalParameters_t;

struct ActionPacket
{
  uint8_t StateMachineNo ;      /* This parameter indicates the state machine number for this action. From 0 to 7. */
  uint8_t ActionTag;            /* The configuration of the current action. 
                                 * Action Tag: PLL_TRIG, TXRX, TIMER_WAKEUP, WHITENING_DISABLE, INC_CHAN, TIMESTAMP_POSITION, RELATIVE */
  uint8_t MaxReceiveLength;     /* Maximum size of received payload. Applicable only for RX actions. */
  uint32_t WakeupTime;          /* Contains the wakeup time in microsecond if it is relative.
                                 * If it is absolute it must be expressed in System Time (STU). */
  uint8_t *data;                /* Pointer to the array with the data to send (header, length and data field), for TX.
                                 * Pointer to the array where the data received are copied, for RX.
                                 * In case of RX, the array must have the max size MAX_PACKET_LENGTH. */
  uint32_t status;              /* The Status Register with the information on the action. */
  uint32_t timestamp_receive;   /* This field contains the timestamp when a packet is received.
                                 * Intended to be used in the dataRoutine() callback routine. RX only. */
  int32_t rssi;                 /* The rssi of the packet was received with. RX only. */
  BlueTransStruct trans_packet; /* This is a linked list, which is going to be used by Hardware.
                                  * User does not need to do anything. */
  ActionPacket *next_true;      /* Pointer to next ActionPacket if condRoutine() returns TRUE */
  ActionPacket *next_false;     /* Pointer to next ActionPacket if condRoutine() returns FALSE */
  uint8_t (*condRoutine)(ActionPacket*);        /* User callback that decide the next ActionPacket to use.
                                                 * It is time critical. Routine must end within 45 us. */
  uint8_t (*dataRoutine)(ActionPacket*, ActionPacket*); /* User callback for managing data. */
  uint8_t trans_config;                                 /* This is for configuring the device for TX or RX. User does not need to do anything. */
};

/**
* @}
*/


/** @defgroup RADIO_Exported_Functions RADIO Exported Functions
  * @{
  */


/** @defgroup RADIO_LL_EF_Configuration Configuration functions
  * @{
  */


/**
  * @brief  Contains the address of the command_start_list used by the RRM block to execute UDRA command.
  * @rmtoll WORD0          RADIOCONFIGPTR       LL_RADIO_SetRadioConfigurationAddressPointer
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetRadioConfigurationAddressPointer(uint32_t value)
{
  MODIFY_REG_FIELD(blueglobWord->WORD0, GLOBAL_WORD0_RADIOCONFIGPTR, value);
}

/**
  * @brief  Contains the address of the command_start_list used by the RRM block to execute UDRA command.
  * @rmtoll WORD0          RADIOCONFIGPTR       LL_RADIO_GetRadioConfigurationAddressPointer
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetRadioConfigurationAddressPointer()
{
  return (uint32_t)(READ_BIT(blueglobWord->WORD0, GLOBAL_WORD0_RADIOCONFIGPTR) >> GLOBAL_WORD0_RADIOCONFIGPTR_Pos);
}

/**
  * @brief  Defines the state machine number (in the range from 0 to 127) which is running for the current transmission or reception
  * @rmtoll WORD1          CURSTMACHNUM       LL_RADIO_SetCurrentConnectionMachineNumber
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetCurrentConnectionMachineNumber(uint32_t value)
{
  MODIFY_REG_FIELD(blueglobWord->WORD1, GLOBAL_WORD1_CURSTMACHNUM, value);
}

/**
  * @brief  Defines the state machine number (in the range from 0 to 127) which is running for the current transmission or reception
  * @rmtoll WORD1          CURSTMACHNUM       LL_RADIO_GetCurrentConnectionMachineNumber
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetCurrentConnectionMachineNumber()
{
  return (uint32_t)(READ_BIT(blueglobWord->WORD1, GLOBAL_WORD1_CURSTMACHNUM) >> GLOBAL_WORD1_CURSTMACHNUM_Pos);
}


/**
  * @brief  RADIO Enable
  * @rmtoll WORD1          ACTIVE            LL_RADIO_GlobalEnableBlue
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_GlobalEnableBlue()
{
  SET_BIT(blueglobWord->WORD1, GLOBAL_WORD1_ACTIVE);
}

/**
  * @brief  RADIO Disable
  * @rmtoll WORD1          ACTIVE            LL_RADIO_GlobalDisableBlue
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_GlobalDisableBlue()
{ 
  CLEAR_BIT(blueglobWord->WORD1, GLOBAL_WORD1_ACTIVE);
}

/**
  * @brief  Indicate if ACTIVE is enabled
  * @rmtoll WORD1          ACTIVE            LL_RADIO_IsEnabledGlobalBlue  
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_IsEnabledGlobalBlue()
{
  return ((READ_BIT(blueglobWord->WORD1, GLOBAL_WORD1_ACTIVE) == (GLOBAL_WORD1_ACTIVE)) ? 1U : 0U);
}


/**
  * @brief  Delay between wakeup timer trig event on sequencer and RX/TX request sending to the Radio FSM. It corresponds to the sequencer 1st INIT step duration.
  * @rmtoll WORD1          WAKEUPINITDELAY       LL_RADIO_SetWakeupInitDelay
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetWakeupInitDelay(uint32_t value)
{
  MODIFY_REG_FIELD(blueglobWord->WORD1, GLOBAL_WORD1_WAKEUPINITDELAY, value);
}

/**
  * @brief  Delay between wakeup timer trig event on sequencer and RX/TX request sending to the Radio FSM. It corresponds to the sequencer 1st INIT step duration.
  * @rmtoll WORD1          WAKEUPINITDELAY       LL_RADIO_GetWakeupInitDelay
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetWakeupInitDelay()
{
  return (uint32_t)(READ_BIT(blueglobWord->WORD1, GLOBAL_WORD1_WAKEUPINITDELAY) >> GLOBAL_WORD1_WAKEUPINITDELAY_Pos);
}
/**
  * @brief  Delay between Timer1 or Timer2 trig event on sequencer and RX/TX request sending to the Radio FSM. It corresponds to the sequencer 1st INIT step duration.
  * @rmtoll WORD1          TIMER12INITDELAYCAL       LL_RADIO_SetTimer12InitDelayCal
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetTimer12InitDelayCal(uint32_t value)
{
  MODIFY_REG_FIELD(blueglobWord->WORD1, GLOBAL_WORD1_TIMER12INITDELAYCAL, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD1          TIMER12INITDELAYCAL       LL_RADIO_GetTimer12InitDelayCal
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetTimer12InitDelayCal()
{
  return (uint32_t)(READ_BIT(blueglobWord->WORD1, GLOBAL_WORD1_TIMER12INITDELAYCAL) >> GLOBAL_WORD1_TIMER12INITDELAYCAL_Pos);
}


/**
  * @brief  Delay between Timer2 trig event on sequencer and RX/TX request sending to the Radio FSM. It corresponds to the sequencer 1st INIT step duration.
  * @rmtoll WORD1          TIMER2INITDELAYNOCAL       LL_RADIO_SetTimer12InitDelayNoCal
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetTimer12InitDelayNoCal(uint32_t value)
{
  MODIFY_REG_FIELD(blueglobWord->WORD1, GLOBAL_WORD1_TIMER2INITDELAYNOCAL, value);
}

/**
  * @brief  Delay between Timer2 trig event on sequencer and RX/TX request sending to the Radio FSM. It corresponds to the sequencer 1st INIT step duration.
  * @rmtoll WORD1          TIMER2INITDELAYNOCAL       LL_RADIO_GetTimer12InitDelayNoCal
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetTimer12InitDelayNoCal()
{
  return (uint32_t)(READ_BIT(blueglobWord->WORD1, GLOBAL_WORD1_TIMER2INITDELAYNOCAL) >> GLOBAL_WORD1_TIMER2INITDELAYNOCAL_Pos);
}

/**
  * @brief  Delay between TX request sent to the Radio FSM and the start pulse sent to the transmit block. It corresponds to the sequencer 2nd INIT + DATA INIT steps duration.
  * @rmtoll WORD2          TRANSMITCALDELAYCHK       LL_RADIO_SetTransmitCalDelayChk
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetTransmitCalDelayChk(uint32_t value)
{
  MODIFY_REG_FIELD(blueglobWord->WORD2, GLOBAL_WORD2_TRANSMITCALDELAYCHK, value);
}

/**
  * @brief  Delay between TX request sent to the Radio FSM and the start pulse sent to the transmit block. It corresponds to the sequencer 2nd INIT + DATA INIT steps duration.
  * @rmtoll WORD2          TRANSMITCALDELAYCHK       LL_RADIO_GetTransmitCalDelayChk
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetTransmitCalDelayChk()
{
  return (uint32_t)(READ_BIT(blueglobWord->WORD2, GLOBAL_WORD2_TRANSMITCALDELAYCHK) >> GLOBAL_WORD2_TRANSMITCALDELAYCHK_Pos);
}

/**
  * @brief  
  * @rmtoll WORD2          TRANSMITNOCALDELAYCHK       LL_RADIO_SetTransmitNoCalDelayChk
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetTransmitNoCalDelayChk(uint32_t value)
{
  MODIFY_REG_FIELD(blueglobWord->WORD2, GLOBAL_WORD2_TRANSMITNOCALDELAYCHK, value);
}

/**
  * @brief  Delay between TX request sent to the Radio FSM and the start pulse to the transmit block. It corresponds to the sequencer 2nd INIT + DATA INIT steps duration.
  * @rmtoll WORD2          TRANSMITNOCALDELAYCHK       LL_RADIO_GetTransmitNoCalDelayChk
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetTransmitNoCalDelayChk()
{
  return (uint32_t)(READ_BIT(blueglobWord->WORD2, GLOBAL_WORD2_TRANSMITNOCALDELAYCHK) >> GLOBAL_WORD2_TRANSMITNOCALDELAYCHK_Pos);
}


/**
  * @brief  
  * @note   
  * @rmtoll WORD2          RECEIVECALDELAYCHK       LL_RADIO_SetReceivedCalDelayChk
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetReceivedCalDelayChk(uint32_t value)
{
  MODIFY_REG_FIELD(blueglobWord->WORD2, GLOBAL_WORD2_RECEIVECALDELAYCHK, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD2          RECEIVECALDELAYCHK       LL_RADIO_GetReceivedCalDelayChk
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetReceivedCalDelayChk()
{
  return (uint32_t)(READ_BIT(blueglobWord->WORD2, GLOBAL_WORD2_RECEIVECALDELAYCHK) >> GLOBAL_WORD2_RECEIVECALDELAYCHK_Pos);
}
/**
  * @brief  
  * @note   
  * @rmtoll WORD2          RECEIVENOCALDELAYCHK       LL_RADIO_SetReceivedNoCalDelayChk
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetReceivedNoCalDelayChk(uint32_t value)
{
  MODIFY_REG_FIELD(blueglobWord->WORD2, GLOBAL_WORD2_RECEIVENOCALDELAYCHK, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD2          RECEIVENOCALDELAYCHK       LL_RADIO_GetReceivedNoCalDelayChk
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetReceivedNoCalDelayChk()
{
  return (uint32_t)(READ_BIT(blueglobWord->WORD2, GLOBAL_WORD2_RECEIVENOCALDELAYCHK) >> GLOBAL_WORD2_RECEIVENOCALDELAYCHK_Pos);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD3          CONFIGENDDURATION       LL_RADIO_SetConfigurationEndDuration
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetConfigurationEndDuration(uint32_t value)
{
  MODIFY_REG_FIELD(blueglobWord->WORD3, GLOBAL_WORD3_CONFIGENDDURATION, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD3          CONFIGENDDURATION       LL_RADIO_GetConfigurationEndDuration
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetConfigurationEndDuration()
{
  return (uint32_t)(READ_BIT(blueglobWord->WORD3, GLOBAL_WORD3_CONFIGENDDURATION) >> GLOBAL_WORD3_CONFIGENDDURATION_Pos);
}


/**
  * @brief  
  * @note   
  * @rmtoll WORD3          TXDATAREADYCHECK       LL_RADIO_SetTxDataReadyCheck
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetTxDataReadyCheck(uint32_t value)
{
  MODIFY_REG_FIELD(blueglobWord->WORD3, GLOBAL_WORD3_TXDATAREADYCHECK, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD3          TXDATAREADYCHECK       LL_RADIO_GetTxDataReadyCheck
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetTxDataReadyCheck()
{
  return (uint32_t)(READ_BIT(blueglobWord->WORD3, GLOBAL_WORD3_TXDATAREADYCHECK) >> GLOBAL_WORD3_TXDATAREADYCHECK_Pos);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD3          TXDELAYSTART       LL_RADIO_SetTxDelayStart
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetTxDelayStart(uint32_t value)
{
  MODIFY_REG_FIELD(blueglobWord->WORD3, GLOBAL_WORD3_TXDELAYSTART, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD3          TXDELAYSTART       LL_RADIO_GetTxDelayStart
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetTxDelayStart()
{
  return (uint32_t)(READ_BIT(blueglobWord->WORD3, GLOBAL_WORD3_TXDELAYSTART) >> GLOBAL_WORD3_TXDELAYSTART_Pos);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD3          TXDELAYEND       LL_RADIO_SetTxDelayEnd
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetTxDelayEnd(uint32_t value)
{
  MODIFY_REG_FIELD(blueglobWord->WORD3, GLOBAL_WORD3_TXDELAYEND, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD3          TXDELAYEND       LL_RADIO_GetTxDelayEnd
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetTxDelayEnd()
{
  return (uint32_t)(READ_BIT(blueglobWord->WORD3, GLOBAL_WORD3_TXDELAYEND) >> GLOBAL_WORD3_TXDELAYEND_Pos);
}


/**
  * @brief  
  * @note   
  * @rmtoll WORD3          TIMECAPTURESEL       LL_RADIO_SetTimeCaptureSel
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetTimeCaptureSel(uint32_t value)
{
  MODIFY_REG_FIELD(blueglobWord->WORD3, GLOBAL_WORD3_TIMECAPTURESEL, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD3          TIMECAPTURESEL       LL_RADIO_GetTimeCaptureSel
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetTimeCaptureSel()
{
  return (uint32_t)(READ_BIT(blueglobWord->WORD3, GLOBAL_WORD3_TIMECAPTURESEL) >> GLOBAL_WORD3_TIMECAPTURESEL_Pos);
}


/**
  * @brief  
  * @note   
  * @rmtoll WORD3          TIMECAPTURE       LL_RADIO_SetTimeCapture
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetTimeCapture(uint32_t value)
{
  MODIFY_REG_FIELD(blueglobWord->WORD3, GLOBAL_WORD3_TIMECAPTURE, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD3          TIMECAPTURE       LL_RADIO_GetTimeCapture
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetTimeCapture()
{
  return (uint32_t)(READ_BIT(blueglobWord->WORD3, GLOBAL_WORD3_TIMECAPTURE) >> GLOBAL_WORD3_TIMECAPTURE_Pos);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD4          TXREADYTIMEOUT       LL_RADIO_SetTransmissionReadyTimeout
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetTransmissionReadyTimeout(uint32_t value)
{
  MODIFY_REG_FIELD(blueglobWord->WORD4, GLOBAL_WORD4_TXREADYTIMEOUT, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD4          TXREADYTIMEOUT       LL_RADIO_GetTransmissionReadyTimeout
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetTransmissionReadyTimeout()
{
  return (uint32_t)(READ_BIT(blueglobWord->WORD4, GLOBAL_WORD4_TXREADYTIMEOUT) >> GLOBAL_WORD4_TXREADYTIMEOUT_Pos);
}


/**
  * @brief  
  * @note   
  * @rmtoll WORD4          RCVTIMEOUT       LL_RADIO_SetReceiveWindowTimeout
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetReceiveWindowTimeout(uint32_t value)
{
  MODIFY_REG_FIELD(blueglobWord->WORD4, GLOBAL_WORD4_RCVTIMEOUT, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD4          RCVTIMEOUT       LL_RADIO_GetReceiveWindowTimeout
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetReceiveWindowTimeout()
{
  return (uint32_t)(READ_BIT(blueglobWord->WORD4, GLOBAL_WORD4_RCVTIMEOUT) >> GLOBAL_WORD4_RCVTIMEOUT_Pos);
}


/**
  * @brief  RADIO Enable
  * @rmtoll WORD5          CHKFLAGAUTOCLEARENA            LL_RADIO_ChkFlagAutoclearEnable_Enable
  * @param  
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_ChkFlagAutoclearEnable_Enable()
{
  SET_BIT(blueglobWord->WORD5, GLOBAL_WORD5_CHKFLAGAUTOCLEARENA);
}

/**
  * @brief  RADIO Disable
  * @rmtoll WORD5          CHKFLAGAUTOCLEARENA            LL_RADIO_ChkFlagAutoclearEnable_Disable
  * @param  
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_ChkFlagAutoclearEnable_Disable()
{ 
  CLEAR_BIT(blueglobWord->WORD5, GLOBAL_WORD5_CHKFLAGAUTOCLEARENA);
}

/**
  * @brief  Indicate if CHKFLAGAUTOCLEARENA is enabled
  * @rmtoll WORD5          CHKFLAGAUTOCLEARENA            LL_RADIO_ChkFlagAutoclearEnable_IsEnabled  
  * @param  
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_ChkFlagAutoclearEnable_IsEnabled()
{
  return ((READ_BIT(blueglobWord->WORD5, GLOBAL_WORD5_CHKFLAGAUTOCLEARENA) == (GLOBAL_WORD5_CHKFLAGAUTOCLEARENA)) ? 1U : 0U);
}


/**
  * @brief  Indicate if INTNOACTIVELERROR is enabled
  * @rmtoll WORD5          INTNOACTIVELERROR            LL_RADIO_NoActiveLErrorInterrupt_Enable  
  * @param  
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void LL_RADIO_NoActiveLErrorInterrupt_Enable()
{
  SET_BIT(blueglobWord->WORD5, GLOBAL_WORD5_INTNOACTIVELERROR);
}

/**
  * @brief  Indicate if INTNOACTIVELERROR is enabled
  * @rmtoll WORD5          INTNOACTIVELERROR            LL_RADIO_NoActiveLErrorInterrupt_Disable 
  * @param  
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void LL_RADIO_NoActiveLErrorInterrupt_Disable()
{
  CLEAR_BIT(blueglobWord->WORD5, GLOBAL_WORD5_INTNOACTIVELERROR);
}

/**
  * @brief  Indicate if INTNOACTIVELERROR is enabled
  * @rmtoll WORD5          INTNOACTIVELERROR            LL_RADIO_NoActiveLErrorInterrupt_IsEnabled  
  * @param  
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_NoActiveLErrorInterrupt_IsEnabled()
{
  return ((READ_BIT(blueglobWord->WORD5, GLOBAL_WORD5_INTNOACTIVELERROR) == (GLOBAL_WORD5_INTNOACTIVELERROR)) ? 1U : 0U);
}

/**
  * @brief  RADIO Enable
  * @rmtoll WORD5          INTACTIVE2ERR            LL_RADIO_Active2ErrorInterrupt_Enable
  * @param  
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_Active2ErrorInterrupt_Enable()
{
  SET_BIT(blueglobWord->WORD5, GLOBAL_WORD5_INTACTIVE2ERR);
}

/**
  * @brief  RADIO Disable
  * @rmtoll WORD5          INTACTIVE2ERR            LL_RADIO_Active2ErrorInterrupt_Disable
  * @param  
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_Active2ErrorInterrupt_Disable()
{ 
  CLEAR_BIT(blueglobWord->WORD5, GLOBAL_WORD5_INTACTIVE2ERR);
}

/**
  * @brief  Indicate if INTACTIVE2ERR is enabled
  * @rmtoll WORD5          INTACTIVE2ERR            LL_RADIO_Active2ErrorInterrupt_IsEnabled  
  * @param  
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_Active2ErrorInterrupt_IsEnabled()
{
  return ((READ_BIT(blueglobWord->WORD5, GLOBAL_WORD5_INTACTIVE2ERR) == (GLOBAL_WORD5_INTACTIVE2ERR)) ? 1U : 0U);
}

#ifdef GLOBAL_WORD6_DEFAULTANTENNAID_Msk
/**
  * @brief  
  * @note   
  * @rmtoll WORD6          DEFAULTANTENNAID       LL_RADIO_SetDefaultAntennaID
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetDefaultAntennaID(uint32_t value)
{
  MODIFY_REG_FIELD(blueglobWord->WORD6, GLOBAL_WORD6_DEFAULTANTENNAID, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD6          DEFAULTANTENNAID       LL_RADIO_GetDefaultAntennaID
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetDefaultAntennaID(void)
{
  return (uint32_t)(READ_BIT(blueglobWord->WORD6, GLOBAL_WORD6_DEFAULTANTENNAID) >> GLOBAL_WORD6_DEFAULTANTENNAID_Pos);
}
#endif /* GLOBAL_WORD6_DEFAULTANTENNAID_Msk */



/**
  * @brief  
  * @note   
  * @rmtoll WORD0          UCHAN       LL_RADIO_SetUnmappedChannel
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetUnmappedChannel(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORD0, STATEMACH_WORD0_UCHAN, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD0          UCHAN       LL_RADIO_GetUnmappedChannel
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetUnmappedChannel(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORD0, STATEMACH_WORD0_UCHAN) >> STATEMACH_WORD0_UCHAN_Pos);
}

/**
  * @brief  RADIO Enable
  * @rmtoll WORD0          RADIOCOMLISTENA            LL_RADIO_RadioCommandList_Enable
  * @param  
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_RadioCommandList_Enable(uint8_t stateMachineNo)
{
  SET_BIT((bluedataWord+stateMachineNo)->WORD0, STATEMACH_WORD0_RADIOCOMLISTENA);
}

/**
  * @brief  RADIO Disable
  * @rmtoll WORD0          RADIOCOMLISTENA            LL_RADIO_RadioCommandList_Disable
  * @param  
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_RadioCommandList_Disable(uint8_t stateMachineNo)
{ 
  CLEAR_BIT((bluedataWord+stateMachineNo)->WORD0, STATEMACH_WORD0_RADIOCOMLISTENA);
}

/**
  * @brief  Indicate if RADIOCOMLISTENA is enabled
  * @rmtoll WORD0          RADIOCOMLISTENA            LL_RADIO_RadioCommandList_IsEnabled  
  * @param  
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_RadioCommandList_IsEnabled(uint8_t stateMachineNo)
{
  return ((READ_BIT((bluedataWord+stateMachineNo)->WORD0, STATEMACH_WORD0_RADIOCOMLISTENA) == (STATEMACH_WORD0_RADIOCOMLISTENA)) ? 1U : 0U);
}

/**
  * @brief  RADIO Enable
  * @rmtoll WORD0          TXMODE            LL_RADIO_TxMode_Enable
  * @param  
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TxMode_Enable(uint8_t stateMachineNo)
{
  SET_BIT((bluedataWord+stateMachineNo)->WORD0, STATEMACH_WORD0_TXMODE);
}

/**
  * @brief  RADIO Disable
  * @rmtoll WORD0          TXMODE            LL_RADIO_TxMode_Disable
  * @param  
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_TxMode_Disable(uint8_t stateMachineNo)
{ 
  CLEAR_BIT((bluedataWord+stateMachineNo)->WORD0, STATEMACH_WORD0_TXMODE);
}

/**
  * @brief  Indicate if TXMODE is enabled
  * @rmtoll WORD0          TXMODE            LL_RADIO_TxMode_IsEnabled  
  * @param  
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_TxMode_IsEnabled(uint8_t stateMachineNo)
{
  return ((READ_BIT((bluedataWord+stateMachineNo)->WORD0, STATEMACH_WORD0_TXMODE) == (STATEMACH_WORD0_TXMODE)) ? 1U : 0U);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD0          REMAP_CHAN       LL_RADIO_SetRemapChannel
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetRemapChannel(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORD0, STATEMACH_WORD0_REMAP_CHAN, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD0          REMAP_CHAN       LL_RADIO_GetRemapChannel
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetRemapChannel(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORD0, STATEMACH_WORD0_REMAP_CHAN) >> STATEMACH_WORD0_REMAP_CHAN_Pos);
}


/**
  * @brief  
  * @note   
  * @rmtoll WORD0          SN       LL_RADIO_SetSequenceNumber
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetSequenceNumber(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORD0, STATEMACH_WORD0_SN, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD0          SN       LL_RADIO_GetSequenceNumber
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetSequenceNumber(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORD0, STATEMACH_WORD0_SN) >> STATEMACH_WORD0_SN_Pos);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD0          SN       LL_RADIO_ToggleSequenceNumber
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_ToggleSequenceNumber(uint8_t stateMachineNo)
{
    TOGGLE_BIT((bluedataWord+stateMachineNo)->WORD0, STATEMACH_WORD0_SN);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD0          NESN       LL_RADIO_SetNextExpectedSequenceNumber
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetNextExpectedSequenceNumber(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORD0, STATEMACH_WORD0_NESN, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD0          NESN       LL_RADIO_ToggleNextExpectedSequenceNumber
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_ToggleNextExpectedSequenceNumber(uint8_t stateMachineNo)
{
    TOGGLE_BIT((bluedataWord+stateMachineNo)->WORD0, STATEMACH_WORD0_NESN);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD0          NESN       LL_RADIO_GetNextExpectedSequenceNumber
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetNextExpectedSequenceNumber(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORD0, STATEMACH_WORD0_NESN) >> STATEMACH_WORD0_NESN_Pos);
}


/**
  * @brief  RADIO Enable
  * @rmtoll WORD0          ENCRYPTON            LL_RADIO_Encryption_Enable
  * @param  
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_Encryption_Enable(uint8_t stateMachineNo)
{
  SET_BIT((bluedataWord+stateMachineNo)->WORD0, STATEMACH_WORD0_ENCRYPTON);
}

/**
  * @brief  RADIO Disable
  * @rmtoll WORD0          ENCRYPTON            LL_RADIO_Encryption_Disable
  * @param  
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_Encryption_Disable(uint8_t stateMachineNo)
{ 
  CLEAR_BIT((bluedataWord+stateMachineNo)->WORD0, STATEMACH_WORD0_ENCRYPTON);
}

/**
  * @brief  Indicate if ENCRYPTON is enabled
  * @rmtoll WORD0          ENCRYPTON            LL_RADIO_Encryption_IsEnabled  
  * @param  
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_Encryption_IsEnabled(uint8_t stateMachineNo)
{
  return ((READ_BIT((bluedataWord+stateMachineNo)->WORD0, STATEMACH_WORD0_ENCRYPTON) == (STATEMACH_WORD0_ENCRYPTON)) ? 1U : 0U);
}


/**
  * @brief  
  * @note   
  * @rmtoll WORD0          TXPHY       LL_RADIO_SetTransmissionPhy
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetTransmissionPhy(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORD0, STATEMACH_WORD0_TXPHY, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD0          TXPHY       LL_RADIO_GetTransmissionPhy
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetTransmissionPhy(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORD0, STATEMACH_WORD0_TXPHY) >> STATEMACH_WORD0_TXPHY_Pos);
}

#ifdef STATEMACH_WORD0_CTEDISABLE

/**
  * @brief  
  * @note   
  * @rmtoll WORD0          CTEDISABLE       LL_RADIO_SetCTEDisable
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetCTEDisable(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORD0, STATEMACH_WORD0_CTEDISABLE, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD0          CTEDISABLE       LL_RADIO_GetCTEDisable
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetCTEDisable(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORD0, STATEMACH_WORD0_CTEDISABLE) >> STATEMACH_WORD0_CTEDISABLE_Pos);
}

#endif

/**
  * @brief  
  * @note   
  * @rmtoll WORD0          RXPHY       LL_RADIO_SetReceptionPhy
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetReceptionPhy(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORD0, STATEMACH_WORD0_RXPHY, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD0          RXPHY       LL_RADIO_GetReceptionPhy
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetReceptionPhy(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORD0, STATEMACH_WORD0_RXPHY) >> STATEMACH_WORD0_RXPHY_Pos);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD1          TXPOINT       LL_RADIO_SetTxPoint
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetTxPoint(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORD1, STATEMACH_WORD1_TXPOINT, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD1          TXPOINT       LL_RADIO_GetTxPoint
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetTxPoint(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORD1, STATEMACH_WORD1_TXPOINT) >> STATEMACH_WORD1_TXPOINT_Pos);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD2          RCVPOINT       LL_RADIO_SetRcvPoint
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetRcvPoint(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORD2, STATEMACH_WORD2_RCVPOINT, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD2          RCVPOINT       LL_RADIO_GetRcvPoint
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetRcvPoint(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORD2, STATEMACH_WORD2_RCVPOINT) >> STATEMACH_WORD2_RCVPOINT_Pos);
}


/**
  * @brief  
  * @note   
  * @rmtoll WORD3          TXPOINTPREV       LL_RADIO_SetTxPointPrevious
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetTxPointPrevious(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORD3, STATEMACH_WORD3_TXPOINTPREV, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD3          TXPOINTPREV       LL_RADIO_GetTxPointPrevious
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetTxPointPrevious(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORD3, STATEMACH_WORD3_TXPOINTPREV) >> STATEMACH_WORD3_TXPOINTPREV_Pos);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD4          RCVPOINTPREV       LL_RADIO_SetRcvPointPrevious
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetRcvPointPrevious(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORD4, STATEMACH_WORD4_RCVPOINTPREV, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD4          RCVPOINTPREV       LL_RADIO_GetRcvPointPrevious
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetRcvPointPrevious(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORD4, STATEMACH_WORD4_RCVPOINTPREV) >> STATEMACH_WORD4_RCVPOINTPREV_Pos);
}
/**
  * @brief  
  * @note   
  * @rmtoll WORD6          PCNTTX_31_0       LL_RADIO_SetPacketCounterTx_31_0
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetPacketCounterTx_31_0(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORD6, STATEMACH_WORD6_PCNTTX_31_0, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD6          PCNTTX_31_0       LL_RADIO_GetPacketCounterTx_31_0
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetPacketCounterTx_31_0(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORD6, STATEMACH_WORD6_PCNTTX_31_0) >> STATEMACH_WORD6_PCNTTX_31_0_Pos);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD7          PCNTTX_39_32       LL_RADIO_SetPacketCounterTx_39_32
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetPacketCounterTx_39_32(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORD7, STATEMACH_WORD7_PCNTTX_39_32, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD7          PCNTTX_39_32       LL_RADIO_GetPacketCounterTx_39_32
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetPacketCounterTx_39_32(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORD7, STATEMACH_WORD7_PCNTTX_39_32) >> STATEMACH_WORD7_PCNTTX_39_32_Pos);
}


/**
  * @brief  
  * @note   
  * @rmtoll WORD7          PCNTRCV_23_0       LL_RADIO_SetPacketCounterRx_23_0
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetPacketCounterRx_23_0(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORD7, STATEMACH_WORD7_PCNTRCV_23_0, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD7          PCNTRCV_23_0       LL_RADIO_GetPacketCounterRx_23_0
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetPacketCounterRx_23_0(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORD7, STATEMACH_WORD7_PCNTRCV_23_0) >> STATEMACH_WORD7_PCNTRCV_23_0_Pos);
}


/**
  * @brief  
  * @note   
  * @rmtoll WORD8          PCNTRCV_39_24       LL_RADIO_SetPacketCounterRx_39_24
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetPacketCounterRx_39_24(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORD8, STATEMACH_WORD8_PCNTRCV_39_24, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD8          PCNTRCV_39_24       LL_RADIO_GetPacketCounterRx_39_24
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetPacketCounterRx_39_24(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORD8, STATEMACH_WORD8_PCNTRCV_39_24) >> STATEMACH_WORD8_PCNTRCV_39_24_Pos);
}

/**
  * @brief  RADIO Enable
  * @rmtoll WORD8          INTENCERROR            LL_RADIO_ReceiveEncryptionErrorInterrupt_Enable
  * @param  
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_ReceiveEncryptionErrorInterrupt_Enable(uint8_t stateMachineNo)
{
  SET_BIT((bluedataWord+stateMachineNo)->WORD8, STATEMACH_WORD8_INTENCERROR);
}

/**
  * @brief  RADIO Disable
  * @rmtoll WORD8          INTENCERROR            LL_RADIO_ReceiveEncryptionErrorInterrupt_Disable
  * @param  
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_ReceiveEncryptionErrorInterrupt_Disable(uint8_t stateMachineNo)
{ 
  CLEAR_BIT((bluedataWord+stateMachineNo)->WORD8, STATEMACH_WORD8_INTENCERROR);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD9          ACCADDR       LL_RADIO_SetAccessAddress
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetAccessAddress(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORD9, STATEMACH_WORD9_ACCADDR, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD9          ACCADDR       LL_RADIO_GetAccessAddress
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetAccessAddress(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORD9, STATEMACH_WORD9_ACCADDR) >> STATEMACH_WORD9_ACCADDR_Pos);
}


/**
  * @brief  
  * @note   
  * @rmtoll WORDA          CRCINIT       LL_RADIO_SetCRCInitializationValue
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetCRCInitializationValue(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORDA, STATEMACH_WORDA_CRCINIT, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORDA          CRCINIT       LL_RADIO_GetCRCInitializationValue
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetCRCInitializationValue(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORDA, STATEMACH_WORDA_CRCINIT) >> STATEMACH_WORDA_CRCINIT_Pos);
}


/**
  * @brief  
  * @note   
  * @rmtoll WORDA          MAXRECEIVEDLENGTH       LL_RADIO_SetMaximumReceiveLength
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetMaximumReceiveLength(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORDA, STATEMACH_WORDA_MAXRECEIVEDLENGTH, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORDA          MAXRECEIVEDLENGTH       LL_RADIO_GetMaximumReceiveLength
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetMaximumReceiveLength(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORDA, STATEMACH_WORDA_MAXRECEIVEDLENGTH) >> STATEMACH_WORDA_MAXRECEIVEDLENGTH_Pos);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORDB          PAPOWER       LL_RADIO_SetPAPower
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetPAPower(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORDB, STATEMACH_WORDB_PAPOWER, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORDB          PAPOWER       LL_RADIO_GetPAPower
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetPAPower(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORDB, STATEMACH_WORDB_PAPOWER) >> STATEMACH_WORDB_PAPOWER_Pos);
}


/**
  * @brief  
  * @note   
  * @rmtoll WORDB          HOPINCR       LL_RADIO_SetHopIncrement
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetHopIncrement(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORDB, STATEMACH_WORDB_HOPINCR, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORDB          HOPINCR       LL_RADIO_GetHopIncrement
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetHopIncrement(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORDB, STATEMACH_WORDB_HOPINCR) >> STATEMACH_WORDB_HOPINCR_Pos);
}


/**
  * @brief  
  * @note   
  * @rmtoll WORDB          USEDCHANNELFLAGS_15_0       LL_RADIO_SetUsedChannelFlags_15_0
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetUsedChannelFlags_15_0(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORDB, STATEMACH_WORDB_USEDCHANNELFLAGS_15_0, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORDB          USEDCHANNELFLAGS_15_0       LL_RADIO_GetUsedChannelFlags_15_0
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetUsedChannelFlags_15_0(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORDB, STATEMACH_WORDB_USEDCHANNELFLAGS_15_0) >> STATEMACH_WORDB_USEDCHANNELFLAGS_15_0_Pos);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORDC          USEDCHANNELFLAGS_36_16       LL_RADIO_SetUsedChannelFlags_36_16
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetUsedChannelFlags_36_16(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORDC, STATEMACH_WORDC_USEDCHANNELFLAGS_36_16, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORDC          USEDCHANNELFLAGS_36_16       LL_RADIO_GetUsedChannelFlags_36_16
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetUsedChannelFlags_36_16(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORDC, STATEMACH_WORDC_USEDCHANNELFLAGS_36_16) >> STATEMACH_WORDC_USEDCHANNELFLAGS_36_16_Pos);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORDE          STATEMACH_WORDE_ENCRYPTIV_0_31       LL_RADIO_SetEncryptIV
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetEncryptIV(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORDE, STATEMACH_WORDE_ENCRYPTIV_0_31, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORDE          STATEMACH_WORDE_ENCRYPTIV_0_31       LL_RADIO_GetEncryptIV
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetEncryptIV(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORDE, STATEMACH_WORDE_ENCRYPTIV_0_31) >> STATEMACH_WORDE_ENCRYPTIV_0_31_Pos);
}

#ifdef STATEMACH_WORD14_AOD_NAOA

/**
  * @brief  
  * @note   
  * @rmtoll WORD14          AOD_NAOA       LL_RADIO_SetAodNaoa
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetAodNaoa(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORD14, STATEMACH_WORD14_AOD_NAOA, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD14          AOD_NAOA       LL_RADIO_GetAodNaoa
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetAodNaoa(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORD14, STATEMACH_WORD14_AOD_NAOA) >> STATEMACH_WORD14_AOD_NAOA_Pos);
}
#endif

#ifdef STATEMACH_WORD14_CTETIME
/**
  * @brief  
  * @note   
  * @rmtoll WORD14          CTETIME       LL_RADIO_SetCTETime
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetCTETime(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORD14, STATEMACH_WORD14_CTETIME, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD14          CTETIME       LL_RADIO_GetCTETime
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetCTETime(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORD14, STATEMACH_WORD14_CTETIME) >> STATEMACH_WORD14_CTETIME_Pos);
}
#endif

#ifdef STATEMACH_WORD14_CTESLOTWIDTH
/**
  * @brief  
  * @note   
  * @rmtoll WORD14          CTESLOTWIDTH       LL_RADIO_SetCTESlotWidth
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetCTESlotWidth(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORD14, STATEMACH_WORD14_CTESLOTWIDTH, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD14          CTESLOTWIDTH       LL_RADIO_GetCTESlotWidth
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetCTESlotWidth(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORD14, STATEMACH_WORD14_CTESLOTWIDTH) >> STATEMACH_WORD14_CTESLOTWIDTH_Pos);
}
#endif

#ifdef STATEMACH_WORD14_MAXIMUMIQSAMPLESNUMBER
/**
  * @brief  
  * @note   
  * @rmtoll WORD14          MAXIMUMIQSAMPLESNUMBER       LL_RADIO_SetMaximumIQSamplesNumber
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetMaximumIQSamplesNumber(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORD14, STATEMACH_WORD14_MAXIMUMIQSAMPLESNUMBER, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD14          MAXIMUMIQSAMPLESNUMBER       LL_RADIO_GetMaximumIQSamplesNumber
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetMaximumIQSamplesNumber(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORD14, STATEMACH_WORD14_MAXIMUMIQSAMPLESNUMBER) >> STATEMACH_WORD14_MAXIMUMIQSAMPLESNUMBER_Pos);
}
#endif

#ifdef STATEMACH_WORD14_ANTENNAPATTERNLENGTH
/**
  * @brief  
  * @note   
  * @rmtoll WORD14          ANTENNAPATTERNLENGTH       LL_RADIO_SetAntennaPatternLength
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetAntennaPatternLength(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORD14, STATEMACH_WORD14_ANTENNAPATTERNLENGTH, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD14          ANTENNAPATTERNLENGTH       LL_RADIO_GetAntennaPatternLength
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetAntennaPatternLength(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORD14, STATEMACH_WORD14_ANTENNAPATTERNLENGTH) >> STATEMACH_WORD14_ANTENNAPATTERNLENGTH_Pos);
}
#endif

#ifdef STATEMACH_WORD15_IQSAMPLESPTR
/**
  * @brief  
  * @note   
  * @rmtoll WORD15          IQSAMPLESPTR       LL_RADIO_SetIQSamplesPtr
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetIQSamplesPtr(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORD15, STATEMACH_WORD15_IQSAMPLESPTR, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD15          IQSAMPLESPTR       LL_RADIO_GetIQSamplesPtr
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetIQSamplesPtr(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORD15, STATEMACH_WORD15_IQSAMPLESPTR) >> STATEMACH_WORD15_IQSAMPLESPTR_Pos);
}
#endif

#ifdef STATEMACH_WORD16_ANTENNAPATTERNPTR
/**
  * @brief  
  * @note   
  * @rmtoll WORD16          ANTENNAPATTERNPTR       LL_RADIO_SetAntennaPatternPtr
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetAntennaPatternPtr(uint8_t stateMachineNo, uint32_t value)
{
  MODIFY_REG_FIELD((bluedataWord+stateMachineNo)->WORD16, STATEMACH_WORD16_ANTENNAPATTERNPTR, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD16          ANTENNAPATTERNPTR       LL_RADIO_GetAntennaPatternPtr
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetAntennaPatternPtr(uint8_t stateMachineNo)
{
  return (uint32_t)(READ_BIT((bluedataWord+stateMachineNo)->WORD16, STATEMACH_WORD16_ANTENNAPATTERNPTR) >> STATEMACH_WORD16_ANTENNAPATTERNPTR_Pos);
}

#endif 


/**
  * @brief  
  * @note   
  * @rmtoll WORD0          NEXTPTR       LL_RADIO_SetNextPointer
  * @param  ppp RADIO Instance
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetNextPointer(TXRXPACK_TypeDef *p, uint32_t value)
{
  MODIFY_REG_FIELD(((TXRXPACK_WORD_TypeDef*)p)->WORD0, TXRXPACK_WORD0_NEXTPTR, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD0          NEXTPTR       LL_RADIO_GetNextPointer
  * @param  ppp RADIO Instance
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetNextPointer(TXRXPACK_TypeDef *p)
{
  return (uint32_t)(READ_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD0, TXRXPACK_WORD0_NEXTPTR) >> TXRXPACK_WORD0_NEXTPTR_Pos);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD1          CALREQ       LL_RADIO_SetCalibrationRequest
  * @param  ppp RADIO Instance
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetCalibrationRequest(TXRXPACK_TypeDef *p, uint32_t value)
{
  MODIFY_REG_FIELD(((TXRXPACK_WORD_TypeDef*)p)->WORD1, TXRXPACK_WORD1_CALREQ, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD1          CALREQ       LL_RADIO_GetCalibrationRequest
  * @param  ppp RADIO Instance
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetCalibrationRequest(TXRXPACK_TypeDef *p)
{
  return (uint32_t)(READ_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD1, TXRXPACK_WORD1_CALREQ) >> TXRXPACK_WORD1_CALREQ_Pos);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD1          KEEPSEMAREQ       LL_RADIO_SetKeepSemaRequest
  * @param  ppp RADIO Instance
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetKeepSemaRequest(TXRXPACK_TypeDef *p, uint32_t value)
{
  MODIFY_REG_FIELD(((TXRXPACK_WORD_TypeDef*)p)->WORD1, TXRXPACK_WORD1_KEEPSEMAREQ, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD1          KEEPSEMAREQ       LL_RADIO_GetKeepSemaRequest
  * @param  ppp RADIO Instance
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetKeepSemaRequest(TXRXPACK_TypeDef *p)
{
  return (uint32_t)(READ_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD1, TXRXPACK_WORD1_KEEPSEMAREQ) >> TXRXPACK_WORD1_KEEPSEMAREQ_Pos);
}

#ifdef TXRXPACK_WORD1_SUPPENA
/**
  * @brief  
  * @note   
  * @rmtoll WORD1          SUPPENA       LL_RADIO_SetSuppEna
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetSuppEna(TXRXPACK_TypeDef *p, uint32_t value)
{
  MODIFY_REG_FIELD(((TXRXPACK_WORD_TypeDef*)p)->WORD1, TXRXPACK_WORD1_SUPPENA, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD1          SUPPENA       LL_RADIO_GetSuppEna
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetSuppEna(TXRXPACK_TypeDef *p)
{
  return (uint32_t)(READ_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD1, TXRXPACK_WORD1_SUPPENA) >> TXRXPACK_WORD1_SUPPENA_Pos);
}
#endif

#ifdef TXRXPACK_WORD1_CTEANDSAMPLINGENABLE
/**
  * @brief  
  * @note   
  * @rmtoll WORD1          CTEANDSAMPLINGENABLE        LL_RADIO_SetCTEAndSamplingEnable
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetCTEAndSamplingEnable(TXRXPACK_TypeDef *p, uint32_t value)
{
  MODIFY_REG_FIELD(((TXRXPACK_WORD_TypeDef*)p)->WORD1, TXRXPACK_WORD1_CTEANDSAMPLINGENABLE , value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD1          CTEANDSAMPLINGENABLE        LL_RADIO_GetCTEAndSamplingEnable
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetCTEAndSamplingEnable(TXRXPACK_TypeDef *p)
{
  return (uint32_t)(READ_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD1, TXRXPACK_WORD1_CTEANDSAMPLINGENABLE ) >> TXRXPACK_WORD1_CTEANDSAMPLINGENABLE_Pos);
}
#endif

/**
  * @brief  
  * @note   
  * @rmtoll WORD1          CRCINITSEL       LL_RADIO_SetCRCInitializationSelector
  * @param  ppp RADIO Instance
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetCRCInitializationSelector(TXRXPACK_TypeDef *p, uint32_t value)
{
  MODIFY_REG_FIELD(((TXRXPACK_WORD_TypeDef*)p)->WORD1, TXRXPACK_WORD1_CRCINITSEL, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD1          CRCINITSEL       LL_RADIO_GetCRCInitializationSelector
  * @param  ppp RADIO Instance
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetCRCInitializationSelector(TXRXPACK_TypeDef *p)
{
  return (uint32_t)(READ_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD1, TXRXPACK_WORD1_CRCINITSEL) >> TXRXPACK_WORD1_CRCINITSEL_Pos);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD1          ADVERTISE       LL_RADIO_SetAdvertise
  * @param  ppp RADIO Instance
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetAdvertise(TXRXPACK_TypeDef *p, uint32_t value)
{
  MODIFY_REG_FIELD(((TXRXPACK_WORD_TypeDef*)p)->WORD1, TXRXPACK_WORD1_ADVERTISE, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD1          ADVERTISE       LL_RADIO_GetAdvertise
  * @param  ppp RADIO Instance
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetAdvertise(TXRXPACK_TypeDef *p)
{
  return (uint32_t)(READ_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD1, TXRXPACK_WORD1_ADVERTISE) >> TXRXPACK_WORD1_ADVERTISE_Pos);
}

/**
  * @brief  RADIO Enable
  * @rmtoll WORD1          SN_EN            LL_RADIO_AutomaticSnNesnHardwareMechanism_Enable
  * @param  
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_AutomaticSnNesnHardwareMechanism_Enable(TXRXPACK_TypeDef *p)
{
  SET_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD1, TXRXPACK_WORD1_SN_EN);
}

/**
  * @brief  RADIO Disable
  * @rmtoll WORD1          SN_EN            LL_RADIO_AutomaticSnNesnHardwareMechanism_Disable
  * @param  
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_AutomaticSnNesnHardwareMechanism_Disable(TXRXPACK_TypeDef *p)
{ 
  CLEAR_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD1, TXRXPACK_WORD1_SN_EN);
}

/**
  * @brief  Indicate if SN_EN is enabled
  * @rmtoll WORD1          SN_EN            LL_RADIO_AutomaticSnNesnHardwareMechanism_IsEnabled  
  * @param  
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_AutomaticSnNesnHardwareMechanism_IsEnabled(TXRXPACK_TypeDef *p)
{
  return ((READ_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD1, TXRXPACK_WORD1_SN_EN) == (TXRXPACK_WORD1_SN_EN)) ? 1U : 0U);
}

/**
  * @brief  RADIO Enable
  * @rmtoll WORD1          INCCHAN            LL_RADIO_IncrementerChannel_Enable
  * @param  
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_IncrementerChannel_Enable(TXRXPACK_TypeDef *p)
{
  SET_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD1, TXRXPACK_WORD1_INCCHAN);
}

/**
  * @brief  RADIO Disable
  * @rmtoll WORD1          INCCHAN            LL_RADIO_IncrementerChannel_Disable
  * @param  
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_IncrementerChannel_Disable(TXRXPACK_TypeDef *p)
{ 
  CLEAR_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD1, TXRXPACK_WORD1_INCCHAN);
}

/**
  * @brief  Indicate if INCCHAN is enabled
  * @rmtoll WORD1          INCCHAN            LL_RADIO_IncrementerChannel_IsEnabled  
  * @param  
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_IncrementerChannel_IsEnabled(TXRXPACK_TypeDef *p)
{
  return ((READ_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD1, TXRXPACK_WORD1_INCCHAN) == (TXRXPACK_WORD1_INCCHAN)) ? 1U : 0U);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD1          NEXTTXMODE       LL_RADIO_SetNextTxMode
  * @param  px RADIO Instance
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetNextTxMode(TXRXPACK_TypeDef *p, uint32_t value)
{
  MODIFY_REG_FIELD(((TXRXPACK_WORD_TypeDef*)p)->WORD1, TXRXPACK_WORD1_NEXTTXMODE, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD1          NEXTTXMODE       LL_RADIO_GetNextTxMode
  * @param  px RADIO Instance
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetNextTxMode(TXRXPACK_TypeDef *p)
{
  return (uint32_t)(READ_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD1, TXRXPACK_WORD1_NEXTTXMODE) >> TXRXPACK_WORD1_NEXTTXMODE_Pos);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD1          ALLTABLEREADY       LL_RADIO_SetAllTableDataReady
  * @param  px RADIO Instance
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetAllTableDataReady(TXRXPACK_TypeDef *p, uint32_t value)
{
  MODIFY_REG_FIELD(((TXRXPACK_WORD_TypeDef*)p)->WORD1, TXRXPACK_WORD1_ALLTABLEREADY, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD1          ALLTABLEREADY       LL_RADIO_GetAllTableDataReady
  * @param  px RADIO Instance
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetAllTableDataReady(TXRXPACK_TypeDef *p)
{
  return (uint32_t)(READ_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD1, TXRXPACK_WORD1_ALLTABLEREADY) >> TXRXPACK_WORD1_ALLTABLEREADY_Pos);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD1          TXDATAREADY       LL_RADIO_SetTransmissionDataReady
  * @param  px RADIO Instance
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetTransmissionDataReady(TXRXPACK_TypeDef *p, uint32_t value)
{
  MODIFY_REG_FIELD(((TXRXPACK_WORD_TypeDef*)p)->WORD1, TXRXPACK_WORD1_TXDATAREADY, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD1          TXDATAREADY       LL_RADIO_GetTransmissionDataReady
  * @param  px RADIO Instance
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetTransmissionDataReady(TXRXPACK_TypeDef *p)
{
  return (uint32_t)(READ_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD1, TXRXPACK_WORD1_TXDATAREADY) >> TXRXPACK_WORD1_TXDATAREADY_Pos);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD1          DISABLEWHITENING       LL_RADIO_SetDisableWhitening
  * @param  px RADIO Instance
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetDisableWhitening(TXRXPACK_TypeDef *p, uint32_t value)
{
  MODIFY_REG_FIELD(((TXRXPACK_WORD_TypeDef*)p)->WORD1, TXRXPACK_WORD1_DISABLEWHITENING, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD1          DISABLEWHITENING       LL_RADIO_GetDisableWhitening
  * @param  px RADIO Instance
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetDisableWhitening(TXRXPACK_TypeDef *p)
{
  return (uint32_t)(READ_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD1, TXRXPACK_WORD1_DISABLEWHITENING) >> TXRXPACK_WORD1_DISABLEWHITENING_Pos);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD2          DATAPTR       LL_RADIO_SetDataPointer
  * @param  px RADIO Instance
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetDataPointer(TXRXPACK_TypeDef *p, uint32_t value)
{
  MODIFY_REG_FIELD(((TXRXPACK_WORD_TypeDef*)p)->WORD2, TXRXPACK_WORD2_DATAPTR, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD2          DATAPTR       LL_RADIO_GetDataPointer
  * @param  px RADIO Instance
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetDataPointer(TXRXPACK_TypeDef *p)
{
  return (uint32_t)(READ_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD2, TXRXPACK_WORD2_DATAPTR) >> TXRXPACK_WORD2_DATAPTR_Pos);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD3          TIMER2       LL_RADIO_SetTimer2Triggering
  * @param  px RADIO Instance
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetTimer2Triggering(TXRXPACK_TypeDef *p, uint32_t value)
{
  MODIFY_REG_FIELD(((TXRXPACK_WORD_TypeDef*)p)->WORD3, TXRXPACK_WORD3_TIMER2, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD3          TIMER2       LL_RADIO_GetTimer2Triggering
  * @param  px RADIO Instance
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetTimer2Triggering(TXRXPACK_TypeDef *p)
{
  return (uint32_t)(READ_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD3, TXRXPACK_WORD3_TIMER2) >> TXRXPACK_WORD3_TIMER2_Pos);
}

/**
  * @brief  RADIO Enable
  * @rmtoll WORD3          TIMER2EN            LL_RADIO_Timer2_Enable
  * @param  
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_Timer2_Enable(TXRXPACK_TypeDef *p)
{
  SET_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD3, TXRXPACK_WORD3_TIMER2EN);
}

/**
  * @brief  RADIO Disable
  * @rmtoll WORD3          TIMER2EN            LL_RADIO_Timer2_Disable
  * @param  
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_Timer2_Disable(TXRXPACK_TypeDef *p)
{ 
  CLEAR_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD3, TXRXPACK_WORD3_TIMER2EN);
}

/**
  * @brief  Indicate if TIMER2EN is enabled
  * @rmtoll WORD3          TIMER2EN            LL_RADIO_Timer2_IsEnabled  
  * @param  
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_Timer2_IsEnabled(TXRXPACK_TypeDef *p)
{
  return ((READ_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD3, TXRXPACK_WORD3_TIMER2EN) == (TXRXPACK_WORD3_TIMER2EN)) ? 1U : 0U);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD3          TRIGRCV       LL_RADIO_SetTrigRcv
  * @param  px RADIO Instance
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetTrigRcv(TXRXPACK_TypeDef *p, uint32_t value)
{
  MODIFY_REG_FIELD(((TXRXPACK_WORD_TypeDef*)p)->WORD3, TXRXPACK_WORD3_TRIGRCV, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD3          TRIGRCV       LL_RADIO_GetTrigRcv
  * @param  px RADIO Instance
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetTrigRcv(TXRXPACK_TypeDef *p)
{
  return (uint32_t)(READ_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD3, TXRXPACK_WORD3_TRIGRCV) >> TXRXPACK_WORD3_TRIGRCV_Pos);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD3          TRIGDONE       LL_RADIO_SetTrigDone
  * @param  px RADIO Instance
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetTrigDone(TXRXPACK_TypeDef *p, uint32_t value)
{
  MODIFY_REG_FIELD(((TXRXPACK_WORD_TypeDef*)p)->WORD3, TXRXPACK_WORD3_TRIGDONE, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD3          TRIGDONE       LL_RADIO_GetTrigDone
  * @param  px RADIO Instance
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetTrigDone(TXRXPACK_TypeDef *p)
{
  return (uint32_t)(READ_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD3, TXRXPACK_WORD3_TRIGDONE) >> TXRXPACK_WORD3_TRIGDONE_Pos);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD3          INTTXOK       LL_RADIO_SetIntTxOk
  * @param  px RADIO Instance
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetIntTxOk(TXRXPACK_TypeDef *p, uint32_t value)
{
  MODIFY_REG_FIELD(((TXRXPACK_WORD_TypeDef*)p)->WORD3, TXRXPACK_WORD3_INTTXOK, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD3          INTTXOK       LL_RADIO_GetIntTxOk
  * @param  px RADIO Instance
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetIntTxOk(TXRXPACK_TypeDef *p)
{
  return (uint32_t)(READ_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD3, TXRXPACK_WORD3_INTTXOK) >> TXRXPACK_WORD3_INTTXOK_Pos);
}

/**
  * @brief  RADIO Enable
  * @rmtoll WORD3          INTDONE            LL_RADIO_IntDone_Enable
  * @param  
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_IntDone_Enable(TXRXPACK_TypeDef *p)
{
  SET_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD3, TXRXPACK_WORD3_INTDONE);
}

/**
  * @brief  RADIO Disable
  * @rmtoll WORD3          INTDONE            LL_RADIO_IntDone_Disable
  * @param  
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_IntDone_Disable(TXRXPACK_TypeDef *p)
{ 
  CLEAR_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD3, TXRXPACK_WORD3_INTDONE);
}

/**
  * @brief  Indicate if INTDONE is enabled
  * @rmtoll WORD3          INTDONE            LL_RADIO_IntDone_IsEnabled  
  * @param  
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_IntDone_IsEnabled(TXRXPACK_TypeDef *p)
{
  return ((READ_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD3, TXRXPACK_WORD3_INTDONE) == (TXRXPACK_WORD3_INTDONE)) ? 1U : 0U);
}

/**
  * @brief  RADIO Enable
  * @rmtoll WORD3          INTRCVTIMEOUT            LL_RADIO_IntRcvTimeout_Enable
  * @param  
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_IntRcvTimeout_Enable(TXRXPACK_TypeDef *p)
{
  SET_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD3, TXRXPACK_WORD3_INTRCVTIMEOUT);
}

/**
  * @brief  RADIO Disable
  * @rmtoll WORD3          INTRCVTIMEOUT            LL_RADIO_IntRcvTimeout_Disable
  * @param  
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_IntRcvTimeout_Disable(TXRXPACK_TypeDef *p)
{ 
  CLEAR_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD3, TXRXPACK_WORD3_INTRCVTIMEOUT);
}

/**
  * @brief  Indicate if INTRCVTIMEOUT is enabled
  * @rmtoll WORD3          INTRCVTIMEOUT            LL_RADIO_IntRcvTimeout_IsEnabled  
  * @param  
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_IntRcvTimeout_IsEnabled(TXRXPACK_TypeDef *p)
{
  return ((READ_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD3, TXRXPACK_WORD3_INTRCVTIMEOUT) == (TXRXPACK_WORD3_INTRCVTIMEOUT)) ? 1U : 0U);
}


/**
  * @brief  
  * @note   
  * @rmtoll WORD3          INTTIMECAPTURE       LL_RADIO_SetIntTimeCapture
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_SetIntTimeCapture(TXRXPACK_TypeDef *p, uint32_t value)
{
  MODIFY_REG_FIELD(((TXRXPACK_WORD_TypeDef*)p)->WORD3, TXRXPACK_WORD3_INTTIMECAPTURE, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll WORD3          INTTIMECAPTURE       LL_RADIO_GetIntTimeCapture
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_GetIntTimeCapture(TXRXPACK_TypeDef *p)
{
  return (uint32_t)(READ_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD3, TXRXPACK_WORD3_INTTIMECAPTURE) >> TXRXPACK_WORD3_INTTIMECAPTURE_Pos);
}

/**
  * @brief  RADIO Enable
  * @rmtoll WORD3          INTRCVCRCERR            LL_RADIO_IntRcvCRCErr_Enable
  * @param  
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_IntRcvCRCErr_Enable(TXRXPACK_TypeDef *p)
{
  SET_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD3, TXRXPACK_WORD3_INTRCVCRCERR);
}

/**
  * @brief  RADIO Disable
  * @rmtoll WORD3          INTRCVCRCERR            LL_RADIO_IntRcvCRCErr_Disable
  * @param  
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_IntRcvCRCErr_Disable(TXRXPACK_TypeDef *p)
{ 
  CLEAR_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD3, TXRXPACK_WORD3_INTRCVCRCERR);
}

/**
  * @brief  Indicate if INTRCVCRCERR is enabled
  * @rmtoll WORD3          INTRCVCRCERR            LL_RADIO_IntRcvCRCErr_IsEnabled  
  * @param  
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_IntRcvCRCErr_IsEnabled(TXRXPACK_TypeDef *p)
{
  return ((READ_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD3, TXRXPACK_WORD3_INTRCVCRCERR) == (TXRXPACK_WORD3_INTRCVCRCERR)) ? 1U : 0U);
}

/**
  * @brief  RADIO Enable
  * @rmtoll WORD3          INTRCVOK            LL_RADIO_IntRcvOk_Enable
  * @param  
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_IntRcvOk_Enable(TXRXPACK_TypeDef *p)
{
  SET_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD3, TXRXPACK_WORD3_INTRCVOK);
}

/**
  * @brief  RADIO Disable
  * @rmtoll WORD3          INTRCVOK            LL_RADIO_IntRcvOk_Disable
  * @param  
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_IntRcvOk_Disable(TXRXPACK_TypeDef *p)
{ 
  CLEAR_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD3, TXRXPACK_WORD3_INTRCVOK);
}

/**
  * @brief  Indicate if INTRCVOK is enabled
  * @rmtoll WORD3          INTRCVOK            LL_RADIO_IntRcvOk_IsEnabled  
  * @param  
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RADIO_IntRcvOk_IsEnabled(TXRXPACK_TypeDef *p)
{
  return ((READ_BIT(((TXRXPACK_WORD_TypeDef*)p)->WORD3, TXRXPACK_WORD3_INTRCVOK) == (TXRXPACK_WORD3_INTRCVOK)) ? 1U : 0U);
}

#ifdef BLUE_CONTROLLERVERNUMREG_SUBVERNUM
/**
  * @brief  
  * @note   
  * @rmtoll CONTROLLERVERNUMREG          SUBVERNUM       LL_RADIO_BlueGetSubversionNumber
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_BlueGetSubversionNumber(void)
{
  return (uint32_t)(READ_BIT(BLUE->CONTROLLERVERNUMREG, BLUE_CONTROLLERVERNUMREG_SUBVERNUM) >> BLUE_CONTROLLERVERNUMREG_SUBVERNUM_Pos);
}
#endif

#ifdef BLUE_CONTROLLERVERNUMREG_VERNUM
/**
  * @brief  
  * @note   
  * @rmtoll CONTROLLERVERNUMREG          VERNUM       LL_RADIO_BlueGetVersionNumber
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_BlueGetVersionNumber(void)
{
  return (uint32_t)(READ_BIT(BLUE->CONTROLLERVERNUMREG, BLUE_CONTROLLERVERNUMREG_VERNUM) >> BLUE_CONTROLLERVERNUMREG_VERNUM_Pos);
}
#endif

#ifdef BLUE_CONTROLLERVERNUMREG_TYP
/**
  * @brief  
  * @note   
  * @rmtoll CONTROLLERVERNUMREG          TYP       LL_RADIO_BlueGetBLEControllerTypeNumber
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_BlueGetBLEControllerTypeNumber(void)
{
  return (uint32_t)(READ_BIT(BLUE->CONTROLLERVERNUMREG, BLUE_CONTROLLERVERNUMREG_TYP) >> BLUE_CONTROLLERVERNUMREG_TYP_Pos);
}
#endif

#ifdef BLUE_INTERRUPT1REG_ALL
/**
  * @brief  
  * @note   
  * @rmtoll INTERRUPT1REG          ALL       LL_RADIO_BlueSetInterrupt1RegRegister
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_BlueSetInterrupt1RegRegister(uint32_t value)
{
  MODIFY_REG_FIELD(BLUE->INTERRUPT1REG, BLUE_INTERRUPT1REG_ALL, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll INTERRUPT1REG          ALL       LL_RADIO_BlueGetInterrupt1RegRegister
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_BlueGetInterrupt1RegRegister(void)
{
  return (uint32_t)(READ_BIT(BLUE->INTERRUPT1REG, BLUE_INTERRUPT1REG_ALL) >> BLUE_INTERRUPT1REG_ALL_Pos);
}
#endif

/**
  * @brief  
  * @note   
  * @rmtoll TIMERCAPTUREREG          TIMERCAPTURE       LL_RADIO_BlueGetTimerCapture
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_BlueGetTimerCapture(void)
{
  return (uint32_t)(READ_BIT(BLUE->TIMERCAPTUREREG, BLUE_TIMERCAPTUREREG_TIMERCAPTURE) >> BLUE_TIMERCAPTUREREG_TIMERCAPTURE_Pos);
}

/**
  * @brief  
  * @note   
  * @rmtoll CMDREG          CLEARSEMAREQ       LL_RADIO_BlueSetClearSemaphoreRequest
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_BlueSetClearSemaphoreRequest(uint32_t value)
{
  MODIFY_REG_FIELD(BLUE->CMDREG, BLUE_CMDREG_CLEARSEMAREQ, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll CMDREG          CLEARSEMAREQ       LL_RADIO_BlueGetClearSemaphoreRequest
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_BlueGetClearSemaphoreRequest(void)
{
  return (uint32_t)(READ_BIT(BLUE->CMDREG, BLUE_CMDREG_CLEARSEMAREQ) >> BLUE_CMDREG_CLEARSEMAREQ_Pos);
}


/**
  * @brief  
  * @note   
  * @rmtoll STATUSREG          ACTIVE2ERROR       LL_RADIO_BlueGetActive2Error
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_BlueGetActive2Error(void)
{
  return (uint32_t)(READ_BIT(BLUE->STATUSREG, BLUE_STATUSREG_ACTIVE2ERROR) >> BLUE_STATUSREG_ACTIVE2ERROR_Pos);
}

/**
  * @brief  
  * @note   
  * @rmtoll INTERRUPT1LATENCYREG          INTERRUPT1LATENCY       LL_RADIO_BlueGetInterrupt1Latency
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_BlueGetInterrupt1Latency(void)
{
  return (uint32_t)(READ_BIT(BLUE->INTERRUPT1LATENCYREG, BLUE_INTERRUPT1LATENCYREG_INTERRUPT1LATENCY) >> BLUE_INTERRUPT1LATENCYREG_INTERRUPT1LATENCY_Pos);
}

/**
  * @brief  
  * @note   
  * @rmtoll MANAESKEY0REG          MANAESKEY_31_0       LL_RADIO_BlueSetManualAesKey_31_0
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_BlueSetManualAesKey_31_0(uint32_t value)
{
  MODIFY_REG_FIELD(BLUE->MANAESKEY0REG, BLUE_MANAESKEY0REG_MANAESKEY_31_0, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll MANAESKEY0REG          MANAESKEY_31_0       LL_RADIO_BlueGetManualAesKey_31_0
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_BlueGetManualAesKey_31_0(void)
{
  return (uint32_t)(READ_BIT(BLUE->MANAESKEY0REG, BLUE_MANAESKEY0REG_MANAESKEY_31_0) >> BLUE_MANAESKEY0REG_MANAESKEY_31_0_Pos);
}

/**
  * @brief  
  * @note   
  * @rmtoll MANAESCMDREG          START       LL_RADIO_BlueSetManAESCmdStart
  * @param  value
  * @retval None
  */
__STATIC_INLINE void LL_RADIO_BlueSetManAESCmdStart(uint32_t value)
{
  MODIFY_REG_FIELD(BLUE->MANAESCMDREG, BLUE_MANAESCMDREG_START, value);
}

/**
  * @brief  
  * @note   
  * @rmtoll MANAESCMDREG          START       LL_RADIO_BlueGetManAESCmdStart
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_BlueGetManAESCmdStart(void)
{
  return (uint32_t)(READ_BIT(BLUE->MANAESCMDREG, BLUE_MANAESCMDREG_START) >> BLUE_MANAESCMDREG_START_Pos);
}

/**
  * @brief  
  * @note   
  * @rmtoll MANAESSTATREG          BUSY       LL_RADIO_BlueGetManAESStatusBusy
  * @retval 
  */
__STATIC_INLINE uint32_t LL_RADIO_BlueGetManAESStatusBusy(void)
{
  return (uint32_t)(READ_BIT(BLUE->MANAESSTATREG, BLUE_MANAESSTATREG_BUSY) >> BLUE_MANAESSTATREG_BUSY_Pos);
}

#ifdef BLUE_STATUS2REG_IQSAMPLES_READY
/**
  * @brief  
  * @note   
  * @rmtoll STATUS2REG          IQSAMPLES_READY       LL_BLUE_GetIQSamplesReady
  * @retval 
  */
__STATIC_INLINE uint32_t LL_BLUE_GetIQSamplesReady(void)
{
  return (uint32_t)(READ_BIT(BLUE->STATUS2REG, BLUE_STATUS2REG_IQSAMPLES_READY) >> BLUE_STATUS2REG_IQSAMPLES_READY_Pos);
}
#endif

#ifdef BLUE_STATUS2REG_IQSAMPLES_NUMBER
/**
  * @brief  
  * @note   
  * @rmtoll STATUS2REG          IQSAMPLES_NUMBER       LL_BLUE_GetIQSamplesNumber
  * @retval 
  */
__STATIC_INLINE uint32_t LL_BLUE_GetIQSamplesNumber(void)
{
  return (uint32_t)(READ_BIT(BLUE->STATUS2REG, BLUE_STATUS2REG_IQSAMPLES_NUMBER) >> BLUE_STATUS2REG_IQSAMPLES_NUMBER_Pos);
}
#endif

#ifdef BLUE_STATUS2REG_IQSAMPLES_MISSING_ERROR
/**
  * @brief  
  * @note   
  * @rmtoll STATUS2REG          IQSAMPLES_MISSING_ERROR       LL_BLUE_GetIQSamplesMissingError
  * @retval 
  */
__STATIC_INLINE uint32_t LL_BLUE_GetIQSamplesMissingError(void)
{
  return (uint32_t)(READ_BIT(BLUE->STATUS2REG, BLUE_STATUS2REG_IQSAMPLES_MISSING_ERROR) >> BLUE_STATUS2REG_IQSAMPLES_MISSING_ERROR_Pos);
}
#endif

#ifdef BLUE_STATUS2REG_ANTENNA_SWITCHING_PATTERN_ACCESS_ERROR
/**
  * @brief  
  * @note   
  * @rmtoll STATUS2REG          ANTENNA_SWITCHING_PATTERN_ACCESS_ERROR       LL_BLUE_GetAntennaSwitchingPatternAccessError
  * @retval 
  */
__STATIC_INLINE uint32_t LL_BLUE_GetAntennaSwitchingPatternAccessError(void)
{
  return (uint32_t)(READ_BIT(BLUE->STATUS2REG, BLUE_STATUS2REG_ANTENNA_SWITCHING_PATTERN_ACCESS_ERROR) >> BLUE_STATUS2REG_ANTENNA_SWITCHING_PATTERN_ACCESS_ERROR_Pos);
}
#endif


#ifdef BLUE_STATUS2REG_ANTENNA_SWITCHING_PATTERN_ADDRESS_ERROR
/**
  * @brief  
  * @note   
  * @rmtoll STATUS2REG          ANTENNA_SWITCHING_PATTERN_ADDRESS_ERROR       LL_BLUE_GetAntennaSwitchingPatternAddressError
  * @retval 
  */
__STATIC_INLINE uint32_t LL_BLUE_GetAntennaSwitchingPatternAddressError(void)
{
  return (uint32_t)(READ_BIT(BLUE->STATUS2REG, BLUE_STATUS2REG_ANTENNA_SWITCHING_PATTERN_ADDRESS_ERROR) >> BLUE_STATUS2REG_ANTENNA_SWITCHING_PATTERN_ADDRESS_ERROR_Pos);
}
#endif 


/**
* @}
*/

void RADIO_Init(void);
uint8_t RADIO_GetStatus(uint32_t *time);
void RADIO_SetChannelMap(uint8_t StateMachineNo,uint8_t *chan_remap);
void RADIO_SetChannel(uint8_t StateMachineNo, uint8_t channel,uint8_t channel_increment); 
void RADIO_SetTxAttributes(uint8_t StateMachineNo, uint32_t NetworkID, uint32_t crc_init);
void RADIO_SetMaxReceivedLength(uint8_t StateMachineNo, uint8_t MaxReceivedLength);
void RADIO_SetBackToBackTime(uint32_t back_to_back_time);  
void RADIO_SetPhy(uint8_t StateMachineNo, uint8_t phy);
void RADIO_SetTxPower(uint8_t PowerLevel);    
void RADIO_IRQHandler(void);
uint8_t RADIO_StopActivity(void);
void RADIO_SetGlobalReceiveTimeout(uint32_t ReceiveTimeout);
void RADIO_SetReservedArea(ActionPacket *p); 
uint8_t RADIO_MakeActionPacketPending(ActionPacket *p);
uint8_t RADIO_StartTone(uint8_t RF_channel, uint8_t powerLevel, uint8_t freq_offset);
uint8_t RADIO_StopTone(void);
void RADIO_SetEncryptionCount(uint8_t StateMachineNo, uint8_t *count_tx, uint8_t *count_rcv);    
void RADIO_SetEncryptionAttributes(uint8_t StateMachineNo, uint8_t *enc_iv, uint8_t *enc_key); 
void RADIO_SetEncryptFlags(uint8_t StateMachineNo, FunctionalState EncryptFlagTx, FunctionalState EncryptFlagRcv);
void RADIO_EncryptPlainData(uint8_t *Key, uint8_t *plainData, uint8_t *cypherData);
void RADIO_SetDefaultPreambleLen(uint8_t StateMachineNo);
void RADIO_SetPreambleRep(uint8_t StateMachineNo, uint8_t PreaLen);
void RADIO_DisableCRC(uint8_t StateMachineNo, FunctionalState hwCRC);
int8_t RADIO_ReadRSSI(void);

/**
  * @}
  */

/**
  * @}
  */ 

/**
  * @}
  */ 

#ifdef __cplusplus
}
#endif

#endif /*RF_DRIVER_LL_RADIO_H */

/******************* (C) COPYRIGHT 2020 STMicroelectronics *****END OF FILE****/
