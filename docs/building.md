# Сборка и запуск

Команды выполняются из корня репозитория. Нужны CMake 3.27+ и C++20.

## Основные примеры

```sh
cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug
cmake --build build/debug --parallel
./build/debug/sorting_insertion
```

Доступные цели: `sorting_bubble`, `sorting_counting`, `sorting_insertion`,
`sorting_merge`, `sorting_quick`, `sorting_quick_recursive`,
`sorting_selection`, `sorting_shell`, `sorting_stupid`.

Для сборки одного примера:

```sh
cmake --build build/debug --target sorting_merge
./build/debug/sorting_merge
```

## Другой исходный файл

Каждая программа со своим `main()` собирается отдельно. Укажите путь от корня
репозитория или абсолютный путь:

```sh
cmake -S . -B build/selected -DALGORITHM_SOURCE=algorithms/misc/EuclideanAlgorithm.cpp
cmake --build build/selected --target selected_algorithm
./build/selected/selected_algorithm
```

При смене файла повторите конфигурацию с новым `ALGORITHM_SOURCE`.
Чтобы убрать дополнительную цель, передайте `-DALGORITHM_SOURCE=`.
Для задач с вводом используйте перенаправление: `./build/selected/selected_algorithm < input.txt`.
В генераторах с несколькими конфигурациями добавьте `--config Debug` при сборке;
исполняемые файлы будут в подкаталоге `Debug` (на Windows — с расширением `.exe`).

Этот способ рассчитан на самостоятельные файлы со стандартной библиотекой;
поддержка потоков подключается автоматически. Фрагменты без `main()`, решения
для окружения LeetCode и незавершённый код могут требовать доработки.

## AddressSanitizer

Для GCC и Clang:

```sh
cmake -S . -B build/asan -DCMAKE_BUILD_TYPE=Debug -DSANITIZE=ON
cmake --build build/asan --parallel
./build/asan/sorting_insertion
```

## Библиотечные эксперименты

Старые модули и тесты находятся в [libraries](../libraries/README.md).
Корневая сборка их не подключает. Conan для основной сборки не нужен.
Старые каталоги `cmake-build-*` содержат кеш с прежними путями;
после переноса используйте новый каталог сборки.
