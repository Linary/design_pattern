// Design Pattern 2.0.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "DesignPattern.h"

int _tmain(int argc, _TCHAR* argv[])
{
	linary_decorator::Test_Decorator();
	linary_builder::Test_Builder();
	linary_observer::Test_Observer();
	linary_visitor::Test_Visitor();
	linary_facade::Test_Facade();
	linary_bridge::Test_Bridge();
	linary_flyweight::Test_Flyweight();
	linary_sigleton::Test_Singleton();
	linary_proxy::Test_Proxy();
	linary_mediator::Test_Mediator();
	linary_prototype::Test_Prototype();
	linary_memento::Test_Memento();
	linary_adapter::Test_Adapter();
	linary_composite::Test_Composite();
	linary_dutychain::Test_DutyChain();
	linary_state::Test_State();
	linary_strategy::Test_Strategy();
	linary_command::Test_Command();
	linary_iterator::Test_Iterator();
	linary_factorymethod::Test_FactoryMethod();
	linary_abstractfactory::Test_AbstractFactory();

	system("pause");
	return 0;
}