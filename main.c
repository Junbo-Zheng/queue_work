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
#include <unistd.h>

#include "queue_work.h"

static void queue_work_cb(void* data)
{
    printf("%s %d run, %p\n", __FUNCTION__, __LINE__, data);
}

static void queue_work_after_cb(void* data)
{
    printf("%s %d run, %p\n", __FUNCTION__, __LINE__, data);
}

int main(void)
{
    printf("main start\n");

    queue_work_t* work = queue_work(queue_work_cb, queue_work_after_cb, NULL);
    if (work) {
        printf("queue work create %p\n", work);
        // queue_work_cancel(work);
    }

    sleep(2);

    printf("main exit\n");

    return 0;
}
