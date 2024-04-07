#ifndef __BINARY_SORT_TREE__HPP__
#define __BINARY_SORT_TREE__HPP__

#include "allocator.hpp"
#include "iostream"

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

private:
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
	inline sizeType& Size() const;
	inline iterator Begin() const;
	inline iterator End() const;


private:
	inline void _InitTree();
	inline std::pair<iterator, bool> _Insert(const keyType& key);

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
inline size_t& Tree<Key, C, A>::Size() const
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
	iterator it(m_Head->m_Left);
	return it;
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
	iterator it(m_Head);
	return it;
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
void Tree<Key, C, A>::_InitTree()
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
