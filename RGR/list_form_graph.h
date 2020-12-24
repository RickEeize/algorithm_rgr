#pragma once
#include "graph_form.h"
#include <vector>
#include <list>
using namespace std;

template <class EdgeT> class GraphListForm : public GraphForm<EdgeT> {
    //Элемент списка
    class Node {
    public:
        EdgeT* edge; //Само ребро
        int v2;      //Вторая вершина, которую ребро соединяет
    };
    bool directed;
    vector<list<Node>> edgeList; //Списки смежности
public:
    GraphListForm(bool directed) : directed(directed) {}
    //Вставка и удаление вершин и рёбер
    bool InsertV(int index) {
        int size = edgeList.size(); //Число вершин
        if (index < 0 || index > size) //Неверный номер вершины
            return false;
        //Создаём новый список смежности
        list<Node> newList;
        //Вставляем
        edgeList.insert(edgeList.begin() + index, newList);
        ++size;
        //Обновляем дескрипторы
        for (int i = 0; i < size; ++i)
            for (typename list<Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
                if ((*j).v2 >= index)//если текущая вершина имеет больший номер, чем вставляемая,
                    ++((*j).v2);//то увеличиваем этот номер
        return true;
    }
    bool DeleteV(int index) {
        int size = edgeList.size(); //Число вершин
        if (index < 0 || index >= size)  //Неверный номер вершины
            return false;
        //Удаляем из списков записи о рёбрах
        for (int i = 0; i < size; ++i)
            for (typename list<Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
                if ((*j).v2 == index) {
                    edgeList[i].erase(j);
                    break;
                }
        //Удаляем список смежности
        edgeList.erase(edgeList.begin() + index);
        --size;
        //Обновляем дескрипторы
        for (int i = 0; i < size; ++i)
            for (typename list<Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
                if ((*j).v2 > index)//если текущая вершина имеет больший номер, чем удаляемая,
                    --((*j).v2);//то уменьшить этот номер
        return true;
    }
    bool InsertE(int v1, int v2, EdgeT* t) {
        int size = edgeList.size(); //Число вершин
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)//Неверный номер вершины
            return false;
        if (v1 == v2 || hasEdge(v1, v2))  //Петля или ребро уже есть
            return false;
        //Вставляем ребро
        Node node;
        node.edge = t;
        node.v2 = v2;
        edgeList[v1].push_front(node);
        return true;
    }
    bool DeleteE(int v1, int v2) {
        int size = edgeList.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            return false;
        //Ребра нет
        if (v1 == v2 || hasEdge(v1, v2) == false)
            return false;
        //Удаляем ребро
        for (typename list<Node>::iterator j = edgeList[v1].begin(); j != edgeList[v1].end(); ++j)
            if ((*j).v2 == v2) {
                edgeList[v1].erase(j);
                break;
            }
        return true;
    }
    //Удалить входящие и исходящие из вершины рёбра
    int DeleteEsFromVertex(int index, bool directed) {
        int size = edgeList.size(); //Число вершин
        int deleted = 0;
        //Неверный номер вершины
        if (index < 0 || index >= size)
            return 0;
        //Удаляем связанные с вершиной рёбра
        for (int i = 0; i < size; ++i)
            for (typename list<Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
                if ((*j).v2 == index) {
                    delete (*j).edge;
                    edgeList[i].erase(j);
                    ++deleted;
                    //Стираем симметричное ребро
                    if (directed == false)
                        for (typename list<Node>::iterator k = edgeList[index].begin(); k != edgeList[index].end(); ++k)
                            if ((*k).v2 == i) {
                                edgeList[index].erase(k);
                                break;
                            }
                    break;
                }
        if (directed == true) {
            for (typename list<Node>::iterator z = edgeList[index].begin(); z != edgeList[index].end(); ++z) {
                delete (*z).edge;
                deleted++;
            }
        }
        return deleted;
    }
    //Проверка и получение
    bool hasEdge(int v1, int v2) {
        int size = edgeList.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            return false;
        //Петля
        if (v1 == v2)
            return false;
        for (typename list<Node>::iterator j = edgeList[v1].begin(); j != edgeList[v1].end(); ++j)
            if ((*j).v2 == v2)
                return true;
        return false;
    }
    EdgeT* getEdge(int v1, int v2) {
        int size = edgeList.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            throw 1;
        //Петля
        if (v1 == v2)
            throw 1;
        for (typename list<Node>::iterator j = edgeList[v1].begin(); j != edgeList[v1].end(); ++j)
            if ((*j).v2 == v2)
                return (*j).edge;
        throw 1;
    }
    //Итератор рёбер
    class EdgeIterator {
        int curI;
        typename list<typename GraphListForm<EdgeT>::Node>::iterator curJ;
        bool end;
        GraphListForm* f;
    public:
        EdgeIterator(GraphListForm* f) {
            this->f = f;
        }
        //Установить итератор рёбер на начальное ребро
        bool begin() {
            for (curI = 0; curI < f->edgeList.size(); ++curI)
                for (curJ = f->edgeList[curI].begin(); curJ != f->edgeList[curI].end(); ++curJ)
                    if ((*curJ).edge) {
                        end = false;
                        return true;
                    }
            end = true;
            return false;
        }
        bool onEnd() {
            return end;
        }
        //Установить итератор рёбер на конечное ребро
        bool toend() {
            typename list<typename GraphListForm<EdgeT>::Node>::iterator prev_curJ;
            for (curI = 0; curI < f->edgeList.size(); ++curI) {
                for (curJ = f->edgeList[curI].begin(); curJ != f->edgeList[curI].end(); ++curJ) {
                    if ((*curJ).edge)
                        prev_curJ = curJ;
                    if (!(*prev_curJ).edge) {
                        end = true;
                        return false;
                    }
                    else {
                        end = false;
                        curJ = prev_curJ;
                        return true;
                    }
                }
            }
        };
        //Переход к следующей позиции
        bool next() {
            if (end)
                return false;
            ++curJ;
            while (curI < f->edgeList.size()) {
                while (curJ != f->edgeList[curI].end()) {
                    if ((*curJ).edge && (f->directed || !f->directed && (*curJ).v2 > curI))
                        return true;
                    ++curJ;
                }
                ++curI;
                if (curI < f->edgeList.size())
                    curJ = f->edgeList[curI].begin();
            }
            end = true;
            return true;
        }
        EdgeT* getEdge() {
            if (end)
                throw 1;
            return (*curJ).edge;
        }
    };

    //Реализация итератора исходящих рёбер

    class OutputEdgeIterator {
        int curI;
        typename list<typename GraphListForm<EdgeT>::Node>::iterator curJ;
        bool end;
        GraphListForm* f;
    public:
        OutputEdgeIterator(GraphListForm* f, int vIndex) {
            this->f = f;
            curI = vIndex;
            begin();
        }
        bool begin() {
            for (curJ = f->edgeList[curI].begin(); curJ != f->edgeList[curI].end(); ++curJ)
                if ((*curJ).edge) {
                    end = false;
                    return true;
                }
            end = true;
            return false;
        }
        bool onEnd() {
            return end;
        }
        bool toend() {
            typename list<typename GraphListForm<EdgeT>::Node>::iterator prev_curJ;
            for (curJ = f->edgeList[curI].begin(); curJ != f->edgeList[curI].end(); ++curJ)
                if ((*curJ).edge)
                    prev_curJ = curJ;
            if (!(*prev_curJ).edge) {
                end = true;
                return false;
            }
            else {
                end = false;
                curJ = prev_curJ;
                return true;
            };
        }
        bool next() {
            if (end)
                return false;
            ++curJ;
            while (curJ != f->edgeList[curI].end()) {
                if ((*curJ).edge)
                    return true;
                ++curJ;
            }
            end = true;
            return true;
        }
        EdgeT* getEdge() {
            if (end)
                throw 1;
            return (*curJ).edge;
        }
    };

};