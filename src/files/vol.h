/*
 *  Cosmo-Engine
 *  Copyright Eric Fry (c) 2017. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#ifndef COSMO_ENGINE_VOL_H
#define COSMO_ENGINE_VOL_H

#include "defines.h"
#include "file.h"

unsigned char *vol_file_extract_by_name(const char *vol_filename, const char *filename, uint32 *bytes_read);

unsigned char *vol_file_load(const char *vol_filename, const char *filename, unsigned char *buffer, uint32 buffer_size, uint32 *bytes_read);

bool vol_file_open(const char *vol_filename, const char *filename, File *file);

#endif //COSMO_ENGINE_VOL_H
