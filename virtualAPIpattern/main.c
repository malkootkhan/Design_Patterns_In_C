#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <string.h>


/*
* UART, SPI, and I2C generic driver
*
* what are the functions used for all these three protocols?
* init()
* write()
* read()
* deInit()
*
* What are the data involved while communicating these devices?
* state
* speed
* clk
* mode
* Data
*
*/
typedef struct config config, *pConfig;
typedef struct uart_t uart_t, *pUart_t;
typedef struct spi_t spi_t, *pSpi;
typedef struct i2c_t i2c_t, *pI2c_t;
typedef struct operations operations, *pOperations;
typedef struct module module, *pModule;
typedef enum MODULE MODULE;
typedef enum MODULE{UART, SPI, I2C};
struct config {
	int state;
	int clk;
	int mode;
	char *data;
	int size;
};
struct spi_t {
	pConfig baseConfig;
	int chipSelect;
};
struct i2c_t {
	pConfig baseConfig;
	int slaveAddress;
};
struct uart_t {
	pConfig baseConfig;
	int baudrate;
};


struct operations {
	MODULE module;
	void (*init)(void *self);
	void (*write)(void *self);
	void (*read)(void *self);
	void (*deInit)(void *self);
};

struct module {
	void *param;
	pOperations ops;
};



void UART_init(void *self) {
	pUart_t uart = (pUart_t)self;
	printf("init state : %d\n", (int)uart->baseConfig->state);
	printf("init baudrate: %d\n", uart->baudrate);
	printf("init clock: %d\n", uart->baseConfig->clk);
	printf("init mode: %d\n", uart->baseConfig->mode);
	uart->baseConfig->data = (char *)malloc(sizeof(uart->baseConfig->size));
	strcpy(uart->baseConfig->data, "Hello World UART Module");
	printf("init data: %s\n", uart->baseConfig->data);
	printf("init data size: %d\n", uart->baseConfig->size);
}
void UART_write(void *self)
{

}
void UART_read(void *self)
{

}
void UART_deInit(void *self)
{

}


config uartConfig = {.state = 1, .clk=2000, .mode = 6, .data = NULL, .size = 10};
uart_t uartObj = {.baseConfig = &uartConfig, .baudrate = 9600};
operations uartOps = {.module = UART, .init = UART_init, .write = UART_write, .read = UART_read, .deInit = UART_deInit};

pModule createNewModule(int mod)
{
	pModule pm = (pModule)malloc(sizeof(module));

	switch(mod)
	{
		case UART:

			pm->param = &uartObj;
			pm->ops = &uartOps;	
			return pm;
			


		case SPI:
		case I2C:
		default:
		return NULL;
	}


}


int main()
{
	pModule uartHandle = createNewModule(UART);
	printf("Module: %d\n", uartHandle->ops->module);
	uartHandle->ops->init(uartHandle->param);
	uartHandle->ops->write(uartHandle->param);
	uartHandle->ops->read(uartHandle->param);
	uartHandle->ops->deInit(uartHandle->param);


}
