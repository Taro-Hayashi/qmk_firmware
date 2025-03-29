// Copyright 2022 @sadekbaroudi (Sadek Baroudi)
// Copyright 2023 @jasonhazel (Jason Hazel)
// Copyright 2025 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-3.0-or-later

/* The centre push is connected to GP14 and is scanned by (1,17) through the diode */

#include "quantum.h"

#include "spi_master.h"
#include "wait.h"

static const uint16_t col_values[SHIFTREG_COLS] = COLS;

int matrixArraySize = SHIFTREG_ROWS * sizeof(matrix_row_t);
matrix_row_t oldMatrix[SHIFTREG_ROWS];

#define SHIFTREG_OUTPUT_BITS 8
pin_t rowPinsSR[SHIFTREG_ROWS] = MATRIX_ROW_PINS_SR;

// semaphore to make sure SPI doesn't get called multiple times
static bool shiftRegisterSPILocked = false;

void semaphore_lock(bool value) {
    shiftRegisterSPILocked = value;
}

bool semaphore_is_locked(void) {
    return shiftRegisterSPILocked;
}

void sr_74hc595_spi_stop(void) {
    spi_stop();
    semaphore_lock(false);
}

bool sr_74hc595_spi_start(void) {
    if (!spi_start(SHIFTREG_MATRIX_COL_CS, false, 0, SHIFTREG_DIVISOR)) {
        sr_74hc595_spi_stop();
        return false;
    }
    semaphore_lock(true);
    wait_us(1);
    return true;
}

bool sr_74hc595_spi_send_byte(uint16_t value) {
    uint8_t message[2] = {(value >> 8) & 0xFF, (uint8_t)(value & 0xFF)};

    sr_74hc595_spi_start();
    gpio_write_pin_low(SHIFTREG_MATRIX_COL_CS);
    matrix_io_delay();
    spi_transmit(message, 2);
    matrix_io_delay();
    gpio_write_pin_high(SHIFTREG_MATRIX_COL_CS);
    sr_74hc595_spi_stop();
    return true;
}

void clearColumns(void) {
    uint8_t message[2] = {0b00000000, 0b00000000};

    sr_74hc595_spi_start();
    gpio_write_pin_low(SHIFTREG_MATRIX_COL_CS);
    matrix_io_delay();
    spi_transmit(message, 2);
    matrix_io_delay();
    gpio_write_pin_high(SHIFTREG_MATRIX_COL_CS);
    sr_74hc595_spi_stop();
}

void setColumn(int col) {
    sr_74hc595_spi_send_byte(col_values[col]);
}

void matrix_init_custom(void) {
    wait_ms(300);
    spi_init();
    for (int r = 0; r < SHIFTREG_ROWS; r++) {
        gpio_set_pin_input_low(rowPinsSR[r]);
    }

    gpio_write_pin_high(SHIFTREG_MATRIX_COL_CS);
    gpio_set_pin_output(SHIFTREG_MATRIX_COL_CS);
    // リセットボタン
    gpio_set_pin_input_high(GP12);
    // スライドスイッチ
    gpio_set_pin_input_high(GP9);

    clearColumns();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    if (semaphore_is_locked()) {
        return false;
    }

    bool matrix_has_changed = false;

    memset(current_matrix, 0, matrixArraySize);

    for (int c = 0; c < SHIFTREG_COLS; c++) {
        setColumn(c);
        matrix_io_delay();

        for (int r = 0; r < SHIFTREG_ROWS; r++) {
            current_matrix[r] |= ((gpio_read_pin(rowPinsSR[r]) ? 1 : 0) << c);
        }
    }

    // リセットボタン
    current_matrix[0] |= ((gpio_read_pin(GP12) ? 0 : 1) << 15);
    // スライドスイッチ
    current_matrix[0] |= ((gpio_read_pin(GP9) ? 0 : 1) << 16);

    matrix_has_changed = memcmp(current_matrix, oldMatrix, matrixArraySize) != 0;
    memcpy(oldMatrix, current_matrix, matrixArraySize);

    if (matrix_has_changed) {
        matrix_print();
    }

    clearColumns();
    matrix_io_delay();

    return matrix_has_changed;
}
