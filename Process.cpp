#include "Process.hpp"

namespace memo {
	Process::Process() : pid(-1) {}
	Process::Process(size_t number_of_pages, int pid, memo::PhysicalMemory* memory) : pid(-1) {
		
		if (number_of_pages == ZERO_SIZE) {
			std::cerr << "[ERROR] Process must have at least one page.\n";
			return;
		}

		if (number_of_pages > MAX_NUMBER_OF_PAGES) {
			std::cerr << "[ERROR] Process cannot have more than " << MAX_NUMBER_OF_PAGES << " pages.\n";
			return;
		}

		if (number_of_pages > memory->get_free_frame_count()) {
			std::cerr << "[ERROR] Not enough frames in physical memory\n";
			//TO DO Handle it with swapping
			return;
		}
		
		this->pid = pid;
		for (size_t i = 0; i < number_of_pages; i++) {
			Page page = { i, PAGE_SIZE, std::vector<char>(PAGE_SIZE, 0)};
			pages.push_back(page);
			PageTableEntry entry = { i, MAX_NUMBER_OF_FRAMES, false, false };
			page_table.push_back(entry);
		}
		this->memory = memory;
	}

	void Process::destroy(){
		pid = -1;
		//TO DO Clear pages from physical memory
	}

	void Process::setData(size_t page_number, size_t offset, char data) {
		if (memory->get_free_frame_count() == 0) {
			std::cerr << "[ERROR] No free frames available in physical memory.\n";
			return;
			//TO DO Handle it with swapping
		}

		if (page_number >= pages.size()) {
			std::cerr << "[ERROR] Invalid page number.\n";
			return;
		}

		if (offset >= pages[page_number].size) {
			std::cerr << "[ERROR] Offset exceeds page size.\n";
			return;
		}

		if (!page_table[page_number].is_valid) {
			size_t frame_number = memory->allocate_frame();
			if (frame_number == MAX_NUMBER_OF_FRAMES) {
				std::cerr << "[ERROR] Failed to allocate frame for page" << page_number << '\n';
				return;
			}
			page_table[page_number].frame_number = frame_number;
			page_table[page_number].is_valid = true;

		}
	}

	size_t Process::translateAddress(size_t frame_number, size_t offset) {
		size_t physical_address = 0;
		physical_address |= frame_number << 12;
		physical_address |= offset;

		return physical_address;
	}
}