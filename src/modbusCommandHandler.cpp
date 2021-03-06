#include <modbus/modbus.h>
#include <modbus/modbus-tcp.h>
#include <stdint.h>
#include <cstring>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <iostream>

#include "sources/modbusCommands.h"

#define MAX_READ_BITS 10
#define MAX_READ_REGISTERS 80

uint8_t *tab_bit;
uint8_t *tab_input_bit;
uint16_t *tab_reg;
modbus_t *ctx;
int nb_points;
int nb_points_reg;




void modbus_init(void)
{
        ctx = modbus_new_tcp("192.168.24.24", 2000);
        
        modbus_set_slave(ctx, 5);
        
        if(modbus_connect(ctx) == -1) {
                modbus_free(ctx);
        }
        
        /* Allocate and initialize the memory to store Read Output Bits */
        tab_bit = (uint8_t *) malloc(MAX_READ_BITS * sizeof(uint8_t));
        memset(tab_bit, 0, MAX_READ_BITS * sizeof(uint8_t));
        
        /* Allocate and initialize the memory to store Input Bits */
        tab_input_bit = (uint8_t *) malloc(MAX_READ_BITS * sizeof(uint8_t));
        memset(tab_input_bit, 0, MAX_READ_BITS * sizeof(uint8_t));
        
        tab_reg = (uint16_t *) malloc(MAX_READ_REGISTERS * sizeof(uint16_t));
        memset(tab_reg, 0, MAX_READ_REGISTERS * sizeof(uint16_t));
}

int dmReadBit(int index)
{
        index = index - 10000;
        
        nb_points = MAX_READ_BITS;
        modbus_read_input_bits(ctx, 0, nb_points, tab_input_bit);
        
        return tab_input_bit[index];
}

int dmReadOutBit(int index)
{        
        index = index - 1000;
        
        nb_points = MAX_READ_BITS;
        modbus_read_bits(ctx, 0, nb_points, tab_bit);
        
        return tab_bit[index];        
}

void dmWriteBit(int index, bool state)
{
        index = index - 1000;
        
        tab_bit[index] = state;
        
        modbus_write_bit(ctx, index, tab_bit[index]);
}

long dmReadReg(int index)
{
        index = index - 30000;
        
        nb_points_reg = MAX_READ_REGISTERS;
        modbus_read_input_registers(ctx, 0, nb_points_reg, tab_reg);
                
        return tab_reg[index];        
}

void modbus_reconnect(void)
{
        modbus_set_error_recovery(ctx, MODBUS_ERROR_RECOVERY_LINK);
}

void modbus_exit(void)
{
        modbus_close(ctx);
        modbus_free(ctx);
}
        
