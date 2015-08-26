/*****************************************************************/
/* 设计模式————抽象工厂模式
/* 作者：李凝瑞	
/* 时间：2015.06.12
/*****************************************************************/


/**	抽象工厂模式：提供一个创建一系列相关或相互依赖对象的接口，而无须指定
 *	它们具体的类。抽象工厂模式又称 KIT 模式，是一种对象创建型模式。
 *	产品族：包含一系列的不同类别的产品，坐标轴上的纵轴。
 *			一个产品族对应一个具体工厂类
 *	产品等级：包含一系列的产品等级，坐标轴上的横轴。
 *			一个产品等级对应一个产品类
 *	思考：该模式是否符合开闭原则，从产品族和产品等级两方面考虑
 */
#pragma once
#include "stdafx.h"

namespace dp_abstractfactory {
	// 抽象产品类
	class AbstractProduct {
	public:
		// 抽象产品应有的业务方法
	};

	// 具体产品A类
	class ProductA : public AbstractProduct {
	public:
	};

	// 具体产品B类
	class ProductB : public AbstractProduct {
	public:
	};
	

	// 抽象工厂
	class AbstractFactory {
	public:
		// 含有虚函数应该有虚析构函数
		virtual ~AbstractFactory() {}
		// 工厂能生产产品A
		virtual ProductA * CreateProductA() = 0;
		// 工厂能生产产品B
		virtual ProductB * CreateProductB() = 0;
	};

	// 工厂1
	class Factory1 : public AbstractFactory {
	public:
		// 工厂能生产产品A
		virtual ProductA * CreateProductA() {
			return new ProductA();
		}
		// 工厂能生产产品B
		virtual ProductB * CreateProductB() {
			return new ProductB();
		}
	};

	// 工厂2
	class Factory2 : public AbstractFactory {
	public:
		// 工厂能生产产品A
		virtual ProductA * CreateProductA() {
			return new ProductA();
		}
		// 工厂能生产产品B
		virtual ProductB * CreateProductB() {
			return new ProductB();
		}
	};
};


namespace linary_abstractfactory {
	// 数码产品：抽象产品
	class DigitalProduct {
	public:
		DigitalProduct(const std::string & band) : band(band) {}
		virtual ~DigitalProduct() {}

		// 打印出产品信息
		virtual void ShowInfo() = 0;
	protected:
		// 电子产品的品牌名
		std::string band;
	};

	// 手机：具体产品A
	class Phone : public DigitalProduct {
	public:
		Phone(const std::string & band) : DigitalProduct(band) {}

		virtual void ShowInfo() {
			std::cout << "手机品牌：" << band << std::endl;
		}
	};

	// 播放器：具体产品B
	class Player : public DigitalProduct {
	public:
		Player(const std::string & band) : DigitalProduct(band) {}

		virtual void ShowInfo() {
			std::cout << "播放器品牌：" << band << std::endl;
		}
	};

	// 数码公司：抽象工厂
	class DigitalCompany {
	public:
		virtual ~DigitalCompany() {}
		// 发布手机
		virtual Phone * CreatePhone() = 0;
		// 发布播放器
		virtual Player * CreatePlayer() = 0;
	};

	// 苹果公司
	class Apple : public DigitalCompany {
	public:
		virtual Phone * CreatePhone() {
			return new Phone("IPhone 6 Plus");
		}

		virtual Player * CreatePlayer() {
			return new Player("IPod Shuffle");
		}
	};

	// 三星公司
	class Samsung : public DigitalCompany {
	public:
		virtual Phone * CreatePhone() {
			return new Phone("Note 4");
		}

		virtual Player * CreatePlayer() {
			return new Player("Altius");
		}
	};


	// 测试代码
	static void Test_AbstractFactory() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--   抽象工厂模式测试   --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		// 创建一个公司
		DigitalCompany * company = new Apple();
		// 公司发布一款手机
		Phone * phone =  company->CreatePhone();
		phone->ShowInfo();
		// 公司发布一款播放器
		Player * player = company->CreatePlayer(); 
		player->ShowInfo();

		delete player;
		delete phone;
		delete company;

		std::cout << std::endl;
	}
};