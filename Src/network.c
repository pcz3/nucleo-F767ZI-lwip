/*******************************************************************************
 * @attention Copyright would go here...
 * @file network.c
 * @author Paul Czeresko
 * @date 26 Oct 2019
 * @brief Networking functions and tasks
 *******************************************************************************/

#include "network.h"

static char theData[128];

static void prvNetworkTcpEchoTask(void *pvParameters)
{
	/**
	 * Pass in the pointer to data. Possibly create init function?
	 */
	databuf_t dbuf;
	dbuf.dataptr = (void *)theData;
	dbuf.len = 0;
	// assert task has stack to fit buffer?
	uint16_t usPort = 10000;
	netbuf_t *nbuf = netbuf_new(); // may want to check/assert this not being null
	netbuf_alloc(nbuf, NETBUF_SIZE); // may want to check/assert this not being null
	netconn_t *conn = netconn_new(NETCONN_TCP);
	netconn_t *newconn;
	if (conn != NULL) // possibly make this an assert?
	{
		err_t err = netconn_bind(conn, NULL, usPort);
		if (err == ERR_OK)
		{
			netconn_listen(conn);
			/**
			 * Main task loop for accepting new connections and spawning child
			 * ports.
			 */
			for (;;)
			{
				err_t accept_err = netconn_accept(conn, &newconn);
				if (accept_err == ERR_OK)
				{
					while (1)
					{
						if (netconn_recv(newconn, &nbuf) != ERR_OK) break;
						do
						{
							netbuf_data(nbuf, &(dbuf.dataptr), &(dbuf.len));
							netconn_write(newconn, dbuf.dataptr, dbuf.len, NETCONN_COPY);
						} while (netbuf_next(nbuf) >= 0);

						netbuf_delete(nbuf);
					}

					netconn_close(newconn);
					netconn_delete(newconn);
				}
			}
		}
		else
		{
			/**
			 * Delete task if we can't initialize properly
			 */
			HARA_KIRI();
		}
	}
}

void vNetworkTcpInit()
{
	xTaskCreate(prvNetworkTcpEchoTask, "tcp-echo", 1024, NULL, 2, NULL);
}
