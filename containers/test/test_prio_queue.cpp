/**
* B-heap priority queue
* Copyright Jollu Emiluulu
*
* Project home: https://github.com/Jollu8/Algorithms
*/

#include <functional>
#include <cstddef>
#include <algorithm>
#include <queue>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include "containers/prio_queue.h"

using A = enjo::prio_q::HeapAddressing<8>;
using V = enjo::prio_q::SkipVector<int, 4>;
using enjo::PrioQueue;

TEST(VectorTest, DefaultConstructedVectorIsEmpty) {
    const V v;
    EXPECT_EQ(v.size(), 0);
    EXPECT_TRUE(v.empty());
}

TEST(VectorTest, SizeIsTwoAfterOnePushKey) {
    V v;
    v.push_back(1);
    EXPECT_FALSE(v.empty());
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v.back(), 1);
}

TEST(VectorTest, VectorOfSizeTwoBecomesEmptyOnPop) {
    V v;
    v.push_back(1);
    v.pop_back();
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0);
}


TEST(VectorTest, PushKeyIndexesSkipMultiplesOf4) {
    V v;
    EXPECT_EQ(v.push_back(1), 1);
    EXPECT_EQ(v.push_back(1), 2);
    EXPECT_EQ(v.push_back(1), 3);
    EXPECT_EQ(v.push_back(1), 5);
    EXPECT_EQ(v.push_back(1), 6);
    EXPECT_EQ(v.push_back(1), 7);
    EXPECT_EQ(v.push_back(1), 9);
}

TEST(VectorTest, BackRefersToLastElementThroughPushKeyAndPop) {
    V v;
    v.push_back(21);
    EXPECT_EQ(v.back(), 21);
    v.push_back(20);
    EXPECT_EQ(v.back(), 20);
    v.push_back(19);
    EXPECT_EQ(v.back(), 19);
    v.push_back(18);
    EXPECT_EQ(v.back(), 18);
    v.push_back(17);
    EXPECT_EQ(v.back(), 17);
    v.pop_back();
    EXPECT_EQ(v.back(), 18);
    v.pop_back();
    EXPECT_EQ(v.back(), 19);
    v.pop_back();
    EXPECT_EQ(v.back(), 20);
    v.pop_back();
    EXPECT_EQ(v.back(), 21);
    v.pop_back();
    EXPECT_TRUE(v.empty());
}

TEST(AddressingTest, BlockRoot) {
    EXPECT_TRUE(A::is_block_root(1));
    EXPECT_TRUE(A::is_block_root(9));
    EXPECT_TRUE(A::is_block_root(17));
    EXPECT_TRUE(A::is_block_root(73));
    EXPECT_FALSE(A::is_block_root(2));
    EXPECT_FALSE(A::is_block_root(3));
    EXPECT_FALSE(A::is_block_root(4));
    EXPECT_FALSE(A::is_block_root(7));
    EXPECT_FALSE(A::is_block_root(31));
}

TEST(AddressingTest, BlockLeaf) {
    EXPECT_FALSE(A::is_block_leaf(1));
    EXPECT_FALSE(A::is_block_leaf(2));
    EXPECT_FALSE(A::is_block_leaf(3));
    EXPECT_TRUE(A::is_block_leaf(4));
    EXPECT_TRUE(A::is_block_leaf(5));
    EXPECT_TRUE(A::is_block_leaf(6));
    EXPECT_TRUE(A::is_block_leaf(7));
    EXPECT_TRUE(A::is_block_leaf(28));
    EXPECT_TRUE(A::is_block_leaf(29));
    EXPECT_TRUE(A::is_block_leaf(30));
    EXPECT_FALSE(A::is_block_leaf(257));
    EXPECT_TRUE(A::is_block_leaf(255));
}

TEST(AddressingTest, ObtainingChild) {
    EXPECT_EQ(A::child_of(1), 2);
    EXPECT_EQ(A::child_of(2), 4);
    EXPECT_EQ(A::child_of(3), 6);
    EXPECT_EQ(A::child_of(4), 9);
    EXPECT_EQ(A::child_of(31), 249);
}

