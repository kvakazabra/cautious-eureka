#include "message.h"

int main(int argc, char** argv) {
	auto testMsg = CMessage(CMessage::Type::Session, "Test");
	auto testMsg2 = CMessage::deserialize(testMsg.serialize());

	if (testMsg.serialize() != testMsg2.serialize()) {
		printf("Failed\n");
		return -1;
	}

	printf("Success\n");
	getchar();
}