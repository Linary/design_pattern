/*****************************************************************/
/* 设计模式————命令模式
/* 作者：李凝瑞	
/* 时间：2015.06.08
/*****************************************************************/


/**	命令模式：讲一个请求封装为一个对象，从而可用不同的请求对客户进行参数化；
 *	对请求排队或者记录日志，以及支持可撤销的操作，是一种对象行为型模式。
 */
#pragma once
#include "stdafx.h"

namespace dp_command {
	// 抽象命令类
	class Command {
	public:
		virtual void Execute() = 0;
	};

	// 请求者
	class Invoker {
	public:
		// 构造注入
		Invoker(Command * command) {
			this->command = command;
		}

		// 设置注入
		void SetInvoker(Command * command) {
			this->command = command;
		}

		// 调用方法
		void Call() {
			command->Execute();
		}
	private:
		Command * command;
	};

	// 接受者（一个具体命令类持有）
	class Receiver {
	public:
		void Action() {
			// 执行具体操作
		}
	};

	// 具体命令类
	class ConcreteCommand : public Command {
	public:
		virtual void Execute() { 
			// 调用接受者的业务处理方法
			receiver->Action();
		}
	private:
		// 持有一个接受者
		Receiver * receiver;
	};
};

namespace linary_command {
	// 3个具体接受者
	class Opener {
	public:
		void open() {
			std::cout << "打开一个文件" << std::endl;
		}
	};

	class Saver {
	public:
		void save() {
			std::cout << "保存一个文件" << std::endl;
		}
	};

	class Exiter {
	public:
		void exit() {
			std::cout << "关闭一个文件" << std::endl;
		}
	};

	// 抽象命令类
	class Command {
	public:
		Command(const std::string & function) : function(function) {} 
		virtual void Execute() = 0;
		const std::string & GetFunction() const {
			return function;
		}
	protected:
		std::string function;
	};

	// 打开命令
	class OpenCommand : public Command {
	public:
		// 构造函数
		OpenCommand() : Command("打开") {
			opener = new Opener();
		}
		// 析构
		~OpenCommand() {
			delete opener;
		}
		virtual void Execute() {
			opener->open();
		}
	private:
		Opener * opener;
	};

	// 保存命令
	class SaveCommand : public Command {
	public:
		// 构造函数
		SaveCommand() : Command("保存") {
			saver = new Saver();
		}
		// 析构
		~SaveCommand() {
			delete saver;
		}
		virtual void Execute() {
			saver->save();
		}
	private:
		Saver * saver;
	};

	// 退出命令
	class ExitCommand : public Command {
	public:
		// 构造函数
		ExitCommand() : Command("退出") {
			exiter = new Exiter();
		}
		// 析构
		~ExitCommand() {
			delete exiter;
		}
		virtual void Execute() {
			exiter->exit();
		}
	private:
		Exiter * exiter;
	};

	// 按钮类：请求发送者
	class Button {
	public:
		Button(const std::string & label) : label(label) {}

		// get/set方法
		const std::string & GetLabel() const {
			return label;
		}

		void SetLabel(const std::string & label) {
			this->label = label;
		}

		// 为功能键注入命令
		void SetCommand(Command * command) {
			this->command = command;
		}

		// 得到命令描述
		const std::string & GetFunction() const {
			return command->GetFunction();
		}

		// 发送请求
		void OnClick() {
			command->Execute();
		}
	private:
		// 按钮标签
		std::string label;
		// 维持一个命令对象
		Command * command;
	};

	// 窗口类：不承担任何角色，纯粹是业务环境的需要
	class Window {
	public:
		// 构造
		Window(const std::string & title) : title(title) {
			for (int i = 0; i < 3; i++) {
				std::stringstream ss;
				ss << "功能" << i + 1; 
				buttons[i] = new Button(ss.str());
			}
		}
		// 析构
		~Window() {
			for (int i = 2; i >= 0 ; --i) {
				delete buttons[i];
			}
		}

		// 给指定按钮设置功能键
		void SetBtnFunction(int idx, Command * command) {
			if (1 <= idx && idx <= 3) {
				buttons[idx - 1]->SetCommand(command);
			} else {
				std::cout << "无效按钮" << std::endl;
			}
			
		}

		// 点击窗口的按钮
		void ClickBtn(int idx) {
			std::cout << "点击按钮" << idx << "：";
			buttons[idx - 1]->OnClick();
		}

		// 显示
		void Display() {
			std::cout << "--------------------------" << std::endl;
			std::cout << "显示窗口：" << this->title << std::endl;
			std::cout << "功能键：" << std::endl;
			std::cout << "--------------------------" << std::endl;
			for (int i = 0; i < 3; i++) {
				std::cout << buttons[i]->GetLabel() << "：" << buttons[i]->GetFunction() << std::endl;
			}
			std::cout << "--------------------------" << std::endl;
		}
	private:
		// 窗口标题
		std::string title;
		// 按钮数组
		Button * buttons[3];
	};

	
	// 测试代码
	static void Test_Command() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--     命令模式测试     --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		Window * window = new Window("自定义功能键");
		Command * openCommand = new OpenCommand(); 
		Command * saveCommand = new SaveCommand();
		Command * exitCommand = new ExitCommand();
		// 自定义功能键
		window->SetBtnFunction(1, openCommand);
		window->SetBtnFunction(2, saveCommand);
		window->SetBtnFunction(3, exitCommand);
		// 显示
		window->Display();
		// 点击按钮
		window->ClickBtn(1);
		window->ClickBtn(2);
		window->ClickBtn(3);

		// 自定义功能键
		window->SetBtnFunction(1, saveCommand);
		window->SetBtnFunction(2, openCommand);
		window->SetBtnFunction(3, exitCommand);
		// 显示
		window->Display();
		window->ClickBtn(1);
		window->ClickBtn(2);
		window->ClickBtn(3);

		delete exitCommand;
		delete saveCommand;
		delete openCommand;
		delete window;

		std::cout << std::endl;
	}
};