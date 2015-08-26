/*****************************************************************/
/* 设计模式————状态模式
/* 作者：李凝瑞	
/* 时间：2015.06.07
/*****************************************************************/


/**	状态模式：
 */
#pragma once
#include "stdafx.h"

namespace dp_state {
	// 抽象状态类
	class State {
	public:
		virtual void Handle() = 0;
	};

	// 具体状态类
	class ConcreteState : public State {
	public:
		virtual void Hanlde() {
			// 方法具体实现代码
		}
	};

	// 环境类，是拥有多种状态的对象
	class Context {
	public:
		// 状态设置
		void SetState(State * state) {
			this->state = state;
		}

		// 事务处理
		void Request() {
			// 调用状态对象的业务方法
			state->Handle();
		}
	private:
		State * state;
	};
};

namespace linary_state {
	// 抽象状态类
	class State {
	public:
		State(int times) : times(times) {}
		int GetTimes() const {
			return times;
		}

		virtual void Display() = 0;
	protected:
		// 屏幕放大倍数
		int times;
	};

	// 正常状态类
	class NormalState : public State {
	public:
		NormalState() : State(1) {}
		virtual void Display() {
			std::cout << "正常大小" <<std::endl;
		}
	};

	// 2倍状态类
	class LargerState : public State {
	public:
		LargerState() : State(2) {}
		virtual void Display() {
			std::cout << "2 倍大小" <<std::endl;
		}
	};

	// 4倍状态类
	class LargestState : public State {
	public:
		LargestState() : State(4) {}
		virtual void Display() {
			std::cout << "4 倍大小" <<std::endl;
		}
	};

	// 屏幕：环境类
	class Screen {
	public:
		Screen() {
			// 创建正常状态对象
			state = new NormalState();
			state->Display();
		}
		~Screen() {
			delete state;
		}
		void SetState(State * state) {
			this->state = state;
		}
		// 单击事件处理方法，封装了对状态类中业务方法的调用和状态的转换
		void OnClick() {
			State * temp = state;
			if (state->GetTimes() == 1) {
				SetState(new LargerState());
			} else if (state->GetTimes() == 2) {
				SetState(new LargestState());
			} else {
				SetState(new NormalState());
			}
			delete temp;
			this->state->Display();
		}
	private:
		// 持有的状态类
		State * state;
	};


	// 测试代码
	static void Test_State() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--     状态模式测试     --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		Screen screen;
		screen.OnClick();
		screen.OnClick();
		screen.OnClick();

		std::cout << std::endl;
	}
};