#pragma once
//Watchia:20120905
#include <iostream>
#include <boost/asio.hpp>
#include <boost/make_shared.hpp>
#include "neuria/network/Server.h"
#include "neuria/utility/Utility.h"

namespace wch
{

class Watchia {
public:
	using Pointer = boost::shared_ptr<Watchia>;
	using Logger = boost::function<void (const std::string&, int, const nr::ByteArray&)>;
	
	static auto Create(nr::ntw::Server::Pointer server, std::ostream& os) -> Pointer {
		auto watchia = Pointer(new Watchia(os));
		server->SetOnReceiveFunc(boost::bind(&Watchia::OnReceive, watchia, _1, _2));
		return watchia;
	}

	auto Register(Logger logger) -> void {
		this->logger_list.push_back(logger);
	}

private:
	Watchia(std::ostream& os) : os(os){}

	auto OnReceive(nr::ntw::Session::Pointer session, 
			const nr::ByteArray& byte_array) -> void {
		this->os << nr::utl::ByteArray2String(byte_array) << std::endl;
		for(auto logger : this->logger_list){
			logger(nr::ntw::GetRemoteAddressStr(session), 
				nr::ntw::GetRemotePort(session), byte_array);
		}
	}
	
	std::vector<Logger> logger_list;
	std::ostream& os;
};

}

