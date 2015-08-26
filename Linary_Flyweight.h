/*****************************************************************/
/* 设计模式————享元模式
/* 作者：李凝瑞	
/* 时间：2015.05.27
/*****************************************************************/


/**	享元模式：
 */
#pragma once
#include "stdafx.h"
namespace linary_flyweight {
	// 数据库连接池的应用，每次连接的IP、Port、数据库都是一样的，可以作为内部状态
	// 而表不一样，可以作为享元的外部状态
	class Connection {
	public:
		// 享元必须接受外部状态
		Connection(const std::string & tablename) : hostport("127.0.0.1:5432"), database("postgres"), 
			tablename(tablename), visituser("未知") {}

		void SetVisitUser(const std::string & visituser) {
			this->visituser = visituser;
		}

		void PrintInfo() {
			std::cout << "主机&端口： " << hostport << std::endl;
			std::cout << "当前表   ： " << tablename << std::endl;
			std::cout << "访问用户 ： " << visituser << std::endl;
		}
	protected:
		// 这两个属性与该模式无关，但为了表现数据库连接，还是加上
		const std::string hostport;
		const std::string database;
		// 内部状态：内部状态不是说所有类中都一模一样的属性，而是指这些属性的取值组合数是固定的，是可以穷举的
		// 比如某个项目开发中，表的数目（对应对象）数目是可以穷举的
		const std::string tablename;
		// 外部状态：每个事件都有可能不一样的值，随环境改变而改变，是无法穷举的，或者说没有必要穷举出来的
		std::string visituser;
	};

	

	// 连接池类，充当享元工厂
	class ConnectionPool {
	public:
		ConnectionPool(int maxNum) : maxNum(maxNum), avlNum(maxNum) {}
		// 这个析构不能少，不然会内存泄漏
		~ConnectionPool() {
			for (auto it = pool.begin(); it != pool.end(); ++it) {
				delete it->second;
				it->second = NULL;
			}
			pool.clear();
		}

		// 获取一个连接
		Connection * GetConnection(const std::string & tablename) {
			// 如果连接数已达最大值，返回NULL
			if (avlNum == 0) {
				return NULL;
			}

			if (!pool.count(tablename)) {
				// 如果未找到对应表名的连接，先创建一个连接，再返回
				pool.insert(std::make_pair(tablename, new Connection(tablename)));
			} 
			std::cout << "--------------------------" << std::endl;
			std::cout << "可用连接 ： " << --avlNum << std::endl;
			// 如果找到对应表名的连接，直接返回
			return pool[tablename];
		}
	private:
		// 最大连接数
		int maxNum;
		// 可用连接数
		int avlNum;
		// 连接池容器
		std::map<std::string, Connection *> pool;
	};


	// 测试代码
	static void Test_Flyweight() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--     享元模式测试     --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		// 新建一个连接池工厂
		ConnectionPool connectionPool(5);
		// 返回一个用户表对象
		Connection * userConnection1 = connectionPool.GetConnection("st_user");
		userConnection1->SetVisitUser("Linary");
		userConnection1->PrintInfo();
		// 返回一个课程表对象
		Connection * lessonConnection = connectionPool.GetConnection("st_lesson");
		lessonConnection->SetVisitUser("Cindy");
		lessonConnection->PrintInfo();
		// 返回一个用户表对象
		Connection * userConnection2 = connectionPool.GetConnection("st_user");
		userConnection2->SetVisitUser("Frank");
		userConnection2->PrintInfo();

		std::cout << std::endl;
	}
};