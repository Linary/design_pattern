
/*****************************************************************/
/* 设计模式————观察者模式
/* 作者：李凝瑞	
/* 时间：2015.04.01
/*****************************************************************/

#pragma once

namespace linary_observer {
	typedef enum {On, Flight, Off} State;
	// 抽象App类（Observer）
	class App {
	public:
		virtual void Update(State state) = 0;
	};

	// 抽象电话类（Subject）
	class Phone {
	public:
		// 安装应用
		void Install(App * app) {
			apps.push_back(app);
		}
		// 卸载应用
		void Uninstall(App * app) {
			auto iter = std::find(apps.begin(), apps.end(), app);
			if (iter != apps.end()) {
				apps.erase(iter);
			}
		}
		// 给所有的App发送消息
		void Notify() {
			auto iter = apps.begin();
			for(; iter != apps.end(); ++iter) {
				(*iter)->Update(state);
			}
		}
		// 切换手机状态
		void SwitchState(State state) {
			this->state = state;
		}
		State GetState() const {
			return state;
		}
	protected:
		State state;
	private:
		typedef std::vector<App *> Apps;
		Apps apps;
	};

	// 具体电话类（ConcreteSubject）
	class IPhone : public Phone {
	public:
		
	};

	// 具体时钟App类
	class Clock : public App {
	public:
		virtual void Update(State state) {
			switch (state) {
			case On : 
				std::cout << "电话处于开机状态，";
				break;
			case Flight :
				std::cout << "电话处于飞行模式，";
				break;
			case Off :
				std::cout << "电话处于关机状态，";
				break;
			}
			std::cout << "时钟可用" << std::endl;
		}
	};

	// 具体天气App类
	class Weather : public App {
	public:
		virtual void Update(State state) {
			switch (state) {
			case On : 
				std::cout << "电话处于开机状态，天气可用" << std::endl;
				break;
			case Flight :
				std::cout << "电话处于飞行模式，天气可用" << std::endl;
				break;
			case Off :
				std::cout << "电话处于关机状态，天气不可用" << std::endl;
				break;
			}
		}
	};	

	// 具体拨号器App类
	class Dialer : public App {
	public:
		virtual void Update(State state) {
			switch (state) {
			case On : 
				std::cout << "电话处于开机状态，可以通话" << std::endl;
				break;
			case Flight :
				std::cout << "电话处于飞行模式，不能通话" << std::endl;
				break;
			case Off :
				std::cout << "电话处于关机状态，不能通话" << std::endl;
				break;
			}
		}
	};


	// 测试代码
	static void Test_Observer() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--    观察者模式测试    --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		IPhone  * iphone  = new IPhone();
		Weather * weather = new Weather();
		Clock	* clock	  = new Clock();
		Dialer	* dialer  = new Dialer();

		iphone->Install(weather);
		iphone->Install(clock);
		iphone->Install(dialer);
		// 开机
		iphone->SwitchState(On);
		iphone->Notify();
		// 切换到飞行模式
		iphone->SwitchState(Flight);
		iphone->Notify();
		// 关机
		iphone->SwitchState(Off);
		iphone->Notify();

		delete dialer;
		delete clock;
		delete weather;
		delete iphone;

		std::cout << std::endl;
	}
}