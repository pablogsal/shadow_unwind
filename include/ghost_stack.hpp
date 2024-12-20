#pragma once
#include <cstdint>
#include <memory>
#include <vector>
#define UNW_LOCAL_ONLY
#include <libunwind.h>

struct StackEntry {
  uintptr_t return_address; // Original return address
  uintptr_t *location;      // Location of return address on stack
  uintptr_t stack_pointer;  // Stack pointer value
  uintptr_t ip;             // Instruction pointer when the trace was taken
};

class GhostStack {
public:
  static GhostStack &get();
  uintptr_t on_ret_trampoline(uintptr_t stack_pointer);
  void capture_stack_trace(bool install_trampolines);
  const std::vector<uintptr_t> unwind(bool install_trampolines = true);
  void reset();

private:
  GhostStack() = default;
  std::vector<StackEntry> entries;
  size_t location = 0;
  static thread_local std::unique_ptr<GhostStack> instance;
};
