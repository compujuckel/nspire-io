/**
 * @file registry.c
 * @author  Julian Mackeben aka compu <compujuckel@googlemail.com>
 * @version 2.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * Store/Get binary data from files
 */
#include <os.h>
#include "nspireio2.h"

int reg_store(void* dataptr, size_t size, char* regpath)
{
	FILE* file;
	
	file = fopen(regpath,"wb");
	if(file == NULL)
		return -1;
	fwrite(dataptr,1,size,file);
	fclose(file);
	
	return 0;
}

void* reg_get(char* regpath)
{
	struct stat fstat;
	void* result;
	FILE* file;
	
	if(stat(regpath,&fstat) == -1)
		return NULL;
	result = malloc(fstat.st_size);
	if(result == NULL)
		return NULL;
	file = fopen(regpath,"rb");
	if(file == NULL)
		return NULL;
	fread(result,1,fstat.st_size,file);
	fclose(file);
	
	return result;
}