#pragma once

class Command {
public:
	virtual void execute(){}
	void release(){delete this;}
private:
};