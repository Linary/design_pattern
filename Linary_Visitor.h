
/*****************************************************************/
/* 设计模式————访问者模式
/* 作者：李凝瑞	
/* 时间：2015.04.02
/*****************************************************************/
#pragma once

namespace linary_visitor {
	// 前置声明
	class Counter;
	class AppleCounter;
	class NokiaCounter;
	// 消费者——访问者
	class Consumer {
	public:
		virtual void VisitAppleCounter(AppleCounter * appleCounter) = 0;
		virtual void VisitNokiaCounter(NokiaCounter * nokiaCounter) = 0;
	};

	// 柜台——元素
	class Counter {
	public:
		// 接受消费者（访问者）的访问
		virtual void Accept(Consumer * consumer) = 0;
	};

	// 购买者——具体访问者1
	class Buyer : public Consumer {
		virtual void VisitAppleCounter(AppleCounter * appleCounter) {
			std::cout << "我想买一台iPhone 6 Plus" << std::endl;
			// 这里应该有一些加之于appleCounter的操作
			// 但是一会儿想不到怎么加
			std::cout << "苹果柜台人员：好的，6288元" << std::endl;
		}

		virtual void VisitNokiaCounter(NokiaCounter * nokiaCounter) {
			std::cout << "我想买一台Lumia 925" << std::endl;
			std::cout << "诺基亚柜台人员：好的，3288元" << std::endl;
		}
	};

	// 退货者——具体访问者2
	class Returner : public Consumer {
		virtual void VisitAppleCounter(AppleCounter * appleCounter) {
			std::cout << "我想退一台iPhone 6 Plus" << std::endl;
			std::cout << "苹果柜台人员：好的，这是6288" << std::endl;
		}

		virtual void VisitNokiaCounter(NokiaCounter * nokiaCounter) {
			std::cout << "我想退一台Lumia 925" << std::endl;
			std::cout << "诺基亚柜台人员：对不起，不支持无理由退货" << std::endl;
		}
	};

	// 保修者——具体访问者3
	class Repairer : public Consumer {
		virtual void VisitAppleCounter(AppleCounter * appleCounter) {
			std::cout << "我想修一台iPhone 6 Plus" << std::endl;
			std::cout << "苹果柜台人员：我们直接给你换一台" << std::endl;
		}

		virtual void VisitNokiaCounter(NokiaCounter * nokiaCounter) {
			std::cout << "我想修一台Lumia 925" << std::endl;
			std::cout << "诺基亚柜台人员：好的，这个要返厂检修" << std::endl;
		}
	};

	// 苹果柜台——具体元素1
	class AppleCounter : public Counter {
	public:
		virtual void Accept(Consumer * consumer) {
			consumer->VisitAppleCounter(this);
		}
	};
	// 诺基亚柜台——具体元素2
	class NokiaCounter : public Counter {
	public:
		virtual void Accept(Consumer * consumer) {
			consumer->VisitNokiaCounter(this);
		}
	};

	// 商店——对象集合
	class Store {
	public:
		// 增设新的柜台
		void Attach(Counter * counter) {
			counters.push_back(counter);
		}
		// 移除一个柜台
		void Detach(Counter * counter) {
			auto iter = std::find(counters.begin(), counters.end(), counter);
			if (iter != counters.end()) {
				if (*iter != NULL) {
					delete *iter;
				}
				// 不知道这里的删除会造成内存泄漏
				counters.erase(iter);
			}
		}
		// 移除所有柜台
		void DetachAll() {
			auto iter = counters.begin();
			for (; iter != counters.end(); ++iter) {
				if (*iter != NULL) {
					delete *iter;
				}
			}
		}
		// 提供一个供高层调用的让访问者访问的接口
		void Accept(Consumer * consumer) {
			// 这里算法 for_each 加仿函数不知道怎么配接
			// for_each(counters.begin(), counters.end(), Accept(consumer));
			auto iter = counters.begin();
			for (; iter != counters.end(); ++iter) {
				(*iter)->Accept(consumer);
			}
		}
	private:
		std::vector<Counter *> counters;
	};


	// 测试代码
	static void Test_Visitor() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--    访问者模式测试    --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		Store * store = new Store();
		store->Attach(new AppleCounter());
		store->Attach(new NokiaCounter());

		Buyer * buyer = new Buyer();
		Returner * returner = new Returner();
		Repairer * repairer = new Repairer();
		store->Accept(buyer);
		store->Accept(returner);
		store->Accept(repairer);

		store->DetachAll();
		delete repairer;
		delete returner;
		delete buyer;
		delete store;

		std::cout << std::endl;
	}
}