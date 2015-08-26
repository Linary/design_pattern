/*****************************************************************/
/* 设计模式————职责链模式
/* 作者：李凝瑞	
/* 时间：2015.06.05
/*****************************************************************/


/**	职责链模式：
 */
#pragma once
#include "stdafx.h"

// 原名是（Chain of Responsibility）
namespace dp_dutychain {
	// 请求类，可以抽象化
	class Request {
	public:
	private:
	};

	// 抽象处理者类
	class Handler {
	public:
		// 设置后继者
		void SetSuccessor(Handler * successor) {
			this->successor = successor;
		}
		// 处理请求
		virtual void Handle(Request * request) = 0;
	protected:
		// 持有一个后继者
		Handler * successor;
	};

	// 具体处理者
	class ConcreteHandlerA : public Handler {
	public:
		virtual void Handle(Request * request) {
			// 如果A能处理request
				// 处理请求
			// 否则
				// 转发请求
		}
	};
};

namespace linary_dutychain {
	// 采购请求：请求类
	class PurchaseRequest {
	public:
		PurchaseRequest(int number, double amount, const std::string & purpose) 
			: number(number), amount(amount), purpose(purpose) {}
		// get
		int GetNumber() const {
			return number;
		}

		double GetAmount() const {
			return amount;
		}

		const std::string & GetPurpose() const {
			return purpose;
		}
	private:
		// 采购单编号
		int number;
		// 采购金额
		double amount;
		// 采购目的
		const std::string purpose;
	};

	// 审批者类：抽象处理者
	class Approver {
	public:
		// 构造函数
		Approver(const std::string & name) : name(name), successor(NULL) {}
		// 设置后继者
		void SetSuccessor(Approver * successor) {
			this->successor = successor;
		}
		// 审批采购单：处理请求
		virtual void Approve(PurchaseRequest * request) = 0; 
	protected:
		const std::string name; 
		Approver * successor;
	};

	// 经理类
	class Manager : public Approver {
	public:
		Manager(const std::string & name) : Approver(name) {}
		// 具体处理请求方法
		virtual void Approve(PurchaseRequest * request) {
			if (request->GetAmount() < 100000) {
				std::cout << "执行CEO：" << name << std::endl;
				std::cout << "审批项目：" << request->GetPurpose() << std::endl;
				std::cout << "项目金额：" << request->GetAmount() << "元" << std::endl;
			} else {
				// 转发请求
				successor->Approve(request);
			}
		}
	};

	// 董事类
	class President : public Approver {
	public:
		President(const std::string & name) : Approver(name) {}
		// 具体处理请求方法
		virtual void Approve(PurchaseRequest * request) {
			if (request->GetAmount() < 500000) {
				std::cout << "董	事主席：" << name << std::endl;
				std::cout << "审批项目：" << request->GetPurpose() << std::endl;
				std::cout << "项目金额：" << request->GetAmount() << "元" << std::endl;
			} else {
				// 转发请求
				successor->Approve(request);
			}
		}
	};

	// 董事会类
	class Congress : public Approver {
	public:
		Congress(const std::string & name) : Approver(name) {}
		// 具体处理请求方法
		virtual void Approve(PurchaseRequest * request) {
			// 最后一级，不用再转发
			std::cout << "董事会：" << name << std::endl;
			std::cout << "审批项目：" << request->GetPurpose() << std::endl;
			std::cout << "项目金额：" << request->GetAmount() << "元" << std::endl;
		}
	};


	// 测试代码
	static void Test_DutyChain() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--    责任链模式测试    --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		Approver * lzx = new Manager("陆兆禧");
		Approver * my = new President("马云");
		Approver * meeting = new Congress("股东大会");

		lzx->SetSuccessor(my);
		my->SetSuccessor(meeting);

		// 新建采购单
		PurchaseRequest * pr1 = new PurchaseRequest(10000, 99998.0, "入股滴滴打车");
		// 首先都是CEO来处理
		lzx->Approve(pr1);

		PurchaseRequest * pr2 = new PurchaseRequest(10002, 468000.0, "入股广州恒大");
		lzx->Approve(pr2);

		PurchaseRequest * pr3 = new PurchaseRequest(10003, 800000.0, "收回3000万股");
		lzx->Approve(pr3);

		delete pr3;
		delete pr2;
		delete pr1;
		delete meeting;
		delete my;
		delete lzx;

		std::cout << std::endl;
	}
};