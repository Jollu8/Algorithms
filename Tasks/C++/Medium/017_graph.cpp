//cmake_minimum_required(VERSION 3.20)
//
//add_executable(
//        task1
//main.cpp
//        Listgraph.cpp
//        Matrixgraph.cpp
//)
//
//target_include_directories(
//        task1 PUBLIC
//        ${MY_HEADER_DIR}
//)

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <set>


class IGraph {
public:

    virtual ~IGraph() {};

    virtual void AddEdge(size_t from, size_t to) = 0;

    virtual int VerticesCount() const = 0;

    virtual void ShowGraph() const = 0;

    virtual void GetNextVertices(size_t vertex, std::vector<size_t> &vertices) const = 0;

    virtual void GetPrevVertices(size_t vertex, std::vector<size_t> &vertices) const = 0;

};

//
//  MatrixGraph class ориентированный
//  (строка направление от вершины from колонка направление до вершины to)
//
class MatrixGraph : public IGraph {
    const int c_ratio; //коэффициент емкости :)
    size_t _size;
    size_t _capacity;
    bool **_graph;

    struct Quantity_cache {
        mutable bool status;
        mutable size_t vertices;
    } cache;

    void resize(size_t new_size);

public:
    //Устанавливает емкость матрицы
    MatrixGraph(int capacity = 5);

    MatrixGraph(IGraph *oth);

    MatrixGraph(const MatrixGraph &matrix_g);

    MatrixGraph &operator=(const MatrixGraph &matrix_g);

    ~MatrixGraph();

// Метод принимает вершины начала и конца ребра и добавляет ребро
    void AddEdge(size_t from, size_t to) override;

// Метод должен считать текущее количество вершин
    int VerticesCount() const override;

// [experimental] Вывод графа в консоль
    void ShowGraph() const override;

// Для конкретной вершины метод выводит в вектор “вершины” все вершины, в которые можно дойти по ребру из данной
    void GetNextVertices(size_t vertex, std::vector<size_t> &vertices) const override;

// Для конкретной вершины метод выводит в вектор “вершины” все вершины, из которых можно дойти по ребру в данную
    void GetPrevVertices(size_t vertex, std::vector<size_t> &vertices) const override;

    int SizeMatrix() const { return _size; }

    int CapacityMatrix() const { return _capacity; }
};


class ListGraph : public IGraph {

    std::map<std::size_t, std::vector<std::size_t>> _graph;

public:
    ListGraph();

    ListGraph(IGraph *oth);

    //ListGraph(const ListGraph &list_g);

    //ListGraph& operator= (const ListGraph &list_g);

    ~ListGraph();

// Метод принимает вершины начала и конца ребра и добавляет ребро
    void AddEdge(size_t from, size_t to) override;

// Метод должен считать текущее количество вершин
    int VerticesCount() const override;

// Вывод графа в консоль
    void ShowGraph() const override;

// Для конкретной вершины метод выводит в вектор “вершины” все вершины, в которые можно дойти по ребру из данной
    void GetNextVertices(size_t vertex, std::vector<size_t> &vertices) const override;

// Для конкретной вершины метод выводит в вектор “вершины” все вершины, из которых можно дойти по ребру в данную
    void GetPrevVertices(size_t vertex, std::vector<size_t> &vertices) const override;

    void GetNameVertices(std::vector<std::size_t> &name) const;
}
//
//  ListGraph implementation
//

ListGraph::ListGraph() {
    std::cout << "constructor ListGraph\n";
    // _graph = new std::map<std::size_t, std::vector<std::size_t>>;
}

ListGraph::ListGraph(IGraph *oth) {
    //Приводим базовый класс к дочернему
    MatrixGraph *matrix = dynamic_cast<MatrixGraph *>(oth);
    //если не матрица то выходим
    if (matrix) {
        std::cout << "Convert matrix to list" << std::endl;
        //Полочаем количество вершин в матрице
        std::size_t vertex_count = matrix->VerticesCount();

        for (std::size_t i = 0; i < vertex_count + 1; ++i) {
            std::vector<std::size_t> vec;
            matrix->GetNextVertices(i, vec);//Сотрим соседей вершины
            if (vec.size() != 0) //если соседи есть
            {
                for (const auto &n: vec)
                    this->AddEdge(i, n);//добавляем ребра от текушей вершины
            } else//если соседей нет
            {
                std::vector<std::size_t> vec;
                matrix->GetPrevVertices(i, vec);//смотрим соседей в другую сторону
                if (vec.size() != 0)//если есть, то добавляем текушую вершину как начальную
                {
                    _graph[i] = std::vector<std::size_t>();//с пустыми исходящими так как в прямом направлении их нет
                }
            }
        }
    } else {
        std::cout << "No convert matrix to list" << std::endl;
    }
}

/*ListGraph::ListGraph(const ListGraph &list_g)
{
     //create ptr || copy ptr
}
ListGraph& ListGraph::operator=(const ListGraph &list_g)
{
    if(this == &list_g)
            return *this;
        //delete ptr
        //create ptr || copy ptr
    return *this;
}*/

