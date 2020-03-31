// ------------------------------------------------------------------------
//  CANBUS J1939
//  Engr. Muhammad Taha 
//  0330-8530186
//  www.rex-es.com
// ------------------------------------------------------------------------
//
// IMPOPRTANT: Depending on the CAN shield used for this programming sample,
//             please make sure you set the proper CS pin in module can.cpp.
//
//  This Arduino program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.

#include <stdlib.h>
#include <SPI.h>

#include "mcp_can.h"
#include "can_ext.h"

uint8_t ECT ;
uint8_t FWT ;
uint16_t EOT ;
uint16_t ETCT ;
uint8_t ICT ;
uint8_t ICTP ;
uint16_t ERPM  ;
float Volt;
float EOP ;
uint8_t EOL;
float ECP ;
uint8_t ECL ;

float EIMP ;

uint8_t EIMT  ;

float EAIP;



// ------------------------------------------------------------------------
//  SYSTEM: Setup routine runs on power-up or reset
// ------------------------------------------------------------------------
void setup()
{
  // Set the serial interface baud rate
  Serial.begin(115200);

  // Initialize the CAN controller
  if (canInitialize(CAN_250KBPS) == CAN_OK)  // Baud rates defined in mcp_can_dfs.h
    Serial.print("iCA CAN Init OK.\n\r\n\r");
  else
    Serial.print("iCA CAN Init Failed.\n\r");

}// end setup

// ------------------------------------------------------------------------
// Main Loop - Arduino Entry Point
// ------------------------------------------------------------------------
void loop()
{
  // Declarations
  byte nPriority;
  byte nSrcAddr;
  byte nDestAddr;
  byte nData[8];
  int nDataLen;
  long lPGN;

  char sString[80];

  // Check for received J1939 messages
  if (j1939Receive(&lPGN, &nPriority, &nSrcAddr, &nDestAddr, nData, &nDataLen) == 0)
  {
    //    sprintf(sString, "PGN: 0x%X Src: 0x%X Dest: 0x%X ", (int)lPGN, nSrcAddr, nDestAddr);
    //    Serial.print(sString);
    //    if (nDataLen == 0 )
    //      Serial.print("No Data.\n\r");
    //    else
    //    {
    //      Serial.print("Data: ");
    //      for (int nIndex = 0; nIndex < nDataLen; nIndex++)
    //      {
    //        sprintf(sString, "0x%X ", nData[nIndex]);
    //        Serial.print(sString);
    //
    //      }// end for
    //      Serial.print("\n\r");
    if (lPGN == 0xFEEE)
    {
      ECT = (nData[0], DEC) - 40;
      FWT = (nData[1], DEC) - 40;
      EOT = (((nData[3] << 8 | nData[2]) / uint16_t(32)  ) - 273  ) ;
      ETCT = (((nData[5] << 8 | nData[4]) / uint16_t(32)  ) - 273  ) ;
      ICT = (nData[6], DEC) - 40;
      ICTP = (nData[7], DEC);
      Serial.print("Engine Coolant Temparature(C): ");
      Serial.println(ECT);
      Serial.print("Engine Fresh Water Temparature(C): ");
      Serial.println(FWT);
      Serial.print("Engine Oil Temparature(C): ");
      Serial.println(EOT, DEC);
      Serial.print("Engine Turbo Charger Temparature(C): ");
      Serial.println(ETCT, DEC);
      Serial.print("Engine Innner Cooler Temparature(C): ");
      Serial.println(ICT);
      Serial.print("Engine Speed (RPM): ");
      Serial.println(ERPM, DEC);

      Serial.print("Engine Oil Pressure(Bar): ");
      Serial.println(EOP, DEC);
      Serial.print("Engine Oil Level(%): ");
      Serial.println(EOL, DEC);
      Serial.print("Engine Coolant Pressure(Bar): ");
      Serial.println(ECP, DEC);
      Serial.print("Engine Coolant Level(%): ");
      Serial.println(ECL, DEC);

      Serial.print("Engine Intake mainfold Pressure(Bar): ");
      Serial.println(EIMP, DEC);
      Serial.print("Engine Intake Mainfold Temparaure (C): ");
      Serial.println(EIMT, DEC);
      Serial.print("Engine Air Inlet Pressure(Bar): ");
      Serial.println(EAIP, DEC);


      Serial.print("Input Voltages (V): ");
      Serial.println(Volt, DEC);
      Serial.println("");

    }
    if (lPGN == 0xF004)
    {
      ERPM = (((nData[4] << 8 | nData[3]) / uint16_t(8)  )  ) ;
    }
    if (lPGN == 0xFEF7)
    {
      Volt = float((float(nData[5] << 8 | nData[4]) / float(20)  ) ) ;

    }
    if (lPGN == 0xFEEF)
    {
      EOP = (((float (nData[3]) / float(0.25)) / float(100)));

      EOL = (nData[2] / float(2.5));

      ECP = (((float (nData[6]) / float(0.5)) / float(100)));

      ECL = (nData[7] / float(2.5) );
    }
    if (lPGN == 0xFEF6)
    {
      EIMP = (((float (nData[1]) / float(0.5)) / float(100)));

      EIMT  = ((nData[2], DEC) - 40);

      EAIP  = (((float (nData[3]) / float(0.5)) / float(100)));
    }
    //}// end else

  }// end if

}// end loop
