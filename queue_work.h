/*
 * Copyright (C) 2024 Junbo Zheng. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef _QUEUE_WORK_H_
#define _QUEUE_WORK_H_

#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*queue_work_cb_t)(void* data);

typedef struct {
    void* data;
    pthread_t pid;
    queue_work_cb_t func_cb;
    queue_work_cb_t func_after_cb;
} queue_work_t;

queue_work_t* queue_work(queue_work_cb_t queue_work_cb,
                         queue_work_cb_t queue_work_after_cb, void* data);

void queue_work_cancel(queue_work_t* queue_work);

#ifdef __cplusplus
}
#endif

#endif /* _QUEUE_WORK_H_ */
