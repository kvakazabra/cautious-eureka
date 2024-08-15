#include <unordered_map>
#include <print>
#include "pugixml.hpp"
#include "port.h"

int main(int argc, char** argv) {
	pugi::xml_document document{ };
	if (!document.load_file("./test_config.xml")) {
		printf("Failed opening a file\n");
		getchar();
		return -1;
	}

	std::unordered_map<int, CPort> portsMap{ }; // using map here so that we can find port by it's ID
	for (const auto node : document.child("ControlSystem").child("Ports")) {
		CPort port(node);
		if (port.id() == -1)
			continue;

		portsMap[port.id()] = port;
	}

	for (const auto node : document.child("ControlSystem").child("Vlans").child("defVlans")) {
		const auto idAttribute = node.attribute("ID");
		const auto vlanChild = node.child("vlan");
		if (!idAttribute || !vlanChild)
			continue;

		int vlanId{ vlanChild.text().as_int(-1) };
		int id{ idAttribute.as_int(-1) };
		if (id == -1 || portsMap.find(id) == portsMap.end() || vlanId == -1)
			continue;

		portsMap[id].setVlanId(vlanId);
	}

	for (auto& p : portsMap) {
		std::println("{:s}", CPort::format(p.second));
	}

	getchar();
}