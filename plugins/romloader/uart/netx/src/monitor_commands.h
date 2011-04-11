/***************************************************************************
 *   Copyright (C) 2010 by Christoph Thelen                                *
 *   doc_bacardi@users.sourceforge.net                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifndef __MONITOR_COMMANDS_H__
#define __MONITOR_COMMANDS_H__


#define MONITOR_MAX_PACKET_SIZE 256

#define MONITOR_STREAM_PACKET_START 0x2a


typedef enum
{
	MONITOR_COMMAND_Read                    = 0x00,
	MONITOR_COMMAND_Write                   = 0x01,
	MONITOR_COMMAND_Execute                 = 0x02
} MONITOR_COMMAND_T;

typedef enum
{
	MONITOR_STATUS_Ok                        = 0x00,
	MONITOR_STATUS_CallMessage               = 0x01,
	MONITOR_STATUS_CallFinished              = 0x02,
	MONITOR_STATUS_InvalidCommand            = 0x03,
	MONITOR_STATUS_InvalidPacketSize         = 0x04,
	MONITOR_STATUS_InvalidSizeParameter      = 0x05
} MONITOR_STATUS_T;

typedef enum
{
	MONITOR_ACCESSSIZE_Byte                  = 0,
	MONITOR_ACCESSSIZE_Word                  = 1,
	MONITOR_ACCESSSIZE_Long                  = 2
} MONITOR_ACCESSSIZE_T;


typedef struct
{
	unsigned char ucStatus;
	unsigned char aucText[63];
} MONITOR_PACKET_MESSAGE_T;


#endif  /* __MONITOR_COMMANDS_H__ */
