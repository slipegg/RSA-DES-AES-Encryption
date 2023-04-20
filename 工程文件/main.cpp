#include"fileEncry.h"

int main()
{
	fileEncry f;
	
	while (1)//设置了一些简单的操作界面
	{
		char chose;
		while (1)
		{
			cout << "请输入数字选择功能ヾ(≧▽≦*)o" << endl << "1.生产新的RSA密钥      2.加密文件及AES密钥      3.解密文件       4.退出程序   \n5.当前目录全加密（小心）   6.当前目录全解密" << endl;
			chose = _getch();
			if (chose == '1' || chose == '2' || chose == '3' || chose == '5' || chose == '6')
			{
				break;
			}
			else if (chose == '4')
			{
				exit(0);
			}
			else
			{
				cout << "输入非法，请重新输入`(*>﹏<*)′" << endl << endl;
			}
		}
		if (chose == '1')
		{
			while (1)
			{
				cout << "请选择要产生的密钥长度（直接回车默认512位）：" << endl << "1.512位      2.1024位" << endl;
				char len;
				len = _getch();
				if (len == '1' || len == char(13))
				{
					f.get_aRSA(512);
					break;
				}
				else if (len == '2')
				{
					f.get_aRSA(1024);
					break;
				}
				else
				{
					cout << "输入非法，请重新输入φ(゜▽゜*)♪" << endl << endl;
				}
			}
		}
		else if (chose == '2')
		{
			string key_file_name = "AES密钥.txt";
			string file_name = "1.txt";
			string temp;
			cout << "请输入AES密钥的文件名(直接回车使用默认的：AES密钥.txt)：" << endl;
			getline(cin, temp);
			if (temp.length() != 0)
				key_file_name = temp;
			cout << "请输入要加密的文件的文件名(直接回车使用默认的：1.txt)：" << endl;
			getline(cin, temp);
			if (temp.length() != 0)
				file_name = temp;
			f.encrye_txt(file_name, key_file_name);
			cout << "加密完成，请去文件中看加密结果" << endl << endl;
		}
		else if (chose == '3')
		{
			string key_file_name = "加密_AES密钥.txt";
			string file_name = "加密_1.txt";
			string temp;
			cout << "请输入要解密的AES密钥的文件名(直接回车使用默认的：加密_AES密钥.txt)：" << endl;
			getline(cin, temp);
			if (temp.length() != 0)
				key_file_name = temp;
			cout << "请输入要解密的文件的文件名(直接回车使用默认的：加密_1.txt)：" << endl;
			getline(cin, temp);
			if (temp.length() != 0)
				file_name = temp;
			f.decry_txt(file_name, key_file_name);
			cout << "解密完成，请去文件中看解密结果" << endl << endl;
		}
		else if (chose == '5')
		{
			cout << "加密中..." << endl;
			string path = ".\\";
			string sdir[200];
			int dlen = 0;
			get_dir(path, sdir, dlen);
			for (int i = 0; i < dlen; i++)
			{
				if (sdir[i] != ".\\\\加密_AES密钥.txt" && sdir[i] != ".\\\\AES密钥.txt" && sdir[i] != ".\\\\公钥.txt" && sdir[i] != ".\\\\私钥.txt" && sdir[i] != ".\\\\SRA课设.exe")
				{
					cout << sdir[i] << endl;
					f.re_encrye_txt(sdir[i], "AES密钥.txt");
				}
			}
		}
		else if (chose == '6')
		{
			cout << "解密中..." << endl;
			string path = ".\\";
			string sdir[200];
			int dlen = 0;
			get_dir(path, sdir, dlen);
			for (int i = 0; i < dlen; i++)
			{
				if (sdir[i] != ".\\\\加密_AES密钥.txt" && sdir[i] != ".\\\\AES密钥.txt" && sdir[i] != ".\\\\公钥.txt" && sdir[i] != ".\\\\私钥.txt" && sdir[i] != ".\\\\SRA课设.exe")
				{
					cout << sdir[i] << endl;
					f.re_decry_txt(sdir[i], "加密_AES密钥.txt");
				}
			}
		}
	}
	return 0;
}
