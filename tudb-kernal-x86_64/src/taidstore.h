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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include <unistd.h>

#include "convert.h"

/*
 * idcache.h
 *
 * Created on: 2020年6月16日
 * Author: Dahai CAO
 */

#ifndef TAIDSTORE_H_
#define TAIDSTORE_H_

#define BUFFERSIZE 8L //
#define PAGESIZE 2500L // read page size.
#define EPSIZE 25L // evolved point size on time axis (25 bytes)


// the cache for new free and reused Ids
typedef struct id_cache {
	long long nId[100];// new Id array
	long long rId[100];// reused Id array
} id_cache_t;

#endif /* IDCACHE_H_ */