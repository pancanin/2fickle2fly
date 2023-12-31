#ifndef UTILS_TIME_TIME_H_
#define UTILS_TIME_TIME_H_

#include <chrono>
#include <cstdint>

class Time {
public:
	/** @brief used to measure elapsed time since last invoke of this method
	 * */
	Time& getElapsed();

	int64_t toSeconds() const;
	int64_t toMilliseconds() const;
	int64_t toMicroseconds() const;
	int64_t toNanoseconds() const;
private:
	std::chrono::time_point<std::chrono::steady_clock> _now = std::chrono::steady_clock::now();
	std::chrono::time_point<std::chrono::steady_clock> _elapsedLastCall;
};

#endif /* UTILS_TIME_TIME_H_ */
