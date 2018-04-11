#ifndef RESOURCE_H_
#define RESOURCE_H_

class Resource {
	virtual void initialize();
	virtual void load();
	virtual void erase();
	virtual void finalize();
};

#endif