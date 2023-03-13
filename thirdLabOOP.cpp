#include <iostream>

template <typename T>
class Container {
private:
	class Node {
	public:
		Node* next;
		T value;

		Node(T value) : value(value), next(nullptr) { }
		~Node() { }
	};

	Node* first, * last;
	size_t size;

public:
	class Iterator {
	private:
		Node* node;

	public:
		Iterator(Node* node) : node(node) { }

		// Проверка на равенство
		bool operator==(const Iterator& other) const {
			return node == other.node;
		}

		// Проверка на неравенство
		bool operator!=(const Iterator& other) const {
			return !operator==(other);
		}

		// Разыменование итератора
		T operator*() const {
			if (node) {
				return node->value;
			}
		}

		// Переход к "next" узлу
		void operator++(int) {
			if (node) {
				node = node->next;
			}
		}
	};

	// Конструктор
	Container() : first(nullptr), last(nullptr), size(0) { }
	~Container() {
		while (first) {
			popFront();
		}
	}
	
	bool isEmpty() const {
		return first == nullptr;
	}

	// Получаем размер списка
	size_t getSize() const {
		return size;
	}

	// Получаем итератор на начало
	Iterator begin() const {
		return Iterator(first);
	}

	// Получаем итератор на конец
	Iterator end() const {
		return Iterator(last);
	}

	// Вставка в конец
	void pushBack(const T& value) { 
		Node* newNode = new Node(value);
		if (isEmpty()) {
			first = last = newNode;
		} else {
			last->next = newNode;
			last = newNode;
		}
		size++;
	}

	// Вставка в начало
	void pushFront(const T& value) {
		Node* newNode = new Node(value);
		if (isEmpty()) {
			first = last = newNode;
		} else {
			newNode->next = first;
			first = newNode;
		}
		size++;
	}

	// Вставка по n-ому индексу
	void pushNth(size_t position, const T& value) {
		if (position == 0) {
			pushFront(value);
			return;
		} else if (position == size - 1) {
			pushBack(value);
			return;
		} else if (position > size - 1) {
			return;
		}

		Node* newNode = new Node(value);
		Node* temp = first;
		
		for (size_t i = 1; i < position; i++) {
			temp = temp->next;
		}

		newNode->next = temp->next;
		temp->next = newNode;
		size++;
	}

	// Возврат первого элемента
	T getFront() {
		return first->value;
	}

	// Возврат последнего элемента
	T getBack() {
		return last->value;
	}

	// Возврат n-ного элемента
	T getNth(size_t position) {
		Node* result = first;
		for (int i = 0; i < position; i++) {
			result = result->next;
		}
		return result->value;
	}

	// Возврат первого элемента с его удалением
	T popFront() {
		T result = first->value;
		Node* temp = first;
		first = first->next;

		delete temp;
		size--;
		return result;
	}


	// Возврат последнего элемента с его удалением
	T popBack() {
		T result = last->value;
		Node* temp = first;
		while (temp->next != last) {
			temp = temp->next;
		}
		delete last;
		last = temp;
		size--;
		return result;
	}

	// Возврат n-ного элемента с его удалением
	T popNth(size_t position) {
		if (position == 0) {
			return popFront();
		} else if (position == size - 1) {
			return popBack();
		} else if (position > size - 1) {
			return -1;
		}

		Node* temp = first, * prev = nullptr;
		for (int i = 0; i < position; i++) {
			prev = temp;
			temp = temp->next;
		}
		int result = temp->value;
		prev->next = temp->next;
		delete temp;

		size--;
		return result;
	}

	// Проверка на наличие
	bool isContain(const T& value) {
		Node* temp = first;
		while (temp != last) {
			if (temp->value == value)
				return true;
			temp = temp->next;
		}
		if (temp->value == value)
			return true;
		return false;
	}
};

int main() {
	Container<std::pair<int, int>> arr;

	for (int i = 0; i < 50; i++)
		for (int j = 0; j < 50; j++)
			arr.pushBack({i, j});
		
	std::cout << "popFront() :\n";
	for (int i = 0; i < 100; i++)
		std::cout << arr.getFront().first << ' ' << arr.popFront().second << "\n";

	std::cout << "popBack() :\n";
	for (int i = 0; i < 100; i++)
		std::cout << arr.getBack().first << ' ' << arr.popBack().second << "\n";

	std::cout << "size = " << arr.getSize() << "\n";

}