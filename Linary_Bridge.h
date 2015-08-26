/*****************************************************************/
/* 设计模式————桥梁模式
/* 作者：李凝瑞	
/* 时间：2015.05.26
/*****************************************************************/


/**	桥梁模式：将抽象和实现解耦，使得两者可以独立变化
 *	一个实现系统能从多个角度去分类，每种分类都可能变化，
 *	那就把这种多角度分离出来让他们独立变化
 */
#pragma once

namespace linary_bridge {
	/**
	 *	苹果手机硬件配置不高，但操作系统好；三星手机硬件配置高，但操作系统懒
	 *	这里面有三个变化量：手机品牌，硬件，操作系统
	 */

	class Hardware {
	public:
		// 硬件配置要被手机搭载
		virtual void BeCarried() = 0; 
	};


	class OperSystem {
	public:
		// 操作系统必须能运行
		virtual void Run() = 0;
	};

	// 抽象
	class PhoneBrand {
	public:
		//PhoneBrand() {}
		PhoneBrand(Hardware * hardware, OperSystem * operSystem) {
			this->hardware = hardware;
			this->operSystem = operSystem;
		}
		// 自身的行为
		void Use() {
			hardware->BeCarried();
			operSystem->Run();
		}
	private:
		Hardware * hardware; 
		OperSystem * operSystem;
	};

	// 一般的硬件配置
	class CommonHardware : public Hardware {
	public:
		void BeCarried() {
			std::cout << "1G RAM，Apple A7 CPU" << std::endl;
		}
	};

	// 高端的硬件配置
	class AdvancedHardware : public Hardware {
	public:
		void BeCarried() {
			std::cout << "4G RAM，高通 X7500 CPU" << std::endl;
		}
	};

	// IOS操作系统
	class IOS : public OperSystem {
	public:
		void Run() {
			std::cout << "运行流畅，无卡顿" << std::endl;
		}
	};

	// Android操作系统
	class Android : public OperSystem {
		void Run() {
			std::cout << "运行经常卡顿" << std::endl;
		}
	};

	// 苹果手机
	class IPhone : public PhoneBrand {
	public:
		// 传入特定类型的参数，调用父类构造方法
		IPhone(CommonHardware * hardware, IOS * operSystem) : PhoneBrand(hardware, operSystem){}

		void Use() {
			// 修正父类的使用行为
			PhoneBrand::Use();
			std::cout << "苹果用户很开心" << std::endl;
		}
	};

	// 三星手机
	class Note4 : public PhoneBrand {
	public:
		// 传入特定类型的参数，调用父类构造方法
		Note4(AdvancedHardware * hardware, Android * operSystem) : PhoneBrand(hardware, operSystem) {}
			
		void Use() {
			// 修正父类的使用行为
			PhoneBrand::Use();
			std::cout << "安卓用户很愤怒" << std::endl;
		}
	};


	// 测试代码
	static void Test_Bridge() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--     桥接模式测试     --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		// 定义实现化角色
		CommonHardware * commonHardware = new CommonHardware();
		AdvancedHardware * advancedHardware = new AdvancedHardware();

		IOS * ios = new IOS();
		Android * android = new Android();

		// 定义抽象化角色
		IPhone * iPhone = new IPhone(commonHardware, ios);
		Note4 * note4 = new Note4(advancedHardware, android);

		iPhone->Use();
		note4->Use();

		delete note4;
		delete iPhone;
		delete android;
		delete ios;
		delete advancedHardware;
		delete commonHardware;

		std::cout << std::endl;
	}
};