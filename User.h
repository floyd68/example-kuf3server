#pragma once
#include "SessionManager.h"

class User : public Session<asio::ip::tcp>
{
public:
	User(asio::io_service& service, SessionManager<User>* pSessionMgr) : Session<asio::ip::tcp>(service)
		, m_pSessionMgr(pSessionMgr){}
	User(asio::ip::tcp::socket&& socket) : Session<asio::ip::tcp>(std::move(socket)) {}

	typedef std::shared_ptr<Session<asio::ip::tcp>> SessionPtr;
	void handle_net_msg(const SMsgRecv& msg) override;
	void on_session_disconnected() override;
	void send(SMsgSend msg);

private:
	void quit(const SMsgRecv& msg);
	bool insert_user();
	bool send_stage_info();
	SessionManager<User>* m_pSessionMgr;

	int _unique_number;
};

