#pragma once

#include "Acceptor.h"
#include "asio.hpp"
#include <thread>
#include <vector>

class NetworkService
{
public:
	NetworkService() {};
	NetworkService(NetworkService& other) = delete;
	NetworkService& operator = (NetworkService& other) = delete;

	template <class T> std::shared_ptr<Acceptor<T>> new_acceptor(int nPort, SessionManager<User>* pSessionMgr)
	{
		auto acceptor = std::make_shared<Acceptor<T>>(m_io_service, nPort,pSessionMgr);
		m_io_service.post([acceptor]() { acceptor->do_accept(); });
		return acceptor;
	}

	void Run( int threads )
	{
		for (int i = 0; i < threads; ++i)
		{
			m_vecThreads.push_back(
				std::thread([this]() 
				{ 
					std::stringstream ss;
					ss << std::this_thread::get_id();

					printf("thread %s started\n", ss.str().c_str());
					m_io_service.run();
				})
			);
		}
	}
	void Join()
	{
		for (auto& thread : m_vecThreads)
			thread.join();
	}
	void Stop()
	{
		m_io_service.stop();
	}
	template <class T> void post(T&& func)
	{
		m_io_service.post( func );
	}
	asio::io_service& get_io_service() { return m_io_service; }

private:
	asio::io_service m_io_service;
	std::vector <std::thread> m_vecThreads;
};
