#include "message.h"

CMessage::CMessage(Type type, const std::string& message)
	: m_Message{ message }, m_Type{ type } { }

CMessage::CMessage(CMessage&& other) noexcept {
	*this = std::move(other);
}
CMessage& CMessage::operator=(CMessage&& other) noexcept {
	m_Type = other.m_Type;
	m_Message = std::move(other.m_Message);
	return *this;
}

CMessage::Type CMessage::type() const {
	return m_Type;
}

const std::string& CMessage::message() const {
	return m_Message;
}

std::string CMessage::serialize() const {
	if (c_MessageTypeToStringMap.find(type()) == c_MessageTypeToStringMap.end())
		return { };

	return c_MessageTypeToStringMap.at(type()) + c_Separator + m_Message;
}

CMessage CMessage::deserialize(const std::string& fullMessage) {
	std::size_t separator{ fullMessage.find(c_Separator) };
	if (separator == std::string::npos)
		return { };

	Type type{ Type::None };
	for (const auto& p : c_MessageTypeToStringMap) {
		if (fullMessage.find(p.second) != 0)
			continue;

		type = p.first;
		break;
	}

	if (type == Type::None)
		return { };

	return CMessage(type, fullMessage.substr(separator + c_Separator.size())); // skip separator
}