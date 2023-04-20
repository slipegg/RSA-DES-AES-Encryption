#pragma once
#include <iostream>
#include<string>
#include <cstdlib>
#include <fstream>
#include <bitset>

#include <windows.h>
using namespace std;
class AES
{
private:
	byte or_key[16];
	byte w[11][4][4];
	byte txt[16];
	byte S_change(byte in, bool is_encry);//具体的S盒变换
	void get_txt(byte in[16]);//获得需要加密txt
	void get_key(byte in[16]);//得到密钥
	void AddRoundKey(byte in[16], byte out[16], int w_n);//轮密钥异或
	void SubBytes(byte in[16], byte out[16]);//S盒操作
	void ShiftRows(byte in[16], byte out[16]);//行移位
	byte GFMul(byte a, byte b);//
	void MixColumns(byte in[16], byte out[16]);//列混合
	void once(byte in[16], byte out[16], int w_n);//一轮操作
	void InvShiftRows(byte in[16], byte out[16]);//解密用的行移位
	void InvSubBytes(byte in[16], byte out[16]);//解密用的S盒操作
	void InvMixColumns(byte in[16], byte out[16]);//解密用的列混合
	void decode_once(byte in[16], byte out[16], int w_n);//解密的一轮操作
public:
	void aes(byte in[16], byte key[16], byte out[16]);//aes加密
	void aes_decode(byte in[16], byte key[16], byte out[16]);//解密
};
