#include <SPI.h>          //SPI is used to talk to the CAN Controller
#include <mcp_can.h>

MCP_CAN CAN(10);          //set SPI Chip Select to pin 10


void setup()
{
  Serial.begin(115200);   //to communicate with Serial monitor

//tries to initialize, if failed --> it will loop here for ever
START_INIT:

    if(CAN_OK == CAN.begin(CAN_500KBPS))      //setting CAN baud rate to 500Kbps
    {
        Serial.println("CAN BUS Shield init ok!");
    }
    else
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println("Init CAN BUS Shield again");
        delay(100);
        goto START_INIT;
    }
}

//loading the data bytes of the message. Up to 8 bytes
unsigned char data[10][8] = {{'C', 'A', 'N', '_', 'B', 'U', 'S', '!'},
                             {'A', 'S', 'U', '_', '_', 'E', 'N', 'G'},
                             {'N', 'E', 'T', 'W', 'O', 'R', 'K', '-'},  
                             {'P', 'R', 'O', 'J', 'E', 'C', 'T', '!'},
                             {'G', 'R', 'O', 'U', 'P', '_', 'N', '-'},
                             {'A', 'M', 'E', 'S', ':', ' ', ' ', ' '},
                             {'*', '*', '*', '*', '*', '*', '*', '*'},
                             {'S', 'A', 'I', 'E', 'E', 'D', ' ', ' '},
                             {'A', 'H', 'M', 'E', 'D', ' ', ' ', ' '},
                             {'Y', 'O', 'U', 'S', 'E', 'F', ' ', ' '}};


void loop()
{
    //CAN.sendMsgBuf(msg ID, extended?, #of data bytes, data array);
    for (int i = 0; i < 10; i++)
    {
      CAN.sendMsgBuf(0xAA, 0, 8, data[i]);
      delay(2000); 
    }
    
    for (int i = 0; i < 3; i++)
    {
      CAN.sendMsgBuf(0xAA, 0, 8, data[6]);
      delay(500); 
    }
                         
}
