/*****************************************************************/
/* 设计模式————代理模式
/* 作者：李凝瑞	
/* 时间：2015.05.30
/*****************************************************************/

#pragma once
#include "stdafx.h"

/**	代理模式：为其他对象提供一种代理以控制对这个对象的访问
 *	优点：1）职责清晰；2）高扩展性；3）智能化（动态代理）
 *	分类扩展：
 *	1）普通代理：要求客户端只能访问代理角色，而不能访问真实角色；
 *	2）
 */

namespace dp_proxy {
	// 抽象主题类
	class Subject {
	public:
		// 定义一个方法
		virtual void Request() = 0;
	};

	// 真实主题类
	class RealSubject : public Subject {
	public:
		// 实现一个方法
		void Request() {}
	};
		
	// 代理类
	class Proxy : public Subject {
	public:
		// 通过构造函数传递被代理者
		Proxy(Subject * subject) {
			this->subject = subject;
		}

		// 实现方法
		void Request() {
			PreProcess();
			subject->Request();
			PostProcess();
		}
	protected:
		// 预处理
		void PreProcess() {
			// do something
		}
		// 后处理
		void PostProcess() {
			// do something
		}
	private:
		Subject * subject;
	};
};


namespace linary_proxy {
	// 抽象文件读取类
	class FileReader {
	public:
		FileReader() {}
		FileReader(const std::string & filePath) : infile(filePath) {
			// 如果文件路径有错，抛出异常
			/*if (!infile) {
				throw "can't find the file";
			}*/
		}

		// 这里可能要用到模板方法模式
		std::vector<float> GetDataByCol(const std::string & colName) {
			// 定义一个数据存储容器
			std::vector<float> dataColl(GetDataTotalLine(), float());
			// 文件指针移动到数据首行
			SeekToDataHeadLine();
			std::cout << infile.get() << "+++++" << std::endl;

			return dataColl;
		}
	protected:
		// 定位到属性行
		virtual void SeekToPropertyLine(){}
		// 定位到数据首行
		virtual void SeekToDataHeadLine(){}
		// 数据的总行数
		int GetDataTotalLine() {
			return 10;
		}

		// 移动到下一行相同位置
		int MoveToNextLine() {
			std::cout << "移动到下一行的相同位置" << std::endl;
		}

	protected:
		// 文件读取流
		std::ifstream infile;
	};

	// 具体文件读取类
	
	class AscFileReader : public FileReader {
	public:
		// 传给父类进行构造
		AscFileReader(const std::string & filePath) : FileReader(filePath) {}

		// 定位到属性行
		virtual void SeekToPropertyLine() {
			
			std::cout << "定位到属性行" << std::endl;
		}
		// 定位到数据首行
		virtual void SeekToDataHeadLine() {
			infile.seekg(8);

			std::cout << "定位到数据首行" << std::endl;
		}
	private:
	};

	// 代理类
	template <typename FileType>
	class FileReaderProxy : public FileReader {
	public:
		// 通过构造函数传递要对什么文件类型对象代理
		FileReaderProxy<FileType>(const std::string & filePath) {
			// 这里可以写一个文件格式提取方法
			// 不过尝试一下模板
			fileReader = new FileType(filePath);
		}
		// 析构函数
		~FileReaderProxy() {
			delete fileReader;
		}
	private:
		FileType * fileReader;
	};

	// 测试代码
	static void Test_Proxy() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--     代理模式测试     --" << std::endl;
		std::cout << "--------------------------" << std::endl;
		// 创建一个文件读取代理类，这好像暴露了一些细节
		FileReaderProxy<AscFileReader> proxy("../xxx.txt");
		proxy.GetDataByCol("Sum");
	
		std::cout << std::endl;
	}
};