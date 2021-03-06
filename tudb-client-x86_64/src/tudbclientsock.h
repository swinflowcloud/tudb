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

#include "log.h"
#include "numberutils.h"

/*
 * tudbclient.h
 *
 * Created on: 2020-01-02 22:34:00
 * Author: Dahai CAO 
 */

#ifndef TUDBCLIENTSOCK_H_
#define TUDBCLIENTSOCK_H_


#define DEFAULT_PORT 9088           // REMOTE PORT
#define DEFAULT_ADDR "127.0.0.1"    // server address

SOCKET createConnection();

int connectServer(SOCKET conn_sock, char *ip, int port);

int sendRequest(SOCKET conn_sock, char *sendbuf);

int receiveResponse(SOCKET conn_sock, char * recvbuf, const int bufsize);

int closeConnection(SOCKET conn_sock);

#endif /* TUDBCLIENTSOCK_H_ */
