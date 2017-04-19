#include "mbed.h"
#include "rtos.h"
#include "usb.h"
#include "lib/sys_tick.h"
#include "ampm_gsm.h"
#include <vector>
#include <string>
#include "lwip/api_msg.h"
#include "SDCard.h"
#include "lwip/sockets.h"
#include "TCPSocketConnection.h"
#include "gps/ampm_mbed_gps_api.h"
#include "lib/ampm_sys_tick.h"
AmpmSysTick sysTick;
//TCPSocketConnection socket_conn;
Serial gsmPort(GSM_TX, GSM_RX,115200);  // tx, rx
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
AnalogIn adc(A0);
SDCard sdcard(PB_15, PB_14, PB_13, PB_12,PC_6, "SDCard");
usb usbhost("USB");
AmpmGsm gsm(GSM_TX,GSM_RX,115200,PE_9,PB_5);
AmpmGps gps(GPS_TX,GPS_RX,9600);

typedef struct {
    uint32_t	taskId; 
    uint32_t    taskStatus;  
    uint32_t counter;
} message_t;
//Serial rs232(UART3TX, UART3RX);  // tx, rx
Queue<message_t, 10> queue;
message_t *message;

uint8_t buf[512];


void HardFault_Handler(void)
{
	while(1);
}


void listdir(const char *dir) {
    DIR *d;
    struct dirent *p;
    d = opendir(dir);
    if (d != NULL) {
        while ((p = readdir(d)) != NULL) {
            printf(" - %s\n", p->d_name);
        }
			closedir(d);
    } else {
        printf("Could not open directory!\n");
    }
}

void led2_thread(void)
{
    while (true) {
			led2 = !led2;
			Thread::wait(5000);
			//listdir("/");
			listdir("/SDCard/");
			listdir("/USB/");
    }
}

void led1_thread()
{
    while (true) {
			led1 = !led1;
			Thread::wait(2000);
			 printf("led1_thread\r\n");
			//usbhost.listdir("/");
    }
}

uint8_t replySmsBuf[256];
uint8_t clientBuf[513];
int sta_socket = -1;
void vAmpmNetTestTask()
{
	int recbytes;
	int sin_size;
	int str_len;
	uint32_t cnt = 0;
	int exit = 0;
	uint32_t interval = 20;
	message_t message;
	struct sockaddr_in remote_ip;
    printf("Hello, welcome to client!\r\n");
    while (1) {
			
				message.taskId = 0; 
				message.taskStatus = 0;
				message.counter = cnt++;
				queue.put(&message);
				Thread::wait(1000);
				if(sta_socket != -1)
					lwip_close(sta_socket);
        sta_socket = lwip_socket(PF_INET, SOCK_STREAM, 0);
			
        if (-1 == sta_socket) {
            lwip_close(sta_socket);
            printf("C > socket fail!\n");
            continue;
        }
				
        printf("C > socket ok!\n");
        memset(&remote_ip, 0,sizeof(struct sockaddr_in));
        remote_ip.sin_family = AF_INET;
        remote_ip.sin_addr.s_addr = inet_addr("117.2.3.40");
        remote_ip.sin_port = htons( 4050 );

        if (0 != lwip_connect(sta_socket, (struct sockaddr *)(&remote_ip), sizeof(struct sockaddr))) {
            lwip_close(sta_socket);
            printf("C > connect fail!\n");
						Thread::wait(3000);
            continue;
        }
				exit = 0;
				printf("C > connect ok!\n");
				while(!exit)
				{
					recbytes = lwip_recv(sta_socket , clientBuf, 512,MSG_DONTWAIT);
					if(recbytes > 0)
					{
							clientBuf[recbytes] = 0;
							printf("C > read data success %d!\nC > %s\n", recbytes, clientBuf);
							if (lwip_write(sta_socket, clientBuf, recbytes) < 0) {
								lwip_close(sta_socket);
								printf("C > send fail\n");
								exit = 1;
							}
					}
					Thread::wait(500);
					printf("TCP_TASK_WAIT:%d\r\n",interval);
					if(interval < 20) interval++;
					else if(!exit)
					{
						interval = 0;//10s
						sprintf((char *)clientBuf, "%s\n", "client_send info");
						if (lwip_write(sta_socket, clientBuf, strlen((char *)clientBuf) + 1) < 0) {
							lwip_close(sta_socket);
							printf("C > send fail\n");
							exit = 1;
						}
					}
					
					message.taskId = 0; 
					message.taskStatus = 0;
					message.counter = cnt++;
					queue.put(&message);
					
				}
    }
}

