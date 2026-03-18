// main.cpp

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Item
{
private:
	string name_;
	int price_;

public:
	Item() : name_("알 수 없음"), price_(0) {}
	Item(string name, int price) : name_(name), price_(price) {}

	void PrintInfo() const
	{
		cout << "[이름 : " << name_ << ", 가격: " << price_ << "G]" << endl;
	}

	int GetPrice() const { return price_; }
};

bool compareItemsByPrice(const Item& a, const Item& b)
{
	return a.GetPrice() < b.GetPrice();
}

template <typename T>
class Inventory
{
private:
	T* pItems_;
	int capacity_;
	int size_;

public:
	Inventory(int capacity = 10)
	{
		if (capacity <= 0) capacity = 1;
		capacity_ = capacity;

		size_ = 0;
		pItems_ = new T[capacity_];
		cout << "시스템: 용량이 " << capacity_ << "인 인벤토리가 생성되었습니다." << endl;
	}

	~Inventory()
	{
		delete[] pItems_;
		pItems_ = nullptr;
	}

	Inventory(const Inventory<T>& other)
	{
		capacity_ = other.capacity_;
		size_ = other.size_;

		pItems_ = new T[capacity_];

		for (int i = 0; i < size_; ++i)
		{
			pItems_[i] = other.pItems_[i];
		}
		cout << "시스템: 인벤토리 복사 완료" << endl;
	}

	void Assign(const Inventory<T>& other)
	{
		if (this == &other) return;

		delete[] pItems_;

		capacity_ = other.capacity_;
		size_ = other.size_;
		pItems_ = new T[capacity_];

		for (int i = 0; i < size_; ++i)
		{
			pItems_[i] = other.pItems_[i];
		}
		cout << "시스템: 인벤토리 덮어쓰기 완료 (Assign)" << endl;
	}

	void Resize(int newCapacity)
	{
		T* newItems = new T[newCapacity];

		for (int i = 0; i < size_; ++i)
		{
			newItems[i] = pItems_[i];
		}

		delete[] pItems_;
		pItems_ = newItems;
		capacity_ = newCapacity;
		cout << "\n[시스템] 인벤토리 용량이 " << capacity_ << "칸으로 확장되었습니다!" << endl;
	}

	void AddItem(const T& item)
	{
		if (size_ >= capacity_)
		{
			Resize(capacity_ * 2);
		}
		pItems_[size_] = item;
		size_++;
	}

	template <typename Compare>
	void SortItems(Compare comp)
	{
		std::sort(pItems_, pItems_ + size_, comp);
		cout << "\n[시스템] 인벤토리가 가격순으로 정렬되었습니다." << endl;
	}

	int GetSize() const { return size_; }
	int GetCapacity() const { return capacity_; }
	void PrintAllItems() const
	{
		cout << "=== [ 인벤토리 목록 ( " << size_ << " / " << capacity_ << " ) ] ===" << endl;
		if (size_ == 0)
		{
			cout << "비어있음" << endl;
		}
		else
		{
			for (int i = 0; i < size_; i++)
			{
				cout << i + 1 << "빈 슬롯: ";
				pItems_[i].PrintInfo();
			}
		}
		cout << "====================================\n" << endl;
	}
};

int main()
{
	// 1. 자동 확장 테스트
	Inventory<Item> myInv(2);
	myInv.AddItem(Item("차가운 불꽃", 2000));
	myInv.AddItem(Item("진실된 모순", 1000));
	myInv.AddItem(Item("날카로운 죽음", 1500));
	myInv.PrintAllItems();

	// 2. 정렬 테스트
	myInv.SortItems(compareItemsByPrice);
	myInv.PrintAllItems();

	// 3. 복사 생성자 테스트
	Inventory<Item> copiedInv(myInv);
	copiedInv.PrintAllItems();

	// 4. Assign(대입) 테스트
	Inventory<Item> anotherInv(10);
	anotherInv.Assign(myInv);

	return 0;
}