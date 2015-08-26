/*****************************************************************/
/* 设计模式————工厂方法模式
/* 作者：李凝瑞	
/* 时间：2015.06.12
/*****************************************************************/


/**	工厂方法模式：定义一个用于创建对象的接口，让子类决定将哪一个类实例化。
 *	工厂方法让一个类的实例化延迟到子类，又称工厂模式、虚拟构造模式、多态
 *	工厂模式，是一种类创建型模式。
 *	思考：工厂方法能不能为静态方法？
 */
#pragma once
#include "stdafx.h"

namespace dp_factorymethod {
	// 抽象产品类
	class Product {

	};

	// 具体产品类
	class ConcreteProduct : public Product {

	};

	// 抽象工厂类
	class Factory {
	public:
		virtual ~Factory() {}
		// 工厂方法，声明但不实现
		virtual Product * FactoryMethod() = 0;
	};

	// 具体工厂类
	class ConcreteFactoy : public Factory {
	public:
		virtual Product * FactoryMethod() {
			return new ConcreteProduct();
		}
	};
};


namespace linary_factorymethod {
	// 数码产品：抽象产品
	class DigitalProduct {
	public:
		DigitalProduct(const std::string & name) : name(name) {}

		// 打印产品信息
		void ShowInfo() {
			std::cout << "产品类别为：" << name << std::endl;
		}
	protected:
		// 产品类别的名字
		std::string name;
	};

	// 手机类：具体产品
	class Phone : public DigitalProduct {
	public:
		Phone(const std::string & name) : DigitalProduct(name) {}
	};

	class Player : public DigitalProduct {
	public:
		Player(const std::string & name) : DigitalProduct(name) {}
	};

	// 数码公司：抽象工厂
	class DigitalCompany {
	public:
		virtual ~DigitalCompany() {}
		// 发布产品
		virtual DigitalProduct * CreateProduct() = 0;
	};

	// 手机制造公司
	class PhoneCompany : public DigitalCompany {
	public:
		virtual DigitalProduct * CreateProduct() {
			return new Phone("Phone");
		}
	};

	// 播放器制造公司
	class PlayerCompany : public DigitalCompany {
	public:
		virtual DigitalProduct * CreateProduct() {
			return new Player("Player");
		}
	};


	// 测试代码
	static void Test_FactoryMethod() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--   工厂方法模式测试   --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		// 创建一个手机制造商
		PhoneCompany * phoneCompany = new PhoneCompany(); 
		// 从工厂中获取一款手机
		DigitalProduct * phone = phoneCompany->CreateProduct();
		// 打印产品信息
		phone->ShowInfo();

		// 创建一个播放器制造商
		PlayerCompany * playerCompany = new PlayerCompany();
		// 从工厂中获取一款播放器
		DigitalProduct * player = playerCompany->CreateProduct();
		// 打印产品信息
		player->ShowInfo();

		delete player;
		delete playerCompany;
		delete phone;
		delete phoneCompany;

		std::cout << std::endl;
	}
};