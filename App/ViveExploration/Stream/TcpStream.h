#pragma once

#include <mutex>

#include "Stream.h"
#include <string>

struct addrinfo;

class TcpStream final : public Stream
{
	typedef unsigned long long Socket;
public:
	virtual ~TcpStream() override;
	TcpStream(std::string host, unsigned port);

	// Try to connect to the endpoint, just returns if the connection already established
	virtual void			Connect() override;

	// Writes row data to the buffer. Note! this operation block thread
	virtual void			Write(const void* data, unsigned count) override;

	// Reads raw data from the stream, and store it into data. Note! this operation block thread
	virtual void			Read(void* data, unsigned count) override;

	// Reads from the stream some amount of data, and do nothing
	virtual void			Skip(unsigned size) override;

	// Closes connection
	virtual void			Close(ClosingPolicy policy) throw() override;
private:
	// Tries to find the endpoint to connect to
	addrinfo* ResolveAddressInfo() const;

	// Adjusts the socket options
	void		SetSocketOptions() const throw();

	// Logs occured error and raises runtime_error with a given message inside
	void		RaiseException(const char* message) const;

	// Implementation of the related functions
	bool		ReadImpl(void* data, std::size_t count) const;
	bool		WriteImpl(const void* data, std::size_t count) const;

	// Checks if connection is currently opened
	bool		IsOpened() const throw();

	Socket		m_socket;			// Handle of the win api socket
	std::mutex	m_socketCloseMutex;	// Sync of the socket close operation
	std::string m_host;
	unsigned	m_port;

	static const unsigned	SkipBufferSize = 8192;			// Size of the buffer to skip unnecessary data.
															// According to Microsoft this size is pretty good to read data from a TCP stream
};
