#ifndef __LIST_HPP
#define __LIST_HPP

#include<exception>

template<typename T>
class List {
private:
	struct Node {
		T m_data;
		Node* m_next;

		Node(T data, Node* next)
			:m_data(data)
			,m_next(next)
		{}
	};

	Node* m_head;
	
public:

	//Big 4
	List()
		:m_head(nullptr)
	{}

	List(const List& otherList) = delete;//not in use
	const List& operator=(const List& otherList) = delete;
	~List() {
		while (!empty()) {
			pop_front();
		}
	}

	void push_back(T element) {
		if (m_head == nullptr) {
			m_head = new Node(element, nullptr);
		}
		else {
			Node* lastElementOfList = m_head;
			for (; lastElementOfList->m_next != nullptr; lastElementOfList = lastElementOfList->m_next);
			lastElementOfList->m_next = new Node(element, nullptr);
		}
	}

	void push_front(T element) {
		m_head = new Node(element, m_head);
	}

	void pop_back() {
		if (empty()) {
			throw "empty list";
		}

		//Ако има само един елемент
		if (m_head->m_next == nullptr) {
			delete m_head;
			m_head = nullptr;
			return;
		}

		//else
		Node* lastElement = m_head;
		for (; lastElement->m_next->m_next != nullptr; lastElement = lastElement->m_next);
		delete lastElement->m_next;
		lastElement->m_next = nullptr;
	}

	void pop_front() {
		if (m_head == nullptr) {
			throw "Error! Empty list!";
		}

		Node* oldHead = m_head;
		m_head = m_head->m_next;
		delete oldHead;
	}

	void insert(T element, int pos) {
		Node* insertionNode = m_head;

		for (; pos > 0; --pos) {
			if (insertionNode == nullptr) {
				throw "No such index in list";
			}
			insertionNode = insertionNode->m_next;
		}

		insertionNode->m_next = new Node(element, insertionNode->m_next);
	}

	void remove(int index) {
		Node* toDeleteNode = m_head;
		for (; index > 1; --index) {
			if (toDeleteNode == nullptr || toDeleteNode->m_next == nullptr) {
				throw "No such index in list";
			}
			toDeleteNode = toDeleteNode->m_next;
		}

		Node* oldNode = toDeleteNode->m_next;
		toDeleteNode->m_next = oldNode->m_next;
		delete oldNode;
	}

	const T& getBack() const {
		if (empty()) {
			throw "Error! List is empty. Invalid operation getFront()";
		}

		Node* back = m_head;
		for (; back->m_next != nullptr; back = back->m_next);
		return back->m_data;

	}

	const T& getFront()const {
		if (empty()) {
			throw "Error! List is empty. Invalid operation getFront()";
		}

		return m_head->m_data;
	}

	const bool empty()const {
		return m_head == nullptr;
	}

	const T& getAt(int index) {
		Node* getNode = m_head;
		for (; index > 0; --index) {
			if (getNode == nullptr) {
				throw "Error! No such index in list!";
			}
			getNode = getNode->m_next;
		}
		return getNode->m_data;
	}

	Node* begin()const {
		return m_head;
	}
};

#endif
