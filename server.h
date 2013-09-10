#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <vector>
#include <string>

#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Util/ServerApplication.h>

class RequestHandler: public Poco::Net::HTTPRequestHandler{
public:
	virtual void handleRequest(Poco::Net::HTTPServerRequest& req,
							   Poco::Net::HTTPServerResponse& resp);
};

class RequestHandlerFactory: public Poco::Net::HTTPRequestHandlerFactory{
public:
	virtual Poco::Net::HTTPRequestHandler* createRequestHandler(
									const Poco::Net::HTTPServerRequest& req){
		return new RequestHandler;
	}
};

class Server: public Poco::Util::ServerApplication{
public:
	explicit Server(short server_port);
	void run_server();
protected:
	int main(const std::vector<std::string>& args);
private:
	const short server_port;
};

#endif //SERVER_H
