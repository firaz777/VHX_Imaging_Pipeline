#include "stdio.h"
#include <SDKDDKVer.h>
#include "include/VHX4RC.h"
#include <list>
#include <iostream>
#include <string>
#include <array>

//takes Mag,Path,Ip as command line arguments

//to do:
//Make string parser thing for // folder path
//make function to calc. angle
//make a parser for the files
HWND dummyHWND = ::CreateWindowA("STATIC", "Remote Accsess Mode", WS_VISIBLE, 0, 0, 100, 100, NULL, NULL, NULL, NULL);


using namespace std;
#define WM_APP 0x8000
#define WM_APP_AUTO_FOCUS_COMPLETED (WM_APP + 1001)
#define WM_APP_XY_STAGE_INITIALIZE_THETA_ORIENTATION_COMPLETED (WM_APP + 1002)


void print(VHX4RC_RESULT result)
{


	string strLog;



	switch (result)
	{
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
		CString strValue;

		strLog = "Unknown";
		break;
	}
	std::cout << strLog + "\n";
}

int main(int argc, char* argv[]) {
	//look for command line arguments
	//printf("You have entered: %d arguments\n", argc);
	//int Xoffset, Yoffset;
	int x, y, Mag,lensheight;
	string path, ip;
	if (argc >= 5) {

		Mag = strtol(argv[1], nullptr, 0);
		lensheight = strtol(argv[2], nullptr, 0);
		path = argv[3];
		ip = argv[4];

		//	Xoffset = strtol(argv[1], nullptr, 0);
		//	Yoffset = strtol(argv[2], nullptr, 0);
		//	printf("X offset: %d,Y offset: %d\n", Xoffset, Yoffset);
	}
	else {
		//crash gracefully here
		printf("Defult");
		Mag = 40;
		lensheight = 0;//to change
		path = "D:\\WorkTermBOLD\\MicroscopeOutput\\ScriptOut";
		ip = "131.104.63.75";
	}
	//else {
	//	printf("Too few arguments provided. Gave:%d , Require:3\n", argc);
	//	return(0);
	//}
	//struct point
	//{
	//	int x;
	//	int y;
	//};
	//std::array<point, 95> plate0;
	//plate0[0] = point{ -32763,-48767 };
	//plate0[1] = point{ -32708,-39667 };
	//plate0[2] = point{ -32854,-30831 };
	//plate0[3] = point{ -32805,-21847 };
	//plate0[4] = point{ -32711, -12864 };
	//plate0[5] = point{ -32719,-3874 };
	//plate0[6] = point{ -32780,5135 };
	//plate0[7] = point{ -32769,14125 };
	//plate0[8] = point{ -32673,23099 };
	//plate0[9] = point{ -32619,32107 };
	//plate0[10] = point{ -32619,41035 };
	//plate0[11] = point{ -33109,50000 };
	//plate0[12] = point{ -23876,-48764 };
	//plate0[13] = point{ -23876,-39764 };
	//plate0[14] = point{ -23997,-30748 };
	//plate0[15] = point{ -23810,-21827 };
	//plate0[16] = point{ -23793,-12883 };
	//plate0[17] = point{ -23796, -3860 };
	//plate0[18] = point{ -23784,14124 };
	//plate0[19] = point{ -23784,14124 };
	//plate0[20] = point{ -23775,23136 };
	//plate0[21] = point{ -23778,32015 };
	//plate0[22] = point{ -23778,40969 };
	//plate0[23] = point{ -23643,50000 };
	//plate0[24] = point{ -14892,-48726 };
	//plate0[25] = point{ -15038,-39920 };
	//plate0[26] = point{ -14893,-30851 };
	//plate0[27] = point{ -14875,-21852 };
	//plate0[28] = point{ -14840,-12844 };
	//plate0[29] = point{ -14853,-3904 };
	//plate0[30] = point{ -14735,5130 };
	//plate0[31] = point{ -14768,14141 };
	//plate0[32] = point{ -14770,23129 };
	//plate0[33] = point{ -14793,32152 };
	//plate0[34] = point{ -14760,41031 };
	//plate0[35] = point{ -14644,50000 };
	//plate0[36] = point{ -5913,-48735 };
	//plate0[37] = point{ -5904,-48735 };
	//plate0[38] = point{ -5850,-30910 };
	//plate0[39] = point{ -5876,-21820 };
	//plate0[40] = point{ -5822,-12884 };
	//plate0[41] = point{ -5822,-3895 };
	//plate0[42] = point{ -5785,5101 };
	//plate0[43] = point{ -5786,14069 };
	//plate0[44] = point{ -5776,23119 };
	//plate0[45] = point{ -5728,32056 };
	//plate0[46] = point{ -5672,41196 };
	//plate0[47] = point{ -5680,49983 };
	//plate0[48] = point{ 3045,-48756 };
	//plate0[49] = point{ 3030,-39794 };
	//plate0[50] = point{ 3109,-30809 };
	//plate0[51] = point{ 3059,-30809 };
	//plate0[52] = point{ 3136,-12874 };
	//plate0[53] = point{ 3159,-3902 };
	//plate0[54] = point{ 3135,5072 };
	//plate0[55] = point{ 3135,14056 };
	//plate0[56] = point{ 3205,23065 };
	//plate0[57] = point{ 3223,32110 };
	//plate0[58] = point{ 3246,41017 };
	//plate0[59] = point{ 3238,49968 };
	//plate0[60] = point{ 12099,-48723 };
	//plate0[61] = point{ 12074,-39813 };
	//plate0[62] = point{ 12087,-30862 };
	//plate0[63] = point{ 12151,-21915 };
	//plate0[64] = point{ 12134,-12861 };
	//plate0[65] = point{ 12119,-3874 };
	//plate0[66] = point{ 12154,5105 };
	//plate0[67] = point{ 12123,14095 };
	//plate0[68] = point{ 12272,23089 };
	//plate0[69] = point{ 12219,-32088 };
	//plate0[70] = point{ 12259,41007 };
	//plate0[71] = point{ 12221,50000 };
	//plate0[72] = point{ 21058,-48902 };
	//plate0[73] = point{ 21058,-39884 };
	//plate0[74] = point{ 21052,-30843 };
	//plate0[75] = point{ 21074,-21873 };
	//plate0[76] = point{ 21101,-12895 };
	//plate0[77] = point{ 21163,-3950 };
	//plate0[78] = point{ 21133,5109 };
	//plate0[79] = point{ 21163,14049 };
	//plate0[80] = point{ 21217,23100 };
	//plate0[81] = point{ 21230,32023 };
	//plate0[82] = point{ 21164,41027 };
	//plate0[83] = point{ 21253,49995 };
	//plate0[84] = point{ 21217,23100 };
	//plate0[85] = point{ 30083,-39882 };
	//plate0[86] = point{ 30122,-30909 };
	//plate0[87] = point{ 30061,-21939 };
	//plate0[88] = point{ 30096,-12904 };
	//plate0[89] = point{ 30043,-3983 };
	//plate0[90] = point{ 30170,5011 };
	//plate0[91] = point{ 30113,14028 };
	//plate0[92] = point{ 30186,23021 };
	//plate0[93] = point{ 30160,32025 };
	//plate0[94] = point{ 30233,40981 };
	//plate0[95] = point{ 30236,49964 };



	//intializing
	CString strAddress = (ip.c_str());
	printf("Connecting:");
	VHX4RC_RESULT result = VHX4RC_Init(strAddress);
	print(result);
	Sleep(1000);
	printf("Setting Lens Power:");
	result = VHX4RC_SetLensPower(Mag);
	print(result);
	Sleep(2000);
	/*double LargeStep = 1155;
	double SmallStep = 231;
	double lPositionLens = 0.0;
	VHX4RC_RESULT resultLens = VHX4RC_GetLensZPos(&lPositionLens);
	double goalLensZ = 304;*/

	//printf("Initiallizing Lens Height\n");
	//if (lPositionLens > goalLensZ) {
	//	double numbersteps = floor((lPositionLens - goalLensZ) / LargeStep);
	//	//printf("%d", numbersteps);
	//	for (double i = 0; i < numbersteps; i++) {
	//		VHX4RC_LensZDown(TRUE);
	//		Sleep(500);
	//	}
	//}else if (lPositionLens < goalLensZ) {
	//	double numbersteps = floor((goalLensZ - lPositionLens) / LargeStep);
	//	for (double i = 0; i < numbersteps; i++) {
	//		VHX4RC_LensZUp(TRUE);
	//		Sleep(500);
	//	}
	//	resultLens = VHX4RC_GetLensZPos(&lPositionLens);
	//	//printf("(%d,%d)",resultLens,goalLensZ );
	//}
	printf("Initializing Theata Orientation and XY Stage:");
	result = VHX4RC_XYStageInitializeThetaOrientation(dummyHWND, WM_APP_XY_STAGE_INITIALIZE_THETA_ORIENTATION_COMPLETED);
	print(result);
	Sleep(20000);

	/*print(VHX4RC_XYStageMoveTo(x, y));
	Sleep(8000);*/

	printf("Starting Autofocus Mode:");
	print(VHX4RC_StartAutoFocusMode());
	Sleep(5000);

	printf("Settinng Autofocus Area:");
	print(VHX4RC_SetAutoFocusAreaSize(2));
	Sleep(5000);



	printf("Start Autofocus:");
	print(VHX4RC_StartAutoFocus(dummyHWND, WM_APP_AUTO_FOCUS_COMPLETED));
	Sleep(5000);
	//printf("%lu", WM_APP_AUTO_FOCUS_COMPLETED);
	//filename here
	string filenameinit = path;


	LPCSTR filename = filenameinit.c_str();
	Sleep(5000);
	printf("Save Image:");
	print(VHX4RC_SaveImageRemotePCA(0, filename));
	Sleep(1000);

	printf("End Autofocus Mode:");
	print(VHX4RC_StopAutoFocusMode());
	Sleep(2000);

	//int nPosx = 0;
	//int nPosy = 0;
	////VHX4RC_RESULT result = VHX4RC_XYStageGetPos(&nPosx, &nPosy);
	////printf("(x,y)=(%d,%d)", nPosx, nPosy);
	//printf("Moving XY Stage to Origan:");
	//result = VHX4RC_XYStageMoveTo(0 + Xoffset, 0 + Yoffset);
	//print(result);
	//Sleep(10000);
	//int autofoucusX = 0;
	//int autofocusY = 0;
	////VHX4RC_GetAutoFocusAreaPosition(autofocusX, autofocusY);
	//

	//for (unsigned int i = 0; i < 10; i++) {
	//	printf("Well number: %d\n", i);
	//	printf("Moving to Point:");
	//	int x = (plate0[i].x) + Xoffset;
	//	int y = (plate0[i].y) + Yoffset;

	//	print(VHX4RC_XYStageMoveTo(x, y));
	//	Sleep(8000);
	//	printf("Starting Autofocus Mode:");
	//	print(VHX4RC_StartAutoFocusMode());
	//	Sleep(5000);
	//	
	//	printf("Settinng Autofocus Area:");
	//	print(VHX4RC_SetAutoFocusAreaSize(2));
	//	Sleep(5000);

	//	printf("Start Autofocus:");
	//	print(VHX4RC_StartAutoFocus(dummyHWND, WM_APP_AUTO_FOCUS_COMPLETED));
	//	Sleep(5000);
	//	//printf("%lu", WM_APP_AUTO_FOCUS_COMPLETED);
	//	//filename here
	//	string filenameinit = "D:\\WorkTermBOLD\\MicroscopeOutput\\ScriptOut";
	//	filenameinit += std::to_string(i);
	//	filenameinit = filenameinit + ".jpg";

	//	LPCSTR filename = filenameinit.c_str();
	//	Sleep(5000);
	//	//printf("Stop QuickComp:");
	//	/*print(VHX4RC_StopQuickComp());
	//	Sleep(1000);*/
	//	printf("Save Image:");
	//	print(VHX4RC_SaveImageRemotePCA(0, filename));
	//	Sleep(1000);

	//	printf("End Autofocus Mode");
	//	print(VHX4RC_StopAutoFocusMode());
	//	Sleep(2000);
	//
	//}



	VHX4RC_Exit(FALSE);

	Sleep(1000);
}
//C:\Users\khanf\source\repos\testingrun\x64\Release\testingrun.exe