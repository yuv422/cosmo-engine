//
// Created by Eric Fry on 1/11/2017.
//

#ifndef COSMO_ENGINE_VOL_H
#define COSMO_ENGINE_VOL_H

#include "defines.h"

unsigned char *vol_file_extract_by_name(const char *vol_filename, const char *filename, uint32 *bytesRead);

unsigned char *vol_file_load(const char *vol_filename, const char *filename, unsigned char *buffer, uint32 buffer_size);

#endif //COSMO_ENGINE_VOL_H
