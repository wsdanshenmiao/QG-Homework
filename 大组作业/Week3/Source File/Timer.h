#ifndef __TIMER__H__
#define __TIMER__H__

#include <chrono>
#include <iostream>

class Timer
{
public:
	Timer()
		:m_StartPoint(std::chrono::high_resolution_clock::now()) {}
	
	~Timer()
	{
		Stop();
	}

	void Stop()
	{
		auto endPointe = std::chrono::high_resolution_clock::now();
		//time_point_cast��ʱ��������ǿת�ɺ������΢��
		//time_since_epochʱ����ʼ�㵽���ڵ�ʱ��
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartPoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endPointe).time_since_epoch().count();

		auto duration = end - start;
		double ms = duration * 0.001;
		std::cout << "Time Cost:" << duration << "us " << "(" << ms << "ms" << ")\n";
	}

private:
	std::chrono::time_point<std::chrono::steady_clock> m_StartPoint;
};

#endif // !__TIMER__H__
