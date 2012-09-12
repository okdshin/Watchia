#ifdef WATCHIA_UNIT_TEST
#include "Watchia.h"
#include <iostream>

using namespace wch;

int main(int argc, char* argv[])
{
	boost::asio::io_service service;
	boost::asio::io_service::work w(service);
	boost::thread t(boost::bind(&boost::asio::io_service::run, &service));
	auto server = nr::ntw::Server::Create(service, 54321, 128, std::cout);
	auto watchia = Watchia::Create(server, std::cout);
	server->StartAccept();
	//t.join();

    return 0;
}

#endif
