# QUEUE WORK

## Overview
- It is a queue work based on `pthread`.

- You can use it when you need to perform some time-consuming operations and don't want to affect your main task.

- It will complete the task you assigned in a separate thread, and tell you in `queue_work_after_cb` that the thread has been completed.

- However, please note that the execution context of `queue_work_after_cb` is still in the queue work thread, so if you want it to notify your main task, you need to notify your main task in `queue_work_after_cb`.

## Features highlights
- queue_work
- queue_work_cancel

## Licensing

**Licensed** is under the Apache license, check the [LICENSE](./LICENSE) file.

## How to build and test
```bash
➜  /Users/junbozheng/project/queue_work git:(master) sw_vers
ProductName:            macOS
ProductVersion:         14.4.1
BuildVersion:           23E224
➜  /Users/junbozheng/project/queue_work git:(master) cmake -S . -B build
-- The C compiler identification is AppleClang 15.0.0.15000309
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /Library/Developer/CommandLineTools/usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Configuring done (0.6s)
-- Generating done (0.0s)
-- Build files have been written to: /Users/junbozheng/project/queue_work/build
➜  /Users/junbozheng/project/queue_work git:(master) cmake --build build -j16
[ 66%] Building C object CMakeFiles/queue_work.dir/queue_work.c.o
[ 66%] Building C object CMakeFiles/queue_work.dir/main.c.o
[100%] Linking C executable queue_work
[100%] Built target queue_work
➜  /Users/junbozheng/project/queue_work git:(master) ./build/queue_work
main start
ready 0x7fe01ff06050
queue work create 0x7fe01ff06050
start
queue_work_cb 8 run, 0x0
finish
queue_work_after_cb 13 run, 0x0
main exit
```
