#ifndef __MYALGORITHM__HPP__
#define __MYALGORITHM__HPP__

#include <vector>
#include <iostream>

namespace QGHW {


//������ӡ����
template <typename T>
inline void print(T* ptr, const size_t count)
{
	for (size_t i = 0; i < count; i++) {
		std::cout << *(ptr + i) << std::endl;
	}
	std::cout << "--------------------------------" << std::endl;
}




//Ĭ�ϱȽϺ���
template <typename T>
inline bool DefaultCmp(const T* v1, const T* v2)
{
	return *v1 > *v2;
}




//��������
template <typename T>
inline void InsertSort(T* const ptr, const size_t count, bool cmp(const T* v1, const T* v2) = DefaultCmp)
{
	if (!count || !ptr) {
		return;
	}
	for (size_t i = 1; i < count; i++) {	//�ӵڶ���Ԫ�ؿ�ʼ
		T value = *(ptr + i);	//��¼��i��Ԫ��
		long long j = i - 1;	//Ҫ����Ԫ�ص�ǰһ��Ԫ��
		for (; j >= 0 && cmp(ptr + j, &value);) {	//cmp����trueʱִ��
			//*(ptr + j + 1) = *(ptr + j);	//����j��Ԫ�ر�value�󣬵�j��Ԫ�غ���
			j--;	//����ǰ��
		}
		//ʹ��memmove��Ԫ���ڴ�ܴ�ʱ����������
		std::memmove(ptr + j + 2, ptr + j + 1, sizeof(T) * (i - j - 1));
		*(ptr + j + 1) = value;	//����Ԫ��
	}
}





//�鲢����ݹ麯��
template <typename T>
inline void SeparateAndMerge(T* const ptr, std::vector<T>& tmpData, size_t left, size_t right, bool cmp(const T*, const T*))
{
	//���뵽ֻʣһ����ݹ�ֹͣ
	if (left < right) {
		//�м�����
		size_t mid = (left + right) / 2;
		//������
		SeparateAndMerge(ptr, tmpData, left, mid, cmp);
		//�Ҳ����
		SeparateAndMerge(ptr, tmpData, mid + 1, right, cmp);
		//�����ϲ�
		size_t lpos = left, rpos = mid + 1;
		//�ϲ�ǰ����±�
		size_t pos = left;
		for (; lpos <= mid && rpos <= right;) {
			//������trueȡ�Ҳ࣬Ҳ�����������Ҳ�
			if (cmp(ptr + lpos, ptr + rpos)) {
				tmpData[pos++] = *(ptr + rpos++);
			}
			else {
				tmpData[pos++] = *(ptr + lpos++);
			}
		}
		//���ʣ��
		for (; lpos <= mid;) {
			tmpData[pos++] = *(ptr + lpos++);
		}
		//�Ҳ�ʣ��
		for (; rpos <= right;) {
			tmpData[pos++] = *(ptr + rpos++);
		}
		std::memmove(ptr + left, tmpData.data() + left, (right - left + 1) * sizeof(T));
		//ʹ��std::mommove�������һ��
		//std::copy(tmpData.data() + left, tmpData.data() + right + 1, ptr + left);
	}
}

//�鲢����
template <typename T>
inline void MergeSort(T* const ptr, const size_t count, bool cmp(const T*, const T*) = DefaultCmp)
{
	if (!count || !ptr) {
		return;
	}
	//��������ϲ�������
	std::vector<T> tmpData;
	tmpData.reserve(count);
	tmpData.resize(count, T(*ptr));
	//�ݹ����
	SeparateAndMerge(ptr, tmpData, 0, count - 1, cmp);
}




//��������
template <typename T>
inline void QuickSort(T* const ptr, const size_t count, bool cmp(const T*, const T*) = DefaultCmp)
{
	if (!count || !ptr) {
		return;
	}
	//ѡ����һ��Ԫ��Ϊ������
	T pivot = *ptr;
	//����ָ��
	T* left = ptr, * right = ptr + count - 1;
	if (left < right) {
		for (; left < right;) {
			//�Ե���Ϊ��������ָ��ָ���Ԫ�ر�����������ȣ���ָ�����
			while (left < right && cmp(right, &pivot) || *right == pivot) {
				--right;
			}
			//������ָ���Ԫ���Ƶ���ָ�봦
			*left = *right;
			//����ָ��ָ���Ԫ�ر�������С����ȣ���ָ��Ӽ�
			while (left < right && cmp(&pivot, left) || *left == pivot) {
				++left;
			}
			//������ָ���Ԫ���Ƶ���ָ�봦
			*right = *left;
		}
		//ȷ���������λ��
		*left = pivot;
		//���ݹ�
		QuickSort(ptr, left - ptr, cmp);
		//�Ҳ�ݹ�
		QuickSort(left + 1, count - (left + 1 - ptr), cmp);
	}
}




//��������,��ʱֻ��������,����������Ϊռλ��������ͳһ����
template <typename T>
inline void CountingSort(T* const ptr, const size_t count,bool (const T*, const T*) = DefaultCmp)
{
	if (!count || !ptr) {
		return;
	}
	//Ѱ�����ֵ
	size_t max = *ptr;
	for (size_t i = 0; i < count; i++) {
		if (*(ptr + i) > max) {
			max = *(ptr + i);
		}
	}
	//��������
	std::vector<size_t> countArray;
	countArray.reserve(max + 1);
	countArray.resize(max + 1, 0);
	for (size_t i = 0; i < count; countArray[*(ptr + i)]++, i++);
	//�ۼ����飬����ȶ��ԣ����Ҫ�������
	for (size_t i = 1; i < max + 1; countArray[i] += countArray[i - 1], i++);
	//��������
	std::vector<T> tmpData;
	tmpData.reserve(count);
	tmpData.resize(count, 0);
	for (size_t i = count; i > 0; i--) {
		//�ѵ�i��ԭʼ�������ۼ������е�ԭʼ�����ۼ�����һ���±괦
		tmpData[countArray[*(ptr + i - 1)]-- - 1] = *(ptr + i - 1);
	}
	std::memcpy(ptr, tmpData.data(), count * sizeof(T));
}




//��������,��ʱֻ��������,����LSD��������
template <typename T>
inline void RadixCountSort(T* const ptr, const size_t count, bool(const T*, const T*) = DefaultCmp)
{
	if (!count || !ptr) {
		return;
	}
	//Ѱ�����ֵ
	size_t max = *ptr;
	for (size_t i = 0; i < count; i++) {
		if (*(ptr + i) > max) {
			max = *(ptr + i);
		}
	}
	std::vector<T> tmpData;
	tmpData.reserve(count);
	tmpData.resize(count, 0);
	//�ֱ�ÿ��λ����
	for (size_t digit = 1; max / digit > 0; digit *= 10) {
		//ÿһλ�ļ�������
		std::vector<size_t> countArr;
		countArr.resize(10, 0);
		//*(ptr + i) / digitΪ��Ҫ�����λ������123/100=1����%10ΪҪ��������
		for (size_t i = 0; i < count; countArr[*(ptr + i) / digit % 10]++, i++);
		//�ۼ����飬��������
		for (size_t i = 1; i < 10; countArr[i] += countArr[i - 1], i++);
		//�ռ���λ����������
		for (size_t i = count; i > 0; i--) {
			//�ѵ�i��ԭʼ�������ۼ������е�ԭʼ�����ۼ�����һ���±괦
			tmpData[countArr[*(ptr + i - 1) / digit % 10]-- - 1] = *(ptr + i - 1);
		}
		std::memcpy(ptr, tmpData.data(), count * sizeof(T));
	}
}





}



#endif // !__MYALGORITHM__HPP__
