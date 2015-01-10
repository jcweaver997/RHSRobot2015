
#ifndef COMPONENT_H
#define COMPONENT_H

class Component : public ComponentBase
{
public:
	Component();
	virtual ~Component();

private:
	void Init();
	void OnStateChange();
	void Run();
};

#endif			//COMPONENT_H
