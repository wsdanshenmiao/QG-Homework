#include <new>
#include <assert.h>

/***************************************************************************************
 *    File Name                :   allocator.hpp
 *    CopyRight                :
 *
 *    SYSTEM                   :   Windows
 *    Create Data              :   2024.3.23
 *    Author/Corportation      :   LiWenHao
 *
 *
 *--------------------------------Revision History--------------------------------------
 *
 *
 *
 ***************************************************************************************/

/**************************************************************
 *    Multi-Include-Prevent Section
 **************************************************************/

#ifndef __ALLOCATOR__HPP__
#define __ALLOCATOR__HPP__

namespace QGHW{

/**************************************************************
 *    Struct Define Section
 **************************************************************/


template <typename T>
class allocator
{
public:
	//ָ������
	using valueType = T;
	using pointer = T*;
	using constPointer = const T*;
	using reference = T&;
	using constReference = const T&;
	using sizeType = size_t;

	//���캯��
	allocator();
	allocator(const allocator&) = default;

	inline ~allocator() = default;

	inline T* allocate(const size_t& count);
	inline void deallocate(pointer const ptr, const size_t& count);
	inline void construct(pointer ptr, constReference value);
	inline void construct(pointer ptr, valueType&& value);
	inline void destroy(pointer ptr);
};


/**************************************************************
 *    Prototype Declare Section
 **************************************************************/

 /**
  *  @Name        : inline bool operator==(const allocator<T1>&, const allocator<T2>&)
  *  @Description : �Ƚ�����Ĭ�Ϸ�����
  *  @Parameters  : Ĭ�Ϸ�����
  *  @Return value: true
  *  @Notice      : ����Ĭ�Ϸ�����������ȵ�
  */
template <class T1, class T2>
inline bool operator==(const allocator<T1>&, const allocator<T2>&)
{
	return true;
}


/**
 *  @Name        : inline bool operator!=(const allocator<T1>&, const allocator<T2>&)
 *  @Description : �Ƚ�����Ĭ�Ϸ�����
 *  @Parameters  : Ĭ�Ϸ�����
 *  @Return value: false
 *  @Notice      : ����Ĭ�Ϸ�����������ȵ�
 */
template <class T1, class T2>
inline bool operator!=(const allocator<T1>&, const allocator<T2>&)
{
	return false;
}


/**
 *  @Name        : allocator<T>::allocator()
 *  @Description : Ĭ�Ϲ���
 *  @Parameters  : None
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T>
allocator<T>::allocator() {}


/**
 *  @Name        : inline T* allocator<T>::allocate(const size_t& count)
 *  @Description : ʹ��ȫ��new�����ڴ�
 *  @Parameters  : const size_t count
 *  @Return value: ����ָ�����ɹ����ڴ��ָ��
 *  @Notice      : None
 */
template <typename T>
inline T* allocator<T>::allocate(const size_t& count)
{
	if (count > static_cast<size_t>(-1) / sizeof(T)) {
		throw std::bad_array_new_length();
	}
	T* ptr = static_cast<T*>(::operator new(count * sizeof(T)));
	if (!ptr) {
		throw std::bad_alloc();
	}
	return ptr;
}


/**
 *  @Name        : inline void allocator<T>::deallocate(T* const ptr, const size_t& count)
 *  @Description : ʹ��ȫ��delete�ͷ��ڴ�
 *  @Parameters  : ptrָ���ڴ��ָ�룬count�ͷŵĸ���
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T>
inline void allocator<T>::deallocate(pointer const ptr, const size_t& count)
{
	assert(ptr);
	::operator delete(ptr, count * sizeof(T));
}


/**
 *  @Name        : inline void allocator<T>::construct(pointer ptr, const_reference value)
 *  @Description : ��ָ����ַ�����й���
 *  @Parameters  : ptrָ���ڴ��ָ�룬value����ʹ�õ�ֵ
 *  @Return value: None
 *  @Notice      : placement new����֪��ַ��ɹ���
 */
template <typename T>
inline void allocator<T>::construct(pointer ptr, constReference value)
{
	new (static_cast<void*>(ptr)) T(value);
}


/**
 *  @Name        : inline void allocator<T>::construct(pointer ptr, const_reference value)
 *  @Description : ��ָ����ַ�����й���
 *  @Parameters  : ptrָ���ڴ��ָ�룬value����ʹ�õ�ֵ
 *  @Return value: None
 *  @Notice      : placement new����֪��ַ��ɹ���
 */
template <typename T>
inline void allocator<T>::construct(pointer ptr, valueType&& value)
{
	new (static_cast<void*>(ptr)) T(std::move(value));	//ʹ����ֵ����Ԫ��
}


/**
 *  @Name        : inline void allocator<T>::construct(pointer ptr, const_reference value)
 *  @Description : ��ָ����ַ�����й���
 *  @Parameters  : ptrָ���ڴ��ָ�룬value����ʹ�õ�ֵ
 *  @Return value: None
 *  @Notice      : placement new����֪��ַ��ɹ���
 */
template <typename T>
inline void allocator<T>::destroy(pointer ptr)
{
	ptr->~T();
}


}

#endif 
