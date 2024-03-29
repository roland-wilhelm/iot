/*****************************************************************************
* Product: QF/C
* Last Updated for Version: 4.1.05
* Date of the Last Update:  Oct 27, 2010
*
*                    Q u a n t u m     L e a P s
*                    ---------------------------
*                    innovating embedded systems
*
* Copyright (C) 2002-2010 Quantum Leaps, LLC. All rights reserved.
*
* This software may be distributed and modified under the terms of the GNU
* General Public License version 2 (GPL) as published by the Free Software
* Foundation and appearing in the file GPL.TXT included in the packaging of
* this file. Please note that GPL Section 2[b] requires that all works based
* on this software must also be made publicly available under the terms of
* the GPL ("Copyleft").
*
* Alternatively, this software may be distributed and modified under the
* terms of Quantum Leaps commercial licenses, which expressly supersede
* the GPL and are specifically designed for licensees interested in
* retaining the proprietary status of their code.
*
* Contact information:
* Quantum Leaps Web site:  http://www.quantum-leaps.com
* e-mail:                  info@quantum-leaps.com
*****************************************************************************/
#include "qf_pkg.h"

/**
* \file
* \ingroup qf
* \brief QF_pwr2Lkup[], QF_invPwr2Lkup[], and QF_div8Lkup[] definitions.
*/

/* Global objects ----------------------------------------------------------*/
uint8_t const Q_ROM Q_ROM_VAR QF_pwr2Lkup[65] = {
    0x00U,                                               /* unused location */
    0x01U, 0x02U, 0x04U, 0x08U, 0x10U, 0x20U, 0x40U, 0x80U,
    0x01U, 0x02U, 0x04U, 0x08U, 0x10U, 0x20U, 0x40U, 0x80U,
    0x01U, 0x02U, 0x04U, 0x08U, 0x10U, 0x20U, 0x40U, 0x80U,
    0x01U, 0x02U, 0x04U, 0x08U, 0x10U, 0x20U, 0x40U, 0x80U,
    0x01U, 0x02U, 0x04U, 0x08U, 0x10U, 0x20U, 0x40U, 0x80U,
    0x01U, 0x02U, 0x04U, 0x08U, 0x10U, 0x20U, 0x40U, 0x80U,
    0x01U, 0x02U, 0x04U, 0x08U, 0x10U, 0x20U, 0x40U, 0x80U,
    0x01U, 0x02U, 0x04U, 0x08U, 0x10U, 0x20U, 0x40U, 0x80U
};

uint8_t const Q_ROM Q_ROM_VAR QF_invPwr2Lkup[65] = {
    0xFFU,                                               /* unused location */
    0xFEU, 0xFDU, 0xFBU, 0xF7U, 0xEFU, 0xDFU, 0xBFU, 0x7FU,
    0xFEU, 0xFDU, 0xFBU, 0xF7U, 0xEFU, 0xDFU, 0xBFU, 0x7FU,
    0xFEU, 0xFDU, 0xFBU, 0xF7U, 0xEFU, 0xDFU, 0xBFU, 0x7FU,
    0xFEU, 0xFDU, 0xFBU, 0xF7U, 0xEFU, 0xDFU, 0xBFU, 0x7FU,
    0xFEU, 0xFDU, 0xFBU, 0xF7U, 0xEFU, 0xDFU, 0xBFU, 0x7FU,
    0xFEU, 0xFDU, 0xFBU, 0xF7U, 0xEFU, 0xDFU, 0xBFU, 0x7FU,
    0xFEU, 0xFDU, 0xFBU, 0xF7U, 0xEFU, 0xDFU, 0xBFU, 0x7FU,
    0xFEU, 0xFDU, 0xFBU, 0xF7U, 0xEFU, 0xDFU, 0xBFU, 0x7FU
};

uint8_t const Q_ROM Q_ROM_VAR QF_div8Lkup[65] = {
    0U,                                                  /* unused location */
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U,
    2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U,
    3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U,
    4U, 4U, 4U, 4U, 4U, 4U, 4U, 4U,
    5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U,
    6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U,
    7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U
};
