/*****************************************************************/
/* 设计模式————组合模式
/* 作者：李凝瑞	
/* 时间：2015.06.04
/*****************************************************************/


/**	组合模式：组合多个对象形成树的结构，以表示“整体——部分”关系的层次结构。
 *	组合模式对单个对象（叶子对象）和组合对象（容器对象）的使用具有一致性。
 */
#pragma once
#include "stdafx.h"

namespace dp_composite {
	// 抽象构件类
	class Component {
	public:
		// 增加成员
		virtual void Add(Component * component) = 0;
		// 删除成员
		virtual void Remove(Component * component) = 0;
		// 查找成员
		virtual Component * GetChild(int idx) = 0;
		// 业务方法
		virtual void Operation() = 0;
	};

	// 叶子节点类
	class Leaf : public Component {
		// 增加成员
		virtual void Add(Component * component) {}
		// 删除成员
		virtual void Remove(Component * component) {}
		// 查找成员
		virtual Component * GetChild(int idx) {}
		// 业务方法
		virtual void Operation() {
			// 叶子节点自己的业务方法
		}
	};

	// 组件（容器）类
	class Compisite : public Component {
	public:
		// 增加成员
		virtual void Add(Component * component) {
			coll.push_back(component);
		}
		// 删除成员
		virtual void Remove(Component * component) {
			coll.remove(component);
		}
		// 查找成员
		virtual Component * GetChild(int idx) {
			auto it = coll.begin();
			std::advance(it, idx);
			return *it;
		}
		// 业务方法
		virtual void Operation() {
			// 叶子节点自己的业务方法
		}
	private:
		std::list<Component *> coll;
	};
};


namespace linary_composite {
	// 这里用的是透明组合模式
	// 抽象文件类
	class AbstractFile {
	public:
		AbstractFile(const std::string & name) : name(name) {}

		virtual void Add(AbstractFile * file) = 0;
		virtual void Remove(AbstractFile * file) = 0;
		virtual AbstractFile * GetChild(int idx) = 0;
		virtual void KillVirus() = 0;
	protected:
		std::string name;
	};

	// 图像文件类
	class ImageFile : public AbstractFile {
	public:
		ImageFile(const std::string & name) : AbstractFile(name) {}

		virtual void Add(AbstractFile * file) {
			std::cout << "对不起，不支持该操作" << std::endl;
		}
		virtual void Remove(AbstractFile * file) {
			std::cout << "对不起，不支持该操作" << std::endl;
		}
		virtual AbstractFile * GetChild(int idx) {
			return NULL;
		}
		virtual void KillVirus() {
			std::cout << "--对图像文件【" << name << "】杀毒" << std::endl;
		}
	};

	// 文本文件类
	class TextFile : public AbstractFile {
	public:
		TextFile(const std::string & name) : AbstractFile(name) {}

		virtual void Add(AbstractFile * file) {
			std::cout << "对不起，不支持该操作" << std::endl;
		}
		virtual void Remove(AbstractFile * file) {
			std::cout << "对不起，不支持该操作" << std::endl;
		}
		virtual AbstractFile * GetChild(int idx) {
			return NULL;
		}
		virtual void KillVirus() {
			std::cout << "--对文本文件【" << name << "】杀毒" << std::endl;
		}
	};

	// 文件夹类
	class Folder : public AbstractFile {
	public:
		Folder(const std::string & name) : AbstractFile(name), coll() {}

		virtual void Add(AbstractFile * file) {
			coll.push_back(file);
		}
		virtual void Remove(AbstractFile * file) {
			coll.remove(file);
		}
		virtual AbstractFile * GetChild(int idx) {
			auto it = coll.begin();
			std::advance(it, idx);
			return *it;
		}
		virtual void KillVirus() {
			std::cout << "对文件夹【" << name << "】杀毒" << std::endl;
			// 递归调用成员的KillVirus方法
			for (auto it = coll.begin(); it != coll.end(); ++it) {
				(*it)->KillVirus();
			}
		}
	private:
		// 这里应该换成如树之类的数据结构
		std::list<AbstractFile *> coll;
	};


	// 测试代码
	static void Test_Composite() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--     组合模式测试     --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		// 针对同样的抽象文件编程
		AbstractFile * file1, * file2, * file3, * file4;
		AbstractFile * folder1, * folder2, * folder3;

		folder1 = new Folder("我的文档");
		folder2 = new Folder("图像文件");
		folder3 = new Folder("文本文件");

		file1 = new ImageFile("小龙女.jpg");
		file2 = new ImageFile("张无忌.jpg");
		file3 = new TextFile("神雕侠侣.txt");
		file4 = new TextFile("倚天屠龙记.pdf");

		folder2->Add(file1);
		folder2->Add(file2);
		folder3->Add(file3);
		folder3->Add(file4);
		folder1->Add(folder2);
		folder1->Add(folder3);

		folder1->KillVirus();

		delete folder3;
		delete folder2;
		delete folder1;
		delete file4;
		delete file3;
		delete file2;
		delete file1;

		std::cout << std::endl;
	}
};