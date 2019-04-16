#pragma once

#include "list.h"
#include<memory>
#include<iostream>

template<class t_data>
class LinkedList :public List<t_data>
{
	struct Node
	{
		t_data data;
		std::unique_ptr<Node> nextNode;

		Node(const t_data &_data)
			:data(_data)
		{}
	};

	int sizeCounter = 0;
	std::unique_ptr<Node> head;
		
public:
	LinkedList() = default;

	void insert(const t_data& data) override
	{
		++sizeCounter;
		insertDateBegin(data);
	}

	void remove(const t_data& data) override
	{
		if (!head)
			return;

		if (head->data == data) {
			auto newhead = std::move(head->nextNode);
			head = std::move(newhead);
			--sizeCounter;
			return;
		}

		if (!head->nextNode) {
			std::cout << data << "Is not Found!";
		}

		Node* prev = head.get();
		Node* next = head->nextNode.get();

		while (next->data != data) {
			prev = next;
			next = next->nextNode.get();
		}

		if (!next) {
			std::cout << data << "Is not Found!";
			return;
		}

		std::unique_ptr<Node> temp = std::move(next->nextNode);
		prev->nextNode = std::move(temp);
	}

	void traverseList() const override {
		Node* Node = head.get();
		while (Node)
		{
			std::cout << Node->data << ' ';
			Node = Node->nextNode.get();
		}
		std::cout << '\n';
	}

	int size() const override {
		return sizeCounter;
	}


private:
	void insertDateBegin(const t_data &data) {
		std::unique_ptr<Node> newNode = std::make_unique<Node>(data);
		newNode->nextNode = std::move(head);
		head = std::move(newNode);
	}
};