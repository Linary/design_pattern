/*****************************************************************/
/* 设计模式————单例模式
/* 作者：李凝瑞	
/* 时间：2015.05.29
/*****************************************************************/

#pragma once
#include "stdafx.h"
namespace linary_sigleton {

	// 应用类
	class App {
	public:
		virtual void Run() = 0;
	};

	// 微信类 
	class WeChat : public App {
	public:
		static WeChat * GetWeChatInstance() {
			if (m_instance == NULL) {
				m_instance = new WeChat();
			}
			return m_instance;
		}

		void Run() {
			std::cout << "微信正在运行..." << std::endl;
		}
	protected:
		WeChat() {}
	private:
		static WeChat * m_instance;
	};
	WeChat * WeChat::m_instance = NULL;


	// 知乎类
	class ZhiHu : public App {
	public:
		static ZhiHu * GetZhiHuInstance() {
			if (m_instance == NULL) {
				m_instance = new ZhiHu();
			}
			return m_instance;
		}

		void Run() {
			std::cout << "知乎正在运行..." << std::endl;
		}
	protected:
		ZhiHu() {}
	private:
		static ZhiHu * m_instance;
	};
	ZhiHu * ZhiHu::m_instance = NULL;


	// 持有几个静态对象
	class IPhone {
	public:
		IPhone() {
			std::cout << "IPhone已解锁" << std::endl;
		}

		// 简单工厂模式
		App * GetAppInstance(const std::string & app) {
			if (app == "wechat") {
				return WeChat::GetWeChatInstance();
			} else if (app == "zhihu") {
				return ZhiHu::GetZhiHuInstance();
			} else {
				return NULL;
			}
		}
	};


	// 测试代码
	static void Test_Singleton() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--     单例模式测试     --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		IPhone * iPhone = new IPhone();
		WeChat * wechat = WeChat::GetWeChatInstance();
		wechat->Run();
		ZhiHu  * zhihu  = ZhiHu::GetZhiHuInstance();
		zhihu->Run();

		delete zhihu;
		delete wechat;
		delete iPhone;
		std::cout << std::endl;
	}
};