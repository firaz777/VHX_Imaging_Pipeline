#pragma once
#include "afxwin.h"

//Firaz's Comments 
/*
-Must put in a sleep after every quick compositon mode function or will thorw error(ensure sleep is long enough)
-Cannot move XY Stage Unless Theta initalization has been done, but only need to be done once per start up
-Cannot mve XY Stage in Quick Compostion Mode
-

*/
extern "C"
{

typedef HRESULT	VHX4RC_RESULT;

//
// エラーコード
//
/// <summary>
/// Normal termination
/// </summary>
/// <remarks>
/// </remarks>
#define VHX4RC_S_OK						0x00000000

/// <summary>
/// Unknown error
/// </summary>
/// <remarks>
/// </remarks>
#define VHX4RC_E_COMMAND_FAILED			0x80000001

/// <summary>
/// Initialization completed
/// </summary>
/// <remarks>
/// </remarks>
#define VHX4RC_E_ALREADY_INITIALIZED	0x80000002

/// <summary>
/// Not yet initialized
/// </summary>
#define VHX4RC_E_NOT_INITIALIZED		0x80000003

/// <summary>
/// Failed to communicate with VHX, communication error
/// </summary>
/// <remarks>
/// </remarks>
#define VHX4RC_E_COMM_ERROR				0x80000004

/// <summary>
/// Argument is invalid
/// </summary>
/// <remarks>
/// </remarks>
#define VHX4RC_E_INVALID_ARGUMENT		0x80000005

/// <summary>
/// Insufficient memory
/// </summary>
/// <remarks>
/// </remarks>
#define VHX4RC_E_OUTOFMEMORY			0x80000006

/// <summary>
/// Path does not exist
/// </summary>
/// <remarks>
/// </remarks>
#define VHX4RC_E_PATH_NOT_FOUND			0x80000007

/// <summary>
/// Failed to save the file
/// </summary>
/// <remarks>
/// </remarks>
#define VHX4RC_E_SAVE_FILE_FAILED		0x80000008

/// <summary>
/// File with same name already exists
/// </summary>
/// <remarks>
/// </remarks>
#define VHX4RC_E_FILE_ALREADY_EXISTS	0x80000009

/// <summary>
/// Mode does not allow request execution
/// </summary>
/// <remarks>
/// </remarks>
#define VHX4RC_E_INVALID_MODE			0x8000000A

/// <summary>
/// State does not allow request execution
/// </summary>
/// <remarks>
/// </remarks>
#define VHX4RC_E_INVALID_STATE			0x8000000B

/// <summary>
/// Ｚ stage is required but not yet connected
/// </summary>
/// <remarks>
/// </remarks>
#define VHX4RC_E_Z_STAGE_NOTHING		0x8000000C

/// <summary>
/// Disconnected during Ｚ stage processing
/// </summary>
/// <remarks>
/// </remarks>
#define VHX4RC_E_Z_STAGE_DISCONNECTED	0x8000000D

/// <summary>
/// Invalid handle
/// </summary>
/// <remarks>
/// </remarks>
#define VHX4RC_E_INVALID_HANDLE			0x8000000E

/// <summary>
/// Facility is not supported by the current version
/// </summary>
/// <remarks>
/// </remarks>
#define VHX4RC_E_NOT_SUPPORT			0x8000000F

/// <summary>
/// 合計枚数が上限を超えた
/// </summary>
/// <remarks>
/// </remarks>
#define VHX4RC_E_OUTOFCOMPLIMIT			0x80000010

/// <summary>
/// XYステージが接続されていない
/// </summary>
/// <remarks>
/// </remarks>
#define VHX4RC_E_XY_STAGE_DISCONNECTED	0x80000011

/// <summary>
/// XY stage is not yet initialized
/// </summary>
/// <remarks>
/// </remarks>
#define VHX4RC_E_XY_STAGE_NOT_INITIALIZED	0x80000012


//
// モード(VHX4RC_GetCurrentModeで取得したモード)
//
/// <summary>
/// Command idle mode
/// </summary>
#define VHX4RC_VHXMODE_IDLE				0x00000000

/// <summary>
/// Auto focus mode
/// </summary>
#define VHX4RC_VHXMODE_AUTOFOCUS		0x00000001

/// <summary>
/// Quick composition mode
/// </summary>
#define VHX4RC_VHXMODE_QUICKCOMP		0x00000002

/// <summary>
/// Shake correction mode
/// </summary>
#define VHX4RC_VHXMODE_SHAKECORRECTION	0x00000004

/// <summary>
/// HDR operating mode
/// </summary>
#define VHX4RC_VHXMODE_HDR				0x00000010

/// <summary>
/// Glare removal mode
/// </summary>
#define VHX4RC_VHXMODE_REMOVEGLARE		0x00000020


//
// 画像フォーマット
//
/// <summary>
/// JPEG
/// </summary>
#define VHX4RC_IMAGEMODE_JPEG			0

/// <summary>
/// TIFF
/// </summary>
#define VHX4RC_IMAGEMODE_TIFF			1


//
// クイック深度合成の完了内容
//
/// <summary>
/// Normal stop
/// </summary>
#define VHX4RC_QUICKCOMP_NORMAL			0

/// <summary>
/// Reached the upper limit of the Lens Z
/// </summary>
#define VHX4RC_QUICKCOMP_LENSZLIMIT	1

/// <summary>
/// Reached the maximum number of compositions
/// </summary>
#define VHX4RC_QUICKCOMP_COUNTLIMIT		2

/// <summary>
/// Stop due to error
/// </summary>
#define VHX4RC_QUICKCOMP_ERROR			3

/// <summary>
/// Stop due to communication error
/// </summary>
#define VHX4RC_QUICKCOMP_NETWORK		4


//
// クイック深度合成の上下限／現在位置から上移動のモード
//
/// <summary>
/// Move to up
/// </summary>
#define VHX4RC_QUICKCOMPMOVEMODE_MOVETOUP		0

/// <summary>
/// Lower to upper
/// </summary>
#define VHX4RC_QUICKCOMPMOVEMODE_LOWERTOUPPER	1

//
// HDRのパラメータ種別
//
/// <summary>
/// Default setting
/// </summary>
#define VHX4RC_HDRITEM_DEFAULT			0

/// <summary>
/// Brightness
/// </summary>
#define VHX4RC_HDRITEM_BRIGHTNESS		1

/// <summary>
/// Texture
/// </summary>
#define VHX4RC_HDRITEM_TEXTURE			2

/// <summary>
/// Contrast
/// </summary>
#define VHX4RC_HDRITEM_CONTRAST			3

/// <summary>
/// Color(saturation)
/// </summary>
#define VHX4RC_HDRITEM_SATURATION		4


//
// オートフォーカスエリアのサイズ
//
/// <summary>
/// Area size (S)
/// </summary>
#define VHX4RC_AUTOFOCUS_S				0

/// <summary>
/// Area size (M)
/// </summary>
#define VHX4RC_AUTOFOCUS_M				1

/// <summary>
/// Area size (L)
/// </summary>
#define VHX4RC_AUTOFOCUS_L				2

/// <summary>
/// Area size (XL)
/// </summary>
#define VHX4RC_AUTOFOCUS_XL				3


//
// オートフォーカスの完了内容
//
/// <summary>
/// Succeeded
/// </summary>
#define VHX4RC_AUTOFOCUS_SUCCEEDED		0

/// <summary>
/// Failed
/// </summary>
#define VHX4RC_AUTOFOCUS_FAILED			1

/// <summary>
/// Canceled
/// </summary>
#define VHX4RC_AUTOFOCUS_CANCELED		2

/// <summary>
/// Error
/// </summary>
#define VHX4RC_AUTOFOCUS_ERROR			3

/// <summary>
/// Communication error
/// </summary>
#define VHX4RC_AUTOFOCUS_NETWORK		4


//
// XYステージθ初期化の完了内容
//
/// <summary>
/// Succeeded
/// </summary>
#define VHX4RC_INITIALIZE_SUCCEEDED		0

/// <summary>
/// Failed
/// </summary>
#define VHX4RC_INITIALIZE_FAILED		1

/// <summary>
/// Network error
/// </summary>
#define VHX4RC_INITIALIZE_NETWORK		2


//
// XYステージの状態
//
/// <summary>
/// Idle
/// </summary>
#define VHX4RC_XYSTAGE_IDLE				0

/// <summary>
/// Not initialized
/// </summary>
#define VHX4RC_XYSTAGE_NOT_INITIALIZED	1

/// <summary>
/// Moving
/// </summary>
#define VHX4RC_XYSTAGE_MOVING			2


/// <summary>
/// Establishes a connection with the VHX unit and sets the VHX to remote control mode.
/// Remote control commands can then be sent.
/// </summary>
/// <remarks>
/// At startup of remote control, the VHX must satisfy the following conditions:
/// ・VHX observation screen is displayed (main menu is displayed and no commands in progress)
/// Startup is not possible in HDR, glare removal, or split screen mode.
/// In addition, startup is not possible in measurement mode/album/3D display/moving image playback/3D profile measurement/wide view/XY stage measurement/image stitching  screens,etc.
/// </remarks>
/// <param name="pszVHXIPAddress">IP address of the VHX (v4) to be connected (ex. "192.168.0.5")</param>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_InitA(LPCSTR pszVHXIPAddress);
VHX4RC_RESULT WINAPI VHX4RC_InitW(LPCWSTR pszVHXIPAddress);
#ifdef UNICODE
#define VHX4RC_Init VHX4RC_InitW
#else
#define VHX4RC_Init VHX4RC_InitA
#endif

/// <summary>
/// Initializes for remote control.
/// </summary>
/// <remarks>
/// At startup of remote control, the VHX must satisfy the following conditions:
/// ・VHX observation screen is displayed (main menu is displayed and no commands in progress)
/// Startup is not possible in HDR, glare removal, or split screen mode.
/// In addition, startup is not possible in measurement mode/album/3D display/moving image playback/3D profile measurement/wide view/XY stage measurement/image stitching  screens,etc.
/// </remarks>
/// <param name="pszVHXIPAddress">IP address of the VHX (v6) to be connected(ex. "2001:db8::dead:beaf")</param>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_Init6A(LPCSTR pszVHXIPAddress);
VHX4RC_RESULT WINAPI VHX4RC_Init6W(LPCWSTR pszVHXIPAddress);
#ifdef UNICODE
#define VHX4RC_Init6 VHX4RC_Init6W
#else
#define VHX4RC_Init6 VHX4RC_Init6A
#endif

/// <summary>
///  Obtains the current operation mode.
/// </summary>
/// <remarks>
/// The value of each operation mode is a combination of the following values.
/// VHX4RC_VHXMODE_IDLE			    = 0x00000000	// Command idle mode
/// VHX4RC_VHXMODE_AUTOFOCUS		= 0x00000001	// Auto focus mode
/// VHX4RC_VHXMODE_QUICKCOMP		= 0x00000002	// Quick composition mode
/// VHX4RC_VHXMODE_SHAKECORRECTION	= 0x00000004	// Shake correction mode
/// VHX4RC_VHXMODE_HDR			    = 0x00000010	// HDR operating mode
/// VHX4RC_VHXMODE_REMOVEGLARE		= 0x00000020	// Glare removal mode
/// </remarks>
/// <param name="plCurrentMode">Store the current operation mode and return it</param>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_GetCurrentMode(long* plCurrentMode);

/// <summary>
/// Exits remote control mode and cuts the connection.
/// </summary>
/// <remarks>
/// Return the screen to the main menu ( auto focus mode/HDR mode/quick composition mode are OFF) before calling this function.
/// </remarks>
/// <param name="bShutdown">If not 0: Cut the connection. The VHX enters the shutdown operation.0: Only cut the connection.</param>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_Exit(BOOL bShutdown);

/// <summary>
/// Moves the Lens Z UP (1 step/high-speed step)
/// </summary>
/// <remarks>
/// You cannot specify the distance of 1 step in [um]. The distance automatically calculated from the lens magnification defines 1 step.
/// The distance for one high-speed step is equal to 10 steps.
/// If you call this function in LOCK OFF state while the VHX-S50F/90F is connected, the VHX automatically switches to LOCK ON and the Lens Z is moved. If the lens magnification
/// after movement of the Lens Z is 300x or less, the VHX automatically switches to LOCK OFF.
/// </remarks>
/// <param name="bLongStep">If not 0: Move by high-speed step 0: Move by 1 step</param>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_LensZUp(BOOL bLongStep);

/// <summary>
/// Moves the Lens Z DOWN (1 step/high-speed step)
/// </summary>
/// <remarks>
/// You cannot specify the distance of 1 step in [um]. The distance automatically calculated from the lens magnification defines 1 step.
/// The distance for one high-speed step is equal to 10 steps.
/// If you call this function in LOCK OFF state while the VHX-S50F/90F is connected, the VHX automatically switches to LOCK ON and the Lens Z is moved. If the lens magnification
/// after movement of the Lens Z is 300x or less, the VHX automatically switches to LOCK OFF.
/// </remarks>
/// <param name="bLongStep">If not 0: Move by high-speed step 0: Move by 1 step</param>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_LensZDown(BOOL bLongStep);

/// <summary>
/// Obtains the current position of the Lens Z.
/// </summary>
/// <remarks></remarks>
/// <param name="plPos">Current position of the Lens Z [in units of 1um]。</param>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_GetLensZPos(double* plPos);

/// <summary>
/// Starts the auto focus mode.
/// </summary>
/// <remarks>The VHX cannot enter this mode while it is in shake correction mode, HDR mode, glare removal mode, or quick composition mode.</remarks>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_StartAutoFocusMode();

/// <summary>
/// Stops the auto focus mode.
/// </summary>
/// <remarks>You cannot call this function in any mode other than auto focus mode.</remarks>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_StopAutoFocusMode();

/// <summary>
/// Sets the auto focus area size.
/// </summary>
/// <remarks>
/// The size of each area is S:64X64pix, M:128X128pix, L:256X256pix,
///	XL: 512X512pix. The position of the auto focus area is the center of the screen.
///	You cannot call this function in any mode other than auto focus mode.
/// </remarks>
/// <param name="nSize">Auto focus area size(0 to 3)</param>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_SetAutoFocusAreaSize(int nSize);

/// <summary>
/// Obtains the auto focus area size.
/// </summary>
/// <remarks>
/// The size of each area is S:64X64pix, M:128X128pix, L:256X256pix,
///	XL: 512X512pix. The position of the auto focus area is the center of the screen.
///	You cannot call this function in any mode other than auto focus mode.
/// </remarks>
/// <param name="pnSize">Auto focus area size</param>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_GetAutoFocusAreaSize(int* pnSize);

/// <summary>
/// Starts the auto focus operation.
/// </summary>
/// <remarks>
/// The VHX searches for the focus position above the current position of the Lens Z.
/// This function is asynchronous, and completion of auto focus is reported by dwMessageId specified in the arguments. The message arguments are:
///    WPARAM・・・Auto focus result
///     VHX2RC_AUTOFOCUS_SUCCEEDED	= 0	// Succeeded
///     VHX2RC_AUTOFOCUS_FAILED		= 1	// Failed
///     VHX2RC_AUTOFOCUS_CANCELED	= 2	// Canceled
///     VHX2RC_AUTOFOCUS_ERROR		= 3	// Error
///     VHX2RC_AUTOFOCUS_NETWORK	= 4	// Communication error
/// 
///   LPARAM???Auto focus evaluation value (enabled only when successful)
/// You cannot call this function in any mode other than auto focus mode.
/// Furthermore, you cannot call another function between the time that you call this function and the time at which the function is completed (the time at which the window message is reported).
/// </remarks>
/// <param name="hWnd">Window handle of the destination for auto focus completion notification</param>
/// <param name="dwMessageId">Window message ID of the auto focus completion notification</param>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_StartAutoFocus(HWND hWnd, DWORD dwMessageId);

/// <summary>
/// Stops the active auto focus operation.
/// </summary>
/// <remarks>
/// If you call this function while auto focus is executing, you will stop the auto focus process. 
/// This function stops movement of the Lens Z. When you call this function, a window message is reported in hWnd and dwMessageId specified in VHX2RC_StartAutoFocus. 
/// At this time, VHX2RC_AUTOFOCUS_CANCELED (canceled) is stored in WPARAM.
/// You cannot call this function in any mode other than auto focus mode.
/// </remarks>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_StopAutoFocus();

/// <summary>
/// Turns the VHX-S50F/S90F (Lens Z) lock ON/OFF.
/// </summary>
/// <remarks>
/// This function is effective only when VHX-S50F/S90F is connected. It is not effective when VHX-S15 is connected.
/// When the VHX-S15 is connected, the Lens Z lock is always ON.
/// If the lens magnification is 300x or less when the VHX-S50F/S90F is connected, the VHX automatically switches to LOCK OFF after the Lens Z has been operated.
/// If the Lens Z is operated at total magnification in LOCK OFF state, operating the Lens Z causes the state to switch automatically to LOCK ON.
/// </remarks>
/// <param name="bLockMode">If not 0: LOCK ON. 0: LOCK OFF.</param>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_SetZLockMode(BOOL bLockMode);

/// <summary>
/// Obtains the Lens Z LOCK state.
/// </summary>
/// <remarks></remarks>
/// <param name="pbLockMode">If not 0: LOCK ON state 0: LOCK OFF state</param>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_GetZLockMode(BOOL* pbLockMode);

/// <summary>
/// Save current image in VHX hard disk path.
/// </summary>
/// <remarks>
/// ? The specified folder must already exist.
///	? The image size must be the standard size.
///	? The specified image format mode and the extension of the save filename must match. (JEPG->***.jpg、TIFF->***.tif)
///	? When saving to C drive, be aware of the system protection state.
/// ? Note that the VHX album displays the folders beneath a specific folder in D drive.
///	? An error occurs if a file having the same name already exists.
/// </remarks>
/// <param name="nImageMode">Support the following image format modes (0:JPEG,1:TIFF)</param>
/// <param name="pszSaveFileName">Full path filename within the target VHX hard disk</param>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_SaveImageVHXHDDA(int nImageMode, LPCSTR pszSaveFileName);
VHX4RC_RESULT WINAPI VHX4RC_SaveImageVHXHDDW(int nImageMode, LPCWSTR pszSaveFileName);
#ifdef UNICODE
#define VHX4RC_SaveImageVHXHDD VHX4RC_SaveImageVHXHDDW
#else
#define VHX4RC_SaveImageVHXHDD VHX4RC_SaveImageVHXHDDA
#endif

/// <summary>
/// Save current VHX image in remote control PC path.
/// </summary>
/// <remarks>
/// ? The specified folder must already exist.
/// ? The image size must be the standard size.
/// ? The specified image format mode and the extension of the save filename must match. (JPEG->***.jpg、TIFF->***.tif)
/// ? An error occurs if a file having the same name already exists.
/// </remarks>
/// <param name="nImageMode">Support the following image format modes. (0:JPEG,1:TIFF)</param>
/// <param name="pszSaveFileName">Full path filename of the target remote control PC</param>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_SaveImageRemotePCA(int nImageMode, LPCSTR pszSaveFileName);
VHX4RC_RESULT WINAPI VHX4RC_SaveImageRemotePCW(int nImageMode, LPCWSTR pszSaveFileName);
#ifdef UNICODE
#define VHX4RC_SaveImageRemotePC VHX4RC_SaveImageRemotePCW
#else
#define VHX4RC_SaveImageRemotePC VHX4RC_SaveImageRemotePCA
#endif

/// <summary>
/// Adjusts the brightness parameter.
/// </summary>
/// <remarks></remarks>
/// <param name="nBrightnessValue">Set the brightness value (0 to 511)</param>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_SetBrightnessValue(int nBrightnessValue);

/// <summary>
/// Changes the lens magnification setting.
/// </summary>
/// <remarks></remarks>
/// <param name="nLensPower">Numerical value of the set lens magnification</param>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_SetLensPower(int nLensPower);

/// <summary>
/// Obtains the lens magnification that is set currently.
/// </summary>
/// <remarks></remarks>
/// <param name="pnLensPower">int* LensPower</param>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_GetLensPower(int* pnLensPower);

/// <summary>
/// Starts the shake correction mode.
/// </summary>
/// <remarks>This function can only be called while the main menu is being displayed (no commands in progress).</remarks>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_StartShakeCorrectionMode();

/// <summary>
/// Stops the shake correction mode
/// </summary>
/// <remarks></remarks>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_StopShakeCorrectionMode();

/// <summary>
/// Starts the glare removal mode.
/// </summary>
/// <remarks>This function can only be called while the main menu is being displayed (no commands in progress).</remarks>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_StartRemoveGlareMode();

/// <summary>
/// Stops the glare removal mode.
/// </summary>
/// <remarks></remarks>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_StopRemoveGlareMode();

/// <summary>
/// Sets the brightness parameter value for glare removal.
/// </summary>
/// <remarks>This function can be used only in glare removal mode.</remarks>
/// <param name="nBrightness">Value of the brightness parameter (0 to 100)</param>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_SetRemoveGlareVal(int nBrightness);

/// <summary>
/// Obtains the brightness parameter value for glare removal mode.
/// </summary>
/// <remarks>This function can be used only in glare removal mode.</remarks>
/// <param name="pnBrightness">Brightness parameter that is currently set (0 to 100)</param>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_GetRemoveGlareVal(int* pnBrightness);

/// <summary>
/// Starts the quick composition mode.
/// </summary>
/// <remarks>
/// This function can only be called while the main menu is being displayed.
/// In quick composition mode, the HDR and glare removal facilities are available.
/// However, it is not possible to transition to the quick composition mode from the HDR mode
/// or glare removal mode.
/// </remarks>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_StartQuickCompMode();

/// <summary>
/// Stops the quick composition mode.
/// </summary>
/// <remarks></remarks>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_StopQuickCompMode();

/// <summary>
/// Starts quick composition processing.
/// </summary>
/// <remarks>
/// This function can only be called in quick composition mode.
/// Construct a depth composition while moving up from the current Lens Z position. 
/// [simplified mode]
/// This function is asynchronous, and completion of quick composition is reported to the arguments 
/// window by the message ID specified in dwMessageId.
/// Meaning of the reported message
/// WPARAM・・・Cause of the stop
///     VHX4RC_QUICKCOMP_NORMAL 	 = 0 // Normal stop
///     VHX4RC_QUICKCOMP_LENSZLIMIT = 1 // Reached the upper limit of the Lens Z
///	    VHX4RC_QUICKCOMP_COUNTLIMIT  = 2 // Reached the maximum number of compositions
///	    VHX4RC_QUICKCOMP_ERROR 	     = 3 // Stop due to error
///	    VHX4RC_QUICKCOMP_NETWORK 	 = 4 // Stop due to communication error
/// 
///	LPARAM??? Current Z position [in units of 1um]
///           The conditions for stopping quick composition are:
///	? VHX4RC_StopQuickComp( ) is called
/// ? The upper limit of the Lens Z is reached
/// ? The maximum composition count of 200 is reached
/// ? A communication error or error due to disconnection of the Lens Z occurs
///  If quick composition stops for any of the above reasons, a message is reported.
///  If you call VHX4RC_StopQuickComp( ) and then call VHX4RC_QuickCompStart( ) again,
///  the composition result is retained and the depth composition is continued or restarted.
/// </remarks>
/// <param name="hWnd">Window handle of the destination for quick composition completion notification</param>
/// <param name="dwMessageId">Window message ID of the quick composition completion notification</param>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_StartQuickComp(HWND hWnd, DWORD dwMessageId);

/// <summary>
/// Stops quick composition and pauses the image.
/// </summary>
/// <remarks>
/// This function can only be called in quick composition mode.
/// If the Lens Z stops after this function has been called, a message is reported to the window
///	handle specified in StartQuickComp(). The application switches to Pause state.
/// </remarks>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_StopQuickComp();

/// <summary>
/// Discards the quick composition result.
/// </summary>
/// <remarks>
/// If this function is called after VHX4RC_StartQuickComp( ), the Lens Z is stopped, the composition result is discarded, and the application switches to the state for displaying live images.
/// If this function is called after VHX4RC_StopQuickComp( ), the application remains paused and the composition result is internally discarded.
/// </remarks>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_ResetQuickComp();

/// <summary>
/// Starts the HDR mode.
/// </summary>
/// <remarks>This function can be called while the main menu is being displayed (no commands in progress).</remarks>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_StartHDRMode();

/// <summary>
/// Stop the HDR mode.
/// </summary>
/// <remarks></remarks>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_StopHDRMode();

/// <summary>
/// Adjusts the HDR parameter.
/// </summary>
/// <remarks>This function can only be called in HDR mode.</remarks>
/// <param name="nParam">HDR parameter types (0 to 4)</param>
/// <param name="nValue">Parameter value (0 to 100)</param>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_SetHDRVal(int nParam, int nValue);

/// <summary>
/// HDRパラメータを取得します。
/// </summary>
/// <remarks>This function is effective only when HDR mode is ON.</remarks>
/// <param name="nParam">HDR parameter types (1 to 4)</param>
/// <param name="pnValue">Parameter value</param>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_GetHDRVal(int nParam, int* pnValue);

/// <summary>
/// Calls the user settings.
/// </summary>
/// <remarks>This function can only be called while the main menu is being displayed (no commands in progress).</remarks>
/// <param name="nUserNumber">User setting number to be called (1 to 20)</param>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_LoadUserSetting(int nUserNumber);

/// <summary>
/// Turns the lamp ON/OFF.
/// </summary>
/// <remarks></remarks>
/// <param name="bLight">If not 0: Turn lamp ON. 0: Turn lamp OFF.</param>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_SetLight(BOOL bLight);

/// <summary>
/// Obtains the ON/OFF state of the lamp.
/// </summary>
/// <remarks></remarks>
/// <param name="pbLight">If not 0: Turn lamp ON. 0: Turn lamp OFF.</param>
/// <returns>VHX4RC_RESULT</returns>
VHX4RC_RESULT WINAPI VHX4RC_GetLight(BOOL* pbLight);

/// <summary>
/// XYステージ移動
/// </summary>
/// <param name="nPosX">移動先X座標を設定する</param>
/// <param name="nPosY">移動先Y座標を設定する</param>
/// <returns>実行結果を返します。</returns>
VHX4RC_RESULT WINAPI VHX4RC_XYStageMoveTo(int nPosX, int nPosY);

/// <summary>
/// XYステージの現在位置取得
/// </summary>
/// <param name="pnPosX">現在のX座標を取得する</param>
/// <param name="pnPosY">現在のY座標を取得する</param>
/// <returns>実行結果を返します。</returns>
VHX4RC_RESULT WINAPI VHX4RC_XYStageGetPos(int* pnPosX, int* pnPosY);

/// <summary>
/// XYステージのθ初期化を実行します。
/// </summary>
/// <param name="hWnd">完了通知メッセージを送るウィンドウハンドルを指定します。</param>
/// <param name="dwMessageId">hWndに送信するメッセージを指定します。</param>
/// <returns>処理結果を返します。</returns>
VHX4RC_RESULT WINAPI VHX4RC_XYStageInitializeThetaOrientation(HWND hWnd, DWORD dwMessageId);

/// <summary>
/// XYステージの状態を取得します。
/// </summary>
/// <param name="plCurrentXYStatus">XYステージの状態を取得する領域のアドレスを指定します。</param>
/// <returns>処理結果を返します。</returns>
VHX4RC_RESULT WINAPI VHX4RC_XYStageGetStatus(long* plCurrentXYStatus);

/// <summary>
/// XYステージを停止します。
/// </summary>
/// <returns>処理結果を返します。</returns>
VHX4RC_RESULT WINAPI VHX4RC_XYStageStop();

/// <summary>
/// XYステージを原点へ移動します。
/// </summary>
/// <returns>処理結果を返します。</returns>
VHX4RC_RESULT WINAPI VHX4RC_XYStageMoveToOrigin();

/// <summary>
/// クイック合成の上限位置を設定します。
/// </summary>
/// <returns>処理結果を返します。</returns>
VHX4RC_RESULT WINAPI VHX4RC_SetCurrentLensPositionAsUpperForQuickComp();

/// <summary>
/// クイック合成の下限位置を設定します。
/// </summary>
/// <returns>処理結果を返します。</returns>
VHX4RC_RESULT WINAPI VHX4RC_SetCurrentLensPositionAsLowerForQuickComp();

/// <summary>
/// クイック合成の上限位置を取得します。
/// </summary>
/// <param name="pUpper">クイック合成の上限位置[1um単位]</param>
/// <returns>処理結果を返します。</returns>
VHX4RC_RESULT WINAPI VHX4RC_GetUpperPositionForQuickComp(double* pUpper);

/// <summary>
/// クイック合成の下限位置を取得します。
/// </summary>
/// <param name="pLower">クイック合成の下限位置[1um単位]</param>
/// <returns>処理結果を返します。</returns>
VHX4RC_RESULT WINAPI VHX4RC_GetLowerPositionForQuickComp(double* pLower);

/// <summary>
/// クイック合成の移動モードを設定します。
/// </summary>
/// <param name="nMoveMode">上下限／現在位置から上移動のモード</param>
/// <returns>処理結果を返します。</returns>
VHX4RC_RESULT WINAPI VHX4RC_SetQuickCompMoveMode(int nMoveMode);

/// <summary>
/// クイック合成の移動モードを取得します。
/// </summary>
/// <param name="pnMoveMode">上下限／現在位置から上移動のモード</param>
/// <returns>処理結果を返します。</returns>
VHX4RC_RESULT WINAPI VHX4RC_GetQuickCompMoveMode(int* pnMoveMode);

/// <summary>
/// オートフォーカスエリア位置を設定します。
/// </summary>
/// <param name="nPosX">オートフォーカスエリアX方向ピクセル座標を設定する（0～2879)</param>
/// <param name="nPosY">オートフォーカスエリアY方向ピクセル座標を設定する（0～2159)</param>
/// <returns>実行結果を返します。</returns>
VHX4RC_RESULT WINAPI VHX4RC_SetAutoFocusAreaPosition(int nPosX, int nPosY);

/// <summary>
/// オートフォーカスエリア位置を取得します。
/// </summary>
/// <param name="pnPosX">オートフォーカスエリアX方向ピクセル座標を取得する（0～2879)</param>
/// <param name="pnPosY">オートフォーカスエリアY方向ピクセル座標を取得する（0～2159)</param>
/// <returns>実行結果を返します。</returns>
VHX4RC_RESULT WINAPI VHX4RC_GetAutoFocusAreaPosition(int* pnPosX, int* pnPosY);

/// <summary>
/// 照明を設定します。
/// </summary>
/// <param name="nLightShiftNumber">照明番号</param>
/// <returns>実行結果を返します。</returns>
VHX4RC_RESULT WINAPI VHX4RC_SetLightShift(int nLightShiftNumber);

/// <summary>
/// 照明を取得します。
/// </summary>
/// <param name="pnLightShiftNumber">照明番号を取得する</param>
/// <returns>実行結果を返します。</returns>
VHX4RC_RESULT WINAPI VHX4RC_GetLightShift(int* pnLightShiftNumber);

/// <summary>
/// 使用できる照明の個数を取得します。
/// </summary>
/// <param name="pnLightShiftCount">使用できる照明の個数を取得する</param>
/// <returns>実行結果を返します。</returns>
VHX4RC_RESULT WINAPI VHX4RC_GetLightShiftCount(int* pnLightShiftCount);

/// <summary>
/// 使用できる照明を取得します。
/// </summary>
/// <param name="pnLightShiftNumber">使用できる照明を取得する</param>
/// <param name="nLightShiftCount">取得する照明の個数</param>
/// <returns>実行結果を返します。</returns>
VHX4RC_RESULT WINAPI VHX4RC_GetLightShiftNumbers(int* pnLightShiftNumber, int nLightShiftCount);

/// <summary>
/// ZステージをUP（1ステップ/高速ステップ）
/// </summary>
/// <param name="bLongStep">0以外なら、高速ステップ移動。0なら、1ステップ移動</param>
/// <returns>実行結果を返します。</returns>
VHX4RC_RESULT WINAPI VHX4RC_StageZUp(BOOL bLongStep);

/// <summary>
/// ZステージをDOWN（1ステップ/高速ステップ）
/// </summary>
/// <param name="bLongStep">0以外なら、高速ステップ移動。0なら、1ステップ移動</param>
/// <returns>実行結果を返します。</returns>
VHX4RC_RESULT WINAPI VHX4RC_StageZDown(BOOL bLongStep);

/// <summary>
/// Zステージの現在位置を取得する
/// </summary>
/// <remarks></remarks>
/// <param name="plPos">Zステージの現在位置[1um単位]</param>
/// <returns>実行結果を返します。</returns>
VHX4RC_RESULT WINAPI VHX4RC_GetStageZPos(double* plPos);

/// <summary>
/// HRH撮影モードの変更
/// </summary>
/// <param name="nRecMode">撮影モード:標準(0)/高速(1)/高解像度(2)</param>
/// <returns>実行結果を返します。</returns>
VHX4RC_RESULT WINAPI VHX4RC_SetRecMode(int nRecMode);

/// <summary>
/// HRH撮影モードを取得
/// </summary>
/// <param name="pnRecMode">撮影モード:標準(0)/高速(1)/高解像度(2)</param>
/// <returns>実行結果を返します。</returns>
VHX4RC_RESULT WINAPI VHX4RC_GetRecMode(int* pnRecMode);

}
