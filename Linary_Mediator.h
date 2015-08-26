/*****************************************************************/
/* 设计模式————中介者模式
/* 作者：李凝瑞	
/* 时间：2015.05.30
/*****************************************************************/

#pragma once
#include "stdafx.h"

/**	中介者模式：用一个中介对象来封装一系列的对象交互。
 *	效果：使得各对象不需要显示地相互引用，从而使其耦合松散，并且可以独立地改变它们之间的交互。
 */

namespace dp_mediator {
	
	// 前置声明
	class Subject;

	// 抽象中介者
	class Mediator {
	public:
		// 这里的方法只是举个例子，表示中介者转发消息
		virtual void Transfer(const std::string & msg, Subject * subject) = 0;
	};

	// 抽象目标类
	// 其实这个类往往没有必要，因为具体的目标对象是完成不同的业务逻辑的
	class Subject {
	public:
		// 构造方法，得到中介者对象
		Subject(Mediator * mediator) {
			this->mediator = mediator;
		}

	protected:
		Mediator * mediator;
	};

	// 具体目标1
	class ConcreteSubject1 : public Subject {
	public:
		// 构造函数传入中介者
		ConcreteSubject1(Mediator * mediator) : Subject(mediator) {}

		// 注意：这两个方法虽然目标1和目标2（业务逻辑可能完全不一样）都有，
		// 但是实际中往往不是这样的，所以不要随意加在父类中
		void SendMsg(const std::string & msg) {
			std::cout << "目标1：" << msg << std::endl;
			mediator->Transfer(msg, this);
		}

		void RecvMsg(const std::string & msg) {
			std::cout << "目标1：收到消息" << std::endl;
		}
	};

	// 具体目标2，注意：其实目标2和目标1可以没有共性！
	class ConcreteSubject2 : public Subject {
	public:
		// 构造函数传入中介者
		ConcreteSubject2(Mediator * mediator) : Subject(mediator) {}

		void SendMsg(const std::string & msg) {
			std::cout << "目标2：" << msg << std::endl;
			mediator->Transfer(msg, this);
		}

		void RecvMsg(const std::string & msg) {
			std::cout << "目标2：收到消息" << std::endl;
		}
	};

	// 具体中介者
	class ConcreteMediator : public Mediator {
	public:
		// 这里不能用构造方法代替，否则外部没法初始化
		void SetConcreteSubject1(ConcreteSubject1 * subject1) {
			this->subject1 = subject1;
		}

		void SetConcreteSubject2(ConcreteSubject2 * subject2) {
			this->subject2 = subject2;
		}

		// 转发消息
		void Transfer(const std::string & msg, Subject * subject) {
			if (subject == subject1) {
				subject2->RecvMsg(msg);
			} else {
				subject1->RecvMsg(msg);
			}
		}

	private:
		ConcreteSubject1 * subject1;
		ConcreteSubject2 * subject2;
	};


	// 测试代码
	static void Test_Mediator() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--    中介者模式测试    --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		ConcreteMediator * mediator = new ConcreteMediator();
		// 创建两个用于通信的对象
		ConcreteSubject1 * subject1 = new ConcreteSubject1(mediator);
		ConcreteSubject2 * subject2 = new ConcreteSubject2(mediator);
		// 指定中介者需要调停的对象
		mediator->SetConcreteSubject1(subject1);
		mediator->SetConcreteSubject2(subject2);

		subject1->SendMsg("我想买一台IPhone 7");
		subject2->SendMsg("对不起，还没有上市");

		delete subject2;
		delete subject1;
		delete mediator;

		std::cout << std::endl;
	}
};


namespace linary_mediator {

	class User;

	// 抽象电商平台
	class OnlineStore {
	public:
		// 展示商品
		virtual void ShowGoods(User * user) = 0;
	};


	class User {
	protected:
		OnlineStore * store;
	};

	// 产品经销商
	class Vendor : public User {
	public:
		// 申请加盟
		void ApplyJoining(OnlineStore * store) {
			std::cout << "经销商：申请入住天猫商城" << std::endl;
			this->store = store;
		}

		// 陈列商品
		void PutGoods() {
			store->ShowGoods(this);
		};
	};

	// 顾客
	class Consumer : public User {
	public:
		// 逛商场
		void VisitStore(OnlineStore * store) {
			std::cout << "顾客：访问天猫" << std::endl;
			this->store = store;
		}

		// 选购商品
		void BuyGoods() {
			store->ShowGoods(this);
		}
	};

	

	// 具体商城
	class TMall : public OnlineStore {
	public:
		void AcceptJoining(Vendor * vendor) {
			std::cout << "天猫商城：允许入住" << std::endl;
			this->vendor = vendor;
		}

		void GreetConsumer(Consumer * consumer) {
			std::cout << "天猫商城：欢迎选购" << std::endl;
			this->consumer = consumer;
		}

		void ShowGoods(User * user) {
			if (user == vendor) {
				std::cout << "天猫商城展出经销商商品" << std::endl;
			} else {
				std::cout << "天猫商城供用户选购商品" << std::endl;
			}
		}
	private:
		Vendor * vendor;
		Consumer * consumer;
	};


	// 测试代码
	static void Test_Mediator() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--    中介者模式测试    --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		TMall * tmall = new TMall();
		// 经销商和顾客
		Vendor * vendor = new Vendor();
		Consumer * consumer = new Consumer();
		// 经销商申请入住天猫商城
		vendor->ApplyJoining(tmall);
		// 天猫商城允许入住
		tmall->AcceptJoining(vendor);
		// 展出商品
		vendor->PutGoods();
		// 顾客访问天猫
		consumer->VisitStore(tmall);
		// 天猫商城欢迎顾客
		tmall->GreetConsumer(consumer);
		consumer->BuyGoods();
		

		delete consumer;
		delete vendor;
		delete tmall;

		std::cout << std::endl;
	}
};