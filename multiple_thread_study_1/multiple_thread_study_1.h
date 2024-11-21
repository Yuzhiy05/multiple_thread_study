// multiple_thread_study_1.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <iostream>
#include<thread>
#include<utility>
#include<stdexcept>


class scoped_thread
{
	std::thread t;
public:
	explicit scoped_thread(std::thread t_) :t(std::move(t_))
	{
		if (!t.joinable())
			throw std::logic_error("no_thread");
	}
	~scoped_thread()
	{
		t.join();
	}  
	scoped_thread(const scoped_thread&) = delete;
	scoped_thread& operator=(const scoped_thread&) = delete;

};

struct func_st {
	func_st() {
		std::cout << "func_st created\n";
	}
	func_st(const func_st&) {
		std::cout << "func_st copyed\n";
	}
	func_st(func_st&&) {
		std::cout << "func_st move\n";
	}
	void operator()() {
		std::cout << "func_st ()\n";
	}
	void f() {
		std::cout << "func_st`s f is calling\n";
	}
};

void test() {
	func_st s{};
	auto thread_t = scoped_thread(std::thread(s));
}
void test2() {
	func_st s{};
	auto thread_t = scoped_thread(std::thread(&func_st::f, &s));
}

// TODO: 在此处引用程序需要的其他标头。
