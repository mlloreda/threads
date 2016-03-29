#include <gtest/gtest.h>
#include "async_queue.hpp"

struct AsyncQueueTest : testing::Test
{
  async_queue *q;
  int i = 0;
  float f = 0;

  AsyncQueueTest()
  {
    q = new async_queue;
  }
  ~AsyncQueueTest()
  {
    delete q;
  }
};

void multiplication_by_addition(int &c, int a, int b)
{
  for(int i = 0; i < b; i++)
    c += a;
}

void multiply(float& out, int a, int b)
{
  out = a * b;
}

TEST_F(AsyncQueueTest, SingleEnqueue)
{
  q->enqueue(multiply, std::ref(f), 1, 500);
  q->enqueue(multiplication_by_addition, std::ref(i), 2, 3);
  q->sync();
  EXPECT_EQ(500, f);
  EXPECT_EQ(6, i);
}
TEST_F(AsyncQueueTest, MultipleEnqueuesOne)
{
  q->enqueue(multiplication_by_addition, std::ref(i), 1, 500);
  q->enqueue(multiply, std::ref(f), 1, 500);
  q->sync();

  EXPECT_EQ(500, i);
  EXPECT_EQ(500, f);
}

TEST_F(AsyncQueueTest, MultipleEnqueuesTwo)
{
  q->enqueue(multiplication_by_addition, std::ref(i), 2, 30);
  q->enqueue(multiplication_by_addition, std::ref(i), 9, 55);
  q->enqueue(multiplication_by_addition, std::ref(i), -1, 15);
  q->sync();

  long result = (2*30) + (9*55) + (-1*15);
  EXPECT_EQ(result, i);
}
