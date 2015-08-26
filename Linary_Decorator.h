
/*****************************************************************/
/* 设计模式————装饰模式
/* 作者：李凝瑞	
/* 时间：2015.04.01
/*****************************************************************/

#pragma once

namespace linary_decorator {
	// 抽象电话类，类比于抽象组件类
	class Phone {
	public:
		// 开启应用的方法
		virtual void Run() = 0; 
	};

	// 具体电话类
	class IPhone : public Phone {
	public:
		virtual void Run() {
			std::cout << "欢迎使用IPhone" << std::endl;
		}
	};

	// 抽象应用类，类比于抽象装饰者类
	class App : public Phone {
	public:
		// 表示把App安装在手机上
		void InstallOn(Phone * phone) {
			this->phone = phone;
		}
		virtual void Run() {
			if (phone != NULL) {
				phone->Run();
			}
		}
	protected:
		Phone * phone;
	};

	// 具体应用类
	class Douban : public App {
	public:
		virtual void Run() {
			App::Run();
			SearchMovie();
		}
	private:
		void SearchMovie() {
			std::cout << "您可以使用豆瓣搜索电影" << std::endl;
		}
	};

	// 具体应用类
	class Wechat : public App {
	public:
		virtual void Run() {
			App::Run();
			Chat();
		}
	private:
		void Chat() {
			std::cout << "您可以使用微信聊天" << std::endl;
		}
	};
	
	// 测试代码
	static void Test_Decorator() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--     装饰模式测试     --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		IPhone * iphone = new IPhone();
		Douban * douban = new Douban();
		Wechat * wechat = new Wechat();

		douban->InstallOn(iphone);
		wechat->InstallOn(douban);
		wechat->Run();

		delete wechat;
		delete douban;
		delete iphone;

		std::cout << std::endl;
	}
}