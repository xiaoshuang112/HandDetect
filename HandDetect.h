
#ifdef HANDDETECT_EXPORTS
#define HANDDETECT_API extern"C" __declspec(dllexport)
#else
#define HANDDETECT_API extern"C" __declspec(dllimport)
#endif


HANDDETECT_API int _stdcall HandDetect(BYTE*Src, int w, int h); //��������Ҷ�ͼ��,���ߡ� ����0Ϊ���֣�1Ϊ���֣�-1Ϊ�������ݴ�����޷�ʶ��
