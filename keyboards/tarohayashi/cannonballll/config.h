// Copyright 2025 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#define RGBLIGHT_LAYERS_RETAIN_VAL
#define RGBLIGHT_DEFAULT_VAL 30

#define MATRIX_ROWS 2
#define MATRIX_COLS 18

#define SPI_DRIVER SPID1
#define SPI_SCK_PIN     GP10
#define SPI_MOSI_PIN    GP11
#define SPI_MISO_PIN    NO_PIN
#define SPI_MODE 3

#define SHIFTREG_MATRIX_COL_CS  GP13
#define SHIFTREG_DIVISOR        32
#define SHIFTREG_ROWS           2
#define SHIFTREG_COLS           15

#define MATRIX_ROW_PINS_SR { GP2, GP3 }

//            0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000
//            1QA     1QB     1QC     1QD     1QE     1QF     1QG     1QH     2QA     2QB     2QC     2QD     2QE     2QF     2QG     2QH
#define COLS {0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000}
