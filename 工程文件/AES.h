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
	byte S_change(byte in, bool is_encry);//�����S�б任
	void get_txt(byte in[16]);//�����Ҫ����txt
	void get_key(byte in[16]);//�õ���Կ
	void AddRoundKey(byte in[16], byte out[16], int w_n);//����Կ���
	void SubBytes(byte in[16], byte out[16]);//S�в���
	void ShiftRows(byte in[16], byte out[16]);//����λ
	byte GFMul(byte a, byte b);//
	void MixColumns(byte in[16], byte out[16]);//�л��
	void once(byte in[16], byte out[16], int w_n);//һ�ֲ���
	void InvShiftRows(byte in[16], byte out[16]);//�����õ�����λ
	void InvSubBytes(byte in[16], byte out[16]);//�����õ�S�в���
	void InvMixColumns(byte in[16], byte out[16]);//�����õ��л��
	void decode_once(byte in[16], byte out[16], int w_n);//���ܵ�һ�ֲ���
public:
	void aes(byte in[16], byte key[16], byte out[16]);//aes����
	void aes_decode(byte in[16], byte key[16], byte out[16]);//����
};
