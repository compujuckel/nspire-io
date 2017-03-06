/**
 * @file queue.c
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
 * Simple queue implementation
 */

#include "../include/nspireio/queue.h"

void queue_init(queue* q)
{
	q->start = 0;
	q->end = QUEUE_SIZE - 1;
	q->count = 0;
}

void queue_put(queue* q, char val)
{
	if(q->count >= QUEUE_SIZE)
		return;
	else
	{
		q->end = (q->end + 1) % QUEUE_SIZE;
		q->data[q->end] = val;
		q->count++;
	}
}

char queue_get_top(queue* q)
{
	char val;
	
	if(q->count <= 0)
		return -1;
	else
	{
		val = q->data[q->end--];
		q->count--;
	}
	
	return val;
}

char queue_get(queue* q)
{
	char val;
	
	if(q->count <= 0)
		return -1;
	else
	{
		val = q->data[q->start];
		q->start = (q->start + 1) % QUEUE_SIZE;
		q->count--;
	}
	
	return val;
}

bool queue_empty(queue* q)
{
	return (q->count <= 0);
}
