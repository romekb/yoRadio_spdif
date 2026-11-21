/*
    This example code is in the Public Domain (or CC0 licensed, at your option.)

    Unless required by applicable law or agreed to in writing, this
    software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
    CONDITIONS OF ANY KIND, either express or implied.
*/

#pragma once
#pragma GCC optimize ("Ofast")
#include "Arduino.h"
#include "assert.h"
#include <stdint.h>
#include <sys/types.h>

/*
 * initialize S/PDIF driver
 *   rate: sampling rate, 44100Hz, 48000Hz etc.
 */ 
void spdif_init(int rate);

/*
 * Queue one 16-bit stereo PCM frame for the asynchronous S/PDIF transmitter.
 * Returns false if the S/PDIF output task is not initialized.
 */
bool spdif_write(int16_t smp[2]);
void spdif_set_sample_rate(uint32_t rate);
void spdif_clear_queue();
void spdif_set_ftp_mode(bool active);
