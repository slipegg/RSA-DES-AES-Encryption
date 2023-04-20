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

	bitset <56> key_IP_change(bitset<64>in);//密钥经过IP盒变化
	void get_key_CD(bitset <56> son_key, bitset<28> key_C[17], bitset<28> key_D[17]);//获得密钥的分组CD
	void get_16_son_key_48(bitset<28> key_C[17], bitset<28> key_D[17]);//得到16个48长度的密钥
	bitset<64> IP_change(bitset<64> in);//对输入进行IP盒变换
	bitset<64> IP_1_change(bitset<64> in);//进行另一种IP变换
	void separate(bitset<64>in, bitset<32>& l_txt, bitset<32>& r_txt);//将in对半分成l_txt和r_txt
	bitset<48> TO_48(bitset<32> right_txt);//将32位的输入变为48位
	bitset<48> XOR(bitset<48>ex_48, bitset<48> key);//48位的进行异或
	bitset<32> S_change(bitset<48>xor_res);//S盒变换
	bitset<32> IP_change2(bitset<32> S_res);//另一种IP变换
	bitset<32> f(bitset<32>R, bitset<48> K);//F函数，整合了一些运算
	bitset<32> xor_32(bitset<32> a, bitset<32> b);//32位bit的数据进行异或
	bitset<64> merge_once_res(bitset<32>right_txt, bitset<32>f_out, int n);//将输入进行拼接
	bitset<64> once(bitset<64> in, bitset<48>key, int n);//对in使用key进行一轮的完整加密，加密结果返回

public:
	bitset<64> des_res;
	bitset<64> decode_res;

	void get_key(bitset<64> in);//获得密钥
	void get_all_key();//得到所有的密钥
	void get_txt(bitset<64> in);//输入加密的txt
	void oper_16();//操作16次，进行完整加密
	void get_ctxt(bitset<64> in);//输入密文
	void decode();//解密
};