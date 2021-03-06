/*************************************************************************************************/
/*!
 *  \file   smp_api.h
 *
 *  \brief  SMP subsystem API.
 *
 *          $Date: 2015-06-12 07:19:18 -0400 (Fri, 12 Jun 2015) $
 *          $Revision: 3061 $
 *
 * Copyright (c) 2009-2016, ARM Limited, All Rights Reserved
 * SPDX-License-Identifier: LicenseRef-PBL
 *
 * This file and the related binary are licensed under the
 * Permissive Binary License, Version 1.0 (the "License");
 * you may not use these files except in compliance with the License.
 *
 * You may obtain a copy of the License here:
 * LICENSE-permissive-binary-license-1.0.txt and at
 * https://www.mbed.com/licenses/PBL-1.0
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*************************************************************************************************/
#ifndef SMP_API_H
#define SMP_API_H

#include "wsf_os.h"
#include "smp_defs.h"
#include "dm_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************************************
  Macros
**************************************************************************************************/

/*! Event handler messages for SMP state machines */
enum
{
  SMP_MSG_API_PAIR_REQ = 1,               /*! API pairing request */
  SMP_MSG_API_PAIR_RSP,                   /*! API pairing response */
  SMP_MSG_API_CANCEL_REQ,                 /*! API cancel request */
  SMP_MSG_API_AUTH_RSP,                   /*! API pin response */
  SMP_MSG_API_SECURITY_REQ,               /*! API security request */
  SMP_MSG_CMD_PKT,                        /*! SMP command packet received */
  SMP_MSG_CMD_PAIRING_FAILED,             /*! SMP pairing failed packet received */
  SMP_MSG_DM_ENCRYPT_CMPL,                /*! Link encrypted */
  SMP_MSG_DM_ENCRYPT_FAILED,              /*! Link encryption failed */
  SMP_MSG_DM_CONN_CLOSE,                  /*! Connection closed */
  SMP_MSG_WSF_AES_CMPL,                   /*! AES calculation complete */
  SMP_MSG_INT_SEND_NEXT_KEY,              /*! Send next key to be distributed */
  SMP_MSG_INT_MAX_ATTEMPTS,               /*! Maximum pairing attempts reached */
  SMP_MSG_INT_PAIRING_CMPL,               /*! Pairing complete */
  SMP_MSG_INT_TIMEOUT,                    /*! Pairing protocol timeout */
  SMP_MSG_INT_LESC,                       /*! Pair with Secure Connections */
  SMP_MSG_INT_LEGACY,                     /*! Pair with Legacy Security */
  SMP_MSG_INT_JW_NC,                      /*! LESC Just-Works/Numeric Comparison pairing */
  SMP_MSG_INT_PASSKEY,                    /*! LESC Passkey pairing */
  SMP_MSG_INT_OOB,                        /*! LESC Out-of-Band Pairing */
  SMP_MSG_API_USER_CONFIRM,               /*! User confirms valid numeric comparison */
  SMP_MSG_API_USER_KEYPRESS,              /*! User keypress in passkey pairing */
  SMP_MSG_API_KEYPRESS_CMPL,              /*! User keypress complete in passkey pairing */
  SMP_MSG_WSF_ECC_CMPL,                   /*! WSF ECC operation complete */
  SMP_MSG_INT_PK_NEXT,                    /*! Continue to next passkey bit */
  SMP_MSG_INT_PK_CMPL,                    /*! Passkey operation complete */
  SMP_MSG_WSF_CMAC_CMPL,                  /*! WSF CMAC operation complete */
  SMP_MSG_DH_CHECK_FAILURE,               /*! WSF CMAC operation complete */
  SMP_NUM_MSGS
};

/**************************************************************************************************
  Data Types
**************************************************************************************************/

/*! Configurable parameters */
typedef struct
{
  uint16_t            attemptTimeout;     /*! 'Repeated attempts' timeout in msec */
  uint8_t             ioCap;              /*! I/O Capability */
  uint8_t             minKeyLen;          /*! Minimum encryption key length */
  uint8_t             maxKeyLen;          /*! Maximum encryption key length */
  uint8_t             maxAttempts;        /*! Attempts to trigger 'repeated attempts' timeout */
  uint8_t             auth;               /*! Device authentication requirements */
} smpCfg_t;

