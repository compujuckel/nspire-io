/**
 * @file file.cpp
 * @author  Julian Mackeben aka compu <compujuckel@googlemail.com>
 * @version 3.1
 *
 * @section LICENSE
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
 *
 * @section DESCRIPTION
 *
 * C++ file wrapper
 */

#include "../../include/nspireio/file.hpp"

using namespace nio;

file::file()
{
	fd = NULL;
	f = (fmtflags)(dec | right | fixed | skipws);
	s = goodbit;
	w = 0;
	p = 5;
	count = 0;
}

file::file(const char* filename, const char* mode)
{
	fd = NULL;
	f = (fmtflags)(dec | right | fixed | skipws);
	s = goodbit;
	w = 0;
	p = 5;
	count = 0;
	open(filename,mode);
}

file::~file()
{
	close();
}

void file::open(const char* filename, const char* mode)
{
	fd = fopen(filename,mode);
	if(fd == NULL)
		setstate(failbit);
}

bool file::is_open()
{
	return fd != NULL;
}

void file::close()
{
	if(fd != NULL)
	{
		if(fclose(fd) != 0)
			clear(eofbit);
	}
}

void file::put(char ch)
{
	fputc(ch,fd);
}

void file::write(const char* s, streamsize n)
{
	int i;
	for(i = 0; i < n; i++)
		put(s[i]);
}

void file::flush()
{

}

streamsize file::gcount() const
{
	return count;
}

int file::get()
{
	int tmp = fgetc(fd);
	if(tmp == EOF)
	{
		if(feof(fd))
			clear((iostate)(eofbit | failbit));
		else if(ferror(fd))
			clear(failbit);
		
		count = 0;
		return EOF;
	}

	count = 1;
	return tmp;
}

void file::get(int& ch)
{
	ch = fgetc(fd);
	if(ch == EOF)
	{
		if(feof(fd))
			clear((iostate)(eofbit | failbit));
		else if(ferror(fd))
			clear(failbit);
		
		count = 0;
		return;
	}

	count = 1;
}

void file::get(char* s, streamsize n)
{
	char* ret = fgets(s,n,fd);
	if(ret == NULL || feof(fd))
	{
		clear((iostate)(eofbit | failbit));
		count = ret == NULL ? 0 : strlen(s);
		return;
	}
	else if(ferror(fd))
	{
		clear(failbit);
		count = 0;
		return;
	}
	
	count = strlen(s);
}

void file::getline(char* s, streamsize n)
{
	get(s,n);
}

int file::tellp()
{
	return ftell(fd);
}

void file::seekp(__attribute__((unused)) int pos)
{
	//if(fsetpos(fd,pos) != 0) // fsetpos is not implemented in Ndless yet, always set failbit
		clear(failbit);
}

void file::seekp(int off, seekdir way)
{
	if(fseek(fd,off,way) != 0)
		clear(failbit);
}
