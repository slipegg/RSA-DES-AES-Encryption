#include <iostream>
#include <io.h>
#include <string>
using namespace std;
void get_dir(string path,string sdir[],int &len)//�����õ�path�µ������ļ������ļ�������������
{
	long hFile = 0;
	string copypath = path;
	struct _finddata_t fileInfo;
	string pathName, exdName;

	if ((hFile = _findfirst(pathName.assign(path).append("\\*").c_str(), &fileInfo)) == -1) {
		return;
	}
	do
	{
		if (!(fileInfo.attrib & _A_SUBDIR))//���ļ����ԵĲż�������
		{
			//cout << fileInfo.name << endl;
			sdir[len++] = copypath+"\\"+fileInfo.name;
		}
	} while (_findnext(hFile, &fileInfo) == 0);
	_findclose(hFile);
}
/*
int dir_test()
{
	//Ҫ������Ŀ¼
	string path = ".\\test";
	string sdir[200];
	int dlen=0;
	get_dir(path,sdir,dlen);
	for (int i = 0; i < dlen; i++)
		cout << sdir[i] << endl;
	system("pause");
	return 0;
}*/