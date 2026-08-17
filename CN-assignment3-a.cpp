#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
    // Definitions
    cout << "************ IPv4 Address Classification ************\n\n";

    cout << "Subnet:\n";
    cout << "A subnet is a logical subdivision of a larger network. "
         << "It is created by dividing a network into smaller networks for efficient IP address utilization, "
         << "reduced network traffic and better security.\n\n";

    cout << "Subnet Mask:\n";
    cout << "A subnet mask is a 32-bit number used to separate the Network ID and Host ID of an IP address. "
         << "It tells which part of the IP address represents the network and which part represents the host.\n\n";

    string ip;
    cout << "Enter the IP Address: ";
    cin >> ip;

    stringstream ss(ip);
    string part;
    int firstOctet;

    // Extract first octet
    getline(ss, part, '.');
    firstOctet = stoi(part);

    // Loopback
    if (firstOctet == 127)
    {
        cout << "\nLoopback Address:\n";
        cout << "A loopback address is a special IP address used by a computer to communicate with itself.\n";
        cout << "Purpose: It is used for testing and troubleshooting the TCP/IP protocol stack without sending data over a physical network.\n\n";

        cout << ip << " belongs to Loopback Address." << endl;
        cout << "Example : 127.0.0.1" << endl;
    }

    // Class A
    else if (firstOctet >= 1 && firstOctet <= 126)
    {
        cout << "\n" << ip << " belongs to Class A." << endl;
        cout << "Default Subnet Mask : 255.0.0.0 (/8)" << endl;

        cout << "\nHosts per Network = 2^24 - 2 = 16,777,214" << endl;
        cout << "Reason: The default subnet mask is /8, therefore 8 bits are used for the Network ID and the remaining 24 bits are used for the Host ID." << endl;
        cout << "Total host addresses = 2^24." << endl;
        cout << "Subtract 2 because one address is reserved as the Network Address and one as the Broadcast Address." << endl;

        cout << "\nNumber of Networks = 2^7 = 128" << endl;
        cout << "Reason: The first bit of a Class A address is fixed as 0. The remaining 7 bits identify different networks." << endl;
    }

    // Class B
    else if (firstOctet >= 128 && firstOctet <= 191)
    {
        cout << "\n" << ip << " belongs to Class B." << endl;
        cout << "Default Subnet Mask : 255.255.0.0 (/16)" << endl;

        cout << "\nHosts per Network = 2^16 - 2 = 65,534" << endl;
        cout << "Reason: The default subnet mask is /16, therefore 16 bits are used for the Network ID and the remaining 16 bits are used for the Host ID." << endl;
        cout << "Total host addresses = 2^16." << endl;
        cout << "Subtract 2 because one address is reserved as the Network Address and one as the Broadcast Address." << endl;

        cout << "\nNumber of Networks = 2^14 = 16,384" << endl;
        cout << "Reason: The first two bits of a Class B address are fixed as 10. The remaining 14 bits identify different networks." << endl;
    }

    // Class C
    else if (firstOctet >= 192 && firstOctet <= 223)
    {
        cout << "\n" << ip << " belongs to Class C." << endl;
        cout << "Default Subnet Mask : 255.255.255.0 (/24)" << endl;

        cout << "\nHosts per Network = 2^8 - 2 = 254" << endl;
        cout << "Reason: The default subnet mask is /24, therefore 24 bits are used for the Network ID and the remaining 8 bits are used for the Host ID." << endl;
        cout << "Total host addresses = 2^8." << endl;
        cout << "Subtract 2 because one address is reserved as the Network Address and one as the Broadcast Address." << endl;

        cout << "\nNumber of Networks = 2^21 = 2,097,152" << endl;
        cout << "Reason: The first three bits of a Class C address are fixed as 110. The remaining 21 bits identify different networks." << endl;
    }

    // Class D
    else if (firstOctet >= 224 && firstOctet <= 239)
    {
        cout << "\n" << ip << " belongs to Class D (Multicast)." << endl;
        cout << "Purpose: Class D addresses are used for multicasting, i.e., sending data to a group of devices simultaneously." << endl;
        cout << "Subnet Mask: Not Applicable." << endl;
    }

    // Class E
    else if (firstOctet >= 240 && firstOctet <= 255)
    {
        cout << "\n" << ip << " belongs to Class E (Experimental)." << endl;
        cout << "Purpose: Class E addresses are reserved for research and experimental purposes." << endl;
        cout << "Subnet Mask: Not Applicable." << endl;
    }

    else
    {
        cout << "Invalid IP Address." << endl;
    }

    return 0;
}
