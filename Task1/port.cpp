#include "port.h"

TAllowedSpeed& operator|=(TAllowedSpeed& lhs, TAllowedSpeed rhs) {
	lhs = static_cast<TAllowedSpeed>(std::to_underlying(lhs) | std::to_underlying(rhs));
	return lhs;
}
bool operator&(TAllowedSpeed lhs, TAllowedSpeed rhs) {
	return std::to_underlying(lhs) & std::to_underlying(rhs);
}

CPort::CPort(const pugi::xml_node& node, bool shouldThrow) { 
	parse(node, shouldThrow); 
}

std::string CPort::format(const CPort& port) {
	static auto formatBoolean = [](bool b) -> std::string {
		return b ? "True" : "False";
		};

	return std::format("Port ID: {:d}\n\tIs Up: {:s}\n\tAuto Negotiation Enabled: {:s}\n\tAllowed Speed: 10M ({:s}), 100M ({:s}), 1G ({:s}), 10G ({:s})\n\tVlan ID: {:d}\n",
		port.id(),
		formatBoolean(port.isUp()),
		formatBoolean(port.isAutoNegotiationEnabled()),
		formatBoolean(port.isSpeedAllowed(TAllowedSpeed::M10)),
		formatBoolean(port.isSpeedAllowed(TAllowedSpeed::M100)),
		formatBoolean(port.isSpeedAllowed(TAllowedSpeed::G1)),
		formatBoolean(port.isSpeedAllowed(TAllowedSpeed::G10)),
		port.vlanId()
	);
}

void CPort::parse(const pugi::xml_node& node, bool shouldThrow) {
	if (const auto idAttribute = node.attribute("ID"); idAttribute) {
		m_Id = idAttribute.as_int(-1);
	}
	else if (shouldThrow) {
		throw std::runtime_error("Failed to find ID attribute");
	}

	auto checkChildIsOn = [&](const std::string& childName) -> bool {
		if (const auto child = node.child(childName.c_str()); child)
			return child.text().as_string() == std::string("On");

		if (shouldThrow)
			throw std::runtime_error(std::string("Failed to find child ") + childName);

		return false;
		};

	m_IsUp = checkChildIsOn("Up");
	m_AutoNegotiationEnabled = checkChildIsOn("AutoNegotiationEnabled");

	if (checkChildIsOn("AllowedSpeed_10M"))
		m_AllowedSpeedFlags |= TAllowedSpeed::M10;
	if (checkChildIsOn("AllowedSpeed_100M"))
		m_AllowedSpeedFlags |= TAllowedSpeed::M100;
	if (checkChildIsOn("AllowedSpeed_1G"))
		m_AllowedSpeedFlags |= TAllowedSpeed::G1;
	if (checkChildIsOn("AllowedSpeed_10G"))
		m_AllowedSpeedFlags |= TAllowedSpeed::G10;
}