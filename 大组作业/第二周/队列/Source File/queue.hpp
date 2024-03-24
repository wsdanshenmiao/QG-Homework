#include "allocator.hpp"

/***************************************************************************************
 *    File Name                :   queue.hpp
 *    CopyRight                :
 *
 *    SYSTEM                   :   Windows
 *    Create Data              :   2024.3.23
 *    Author/Corportation      :   LiWenHao
 *
 *
 *--------------------------------Revision History--------------------------------------
 *    No    version        Data            Revised By            Item            Description
 *
 *
 ***************************************************************************************/

 /**************************************************************
  *    Multi-Include-Prevent Section
  **************************************************************/

#ifndef __QUEUE__HPP__
#define __QUEUE__HPP__

namespace QGHW {

/**************************************************************
 *    Struct Define Section
 **************************************************************/

//���нڵ�
template <typename T>
class QueueNode
{
public:
	using valueType = T;
	using thisType = QueueNode<T>;
	using pointer = thisType*;

	valueType m_Data;
	pointer m_Next;

	QueueNode();
	QueueNode(const valueType& value, const pointer next);
};

/**************************************************************
 *    Prototype Declare Section
**************************************************************/

/**
 *  @Name        : QueueNode<T>::QueueNode()
 *  @Description : Ĭ�Ϲ���
 *  @Parameters  : None
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T>
QueueNode<T>::QueueNode(){}


/**
 *  @Name        : QueueNode<T>::QueueNode(const valueType& value, const pointer next)
 *  @Description : �вι���
 *  @Parameters  : None
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T>
QueueNode<T>::QueueNode(const valueType& value, const pointer next)
	:m_Data(value), m_Next(next) {}



/**************************************************************
 *    Struct Define Section
 **************************************************************/

template <typename T>
class QueueIterator
{
public:
	using thisType = QueueIterator<T>;
	using valueType = T;
	using pointer = T*;
	using reference = T&;
	using nodeType = QueueNode<T>*;

	QueueIterator();
	QueueIterator(nodeType node);
	QueueIterator(const thisType& other);

	inline reference operator*()const;
	inline pointer operator->()const;
	inline thisType& operator++();
	inline thisType operator++(int);
	inline bool operator==(const thisType& other)const;
	inline bool operator!=(const thisType& other)const;

private:
	nodeType m_Node;
};

 /**************************************************************
  *    Prototype Declare Section
 **************************************************************/

 /**
  *  @Name        : QueueIterator<T>::QueueIterator()
  *  @Description : Ĭ�Ϲ���
  *  @Parameters  : None
  *  @Return value: None
  *  @Notice      : None
  */
template <typename T>
QueueIterator<T>::QueueIterator()
	:m_Node(nullptr) {}


/**
 *  @Name        : QueueIterator<T>::QueueIterator(nodeType node)
 *  @Description : �вι���
 *  @Parameters  : nodeType node��Ҫά���Ľڵ�
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T>
QueueIterator<T>::QueueIterator(nodeType node)
	:m_Node(node) {}


/**
 *  @Name        : QueueIterator<T>::QueueIterator(const thisType& other)
 *  @Description : ��������
 *  @Parameters  : const thisType& other��Ҫ�������Ķ���
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T>
QueueIterator<T>::QueueIterator(const thisType& other)
	:m_Node(other.m_Node) {}


/**
 *  @Name        : inline T& QueueIterator<T>::operator*()const
 *  @Description : ���ؽ����ã����ؽڵ�����
 *  @Parameters  : None
 *  @Return value: m_Node->m_Data���ڵ�����
 *  @Notice      : None
 */
template <typename T>
inline T& QueueIterator<T>::operator*()const
{
	return m_Node->m_Data;
}


/**
 *  @Name        : inline T& QueueIterator<T>::operator*()const
 *  @Description : ���س�Ա��������������ؽڵ����ݵ�ַ
 *  @Parameters  : None
 *  @Return value: &(m_Node->m_Data)���ڵ����ݵ�ַ
 *  @Notice      : None
 */
template <typename T>
inline T* QueueIterator<T>::operator->()const
{
	return &(m_Node->m_Data);
}


/**
 *  @Name        : inline QueueIterator<T>& QueueIterator<T>::operator++()
 *  @Description : ����ǰ�üӼ�
 *  @Parameters  : None
 *  @Return value: *this
 *  @Notice      : None
 */
template <typename T>
inline QueueIterator<T>& QueueIterator<T>::operator++()
{
	this->m_Node = this->m_Node->m_Next;
	return *this;
}


/**
 *  @Name        : inline QueueIterator<T> QueueIterator<T>::operator++(int)
 *  @Description : ���غ��üӼ�
 *  @Parameters  : None
 *  @Return value: *tmp
 *  @Notice      : None
 */
template <typename T>
inline QueueIterator<T> QueueIterator<T>::operator++(int)
{
	thisType tmp = *this;
	++(*this);
	return tmp;
}


/**
 *  @Name        : inline bool QueueIterator<T>::operator==(const thisType& other)const
 *  @Description : �������Ƚ�
 *  @Parameters  : const thisType& other
 *  @Return value: this->m_Node == other.m_Node
 *  @Notice      : None
 */
template <typename T>
inline bool QueueIterator<T>::operator==(const thisType& other)const
{
	return this->m_Node == other.m_Node;
}


/**
 *  @Name        : inline bool QueueIterator<T>::operator==(const thisType& other)const
 *  @Description : �������Ƚ�
 *  @Parameters  : const thisType& other
 *  @Return value: this->m_Node == other.m_Node
 *  @Notice      : None
 */
template <typename T>
inline bool QueueIterator<T>::operator!=(const thisType& other)const
{
	return !(*this == other);
}


/**************************************************************
 *    Struct Define Section
 **************************************************************/

template <typename T, typename Allocator = QGHW::allocator<T>>
class queue
{
public:
	using valueType = T;
	using nodeType = QueueNode<T>;
	using valueAllocator = Allocator;
	using nodeAllocator = QGHW::allocator<nodeType>;
	using sizeType = size_t;
	using reference = valueType&;
	using constReference = const valueType&;
	using pointer = typename valueAllocator::pointer;
	using constPointer = typename valueAllocator::constPointer;
	using iterator = QueueIterator<T>;

public:
	inline queue();
	inline queue(sizeType count, const valueType& value);
	inline queue(const queue& other);
	inline queue(queue&& other);