ListGraph::~ListGraph() {
    std::cout << "destructor ~ListGraph\n";
}

void ListGraph::AddEdge(size_t from, size_t to) {
    // провекра на отрицательные

    if (from == ULONG_MAX || to == ULONG_MAX) {
        std::cout << "error input: can't be negative\n";
        return;
    }
    std::vector<std::size_t> vertices_to{to};

    //Вствляем вершины
    auto it = _graph.insert(std::make_pair(from, vertices_to));
    //Если вершина from уже есть, то вставлем соседа
    if (!it.second) {
        it.first->second.push_back(to);
    }
    //ищем вершину to в ключах from, если ее нет вставляем пустую
    auto fit = _graph.find(to);
    if (fit == _graph.end()) {
        _graph[to] = std::vector<std::size_t>();
    }
}

int ListGraph::VerticesCount() const {
    return _graph.size();
}

void ListGraph::ShowGraph() const {
    for (auto &it: _graph) {
        std::cout << it.first;
        for (auto &verex: it.second)
            std::cout << "->" << verex;

        std::cout << std::endl;
    }
}

void ListGraph::GetNextVertices(size_t vertex, std::vector<size_t> &vertices) const {
    auto it = _graph.find(vertex);

    if (it != _graph.end()) {
        for (auto &vert: it->second)
            vertices.push_back(vert);
    } else {
        std::cout << "Incorect vertex" << std::endl;
    }
}

void ListGraph::GetPrevVertices(size_t vertex, std::vector<size_t> &vertices) const {
    auto it_g = _graph.find(vertex);

    if (it_g != _graph.end()) {
        for (auto it = _graph.begin(); it != _graph.end(); ++it) {
            for (std::size_t vec = 0; vec < it->second.size(); ++vec) {
                if (vertex == it->second[vec]) {
                    vertices.push_back(it->first);
                }
            }
        }
    } else {
        std::cout << "Incorect vertex" << std::endl;
    }
}

void ListGraph::GetNameVertices(std::vector<std::size_t> &name) const {
    for (auto it = _graph.begin(); it != _graph.end(); ++it) {
        name.push_back(it->first);
    }
}



//  MatrixGraph implementation
//

MatrixGraph::MatrixGraph(int capacity) : c_ratio(capacity) {
    _size = 0;
    _capacity = 0;
    _graph = nullptr;
    cache.status = false;
    cache.vertices = 0;
}

void MatrixGraph::resize(size_t new_size) {

    bool **new_graph = nullptr;

    //копируем старый массив во временный если он есть
    if (_graph != nullptr) {
        //Создаем временный массив с новым размером
        new_graph = new bool *[new_size];
        for (size_t count_row = 0; count_row < new_size; ++count_row) {
            new_graph[count_row] = new bool[new_size];
            //Заполняем строку массива
            for (size_t j = 0; j < new_size; ++j) {
                new_graph[count_row][j] = false;
            }
        }
        //копируем старый массив во временный
        for (size_t i = 0; i < new_size; ++i) {
            for (size_t j = 0; j < new_size; ++j) {
                if (i < _size) {
                    new_graph[i][j] = _graph[i][j];
                }
            }
        }
        //Удаляем старый массив из пямяти
        for (size_t count_col = 0; count_col < _capacity; ++count_col) {
            delete[] _graph[count_col];
        }
        delete[] _graph;
        _graph = nullptr;
    }
    //Сохраняем новый размер
    _size = new_size;

    //увеличиваем емскость
    _capacity = new_size + c_ratio;

    //Выделяем новый размер массива из пямяти c увеличенной емкостью
    _graph = new bool *[_capacity];
    for (size_t count_row = 0; count_row < _capacity; ++count_row) {
        _graph[count_row] = new bool[_capacity];
        for (size_t j = 0; j < new_size; ++j) {
            _graph[count_row][j] = false;
        }
    }
    //Копируем массив из временного в постоянный
    if (new_graph != nullptr) {
        for (size_t i = 0; i < new_size; ++i) {
            for (size_t j = 0; j < new_size; ++j) {
                _graph[i][j] = new_graph[i][j];
            }
        }
        //Удаляем временный массив
        for (size_t count_col = 0; count_col < new_size; ++count_col) {
            delete[] new_graph[count_col];
        }
        delete[] new_graph;
        new_graph = nullptr;
    }
}

MatrixGraph::MatrixGraph(IGraph *oth) : MatrixGraph() {
    ListGraph *list = dynamic_cast<ListGraph *>(oth);
    if (list) {
        std::cout << "Convert List to Matrix" << std::endl;
        std::size_t vertex_count = list->VerticesCount();
        std::vector<std::size_t> name_vertex;
        list->GetNameVertices(name_vertex);
        if (name_vertex.size() != vertex_count)
            return;

        for (std::size_t i_count = 0; i_count < vertex_count; ++i_count) {
            std::vector<std::size_t> vertex;
            list->GetNextVertices(name_vertex[i_count], vertex);
            for (auto &v: vertex)
                this->AddEdge(name_vertex[i_count], v);
        }

    } else {
        std::cout << "No convert List to Matrix" << std::endl;
    }
}


