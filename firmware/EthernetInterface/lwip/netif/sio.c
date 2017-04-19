



#include "lwip/sio.h"
#include "comm.h"

static volatile u8_t m_abort = 0;
/**
 * Opens a serial device for communication.
 * 
 * @param devnum device number
 * @return handle to serial device if successful, NULL otherwise
 */
sio_fd_t sio_open(u8_t devnum)
{
  return NULL;
}

/**
 * Sends a single character to the serial device.
 * 
 * @param c character to send
 * @param fd serial device handle
 * 
 * @note This function will block until the character can be sent.
 */
void sio_send(u8_t c, sio_fd_t fd)
{
  COMM_Putc( (char) c );
}

/**
 * Receives a single character from the serial device.
 * 
 * @param fd serial device handle
 * 
 * @note This function will block until a character is received.
 */
u8_t sio_recv(sio_fd_t fd)
{
	u8_t c;
	COMM_Getc(&c);
  return c;
}

/**
 * Reads from the serial device.
 * 
 * @param fd serial device handle
 * @param data pointer to data buffer for receiving
 * @param len maximum length (in bytes) of data to receive
 * @return number of bytes actually received - may be 0 if aborted by sio_read_abort
 * 
 * @note This function will block until data can be received. The blocking
 * can be cancelled by calling sio_read_abort().
 */
u32_t sio_read(sio_fd_t fd, u8_t *data, u32_t len)
{
  u32_t recvd = 0; //bytes received
  while(len)
  {
		COMM_Getc(data);
    data++;
    len--;
    recvd++;
  }
	m_abort = 0;
  return recvd;
}

/**
 * Tries to read from the serial device. Same as sio_read but returns
 * immediately if no data is available and never blocks.
 * 
 * @param fd serial device handle
 * @param data pointer to data buffer for receiving
 * @param len maximum length (in bytes) of data to receive
 * @return number of bytes actually received
 */
u32_t sio_tryread(sio_fd_t fd, u8_t *data, u32_t len)
{
  u32_t recvd = 0; //bytes received
  while(len)
  {
    if(COMM_Getc(data) == 0)
    {
      data++;
			len--;
			recvd++;
    }
		else
			return recvd;
  }
  return recvd;
}

/**
 * Writes to the serial device.
 * 
 * @param fd serial device handle
 * @param data pointer to data to send
 * @param len length (in bytes) of data to send
 * @return number of bytes actually sent
 * 
 * @note This function will block until all data can be sent.
 */
u32_t sio_write(sio_fd_t fd, u8_t *data, u32_t len)
{
  u32_t sent = 0; //bytes sent
  while(len)
  {
		COMM_Putc(*data);
    data++;
    len--;
    sent++;
  }
  return sent; //Well, this is bound to be len if no interrupt mechanism
}

/**
 * Aborts a blocking sio_read() call.
 * 
 * @param fd serial device handle
 */
void sio_read_abort(sio_fd_t fd)
{
  m_abort = 1;
}

//}


