#ifndef _MODBUSCOMMANDS_H_
#ifdef __cplusplus
extern "C" {
#endif

  extern    void modbus_init(void);
  extern    void dmWriteBit(int index, bool state);
  extern    int dmReadBit(int index);
  extern    int dmReadOutBit(int index);
  extern    int dmReadInReg(int index);
  
#ifdef __cplusplus
}
#endif
#endif //_MODBUSCOMMANDS_H_
