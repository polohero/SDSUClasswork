#ifndef PAGE_H
#define PAGE_H

#include <string>

/**
 * A Page represents a single page in the page table.
 */
class Page
{
	public:
		Page (int id);
		int GetID();
		void SetID(int id);
		std::string ToString();

		bool GetRBit();
		void SetRBit(bool rBit);

	private:
		int _id;
		bool _rBit;
};

#endif
