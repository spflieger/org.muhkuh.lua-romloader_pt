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


#ifndef __USB_H__
#define __USB_H__


void usb_deinit(void);
void usb_init(void);
void usb_send_byte(unsigned char ucData);
void usb_send_packet(void);
unsigned long usb_get_rx_fill_level(void);
unsigned long usb_get_tx_fill_level(void);
unsigned char usb_get_byte(void);

unsigned char usb_call_console_get(void);
void usb_call_console_put(unsigned int uiChar);
unsigned int usb_call_console_peek(void);
void usb_call_console_flush(void);

void usb_loop(void);


#endif  /* __USB_H__ */
