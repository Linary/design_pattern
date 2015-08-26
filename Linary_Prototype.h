/*****************************************************************/
/* 设计模式————原型模式
/* 作者：李凝瑞	
/* 时间：2015.06.01
/*****************************************************************/


/**	原型模式：使用原型实例指定创建对象的种类，并且通过克隆这些原型创建新的对象
 */
#pragma once
#include "stdafx.h"

namespace linary_prototype {
	// 抽象原型类
	class Frame {
	public:
		// 构造函数
		Frame(const std::string & title) : title(title) {}
		// 拷贝构造函数，注意这里不是传指针，而是对象引用
		Frame(Frame & frame) {
			*this = frame;
		}

		virtual Frame * Clone() = 0;

		// 设置参数
		void SetTitle(const std::string & title) {
			this->title = title;
		}

		// 打印信息
		virtual void Print() {
			std::cout << "视图标题：" << title << std::endl;
		}
	protected:
		std::string title;
	};


	// Button也需要能被克隆
	class Button {
	public:
		Button(const std::string & label) : label(label) {}
		// 拷贝构造函数
		Button(Button & button) {
			*this = button;
		}
		// Set方法
		void SetLabel(const std::string & label) {
			this->label = label;
		}

		// 克隆函数
		Button * Clone() {
			return new Button(*this);
		}

		// 
		void Print() {
			std::cout << "按钮标签：" << this->label << std::endl;
		}
	private:
		std::string label;
	};


	// 借用我之前animation开发用到的模板框架思想
	class ContainerView : public Frame {
	public:
		ContainerView(const std::string & title, const std::string & label) : Frame(title) {
			button = new Button(label);
		}
		// 千万别忘记析构
		~ContainerView() {
			delete button;
		}
		// 实现clone方法
		virtual ContainerView * Clone() {
			ContainerView * containerView = new ContainerView(*this);
			Button * button = this->button->Clone();

			containerView->button = button;
			return containerView;
		}

		// 设置按钮标签
		void SetBtnLabel(const std::string & label) {
			button->SetLabel(label);
		}

		// 打印信息
		virtual void Print() {
			Frame::Print();
			button->Print();
		}
	protected:
		Button * button;
	};


	// 测试代码
	static void Test_Prototype() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--     原型模式测试     --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		ContainerView * studyContainer = new ContainerView("学习", "开始学习");
		ContainerView * examContainer = studyContainer->Clone();

		examContainer->SetTitle("考试");
		examContainer->SetBtnLabel("开始考试");
		studyContainer->Print();
		examContainer->Print();

		std::cout << (studyContainer == examContainer ? "true" : "false") << std::endl;

		delete examContainer;
		delete studyContainer;

		std::cout << std::endl;
	}
};