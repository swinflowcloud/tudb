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

#undef UNICODE

#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <string.h>
#include <conio.h>

#include "rqthandler.h"
//#include "base64util.h"
//#include "numberutils.h"

/*
 * tudbserversock.h
 *
 * Created on: 2020-01-02 22:55:46
 * Author: Dahai CAO 
 */

#ifndef TUDBSERVERSOCK_H_
#define TUDBSERVERSOCK_H_

SOCKET createServerSocket();

int bindIpandPort(SOCKET srv_socket, char *ip, int port);

int listenPort(SOCKET srv_socket);

int closeClientSocket(SOCKET clt_socket);

int closeServerSocket(SOCKET clt_socket);

SOCKET acceptRequest(SOCKET srv_socket);

int handleRequest(SOCKET clt_socket);

int receiveMsg(SOCKET clt_socket, char *rqname, char *reqbody, const int bufsize);

#endif /* TUDBSERVERSOCK_H_ */