TEST(AddressingTest, ObtainingParent) {
    EXPECT_EQ(A::parent_of(2), 1);
    EXPECT_EQ(A::parent_of(3), 1);
    EXPECT_EQ(A::parent_of(6), 3);
    EXPECT_EQ(A::parent_of(7), 3);
    EXPECT_EQ(A::parent_of(9), 4);
    EXPECT_EQ(A::parent_of(17), 4);
    EXPECT_EQ(A::parent_of(33), 5);
    EXPECT_EQ(A::parent_of(29), 26);
    EXPECT_EQ(A::parent_of(1097), 140);
}

TEST(PrioQueueTest, DefaultConstructedQueueIsEmpty) {
    const PrioQueue<16, int, void> q;
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);
}

TEST(PrioQueueTest, EmptyQueueIsNotEmptyWhenOneElementIsInserted) {
    PrioQueue<16, int, void> q;
    q.push(1);
    EXPECT_FALSE(q.empty());
    EXPECT_EQ(q.size(), 1);
}

TEST(PrioQueueTest, QueueWithOneElementHasItOnTop) {
    PrioQueue<16, int, void> q;
    q.push(8);
    EXPECT_EQ(q.top(), 8);
}

TEST(PrioQueueTest, QueueWithOneElementBecomesEmptyWhenPopped) {
    PrioQueue<16, int, void> q;
    q.push(9);
    q.pop();
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);
}

TEST(PrioQueueTest, InsertSortedStaysSorted) {
    PrioQueue<16, int, void> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);
    q.push(6);
    q.push(7);
    q.push(8);
    EXPECT_EQ(q.top(), 1);
    q.pop();
    EXPECT_EQ(q.top(), 2);
    q.pop();
    EXPECT_EQ(q.top(), 3);
    q.pop();
    EXPECT_EQ(q.top(), 4);
    q.pop();
    EXPECT_EQ(q.top(), 5);
    q.pop();
    EXPECT_EQ(q.top(), 6);
    q.pop();
    EXPECT_EQ(q.top(), 7);
    q.pop();
    EXPECT_EQ(q.top(), 8);
    q.pop();
    EXPECT_TRUE(q.empty());
}


TEST(PrioQueueTest, KeyValuePairsGoInTandemNontrivial) {
    struct P {
        int a;
        int b;

        bool operator==(const std::pair<int const &, int &> &rh) const {
            return a == rh.first && b == rh.second;
        }
    };
    PrioQueue<16, int, int> q;
    q.push(3, -3);
    q.push(4, -4);
    q.push(8, -8);
    q.push(1, -1);
    q.push(22, -22);
    q.push(23, -23);
    q.push(16, -16);
    q.push(9, -9);
    q.push(25, -25);
    q.push(20, -20);
    q.push(10, -10);
    q.push(5, -5);
    q.push(11, -11);
    q.push(12, -12);
    q.push(19, -19);
    q.push(2, -2);

    EXPECT_EQ((P{1, -1}), q.top());
    q.pop();
    EXPECT_EQ((P{2, -2}), q.top());
    q.pop();
    EXPECT_EQ((P{3, -3}), q.top());
    q.pop();
    EXPECT_EQ((P{4, -4}), q.top());
    q.pop();
    EXPECT_EQ((P{5, -5}), q.top());
    q.pop();
    EXPECT_EQ((P{8, -8}), q.top());
    q.pop();
    EXPECT_EQ((P{9, -9}), q.top());
    q.pop();
    EXPECT_EQ((P{10, -10}), q.top());
    q.pop();
    EXPECT_EQ((P{11, -11}), q.top());
    q.pop();
    EXPECT_EQ((P{12, -12}), q.top());
    q.pop();
    EXPECT_EQ((P{16, -16}), q.top());
    q.pop();
    EXPECT_EQ((P{19, -19}), q.top());
    q.pop();
    EXPECT_EQ((P{20, -20}), q.top());
    q.pop();
    EXPECT_EQ((P{22, -22}), q.top());
    q.pop();
    EXPECT_EQ((P{23, -23}), q.top());
    q.pop();
    EXPECT_EQ((P{25, -25}), q.top());
    q.pop();
    EXPECT_TRUE(q.empty());
}

TEST(PrioQueueTest, KeyValuePairsCanHaveComplexValueTypeNontrivial) {
    PrioQueue<16, int, std::unique_ptr<int> > q;
    q.push(2, nullptr);
    q.push(1, nullptr);
    EXPECT_EQ(1, q.top().first);
    q.pop();
    EXPECT_EQ(2, q.top().first);
    q.pop();
    EXPECT_TRUE(q.empty());
}

