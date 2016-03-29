#include <gtest/gtest.h>
#include "async_queue.hpp"

void other(float& out, int a, int b)
{
  out = a * b;
}

TEST(AsyncQueueTest, wat)
{
  float d = 0;
  async_queue my_queue;
  my_queue.enqueue(other, std::ref(d), 1, 500);
  my_queue.sync();
  EXPECT_EQ(500, d);
}


