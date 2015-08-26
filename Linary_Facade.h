
/*****************************************************************/
/* 设计模式————外观模式
/* 作者：李凝瑞	
/* 时间：2015.04.03
/*****************************************************************/

#pragma once

namespace linary_facade {
	// 编译器
	class Compiler {
	public:
		void Compile() {
			std::cout << "1）编译源代码" << std::endl;
		}
	};

	// 链接器
	class Linker {
	public:
		void Link() {
			std::cout << "2）链接对象文件" << std::endl;
		}
	};

	// 控制台
	class Consoler {
	public:
		void Print() {
			std::cout << "3）打印输出" << std::endl;
		}
	};

	// 集成开发环境，包含编译器，链接器，执行器
	class IDE {
	public:
		// 集成开发环境的构造函数
		IDE() {
			compiler = new Compiler();
			linker   = new Linker();
			consoler = new Consoler();
		}
		// 集成开发环境的析构函数
		~IDE() {
			delete consoler;
			delete linker;
			delete compiler;
		}
		// 仅编译
		void Compile() {
			compiler->Compile();
		}
		// 生成解决方案（编译 + 链接）
		void GenerateSolution() {
			compiler->Compile();
			linker->Link();
		}
		// 运行（编译 + 链接 + 打印输出）
		void Run() {
			compiler->Compile();
			linker->Link();
			consoler->Print();
		}

	private:
		Compiler * compiler;
		Linker   * linker;
		Consoler * consoler;
	};

	// 测试代码
	static void Test_Facade() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--     外观模式测试     --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		IDE * VS2010 = new IDE();
		VS2010->Compile();
		VS2010->GenerateSolution();
		VS2010->Run();

		delete VS2010;

		std::cout << std::endl;
	}
}