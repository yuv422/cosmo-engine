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

#ifndef COSMO_ENGINE_FILE_H
#define COSMO_ENGINE_FILE_H

#include <stdio.h>
#include <stdbool.h>
#include "defines.h"

typedef struct {
    FILE *fp;
    uint32 size;
    uint32 pos;
    uint32 initial_offset;
} File;

bool file_open(const char *filename, const char *mode, File *file); //FIXME is bool c99?
bool file_open_at_offset(const char *filename, const char *mode, File *file, uint32 offset, uint32 size); //FIXME is bool c99?
uint32 file_get_filesize(File *file);
uint32 file_get_current_position(File *file);

void file_seek(File *file, uint32 new_position);
uint8 file_read1(File *file);
uint16 file_read2(File *file);
uint32 file_read4(File *file);
uint32 file_read_to_buffer(File *file, unsigned char *buf, uint32 num_bytes);

void file_write1(uint8 byte, File *file);
void file_write2(uint16 word, File *file);
void file_write4(uint32 double_word, File *file);

void file_close(File *file);

#endif //COSMO_ENGINE_FILE_H
