#include <assert.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include "malloc.h"

static void check_consistency ();

typedef struct {
    union {
        unsigned free : 1;
        size_t size_dirty;
    };
} header_t;

static void stamp_memory (header_t* h);
static void check_memory_stamp (header_t* h);

typedef header_t footer_t;

typedef struct {
    header_t* heap_start;
    void*     brk;
} params_t;

static params_t params = { NULL, NULL };

static void* header_to_payload (header_t* h) {
  void* p = h + 1;
  assert (ALIGN (p) == p);
  return p;
}

static header_t* payload_to_header (void* p) {
  return p - sizeof (header_t);
}

// b could be a header or a footer
static size_t payload_size (void* b) {
  return ((footer_t*) b)->size_dirty & ~1;
}

// b could be a header or a footer
static size_t block_size (void* b) {
  return sizeof (header_t) + payload_size (b) + sizeof (footer_t);
}

static header_t* header_to_right_header (header_t* h) {
  void* nh = (void*) h + block_size (h);
  if (nh >= params.brk)
    return NULL;
  return (header_t*) nh;
}

static footer_t* header_to_footer (header_t* h) {
  return (footer_t*) ((void*) h + block_size (h) - sizeof (footer_t));
}

static footer_t* header_to_left_footer (header_t* h) {
  footer_t* f = (footer_t*) h - 1;
  if ((void*) f < (void*) params.heap_start)
    return NULL;
  return f;
}

static header_t* header_to_left_header (header_t* h) {
  footer_t* f = header_to_left_footer (h);
  if (f == NULL)
    return NULL;
  return (header_t*) ((void*) h - block_size (f));
}

static void write_size (header_t* b, size_t size, int free, int is_blocksize) {
  if (size) {
    if (is_blocksize)
      size = size - sizeof (header_t) - sizeof (footer_t);
    else
      size = size;
    b->size_dirty = size;
  }

  b->free = free;
  footer_t* f = header_to_footer (b);

  // Size before free!
  if (size)
    f->size_dirty = size;
  f->free = free;
}

static void* find_fit (size_t plsize) {
  for (header_t* h = params.heap_start; h != NULL; h = header_to_right_header (h))
    if (h->free && payload_size (h) >= plsize)
      return h;
  return NULL;
}

#define INIT_ALLOC 4096

static void init_malloc () {
  void* p = sbrk (0) + sizeof (header_t);
  size_t padding = ALIGN (p) - p;
  params.heap_start = padding + sbrk (padding + INIT_ALLOC);
  params.brk = sbrk (0);
  write_size (params.heap_start, INIT_ALLOC, 1, 1);
  stamp_memory (params.heap_start);
}

#define MIN_PAYLOAD_SIZE (add_padding_to_payload_size (16))
#define MIN_BLOCK_SIZE (sizeof (header_t) + sizeof (footer_t) + MIN_PAYLOAD_SIZE)

// This rounds up a payload size so that plsize + footer + header is aligned.
static size_t add_padding_to_payload_size (size_t plsize) {
  size_t protuding = (plsize + sizeof (header_t) + sizeof (footer_t)) % ALIGNMENT;
  if (protuding != 0)
    return plsize + ALIGNMENT - protuding;
  return plsize;
}

static void* new_block_extend_heap (size_t plsize) {
  // Maybe check that left is free and coalesce?
  // header_t* left = header_to_left_header ((header_t*) params.brk);

  size_t minsize = sizeof (header_t) + plsize + sizeof (footer_t);
  assert (minsize >= MIN_BLOCK_SIZE);
  header_t* h = (header_t*) sbrk (minsize);
  write_size (h, plsize, 1, 0);
  params.brk = sbrk (0);
  return h;
}

void* malloc (size_t plsize) {
  if (params.heap_start == NULL)
    init_malloc ();

  check_consistency ();

  plsize = add_padding_to_payload_size (plsize);
  if (plsize < MIN_PAYLOAD_SIZE)
    plsize = MIN_PAYLOAD_SIZE;

  header_t *b = find_fit (plsize);

  if (b == NULL) { // No match, enlarge heap.
    b = new_block_extend_heap (plsize);
    assert (b != NULL);
    check_consistency ();
  }
  else
    check_memory_stamp (b);
  assert (b->free);
  assert (payload_size (b) >= plsize);
  assert (block_size (b) <= ((uintptr_t) params.brk - (uintptr_t) b));

  // Split
  if (block_size (b) > sizeof (header_t) + plsize + sizeof (footer_t) + MIN_BLOCK_SIZE) {
    size_t blsize = block_size (b);
    write_size (b, plsize, 1, 0);
    header_t* n = header_to_right_header (b);
    write_size (n, (uintptr_t) b + blsize - (uintptr_t) n, 1, 1);
  }
  write_size (b, 0, 0, 0);
  check_consistency ();
  return header_to_payload (b);
}

void free (void* p) {
  if (p == NULL)
    return;

  header_t* h = payload_to_header (p);
  header_t* left = header_to_left_header (h);
  header_t* right = header_to_right_header (h);

  // Coalesce
  if (left && left->free && right && right->free) {
    write_size (left, block_size (left) + block_size (h) + block_size (right), 1, 1);
    stamp_memory (left);
  }
  else if (left && left->free) {
    write_size (left, block_size (left) + block_size (h), 1, 1);
    stamp_memory (left);
  }
  else if (right && right->free) {
    write_size (h, block_size (h) + block_size (right), 1, 1);
    stamp_memory (h);
  }
  else {
    write_size (h, 0, 1, 0);
    stamp_memory (h);
  }

  check_consistency ();
}

static void check_consistency () {
#ifndef NDEBUG
  for (header_t* h = params.heap_start; h != NULL; h = header_to_right_header (h)) {
    header_t* left = header_to_left_header (h);
    header_t* right = header_to_right_header (h);
    if (left)
      assert (h == header_to_right_header (left));
    if (right)
      assert (h == header_to_left_header (right));
    assert (((uintptr_t) h + sizeof (header_t)) % ALIGNMENT == 0);
    assert ((void*) h + block_size (h) <= params.brk);
    assert (h->size_dirty == (header_to_footer (h))->size_dirty);
  }
#endif
}

// This should be enough space to not clutter the payload of a free block.
#define STAMP_START(h)  ((void*) h + 40)

static void stamp_memory (header_t* h) {
#ifndef NDEBUG
  for (unsigned* p = STAMP_START (h); p < (unsigned*) header_to_footer (h) - 1; ++p)
    *p = 0xDEADBEEF;
#endif
}

static void check_memory_stamp (header_t* h) {
#ifndef NDEBUG
  for (unsigned* p = STAMP_START (h); p < (unsigned*) header_to_footer (h) - 1; ++p)
    assert (*p == 0xDEADBEEF);
#endif
}

void* realloc (void* p, size_t plsize) {
  if (p == NULL)
    return malloc (plsize);

  header_t* h = payload_to_header (p);
  size_t old_plsize = payload_size (h);
  void *p2 = malloc (plsize);
  memcpy (p2, p, plsize > old_plsize ? old_plsize : plsize);
  free (p);
  return p2;
}
