/*
*@author James Inglis
*@date July 6th 2015
*This program was written to run from the command line on startup of a raspberry Pi running rapsbian
*Intended to be used to display the selected webpages in a lobby and cycle through them on a delay
*To run on startup add @[file path]./[compiled name] to the autostart file in the etc/xdg/lxsession/LXDE-[username]
*The program uses an infinite loop so must be terminated from the terminal
*This program uses the xdotool command line tool set (sudo apt-get install xdotool)
*This program uses the chromium browser by default (sudo apt-get install chromium-browser)
*/


#include <stdlib.h>
#include <unistd.h>


using namespace std;

int main(){

int websites = 3;//enter the number of websites you wish to switch between

char* Addresses[]{
	//any number of websites can be added. Just add the URLs formatted the same as the sample URLs 
	//make sure they are seperated by commas! the first URL must use the --kiosk option to go full screen
	"chromium-browser --kiosk http://www.cmegroup.com/trading/agricultural/grain-and-oilseed/corn.html&" ,
	"chromium-browser http://www.cmegroup.com/trading/fx/g10/canadian-dollar.html&",
	"chromium-browser http://www.cmegroup.com/trading/agricultural/livestock/lean-hogs.html&"
	};

for(int i = 0; i<websites; i++){//open URLS in seperate tabs of a browser window
	system(Addresses[i]);
}

sleep(10);//just for timing so the pages are loaded before key commands are sent

int refresh = 0;//initialize refresh counter

while(1){
	refresh++;//increment the refresh counter

	system("xdotool key ctrl+Page_Down");	//move to next tab

	if(refresh == 30){//if the refresh counter has reached 30 refresh current page and reset counter
	system("xdotool key ctrl+r")
	refresh = 0;
	}
	
	/* CHANGE THIS SLEEP TIME TO ALTER THE DELAY BETWEEN PAGES (IN SECONDS)*/
	sleep(15); 

return 0;
}
