# The Algorithms in C++

These algorithms are the demonstration purposes only. There are
many algorithms implementations in the C++ standard
library that are much better for performance reasons. This
project contains the following algorithms...

## Allocator

|              Name allocator              | Allocation | Free |
|:----------------------------------------:|:----------:|:----:|
| [Linear allocator](Allocator/Linear.cpp) |    O(1)    |  -   |
|   [Pool allocator](Allocator/Pool.cpp)   |    O(1)    | O(1) |

## Caching

|                      Name algorithm                       |
|:---------------------------------------------------------:|
| [First in, first out (FIFO)](Cache/First_InFirst_Out.cpp) |
|  [Last recently used (LRU)](Cache/LeastRecentlyUsed.cpp)  |

## Computational geometry

|                            Name algorithm                             | Average result | Worse result |
|:---------------------------------------------------------------------:|---------------:|:------------:|
|     [Bresenham's line](ComputationalGeometry/BresenhamsLine.cpp)      |              - |      -       |
| [Ramer-Douglas-Peucker](ComputationalGeometry/RamerDuglasPeucker.cpp) |    O(n*log(n)) |    O(n^2)    |
|     [Scan-line method](ComputationalGeometry/ScanLineMethod.cpp)      |    O(n*log(n)) | O(n*log(n))  |

## Cryptography

|                 Name algorithm                  |
|:-----------------------------------------------:|
| [Caesar cipher](Cryptography/CeasarChiper.cpp)  |
|           [RSA](Cryptography/RSA.cpp)           |
| [Diffie-Hellman](Cryptography/DiffieHelman.cpp) |

[//]: # (## Data structures)

[//]: # ()

[//]: # (| Name structure | Indexation |  Search   | Inserting | Deleting  | Memory |)

[//]: # (|:--------------:|:----------:|:---------:|:---------:|:---------:|:------:|)

[//]: # (|  Binary Heap   |     -      |     -     | O&#40;log&#40;n&#41;&#41; | O&#40;log&#40;n&#41;&#41; |  O&#40;n&#41;  |)

[//]: # (|  Binary Tree   | O&#40;log&#40;n&#41;&#41;  | O&#40;log&#40;n&#41;&#41; | O&#40;log&#40;n&#41;&#41; | O&#40;log&#40;n&#41;&#41; |  O&#40;n&#41;  |)

[//]: # (|   LinkedList   |    O&#40;n&#41;    |   O&#40;n&#41;    |   O&#40;1&#41;    |   O&#40;1&#41;    |  O&#40;n&#41;  |)

[//]: # (|     Queue      |     -      |     -     |   O&#40;1&#41;    |   O&#40;1&#41;    |  O&#40;n&#41;  |)

[//]: # (|     Stack      |     -      |     -     |   O&#40;1&#41;    |   O&#40;1&#41;    |  O&#40;n&#41;  |)

## Dynamic programming

|                       Name algorithm                        |
|:-----------------------------------------------------------:|
| [Exchange of coins](DinamicProgramming/ExchangeOfCoins.cpp) |
|        [Fibonacci](DinamicProgramming/Fibonacci.cpp)        |

## Graphs

|                Name algorithm                |
|:--------------------------------------------:|
|  [Depth-First Search (DFS)](Graphs/DFS.cpp)  |
| [Breadth-First Search (BFS)](Graphs/BFS.cpp) |

## Multithreading

|    Name algorithm     |
|:---------------------:|
|       [Ping Pong](Multithreads/PingPong.cpp)       |
| [Producer and consumer](Multithreads/ProduceAndConsumer.cpp) |

## Search

|             Name algorithm              | Data Structure | Average result | Worse result |
|:---------------------------------------:|:--------------:|:--------------:|:------------:|
|   [Binary search](Search/Binary.cpp)    |  Sorted array  |   O(log(n))    |  O(log(n))   |
|    [Linear search](Search/Liner.cpp)    |     Array      |      O(n)      |     O(n)     |
| [Ternary Searching](Search/Ternary.cpp) |     Array      |      O(n)      |     (On)     |

## Set operations

|                                    Name algorithm                                     |
|:-------------------------------------------------------------------------------------:|
| [Difference between the ordered sets](Sets/DifferenceOrderedSetsInFirstContainer.cpp) |
|   [ Generation of all permutations from set](Sets/IntersectionOfTheOrderedSet.cpp)    |
|          [Generation of all subsets of the set](Sets/Gen_OfSubsetOfAll.cpp)           |
|       [Intersection of the ordered sets](Sets/IntersectionOfTheOrderedSet.cpp)        |
|        [Symmetric difference of ordered sets](Sets/SymmetricDifferenceSet.cpp)        |
|              [Union of the ordered sets](Sets/UnionOfTheOrderedSets.cpp)              |

## SmartPointers

|                    Name pointer                    |
|:--------------------------------------------------:|
| [Unique smart pointer](SmartPointes/UniquePtr.cpp) |
| [Shared smart pointer](SmartPointes/SharedPtr.cpp) |

## Sorting

|                    Name algorithm                     | Data Structure | Best result | Average result | Worse result |
|:-----------------------------------------------------:|:--------------:|:-----------:|:--------------:|:------------:|
|           [Bubble sorting](Sort/Bubble.cpp)           |     Array      |    O(n)     |     O(n^2)     |    O(n^2)    |
|         [Counting sorting](Sort/Counting.cpp)         |     Array      |    O(n)     |      O(n)      |     O(n)     |
|        [Insertion sorting](Sort/Insertion.cpp)        |     Array      |   O(n^2)    |     O(n^2)     |    O(n^2)    |
|           [Merge sorting ](Sort/Merge.cpp)            |     Array      | O(n*log(n)) |  O(n*log(n))   | O(n*log(n))  |
|            [Quick sorting](Sort/Quick.cpp)            |     Array      | O(n*log(n)) |  O(n*log(n))   |    O(n^2)    |
|       [Selection sorting ](Sort/Selection.cpp)        |     Array      |    O(n)     |     O(n^2)     |    O(n^2)    |
|           [Shell sorting  ](Sort/Shell.cpp)           |     Array      |   O(n^2)    |     O(n^2)     |    O(n^2)    |
|          [Stupid sorting ](Sort/Stupid.cpp)           |     Array      |    O(n)     |     O(n^3)     |    O(n^3)    |
| [Quick recursive Sorting](Sort/QuicSortRecursive.cpp) |     Array      | O(n*log(n)) |  O(n*log(n))   | O(n*log(n))  |

## Differences

|                            Name algorithm                            |
|:--------------------------------------------------------------------:|
|      [Euclidean algorithm](Differences/EuclideanAlgorithm.cpp)       |
|       [ Eratosthenes sieve](Differences/EratosthenesSieve.cpp)       |
|            [Queens puzzle](Differences/QueensPuzzle.cpp)             |
| [Maximum amount of subArrays](Differences/Max amountOfSumArrays.cpp) |
| [Reversal of the forward list](Differences/ReversAlFoorwardList.cpp) |
|          [Tom Sawyer sense](Differences/TomSawyerSense.cpp)          |

---
