#include "stdio.h"
#include <SDKDDKVer.h>
#include "include/VHX4RC.h"
#include <list>
#include <iostream>
#include <string>
#include <array>


//takes X,Y,PAth,ip

//to do:
//Make string parser thing for // folder path
//make a parser for the files
HWND dummyHWND = ::CreateWindowA("STATIC", "Remote Accsess Mode", WS_VISIBLE, 0, 0, 100, 100, NULL, NULL, NULL, NULL);

using namespace std;
#define WM_APP 0x8000
#define WM_APP_AUTO_FOCUS_COMPLETED (WM_APP + 1001)
#define WM_APP_XY_STAGE_INITIALIZE_THETA_ORIENTATION_COMPLETED (WM_APP + 1002)
#define WM_APP_QUICK_COMP_COMPLETED (WM_APP + 1000 )

void printResultMsg(VHX4RC_RESULT result){		//CW: extract out this to a separate class 

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


int errorCode = 0;	//last non-detrimental error code 
int getExitCode(VHX4RC_RESULT result) {
	int code = 5;   //default general error
	switch (result){
		case VHX4RC_S_OK:
			code = 0;
			break;
		case VHX4RC_E_COMMAND_FAILED:
			break;
		case VHX4RC_E_ALREADY_INITIALIZED:
			code = 0;  //new
			break;
		case VHX4RC_E_NOT_INITIALIZED://d
			code = 1;
			break;
		case VHX4RC_E_COMM_ERROR:
			code = 1; 
			break;
		case VHX4RC_E_INVALID_ARGUMENT://d
			code = 2;
			break;
		case VHX4RC_E_OUTOFMEMORY://d

			break;
		case VHX4RC_E_PATH_NOT_FOUND://d
			code = 2;
			break;
		case VHX4RC_E_SAVE_FILE_FAILED:
			break;
		case VHX4RC_E_FILE_ALREADY_EXISTS:

			break;
		case VHX4RC_E_INVALID_MODE:

			break;
		case VHX4RC_E_INVALID_STATE:

			break;
		case VHX4RC_E_Z_STAGE_NOTHING://?

			break;
		case VHX4RC_E_Z_STAGE_DISCONNECTED://d
			code = 3;
			break;
		case VHX4RC_E_INVALID_HANDLE:

			break;
		case VHX4RC_E_NOT_SUPPORT:
			code = 2; 
			break;
		case VHX4RC_E_OUTOFCOMPLIMIT:

			break;
		case VHX4RC_E_XY_STAGE_DISCONNECTED://d
			code = 3;
			break;
		case VHX4RC_E_XY_STAGE_NOT_INITIALIZED://d
			code = 3;
			break;
		default:
			break;
	}

	return (code);

}

int main(int argc, char* argv[]) {
	int X, Y, alpha, lensMag;
	double waitAutoFocus;
	string path, ip;

	//Process command line arguments
	if (argc >= 8) {
		X = strtol(argv[1], nullptr, 0);
		Y = strtol(argv[2], nullptr, 0);
		alpha = strtol(argv[3], nullptr, 0);
		waitAutoFocus = strtol(argv[4], nullptr, 0);
		lensMag = strtol(argv[5], nullptr, 0);
		path = argv[6];
		ip = argv[7];
		printf("X: %d,Y: %d\n", X, Y);

	} else {
		printf("Too few Argumets");
		return(-1);
	}

	//Initialize & connect to microscope
	CString strAddress = ip.c_str();
	printf("Connecting to %s: ", ip);
	VHX4RC_RESULT result = VHX4RC_Init(strAddress);
	printResultMsg(result);
	errorCode = getExitCode(result);
	if (result != VHX4RC_S_OK) {
		//VHX4RC_StopAutoFocusMode();		//CW: why do we need this when startAFMode was never called
		//Sleep(100);
		return errorCode;
	}
	Sleep(1000);

	//Set Lens Magnificiation
	int currLensMag;
	printf("Getting lens current magnification: ");
	result = VHX4RC_GetLensPower(&currLensMag);
	printResultMsg(result);
	Sleep(100);	//CW: why do we need this sleep?  Can we immediately print currLensMag? 
	printf("\tCurrent magnification: %dx\n", currLensMag);
	if (currLensMag != lensMag) {
		printf("Switching lens magnification to %dx: ", lensMag);
		result = VHX4RC_SetLensPower(lensMag);
		printResultMsg (result)
		errorCode = getExitCode(result);
		if (result == VHX4RC_E_Z_STAGE_DISCONNECTED) {	
			//VHX4RC_StopAutoFocusMode();	//CW: Why do we need this? 
			//Sleep(100);
			return errorCode;
		}
		Sleep(3000);	//CW: What is this sleep for?  Allow lens to rotate?  
	}

	//Move the stage to (X, Y) 
	int currX, currY;
	VHX4RC_XYStageGetPos(&currX, &currY);
	int distance = ceil(sqrt(pow(currX - X, 2) + pow(currY - Y, 2)));
	int speed = 6808;
	int movetime = 1000 * (ceil(distance / speed)) + 1500;
	movetime = ceil(alpha * movetime)

	printf("Moving XY Stage to (%d, %d): ", X, Y);
	result = VHX4RC_XYStageMoveTo(X, Y);
	printResultMsg(result);
	errorCode = getExitCode(result);
	if (result == VHX4RC_E_XY_STAGE_DISCONNECTED || result == VHX4RC_E_XY_STAGE_NOT_INITIALIZED) {
		//VHX4RC_StopAutoFocusMode();
		//Sleep(100);
		return errorCode;
	}
	Sleep(movetime);	//Allow stage to finish moving 

	printf("Starting Autofocus mode: ");
	result = (VHX4RC_StartAutoFocusMode());
	printResultMsg(result);
	Sleep(100);	
	errorCode = getExitCode(result);
	if (result != VHX4RC_S_OK) {
		VHX4RC_StopAutoFocusMode();	
		Sleep(100);
		return errorCode;
	}

	printf("Settinng Autofocus area size: ");
	result = VHX4RC_SetAutoFocusAreaSize(3);
	printResultMsg (result);
	errorCode = getExitCode(result);
	if (result != VHX4RC_S_OK) {
		VHX4RC_StopAutoFocusMode();
		Sleep(100);
		return errorCode;
	}
	Sleep(1000);

	printf("Autofocusing begins: ");
	printResultMsg(VHX4RC_StartAutoFocus(dummyHWND, WM_APP_AUTO_FOCUS_COMPLETED));
	Sleep(ceil(1000 * waitAutoFocus));

	printf("Saving image %s: ", path);
	LPCSTR filename = path.c_str();
	printResultMsg(VHX4RC_SaveImageRemotePCA(0, filename));
	Sleep(100);

	printf("Stopping Autofocus mode: ");
	result = VHX4RC_StopAutoFocusMode();
	printResultMsg(result);
	errorCode = getExitCode(result);
	if (result != VHX4RC_S_OK) {
		VHX4RC_StopAutoFocusMode();	//retry again before aborting
		Sleep(100);
		return errorCode;
	}
	sleep(100);
	
	VHX4RC_Exit(FALSE);
	Sleep(1500);
	return (errorCode);
}