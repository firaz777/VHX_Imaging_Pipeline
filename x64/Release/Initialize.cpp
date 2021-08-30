#include "stdio.h"
#include <SDKDDKVer.h>
#include "include/VHX4RC.h"
#include <list>
#include <iostream>
#include <string>
#include <array>

/*
This is the source code for initialize the Keyence microscope. 

Input: 
- int lens magnification
- int lens height
- string file path to save test jpeg image
- string IP of the microscope for remote connection
*/

HWND dummyHWND = ::CreateWindowA("STATIC", "Remote Accsess Mode", WS_VISIBLE, 0, 0, 100, 100, NULL, NULL, NULL, NULL);

using namespace std;
#define WM_APP 0x8000
#define WM_APP_AUTO_FOCUS_COMPLETED (WM_APP + 1001)
#define WM_APP_XY_STAGE_INITIALIZE_THETA_ORIENTATION_COMPLETED (WM_APP + 1002)


void printResultMsg(VHX4RC_RESULT result){

	string strLog;

	switch (result){
		case VHX4RC_S_OK:
			strLog += ("VHX4RC_S_OK");
			break;
		case VHX4RC_E_COMMAND_FAILED:
			strLog += ("VHX4RC_E_COMMAND_FAILED");
			break;
		case VHX4RC_E_ALREADY_INITIALIZED:
			strLog += ("VHX4RC_E_ALREADY_INITIALIZED");
			break;
		case VHX4RC_E_NOT_INITIALIZED:
			strLog += ("VHX4RC_E_NOT_INITIALIZED");
			break;
		case VHX4RC_E_COMM_ERROR:
			strLog += ("VHX4RC_E_COMM_ERROR");
			break;
		case VHX4RC_E_INVALID_ARGUMENT:
			strLog += ("VHX4RC_E_INVALID_ARGUMENT");
			break;
		case VHX4RC_E_OUTOFMEMORY:
			strLog += ("VHX4RC_E_OUTOFMEMORY");
			break;
		case VHX4RC_E_PATH_NOT_FOUND:
			strLog += ("VHX4RC_E_PATH_NOT_FOUND");
			break;
		case VHX4RC_E_SAVE_FILE_FAILED:
			strLog += ("VHX4RC_E_SAVE_FILE_FAILED");
			break;
		case VHX4RC_E_FILE_ALREADY_EXISTS:
			strLog += ("VHX4RC_E_FILE_ALREADY_EXISTS");
			break;
		case VHX4RC_E_INVALID_MODE:
			strLog += ("VHX4RC_E_INVALID_MODE");
			break;
		case VHX4RC_E_INVALID_STATE:
			strLog += ("VHX4RC_E_INVALID_STATE");
			break;
		case VHX4RC_E_Z_STAGE_NOTHING:
			strLog += ("VHX4RC_E_Z_STAGE_NOTHING");
			break;
		case VHX4RC_E_Z_STAGE_DISCONNECTED:
			strLog += ("VHX4RC_E_Z_STAGE_DISCONNECTED");
			break;
		case VHX4RC_E_INVALID_HANDLE:
			strLog += ("VHX4RC_E_INVALID_HANDLE");
			break;
		case VHX4RC_E_NOT_SUPPORT:
			strLog += ("VHX4RC_E_NOT_SUPPORT");
			break;
		case VHX4RC_E_OUTOFCOMPLIMIT:
			strLog += ("VHX4RC_E_OUTOFCOMPLIMIT");
			break;
		case VHX4RC_E_XY_STAGE_DISCONNECTED:
			strLog += ("VHX4RC_E_XY_STAGE_DISCONNECTED");
			break;
		case VHX4RC_E_XY_STAGE_NOT_INITIALIZED:
			strLog += ("VHX4RC_E_XY_STAGE_NOT_INITIALIZED");
			break;
		default:
			strLog = "Unknown";
			break;
	}
	std::cout << strLog + "\n";
}

int main(int argc, char* argv[]) {

	//Process command line arguments
	//printf("You have entered: %d arguments\n", argc);
	int lensMag,lensHeight;
	string path, ip;
	if (argc == 5) {
		lensMag = strtol(argv[1], nullptr, 0);
		lensHeight = strtol(argv[2], nullptr, 0);
		path = argv[3];
		ip = argv[4];
	} /*else {	//CW: Did SR ask for default? 
		//crash gracefully here
		printf("Default params used. Ignore input parameters if any.");
		lensMag = 40;
		lensHeight = 0;//to change
		path = "D:\\WorkTermBOLD\\MicroscopeOutput\\ScriptOut";
		ip = "131.104.63.75";
	} */
	else {
		printf("Too few arguments provided. Gave:%d , Require:3\n", argc);
		return(0);
	}


	//Initialize Keyence Microscope
	CString strAddress = (ip.c_str());
	printf("Connecting to %s: ", ip);		//CW: check printf syntax
	VHX4RC_RESULT result = VHX4RC_Init(strAddress);
	printResultMsg(result);
	Sleep(1000);

	printf("Setting lens magnification (%d x): ", lensMag);
	printResultMsg(VHX4RC_SetLensPower(lensMag));
	Sleep(2000);

	printf("Initializing XY Stage and Theata Orientation: ");
	printResultMsg(VHX4RC_XYStageInitializeThetaOrientation(dummyHWND, WM_APP_XY_STAGE_INITIALIZE_THETA_ORIENTATION_COMPLETED));
	Sleep(20000);
	//CW: print WM_APP_XY_STAGE_INITIALIZE_THETA_ORIENTATION_COMPLETED too

	//Test if image can be saved
	printf("Starting Autofocus mode: ");
	printResultMsg(VHX4RC_StartAutoFocusMode());
	Sleep(5000);

	printf("Settinng Autofocus area size: ");
	printResultMsg(VHX4RC_SetAutoFocusAreaSize(2));
	Sleep(5000);

	printf("Autofocusing begins: ");
	printResultMsg(VHX4RC_StartAutoFocus(dummyHWND, WM_APP_AUTO_FOCUS_COMPLETED));
	Sleep(5000);
	//CW: printf("%lu", WM_APP_AUTO_FOCUS_COMPLETED);

	LPCSTR filename = path.c_str(); //filenameinit.c_str();		//CW: make sure this works still
	//Sleep(5000);			//CW: Confirm with Firaz if we need 5 sec extra here. If so, add to previous sleep
	printf("Saving image %s: ", path);
	printResultMsg(VHX4RC_SaveImageRemotePCA(0, filename));
	Sleep(1000);

	printf("Stopping Autofocus mode: ");
	printResultMsg(VHX4RC_StopAutoFocusMode());
	Sleep(2000);

	printf("Disconnecting to microscope")
	VHX4RC_Exit(FALSE);
	Sleep(1000);

}