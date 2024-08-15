#pragma once
#include <string>
#include <vector>
#include <memory>
#include <print>
#include "storage.h"

class CServer {
public:
	std::string m_IP{ }; // would be much better to validate each IP in ctor or make a fabric method with it

	bool operator==(const CServer& s1);
};

class CServerStorage {
public:
	CServerStorage(std::weak_ptr<IStorage> storage);
	~CServerStorage() = default;

	CServerStorage(const CServerStorage&) = delete; // disable copy/move semantics
	CServerStorage& operator=(const CServerStorage&) = delete;

	std::vector<CServer> GetServersList() const;

	// @return True when added
	bool AddServer(const CServer& server);
	// @return True when deleted
	bool DeleteServer(const CServer& server);
private:
	std::weak_ptr<IStorage> m_Storage{ };
	std::vector<CServer> m_Servers{ };
private:
	bool isPresent(const CServer& server);
	void parse();
	void onChanged();
	void printAllServers() const;
};
