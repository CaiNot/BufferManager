#include "buf/buf_mgr.h"

// page_size must be times of 4B, page_num must larger than 0
BufferPool::BufferPool(const size_t page_size, const size_t page_num) : capacity_in_pages(page_size) {
  assert(page_size % 4 == 0);
  assert(page_num);

  // get large memory to avoid frequently malloc and free 
  Page *pages = (Page *)malloc(page_num * sizeof(Page));
  char *frames = (char *)malloc(page_num * page_size * sizeof(char));
  
  assert(pages && frames);

  pages[0].prev = NULL;
  pages[page_num - 1].next = NULL;
  pages[0].frame = &frames[0];

  for (int i = 1; i < page_num; i++) {
    pages[i].prev = &pages[i - 1];
    pages[i].frame = &frames[i];
    pages[i - 1].next = &pages[i];
  }
  this->free_list = pages;
  this->lru_list = NULL;
  this->flush_list = NULL;
}

BufferPool::~BufferPool() {}

Status BufferPool::Get(page_id_t page_id, Page *&target_page) {
  auto it = mapping_table.find(page_id);
  if (it == mapping_table.end()) {  // Not in buffer pool
    return Status::NotFound("");
  } else {
    target_page = it->second;
    return Status::OK();
  }
}

Status BufferPool::Put(Page *page) {}