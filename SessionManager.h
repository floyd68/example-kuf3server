#pragma once

#include "session.h"
#include <list>
#include <mutex>

template <class T> class SessionManager
{
public:
	typedef typename T::ptr UserPtr;
	SessionManager(asio::io_service& service, int nInitial, bool bGrow)
	{
		for (int i = 0; i < nInitial; ++i)
			m_listSessionsInactive.emplace_back(std::make_shared<T>(service,this));
	}
	void on_session_connected(typename T::protocol_type::socket&& socket) 
	{
		fprintf(stdout, "add_session\n");


		typename T::ptr pSession;


		std::lock_guard<std::recursive_mutex> lock(m_mutex);

		if (m_listSessionsInactive.empty())
		{
			throw "No more available session";
		}
		else
		{
			pSession = m_listSessionsInactive.front();
			m_listSessionsInactive.pop_front();

			pSession->set_socket(std::move(socket));
		}

		pSession->set_active(true);
		m_listSessionsActive.push_back(pSession);
		pSession->socket().get_io_service().post([pSession]() { pSession->start_receive(); });
		SMsgSend msg(static_cast<unsigned short>(PACKET_ID::PACKET_IS_LOGIN_REQ));
		pSession->start_send(msg);

	}

	
	void on_session_disconnected(typename T::ptr session)
	{
		fprintf(stdout, "remove_session\n");

		session->set_active(false);

		std::lock_guard<std::recursive_mutex> lock(m_mutex);

		auto it = std::find(m_listSessionsActive.begin(), m_listSessionsActive.end(), session);
		if ( it != m_listSessionsActive.end() )
			m_listSessionsActive.erase(it);

		m_listSessionsInactive.push_back(session);
	}

	virtual void AddUserList(UserPtr session) = 0;
	virtual void BroadCast(UserPtr, SMsgSend& msg) = 0;
	//virtual void AddStatObjInfo(UserPtr, const SMsgRecv& msg) = 0;
	virtual void SendIsHost(UserPtr pSession) = 0;
	std::list < typename T::ptr > m_listSessionsActive;
	std::list < typename T::ptr > m_listSessionsInactive;

protected:
	std::recursive_mutex m_mutex;
	bool m_bGrow;
};

