# The Algorithms in C++

These algorithms are the demonstration purposes only. There are
many algorithms implementations in the C++ standard
library that are much better for performance reasons. This
project contains the following algorithms...

## Allocator

|              Name allocator              | Allocation | Free |
|:----------------------------------------:|:----------:|:----:|
| [Linear allocator](allocators/Linear.cpp) |    O(1)    |  -   |
|   [Pool allocator](allocators/Pool.cpp)   |    O(1)    | O(1) |

## Caching

|                      Name algorithm                       |
|:---------------------------------------------------------:|
| [First in, first out (FIFO)](cache/First_InFirst_Out.cpp) |
|  [Last recently used (LRU)](cache/LeastRecentlyUsed.cpp)  |

## Computational geometry

|                            Name algorithm                             | Average result | Worse result |
|:---------------------------------------------------------------------:|---------------:|:------------:|
|     [Bresenham's line](computationalGeometry/BresenhamsLine.cpp)      |              - |      -       |
| [Ramer-Douglas-Peucker](computationalGeometry/RamerDuglasPeucker.cpp) |    O(n*log(n)) |    O(n^2)    |
|     [Scan-line method](computationalGeometry/ScanLineMethod.cpp)      |    O(n*log(n)) | O(n*log(n))  |

## Cryptography

|                          Name algorithm                          |
|:----------------------------------------------------------------:|
|          [Caesar cipher](cryptography/CeasarChiper.cpp)          |
|                   [RSA](cryptography/RSA.cpp)                    |
|         [Diffie-Hellman](cryptography/DiffieHelman.cpp)          |
| [Data Encryption Standard](cryptography/DataEncryptStandard.cpp) |
|             [Blow Fish ](cryptography/BlowFish.cpp)              |
|             [Triple DES](cryptography/TripleDES.cpp)             |
|                   [RC4](cryptography/RC4.cpp)                    |

## Data structures


|                Name structure                | Indexation |  Search  | Inserting | Deleting  | Memory |
|:--------------------------------------------:|:----------:|:--------:|:---------:|:---------:|:------:|
| [Binary Heap](DS/BinaryHeap.cpp) |     -      |    -     | O(log(n)) | O(log(n)) |  O(n)  |
|    [AVL tree](DS/AVLTree.cpp)    |     -      | O(log n) | O(log n)  | O(log n)  |  O(n)  | 

[//]: # (|  Binary Tree   | O&#40;log&#40;n&#41;&#41;  | O&#40;log&#40;n&#41;&#41; | O&#40;log&#40;n&#41;&#41; | O&#40;log&#40;n&#41;&#41; |  O&#40;n&#41;  |)

[//]: # (|   LinkedList   |    O&#40;n&#41;    |   O&#40;n&#41;    |   O&#40;1&#41;    |   O&#40;1&#41;    |  O&#40;n&#41;  |)

[//]: # (|     Queue      |     -      |     -     |   O&#40;1&#41;    |   O&#40;1&#41;    |  O&#40;n&#41;  |)

[//]: # (|     Stack      |     -      |     -     |   O&#40;1&#41;    |   O&#40;1&#41;    |  O&#40;n&#41;  |)

## Dynamic programming

|                       Name algorithm                        |
|:-----------------------------------------------------------:|
| [Exchange of coins](problems/dp/ExchangeOfCoins.cpp) |
|        [Fibonacci](problems/dp/Fibonacci.cpp)        |

## Graphs

|                Name algorithm                |
|:--------------------------------------------:|
|  [Depth-First Search (DFS)](theory_graph/DFS.cpp)  |
| [Breadth-First Search (BFS)](theory_graph/BFS.cpp) |

## Multithreading

|                        Name algorithm                        |
|:------------------------------------------------------------:|
|            [Ping Pong](threads/PingPong.cpp)            |
| [Producer and consumer](threads/ProduceAndConsumer.cpp) |

## Search

|             Name algorithm              | Data Structure | Average result | Worse result |
|:---------------------------------------:|:--------------:|:--------------:|:------------:|
|   [Binary search](earch/Binary.cpp)    |  Sorted array  |   O(log(n))    |  O(log(n))   |
|    [Linear search](earch/Liner.cpp)    |     Array      |      O(n)      |     O(n)     |
| [Ternary Searching](earch/Ternary.cpp) |     Array      |      O(n)      |     (On)     |

## Set operations

|                                    Name algorithm                                     |
|:-------------------------------------------------------------------------------------:|
| [Difference between the ordered sets](sets/DifferenceOrderedSetsInFirstContainer.cpp) |
|   [ Generation of all permutations from set](sets/IntersectionOfTheOrderedSet.cpp)    |
|          [Generation of all subsets of the set](sets/Gen_OfSubsetOfAll.cpp)           |
|       [Intersection of the ordered sets](sets/IntersectionOfTheOrderedSet.cpp)        |
|        [Symmetric difference of ordered sets](sets/SymmetricDifferenceSet.cpp)        |
|              [Union of the ordered sets](sets/UnionOfTheOrderedSets.cpp)              |

## SmartPointers

|                    Name pointer                    |
|:--------------------------------------------------:|
| [Unique smart pointer](smart_pointers/UniquePtr.cpp) |
| [Shared smart pointer](smart_pointers/SharedPtr.cpp) |

## Sorting

|                    Name algorithm                     | Data Structure | Best result | Average result | Worse result |
|:-----------------------------------------------------:|:--------------:|:-----------:|:--------------:|:------------:|
|           [Bubble sorting](sort/Bubble.cpp)           |     Array      |    O(n)     |     O(n^2)     |    O(n^2)    |
|         [Counting sorting](sort/Counting.cpp)         |     Array      |    O(n)     |      O(n)      |     O(n)     |
|        [Insertion sorting](sort/Insertion.cpp)        |     Array      |   O(n^2)    |     O(n^2)     |    O(n^2)    |
|           [Merge sorting ](sort/Merge.cpp)            |     Array      | O(n*log(n)) |  O(n*log(n))   | O(n*log(n))  |
|            [Quick sorting](sort/Quick.cpp)            |     Array      | O(n*log(n)) |  O(n*log(n))   |    O(n^2)    |
|       [Selection sorting ](sort/Selection.cpp)        |     Array      |    O(n)     |     O(n^2)     |    O(n^2)    |
|           [Shell sorting  ](sort/Shell.cpp)           |     Array      |   O(n^2)    |     O(n^2)     |    O(n^2)    |
|          [Stupid sorting ](sort/Stupid.cpp)           |     Array      |    O(n)     |     O(n^3)     |    O(n^3)    |
| [Quick recursive Sorting](sort/QuicSortRecursive.cpp) |     Array      | O(n*log(n)) |  O(n*log(n))   | O(n*log(n))  |

## Differences

|                            Name algorithm                            |
|:--------------------------------------------------------------------:|
|      [Euclidean algorithm](differences/EuclideanAlgorithm.cpp)       |
|       [ Eratosthenes sieve](differences/EratosthenesSieve.cpp)       |
|            [Queens puzzle](differences/QueensPuzzle.cpp)             |
| [Maximum amount of subArrays](differences/MaxAmountOfSumArrays.cpp)  |
| [Reversal of the forward list](differences/ReversAlFoorwardList.cpp) |
|          [Tom Sawyer sense](differences/TomSawyerSense.cpp)          |

---
