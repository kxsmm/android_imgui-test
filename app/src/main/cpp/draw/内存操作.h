#pragma once
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "definition.h"


// 获取当前进程的PID
pid_t get_my_pid() {
	return getpid();
}


