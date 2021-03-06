/**
 * Copyright 2020 Dahai Cao
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "utf8convert.h"
/*
 * utf8convert.c
 *
 * Created on: 2020年9月29日
 * Author: Dahai CAO
 */

//int UnicodeToUtf8(char *pInput, char *pOutput) {
//	int len = 0; //记录转换后的Utf8字符串的字节数
//	while (*pInput) { //处理一个unicode字符
//		char low = *pInput; //取出unicode字符的低8位
//		pInput++;
//		char high = *pInput; //取出unicode字符的高8位
//		int w = high << 8;
//		unsigned wchar = (high << 8) + low; //高8位和低8位组成一个unicode字符,加法运算级别高
//		if (wchar <= 0x7F) { //英文字符
//			pOutput[len] = (char) wchar;  //取wchar的低8位
//			len++;
//		} else if (wchar >= 0x80 && wchar <= 0x7FF) { //可以转换成双字节pOutput字符
//			pOutput[len] = 0xc0 | ((wchar >> 6) & 0x1f); //取出unicode编码低6位后的5位，填充到110yyyyy 10zzzzzz 的yyyyy中
//			len++;
//			pOutput[len] = 0x80 | (wchar & 0x3f); //取出unicode编码的低6位，填充到110yyyyy 10zzzzzz 的zzzzzz中
//			len++;
//		} else if (wchar >= 0x800 && wchar < 0xFFFF) { //可以转换成3个字节的pOutput字符
//			pOutput[len] = 0xe0 | ((wchar >> 12) & 0x0f); //高四位填入1110xxxx 10yyyyyy 10zzzzzz中的xxxx
//			len++;
//			pOutput[len] = 0x80 | ((wchar >> 6) & 0x3f); //中间6位填入1110xxxx 10yyyyyy 10zzzzzz中的yyyyyy
//			len++;
//			pOutput[len] = 0x80 | (wchar & 0x3f); //低6位填入1110xxxx 10yyyyyy 10zzzzzz中的zzzzzz
//			len++;
//		} else { //对于其他字节数的unicode字符不进行处理
//			return -1;
//		}
//		pInput++; //处理下一个unicode字符
//	}
//	//utf8字符串后面，有个\0
//	pOutput[len] = 0;
//	return len;
//}

/*************************************************************************************************
 * 将UTF8编码转换成Unicode（UCS-2LE）编码  低地址存低位字节
 * 参数：
 *    char* pInput   输入字符串
 *    char*pOutput   输出字符串
 * 返回值：转换后的Unicode字符串的字节数，如果出错则返回-1
 **************************************************************************************************/
//utf8转unicode
//int Utf8ToUnicode(char *pInput, char *pOutput) {
//	int outputSize = 0; //记录转换后的Unicode字符串的字节数
//	while (*pInput) {
//		if (*pInput > 0x00 && *pInput <= 0x7F) { //处理单字节UTF8字符（英文字母、数字）
//			*pOutput = *pInput;
//			pOutput++;
//			*pOutput = 0; //小端法表示，在高地址填补0
//		} else if (((*pInput) & 0xE0) == 0xC0) { //处理双字节UTF8字符
//			char high = *pInput;
//			pInput++;
//			char low = *pInput;
//			if ((low & 0xC0) != 0x80) { //检查是否为合法的UTF8字符表示
//				return -1; //如果不是则报错
//			}
//			*pOutput = (high << 6) + (low & 0x3F);
//			pOutput++;
//			*pOutput = (high >> 2) & 0x07;
//		} else if (((*pInput) & 0xF0) == 0xE0) { //处理三字节UTF8字符
//			char high = *pInput;
//			pInput++;
//			char middle = *pInput;
//			pInput++;
//			char low = *pInput;
//			if (((middle & 0xC0) != 0x80) || ((low & 0xC0) != 0x80)) {
//				return -1;
//			}
//			*pOutput = (middle << 6) + (low & 0x3F); //取出middle的低两位与low的低6位，组合成unicode字符的低8位
//			pOutput++;
//			*pOutput = (high << 4) + ((middle >> 2) & 0x0F); //取出high的低四位与middle的中间四位，组合成unicode字符的高8位
//		} else { //对于其他字节数的UTF8字符不进行处理
//			return -1;
//		}
//		pInput++; //处理下一个utf8字符
//		pOutput++;
//		outputSize += 2;
//	}
//	//unicode字符串后面，有两个\0
//	*pOutput = 0;
//	pOutput++;
//	*pOutput = 0;
//	return outputSize;
//}

//bool check_ascii(const char *str, size_t length) {
//	size_t i = 0;
//	unsigned char ch = 0;
//	while (i < length) {
//		ch = *(str + i);
//		//判断是否ASCII编码,如果不是,说明有可能是UTF8,ASCII用7位编码,最高位标记为0,0xxxxxxx
//		if ((ch & 0x80) != 0)
//			return false;
//		i++;
//	}
//	return true;
//}

