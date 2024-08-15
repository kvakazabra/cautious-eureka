#pragma once
#include <string>
#include <exception>
#include <filesystem>
#include <mutex>
#include <sstream>
#include <fstream>

class IStorage {
public:
	virtual ~IStorage() = default;

	virtual std::string parse() const = 0; // template here??
	virtual void append(const std::string& data) = 0;
	virtual void overwrite(const std::string& data) = 0;
	virtual void clear() = 0;
};

class CFileStorage final : public IStorage {
public:
	CFileStorage(const std::string& path);
	virtual ~CFileStorage() = default;

	CFileStorage(const CFileStorage& file) = delete;
	CFileStorage& operator=(const CFileStorage& file) = delete;

	bool isValid() const;

	std::string parse() const override;
	void append(const std::string& data) override;
	void overwrite(const std::string& data) override;
	void clear() override;
private:
	std::string m_Path{ };
	mutable std::mutex m_Mutex{ };
};