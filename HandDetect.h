
#ifdef HANDDETECT_EXPORTS
#define HANDDETECT_API extern"C" __declspec(dllexport)
#else
#define HANDDETECT_API extern"C" __declspec(dllimport)
#endif


HANDDETECT_API int _stdcall HandDetect(BYTE*Src, int w, int h); //依次输入灰度图像,宽，高。 返回0为左手，1为右手，-1为输入数据错误或无法识别