// check UTF-8 and ASCII charset
bool check_utf8(unsigned char *str, size_t length) {
	size_t i = 0;
	int nBytes = 0; //UTF8可用1 - 6个字节编码, ASCII用一个字节
	unsigned char ch = 0;
	//bool bAllAscii = true; //如果全部都是ASCII,说明不是UTF-8
	while (i < length) {
		ch = *(str + i);
		//判断是否ASCII编码,如果不是,说明有可能是UTF8,ASCII用7位编码,最高位标记为0,0xxxxxxx
		//if ((ch & 0x80) != 0)
		//	bAllAscii = false;
		if (nBytes == 0) { //计算字节数
			if ((ch & 0x80) != 0) {
				while ((ch & 0x80) != 0) {
					// i.e., 1110xxxx: <<1, 110xxxxx直到10xxxxxx
					//       11110xxx: <<1, 1110xxxx直到10xxxxxx
					ch <<= 1;
					nBytes++;
				}
				// nBytes是一个2到6之间的数
				if ((nBytes < 2) || (nBytes > 6)) {
					//第一个字节最少为110x xxxx，也就是至少移动2次（110xxxxx），
					// 最多移动6次（1111110x）
					return false;
				}
				nBytes--;					//减去自身占的一个字节
			}
		} else {					//多字节除了首字节外
			//多字节符的非首字节,应为 10xxxxxx
			if ((ch & 0xc0) != 0x80) {
				//剩下的字节都是10xx xxxx的形式
				return false;
			}
			//减到为零为止
			nBytes--;
		}
		i++;
	}
	if (nBytes != 0) {   //违返规则
		return false;
	}
	//if (bAllAscii) //如果全部都是ASCII, 也是UTF8，因此去掉该语句。
	//	return false;
	return (nBytes == 0);
}

bool check_gb2312(unsigned char *str, size_t length) {
	return true;
}

bool check_gbk(unsigned char *str, size_t length) {
	size_t i = 0;
	unsigned char ch = 0;
	unsigned char ch1 = 0;
	while (i < length) {
		ch = *(str + i);
		ch1 = *(str + i + 1);
		//编码0~127,只有一个字节的编码，兼容ASCII码
		if (ch <= 0x7f) {
			i++;
			continue;
		} else {
			//大于127的使用双字节编码，落在gbk编码范围内的字符
			if (ch >= 0x81 && ch <= 0xfe && ch1 >= 0x40 && ch1 <= 0xfe
					&& ch1 != 0xf7) {
				i += 2;
				continue;
			} else {
				return false;
			}
		}
	}
	return true;
}

//int is_str_utf8(const char *str) {
//	unsigned int nBytes = 0; //UFT8可用1-6个字节编码,ASCII用一个字节
//	unsigned char chr = *str;
//	int bAllAscii = 1;
//	for (unsigned int i = 0; str[i] != '\0'; ++i) {
//		chr = *(str + i);
//		//判断是否ASCII编码,如果不是,说明有可能是UTF8,ASCII用7位编码,最高位标记为0,0xxxxxxx
//		if (nBytes == 0 && (chr & 0x80) != 0) {
//			bAllAscii = 0;
//		}
//		if (nBytes == 0) {
//			//如果不是ASCII码,应该是多字节符,计算字节数
//			if (chr >= 0x80) {
//				if (chr >= 0xFC && chr <= 0xFD) {
//					nBytes = 6;
//				} else if (chr >= 0xF8) {
//					nBytes = 5;
//				} else if (chr >= 0xF0) {
//					nBytes = 4;
//				} else if (chr >= 0xE0) {
//					nBytes = 3;
//				} else if (chr >= 0xC0) {
//					nBytes = 2;
//				} else {
//					return 0;
//				}
//				nBytes--;
//			}
//		} else {
//			//多字节符的非首字节,应为 10xxxxxx
//			if ((chr & 0xC0) != 0x80) {
//				return 0;
//			}
//			//减到为零为止
//			nBytes--;
//		}
//	}
//	//违返UTF8编码规则
//	if (nBytes != 0) {
//		return 0;
//	}
//	if (bAllAscii) { //如果全部都是ASCII, 也是UTF8
//		return 1;
//	}
//	return 1;
//}

int code_convert(char *from_charset, char *to_charset, char *inbuf,
		size_t inlen, char *outbuf, size_t outlen) {
	iconv_t cd;
	char **pin = &inbuf;
	char **pout = &outbuf;

	cd = iconv_open(to_charset, from_charset);
	if (cd == 0)
		return -1;
	memset(outbuf, 0, outlen);
	if (iconv(cd, pin, &inlen, pout, &outlen) == -1) {
		pin = NULL;
		pout = NULL;
		return -1;
	}
	iconv_close(cd);
	*pout = '\0';
	pin = NULL;
	pout = NULL;
	return 0;
}

int u2g(char *inbuf, size_t inlen, char *outbuf, size_t outlen) {
	//return code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, outlen);
	return code_convert("utf-8", "gbk", inbuf, inlen, outbuf, outlen);
}

int g2u(char *inbuf, size_t inlen, char *outbuf, size_t outlen) {
	//return code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, outlen);
	return code_convert("gbk", "utf-8", inbuf, inlen, outbuf, outlen);
}

void convert2Utf8(char *fromstr, char *tostr, size_t length) {
	if (!check_utf8(fromstr, strlen((const char*) fromstr))) {
		if (check_gbk(fromstr, strlen((const char*) fromstr))
				|| check_gb2312(fromstr, strlen((const char*) fromstr))) {
			g2u(fromstr, strlen(fromstr), tostr, sizeof(tostr));
		}
	} else {
		//tostr = &fromstr;
		memcpy(tostr, fromstr, length);
	}
}

