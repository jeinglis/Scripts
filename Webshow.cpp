/*
*@author James Inglis
*@date July 6th 2015
*This program was written to run on startup of a rasberrypi attached to a display
*Intended to be used to display the selected webpages and cycle through them on a delay
*The program uses an infinite loop so must be terminated from the terminal
*/


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


using namespace std;

int main(){

int websites = 3;

char* Addresses[3]{

	"chromium-browser --kiosk http://www.cmegroup.com/trading/agricultural/grain-and-oilseed/corn.html&" ,
	"chromium-browser http://www.cmegroup.com/trading/fx/g10/canadian-dollar.html&",
	"chromium-browser http://www.cmegroup.com/trading/agricultural/livestock/lean-hogs.html&"
	};

for(int i = 0; i<websites; i++){
	system(Addresses[i]);

sleep(3);
}


sleep(20);


int refresh = 0;

while(1){
	refresh++;//increment the refresh counter

	system("xdotool key ctrl+Page_Down");	//move to next tab

	if(refresh == 30){//if the refresh counter has reached 30 refresh current page and reset counter
	system("xdotool key ctrl+r")
	refresh = 0;
	}
	
	sleep(15); // amount of time to wait between tab switches
}


return 0;
}
