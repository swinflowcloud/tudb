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
#include <string.h>
#include "macrodef.h"
/*
 * convert.h
 *
 * Created on: 2020年6月19日
 * Author: Dahai CAO
 */

#ifndef CONVERT_H_
#define CONVERT_H_

// Convert long long to byte array
void longToByteArray(long long value, unsigned char buffer[]);

// Convert byte array to long long
long long byteArrayToLong(unsigned char buffer[]);

// convert integer to bytes
void integer2Bytes(int value, unsigned char bytes[4]);

// convert byte array to integer
int bytes2Integer(unsigned char bytes[4]);

void longlongtoByteArray(long long value, unsigned char *buffer);

void integerBytesArry(int value, unsigned char *bytes);

long long bytesLonglong(unsigned char *buffer);

int byteArray2Integer(unsigned char *bytes);

#endif /* CONVERT_H_ */
