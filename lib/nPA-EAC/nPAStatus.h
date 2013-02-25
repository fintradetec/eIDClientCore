/*
 * Copyright (C) 2012 Bundesdruckerei GmbH
 */

#if !defined(__NPASTATUS_INCLUDED__)
#define _NPASTATUS_INCLUDED__

#include "eCardCore/eCardStatus.h"

#define ECARD_INVALID_EPA                         ECARD_MAKE_USER_ERROR(0x001)

// PACE related errors
#define ECARD_EFCARDACCESS_PARSER_ERROR           ECARD_MAKE_USER_ERROR(0x002)
#define ECARD_PACE_STEP_B_FAILED                  ECARD_MAKE_USER_ERROR(0x003)
#define ECARD_PACE_STEP_C_FAILED                  ECARD_MAKE_USER_ERROR(0x004)
#define ECARD_PACE_STEP_C_DECRYPTION_FAILED       ECARD_MAKE_USER_ERROR(0x005)
#define ECARD_PACE_STEP_D_FAILED                  ECARD_MAKE_USER_ERROR(0x006)
#define ECARD_PACE_STEP_E_FAILED                  ECARD_MAKE_USER_ERROR(0x007)
#define ECARD_PACE_STEP_F_FAILED                  ECARD_MAKE_USER_ERROR(0x008)
#define ECARD_PACE_STEP_F_VERIFICATION_FAILED     ECARD_MAKE_USER_ERROR(0x009)

// Terminal Authentication related errors
#define ECARD_TA_STEP_A_FAILED                    ECARD_MAKE_USER_ERROR(0x00A)
#define ECARD_TA_STEP_A_VERIFY_FAILED             ECARD_MAKE_USER_ERROR(0x00B)
#define ECARD_TA_STEP_B_FAILED                    ECARD_MAKE_USER_ERROR(0x00C)
#define ECARD_TA_STEP_B_INVALID_CERTIFCATE_FORMAT ECARD_MAKE_USER_ERROR(0x00D)
#define ECARD_TA_STEP_B_VERIFY_FAILED             ECARD_MAKE_USER_ERROR(0x00E)
#define ECARD_TA_STEP_C_FAILED                    ECARD_MAKE_USER_ERROR(0x00F)
#define ECARD_TA_STEP_C_VERIFY_FAILED             ECARD_MAKE_USER_ERROR(0x010)
#define ECARD_TA_STEP_D_FAILED                    ECARD_MAKE_USER_ERROR(0x011)
#define ECARD_TA_STEP_D_VERIFY_FAILED             ECARD_MAKE_USER_ERROR(0x012)
#define ECARD_TA_STEP_D_INVALID_CERTIFCATE_FORMAT ECARD_MAKE_USER_ERROR(0x013)
#define ECARD_TA_STEP_E_FAILED                    ECARD_MAKE_USER_ERROR(0x014)
#define ECARD_TA_STEP_E_VERIFY_FAILED             ECARD_MAKE_USER_ERROR(0x015)
#define ECARD_TA_STEP_F_FAILED                    ECARD_MAKE_USER_ERROR(0x016)
#define ECARD_TA_STEP_F_VERIFY_FAILED             ECARD_MAKE_USER_ERROR(0x017)
#define ECARD_TA_STEP_G_FAILED                    ECARD_MAKE_USER_ERROR(0x018)
#define ECARD_TA_STEP_G_VERIFY_FAILED             ECARD_MAKE_USER_ERROR(0x019)

// Chip Authentication related errors
#define ECARD_CA_STEP_B_FAILED                    ECARD_MAKE_USER_ERROR(0x01A)
#define ECARD_CA_STEP_B_VERIFY_FAILED             ECARD_MAKE_USER_ERROR(0x01B)
#define ECARD_EFCARDSECURYITY_PARSER_ERROR        ECARD_MAKE_USER_ERROR(0x01C)
#define ECARD_VERIFY_RESPONSE_FAILED              ECARD_MAKE_USER_ERROR(0x01D)

// PIN Management related errors
#define ECARD_CHANGE_PIN_FAILED                   ECARD_MAKE_USER_ERROR(0x020)

#define ECARD_PIN_DEACTIVATED					  ECARD_MAKE_USER_ERROR(0x021)
#endif
