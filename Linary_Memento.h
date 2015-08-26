/*****************************************************************/
/* 设计模式————备忘录模式
/* 作者：李凝瑞	
/* 时间：2015.06.02
/*****************************************************************/


/**	备忘录模式：在不破坏封装性的前提下，捕获一个对象的内部状态，并在该
 *	对象之外保存这个状态，这样可以在以后将对象恢复到之前保存的状态。
 */
#pragma once
#include "stdafx.h"
namespace linary_memento {

	// 备忘录类
	class Memento {
	public:
		Memento(const std::string & label, int x, int y) : label(label), x(x), y(y) {}

		// 全是get/set方法
		void SetLabel(const std::string & label) {
			this->label = label;
		}

		std::string GetLabel() const {
			return this->label;
		}

		void SetX(int x) {
			this->x = x;
		}

		int GetX() const {
			return this->x;
		}

		void SetY(int y) {
			this->y = y;
		}

		int GetY() const {
			return this->y;
		}
	private:
		std::string label;
		int x;
		int y;
	};


	// 棋子类，充当原发器
	class Chess {
	public:
		Chess(const std::string & label, int x, int y) : label(label), x(x), y(y) {}

		// 全是get/set方法
		void SetLabel(const std::string & label) {
			this->label = label;
		}

		std::string GetLabel() const {
			return this->label;
		}

		void SetX(int x) {
			this->x = x;
		}

		int GetX() const {
			return this->x;
		}

		void SetY(int y) {
			this->y = y;
		}

		int GetY() const {
			return this->y;
		}

		// 打印自身状态
		void Print() const {
			std::cout << "棋子 " << label << " 位于 " << x << " 行 " << y << " 列" << std::endl;
		}

		// 保存状态
		Memento * Save() {
			return new Memento(label, x, y);
		}

		// 恢复状态
		void Restore(Memento * memento) {
			this->label = memento->GetLabel();
			this->x = memento->GetX();
			this->y = memento->GetY();
		}
	private:
		std::string label;
		int x;
		int y;
	};


	// 备忘录管理者类，有待扩展，实现多步撤销，以及取消撤销
	class CareTaker {
	public:
		CareTaker() : memento(NULL) {}

		// 保存新状态时，记得把之前的对象析构
		void SetMemento(Memento * memento) {
			if (this->memento != NULL) {
				delete this->memento;
			}
			this->memento = memento;
		}

		Memento * GetMemento() const {
			return this->memento;
		}
	private:
		Memento * memento;
	};


	// 测试代码
	static void Test_Memento() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--    备忘录模式测试    --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		CareTaker careTaker;
		Chess * chess = new Chess("车", 1, 1);
		chess->Print();
		// 保存状态
		careTaker.SetMemento(chess->Save());
		chess->SetX(4);
		chess->Print();
		// 保存状态
		careTaker.SetMemento(chess->Save());
		chess->SetY(6);
		chess->Print();
		// 恢复状态
		chess->Restore(careTaker.GetMemento());
		chess->Print();

		delete chess;
		std::cout << std::endl;
	}
};