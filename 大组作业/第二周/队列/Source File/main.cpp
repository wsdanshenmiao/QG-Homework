#define _CRT_SECURE_NO_WARNINGS

#include <memory>
#include <iostream>
#include "allocator.hpp"
#include "queue.hpp"

class Entity
{
public:
	int m_X, m_Y;

	Entity(int x, int y)
		:m_X(x), m_Y(y) {}

	Entity& operator++()
	{
		m_X++;
		m_Y++;
		return *this;
	}
	Entity& operator++(int)
	{
		Entity e = *this;
		m_X++;
		m_Y++;
		return e;
	}

	friend std::ostream& operator<<(std::ostream& stream, const Entity& e);
	bool operator!=(const Entity& e) {
		return m_X != e.m_X || m_Y != e.m_Y;
	}
	bool operator==(const Entity& e) {
		return !(*this != e);
	}
	bool operator<(const Entity& e) {
		return m_X < e.m_X && m_Y < e.m_Y;
	}
	bool operator>(const Entity& e) {
		return !(*this < e || *this == e);
	}
};

std::ostream& operator<<(std::ostream& stream, const Entity& e)
{
	stream << e.m_X << " " << e.m_Y << std::endl;
	return stream;
}

enum Function
{
	EXIT,
	PRINT,
	PUSH,
	POP,
	ASSIGN,
	CLEAR,
	RESIZE,
	SWAP,
};

void Catalogue()
{
	printf("��Entity(int x, int y)Ϊ����ʾ����Ч��������һ�ξ�һ�����x��y��ֵ\n");
	printf("***************************0.EXIT			1.PRINT*************************\n");
	printf("***************************2.PUSH			3.POP***************************\n");
	printf("***************************4.ASSIGN			5.CLEAR*************************\n");
	printf("***************************6.RESIZE			7.SWAP**************************\n");

}

void testMemory()
{
	QGHW::allocator<int> a;
	std::cout << sizeof(a) << std::endl;
	QGHW::queue<int> q;
	std::cout << sizeof(q) << std::endl;
	QGHW::QueueNode<int> n;
	std::cout << sizeof(n) << std::endl;
	QGHW::QueueIterator<int> i;
	std::cout << sizeof(i) << std::endl;
}

void test()
{
	enum Function select;
	QGHW::queue<Entity> queue;
	for (int i = 0; i < 5; i++) {
		queue.Push(Entity(i, i));
	}
	do {
		Catalogue();	//��ӡĿ¼
		printf("��ѡ��:");
		scanf("%d", &select);	//ö�ٲ�����cin
		fflush(stdin);
		system("cls");
		switch (select)
		{
		case EXIT:
			break;
		case PRINT: {
			for (QGHW::queue<Entity>::iterator it = queue.Begin(); it != queue.End(); it++) {
				std::cout << *it << std::endl;
			}
			getchar();
			getchar();
			break;
		}
		case PUSH: {
			int value;
			std::cout << "������ҪPUSH��ֵ����cin�����������ַ��ͽ���������0����";
			std::cin >> value;
			if (std::cin.fail())
			{
				std::cin.clear();
			}
			else {
				queue.Push(Entity(value, value));
			}
			getchar();
			break;
		}
		case POP: {
			queue.Pop();
			for (QGHW::queue<Entity>::iterator it = queue.Begin(); it != queue.End(); it++) {
				std::cout << *it << std::endl;
			}
			getchar();
			break;
		}
		case ASSIGN: {
			int count;
			int value;
			std::cout << "������ҪASSIGN�ĸ�������cin�����������ַ��ͽ���������0����";
			std::cin >> count;
			if (std::cin.fail())
			{
				std::cin.clear();
			}
			else {
				std::cout << "������ҪASSIGN��ֵ����cin�����������ַ��ͽ���������0����";
				std::cin >> value;
				if (std::cin.fail()){
					std::cin.clear();
				}
				else {
					queue.Assign(count, Entity(value, value));
					for (QGHW::queue<Entity>::iterator it = queue.Begin(); it != queue.End(); it++) {
						std::cout << *it << std::endl;
					}
				}
			}
			getchar();
			break;
		}
		case CLEAR: {
			queue.Clear();
			getchar();
			break;
		}
		case RESIZE: {
			int count;
			int value;
			std::cout << "������ҪRESIZE�������С����ɶ����������";
			std::cin >> count;
			if (std::cin.fail())
			{
				std::cin.clear();
			}
			else {
				std::cout << "������ҪRESIZE��ֵ����cin�����������ַ��ͽ���������0����";
				std::cin >> value;
				if (std::cin.fail()) {
					std::cin.clear();
				}
				else {
					queue.Resize(count, Entity(value, value));
					for (QGHW::queue<Entity>::iterator it = queue.Begin(); it != queue.End(); it++) {
						std::cout << *it << std::endl;
					}
				}
			}
			getchar();
			break;
		}
		case SWAP: {
			int count;
			int value;
			std::cout << "������ҪSWAP����ĸ�������cin�����������ַ��ͽ���������0����";
			std::cin >> count;
			if (std::cin.fail())
			{
				std::cin.clear();
			}
			else {
				std::cout << "������ҪSWAP�����ֵ����cin�����������ַ��ͽ���������0����";
				std::cin >> value;
				if (std::cin.fail()) {
					std::cin.clear();
				}
				else {
					QGHW::queue<Entity> tmp;
					queue.Assign(count, Entity(value, value));
					for (QGHW::queue<Entity>::iterator it = queue.Begin(); it != queue.End(); it++) {
						std::cout << *it << std::endl;
					}
				}
			}

			getchar();
			break;
		}
		default: {
			printf("�������\n");
			getchar();
			break;
		}
		}
		system("cls");
		fflush(stdin);
	} while (select);
}

void test1()
{
	std::cout << "�вι��죺" << std::endl;
	QGHW::queue<Entity> q1(3, Entity(6, 6));
	for (QGHW::queue<Entity>::iterator it = q1.Begin(); it != q1.End(); it++) {
		std::cout << *it << std::endl;
	}
	std::cout << "�������죺" << std::endl;
	QGHW::queue<Entity> q2(3, Entity(5, 5));
	QGHW::queue<Entity> q3(q2);
	for (QGHW::queue<Entity>::iterator it = q3.Begin(); it != q3.End(); it++) {
		std::cout << *it << std::endl;
	}
	std::cout << "�ƶ����죺" << std::endl;
	QGHW::queue<Entity> q5(3, Entity(4, 4));
	QGHW::queue<Entity> q4(std::move(q5));
	for (QGHW::queue<Entity>::iterator it = q4.Begin(); it != q4.End(); it++) {
		std::cout << *it << std::endl;
	}
	std::cout << "�ȽϷ����ԣ�" << std::endl;
	std::cout << (q2 == q3) << std::endl;	//1
	std::cout << (q2 != q3) << std::endl;	//0
	std::cout << (q1 == q3) << std::endl;	//0
	std::cout << (q1 != q3) << std::endl;	//1
	std::cout << (q1 < q3) << std::endl;	//0
	std::cout << (q1 <= q3) << std::endl;	//0
	std::cout << (q1 > q3) << std::endl;	//1
	std::cout << (q1 >= q3) << std::endl;	//1
	std::cout << "û����" << std::endl;
}

int main()
{
	test1();
	getchar();
	test();
}