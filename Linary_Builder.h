
/*****************************************************************/
/* 设计模式————建造者模式
/* 作者：李凝瑞	
/* 时间：2015.04.01
/*****************************************************************/
#pragma once

namespace linary_builder {
	// 电话类，类比于产品类
	class Phone {
	public:
		// 展示配置
		void ShowConfig() {
			std::cout << "--  配置  --" << std::endl;
			std::copy(widgets.begin(), widgets.end(), 
				 std::ostream_iterator<std::string>(std::cout, "\n"));
		}
		// 组装
		void Assemble(const std::string & widget) {
			widgets.push_back(widget);
		}
	private:
		// 电话的部件
		std::vector<std::string> widgets;
	};

	// 抽象制造商，类比于抽象建造者
	class Manufacturer {
	public:
		// 开始组装Phone
		virtual void BeginAssemble() = 0;
		// 以下是装配（建造）步骤
		virtual void AssembleBoard() = 0;
		virtual void AssembleChip() = 0;
		virtual void AssembleScreen() = 0;
		// 返回产品
		virtual Phone * GetProduct() = 0;
	};

	// 具体制造商（富士康），类比于具体建造者A
	class Foxconn : public Manufacturer {
	public:
		virtual void BeginAssemble() {
			this->phone = new Phone();
		}

		virtual void AssembleBoard() {
			this->phone->Assemble("技嘉主板");
		}

		virtual void AssembleChip() {
			this->phone->Assemble("高通芯片");
		}

		virtual void AssembleScreen() {
			this->phone->Assemble("三星显示屏");
		}

		virtual Phone * GetProduct() {
			return this->phone;
		}
	private:
		Phone * phone;
	};

	// 具体制造商（华硕），类比于具体建造者B
	class Asus : public Manufacturer {
	public:
		virtual void BeginAssemble() {
			this->phone = new Phone();
		}

		virtual void AssembleBoard() {
			this->phone->Assemble("华硕主板");
		}

		virtual void AssembleChip() {
			this->phone->Assemble("联发科芯片");
		}

		virtual void AssembleScreen() {
			this->phone->Assemble("飞利浦显示屏");
		}

		virtual Phone * GetProduct() {
			return this->phone;
		}
	private:
		Phone * phone;
	};

	// 指挥者，只负责指挥建造，不负责交付产品
	class Director {
	public:
		void ChooseManufacturer(Manufacturer * manufacturer) {
			this->manufacturer = manufacturer;
		}
		void Construct() {
			manufacturer->BeginAssemble();
			manufacturer->AssembleBoard();
			manufacturer->AssembleChip();
			manufacturer->AssembleScreen();
		}
	private:
		Manufacturer * manufacturer;
	};

	static void Test_Builder() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--    建造者模式测试    --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		Director * director = new Director();
		Manufacturer * foxconn = new Foxconn();
		Manufacturer * asus = new Asus();

		director->ChooseManufacturer(foxconn);
		director->Construct();
		Phone * phone = foxconn->GetProduct();
		phone->ShowConfig();

		delete phone;
		delete asus;
		delete foxconn;
		delete director;

		std::cout << std::endl;
	}
}