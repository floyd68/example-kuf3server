#pragma once

#include <asio.hpp>
#include <memory>
#include "SMsg.h"
#include <assert.h>
#include <thread>



template <class T> class Session : public std::enable_shared_from_this< Session<T> >
{
public:
	using ptr = std::shared_ptr<Session<T>>;
	using protocol_type = T;

	Session(asio::io_service& service) : m_socket(service), m_bActive(false), m_bHost(false){}
	explicit Session(typename T::socket&& socket) : m_socket(std::move(socket)), m_bActive(false) {}
	/* Session(Session<T>&& other)
		: m_socket(std::move(other.m_socket))
		, m_bActive(std::move(other.m_bActive))
	{} */
	Session<T>& operator = (Session<T>&& other)
	{
		m_socket = std::move(other.m_socket);
		m_bActive = std::move(other.m_bActive);
		return *this;
	}

	Session(Session<T>& other) = delete;
	Session<T>& operator = (Session<T>& other) = delete;

	void set_socket(typename T::socket&& socket)
	{
		m_socket = std::move(socket);
		m_netBuf.clear();
	}
	typename T::socket& socket() { return m_socket; }
	bool is_active() { return m_bActive; }
	void set_active(bool bEnable) { m_bActive = bEnable; }

	void start_receive()
	{
		SNetBuf::vecBuf bufs = m_netBuf.get_empty_buf();
		std::vector < asio::mutable_buffer > vecAsioBuf;
		for (auto buf : bufs)
			vecAsioBuf.push_back(asio::buffer(buf.first, buf.second));

		auto on_recv = [this](std::error_code ec, std::size_t length)
		{
			std::stringstream ss;
			ss << std::this_thread::get_id();

			fprintf(stdout, "Thread %s, Received : %zd\n", ss.str().c_str(), length);

			if (!ec && length > 0)
			{
				m_socket.get_io_service().post([this,length]()
				{
					m_netBuf.commit_recv(length);

					while (m_netBuf.available_data() >= 4)
					{
						fprintf(stdout, "Received %d\n", (int)length);
						SMsgRecv msg(&m_netBuf);

						if (!msg.is_valid())
							break;

						handle_net_msg(msg);
						msg.done_msg();
					}
					m_socket.get_io_service().post([this]() { start_receive(); });
				});
			}
			else
			{
				fprintf(stderr, "error on receive: %d - %s\n", ec.value(), ec.message().c_str());
				on_session_disconnected();
			}
		};

		m_socket.async_read_some(vecAsioBuf, on_recv);
	}
	void start_send(SMsgSend& msg)
	{
		size_t s = m_socket.write_some(asio::buffer(msg.GetData(), msg.GetSize()));
	}
	void close()
	{
		m_socket.close();
		set_active(false);
	}
	virtual void handle_net_msg(const SMsgRecv& msg)
	{
		std::string str;
		
		msg >> str;

		std::stringstream ss;
		ss << std::this_thread::get_id();

		fprintf(stdout, "Thread %s - Msg : %s\n", ss.str().c_str(), str.c_str());
	}
	virtual void on_session_disconnected() {}
	void SetHost(bool bHost) { m_bHost = bHost; }
private:
	typename T::socket m_socket;
	bool m_bActive;
	bool m_bHost;
	SNetBuf m_netBuf;
};

