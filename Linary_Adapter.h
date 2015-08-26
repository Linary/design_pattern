/*****************************************************************/
/* 设计模式————适配器模式
/* 作者：李凝瑞	
/* 时间：2015.06.04
/*****************************************************************/


/**	适配器模式：
 */
#pragma once
#include "stdafx.h"
namespace linary_adapter {
	// 算法库中的类
	// 二分查找类
	class BinarySearch {
	public:
		// 可以扩展成泛型的
		int Run(int * coll, int len, int key) {
			int low = 0;
			int high = len - 1;
			int mid = 0;
			while (low <= high) {
				mid = (low + high) / 2;
				if (coll[mid] < key) {
					low = mid + 1;
				} else if (coll[mid] > key) {
					high = mid - 1;
				} else {
					return mid;
				}
			}
			// 如果没找到
			return -1;
		}
	};

	// 快速排序类
	class QuickSort {
	public:
		// 执行算法的入口函数
		void Run(int * coll, int begin, int end) {
			// 如果左游标的位置大于等于右游标，则退出递归
			if (begin >= end) {
				return ;
			}

			// 定义两个游标
			int lp = begin;
			int rp = end;
			// 枢轴
			int key = coll[lp];

			while (lp < rp) {
				while ((coll[rp] >= key) && (lp < rp)) {
					rp--;
				}
				// 把比 key 小的数移到左边
				coll[lp] = coll[rp];
				while ((coll[lp] <= key) && (lp < rp)) {
					lp++;
				}
				// 把比 key 大的数移到右边
				coll[rp] = coll[lp];
			}
			// 左右游标已经碰头，把 key 放到合适的位置
			coll[lp] = key;
			// 对左子块做快速排序
			Run(coll, begin, lp - 1);
			// 对右子块做快速排序
			Run(coll, lp + 1, end);
		}
	};

	// 抽象成绩操作类：目标接口
	class ScoreOperation {
	public:
		virtual void ScoreSort(int * coll, int len) = 0;
		virtual int ScoreSearch(int * coll, int len, int key) = 0;
	};

	// 操作适配器：适配器
	class OperationAdapter : public ScoreOperation {
	public:
		OperationAdapter() {
			sortObj = new QuickSort();
			searchObj = new BinarySearch();
		}

		~OperationAdapter() {
			delete searchObj;
			delete sortObj;
		}

		void ScoreSort(int * coll, int len) {
			sortObj->Run(coll, 0, len - 1);
		};

		int ScoreSearch(int * coll, int len, int key) {
			return searchObj->Run(coll, len, key);
		}
	private:
		QuickSort * sortObj;
		BinarySearch * searchObj;
	};


	// 测试代码
	static void Test_Adapter() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--    适配器模式测试    --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		ScoreOperation * operation = new OperationAdapter();
		int scores[] = {84, 76, 50, 69, 90, 88};
		int score;
		std::cout << "原始成绩为：" << std::endl;
		std::copy(scores, scores + 6, std::ostream_iterator<int>(std::cout, "\t"));
		std::cout << std::endl;
		operation->ScoreSort(scores, 6);
		std::cout << "排序后成绩：" << std::endl;
		std::copy(scores, scores + 6, std::ostream_iterator<int>(std::cout, "\t"));
		std::cout << std::endl;
		std::cout << "查找成绩90：" << std::endl;
		score = operation->ScoreSearch(scores, 6, 90);
		std::cout << (score >= 0 ? "找到" : "未找到") << std::endl;
		delete operation;

		std::cout << std::endl;
	}
};