TEST(PrioQueueTest, RandomlyInsertedElementsArePoppedSortedHeap) {
    PrioQueue<16, int, void> q;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100000);
    int n[36000];
    for (auto &i: n) {
        i = dist(gen);
        q.push(i);
    }

    EXPECT_FALSE(q.empty());
    EXPECT_EQ(36000, q.size());
    std::sort(std::begin(n), std::end(n));
    for (auto i: n) {
        EXPECT_EQ(i, q.top());
        q.pop();
    }
    EXPECT_TRUE(q.empty());
}

TEST(PrioQueueTest, RescheduleTopWithHighestPrioLeavesOrderUnchangedHeap) {
    PrioQueue<4, int, int *> q;
    //              0  1   2   3  4   5  6   7   8
    int nums[] = {32, 1, 88, 16, 9, 11, 3, 22, 23};
    for (auto &i: nums) q.push(i, &i);
    EXPECT_EQ(1, q.top().first);
    EXPECT_EQ(&nums[1], q.top().second);
    EXPECT_EQ(1, *q.top().second);

    q.reschedule_top(2);

    EXPECT_EQ(2, q.top().first);
    EXPECT_EQ(&nums[1], q.top().second);
    q.pop();
    EXPECT_EQ(3, q.top().first);
    EXPECT_EQ(&nums[6], q.top().second);
    q.pop();
    EXPECT_EQ(9, q.top().first);
    EXPECT_EQ(&nums[4], q.top().second);
    q.pop();
    EXPECT_EQ(11, q.top().first);
    EXPECT_EQ(&nums[5], q.top().second);
    q.pop();
    EXPECT_EQ(16, q.top().first);
    EXPECT_EQ(&nums[3], q.top().second);
    q.pop();
    EXPECT_EQ(22, q.top().first);
    EXPECT_EQ(&nums[7], q.top().second);
    q.pop();
    EXPECT_EQ(23, q.top().first);
    EXPECT_EQ(&nums[8], q.top().second);
    q.pop();
    EXPECT_EQ(32, q.top().first);
    EXPECT_EQ(&nums[0], q.top().second);
    q.pop();
    EXPECT_EQ(88, q.top().first);
    EXPECT_EQ(&nums[2], q.top().second);
    q.pop();
    EXPECT_TRUE(q.empty());
}

TEST(PrioQueueTest, RescheduleToLastMovesElementToCorrectPlaceHeap) {
    PrioQueue<4, int, int *> q;
    //              0  1   2   3  4   5  6   7   8
    int nums[] = {32, 1, 88, 16, 9, 11, 3, 22, 23};
    for (auto &i: nums) q.push(i, &i);
    EXPECT_EQ(1, q.top().first);
    EXPECT_EQ(&nums[1], q.top().second);
    EXPECT_EQ(1, *q.top().second);

    q.reschedule_top(89);

    EXPECT_EQ(3, q.top().first);
    EXPECT_EQ(&nums[6], q.top().second);
    q.pop();
    EXPECT_EQ(9, q.top().first);
    EXPECT_EQ(&nums[4], q.top().second);
    q.pop();
    EXPECT_EQ(11, q.top().first);
    EXPECT_EQ(&nums[5], q.top().second);
    q.pop();
    EXPECT_EQ(16, q.top().first);
    EXPECT_EQ(&nums[3], q.top().second);
    q.pop();
    EXPECT_EQ(22, q.top().first);
    EXPECT_EQ(&nums[7], q.top().second);
    q.pop();
    EXPECT_EQ(23, q.top().first);
    EXPECT_EQ(&nums[8], q.top().second);
    q.pop();
    EXPECT_EQ(32, q.top().first);
    EXPECT_EQ(&nums[0], q.top().second);
    q.pop();
    EXPECT_EQ(88, q.top().first);
    EXPECT_EQ(&nums[2], q.top().second);
    q.pop();
    EXPECT_EQ(89, q.top().first);
    EXPECT_EQ(&nums[1], q.top().second);
    q.pop();
    EXPECT_TRUE(q.empty());
}

TEST(PrioQueueTest, RescheduleTopOf2ElementsToLastHeap) {
    PrioQueue<8, int, void> q;
    q.push(1);
    q.push(2);
    EXPECT_EQ(1, q.top());
    q.reschedule_top(3);
    EXPECT_EQ(2, q.top());
}

