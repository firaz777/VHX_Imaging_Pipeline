#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include <SDKDDKVer.h>
#include "include/VHX4RC.h"
#include <list>
#include <iostream>
#include <string>
#include <array>
#include <iostream>
#include <ctime>
#include<vector>
#include <chrono>





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


std::string getTimeStamp() {
 time_t rawtime;
 struct tm* timeinfo;
 char buffer[80];
 std::string str;

 time(&rawtime);
 timeinfo = localtime(&rawtime);

 strftime(buffer, sizeof(buffer), "[%Y-%m-%d %H:%M:%S] ", timeinfo);
 return buffer;
}


void printResultMsg(VHX4RC_RESULT result) {  //CW: extract out this to a separate class
 string strLog;
 switch (result) {
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

int errorCode = 0; //last non-detrimental error code
int getExitCode(VHX4RC_RESULT result) {
 int code = 5;   //default general error
 switch (result) {
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

int* getInfo(int sleepTime) {
 int stageX, stageY;
 double lensZ;
 stageX = 111111;
 stageY = 111111;
 lensZ = 111111;
 long mode = -1;
 int numstageresult = 111111;
 int numlensresult = 1111111;
 //put system time in ms in a var
 auto start = chrono::steady_clock::now();

 Sleep(sleepTime);
 VHX4RC_GetCurrentMode(&mode);
 Sleep(sleepTime);
 //to do use byte location
 if (mode == VHX4RC_VHXMODE_IDLE) {
  //printf("test\n");
  VHX4RC_RESULT resultstage = VHX4RC_XYStageGetPos(&stageX, &stageY);
  numstageresult = (int)resultstage;
  //4ms is saftey for communication
  Sleep(sleepTime);
  VHX4RC_RESULT resultlens = VHX4RC_GetLensZPos(&lensZ);
  numlensresult = (int)resultlens;
 }


 //Sleep(20);
 //printf("Current (mode,x,y,z) is (%ld,%d,%d,%f)\n", mode,stageX, stageY, lensZ);
 //add return of array of int with 4 values of mode stagex stagey lensz
 int lensZI = (int)lensZ;
 int modeI = int(mode);
 if (modeI == -1) {
  VHX4RC_StopAutoFocusMode();
 }
 //put system time in milliseconds in a var here and subtract it from above
 auto end = chrono::steady_clock::now();
 int TimeElapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();
 static int output[7];
 output[0] = modeI;
 output[1] = stageX;
 output[2] = stageY;
 output[3] = lensZI;
 output[4] = numstageresult;
 output[5] = numlensresult;
 output[6] = TimeElapsed;
 //add system time to array
 return(output);
}

void MonitoredSleep(int SleepTimeInMilliseconds) {
 //int timeRunofGetInfo = 70;
 printf("sleeping for %d milliseconds\n", SleepTimeInMilliseconds);
 int loopSleep = 500;
 int inbetweenPollingSleep = 75;
 int elapsedMilliseconds = 0;
 int timeRemaining = SleepTimeInMilliseconds;
 while (elapsedMilliseconds < SleepTimeInMilliseconds) {
  int* out = getInfo(inbetweenPollingSleep);
  elapsedMilliseconds += out[6];
  if (out[0] != -1) {
   cout << getTimeStamp();
   for (int i = 0; i < 7; i++) {
    cout << *(out + i) << " ";
   }
   cout << endl;
   if (elapsedMilliseconds < SleepTimeInMilliseconds) {
    timeRemaining = SleepTimeInMilliseconds - elapsedMilliseconds;
    if (loopSleep < timeRemaining) {
     Sleep(loopSleep);
     elapsedMilliseconds += loopSleep;
    }
    else {
     Sleep(timeRemaining);
     elapsedMilliseconds += loopSleep;
    }
   }
  }
  else { //exception where program exits
   printf("Invalid mode Error\n");
   printResultMsg(VHX4RC_StopAutoFocusMode());
   Sleep(400);
   printResultMsg(VHX4RC_Exit(TRUE));
   Sleep(256);
   exit(-1);
  }
 }
}
void MoveZ(int min, int max) {
 double zheight;
 VHX4RC_GetLensZPos(&zheight);
 Sleep(100);
 while (min > zheight || max < zheight)
 {
  if (min > zheight && (min - zheight) >= 1000) {
   VHX4RC_LensZUp(true);
   Sleep(250);
  }
  if (min > zheight && (min - zheight) < 1000) {
   VHX4RC_LensZUp(false);
   Sleep(150);
  }
  if (max < zheight && (zheight - max) >= 1000) {
   VHX4RC_LensZDown(true);
   Sleep(250);
  }
  if (max < zheight && (zheight - max) < 1000) {
   VHX4RC_LensZDown(false);
   Sleep(150);
  }
  VHX4RC_GetLensZPos(&zheight);
  Sleep(100);
 }
}

void MoveToZWithPhotos(double goal, string path) {
 double min = goal - 500;
 double max = goal + 500;
 double sizesmallstep = 200;
 double zheight;
 VHX4RC_GetLensZPos(&zheight);
 printf("%f\n", zheight);
 Sleep(100);
 int numbersteps;
 if (goal > zheight) {
  numbersteps = floor((goal - zheight) / sizesmallstep);
  //printf("in >");
  for (int i = 1; i <= numbersteps; i++) {
   //printf("test");
   path = path + std::to_string(i) + std::to_string(i);
   //printf("test2");
   printResultMsg(VHX4RC_LensZUp(false));
   //Sleep(200);
   LPCSTR filename = path.c_str();
   cout << getTimeStamp();
   printf("Saving image %s: \n", filename);
   VHX4RC_RESULT result = (VHX4RC_SaveImageRemotePCA(0, filename));
   cout << getTimeStamp();
   printf("Done Saving image %s:", filename);
   printResultMsg(result);
   //MonitoredSleep(100);
  }
 }
 else if (goal < zheight) {
  numbersteps = floor((zheight-goal) / sizesmallstep);
  //printf("in <");
  for (int i = 1; i <= numbersteps; i++) {
   path = path + std::to_string(i)+ std::to_string(i);
   printResultMsg(VHX4RC_LensZDown(false));
   Sleep(200);
   LPCSTR filename = path.c_str();
   cout << getTimeStamp();
   printf("Saving image %s: \n", filename);
   VHX4RC_RESULT result = (VHX4RC_SaveImageRemotePCA(0, filename));
   cout << getTimeStamp();
   printf("Done Saving image %s:", filename);
   printResultMsg(result);
   MonitoredSleep(100);
  }
 }
 else {
  printf("Already at goal height");
 }
 
 
}
int main(int argc, char* argv[]) {
 //int goalZ = 16600;
 //TRUE stepsize at 40x = 1000
 int X, Y, alpha, lensMag;
 double waitAutoFocus;
 string path, ip;
 int timeConnect, TimeMag, timeAutoFocusMode, timeStopAutoFocusMode, timeSetArea, timeCapture, timeEndAutoFocusMode, timeDisconnect;
 timeConnect = 16;
 timeAutoFocusMode = 200;
 timeSetArea = 32;
 timeStopAutoFocusMode = 200;
 timeCapture = 200;
 timeDisconnect = 128;
 timeEndAutoFocusMode = 200;
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
 }
 else {
  printf("Too few Argumets");
  return(-1);
 }
 //Initialize & connect to microscope
 CString strAddress = ip.c_str();
 cout << getTimeStamp();
 printf("Connecting to %s: \n", ip);
 VHX4RC_RESULT result = VHX4RC_Init(strAddress);
 cout << getTimeStamp();
 printf("Connected to %s: ", ip);
 printResultMsg(result);
 errorCode = getExitCode(result);
 if (result != VHX4RC_S_OK) {
  //VHX4RC_StopAutoFocusMode();  //CW: why do we need this when startAFMode was never called
  //Sleep(100);
  return 1000;
 }
 MonitoredSleep(timeConnect);
 //Set Lens Magnificiation
 int currLensMag;
 cout << getTimeStamp();
 printf("Getting lens current magnification:\n");
 result = VHX4RC_GetLensPower(&currLensMag);
 cout << getTimeStamp();
 printf("Done Getting lens current magnification: ");
 printResultMsg(result);
 Sleep(100); //CW: why do we need this sleep?  Can we immediately print currLensMag?
 cout << getTimeStamp();
 printf("Current magnification: %dx\n", currLensMag);
 if (currLensMag != lensMag) {
  cout << getTimeStamp();
  printf("Switching lens magnification to %dx: ", lensMag);
  result = VHX4RC_SetLensPower(lensMag);
  cout << getTimeStamp();
  printf("Done Switching lens magnification to %dx: ", lensMag);
  printResultMsg(result);
  errorCode = getExitCode(result);
  if (result == VHX4RC_E_Z_STAGE_DISCONNECTED) {
   //VHX4RC_StopAutoFocusMode(); //CW: Why do we need this?
   //Sleep(100);
   return errorCode;
  }
  Sleep(3000); //CW: What is this sleep for?  Allow lens to rotate? 
 }
 //Move the stage to (X, Y)
 int currX, currY;
 VHX4RC_XYStageGetPos(&currX, &currY);
 int distance = ceil(sqrt(pow(currX - X, 2) + pow(currY - Y, 2)));
 int speed = 6808;
 int movetime = 1000 * (ceil(distance / speed)) + 1500;
 movetime = ceil(alpha * movetime);
 cout << getTimeStamp();
 printf("Moving XY Stage to (%d, %d): \n", X, Y);
 result = VHX4RC_XYStageMoveTo(X, Y);
 cout << getTimeStamp();
 printf("Done Moving XY Stage to (%d, %d): ", X, Y);
 printResultMsg(result);
 errorCode = getExitCode(result);
 if (result == VHX4RC_E_XY_STAGE_DISCONNECTED || result == VHX4RC_E_XY_STAGE_NOT_INITIALIZED) {
  //VHX4RC_StopAutoFocusMode();
  //Sleep(100);
  return errorCode;
 }
 MonitoredSleep(movetime);

 MoveZ(11400, 13800);
 Sleep(2000);
 MoveToZWithPhotos(17000.0,"image");
 //Allow stage to finish moving
 //for adjusting too high lens
 printf("Starting Quick Composition Mode:");
  result = VHX4RC_StartQuickCompMode();
  print(result);
  errorout(result);
  Sleep(100);
  printf("Start QuickComp:");
  result = VHX4RC_StartQuickComp(dummyHWND, WM_APP_QUICK_COMP_COMPLETED);
  print(result);
  errorout(result);
  Sleep(QuickCompSleep);
  //printf("2b. After 2s sleep");

  //filename here
  string filenameinit = Path;
  filenameinit = filenameinit + ".jpg";

  LPCSTR filename = filenameinit.c_str();
  printf("Stop QuickComp:");
  result = VHX4RC_StopQuickComp();
  print(result);
  errorout(result);
  Sleep(ProccesingQucikCompTime);
  printf("Save Image:");
  result = VHX4RC_SaveImageRemotePCA(0, filename);
  print(result);
  errorout(result);
  Sleep(100);
  printf("End Qucick Compostion Mode:");
  result= VHX4RC_StopQuickCompMode();
  print(result);
  errorout(result);
 
 MonitoredSleep(100);
 cout << getTimeStamp();
 printf("Disconnecting\n");
 VHX4RC_Exit(FALSE);
 cout << getTimeStamp();
 printf("Done Disconnecting\n");
 MonitoredSleep(1500);
 return (errorCode);
}