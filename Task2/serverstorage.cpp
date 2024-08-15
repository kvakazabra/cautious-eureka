#include "serverstorage.h"

bool CServer::operator==(const CServer& s1) {
	return m_IP == s1.m_IP;
}

CServerStorage::CServerStorage(std::weak_ptr<IStorage> storage)
	: m_Storage{ storage } {
	parse();
}

std::vector<CServer> CServerStorage::GetServersList() const {
	return m_Servers;
}

bool CServerStorage::AddServer(const CServer& server) {
	if (isPresent(server))
		return false;

	m_Servers.push_back(server);
	onChanged();
	return true;
}

bool CServerStorage::DeleteServer(const CServer& server) {
	if (!isPresent(server))
		return false;

	m_Servers.erase(std::find(m_Servers.begin(), m_Servers.end(), server));
	onChanged();
	return true;
}

bool CServerStorage::isPresent(const CServer& server) {
	return std::find(m_Servers.begin(), m_Servers.end(), server) != m_Servers.end();
}

void CServerStorage::parse() {
	if (m_Storage.expired())
		return; // exception here is better i guess?

	std::string content = m_Storage.lock()->parse();
	std::istringstream stream(content);
	std::string currentLine{ };

	while (std::getline(stream, currentLine)) {
		m_Servers.emplace_back(currentLine);
	}
}

void CServerStorage::onChanged() {
	if (m_Storage.expired())
		return; // exception here is better i guess?

	std::string finalData{ };
	for (auto& server : m_Servers) {
		finalData += server.m_IP + std::string("\n");
	}
	m_Storage.lock()->overwrite(finalData);
}

void CServerStorage::printAllServers() const {
	for (auto& server : m_Servers) {
		std::println("{:s}", server.m_IP);
	}
	std::println("");
}