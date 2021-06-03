//------------------------------------------------------------------------------
// ProducerConsumerQueue.h
// This is single producer thread/single consumer thread lock-free queue implementation 
// based off of Herb Sutter's Oct 2008 article (http://www.ddj.com/hpc-high-performance-computing/210604448)
//
// Copyright (c) 2011 Multisoft
// All rights reserved.
//
// Date:       17.05.11
// Author:     Соловьев И.С.
//------------------------------------------------------------------------------
#pragma once

#include <atomic>

namespace ClassLib
{

template <typename T> 
class ProducerConsumerQueue
{
private:
	struct Node
	{
		template<typename TVal>
		Node(TVal&& val) : value(std::forward<TVal>(val)), next(nullptr) { }
		T value;
		Node* next;
	};

	Node* 				m_first;	// Producer Only
	std::atomic<Node*> 	m_divider;	// Producer / Consumer
	std::atomic<Node*> 	m_last;		// Producer / Consumer

public:
	// This queue must be fully constructed before being used in another thread.
	ProducerConsumerQueue()
	{
		m_first = m_divider = m_last = new Node(T());
	}

	~ProducerConsumerQueue()
	{
		while (m_first != nullptr)
		{
			Node* temp = m_first;
			m_first = temp->next;
			delete temp;
		}
	}

	template<typename TVal>
	void Produce(TVal&& item)
	{
		Node* tmpLast = m_last.load();
		tmpLast->next = new Node(std::forward<TVal>(item));

		ProduceImpl(tmpLast);
	}

	bool Consume(T& item)
	{
		Node* divNode = m_divider.load();
		Node* lastNode = m_last.load();
		if (divNode != lastNode)
		{
			item = std::move(divNode->next->value);
			divNode = divNode->next;
			m_divider.store(divNode);

			return true;
		}
		return false;
	}

	bool Peek(T& item)
	{
		Node* divNode = m_divider.load();
		Node* lastNode = m_last.load();
		if (divNode != lastNode)
		{
			item = divNode->next->value;
			return true;
		}
		return false;
	}
	
private:
	void ProduceImpl(Node* tmpLast)
	{
		tmpLast = tmpLast->next;

		m_last.store(tmpLast);

		Node* div = m_divider.load();
		while (m_first != div)
		{
			Node* temp = m_first;
			m_first = m_first->next;
			delete temp;

			div = m_divider.load();
		}
	}
};	
//------------------------------------------------------------------------------
}