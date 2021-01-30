#pragma once
#include <stdlib.h>
#include <arpa/inet.h>
#include <string>
#include<iostream>
#include "mac.h"
using namespace std;
#pragma pack(push, 1)
typedef struct deauth_packet {
        uint8_t        revesion; //0x00
        uint8_t        pad; //0x00
        uint16_t       length;  //0x0c
        uint32_t       present_flags;   //8004
        uint8_t        data_Rate; //0x02
        uint8_t        dummy1;  //0x00
        uint8_t        dummy2;  //0x18
        uint8_t        dummy3;  //0x00
        uint8_t        typesubtype;     //deauth
#define DEAUTHTYPE 0xc0
        uint8_t        flags; //0x00
        uint16_t        duration; //0x013a
        Mac             destmac;
        Mac             srcmac;
        Mac             bssid;
        uint16_t        fragmentnum; //0x00
        uint16_t        reason; //0x0007
        deauth_packet(){
                this->revesion=0x00;
                this->pad=0x00;
                this->length=0x0c;
                this->present_flags=0x8004;
                this->data_Rate=0x02;
                this->dummy1=0x00;
                this->dummy2=0x18;
                this->dummy3=0x00;
                this->typesubtype=DEAUTHTYPE;
                this->flags=0x00;
                this->duration=0x013a;
                this->fragmentnum=0x00;
                this->reason=0x07;
        }
        deauth_packet(Mac ap, Mac st){
                this->revesion=0x00;
                this->pad=0x00;
                this->length=0x0c;
                this->present_flags=0x8004;
                this->data_Rate=0x02;
                this->dummy1=0x00;
                this->dummy2=0x18;
                this->dummy3=0x00;
                this->typesubtype=DEAUTHTYPE;
                this->flags=0x00;
                this->duration=0x013a;
                this->fragmentnum=0x00;
                this->reason=0x07;
                this->srcmac=ap;
                this->bssid=ap;
                this->destmac=st;
        }
}deauth_packet;
#pragma pack(pop)