TEST(PrioQueueTest, RescheduleTopOf3elementsLeftTo2ndHeap) {
    PrioQueue<8, int, void> q;
    q.push(1);
    q.push(2);
    q.push(4);
    EXPECT_EQ(1, q.top());
    q.reschedule_top(3);
    EXPECT_EQ(2, q.top());
}

TEST(PrioQueueTest, RescheduleTopOf3ElementsRightTo2ndHeap) {
    PrioQueue<8, int, void> q;
    q.push(1);
    q.push(4);
    q.push(2);
    EXPECT_EQ(1, q.top());
    q.reschedule_top(3);
    EXPECT_EQ(2, q.top());
}

TEST(PrioQueueTest, RescheduleTopRandomGivesSameResultasPopPushHeap) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned> dist(1, 100000);

    PrioQueue<8, unsigned, void> pq;
    std::priority_queue<unsigned, std::vector<unsigned>, std::greater<> > stdq;

    for (size_t outer = 0; outer < 100U; ++outer) {
        unsigned num = gen();
        pq.push(num);
        stdq.push(num);
        for (size_t inner = 0; inner < 100; ++inner) {
            unsigned newval = gen();
            pq.reschedule_top(newval);
            stdq.pop();
            stdq.push(newval);
            auto n = pq.top();
            auto sn = stdq.top();
            EXPECT_EQ(sn, n);
        }
    }
}

struct PtrCmp {
    template<typename T>
    bool operator()(T const &lh, T const &rh) const { return *lh < *rh; }
};

TEST(PrioQueueTest, UniquePtrsAreSortedWithCustomCompareNontrivial) {
    PrioQueue<8, std::unique_ptr<int>, void, PtrCmp> q;
    for (int i = 255; i >= 0; --i) {
        q.push(std::make_unique<int>(i));
    }

    for (int i = 0; i < 256; ++i) {
        EXPECT_EQ(i, *q.top());
        q.pop();
    }
    EXPECT_TRUE(q.empty());
}

unsigned g_obj_count{};
unsigned g_copy_count{};
unsigned g_move_throw_count{};
unsigned g_copy_throw_count{};

struct TracedThrowingMove {
    TracedThrowingMove(int n_) : n{n_} { ++g_obj_count; }

    TracedThrowingMove(const TracedThrowingMove &rh) : n{rh.n} {
        if (--g_copy_throw_count == 0) throw 2;
        ++g_obj_count;
        ++g_copy_count;
    }

    TracedThrowingMove(TracedThrowingMove &&rh) noexcept : n{rh.n} {
        if (--g_move_throw_count == 0) throw 3;
        ++g_obj_count;
        rh.n = -rh.n;
    }

    ~TracedThrowingMove() { --g_obj_count; }

    TracedThrowingMove &operator=(const TracedThrowingMove &rh) {
        n = rh.n;
        return *this;
    }

    int n;
    bool operator<(const TracedThrowingMove &rh) const { return n < rh.n; }
};

// TEST(PrioQueueTest, ThrowingMoveAllowsSafeDestructionNontrivial) {
//     g_obj_count = 0;
//     g_move_throw_count = 18;
//     g_copy_throw_count = 0;
//     g_copy_count = 0;
//     bool too_soon = true;
//     try {
//         PrioQueue<16, TracedThrowingMove, void> q;
//         for (int i = 0; i < 17; ++i) {
//             q.push(i);
//         }
//         too_soon = false;
//         q.push(18);
//         FAIL() << "didn't throw";
//     } catch (int) {
//     }
//     EXPECT_FALSE(too_soon);
//     EXPECT_EQ(0, g_obj_count);
// }
//
// TEST(PrioQueueTest, ThrowingCopyAllowSafeDestructionNontrivial) {
//     g_obj_count = 0;
//     g_move_throw_count = 0;
//     g_copy_throw_count = 15 * 15;
//     g_copy_count = 0;
//     std::cout << "begin\n"; /// todo change to log
//     bool too_soon = true;
//     try {
//         PrioQueue<16, TracedThrowingMove, void> q;
//         for (int i = 0; i < 15 * 16; ++i) {
//             q.push(i);
//         }
//         too_soon = false;
//         q.push(1000);
//         FAIL() << "didn't throw";
//     } catch (int) {
//     }
//     EXPECT_FALSE(too_soon);
//     // EXPECT_EQ(0, obj_count); // todo neet to integration user exception
// }
