/*****************************************************************/
/* 设计模式————迭代器模式
/* 作者：李凝瑞	
/* 时间：2015.06.11
/*****************************************************************/


/**	迭代器模式：
 */
#pragma once
#include "stdafx.h"

// 我想利用C++的type_traits技术，实现类似于STL的迭代器

namespace linary_iterator {
	template <typename T>
	class Iterator;

	template <typename T>
	class VectorIterator;

	// 抽象集合类
	template <typename T = int>
	class Collection {
	public:
		virtual ~Collection() {}
		virtual Iterator<T> * GetIterator() = 0;
		// 添加，移除元素的操作
		virtual bool Add(const T & elem) = 0;
		// 移除这里很难写
		virtual void Remove(int idx) = 0;
	};

	// 具体集合类
	template <typename T>
	class Vector : public Collection<T> {
	public:
		Vector(int size) : cur(0), size(size) {
			ptr = new T[size];
		}
		~Vector() {
			delete []ptr;
		}

		virtual Iterator<T> * GetIterator() {
			return new VectorIterator<T>(*this);
		}

		// 添加元素
		virtual bool Add(const T & elem) {
			if (cur < size) {
				*(ptr + cur) = elem;
				++cur;
				return true;
			} else {
				return false;
			}
		}

		// 移除元素
		virtual void Remove(int idx) {
			if (0 <= idx && idx <= cur) {
				*(ptr + idx--) = T();
			}
		}

		// 返回集合大小
		int Size() const {
			return size;
		}
		// 返回集合现有元素个数
		int Count() const {
			return cur;
		}
		// 重载[]操作符
		T & operator[](int idx) {
			return *(ptr + idx);
		}
	private:
		T * ptr;
		int cur;
		int size;
	};

	// 抽象迭代器类
	template <typename T>
	class Iterator {
	public:
		virtual ~Iterator() {}
		// 遍历元素的操作
		virtual bool Begin() = 0;
		virtual bool End() = 0;
		virtual void Last() = 0;
		virtual void Next() = 0;
		virtual T & Item() = 0;
	};

	// 具体迭代器类
	template <typename T>
	class VectorIterator : public Iterator<T> {
	public:
		VectorIterator(Vector<T> & coll) : coll(coll), pivot(0) {}

		virtual bool Begin() {
			return pivot == 0;
		}
		virtual bool End() {
			return pivot == coll.Count();
		}
		virtual void Last() {
			if (pivot > 0) {
				--pivot;
			}
		}
		virtual void Next() {
			if (pivot < coll.Size()) {
				++pivot;
			}
		}
		virtual T & Item() {
			return coll[pivot];
		}
	private:
		// 持有一个具体的集合对象
		Vector<T> coll;
		// 持有一个游标（当作指针用）
		int pivot;
	};


	// 测试代码
	static void Test_Iterator() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--    迭代器模式测试    --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		Vector<std::string> books(5); 
		books.Add("神雕侠侣");
		books.Add("射雕英雄传");
		books.Add("笑傲江湖");

		Iterator<std::string> * it = books.GetIterator();
		std::cout << "-->正向遍历..." << std::endl;
		while (!it->End()) {
			std::cout << it->Item() << std::endl;
			it->Next();
		}
		std::cout<< "<--反向遍历..." << std::endl;
		while (!it->Begin()) {
			it->Last();
			std::cout << it->Item() << std::endl;
			
		}

		std::cout << std::endl;
	}
};