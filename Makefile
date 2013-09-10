server: server.cpp
	g++ $^ -o $@ -lPocoNet -lPocoUtil -lboost_program_options
