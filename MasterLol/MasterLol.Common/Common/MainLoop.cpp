#include "MainLoop.h"
#include "Misk/date.h"
#include <chrono>
#include <iostream>
#include <thread>

#include <SDK/EventManager.h>

void MainLoop::Run( unsigned long long updateFrequency)
{
	using namespace std::chrono;
	static auto updateFreq = std::chrono::milliseconds( updateFrequency );
	static auto next = steady_clock::now();
	static auto prev = next - updateFreq;

	auto now = steady_clock::now();
	prev = now;

	EventHandler<EventIndex::OnMainLoop, EventDefines::OnMainLoop>::GetInstance()->Trigger();

	next += updateFreq;
	std::this_thread::sleep_until( next );
}
