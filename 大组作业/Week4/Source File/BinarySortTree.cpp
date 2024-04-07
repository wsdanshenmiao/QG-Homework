#ifndef __BINARY_SORT_TREE__HPP__
#define __BINARY_SORT_TREE__HPP__

#include "allocator.hpp"
#include <iostream>
#include <queue>
#include <stack>

namespace QGHW {



/*****************************
Class Declaration
*****************************/

//���Ľڵ�
template <typename Type>
class TreeNode
{
public:
	using valueType = Type;
	using thisType = TreeNode<valueType>;

	valueType m_Key;
	thisType* m_Parent;
	thisType* m_Left;
	thisType* m_Right;

	//ʹ��Ĭ�Ϲ��캯��
	TreeNode() = default;
	TreeNode(const thisType& other) = delete;
	thisType& operator==(const thisType& other) = delete;
};

template <typename T>
TreeNode<T>* FindPosterior(TreeNode<T>* node);	//����ָ���������ڵ�
template <typename T>
TreeNode<T>* FindFront(TreeNode<T>* node);



/*****************************
Class Declaration
*****************************/

//���ĵ�����
template <typename Key>
class TreeIterator
{
public:
	//ʹ��typename���߱���������һ�����ͣ����Ǳ���
	using nodePointer = TreeNode<Key>*;
	using keyType = Key;
	using pointer = keyType*;
	using reference = keyType&;
	using thisType = TreeIterator<Key>;

	TreeIterator();
	TreeIterator(nodePointer node);
	TreeIterator(const TreeIterator<Key>& other);
	inline TreeIterator<Key>& operator=(const TreeIterator<Key>& other);

	inline reference operator*() const;
	inline pointer operator->() const;
	inline thisType& operator++();
	inline thisType operator++(int);
	inline thisType& operator--();
	inline thisType operator--(int);

