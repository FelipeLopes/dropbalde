#include <boost/program_options.hpp>
#include "server.h"

using namespace std;
using namespace boost::program_options;
using namespace Poco::Net;
using namespace Poco::Util;

void RequestHandler::handleRequest(HTTPServerRequest& req, HTTPServerResponse& resp){
	resp.setStatus(HTTPResponse::HTTP_OK);
    resp.setContentType("text/html");

    ostream& out = resp.send();
    out << "<h1>Hello world!</h1>"
        << "<p>Host: "   << req.getHost()   << "</p>"
        << "<p>Method: " << req.getMethod() << "</p>"
        << "<p>URI: "    << req.getURI()    << "</p>";
    out.flush();
}

Server::Server(short server_port):server_port(server_port){

}

int Server::main(const std::vector<std::string>& args){
	HTTPServer s(new RequestHandlerFactory, ServerSocket(server_port), new HTTPServerParams);
	s.start();
	waitForTerminationRequest();
    s.stop();
	return Application::EXIT_OK;
}

void Server::run_server(){
	run();
}

int main(int argc, char* argv[]){
	options_description desc("Allowed options");
	desc.add_options()
		("help", "Produce help message")
		("version", "Display version information")
		("port",  value<short>(), "Set port to serve on");
	variables_map vm;
	try {
		store(parse_command_line(argc,argv,desc),vm);
	}
	catch (exception& ex){
		cout<<desc<<"\n";
		return 1;
	}
	notify(vm);
	
	if (vm.count("help") || vm.empty()){
		cout<<desc<<"\n";
		return 1;
	}
	if (vm.count("version")){
		printf("DropBalde v1.0 alpha\n");
		return 1;
	}
	if (vm.count("port")){
		short port = vm["port"].as<short>();
		printf("Serving on port %d...\n",port);
		Server s(port);
		s.run_server();
	}
	return 0;
}
