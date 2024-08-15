#pragma once
#include <functional>
#include <string>
#include <exception>
#include <format>
#include "pugixml.hpp"

enum class TAllowedSpeed {
	M10 = 1,
	M100 = 2,
	G1 = 4,
	G10 = 8,
};

TAllowedSpeed& operator|=(TAllowedSpeed& lhs, TAllowedSpeed rhs);
bool operator&(TAllowedSpeed lhs, TAllowedSpeed rhs);

class CPort final {
public:
	CPort() = default;
	CPort(const pugi::xml_node& node, bool shouldThrow = false);
	~CPort() = default;

	CPort(const CPort&) = default;
	CPort& operator=(const CPort&) = default;
public:
	int id() const { return m_Id; }
	bool isValid() const { return m_Id != -1; }

	bool isUp() const { return m_IsUp; }
	bool isAutoNegotiationEnabled() const { return m_AutoNegotiationEnabled; }
	TAllowedSpeed allowedSpeedFlags() const { return m_AllowedSpeedFlags; }
	bool isSpeedAllowed(TAllowedSpeed speed) const { return m_AllowedSpeedFlags & speed; }

	int vlanId() const { return m_VlanId; }
	void setVlanId(int id) { m_VlanId = id; }

	static std::string format(const CPort& port);
private:
	int m_Id{ };
	int m_VlanId{ };
	bool m_IsUp{ };
	bool m_AutoNegotiationEnabled{ };
	TAllowedSpeed m_AllowedSpeedFlags{ };
private:
	void parse(const pugi::xml_node& node, bool shouldThrow);
};