#include <assert.h>

/***************************************************************************************
 *	File Name				:	LinkList.hpp
 *	CopyRight				:	2024 QG Studio
 *	SYSTEM					:   win11
 *	Create Data				:	2024.3.16
 *
 *
 *--------------------------------Revision History--------------------------------------
 *
 *
 *
 ***************************************************************************************/

 /**************************************************************
*	Multi-Include-Prevent Section
**************************************************************/

#ifndef __LINKLIST__H__
#define __LINKLIST__H__

namespace QGHW {

/**************************************************************
*	Macro Define Section	�궨��
**************************************************************/


/**************************************************************
*	Struct Define Section
**************************************************************/

//�ڵ���
template <typename T>
class Node
{
public:
	T m_Data;	//�洢����
	Node* m_Next;	//ָ����һ���ڵ�
	Node* m_Pre;	//ָ����һ���ڵ�

public:
	Node();
	Node(const T& value, Node* pre, Node* next);
};


/**************************************************************
*	Prototype Declare Section
**************************************************************/

/**
 *  @name        : inline Node<T>::Node()
 *	@description : �ڵ��Ĭ�Ϲ��캯��
 *	@param		 : None
 *	@return		 : Node
 *  @notice      : None
 */
template <typename T>
inline Node<T>::Node()
	:m_Next(nullptr), m_Pre(nullptr) {}

/**
 *  @name        : void DestroyList_DuL(DuLinkedList *L)
 *	@description : destroy a linked list
 *	@param		 : L(the head node)
 *	@return		 : status
 *  @notice      : None
 */
template <typename T>
inline Node<T>::Node(const T& value, Node* pre, Node* next)
	:m_Data(value), m_Pre(pre), m_Next(next) {}


/**************************************************************
*	Struct Define Section
**************************************************************/

//���������
template <typename T>
class ListIterator
{
public:
	typedef ListIterator<T> iterator;
	typedef Node<T> node_type;

public:
	ListIterator()
		:m_Pointer(nullptr) {}
	ListIterator(node_type* pointer)
		:m_Pointer(pointer) {}
	ListIterator(const iterator& it)
		:m_Pointer(it.m_Pointer) {}
	~ListIterator() {}

	//�����ò�����
	inline T& operator*()const
	{
		return m_Pointer->m_Data;
	}

	inline T& operator->()const
	{
		return &(m_Pointer->m_Data);
	}

	//������ǰ�üӼ�,����ĵ�����Ϊ˫���������ֻ��ǰ�ƺ��ƣ�������Ծʽ����
	inline iterator& operator++()
	{
		this->m_Pointer = this->m_Pointer->m_Next;
		return *this;
	}
	//���üӼ�,���ܷ��ؾֲ����ݵ�����
	inline iterator operator++(int)
	{
		iterator tmp = *this;
		++(*this);
		return tmp;
	}

	//ǰ�ü���
	inline iterator& operator--()
	{
		this->m_Pointer = this->m_Pointer->m_Pre;
		return *this;
	}
	//���ü���
	inline iterator operator--(int)
	{
		iterator tmp = *this;
		--(*this);
		return tmp;
	}

	//�������Ƚ�
	inline bool operator==(const iterator& right)const
	{
		return m_Pointer == right.m_Pointer;
	}
	inline bool operator!=(const iterator& right)const
	{
		return !(*this == right);
	}

public:
	node_type* m_Pointer;
};


/**************************************************************
*	Struct Define Section
**************************************************************/

//������
template <typename T>
class LinkList
{
public:
	typedef Node<T> node_type;
	typedef ListIterator<T> iterator;

public:
	LinkList();	//Ĭ�Ϲ���
	LinkList(const T& value);	//�вι���
	~LinkList();	//����

	inline bool IsEmpty()const;
	inline size_t Size()const;
	inline iterator Begin()const;
	inline iterator End()const;
	inline T& Front()const;
	inline T& Back()const;
	inline void PushBack(const T& value);
	inline void PushFront(const T& value);

private:
	inline Node<T>* allocate_memory();

private:
	node_type* m_Head;	//�����ͷ�ڵ�	
	node_type* m_Tail;	//����β�ڵ�
	size_t m_Size;	//����Ĵ�С
};


/**************************************************************
*	Prototype Declare Section
**************************************************************/

/**
 *  @name        : inline Node<T>* LinkList<T>::allocate_memory()
 *	@description : �ֶ����亯��,����û��Ĭ�Ϲ��캯�������
 *	@param		 : None
 *	@return		 : static_cast<node_type*>(::operator new(sizeof(node_type)));
 *  @notice      : None
 */
template <typename T>
inline Node<T>* LinkList<T>::allocate_memory()
{
	return static_cast<node_type*>(::operator new(sizeof(node_type)));
}
	
/**
 *  @name        : inline LinkList<T>::LinkList()
 *	@description : Ĭ�Ϲ���
 *	@param		 : None
 *	@return		 : None
 *  @notice      : None
 */
template <typename T>
inline LinkList<T>::LinkList()
	:m_Size(0)
{
	m_Head = allocate_memory();	//����ͷ�ڵ�

	m_Tail = m_Head;
}
/**
 *  @name        : inline LinkList<T>::LinkList(const T& value)
 *	@description : Ĭ�Ϲ���
 *	@param		 : const T& value
 *	@return		 : None
 *  @notice      : None
 */
template <typename T>
inline LinkList<T>::LinkList(const T& value)
{
	m_Size = 0;
	m_Head = new node_type();	//����ͷ�ڵ�
	PushBack(value);	//β������Ԫ��
}	

/**
*  @name        : inline LinkList<T>::~LinkList()
*  @description : ��������
*  @param		: None
*  @return		: None
*  @notice      : None
*/
template <typename T>
inline LinkList<T>::~LinkList()
{
}
	
/**
*  @name        : inline bool LinkList<T>::IsEmpty()const
*  @description : �ж��Ƿ�Ϊ��
*  @param		: None
*  @return		: m_Size == 0
*  @notice      : None
*/
template <typename T>
inline bool LinkList<T>::IsEmpty()const
{
	return m_Size == 0;
}
	
/**
*  @name        : inline size_t LinkList<T>::Size()const
*  @description : ���������С
*  @param		: None
*  @return		: m_Size
*  @notice      : None
*/
template <typename T>
inline size_t LinkList<T>::Size()const
{
	return m_Size;
}
	
/**
*  @name        : typename inline ListIterator<T> LinkList<T>::Begin()const
*  @description : �����׽ڵ�ĵ�����
*  @param		: None
*  @return		: iterator(m_Head->m_Next)
*  @notice      : None
*/
template <typename T>
typename inline ListIterator<T> LinkList<T>::Begin()const
{
	assert(!IsEmpty());
	return iterator(m_Head->m_Next);
}
	
/**
*  @name        : typename inline ListIterator<T> LinkList<T>::End()const
*  @description : �������һ��Ԫ����һ��λ�õĵ�����
*  @param		: None
*  @return		: ++iterator(m_Tail)
*  @notice      : ��֪������ôʵ��ԭ�����ܵ�End()���Զ�����ָ�����һ��Ԫ�ء�
	����ְ����һ��Ԫ�صĵ������Ӽ�һ�¾��ܴﵽԤ�ڵ�Ч������Ȼ��֪��ԭ�򣬵�ֻ�ܽ������á�
	֪��ԭ���ˣ��ӼӺ���˿�ָ�룬Begin()�Ӽ����Ҳ��ɿ�ָ�룬���Ե�����ͣ�ˣ��������޷��õ�����ǰ�ơ�
*/
template <typename T>
typename inline ListIterator<T> LinkList<T>::End()const
{
	assert(!IsEmpty());
	return ++iterator(m_Tail);
}
	
/**
*  @name        : typename inline T& LinkList<T>::Front()const
*  @description : �����׽ڵ�
*  @param		: None
*  @return		: m_Head->m_Next->m_Data
*  @notice      : None
*/
template <typename T>
typename inline T& LinkList<T>::Front()const
{
	assert(!IsEmpty());
	return m_Head->m_Next->m_Data;
}
	
/**
*  @name        : typename inline T& LinkList<T>::Back()const
*  @description : ����β�ڵ�
*  @param		: None
*  @return		: m_Tail->m_Data
*  @notice      : None
*/
template <typename T>
typename inline T& LinkList<T>::Back()const
{
	assert(!IsEmpty());
	return m_Tail->m_Data;
}
	
/**
*  @name        : inline void LinkList<T>::PushBack(const T& value)
*  @description : β������Ԫ��
*  @param		: const T& value
*  @return		: None
*  @notice      : None
*/
template <typename T>
inline void LinkList<T>::PushBack(const T& value)
{
	node_type* node = new node_type(value, m_Tail, m_Tail->m_Next);
	m_Tail->m_Next = node;
	m_Tail = node;
	node = nullptr;
	m_Size++;
}
	
/**
*  @name        : inline void LinkList<T>::PushBack(const T& value)
*  @description : ͷ������Ԫ��
*  @param		: const T& value
*  @return		: None
*  @notice      : None
*/
template <typename T>
inline void LinkList<T>::PushFront(const T& value)
{
	node_type* node = new node_type(value, m_Head, m_Head->m_Next);
	if (!IsEmpty()) {	//��Ϊ�ǿ�Ҫ����ǰ��ָ��
		m_Head->m_Next->m_Pre = node;
		m_Head->m_Next = node;
	}
	else {	//��Ϊ��Ҫ����βָ��
		m_Head->m_Next = node;
		m_Tail = node;
	}
	node = nullptr;
	m_Size++;
}
	


}

/**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/
#endif // !__LINKLIST__H__