	inline ~queue();

	inline sizeType Size()const;
	inline bool IsEmpty()const;
	inline reference Front()const;
	inline reference Back()const;
	inline iterator Begin()const;
	inline iterator End()const;
	inline void Push(constReference value);
	inline void Push(valueType&& value);
	inline void Pop();
	inline void Assign(sizeType count, constReference value);
	//ͻȻ���������к���������Щ����
	//inline iterator Insert(iterator pos, constReference value);
	//inline iterator Insert(iterator pos, valueType&& value);
	//inline iterator Insert(iterator pos, sizeType count, constReference value);
	//inline iterator Erase(iterator pos);
	inline void Clear();
	inline void Resize(sizeType count);
	inline void Resize(sizeType count, constReference value);
	inline void Swap(queue<T, Allocator>& other);

	inline queue<T, Allocator>& operator=(const queue<T, Allocator>& other);
	inline queue<T, Allocator>& operator=(queue<T, Allocator>&& other);

private:
	inline nodeType* FindPre(nodeType* node);

	inline void _Resize(sizeType count, constReference value);


private:
	nodeType* m_Head;
	nodeType* m_Tail;
	sizeType m_Size;
	valueAllocator m_vAllocator;
	nodeAllocator m_nAllocator;
};


/**************************************************************
 *    Prototype Declare Section
 **************************************************************/

