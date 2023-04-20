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
	void get_txt(string file_name);//得到需要加密的文件
	void decry_get_txt(string file_name);//得到需要解密的文件
	void get_fkey(string key_file_name);//得到使用的AES密钥
	void decry_key(string key_file_name);//用私钥解密AES
	ZZ encry_key(string key_file_name);//加密AES的密钥
public:
	void get_aRSA(int Z_n = 512);//得到一组RSA密钥
	void encrye_txt(string file_name, string key_file_name);//加密文件，加密的文件在另一个文件中
	void decry_txt(string file_name, string key_file_name);//解密文件，解密的文件在另一个文件中
	void re_encrye_txt(string file_name, string key_file_name);//加密文件，并将原文件覆盖
	void re_decry_txt(string file_name, string key_file_name);//解密文件，并将原文件覆盖
};

void get_dir(string path, string sdir[], int& len);//获得当前目录所以文件名
ZZ Z_mul(ZZ b, ZZ c, ZZ n);//模n的b*c
ZZ get_prim(int n);//获得一个n长度的素数
ZZ random_ZZ(int n);//获得n长度的随机数
void Euclidean(ZZ a, ZZ b, ZZ& gcd, ZZ& t);//拓展欧几里得算法，gcd为a，b的公因数，gcd=1，t就是b的逆元
ZZ rsa_jiemi(ZZ y, ZZ a, ZZ n);//rsa解密