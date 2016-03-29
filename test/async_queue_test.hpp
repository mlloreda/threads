#include <gtest/gtest.h>
#include "async_queue.hpp"

struct AsyncQueueTest : testing::Test
{
  async_queue *q;

  AsyncQueueTest()
  {
    q = new async_queue;
  }
  ~AsyncQueueTest()
  {
    delete q;
  }

};

void target_function(int &c, int a, int b)
{
  for(int i = 0; i < b; i++)
    c += a;
}

void other(float& out, int a, int b)
{
  out = a * b;
}

TEST_F(AsyncQueueTest, SingleEnqueue)
{
  float f = 0;
  q->enqueue(other, std::ref(f), 1, 500);
  q->sync();
  EXPECT_EQ(500, f);
}
TEST_F(AsyncQueueTest, MultipleEnqueuesOne)
{
  int i = 0;
  float f = 0;
  q->enqueue(target_function, std::ref(i), 1, 500);
  q->enqueue(other, std::ref(f), 1, 500);

  q->sync();

  EXPECT_EQ(500, i);
  EXPECT_EQ(500, f);
}

TEST_F(AsyncQueueTest, MultipleEnqueuesTwo)
{
  int i = 0;

  q->enqueue(target_function, std::ref(i), 7, 5000);
  q->enqueue(target_function, std::ref(i), 9, 5000000000);
  q->enqueue(target_function, std::ref(i), 1, 15);

  q->sync();

  EXPECT_EQ(2050362055, i);
}



