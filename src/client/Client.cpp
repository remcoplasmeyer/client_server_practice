#include "Client.h"
#include "../Log.h"

int main() {
	CLIENT::Client client;
	return 0;
}

namespace CLIENT {


Client::Client() {
	FILE_LOG(logDEBUG) << "test";
}

void Client::tick()
{

}

} /* End of namespace CLIENT */
