/*******************************************************************************
 * @attention Copyright would go here...
 * @file network.h
 * @author Paul Czeresko
 * @date 26 Oct 2019
 * @brief Definitions for networking functions
 *******************************************************************************/

#ifndef __NETWORK_H
#define __NETWORK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "lwip.h"
#include "lwip/api.h"
#include "lwip/netbuf.h"

#define NETBUF_SIZE		( (uint16_t)256 )

typedef struct databuf_s
{
	void *dataptr;
	uint16_t len;
} databuf_t;
typedef struct netbuf netbuf_t; // from netbuf.h
typedef struct netconn netconn_t; // from api.h

void vNetworkTcpInit(void);

#ifdef __cplusplus
}
#endif

#endif /* __NETWORK_H */
