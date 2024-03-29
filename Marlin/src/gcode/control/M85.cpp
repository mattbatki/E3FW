/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "../gcode.h"

/**
 * M85: Set inactivity shutdown timer with parameter S<seconds>. To disable set zero (default)
 */
void GcodeSuite::M85() {

  if (parser.seen('S')) {
    reset_stepper_timeout();
    const millis_t ms = parser.value_millis_from_seconds();
    #if LASER_SAFETY_TIMEOUT_MS > 0
      if (ms && ms <= LASER_SAFETY_TIMEOUT_MS) {
        SERIAL_ECHO_MSG(GCODE_ERR_MSG("M85 timeout must be > ", MS_TO_SEC(LASER_SAFETY_TIMEOUT_MS + 999), " s for laser safety."));
        return;
      }
    #endif
    max_inactive_time = ms;
  }
  else {
    #if DISABLED(MARLIN_SMALL_BUILD)
      SERIAL_ECHOLNPGM("Inactivity timeout ", MS_TO_SEC(max_inactive_time), " s.");
    #endif
  }

}
