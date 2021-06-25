#include "TcpStream.h"

#include <iostream>
#include <Winsock2.h>
#include <ws2tcpip.h>
#include "ws2ipdef.h"
#include "ws2def.h"
//#include <Mstcpip.h>

namespace
{
	WSADATA WsaData;
	unsigned int InitializedCount = 0;
}

TcpStream::~TcpStream()
{
	--InitializedCount;

	if (InitializedCount == 0)
		WSACleanup();
}
// ------------------------------------------------------------------------------
TcpStream::TcpStream(std::string host, unsigned port)
	: m_socket(INVALID_SOCKET)
    , m_host(std::move(host))
    , m_port(port)
{
	if (InitializedCount == 0)
		WSAStartup(MAKEWORD(2, 2), &WsaData);

	++InitializedCount;
}
// ------------------------------------------------------------------------------
void TcpStream::Connect()
{
	if (IsOpened())
		return;

	const auto addressInfo = ResolveAddressInfo();

	m_socket = socket(addressInfo->ai_family, SOCK_STREAM, addressInfo->ai_protocol);
	if (m_socket == INVALID_SOCKET)
		RaiseException("Cannot create socket to the endpoint");

	bool connected = false;
	for (auto curAddress = addressInfo; curAddress != nullptr; curAddress = curAddress->ai_next)
	{	// In case the computer name is used as IP alias, there are might be multiple addresses to connect
		// just run the connection operation according to the linked list of addresses, while not succeeded
		if (connect(m_socket, curAddress->ai_addr, sizeof(sockaddr)) == 0)
		{
			connected = true;
			break;
		}
	}

	if (!connected)
	{
		m_socket = INVALID_SOCKET;
		RaiseException("Cannot connect to the endpoint");
	}

	SetSocketOptions();
}
// ------------------------------------------------------------------------------
addrinfo* TcpStream::ResolveAddressInfo() const
{
	// NOTE! We have to resolve the address info for every connection. if addrinfo struct will be cashed there are occured data corruption,
	// now a day the explanation of this phenomena is hidden for me,
	// btw in every sample, I found at the msdn or github addrinfo resolves before connection without cashing
	addrinfo hints;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET; // IPv4

	addrinfo* addressInfo = nullptr;
	const int errorCode = getaddrinfo(m_host.c_str(), std::to_string(m_port).c_str(), &hints, &addressInfo);
	if (errorCode != 0)
		RaiseException("Cannot resolve connection info to the endpoint");

	return addressInfo;
}
// ------------------------------------------------------------------------------
void TcpStream::SetSocketOptions() const throw()
{
	const int noDelay = 1;
	setsockopt(m_socket, IPPROTO_TCP, TCP_NODELAY, (const char*)&noDelay, sizeof noDelay);

	//struct tcp_keepalive alive;
	//alive.onoff = 1;
	//alive.keepalivetime = 1000;
	//alive.keepaliveinterval = 500;
	//DWORD dwBytesRet = 0;
	//WSAIoctl(m_socket, SIO_KEEPALIVE_VALS, &alive, sizeof alive,
	//	nullptr, 0, &dwBytesRet, nullptr, nullptr);

	const int aliveTime = 3;
	setsockopt(m_socket, IPPROTO_TCP, TCP_MAXRT, (const char*)&aliveTime, sizeof aliveTime);

	const int bufferSize = 1 << 15;
	setsockopt(m_socket, SOL_SOCKET, SO_SNDBUF, (const char*)&bufferSize, sizeof bufferSize);
}
// ------------------------------------------------------------------------------
void TcpStream::Close(ClosingPolicy policy) throw()
{
	const std::lock_guard locker(m_socketCloseMutex);
	// close operation (unlike of open) might be run from different threads, thus a critical section is needed
	if (IsOpened())
	{
		if (policy == ClosingPolicy::ClearOperations)
			shutdown(m_socket, SD_BOTH);
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
	}
}
// ------------------------------------------------------------------------------
void TcpStream::Write(const void* data, unsigned count)
{
	if (!WriteImpl(data, count))
	{
		Close(ClosingPolicy::ClearOperations);
		RaiseException("Cannot write data to the socket");
	}
}
// ------------------------------------------------------------------------------
bool TcpStream::WriteImpl(const void* data, std::size_t count) const
{
	unsigned sentTotal = 0;
	while (sentTotal != count)
	{
		const int sent = send(m_socket, (const char*)data + sentTotal, (int)(count - sentTotal), 0);
		if (sent <= 0) // error appeared, marking connection as closed.
			return false;

		sentTotal += sent;
	}

	return true;
}
// ------------------------------------------------------------------------------
void TcpStream::Read(void* data, unsigned count)
{
	if (!ReadImpl(data, count))
	{
		Close(ClosingPolicy::ClearOperations);
		RaiseException("Cannot read data from the socket");
	}
}
// ------------------------------------------------------------------------------
bool TcpStream::ReadImpl(void* data, std::size_t count) const
{
	unsigned receivedTotal = 0;
	while (receivedTotal != count)
	{
		const int received = recv(m_socket, (char*)data + receivedTotal, (int)(count - receivedTotal), 0);
		if (received <= 0) // error appeared, marking connection as closed.
			return false;

		receivedTotal += received;
	}

	return true;
}
// ------------------------------------------------------------------------------
void TcpStream::Skip(unsigned size)
{
	char buffer[SkipBufferSize];
	for (int i = size; i > 0; i -= SkipBufferSize)
		Read(buffer, size);
}
// ------------------------------------------------------------------------------
bool TcpStream::IsOpened() const throw()
{
	return m_socket != INVALID_SOCKET;
}
// ------------------------------------------------------------------------------
void TcpStream::RaiseException(const char* message) const
{
	std::cout << message << std::endl;
	//throw std::runtime_error(message);
}