	inline bool operator==(const thisType& other) const;
	inline bool operator!=(const thisType& other) const;

public:
	nodePointer m_Pointer;
};

/*****************************
Class Definition
*****************************/

/**
 *  @Name        : TreeIterator()
 *  @Description : Ĭ�Ϲ���
 *  @Parameters  : None
 *  @Return value: None
 */
template <typename Key>
TreeIterator<Key>::TreeIterator()
	:m_Pointer(nullptr) {}

/**
 *  @Name        : TreeIterator()
 *  @Description : �вι���
 *  @Parameters  : const pointer& node
 *  @Return value: None
 */
template <typename Key>
TreeIterator<Key>::TreeIterator(nodePointer node)
	:m_Pointer(node) {}

/**
 *  @Name        : TreeIterator()
 *  @Description : �вι���
 *  @Parameters  : const pointer& node
 *  @Return value: None
 */
template <typename Key>
TreeIterator<Key>::TreeIterator(const TreeIterator<Key>& other)
	:m_Pointer(other.m_Pointer) {}

/**
 *  @Name        : TreeIterator()
 *  @Description : �вι���
 *  @Parameters  : const pointer& node
 *  @Return value: None
 */
template <typename Key>
inline TreeIterator<Key>& TreeIterator<Key>::operator=(const TreeIterator<Key>& other)
{
    m_Pointer = other.m_Pointer;
    return *this;
}
/**
 *  @Name        : operator*()
 *  @Description : ���ؽ�����
 *  @Parameters  : None
 *  @Return value: ���ڵ��еļ�ֵ
 */
template <typename Key>
inline Key& TreeIterator<Key>::operator*() const
{
	return m_Pointer->m_Key;
}

/**
 *  @Name        : operator->()
 *  @Description : ���ؼ�ͷ������
 *  @Parameters  : None
 *  @Return value: ���ڵ��м�ֵ�ĵ�ַ
 */
template <typename Key>
inline Key* TreeIterator<Key>::operator->() const
{
	return &(m_Pointer->m_Key);
}

/**
 *  @Name        : operator++()
 *  @Description : ����ǰ��++��ҪѰ�ұ��������ӽ��Ľڵ�
 *  @Parameters  : None
 *  @Return value: ++��ĵ�����
 */
template <typename Key>
inline TreeIterator<Key>& TreeIterator<Key>::operator++()
{
	m_Pointer = static_cast<nodePointer>(FindPosterior(m_Pointer));
	return *this;
}

/**
 *  @Name        : operator++(int)
 *  @Description : ���غ���++��ҪѰ�ұ��������ӽ��Ľڵ�
 *  @Parameters  : None
 *  @Return value: ++ǰ�ĵ�����
 */
template <typename Key>
inline TreeIterator<Key> TreeIterator<Key>::operator++(int)
{
	thisType tmp(*this);
	m_Pointer = static_cast<nodePointer>(FindPosterior(m_Pointer));
	return tmp;
}

/**
 *  @Name        : operator--()
 *  @Description : ����ǰ��--
 *  @Parameters  : None
 *  @Return value: --��ĵ�����
 */
template <typename Key>
inline TreeIterator<Key>& TreeIterator<Key>::operator--()
{
	m_Pointer = static_cast<nodePointer>(FindFront(m_Pointer));
	return *this;
}

/**
 *  @Name        : operator--(int)
 *  @Description : ���غ���--
 *  @Parameters  : None
 *  @Return value: --ǰ�ĵ�����
 */
template <typename Key>
inline TreeIterator<Key> TreeIterator<Key>::operator--(int)
{
	thisType tmp(*this);
	m_Pointer = static_cast<nodePointer>(FindFront(m_Pointer));
	return tmp;
}

/**
 *  @Name        : operator==
 *  @Description : �ж��Ƿ����
 *  @Parameters  : const thisType& other
 *  @Return value: true or false
 */
template <typename Key>
inline bool TreeIterator<Key>::operator==(const thisType& other) const
{
	return m_Pointer == other.m_Pointer;
}

/**
 *  @Name        : operator!=
 *  @Description : �ж��Ƿ����
 *  @Parameters  : const thisType& other
 *  @Return value: true or false
 */
template <typename Key>
inline bool TreeIterator<Key>::operator!=(const thisType& other) const
{
	return !(*this == other);
}


/*****************************
Class Declaration
*****************************/

template <
	typename Key,
	typename Compare =std::less<Key>,
	typename Allocator = QGHW::allocator<Key>
>class Tree
{
public:
	using keyType = Key;
	using sizeType = size_t;
	using keyCompare = Compare;
	using keyAllocator = Allocator;
	using reference = keyType&;
	using constReference = const keyType&;
	using pointer = typename Allocator::pointer;
	using constPointer = typename Allocator::constPointer;
	using thisType = Tree<Key, Compare, Allocator>;
	using iterator = QGHW::TreeIterator<Key>;
	using nodeType = TreeNode<Key>;
	using nodePointer = nodeType*;
	using nodeAllocator = QGHW::allocator<nodeType>;

	Tree();
	Tree(const thisType& other);
	Tree(thisType&& other);
	Tree(std::initializer_list<keyType> initList);

	inline iterator Find(const keyType& key) const;
	inline std::pair<iterator, bool> Insert(const keyType& key);
	inline bool IsEmpty() const;
	inline sizeType Size() const;
	inline iterator Begin() const;
	inline iterator End() const;
	inline sizeType Erase(const Key& key);
	inline iterator Erase(iterator pos);

	inline Key* Traversal(void function(const TreeNode<Key>*, Key*));
	inline Key* PreTraversal();
	inline Key* InorderTraversal();
	inline Key* PostorderTraversal();

	inline Key* HierarchicalTraversal();

	inline Key* PreTNoRecursion();
	inline Key* ITNoRecursion();
	inline Key* PosTNoRecursion();

private:
	inline void _InitTree();
	inline std::pair<iterator, bool> _Insert(const keyType& key);
	inline std::pair<iterator, bool> _Erase(const Key& key);

private:
	sizeType m_Size;	//���Ĵ�С
	nodePointer m_Head;	//����ͷ�ڵ㣬����ά�����ڵ㣬Begin()��End()
	keyCompare m_keyCompate;	//��ֵ�Ƚ�
};

/*****************************
Class Definition	(public)
*****************************/

/**
 *  @Name        : Tree()
 *  @Description : Ĭ�Ϲ���ֻ����ͷ�ڵ�
 *  @Parameters  : None
 *  @Return value: None
 */
template <typename Key,typename C,typename A>
Tree<Key, C, A>::Tree()
{
	_InitTree();
}

template <typename Key, typename C, typename A>
Tree<Key, C, A>::Tree(const thisType& other)
{
	_InitTree();
	for (typename Tree<Key, C, A>::iterator it = other.Begin(); it != other.End(); it++){
		Insert(*it);
	}
}

template <typename Key, typename C, typename A>
Tree<Key, C, A>::Tree(thisType&& other)
{
	m_Head = other.m_Head;
	m_Size = other.m_Size;
	m_keyCompate = other.m_keyCompate;
	other.m_Head = nullptr;
	other.m_Size = 0;
}


/**
 *  @Name        : Find(const keyType& key)
 *  @Description : Ѱ��ĳ���ڵ�
 *  @Parameters  : const keyType& key
 *  @Return value: ҪѰ�ҽڵ�ĵ�����
 */
template <typename Key, typename C, typename A>
inline TreeIterator<Key> Tree<Key, C, A>::Find(const keyType& key) const
{
	nodePointer node = m_Head->m_Parent;
	for (; node && key != node->m_Key;) {
		if (m_keyCompate(key, node->m_Key)) {	//��key�ȸýڵ�С���ƶ���������
			node = node->m_Left;
		}
		else {	//�����ƶ���������
			node = node->m_Right;
		}
		return iterator(node);	//�����ҵ��ڵ�ĵ�������û�ҵ��ͷ��ؿ�ָ�������
	}
	return iterator(node);
}

/**
 *  @Name        : Insert(const keyType& key)
 *  @Description : ����ĳ��Ԫ��
 *  @Parameters  : const keyType& key
 *  @Return value: std::pair
 */
template <typename Key, typename C, typename A>
inline std::pair<TreeIterator<Key>, bool> Tree<Key, C, A>::Insert(const keyType& key)
{
	return _Insert(key);
}

/**
 *  @Name        : IsEmpty()
 *  @Description : �ж��Ƿ�Ϊ��
 *  @Parameters  : None
 *  @Return value: true or false
 */
template <typename Key, typename C, typename A>
inline bool Tree<Key, C, A>::IsEmpty() const
{
	return m_Size == 0;
}

/**
 *  @Name        : Size()
 *  @Description : �������Ĵ�С
 *  @Parameters  : None
 *  @Return value: �������Ĵ�С
 */
template <typename Key, typename C, typename A>
inline size_t Tree<Key, C, A>::Size() const
{
	return m_Size;
}

/**
 *  @Name        : Begin()
 *  @Description : ��СԪ�صĵ���������ʱ����End()
 *  @Parameters  : None
 *  @Return value: ��СԪ�صĵ�����
 */
template <typename Key, typename C, typename A>
inline TreeIterator<Key> Tree<Key, C, A>::Begin() const
{
	if (IsEmpty()) {
		return End();
	}
	return iterator(m_Head->m_Left);
}

/**
 *  @Name        : End()
 *  @Description : ͷ�ڵ�ĵ�����
 *  @Parameters  : None
 *  @Return value: ͷ�ڵ�ĵ�����
 */
template <typename Key, typename C, typename A>
inline TreeIterator<Key> Tree<Key, C, A>::End() const
{
	
	return iterator(m_Head);;
}

template <typename Key, typename C, typename A>
inline size_t Tree<Key, C, A>::Erase(const Key& key)
{
	std::pair<iterator, bool> pair = _Erase(key);
	return pair.second;
}

template <typename Key, typename C, typename A>
inline TreeIterator<Key> Tree<Key, C, A>::Erase(iterator pos)
{
	std::pair<iterator, bool> pair = _Erase(*pos);
	return pair.first;
}

template <typename Key>
inline void pre_Traversal(const TreeNode<Key>* node, Key* arr)
{
	if (node) {
		static size_t i = 0;
		*(arr + i++) = node->m_Key;
		pre_Traversal(node->m_Left, arr);
		pre_Traversal(node->m_Right, arr);
	}
}
template <typename Key>
inline void inorder_Traversal(const TreeNode<Key>* node, Key* arr)
{
	if (node) {
		static size_t i = 0;
		inorder_Traversal(node->m_Left, arr);
		*(arr + i++) = node->m_Key;
		inorder_Traversal(node->m_Right, arr);
	}
}
template <typename Key>
inline void pos_Traversal(const TreeNode<Key>* node, Key* arr)
{
	if (node) {
		static size_t i = 0;
		pos_Traversal(node->m_Left, arr);
		pos_Traversal(node->m_Right, arr);
		*(arr + i++) = node->m_Key;
	}
}
template <typename Key, typename C, typename A>
inline Key* Tree<Key, C, A>::Traversal(void function(const TreeNode<Key>*, Key*))
{
	if (m_Size == 0) {
		return nullptr;
	}
	QGHW::allocator<Key> k_Allocator;
	Key* arr = k_Allocator.allocate(m_Size);
	function(m_Head->m_Parent, arr);
	return arr;
}
template <typename Key, typename C, typename A>
inline Key* Tree<Key, C, A>::PreTraversal()
{
	return Traversal(pre_Traversal);
}
template <typename Key, typename C, typename A>
inline Key* Tree<Key, C, A>::InorderTraversal()
{
	return Traversal(inorder_Traversal);
}
template <typename Key, typename C, typename A>
inline Key* Tree<Key, C, A>::PostorderTraversal()
{
	return Traversal(pos_Traversal);
}


template <typename Key, typename C, typename A>
inline Key* Tree<Key, C, A>::HierarchicalTraversal()
{
	if (m_Size == 0) {
		return nullptr;
	}
	size_t i = 0;
	keyAllocator k_Allocator;
	Key* arr = k_Allocator.allocate(m_Size);
	std::queue<nodePointer> queue;
	queue.push(m_Head->m_Parent);	//���ڵ����
	for (; !queue.empty();) {	//����Ϊ����û������
		nodePointer tmp = queue.front();
		queue.pop();	//����
		*(arr + i++) = tmp->m_Key;
		if (tmp->m_Left) {	//��ڵ����
			queue.push(tmp->m_Left);
		}
		if (tmp->m_Right) {	//�ҽڵ����
			queue.push(tmp->m_Right);
		}
	}
	return arr;
}

template <typename Key, typename C, typename A>
inline Key* Tree<Key, C, A>::PreTNoRecursion()
{
	if (m_Size == 0) {
		return nullptr;
	}
	size_t i = 0;
	keyAllocator k_Allocator;
	Key* arr = k_Allocator.allocate(m_Size);
	std::stack<nodePointer> stack;	//ʹ��ջģ��ݹ�
	stack.push(m_Head->m_Parent);	//���ڵ���ջ
	while (!stack.empty()) {	//������
		nodePointer tmp = stack.top();	//��¼ջ��
		stack.pop();	//��ջ
		*(arr + i++) = tmp->m_Key;
		if (tmp->m_Right) {	//�ҽڵ���ջ
			stack.push(tmp->m_Right);
		}
		if (tmp->m_Left) {	//��ڵ���ջ
			stack.push(tmp->m_Left);
		}
	}
	return arr;
}

template <typename Key, typename C, typename A>
inline Key* Tree<Key, C, A>::ITNoRecursion()
{
	if (m_Size == 0) {
		return nullptr;
	}
	size_t i = 0;
	keyAllocator k_Allocator;
	Key* arr = k_Allocator.allocate(m_Size);
	std::stack<nodePointer> stack;	//ʹ��ջģ��ݹ�
	nodePointer node = m_Head->m_Parent;
	while (!stack.empty() || node) {
		if (node) {
			stack.push(node);
			node = node->m_Left;
		}
		else {
			node = stack.top();
			stack.pop();
			*(arr + i++) = node->m_Key;
			node = node->m_Right;
		}
	}
	return arr;
}

template <typename Key, typename C, typename A>
inline Key* Tree<Key, C, A>::PosTNoRecursion()
{
	if (m_Size == 0) {
		return nullptr;
	}
	size_t i = 0, j = 0;
	keyAllocator k_Allocator;
	Key* arr = k_Allocator.allocate(m_Size);
	std::vector<Key> vector;	//��ʱ���飬���ת
	vector.reserve(m_Size);
	std::stack<nodePointer> stack;	//ʹ��ջģ��ݹ�
	stack.push(m_Head->m_Parent);	//���ڵ���ջ
	while (!stack.empty()) {	//������
		nodePointer tmp = stack.top();	//��¼ջ��
		stack.pop();	//��ջ
		vector.push_back(tmp->m_Key);
		if (tmp->m_Left) {	//��ڵ���ջ
			stack.push(tmp->m_Left);
		}
		if (tmp->m_Right) {	//�ҽڵ���ջ
			stack.push(tmp->m_Right);
		}
	}
	//���ת���鼴Ϊ������
	for (typename std::vector<Key>::reverse_iterator it = vector.rbegin(); it != vector.rend(); *(arr + j++) = *it, it++);
	return arr;
}




/*****************************
Class Definition	(private)
*****************************/

/**
 *  @Name        : InitTree()
 *  @Description : ��ʼ����,����ͷ�ڵ�
 *  @Parameters  : None
 *  @Return value: None
 */
template <typename Key, typename C, typename A>
inline void Tree<Key, C, A>::_InitTree()
{
	nodeAllocator n_Allocator;
	keyAllocator k_Allovator;
	m_Head = n_Allocator.allocate(1);
	k_Allovator.construct((Key*)m_Head, Key());
	m_Head->m_Parent = nullptr;
	m_Head->m_Left = nullptr;
	m_Head->m_Right = nullptr;
	m_Size = 0;
}

//����������
template <typename Key, typename C, typename A>
inline std::pair<TreeIterator<Key>, bool> Tree<Key, C, A>::_Insert(const keyType& key)
{
	nodePointer node = m_Head->m_Parent;
	nodePointer pre = m_Head;
	for (; node && node->m_Key != key;) {	//Ѱ�Ҳ���㣬����ͬ���˳�ѭ��
		pre = node;
		if (m_keyCompate(key, node->m_Key)) {
			node = node->m_Left;
		}
		else {
			node = node->m_Right;
		}
	}
	if (node) {
		iterator it(node);
		return { it, false };	//������ֹ����Ľڵ�ĵ�����
	}
	else {
		nodeAllocator n_Allocator;
		nodePointer ret = n_Allocator.allocate(1);
		keyAllocator k_Allocator;
		k_Allocator.construct((Key*)ret, key);
		ret->m_Left = nullptr;
		ret->m_Right = nullptr;
		ret->m_Parent = pre;
		if (IsEmpty()) {
			pre->m_Parent = ret;
			pre->m_Left = ret;
			pre->m_Right = ret;
		}
		else {
			if (m_keyCompate(key, pre->m_Key)) {	//����������
				ret->m_Left = pre->m_Left;
				pre->m_Left = ret;
			}
			else {	//����������
				ret->m_Right = pre->m_Right;
				pre->m_Right = ret;
			}
			if (m_keyCompate(key, m_Head->m_Left->m_Key)) {
				m_Head->m_Left = ret;
			}
			else if (m_keyCompate(m_Head->m_Right->m_Key, key)) {
				m_Head->m_Right = ret;
			}
		}
		++m_Size;
		iterator it(ret);
		return { it, true };	//���ز���Ľڵ�
	}
}

//ɾ��������
template <typename Key, typename C, typename A>
inline std::pair<TreeIterator<Key>, bool> Tree<Key, C, A>::_Erase(const Key& key)
{
	nodePointer node = Find(key).m_Pointer;
	if (!node) {
		iterator it(node);
		return { it,false };
	}
	nodePointer const transform = FindPosterior(node);
	if (node == m_Head->m_Left) {
		m_Head->m_Left = transform;
	}
	nodeAllocator n_Allocator;
	keyAllocator k_Allocator;
	if (node->m_Parent->m_Parent == node) {	//Ϊ���ڵ�
		if (!node->m_Left && !node->m_Right) {	//����Ϊ��
			m_Head->m_Left = nullptr;
			m_Head->m_Parent = nullptr;
			m_Head->m_Right = nullptr;
		}
		else {	//��һ��Ϊ��
			if (node->m_Left) {
				m_Head->m_Parent = node->m_Left;
				node->m_Left->m_Parent = m_Head;
			}
			else {
				m_Head->m_Parent = node->m_Right;
				node->m_Right->m_Parent = m_Head;
			}
		}
	}
	else {
		if (!node->m_Left && !node->m_Right) {	//����Ϊ��
			if (node->m_Parent->m_Left == node) {
				node->m_Parent->m_Left = nullptr;
			}
			else {
				node->m_Parent->m_Right = nullptr;
			}
		}
		else if (node->m_Left && node->m_Right) {	//����Ϊ��
			nodePointer trans = transform;	//Ѱ�����λ
			nodePointer tmp = trans;
			node->m_Key = trans->m_Key;	//�ú�λ����
			trans = node;
			node = tmp;	//����
		}
		else {	//��һ��Ϊ��
			if (node->m_Parent->m_Left == node) {	//nodeΪ������
				if (node->m_Left) {
					node->m_Parent->m_Left = node->m_Left;
					node->m_Left->m_Parent = node->m_Parent;
				}
				else {
					node->m_Parent->m_Left = node->m_Right;
					node->m_Right->m_Parent = node->m_Parent;
				}
			}
			else {	//nodeΪ������
				if (node->m_Left) {
					node->m_Parent->m_Right = node->m_Left;
					node->m_Left->m_Parent = node->m_Parent;
				}
				else {
					node->m_Parent->m_Right = node->m_Right;
					node->m_Right->m_Parent = node->m_Parent;
				}
			}
		}
	}
	k_Allocator.destroy((Key*)node);	//�ȵ�������
	n_Allocator.deallocate(node, 1);	//���ͷ��ڴ�
	node = nullptr;
	m_Size--;
	iterator it(transform);
	return { it,true };
}

/*****************************
Auxiliary Function
*****************************/

/**
 *  @Name        : FindPosterior(TreeNode* node)
 *  @Description : Ѱ��ĳ���ڵ�ĺ�λ�ڵ�,����ͷ�ڵ�ʹ�û����δ������Ϊ
 *  @Parameters  : TreeNode* nodeҪѰ�ҵĽڵ�
 *  @Return value: ��λ�ڵ�
 */
template <typename T>
TreeNode<T>* FindPosterior(TreeNode<T>* node)
{
	if (node->m_Right){	//������������
		for (node = node->m_Right; node->m_Left; node = node->m_Left);	//Ѱ����������С��ֵ
	}
	else {	//��������������
		TreeNode<T>* tmp = node->m_Parent;
		//����ǰ�ڵ�����ʱ�ڵ���������������������ֱ��nodeΪ��ԭʼֵΪ�������ֵΪֹ
		for (; node == tmp->m_Right; node = tmp, tmp = tmp->m_Parent);
		//��Ҫ����ֻ�и��ڵ���������ֻ�и��ڵ㣬node��������ͷ�ڵ㴦��tmpΪ���ڵ㣻����֮
		if (node->m_Right != tmp) {	//��node����ͷ�ڵ�
			node = tmp;	//��Ϊͷ�ڵ�
		}
	}

	return node;
}

/**
 *  @Name        : FindFront(TreeNode* node)
 *  @Description : Ѱ��ĳ���ڵ��ǰλ�ڵ㣬������С�Ľڵ�ʹ�û����δ������Ϊ
 *  @Parameters  : TreeNode* nodeҪѰ�ҵĽڵ�
 *  @Return value: ǰλ�ڵ�
 */
template <typename T>
TreeNode<T>* FindFront(TreeNode<T>* node)
{
	if (node->m_Left) {	//������������
		for (node = node->m_Left; node->m_Right; node = node->m_Right);	//Ѱ������������ֵ
	}
	else {	//��������������
		TreeNode<T>* tmp = node->m_Parent;
		//����ǰ�ڵ�����ʱ�ڵ���������������������ֱ��nodeΪ��ԭʼֵΪ������СֵΪֹ
		for (; node == tmp->m_Left; node = tmp, tmp = tmp->m_Parent);
		node = tmp;
	}
	return node;
}






}


#endif // !__BINARY_SORT_TREE__HPP__
