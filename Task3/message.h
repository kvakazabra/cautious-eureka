#pragma once
#include <string>
#include <array>
#include <unordered_map>

class CMessage {
public:
	enum class Type {
		None,
		System,
		Server,
		Session
	};
public:
	CMessage() = default;
	CMessage(Type type, const std::string& message);
	~CMessage() = default;

	CMessage(const CMessage& other) = default;
	CMessage& operator=(const CMessage& other) = default;

	CMessage(CMessage&& other) noexcept;
	CMessage& operator=(CMessage&& other) noexcept;
public:
	Type type() const;
	const std::string& message() const;

	std::string serialize() const;
	static CMessage deserialize(const std::string& fullMessage);
private:
	Type m_Type{ Type::None };
	std::string m_Message{ };

	static const inline std::unordered_map<Type, std::string> c_MessageTypeToStringMap{
		{ Type::System, "System" },
		{ Type::Server, "Server" },
		{ Type::Session, "Session" },
	};
	static const inline std::string c_Separator{ ": " };
};