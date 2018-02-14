#pragma once

template <class VALUE> class TSet
{
public:
	virtual ~TSet(void) = 0;
	virtual void Add(const VALUE e) = 0;
	virtual bool Contains(const VALUE e) = 0;
	virtual bool IsEmpty(void) = 0;
	virtual void Remove(const VALUE e) = 0;
	virtual int Size(void) = 0;
	virtual void AddAll(const TSet<VALUE> &other) = 0;
	virtual void RemoveAll(const TSet<VALUE> &other) = 0;
	virtual void RetainAll(const TSet<VALUE> &other) = 0;
};

template <class VALUE> class THashSet : public TSet
{
public:
	~THashSet(void) {}
	void Add(const VALUE e) {}
	bool Contains(const VALUE e) {}
	bool IsEmpty(void) {}
	void Remove(const VALUE e) {}
	int Size(void) {}
	void AddAll(const TSet<VALUE> &other) {}
	void RemoveAll(const TSet<VALUE> &other) {}
	void RetainAll(const TSet<VALUE> &other) {}
private:
	TArray<VALUE> data;
};