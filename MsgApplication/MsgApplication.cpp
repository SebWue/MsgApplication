

#include <iostream>
#include <vector>
#include <thread>
#include <Windows.h>
#include <chrono>
#include "generateKey.h"
#include "window.h"
#include "server.h"

using namespace std;
#include "endecryp.h"

int main()
{
	window window;
	server server;

	generateKey keyget;

	/*const auto processor_count = std::thread::hardware_concurrency();
	cout << processor_count << endl;*/
	thread t1 = thread(&generateKey::newThreadToCheck, &keyget);
	window.create();
	t1.join();
}