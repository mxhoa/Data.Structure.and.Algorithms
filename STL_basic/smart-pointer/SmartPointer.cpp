#include <iostream>
#include <string>

class RefCount
{
private:
	int m_RefCount{0};

public:
	void increment() { ++m_RefCount; }
	void decrement() { --m_RefCount; }
	int getCount() { return m_RefCount; }
};

template <typename T>
class SmartPointer
{
private:
	T *m_Obj{nullptr};
	RefCount *m_RefCount{nullptr};

public:
	SmartPointer() {}

	SmartPointer(T *obj)
		: m_Obj(obj), m_RefCount(new RefCount())
	{
		m_RefCount->increment();
		std::cout << "Created SmartPointer! Ref count is "
				  << m_RefCount->getCount() << std::endl;
	}

	// Destructor
	virtual ~SmartPointer()
	{
		if (m_RefCount)
		{
			m_RefCount->decrement();
			std::cout << "Destroyed SmartPointer! Ref count is "
					  << m_RefCount->getCount() << std::endl;

			if (m_RefCount->getCount() <= 0)
			{
				delete m_RefCount;
				delete m_Obj;
				m_RefCount = nullptr;
				m_Obj = nullptr;
			}
		}
	}

	// Copy constructor
	SmartPointer(const SmartPointer<T> &other)
		: m_Obj(other.m_Obj), m_RefCount(other.m_RefCount)
	{
		m_RefCount->increment();
		std::cout << "Copied SmartPointer! Ref count is "
				  << m_RefCount->getCount() << std::endl;
	}

	/**
	 * Override the equal opertor, so that when you set one smart pointer equal to
	 * another the old smart pointer has its reference count decremented and the new
	 * smart pointer has its reference count incremented.
	 */
	SmartPointer<T> &operator=(const SmartPointer<T> &other)
	{
		if (this == &other)
			return *this;

		/* If already assiged to an object, remove one reference */
		if (m_RefCount && m_RefCount->getCount() > 0)
		{
			m_RefCount->decrement();
			if (m_RefCount->getCount() == 0)
			{
				delete m_RefCount;
				delete m_Obj;
			}
		}

		m_Obj = other.m_Obj;
		m_RefCount = other.m_RefCount;
		m_RefCount->increment();

		std::cout << "Assigning SmartPointer! Ref count is "
				  << m_RefCount->getCount() << std::endl;

		return *this;
	}

	// Dereference operator
	T &operator*()
	{
		return *m_Obj;
	}

	// Member access operator
	T *operator->()
	{
		return m_Obj;
	}
};

class AirCraft
{
private:
	std::string m_Model;

public:
	AirCraft() : m_Model("Generic Model")
	{
		std::cout << "Generic model aircrarf created" << std::endl;
	}

	AirCraft(const std::string &modelName) : m_Model(modelName)
	{
		std::cout << "AirCraft type [" << m_Model << "] is created!" << std::endl;
	}

	void SetAirCraftModel(const std::string &modelName)
	{
		std::cout << "AirCraft model changed from [" << m_Model << "] to [" << modelName << "]\n";
		m_Model = modelName;
	}
	~AirCraft()
	{
		std::cout << "Destroying AirCraft of model: [" << m_Model << "]!" << std::endl;
	}
};

int main()
{
	SmartPointer<AirCraft> raptorPointer(new AirCraft("F-22 Raptor"));

	raptorPointer->SetAirCraftModel("B2 Bomber");

	(*raptorPointer).SetAirCraftModel("B2 Spirit");

	SmartPointer<AirCraft> testPoint = raptorPointer;

	SmartPointer<AirCraft> hornettPointer(new AirCraft("F-14 Hornett"));

	raptorPointer = hornettPointer;

	std::cout << "EXIT" << std::endl;

	return 0;
}