/*! Data type for SMP_MSG_API_PAIR_REQ and SMP_MSG_API_PAIR_RSP */
typedef struct
{
  wsfMsgHdr_t         hdr;
  uint8_t             oob;
  uint8_t             auth;
  uint8_t             iKeyDist;
  uint8_t             rKeyDist;
} smpDmPair_t;

/*! Data type for SMP_MSG_API_AUTH_RSP */
typedef struct
{
  wsfMsgHdr_t         hdr;
  uint8_t             authData[SMP_OOB_LEN];
  uint8_t             authDataLen;
} smpDmAuthRsp_t;

/*! Data type for SMP_MSG_API_USER_KEYPRESS */
typedef struct
{
  wsfMsgHdr_t         hdr;
  uint8_t             keypress;
} smpDmKeypress_t;

/*! Data type for SMP_MSG_API_SECURITY_REQ */
typedef struct
{
  wsfMsgHdr_t         hdr;
  uint8_t             auth;
} smpDmSecurityReq_t;

/*! Union SMP DM message data types */
typedef union
{
  wsfMsgHdr_t         hdr;
  smpDmPair_t         pair;
  smpDmAuthRsp_t      authRsp;
  smpDmSecurityReq_t  securityReq;
  smpDmKeypress_t     keypress;
} smpDmMsg_t;

/**************************************************************************************************
  Global Variables;
**************************************************************************************************/

/*! Configuration pointer */
extern smpCfg_t *pSmpCfg;

/**************************************************************************************************
  Function Declarations
**************************************************************************************************/

/*************************************************************************************************/
/*!
 *  \fn     SmpiInit
 *
 *  \brief  Initialize SMP initiator role.
 *
 *  \return None.
 */
/*************************************************************************************************/
void SmpiInit(void);

/*************************************************************************************************/
/*!
 *  \fn     SmprInit
 *
 *  \brief  Initialize SMP responder role.
 *
 *  \return None.
 */
/*************************************************************************************************/
void SmprInit(void);

/*************************************************************************************************/
/*!
 *  \fn     SmpiScInit
 *
 *  \brief  Initialize SMP initiator role utilizing BTLE Secure Connections.
 *
 *  \return None.
 */
/*************************************************************************************************/
void SmpiScInit(void);

/*************************************************************************************************/
/*!
 *  \fn     SmprScInit
 *
 *  \brief  Initialize SMP responder role utilizing BTLE Secure Connections.
 *
 *  \return None.
 */
/*************************************************************************************************/
void SmprScInit(void);

/*************************************************************************************************/
/*!
 *  \fn     SmpNonInit
 *
 *  \brief  Use this SMP init function when SMP is not supported.
 *
 *  \return None.
 */
/*************************************************************************************************/
void SmpNonInit(void);

/*************************************************************************************************/
/*!
 *  \fn     SmpDmMsgSend
 *
 *  \brief  This function is called by DM to send a message to SMP.
 *
 *  \param  pMsg      Pointer to message structure.
 *
 *  \return None.
 */
/*************************************************************************************************/
void SmpDmMsgSend(smpDmMsg_t *pMsg);

/*************************************************************************************************/
/*!
 *  \fn     SmpDmEncryptInd
 *
 *  \brief  This function is called by DM to notify SMP of encrypted link status.
 *
 *  \param  pMsg    Pointer to HCI message structure.
 *
 *  \return None.
 */
/*************************************************************************************************/
void SmpDmEncryptInd(wsfMsgHdr_t *pMsg);

/*************************************************************************************************/
/*!
 *  \fn     SmpDmGetStk
 *
 *  \brief  Return the STK for the given connection.
 *
 *  \param  connId    Connection identifier.
 *  \param  pSecLevel Returns the security level of pairing when STK was created.
 *
 *  \return Pointer to STK or NULL if not available.
 */
/*************************************************************************************************/
uint8_t *SmpDmGetStk(dmConnId_t connId, uint8_t *pSecLevel);

#ifdef __cplusplus
};
#endif

#endif /* SMP_API_H */
