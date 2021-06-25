#pragma once

class Stream
{
public:

	enum class ClosingPolicy : unsigned
	{
		CompleteOperationsQueue,	// Send all the data already copied at the socket kernel buffer (do not tear connection, send TCP-FIN)
		ClearOperations,			// Tear the connection, send TCP-RST, drop all the data to be sent
	};

	virtual ~Stream() = default;

	// Casts object to TWrite, and writes it to the stream as WT argument
	template <typename TWrite, typename TNative>
	void WriteAs(const TNative& object);

	// Reads some data as TRead, casts it into TReturn and returns
	template <typename TRead, typename TReturn>
	TReturn ReadAs();

	// Writes argument to the stream <as is>, argument should be of integral type
	template <typename T>
	void Write(const T& object);

	// Reads argument from stream, argument must be of integral type
	template <typename T>
	T Read();

	// Try to connect to the endpoint, just returns if the connection was already established
	virtual void			Connect() = 0;

	// Closes connection
	virtual void			Close(ClosingPolicy policy) = 0;

	// Writes row data to the buffer. Note! this operation block thread
	virtual void			Write(const void* data, unsigned count) = 0;

	// Reads raw data from the stream, and store it into data. Note! this operation block thread
	virtual void			Read(void* data, unsigned count) = 0;

	// Reads from the stream the number of bytes, and nothing else
	virtual void			Skip(unsigned size) = 0;
};

template <typename TWrite, typename TNative>
void Stream::WriteAs(const TNative& object)
{
	const auto writableObject = static_cast<TWrite>(object);
	Write(&writableObject, sizeof writableObject);
}

template <typename TRead, typename TReturn>
TReturn Stream::ReadAs()
{
	TRead readObject;
	Read(&readObject, sizeof readObject);
	return static_cast<TReturn>(readObject);
}

template <typename T>
void Stream::Write(const T& object)
{
	Write(&object, sizeof object);
}

template <typename T>
T Stream::Read()
{
	T res;
	Read(&res, sizeof(res));
	return res;
}