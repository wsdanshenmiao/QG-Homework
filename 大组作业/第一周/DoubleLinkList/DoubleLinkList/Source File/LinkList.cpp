#include <assert.h>
#include <iostream>

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
	typedef Node<T> this_type;

public:
	T m_Data;	//�洢����
	this_type* m_Next;	//ָ����һ���ڵ�
	this_type* m_Pre;	//ָ����һ���ڵ�

public:
	inline Node();
	inline Node(const T& value);
	inline Node(const T& value, this_type* pre, this_type* next);
	inline void insert(this_type* next);
};


/**************************************************************
*	Prototype Declare Section
**************************************************************/

/**
 *  @name        : inline Node<T>::Node()
 *	@description : �ڵ��Ĭ�Ϲ��캯��
 *	@param		 : None
 *	@return		 : None
 *  @notice      : None
 */
template <typename T>
inline Node<T>::Node()
	:m_Next(nullptr), m_Pre(nullptr) {}

/**
 *  @name        : inline Node<T>::Node(const T& value)
 *	@description : �вι���
 *	@param		 : const T& value
 *	@return		 : status
 *  @notice      : None
 */
template <typename T>
inline Node<T>::Node(const T& value)
	:m_Data(value), m_Pre(nullptr), m_Next(nullptr) {}

/**
 *  @name        : inline Node<T>::Node(const T& value, this_type* pre, this_type* next)
 *	@description : �вι���
 *	@param		 : const T& value, this_type* pre, this_type* next
 *	@return		 : None
 *  @notice      : None
 */
template <typename T>
inline Node<T>::Node(const T& value, this_type* pre, this_type* next)
	:m_Data(value), m_Pre(pre), m_Next(next) {}

/**
 *  @name        : inline void Node<T>::insert(this_type* next)
 *	@description : ���ڵ����next֮ǰ
 *	@param		 : this_type* next
 *	@return		 : None
 *  @notice      : None
 */
template <typename T>
inline void Node<T>::insert(this_type* next)
{
	m_Next = next;
	m_Pre = next->m_Pre;
	next->m_Pre->m_Next = this;
	next->m_Pre = this;
}



/**************************************************************
*	Struct Define Section
**************************************************************/

//������
template <typename T>
class LinkList
{
public:
	typedef Node<T> node_type;
	//���������
	class iterator
	{
	public:
		typedef Node<T> node_type;

	public:
		iterator()
			:m_Pointer(nullptr) {}
		iterator(node_type* pointer)
			:m_Pointer(pointer) {}
		iterator(const iterator& it)
			:m_Pointer(it.m_Pointer) {}
		~iterator() {}

		//�����ò�����
		inline T& operator*()const
		{
			return m_Pointer->m_Data;
		}

