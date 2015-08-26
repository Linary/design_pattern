/*****************************************************************/
/* 设计模式————策略模式
/* 作者：李凝瑞	
/* 时间：2015.06.07
/*****************************************************************/


/**	策略模式：定义一系列算法类，将每一个算法封装起来，并让它们可以相互替换。
 *	策略模式让算法独立于使用它的客户端而变化，是一种对象行为型模式。
 */

#pragma once
#include "stdafx.h"

namespace dp_strategy {
	// 抽象策略类
	class Strategy {
	public:
		// 算法
		virtual void Algorithm() = 0;
	};

	// 具体算法A
	class ConcreteStrategyA : public Strategy {
	public:
		virtual void Algorithm() {}
	};

	// 具体算法B
	class ConcreteStrategyB : public Strategy {
	public:
		virtual void Algorithm() {}
	};

	// 环境类
	class Context {
	public:
		void Algorithm() {
			return strategy->Algorithm();
		}
	private:
		Strategy * strategy;
	};
};

namespace linary_strategy {
	

	// 训练模型：抽象策略类
	class TrainModel {
	public:
		// 抽象训练算法
		virtual void Train() = 0;
	};

	// RBM模型：具体策略
	class RBM : public TrainModel {
	public:
		virtual void Train() {
			std::cout << "用RBM模型训练" << std::endl;
		}
	};

	// CNN模型：具体策略
	class CNN : public TrainModel {
	public:
		virtual void Train() {
			std::cout << "用CNN模型训练" << std::endl;
		}
	};

	// 分类模型：抽象策略类
	class ClassifyModel {
	public:
		// 抽象分类算法
		virtual void Classify() = 0;
	};

	// SVM模型：具体策略
	class SVM : public ClassifyModel {
	public:
		virtual void Classify() {
			std::cout << "用SVM模型分类" << std::endl;
		}
	};

	// KMeans模型：具体策略
	class KMeans : public ClassifyModel {
	public:
		virtual void Classify() {
			std::cout << "用KMeans模型分类" << std::endl;
		}
	};

	// 深度学习算法类：环境类
	class DeepLearning {
	public:
		// 构造与析构
		DeepLearning() {}
		~DeepLearning() {
			delete classifyModel;
			delete trainModel;
		}

		void SetTrainModel(TrainModel * trainModel) {
			this->trainModel = trainModel;
		}

		void SetClassifyModel(ClassifyModel * classifyModel) {
			this->classifyModel = classifyModel;
		}

		// 这是模板方法模式的应用
		void Run() {
			std::cout << "开始执行深度学习..." << std::endl;
			Train();
			Classify();
		}

		// 调用模型类的算法
		void Train() {
			trainModel->Train();
		}

		void Classify() {
			classifyModel->Classify();
		}

	private:
		// ... 预处理
		TrainModel * trainModel;
		ClassifyModel * classifyModel;
		// ... 后处理
	};


	// 测试代码
	static void Test_Strategy() {
		std::cout << "--------------------------" << std::endl;
		std::cout << "--     策略模式测试     --" << std::endl;
		std::cout << "--------------------------" << std::endl;

		DeepLearning deepLearning;
		deepLearning.SetTrainModel(new RBM());
		deepLearning.SetClassifyModel(new SVM());
		deepLearning.Run();

		std::cout << std::endl;
	}
};