MatrixGraph::MatrixGraph(const MatrixGraph &list_g) : MatrixGraph() {
    std::cout << "Create copy Matrix" << std::endl;
    //Выделяем новый размер массива из пямяти
    _graph = new bool *[list_g._capacity];
    for (size_t count_row = 0; count_row < list_g._capacity; ++count_row) {
        _graph[count_row] = new bool[list_g._capacity];
        //Заполняем строку массива
        for (size_t j = 0; j < list_g._capacity; ++j) {
            _graph[count_row][j] = false;
        }
    }
    //Копируем массив
    for (size_t i = 0; i < list_g._size; ++i) {
        for (size_t j = 0; j < list_g._size; ++j) {
            _graph[i][j] = list_g._graph[i][j];
        }
    }
    _size = list_g._size;
    _capacity = list_g._capacity;
}

MatrixGraph &MatrixGraph::operator=(const MatrixGraph &list_g) {
    std::cout << "Create copy= Matrix" << std::endl;
    if (this == &list_g)
        return *this;

    if (_graph != nullptr) {
        for (size_t count_col = 0; count_col < _capacity; ++count_col) {
            delete[] _graph[count_col];
        }
        delete[] _graph;
    }

    _graph = new bool *[list_g._capacity];
    for (size_t count_row = 0; count_row < list_g._capacity; ++count_row) {
        _graph[count_row] = new bool[list_g._capacity];
        //Заполняем строку массива
        for (size_t j = 0; j < list_g._capacity; ++j) {
            _graph[count_row][j] = false;
        }
    }
    //Копируем массив
    for (size_t i = 0; i < list_g._size; ++i) {
        for (size_t j = 0; j < list_g._size; ++j) {
            _graph[i][j] = list_g._graph[i][j];
        }
    }
    _size = list_g._size;
    _capacity = list_g._capacity;

    return *this;
}

MatrixGraph::~MatrixGraph() {
    std::cout << "destructor ~MatrixGraph\n";
    for (size_t count_col = 0; count_col < _capacity; ++count_col) {
        delete[] _graph[count_col];
    }
    delete[] _graph;
}

void MatrixGraph::AddEdge(size_t from, size_t to) {
    // провекра на отрицательные
    auto ULONG_MAX;
    if (from == ULONG_MAX || to == ULONG_MAX) {
        std::cout << "error input: can't be negative\n";
        return;
    }
    //Проверка на длину ребра и если мало увеличиваем массив и емкость
    if (from >= _capacity || to >= _capacity) {
        //Увеличиваем размер на 1 из за принимаемых параметров от 0
        std::size_t max_from = std::max(_capacity, from + 1);
        std::size_t max_to = std::max(_capacity, to + 1);
        resize(std::max(max_from, max_to));
    }
    //Проверка на длину ребра и если мало увеличиваем рабочий размер массива
    if (from >= _size || to >= _size) {
        std::size_t max_from = std::max(_size, from + 1);
        std::size_t max_to = std::max(_size, to + 1);
        _size = std::max(max_from, max_to);
    }

    //Соединяем вершины от from до to
    //(индекс строки массива - номер вершины хвоста)
    //(индекс колонки массива - номер вершины головы)
    // Например from->to
    _graph[from][to] = true;
    cache.status = true;
}

int MatrixGraph::VerticesCount() const {
    if (cache.status) {
        std::set<size_t> vertices_count;
        for (size_t row = 0; row < _size; ++row) {
            for (size_t col = 0; col < _size; ++col) {
                if (_graph[row][col] == true) {
                    vertices_count.insert(row);
                    vertices_count.insert(col);
                }
            }
        }
        cache.status = false;
        cache.vertices = vertices_count.size();
    }

    return cache.vertices;
}

void MatrixGraph::ShowGraph() const {
    std::cout << "  ";
    for (int head = 0; head < _size; ++head)
        std::cout << head;
    std::cout << std::endl;

    for (int i = 0; i < _size; ++i) {
        std::cout << i << ":";
        for (int j = 0; j < _size; ++j) {
            std::cout << _graph[i][j];

        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void MatrixGraph::GetNextVertices(size_t vertex, std::vector<size_t> &vertices) const {
    if (vertex > _size) {
        std::cout << "Incorect vertex" << std::endl;
        return;
    }

    for (size_t col = 0; col < _size; ++col) {
        if (_graph[vertex][col] == true) {
            vertices.push_back(col);
        }
    }
}

void MatrixGraph::GetPrevVertices(size_t vertex, std::vector<size_t> &vertices) const {
    if (vertex > _size) {
        std::cout << "Incorect vertex" << std::endl;
        return;
    }
    for (size_t row = 0; row < _size; ++row) {
        if (_graph[row][vertex] == true) {
            vertices.push_back(row);
        }
    }
}