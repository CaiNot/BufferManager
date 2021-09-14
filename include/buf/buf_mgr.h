#ifndef BufferManager_BUF_MGR_H
#define BufferManager_BUF_MGR_H

#include <cstddef>
#include <functional>
#include <unordered_map>

#include "utils/status.h"
typedef uint64_t page_id_t;

struct Page {
  page_id_t page_id;

  Page *prev;
  Page *next;
  char *frame;
};

class BufferPool {
 private:
  const size_t capacity_in_pages;
  Page *free_list;
  Page *lru_list;
  Page *flush_list;

  std::unordered_map<page_id_t, Page *> mapping_table;

 public:
  BufferPool(const size_t page_size, const size_t page_num);
  Status Get(page_id_t page_id,Page *&target_page);
  Status Put(Page *page);
  ~BufferPool();
};

#endif