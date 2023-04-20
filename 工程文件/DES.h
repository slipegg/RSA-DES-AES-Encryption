#pragma once
#include <bitset>
#include <iostream>
#include<string>
#include <cstdlib>
#include <fstream>
#include <bitset>
#include <NTL/ZZ.h>
#include <windows.h>
using namespace std;
using namespace NTL;
class DES
{
	private:
	bitset<64> txt;
	bitset<64> s_key;
	bitset<48> r_son_key[16];
	bitset<32> left_txt;
	bitset<32> right_txt;
	bitset<48> ex_txt;
	bitset<64> once_res;
	bitset<64> c_txt;
	bool is_decode = 0;

	bitset <56> key_IP_change(bitset<64>in);//��Կ����IP�б仯
	void get_key_CD(bitset <56> son_key, bitset<28> key_C[17], bitset<28> key_D[17]);//�����Կ�ķ���CD
	void get_16_son_key_48(bitset<28> key_C[17], bitset<28> key_D[17]);//�õ�16��48���ȵ���Կ
	bitset<64> IP_change(bitset<64> in);//���������IP�б任
	bitset<64> IP_1_change(bitset<64> in);//������һ��IP�任
	void separate(bitset<64>in, bitset<32>& l_txt, bitset<32>& r_txt);//��in�԰�ֳ�l_txt��r_txt
	bitset<48> TO_48(bitset<32> right_txt);//��32λ�������Ϊ48λ
	bitset<48> XOR(bitset<48>ex_48, bitset<48> key);//48λ�Ľ������
	bitset<32> S_change(bitset<48>xor_res);//S�б任
	bitset<32> IP_change2(bitset<32> S_res);//��һ��IP�任
	bitset<32> f(bitset<32>R, bitset<48> K);//F������������һЩ����
	bitset<32> xor_32(bitset<32> a, bitset<32> b);//32λbit�����ݽ������
	bitset<64> merge_once_res(bitset<32>right_txt, bitset<32>f_out, int n);//���������ƴ��
	bitset<64> once(bitset<64> in, bitset<48>key, int n);//��inʹ��key����һ�ֵ��������ܣ����ܽ������

public:
	bitset<64> des_res;
	bitset<64> decode_res;

	void get_key(bitset<64> in);//�����Կ
	void get_all_key();//�õ����е���Կ
	void get_txt(bitset<64> in);//������ܵ�txt
	void oper_16();//����16�Σ�������������
	void get_ctxt(bitset<64> in);//��������
	void decode();//����
};