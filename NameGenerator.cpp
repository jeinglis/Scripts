/*
*@author James Inglis
*@date June 12th 2015
*This program receives a macaddress then
*removes the : or - and appends it to a prefix
*the new name is then written to the registry
*intended to be used when creating computer names
*for a domain/computer name autochange utility
*requires@ mac address passed as a string
*returns@ writes the prefix + modified Mac to the registry 
*/

#include <string>
#include <iostream>
#include <Windows.h>
#include <winreg.h>


using namespace std;
void regWrite(const LPCWSTR namePtr, int size);

int main(int argc, char* argv[])
{

	//std::string mac = "F0:4D:A2:9F:C4:5F";
	std::string prefix = "";//enter  prefix 
	string mac = argv[1];

	//moves through command line argument (the mac address)
	//removes the punctuation and appends altered macAdress to the prefix
	for (int i = 0; i<mac.length(); i++){
		if (mac[i] != ':' && mac[i] != '-'){
			prefix.push_back(mac[i]);
		}
	}

	//creates LPCWSTR to be used with RegSetValueEx func
	wstring ws;
	ws.assign(prefix.begin(), prefix.end());
	LPCWSTR namePtr = ws.c_str();
	int size = (ws.size() + 1)*sizeof(wchar_t);
	regWrite(namePtr, size);

	return 0;
}

	/*
	*Checks if Reg key is created already if not makes reg key and sets value
	*@Requires LPCWSTR string pointer aswell as the size of the wstring being pointed to
	*@Returns writes generated computerName to the specified Reg location
	*/
void regWrite(LPCWSTR namePtr, int size)
{
	//enter the registry location you want to use
	//by default the key will be placed in
	//HKCU\Software\ComputerInfo\name
	HKEY hKey;

	//Step 1: Open the key
	long sts = RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\ComputerInfo", 0, KEY_ALL_ACCESS, &hKey);

	//Step 2: If failed, create the key
	if (ERROR_NO_MATCH == sts || ERROR_FILE_NOT_FOUND == sts)
	{
		cout << "Creating registry key Software\\ComputerName" << endl;

		long j = RegCreateKeyEx(HKEY_CURRENT_USER, L"Software\\ComputerInfo", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
		if (ERROR_SUCCESS != j)
			cout << "Error: Could not create registry key Software\\ComputerInfo" << endl << "\tERROR: " << j << endl;
		else
			cout << "Success: Key created" << endl;

	}
	else if (ERROR_SUCCESS != sts)
	{
		cout << "Cannot open registry key Software\\ComputerInfo" << endl << "\tERROR: " << sts << endl;
		exit;

	}
	//set  the registry value to the wstring pointed to by namePtr
	LONG nError = RegSetValueEx(hKey, L"name", 0, REG_SZ, (const BYTE*)namePtr, size);

	if (nError)
		cout << "Error: " << nError << " Could not set registry value: " << endl;


	RegCloseKey(hKey);


}
