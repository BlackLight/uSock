#include <iostream>
#include <usock.h>
using namespace std;

int main(int argc, char **argv)  {
	if (argc<3)  {
		cerr << "Usage: " << argv[0] << " <network interface> <host>\n";
		return 1;
	}

	u_int8_t payload[56];

	for (int i=0; i < sizeof(payload); i++)
		payload[i] = i;

	RawSocket s(argv[1]);
	s.buildIPv4(argv[2], s.getIPv4addr(), IPPROTO_ICMP);
	s.buildICMPv4(8);
	s.setPayload(payload, sizeof(payload));
	
	cout << "Sending a ping request to " << argv[2] << endl;
	s.write();

	unsigned char* buf = (unsigned char*) s.read(64, argv[2]);
	struct iphdr ip;
	memcpy (&ip, buf, sizeof(struct iphdr));
	string addr = s.ntoa(ip.saddr);

	cout << "Reply from " << addr << endl;
	s.close();
}

