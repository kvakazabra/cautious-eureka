#include "storage.h"
#include "serverstorage.h"

int main(int argc, char** argv) {
	auto fileStorage = std::make_shared<CFileStorage>("./servers.txt");
	auto serverStorage = std::make_unique<CServerStorage>(fileStorage);

	/*serverStorage->AddServer(CServer("127.0.0.1"));
	serverStorage->AddServer(CServer("128.0.0.1"));
	serverStorage->AddServer(CServer("122.0.0.1"));
	serverStorage->AddServer(CServer("123.0.0.1"));
	serverStorage->AddServer(CServer("124.0.0.1"));
	serverStorage->AddServer(CServer("121.0.0.1"));
	serverStorage->AddServer(CServer("127.0.0.1"));
	serverStorage->DeleteServer(CServer("123.0.0.1"));
	serverStorage->DeleteServer(CServer("123.0.0.1"));*/
}