struct netconn *ampm_net;
void vAmpmNetTestTask4()
{
	
	struct ip_addr remote_addr;
  u16_t remote_port = 4050,i;
	struct netbuf *data;
  err_t err;
	((uint8_t *)&remote_addr)[0] = 117;
	((uint8_t *)&remote_addr)[1] = 2;
	((uint8_t *)&remote_addr)[2] = 3;
	((uint8_t *)&remote_addr)[3] = 40;
	
	if(ampm_net)
		netconn_delete(ampm_net);
	ampm_net = netconn_new(NETCONN_TCP);
	while(1)
	{
		std::printf("vAmpmNetTestTask:Try to creat new netconn \n");
		if(ampm_net == NULL)
			ampm_net = netconn_new(NETCONN_TCP);
		if(ampm_net != NULL)
		{
			std::printf("vAmpmNetTestTask:Try to connnect \n");
			if(netconn_connect(ampm_net, &remote_addr, remote_port) == ERR_OK)
				while(1)
				{
					std::printf("vAmpmNetTestTask:%d seconds.\n", i++);
					err = netconn_write(ampm_net, "thienhaiblue\r\n", 14, NETCONN_COPY);
					if(err == ERR_OK)
						Thread::wait(10000);
					else
					{
						std::printf("vAmpmNetTestTask:Kill\n");
						netconn_disconnect(ampm_net);
						netconn_delete(ampm_net);
						std::printf("vAmpmNetTestTask:Ok\n");
						ampm_net = netconn_new(NETCONN_TCP);
						break;
					}
				}
		}
		Thread::wait(3000);
	}
}


void testSMS0(void const *argument)
{
	Thread::wait(30000);
	std::printf("testSMS0*****************\r\n");
	gsm.SendSmsWait("0934937707","thienhaiblue0");
	while (true);
}

void testSMS1(void const *argument)
{
	Thread::wait(30000);
	std::printf("testSMS1*****************\r\n");
	gsm.SendSmsWait("0934937707","thienhaiblue1");
	while (true);
}

void testSMS2(void const *argument)
{
	Thread::wait(30000);
	std::printf("testSMS2*****************\r\n");
	gsm.SendSmsWait("0934937707","thienhaiblue2");
	while (true);
}


// main() runs in its own thread in the OS
// (note the calls to Thread::wait below for delays)

int main() {
	int i = 1;
	uint32_t monitorCnt[3];
	
	gsm.SetMode(AMPM_GSM_GPRS_ENABLE);
	gsm.Init("internet","mms","mms");
	//Thread thread_led1(led1_thread,NULL,osPriorityNormal,1024,NULL);
	Thread thread_led2(osPriorityNormal,2048,NULL);
	Thread thread_test(osPriorityNormal,2048,NULL);
	//Thread thread0(testSMS0,NULL,osPriorityNormal,512,NULL);
	//Thread thread1(testSMS1,NULL,osPriorityNormal,512,NULL);
	//Thread thread2(testSMS2,NULL,osPriorityNormal,512,NULL);
	Thread clientThread;
	thread_led2.start(led2_thread);
	thread_test.start(vAmpmNetTestTask);
	std::printf("Hello World !\n");
	gsm.SendSms("0978779222","thienhaiblue1");
	gsm.SendSms("0978779222","thienhaiblue2");
	gsm.SendSms("0978779222","thienhaiblue3");
	while (true) {
		led3 = !led3; 
		gps.Process();
		std::printf("ADC Value:%d\n",adc.read_u16());
		Thread::wait(1000);
		for(i = 0;i < 3;i++)
		{
			monitorCnt[i]++;
			if(monitorCnt[i] >= 10)
			{
				switch(i)
				{
					case 0:
						monitorCnt[0] = 0;
						if(thread_test.get_state() != Thread::Deleted)
						{
							thread_test.terminate();
							thread_test.join();
						}
						thread_test.start(vAmpmNetTestTask);
					break;
					case 1:
						monitorCnt[1] = 0;
					break;
					case 2:
						monitorCnt[2] = 0;
					break;
					default:
					break;
				}
			}
		}
		osEvent evt = queue.get(10);
		if (evt.status == osEventMessage) {
			message_t *message = (message_t*)evt.value.p;
			printf("\nTaskId: %d\n\r"   , message->taskId);
			printf("taskStatus: %d \n\r"     , message->taskStatus);
			printf("Task cnt: %u\n\r", message->counter);
			switch(message->taskId)
			{
				case 0:
					monitorCnt[0] = 0;
					printf("\nvAmpmNetTestTask:->ok\n\r");
				break;
				case 1:
					monitorCnt[1] = 0;
				break;
				case 2:
					monitorCnt[2] = 0;
				break;
				default:
				break;
			}
		}
	}
}