 /**
  *  @Name        : inline queue<T, Allocator>::queue()
  *  @Description : Ĭ�Ϲ���,����ͷ�ڵ�
  *  @Parameters  : None
  *  @Return value: None
  *  @Notice      : None
  */
template <typename T, typename Allocator>
inline queue<T, Allocator>::queue()
	:m_Size(0)
{
	m_Head = m_nAllocator.allocate(1);	//����ͷ�ڵ��ڴ�
	m_Head->m_Next = m_Head;	//ѭ������
	m_Tail = m_Head;
}


/**
 *  @Name        : inline queue<T, Allocator>::queue(sizeType count, const valueType& value)
 *  @Description : �вι���,����ͷ�ڵ�
 *  @Parameters  : sizeType count, const valueType& value
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline queue<T, Allocator>::queue(sizeType count, const valueType& value)
{
	m_Head = m_nAllocator.allocate(1);	//����ͷ�ڵ��ڴ�
	m_Head->m_Next = m_Head;	//ѭ������
	m_Tail = m_Head;
	for (int i = 0; i < count; i++) {
		Push(std::move(value));
	}
}


/**
 *  @Name        : inline queue<T, Allocator>::queue(const queue& other)
 *  @Description : ��������
 *  @Parameters  : const queue& other
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline queue<T, Allocator>::queue(const queue<T, Allocator>& other)
{
	m_Head = m_nAllocator.allocate(1);	//����ͷ�ڵ��ڴ�
	m_Head->m_Next = m_Head;	//ѭ������
	m_Tail = m_Head;
	for (queue<T, Allocator>::iterator it = other.Begin(); it != other.End(); it++) {
		this->Push(std::move(*it));
	}
}


/**
 *  @Name        : inline queue<T, Allocator>::queue(queue&& other)
 *  @Description : �ƶ�����
 *  @Parameters  : queue&& other
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline queue<T, Allocator>::queue(queue<T, Allocator>&& other)
{
	this->m_Head = other.m_Head;
	this->m_Tail = other.m_Tail;
	this->m_Size = other.m_Size;
	other.m_Head = nullptr;
	other.m_Tail = nullptr;
	other.m_Size = 0;
}


/**
 *  @Name        : inline queue<T, Allocator>::~queue()
 *  @Description : ��������
 *  @Parameters  : None
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline queue<T, Allocator>::~queue()
{
	if (m_Head) {
		Clear();
		m_nAllocator.deallocate(m_Head, 1);	//�ͷ�ͷ�ڵ�
	}
}


/**
 *  @Name        : inline size_t queue<T, Allocator>::Size()const
 *  @Description : ���ض��д�С
 *  @Parameters  : None
 *  @Return value: m_Size
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline size_t queue<T, Allocator>::Size()const
{
	return m_Size;
}


/**
 *  @Name        : inline bool queue<T, Allocator>::IsEmpty()const
 *  @Description : �ж��Ƿ�Ϊ��
 *  @Parameters  : None
 *  @Return value: m_Size == 0
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline bool queue<T, Allocator>::IsEmpty()const
{
	return m_Size == 0;
}


/**
 *  @Name        : inline T& queue<T, Allocator>::Front()const
 *  @Description : �����׽ڵ������
 *  @Parameters  : None
 *  @Return value: m_Head->m_Next->m_Data
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline T& queue<T, Allocator>::Front()const
{
	assert(!IsEmpty());
	return m_Head->m_Next->m_Data;
}


/**
 *  @Name        : inline T& queue<T, Allocator>::Back()const
 *  @Description : ����β�ڵ������
 *  @Parameters  : None
 *  @Return value: m_Tail->m_Data
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline T& queue<T, Allocator>::Back()const
{
	assert(!IsEmpty());
	return m_Tail->m_Data;
}


/**
 *  @Name        : inline QueueIterator<T> queue<T, Allocator>::Begin()const
 *  @Description : ����ά���׽ڵ�ĵ�����
 *  @Parameters  : None
 *  @Return value: iterator(m_Head->m_Next)
 *  @Notice      : Ϊ��ʱ����Ended()
 */
template <typename T, typename Allocator>
inline QueueIterator<T> queue<T, Allocator>::Begin()const
{
	if (IsEmpty()) {
		return End();
	}
	else {
		return iterator(m_Head->m_Next);
	}
}


/**
 *  @Name        : inline QueueIterator<T> queue<T, Allocator>::End()const
 *  @Description : ����ά��ͷ�ڵ�ĵ�����
 *  @Parameters  : None
 *  @Return value: iterator(m_Head)
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline QueueIterator<T> queue<T, Allocator>::End()const
{
	return iterator(m_Head);
}


/**
 *  @Name        : inline void queue<T, Allocator>::Push(const valueType& value)
 *  @Description : ͷ������Ԫ��
 *  @Parameters  : const valueType& value��Ҫ���������
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline void queue<T, Allocator>::Push(constReference value)
{
	nodeType* node = m_nAllocator.allocate(1);	//����ڵ��ڴ�
	m_vAllocator.construct((pointer)node, value);	//����Ԫ��
	node->m_Next = m_Head->m_Next;
	m_Head->m_Next = node;
	if (IsEmpty()) {
		m_Tail = node;
	}
	node = nullptr;
	m_Size++;
}


/**
 *  @Name        : inline void queue<T, Allocator>::Push(valueType&& value)
 *  @Description : ͷ������Ԫ��,������ֵ
 *  @Parameters  : valueType&& value��Ҫ���������
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline void queue<T, Allocator>::Push(valueType&& value)
{
	nodeType* node = m_nAllocator.allocate(1);	//����ڵ��ڴ�
	m_vAllocator.construct((pointer)node, std::move(value));	//������ֵ����Ԫ��
	node->m_Next = m_Head->m_Next;
	m_Head->m_Next = node;
	if (IsEmpty()) {
		m_Tail = node;
	}
	node = nullptr;
	m_Size++;
}


/**
 *  @Name        : inline void queue<T, Allocator>::Pop()
 *  @Description : β��ɾ��Ԫ��
 *  @Parameters  : None
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline void queue<T, Allocator>::Pop()
{
	assert(!IsEmpty());
	nodeType* node = m_Tail;
	nodeType* pre = FindPre(node);	//Ѱ��ǰ��Ԫ
	pre->m_Next = node->m_Next;
	m_vAllocator.destroy((pointer)node);	//���ýڵ���Ԫ�ص���������
	m_nAllocator.deallocate(node, 1);	//�ͷŽڵ��ڴ�
	node = nullptr;
	m_Tail = pre;
	m_Size--;
}


/**
 *  @Name        : inline void queue<T, Allocator>::Assign(sizeType count, constReference value)
 *  @Description : ��պ����·���
 *  @Parameters  : sizeType count, constReference value
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline void queue<T, Allocator>::Assign(sizeType count, constReference value)
{
	Clear();
	for (int i = 0; i < count; i++) {
		Push(std::move(value));
	}
}


/**
 *  @Name        : inline void queue<T, Allocator>::Clear()
 *  @Description : �������Ԫ��
 *  @Parameters  : None
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline void queue<T, Allocator>::Clear()
{
	m_Tail->m_Next = nullptr;	//�Ͽ�ѭ��
	nodeType* node = m_Head->m_Next;	//�ӹ�Ԫ��
	m_Head->m_Next = m_Head;	//����ѭ��
	m_Tail = m_Head;
	while (node) {
		nodeType* tmp = node->m_Next;
		m_vAllocator.destroy((pointer)node);	//��������
		m_nAllocator.deallocate(node, 1);	//�ͷ��ڴ�
		node = tmp;
	}
	m_Size = 0;
}


/**
 *  @Name        : inline void queue<T, Allocator>::Resize(sizeType count)
 *  @Description : ���ô�С
 *  @Parameters  : sizeType count
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline void queue<T, Allocator>::Resize(sizeType count)
{
	_Resize(count, T());
}


/**
 *  @Name        : inline void queue<T, Allocator>::Resize(sizeType count)
 *  @Description : ���ô�С
 *  @Parameters  : sizeType count, constReference value
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline void queue<T, Allocator>::Resize(sizeType count, constReference value)
{
	_Resize(count, T(value));
}


/**
 *  @Name        : inline void queue<T, Allocator>::Swap(queue<T, Allocator>& other)
 *  @Description : ������������
 *  @Parameters  : queue<T, Allocator>& other
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline void queue<T, Allocator>::Swap(queue<T, Allocator>& other)
{
	nodeType* headTmp = m_Head;
	nodeType* tailTmp = m_Tail;
	sizeType sizeTmp = m_Size;
	m_Head = other.m_Head;
	m_Tail = other.m_Tail;
	m_Size = other.Size;
	other.m_Head = headTmp;
	other.m_Tail = tailTmp;
	other.Size = sizeTmp;
}


/**
 *  @Name        : inline queue<T, Allocator>& queue<T, Allocator>::operator=(const queue<T, Allocator>& other)
 *  @Description : ��ֵ����
 *  @Parameters  : const queue<T, Allocator>& other
 *  @Return value: *this
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline queue<T, Allocator>& queue<T, Allocator>::operator=(const queue<T, Allocator>& other)
{
	if (m_Head) {	//�ǿ����ͷ�ԭ�ڴ�
		Clear();
	}
	else {	//Ϊ��
		m_Head = m_nAllocator.allocate(1);	//����ͷ�ڵ��ڴ�
		m_Head->m_Next = m_Head;	//ѭ������
		m_Tail = m_Head;
	}
	for (queue<T, Allocator>::iterator it = other.Begin(); it != other.End(); it++) {
		this->Push(std::move(*it));
	}
	return *this;
}


/**
 *  @Name        : inline queue<T, Allocator>& queue<T, Allocator>::operator=(queue<T, Allocator>&& other)
 *  @Description : �ƶ���ֵ
 *  @Parameters  : queue<T, Allocator>&& other
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline queue<T, Allocator>& queue<T, Allocator>::operator=(queue<T, Allocator>&& other)
{
	if (m_Head) {	//�ǿ����ͷ�ԭ�ڴ�
		Clear();
		m_nAllocator.deallocate(m_Head, 1);	//�ͷ�ͷ�ڵ�
	}
	this->m_Head = other.m_Head;
	this->m_Tail = other.m_Tail;
	this->m_Size = other.m_Size;
	other.m_Head = nullptr;
	other.m_Tail = nullptr;
	other.m_Size = 0;
	return *this;
}


/**
 *  @Name        : inline bool operator==(const queue<T, Allocator>& left, const queue<T, Allocator>& right)
 *  @Description : �ж����������Ƿ����
 *  @Parameters  : ��������
 *  @Return value: true or false
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline bool operator==(const queue<T, Allocator>& left, const queue<T, Allocator>& right)
{
	if (left.Size() != right.Size()) {
		return false;
	}
	for (QueueIterator<T> itl = left.Begin(), itr = right.Begin()
		; itl != left.End(); itl++, itr++) {
		if (*itl != *itr) {
			return false;
		}
	}
	return true;
}


/**
 *  @Name        : inline bool operator!=(const queue<T, Allocator>& left, const queue<T, Allocator>& right)
 *  @Description : �ж����������Ƿ����
 *  @Parameters  : ��������
 *  @Return value: true or false
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline bool operator!=(const queue<T, Allocator>& left, const queue<T, Allocator>& right)
{
	return !(left == right);
}


/**
 *  @Name        : inline bool operator<(const queue<T, Allocator>& left, const queue<T, Allocator>& right)
 *  @Description : �ж��������еĴ�С
 *  @Parameters  : ��������
 *  @Return value: true or false
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline bool operator<(const queue<T, Allocator>& left, const queue<T, Allocator>& right)
{
	size_t size = left.Size() < right.Size() ? left.Size() : right.Size();
	int i = 0;
	for (QueueIterator<T> itl = left.Begin(), itr = right.Begin()
		; i < size; itl++, itr++, i++) {
		if (*itl > *itr) {
			return false;
		}
	}
	if (left.Size() < right.Size()) {	//ǰ��Ԫ�ض���ȣ��Ϳ���С
		return true;
	}
	return false;
}


/**
 *  @Name        : inline bool operator<=(const queue<T, Allocator>& left, const queue<T, Allocator>& right)
 *  @Description : �ж��������еĴ�С
 *  @Parameters  : ��������
 *  @Return value: true or false
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline bool operator<=(const queue<T, Allocator>& left, const queue<T, Allocator>& right)
{
	return (left < right || left == right);
}


/**
 *  @Name        : inline bool operator>(const queue<T, Allocator>& left, const queue<T, Allocator>& right)
 *  @Description : �ж��������еĴ�С
 *  @Parameters  : ��������
 *  @Return value: true or false
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline bool operator>(const queue<T, Allocator>& left, const queue<T, Allocator>& right)
{
	return !(left <= right);
}


/**
 *  @Name        : inline bool operator>=(const queue<T, Allocator>& left, const queue<T, Allocator>& right)
 *  @Description : �ж��������еĴ�С
 *  @Parameters  : ��������
 *  @Return value: true or false
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline bool operator>=(const queue<T, Allocator>& left, const queue<T, Allocator>& right)
{
	return !(left < right);
}





/**
 *  @Name        : inline QueueNode<T>* queue<T, Allocator>::FindPre(nodeType* node)
 *  @Description : Ѱ��ǰ��Ԫ
 *  @Parameters  : nodeType* node��ҪѰ��ǰ��Ԫ�Ľڵ�
 *  @Return value: pre
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline QueueNode<T>* queue<T, Allocator>::FindPre(nodeType* node)
{
	assert(node);
	nodeType* pre;
	for (pre = m_Head; pre->m_Next != node; pre = pre->m_Next);
	return pre;
}


/**
 *  @Name        : inline void queue<T, Allocator>::_Resize(sizeType count, constReference value)
 *  @Description : ���ô�С
 *  @Parameters  : sizeType count
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline void queue<T, Allocator>::_Resize(sizeType count, constReference value)
{
	if (0 <= count && count <= m_Size) {
		for (size_t i = count; i < m_Size;) {
			Pop();
		}
	}
	if (count > m_Size) {
		for (size_t i = m_Size; i < count; i++) {
			Push(std::move(value));
		}
	}
}




}

#endif 
