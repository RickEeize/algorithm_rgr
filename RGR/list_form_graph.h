#pragma once
#include "graph_form.h"
#include <vector>
#include <list>
using namespace std;

template <class EdgeT> class GraphListForm : public GraphForm<EdgeT> {
    //������� ������
    class Node {
    public:
        EdgeT* edge; //���� �����
        int v2;      //������ �������, ������� ����� ���������
    };
    bool directed;
    vector<list<Node>> edgeList; //������ ���������
public:
    GraphListForm(bool directed) : directed(directed) {}
    //������� � �������� ������ � ����
    bool InsertV(int index) {
        int size = edgeList.size(); //����� ������
        if (index < 0 || index > size) //�������� ����� �������
            return false;
        //������ ����� ������ ���������
        list<Node> newList;
        //���������
        edgeList.insert(edgeList.begin() + index, newList);
        ++size;
        //��������� �����������
        for (int i = 0; i < size; ++i)
            for (typename list<Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
                if ((*j).v2 >= index)//���� ������� ������� ����� ������� �����, ��� �����������,
                    ++((*j).v2);//�� ����������� ���� �����
        return true;
    }
    bool DeleteV(int index) {
        int size = edgeList.size(); //����� ������
        if (index < 0 || index >= size)  //�������� ����� �������
            return false;
        //������� �� ������� ������ � �����
        for (int i = 0; i < size; ++i)
            for (typename list<Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
                if ((*j).v2 == index) {
                    edgeList[i].erase(j);
                    break;
                }
        //������� ������ ���������
        edgeList.erase(edgeList.begin() + index);
        --size;
        //��������� �����������
        for (int i = 0; i < size; ++i)
            for (typename list<Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
                if ((*j).v2 > index)//���� ������� ������� ����� ������� �����, ��� ���������,
                    --((*j).v2);//�� ��������� ���� �����
        return true;
    }
    bool InsertE(int v1, int v2, EdgeT* t) {
        int size = edgeList.size(); //����� ������
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)//�������� ����� �������
            return false;
        if (v1 == v2 || hasEdge(v1, v2))  //����� ��� ����� ��� ����
            return false;
        //��������� �����
        Node node;
        node.edge = t;
        node.v2 = v2;
        edgeList[v1].push_front(node);
        return true;
    }
    bool DeleteE(int v1, int v2) {
        int size = edgeList.size(); //����� ������
        //�������� ����� �������
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            return false;
        //����� ���
        if (v1 == v2 || hasEdge(v1, v2) == false)
            return false;
        //������� �����
        for (typename list<Node>::iterator j = edgeList[v1].begin(); j != edgeList[v1].end(); ++j)
            if ((*j).v2 == v2) {
                edgeList[v1].erase(j);
                break;
            }
        return true;
    }
    //������� �������� � ��������� �� ������� ����
    int DeleteEsFromVertex(int index, bool directed) {
        int size = edgeList.size(); //����� ������
        int deleted = 0;
        //�������� ����� �������
        if (index < 0 || index >= size)
            return 0;
        //������� ��������� � �������� ����
        for (int i = 0; i < size; ++i)
            for (typename list<Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
                if ((*j).v2 == index) {
                    delete (*j).edge;
                    edgeList[i].erase(j);
                    ++deleted;
                    //������� ������������ �����
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
    //�������� � ���������
    bool hasEdge(int v1, int v2) {
        int size = edgeList.size(); //����� ������
        //�������� ����� �������
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            return false;
        //�����
        if (v1 == v2)
            return false;
        for (typename list<Node>::iterator j = edgeList[v1].begin(); j != edgeList[v1].end(); ++j)
            if ((*j).v2 == v2)
                return true;
        return false;
    }
    EdgeT* getEdge(int v1, int v2) {
        int size = edgeList.size(); //����� ������
        //�������� ����� �������
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            throw 1;
        //�����
        if (v1 == v2)
            throw 1;
        for (typename list<Node>::iterator j = edgeList[v1].begin(); j != edgeList[v1].end(); ++j)
            if ((*j).v2 == v2)
                return (*j).edge;
        throw 1;
    }
    //�������� ����
    class EdgeIterator {
        int curI;
        typename list<typename GraphListForm<EdgeT>::Node>::iterator curJ;
        bool end;
        GraphListForm* f;
    public:
        EdgeIterator(GraphListForm* f) {
            this->f = f;
        }
        //���������� �������� ���� �� ��������� �����
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
        //���������� �������� ���� �� �������� �����
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
        //������� � ��������� �������
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

    //���������� ��������� ��������� ����

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