		inline T* operator->()const
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
	inline void PopBack();
	inline void PopFront();
	inline iterator empalce(iterator pos, T&& value);
	inline iterator insert(iterator pos, const T& value);
	inline iterator insert(iterator pos, size_t num, const T& value);
	inline iterator insert(iterator pos, T&& value);
	inline iterator erase(iterator pos);
	inline iterator erase(iterator first, iterator last);
	inline void clear();
	inline void resize(size_t size);
	inline void resize(size_t size, const T& value);


private:
	inline void _Resize(size_t size, const T& value);

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
template <typename Type>
inline static Type* allocate_memory(const size_t& size)
{
	return static_cast<Type*>(::operator new(size));
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
	m_Head = allocate_memory<node_type>(sizeof(node_type));	//����ͷ�ڵ�
	m_Head->m_Next = nullptr;
	m_Head->m_Pre = nullptr;
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
	clear();
	delete m_Head;
	m_Head = nullptr;
	m_Tail = nullptr;
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
*  @name        : inline LinkList<T>::iterator LinkList<T>::Begin()const
*  @description : �����׽ڵ�ĵ�����
*  @param		: None
*  @return		: iterator(m_Head->m_Next)
*  @notice      : None
*/
template <typename T>
typename inline LinkList<T>::iterator LinkList<T>::Begin()const
{
	if (IsEmpty()) {
		return End();
	}
	return iterator(m_Head->m_Next);
}
	
/**
*  @name        : inline LinkList<T>::iterator LinkList<T>::End()const
*  @description : �������һ��Ԫ����һ��λ�õĵ�����
*  @param		: None
*  @return		: ++iterator(m_Tail)
*  @notice      : ��֪������ôʵ��ԭ�����ܵ�End()���Զ�����ָ�����һ��Ԫ�ء�
	����ְ����һ��Ԫ�صĵ������Ӽ�һ�¾��ܴﵽԤ�ڵ�Ч������Ȼ��֪��ԭ�򣬵�ֻ�ܽ������á�
	֪��ԭ���ˣ��ӼӺ���˿�ָ�룬Begin()�Ӽ����Ҳ��ɿ�ָ�룬���Ե�����ͣ�ˣ��������޷��õ�����ǰ�ơ�
	�����������ָ��β�ڵ�
*/
template <typename T>
typename inline LinkList<T>::iterator LinkList<T>::End()const
{
	iterator it(m_Tail);
	return it;
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
	
/**
*  @name        : inline void LinkList<T>::PopBack()
*  @description : β��ɾ��Ԫ��
*  @param		: None
*  @return		: None
*  @notice      : None
*/
template <typename T>
inline void LinkList<T>::PopBack()
{
	assert(!IsEmpty());
	node_type* node = m_Tail;
	m_Tail = m_Tail->m_Pre;
	m_Tail->m_Next = node->m_Next;
	delete node;
	node = nullptr;
	m_Size--;
}

/**
*  @name        : inline void LinkList<T>::PopFront()
*  @description : ͷ��ɾ��Ԫ��
*  @param		: None
*  @return		: None
*  @notice      : None
*/
template <typename T>
inline void LinkList<T>::PopFront()
{
	assert(!IsEmpty());
	node_type* node = m_Head->m_Next;
	m_Head->m_Next = node->m_Next;
	if (node->m_Next) {
		node->m_Next->m_Pre = m_Head;	//����ǰ��Ԫ
	}
	delete node;
	node = nullptr;
	m_Size--;
}

/**
*  @name        : inline LinkList<T>::iterator LinkList<T>::empalce(iterator pos, T&& value)
*  @description : posǰ�͵ع������
*  @param		: ListIterator<T> pos, T&& value
*  @return		: iterator(pos.m_Pointer->m_Pre)
*  @notice      : �ɴ��˽⵽�ɱ�ģ������������Ǻ��˽⣬����û��Ӧ��
*/
template <typename T>
typename inline LinkList<T>::iterator LinkList<T>::empalce(iterator pos, T&& value)
{
	node_type* node = allocate_memory<node_type>(sizeof(node_type));	//ʹ��ȫ��new�����ڴ�
	new ((void*) &(node->m_Data)) T(value);	//�ֶ����캯��
	if (!IsEmpty()) {
		node->insert(pos.m_Pointer);
	}
	else {
		node->m_Next = m_Head->m_Next;
		node->m_Pre = m_Head;
		m_Head->m_Next = node;
	}
	if (!node->m_Next) {	//����β�ڵ�
		m_Tail = node;
	}
	m_Size++;
	return iterator(pos.m_Pointer->m_Pre);
}

/**
*  @name        : inline LinkList<T>::iterator LinkList<T>::insert(iterator pos, const T& value)
*  @description : ��posǰ����value
*  @param		: ListIterator<T> pos, const T& value
*  @return		: None
*  @notice      : None
*/
template <typename T>
typename inline LinkList<T>::iterator LinkList<T>::insert(iterator pos, const T& value)
{
	node_type* node = new node_type(value);
	if (IsEmpty()) {
		node->m_Next = m_Head->m_Next;
		node->m_Pre = m_Head;
		m_Head->m_Next = node;
	}
	else {
		node->insert(pos.m_Pointer);
	}
	if (!node->m_Next) {	//���½ڵ�
		m_Tail = node;
	}
	m_Size++;
	return iterator(node);
}

/**
*  @name        : inline LinkList<T>::iterator LinkList<T>::insert(iterator pos, size_t num, const T& value)
*  @description : ��posǰ����num��value
*  @param		: ListIterator<T> pos, size_t num, const T& value
*  @return		: ++it
*  @notice      : None
*/
template <typename T>
typename inline LinkList<T>::iterator LinkList<T>::insert(iterator pos, size_t num, const T& value)
{
	iterator it(pos);
	if (!IsEmpty()) {
		--it;	//ƫ�Ƶ�������ǰһ��������
	}
	for (; num > 0; num--, pos) {
		insert(pos, value);
		if (pos.m_Pointer == m_Head) {
			pos++;
		}
	}
	return ++it;
}

/**
*  @name        : inline LinkList<T>::iterator LinkList<T>::insert(iterator pos, T&& value)
*  @description : ��posǰ����value,��ֵ�汾
*  @param		: ListIterator<T> pos, const T&& value
*  @return		: ++it
*  @notice      : None
*/
template <typename T>
typename inline LinkList<T>::iterator LinkList<T>::insert(iterator pos, T&& value)
{
	return empalce(pos, std::move(value));
}

/**
*  @name        : LinkList<T>::iterator LinkList<T>::erase(iterator pos)
*  @description : ɾ��pos����Ԫ��
*  @param		: iterator pos
*  @return		: �Ƴ������һ��������
*  @notice      : ��ŷ��ּӸ�β�ڵ���鷳
*/
template <typename T>
typename inline LinkList<T>::iterator LinkList<T>::erase(iterator pos)
{
	assert(!IsEmpty());
	node_type* node = pos.m_Pointer;
	++pos;
	node->m_Pre->m_Next = node->m_Next;
	if (node->m_Next) {	//����β�ڵ�
		node->m_Next->m_Pre = node->m_Pre;
	}
	else {	//����β�ڵ�
		m_Tail = node->m_Pre;
	}
	delete node;
	m_Size--;
	return iterator(pos);
}

/**
*  @name        : inline LinkList<T>::iterator LinkList<T>::erase(iterator pos)
*  @description : ɾ��first��last��Ԫ��
*  @param		: iterator first, iterator last
*  @return		: �Ƴ������һ��������
*  @notice      : None
*/
template <typename T>
typename inline LinkList<T>::iterator LinkList<T>::erase(iterator first, iterator last)
{
	for (; first != last;) {
		erase(first++);
	}
	erase(last);
	return ++last;
}

/**
*  @name        : inline void LinkList<T>::clear()
*  @description : ɾ������Ԫ��
*  @param		: None
*  @return		: None
*  @notice      : None
*/
template <typename T>
inline void LinkList<T>::clear()
{	
	node_type* node = m_Head->m_Next;
	m_Head->m_Next = nullptr;
	m_Tail = m_Head;
	while (node) {
		node_type* tmp = node->m_Next;
		delete node;
		node = tmp;
	}
	m_Size = 0;
}

/**
*  @name        : inline void resize(size_t size)
*  @description : ����ָ����С
*  @param		: size_t size, const T& value
*  @return		: None
*  @notice      : None
*/
template <typename T>
inline void LinkList<T>::_Resize(size_t size, const T& value)
{
	if (size < m_Size) {	//ɾ������ڵ�
		for (; size < m_Size;) {
			PopBack();
		}
	}
	else {	//�����½ڵ�
		for (; size > m_Size;) {
			PushBack(value);
		}
	}
}
template <typename T>
inline void LinkList<T>::resize(size_t size)
{
	_Resize(size, T());
}
template <typename T>
inline void LinkList<T>::resize(size_t size, const T& value)
{
	_Resize(size, value);
}

}

/**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/
#endif // !__LINKLIST__H__
