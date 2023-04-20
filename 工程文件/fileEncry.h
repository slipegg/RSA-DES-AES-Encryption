#pragma once
#include <iostream>
#include<string>
#include <cstdlib>
#include <fstream>
#include <bitset>
#include <NTL/ZZ.h>
#include<fstream>
#include <windows.h>
#include"conio.h" 
#include"AES.h"
#include<sstream>
using namespace std;
using namespace NTL;
class fileEncry
{
private:
	char* txt;
	byte* encry_txt;
	int len;
	ZZ p, q, n, f_n, a, b;
	byte fkey[16];
	void get_txt(string file_name);//�õ���Ҫ���ܵ��ļ�
	void decry_get_txt(string file_name);//�õ���Ҫ���ܵ��ļ�
	void get_fkey(string key_file_name);//�õ�ʹ�õ�AES��Կ
	void decry_key(string key_file_name);//��˽Կ����AES
	ZZ encry_key(string key_file_name);//����AES����Կ
public:
	void get_aRSA(int Z_n = 512);//�õ�һ��RSA��Կ
	void encrye_txt(string file_name, string key_file_name);//�����ļ������ܵ��ļ�����һ���ļ���
	void decry_txt(string file_name, string key_file_name);//�����ļ������ܵ��ļ�����һ���ļ���
	void re_encrye_txt(string file_name, string key_file_name);//�����ļ�������ԭ�ļ�����
	void re_decry_txt(string file_name, string key_file_name);//�����ļ�������ԭ�ļ�����
};

void get_dir(string path, string sdir[], int& len);//��õ�ǰĿ¼�����ļ���
ZZ Z_mul(ZZ b, ZZ c, ZZ n);//ģn��b*c
ZZ get_prim(int n);//���һ��n���ȵ�����
ZZ random_ZZ(int n);//���n���ȵ������
void Euclidean(ZZ a, ZZ b, ZZ& gcd, ZZ& t);//��չŷ������㷨��gcdΪa��b�Ĺ�������gcd=1��t����b����Ԫ
ZZ rsa_jiemi(ZZ y, ZZ a, ZZ n);//rsa����