//
// Created by Jollu Emil on 2/25/24.
//

#include "gtest/gtest.h"
#include "include/DS/binary_heap.h"

TEST(BinaryHeapTest, PushAndTop)
{
    BinaryHeap<int> heap;
    heap.push(5);
    EXPECT_EQ(heap.top(), 5);
}

TEST(BinaryHeapTest, Pop)
{
    BinaryHeap<int> heap;
    heap.push(5);
    heap.push(3);
    heap.pop();
    EXPECT_EQ(heap.top(), 3);
}

TEST(BinaryHeapTest, Clear)
{
    BinaryHeap<int> heap;
    heap.push(5);
    heap.push(3);
    heap.clear();
    EXPECT_TRUE(heap.isEmpty());
}

TEST(BinaryHeapTest, Size)
{
    BinaryHeap<int> heap;
    heap.push(5);
    heap.push(3);
    EXPECT_EQ(heap.getSize(), 2);
}

TEST(BinaryHeapTest, Depth)
{
    BinaryHeap<int> heap;
    for(int i = 0; i < 8; ++i)
        heap.push(i);
    EXPECT_EQ(heap.getDepth(), 4);
}

TEST(BinaryHeapTest, IsEmpty)
{
    BinaryHeap<int> heap;
    EXPECT_TRUE(heap.isEmpty());
    heap.push(5);
    EXPECT_FALSE(heap.isEmpty());
}
