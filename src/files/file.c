//
// Created by Eric Fry on 1/11/2017.
//

#include "file.h"

uint32 calculate_filesize(FILE *fp) {
    uint32 file_length;

    fseek(fp, 0, SEEK_END);
    file_length = (uint32)ftell(fp);
    fseek(fp, 0, SEEK_SET);

    return file_length;
}

bool file_open(const char *filename, const char *mode, File *file) {
    if(file->fp) //We already have a file open lets bail.
        return false;

    file->fp = fopen(filename,mode);

    if(file->fp == NULL)
    {
        printf("Failed opening '%s'\n",filename);
        return false;
    }

    file->size = calculate_filesize(file->fp);
    file->pos = 0;

    return true;
}

uint32 file_get_filesize(File *file) {
    return file->fp != NULL ? file->size : 0;
}

uint8 file_read1(File *file) {
    if(!file->fp || file->pos >= file->size)
        return 0;

    file->pos++;

    return(uint8)fgetc(file->fp);
}

uint16 file_read2(File *file) {
    uint8 b0, b1;

    if(!file->fp || file->pos > file->size-2)
        return 0;

    file->pos += 2;

    b0 = (uint8)fgetc(file->fp);
    b1 = (uint8)fgetc(file->fp);

    return (b0 + (b1<<8));
}

uint32 file_read4(File *file) {
    uint8 b0, b1, b2, b3;
    if(!file->fp || file->pos > file->size-4)
        return 0;

    file->pos += 4;

    b0 = (uint8)fgetc(file->fp);
    b1 = (uint8)fgetc(file->fp);
    b2 = (uint8)fgetc(file->fp);
    b3 = (uint8)fgetc(file->fp);

    return (b0 + (b1<<8) + (b2<<16) + (b3<<24));
}

bool file_read_to_buffer(File *file, unsigned char *buf, uint32 buf_size) {
    if(file->pos + buf_size > file->size)
        return false;

    fread(buf,1,buf_size,file->fp); // FIX for partial read.

    file->pos += buf_size;

    return true;
}

void file_close(File *file) {
    if(file->fp)
    {
        fclose(file->fp);
        file->fp = NULL;
    }
}

void file_seek(File *file, uint32 new_position) {
    if(file->fp && new_position <= file->size)
    {
        fseek(file->fp,new_position,SEEK_SET);
        file->pos = new_position;
    }

    return;
}

