#pragma once

#include <asio.hpp>
#include "SessionManager.h"

class User;

template <class T> class Acceptor
{
public:
	using acceptor_type = typename T::protocol_type::acceptor;

	Acceptor(asio::io_service& io_service, int nPort, SessionManager<User>* pSessionMgr)
		: m_acceptor(io_service, typename T::protocol_type::endpoint(typename T::protocol_type::v4(), nPort))
		, m_socket(io_service)
		, m_pSessionMgr(pSessionMgr)
	{}

	void do_accept()
	{
		auto on_accept = [this](std::error_code ec)
		{
			if (!ec)
			{
				m_pSessionMgr->on_session_connected(std::move(m_socket));
			}
			else
			{
				fprintf(stderr, "error on accept : %d - %s\n", ec.value(), ec.message().c_str());
			}
			do_accept();
		};

		std::stringstream ss;
		ss << std::this_thread::get_id();

		fprintf(stdout, "Thread %s, do_accept\n", ss.str().c_str());
		m_acceptor.async_accept(m_socket, on_accept);
	}

private:
	acceptor_type m_acceptor;
	typename T::protocol_type::socket m_socket;
	SessionManager<User>* m_pSessionMgr;
};

