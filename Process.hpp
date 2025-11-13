#ifndef __PROCESS_HPP__
#define __PROCESS_HPP__

#include "Constants.hpp"
#include "PhysicalMemory.hpp"

namespace memo {

	struct Page {
		size_t number;
		size_t size;
		std::vector<char> data;
	};

	struct PageTableEntry {
		size_t page_number;
		size_t frame_number;
		bool is_valid;
		bool is_modified;
	};

	class Process {
	public:
		Process();
		Process(size_t number_of_pages, int pid, memo::PhysicalMemory* memory);
		void destroy();
		void setData(size_t page_number, size_t offset, char value);
		size_t translateAddress(size_t page_number, size_t offset);
	private:
		int pid;
		std::vector<PageTableEntry> page_table;
		std::vector<Page> pages;
		PhysicalMemory* memory;
	};
}

#endif