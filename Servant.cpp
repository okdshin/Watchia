#ifdef SERVANT_UNIT_TEST
#include "Servant.h"
#include <iostream>

using namespace wch;

int main(int argc, char* argv[])
{
	boost::asio::io_service service;
	boost::asio::io_service::work w(service);
	boost::thread t(boost::bind(&boost::asio::io_service::run, &service));
	auto servent = Servant::Create(service, 54321, 128, std::cout);
	servent->StartAccept();
	t.join();

    return 0;
}

#endif
