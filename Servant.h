#pragma once
//Servant:20120905
#include <iostream>
#include <boost/asio.hpp>
#include "neuria/Neuria.h"

namespace svy
{
class Servant{
public:
	using Pointer = boost::shared_ptr<Servant>;
	using Logger = boost::function<void (const std::string&, int, const nr::ByteArray&)>;
	static auto Create(boost::asio::io_service& service, 
			int port, int buffer_size, std::ostream& os) -> Pointer {
		auto servant = Pointer(new Servant(os));
		auto core = nr::ntw::P2pCore::Create(service, port, buffer_size,
			boost::bind(&Servant::OnAccept, servant, _1),
			boost::bind(&Servant::OnReceive, servant, _1, _2),
			boost::bind(&Servant::OnClose, servant, _1), os);
		servant->SetCorePtr(core);
		return servant;
	}

	auto Register(Logger logger) -> void {
		this->logger_list.push_back(logger);
	}

private:
	Servant(std::ostream& os):pool(nr::ntw::SessionPool::Create()), os(os){}

	auto OnReceive(
			nr::ntw::Session::Pointer session, const nr::ByteArray& byte_array) -> void {
		this->os << nr::utl::ByteArray2String(byte_array) << std::endl;
		for(auto logger : this->logger_list){
			logger(nr::ntw::GetRemoteAddressStr(session), nr::ntw::GetRemotePort(session), 
				byte_array);
		}
	}
	
	auto SetCorePtr(nr::ntw::P2pCore::Pointer core) -> void { this->core = core; }

	auto OnAccept(nr::ntw::Session::Pointer session) -> void {
		this->pool->Add(session);
	}
	
	auto OnClose(nr::ntw::Session::Pointer session) -> void {
		this->pool->Erase(session);	
	}

	nr::ntw::P2pCore::Pointer core;
	nr::ntw::SessionPool::Pointer pool;
	std::vector<Logger> logger_list;
	std::ostream& os;

};
}

