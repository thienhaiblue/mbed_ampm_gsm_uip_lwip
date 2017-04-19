/* Copyright (C) 2012 mbed.org, MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef LWIPOPTS_CONF_H
#define LWIPOPTS_CONF_H

#define LWIP_TRANSPORT_PPP      1

#define LWIP_UDP                     1
#define LWIP_UDPLITE                 0

#define LWIP_STATS                   0

#define LWIP_ARP                    	0
#define ARP_TABLE_SIZE               10
#define ARP_QUEUEING                 0
#define ETHARP_TRUST_IP_MAC          0

#define IP_FORWARD                   0
#define IP_OPTIONS_ALLOWED           1
#define IP_REASSEMBLY                0
#define IP_FRAG                      0
#define IP_DEFAULT_TTL               255

#endif
