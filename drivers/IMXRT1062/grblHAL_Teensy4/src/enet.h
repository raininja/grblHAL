/*
  enet.h - lwIP driver glue code for IMXRT1062 processor (on Teensy 4.1 board)

  Part of GrblHAL

  Copyright (c) 2020 Terje Io

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __ENET_H__
#define __ENET_H__

#include "driver.h"

bool grbl_enet_init (network_settings_t *network);
void grbl_enet_poll (void);
char *enet_ip_address (void);
status_code_t ethernet_setting (setting_type_t param, float value, char *svalue);
void ethernet_settings_report (setting_type_t setting);
void ethernet_settings_restore (void);

#endif
