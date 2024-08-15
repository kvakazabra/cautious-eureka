#include "storage.h"

CFileStorage::CFileStorage(const std::string& path) 
	: m_Path{ path } {
	if (!isValid())
		throw std::runtime_error("Failed to initialize CFileStorage");
}

bool CFileStorage::isValid() const {
	if (!std::filesystem::exists(m_Path))
		return true;

	return std::filesystem::is_regular_file(m_Path);
}

std::string CFileStorage::parse() const {
	std::lock_guard lock(m_Mutex);

	std::ifstream file(m_Path);
	if (!file.is_open())
		return { };

	std::ostringstream stream{ };
	stream << file.rdbuf();
	return stream.str();;
}

void CFileStorage::append(const std::string& data) {
	std::lock_guard lock(m_Mutex);

	std::ofstream file(m_Path, std::ios::app);
	if (!file.is_open())
		return;

	file.write(data.c_str(), data.size());
}

void CFileStorage::overwrite(const std::string& data) {
	std::lock_guard lock(m_Mutex);

	std::ofstream file(m_Path, std::ios::trunc);
	if (!file.is_open())
		return;

	file.write(data.c_str(), data.size());
}

void CFileStorage::clear() {
	std::lock_guard lock(m_Mutex);

	std::ofstream file(m_Path);
	if (!file.is_open())
		return;

	file.clear();
}