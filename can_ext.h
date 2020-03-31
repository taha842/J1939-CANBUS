// ------------------------------------------------------------------------
//  CANBUS J1939
//  Engr. Muhammad Taha 
//  0330-8530186
//  www.rex-es.com
// ------------------------------------------------------------------------

#ifndef CAN_EXT_H
#define CAN_EXT_H

extern int canInitialize(int nBaudRate);
extern byte j1939Transmit(long lPGN, byte nPriority, byte nSrcAddr, byte nDestAddr, byte* nData, int nDataLen);
extern byte j1939Receive(long* lPGN, byte* nPriority, byte* nSrcAddr, byte *nDestAddr, byte* nData, int* nDataLen);

#endif
