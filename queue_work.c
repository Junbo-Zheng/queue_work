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

#include <stdio.h>
#include <stdlib.h>

#include "queue_work.h"

#ifndef FAIL
#define FAIL -1
#endif

#ifndef OK
#define OK 0
#endif

static void _worker_after_cb(void* data)
{
    printf("finish\n");

    queue_work_t* queue_work = data;
    if (queue_work == NULL) {
        return;
    }

    if (queue_work->func_after_cb) {
        queue_work->func_after_cb(queue_work->data);
    }

    free(data);
}

static void* _worker_cb(void* data)
{
    printf("start\n");

    // Check cancellation status and exit if requested
    pthread_testcancel();

    queue_work_t* queue_work = data;
    if (queue_work == NULL) {
        return (void*)FAIL;
    }

    if (queue_work->func_cb) {
        queue_work->func_cb(queue_work->data);
    }

    _worker_after_cb(data);
    return (void*)OK;
}

queue_work_t* queue_work(queue_work_cb_t queue_work_cb,
                         queue_work_cb_t queue_work_after_cb, void* data)
{
    if (queue_work_cb == NULL) {
        return NULL;
    }

    queue_work_t* queue_work = calloc(1, sizeof(queue_work_t));
    if (queue_work == NULL) {
        return NULL;
    }

    /* clang-format off */
    queue_work->data          = data;
    queue_work->func_cb       = queue_work_cb;
    queue_work->func_after_cb = queue_work_after_cb;

    pthread_t      pid  = { 0 };
    pthread_attr_t attr = { 0 };

    struct sched_param param ={
        .sched_priority = CONFIG_QUEUE_WORK_THREAD_LEVEL
    };
    /* clang-format on */

    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, CONFIG_QUEUE_WORK_THREAD_SIZE);

    pthread_attr_setschedparam(&attr, &param);

    pthread_create(&pid, &attr, _worker_cb, queue_work);
    pthread_setname_np((const char*)CONFIG_QUEUE_WORK_THREAD_NAME);

    pthread_detach(pid);
    pthread_attr_destroy(&attr);

    printf("ready %p\n", queue_work);

    queue_work->pid = pid;
    return queue_work;
}

void queue_work_cancel(queue_work_t* queue_work)
{
    printf("queue work cancel %p\n", queue_work);

    if (queue_work == NULL) {
        return;
    }

    pthread_cancel(queue_work->pid);

    free(queue_work);
}
