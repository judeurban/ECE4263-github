/*
  ***************************************************************************************************************
  ***************************************************************************************************************
  ***************************************************************************************************************

  File:		  udpClientRAW.c
  Author:     ControllersTech.com
  Updated:    Jul 23, 2021

  ***************************************************************************************************************
  Copyright (C) 2017 ControllersTech.com

  This is a free software under the GNU license, you can redistribute it and/or modify it under the terms
  of the GNU General Public License version 3 as published by the Free Software Foundation.
  This software library is shared with public for educational purposes, without WARRANTY and Author is not liable for any damages caused directly
  or indirectly by this software, read more about this on the GNU General Public License.

  ***************************************************************************************************************
*/

#include "main.h"

#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/tcp.h"

#include "stdio.h"
#include "string.h"

#include "udpClientRAW.h"

struct udp_pcb *upcb;
char received_buffer[100];
char *token;
#define HOST_PORT 12345
#define LOCAL_PORT 7

void udpClient_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);

// extern Bool server_connected = false;

/* IMPLEMENTATION FOR UDP CLIENT :   source:https://www.geeksforgeeks.org/udp-server-client-implementation-c/

1. Create UDP socket.
2. Send message to server.
3. Wait until response from server is received.
4. Process reply and go back to step 2, if necessary.
5. Close socket descriptor and exit.
*/


void udpClient_connect(void)
{
	err_t err;

	/* 1. Create a new UDP control block  */
	upcb = udp_new();

	/* Bind the block to module's IP and port */
	ip_addr_t myIPaddr;
	IP_ADDR4(&myIPaddr, 192,168,2,90);
	udp_bind(upcb, &myIPaddr, 7);

	/* configure host IP address and port */
	ip_addr_t DestIPaddr;
	IP_ADDR4(&DestIPaddr, 192,168,2,95);
	err = udp_connect(upcb, &DestIPaddr, 20001);

	if (err == ERR_OK)
	{
//		 server_connected = true;

		/* 2. Send message to server */
		udpClient_send("stmF746ZG_ready");

    /* 3. Set a receive callback for the upcb */
    // subscribe to a server callback
		udp_recv(upcb, udpClient_receive_callback, NULL);
	}
}

void udpClient_send(char* send_msg[])
{
  // int len = sprintf(data, "\n");
  struct pbuf *txBuf;
  char data[100];

  int len = sprintf(data, send_msg);

  /* allocate pbuf from pool*/
  txBuf = pbuf_alloc(PBUF_TRANSPORT, len, PBUF_RAM);

  if (txBuf != NULL)
  {
    /* copy data to pbuf */
    pbuf_take(txBuf, data, len);

    /* send udp data */
    udp_send(upcb, txBuf);

    /* free pbuf */
    pbuf_free(txBuf);
  }
}

// this function is run on callback event from the python server
void udpClient_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{

  /*
    if Return value < 0 then it indicates str1 is less than str2.
    if Return value > 0 then it indicates str2 is less than str1.
    if Return value = 0 then it indicates str1 is equal to str2.
  */

	/* Copy the data from the pbuf */
	strncpy(received_buffer, (char *)p->payload, p->len);

	if(!server_connected)
	{
    if (strcmp(received_buffer, "server_ready") == 0)
      server_connected = true;

    else
      udpClient_send("stmF746ZG_ready");
  }
  else
  {
    token = strtok(received_buffer, ",");
    token = strtok(NULL, ",");
    if(strcmp(token, "T"))
    {
      // open lockbox
      // close on button interrupt?
    }
    else
    {
      // keep lockbox close
    }
  }

	// Free receive pbuf
	pbuf_free(p);

  //	reset buffer
  memset(received_buffer, 0, strlen(received_buffer));

}


