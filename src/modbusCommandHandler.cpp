#include <modbus/modbus.h>
#include <modbus/modbus-tcp.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <iostream>

#include "sources/modbusCommands.h"

#define MODBUS_MAX_READ_BITS 5;

uint8_t *tab_bit;
uint16_t *tab_reg;
modbus_t *ctx;
int i;
int nb_points;
uint32_t bytes;
uint32_t rate;
int rc;

/* Allocate and initialize the memory to store the status */
tab_bit = (uint8_t *) malloc(MODBUS_MAX_READ_BITS * sizeof(uint8_t));
memset(tab_bit, 0, MODBUS_MAX_READ_BITS * sizeof(uint8_t));

void modbus_init(void)
{
        ctx = modbus_new_tcp("192.168.24.24", 2000);
        
        modbus_set_slave(ctx, 5);
        
        if(modbus_connect(ctx) == -1) {
                modbus_free(ctx);
        }
}

int dmReadBits(int index)
{
        index = index - 10;
        
        nb_points = MODBUS_MAX_READ_BITS;
        rc = modbus_read_bits(ctx, 0, nb_points, tab_bit);
        
        return tab_bits[index];
}

void modbus_exit(void)
{
        modbus_close(ctx);
        modebus_free(ctx);
}
        
