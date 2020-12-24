#pragma once
#include "graph_form.h"
#include <vector>
using namespace std;

template <class EdgeT> class GraphMatrixForm : public GraphForm<EdgeT> {
    friend class EdgeIterator;
    bool directed;
public:
    vector<vector<EdgeT*>> matrix;        //������� ���������
    vector<vector<EdgeT*>> matrix_tmp1;  //temp ������� ���������
    vector<vector<EdgeT*>> matrix_tmp2;  //temp ������� ���������

    GraphMatrixForm(bool directed) : directed(directed) {}
    //������� � �������� ������ � ����
    bool InsertV(int index) {
        int size = matrix.size(); //����� ������
        //�������� ����� �������
        if (index < 0 || index > size) return false;
        //������ ����� ������ ������
        vector<EdgeT*> newLine;
        newLine.assign(size, NULL);
        //��������� ����� ������:
        matrix.insert(matrix.begin() + index, newLine);
        ++size;
        //��������� ����� �������:
        for (int i = 0; i < size; ++i)
            matrix[i].insert(matrix[i].begin() + index, (EdgeT*)NULL);
        return true;
    }
    bool DeleteV(int index) {
        int size = matrix.size(); //����� ������
        //�������� ����� �������
        if (index < 0 || index >= size) return false;
        //������� ������:
        matrix.erase(matrix.begin() + index);
        --size;
        //������� �������:
        for (int i = 0; i < size; i++)
            matrix[i].erase(matrix[i].begin() + index);
        return true;
    }
    bool InsertE(int v1, int v2, EdgeT* t) {
        int size = matrix.size(); //����� ������
        //�������� ����� �������
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;
        //����� ��� ����� ��� ����
        if (v1 == v2 || matrix[v1][v2] != NULL) return false;
        //��������� �����
        matrix[v1][v2] = t;
        return true;
    }
    bool DeleteE(int v1, int v2) {
        int size = matrix.size(); //����� ������
        //�������� ����� �������
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;
        //����� ���
        if (v1 == v2 || matrix[v1][v2] == NULL) return false;
        matrix[v1][v2] = NULL;
        return true;
    }
    //������� �������� � ��������� �� ������� ����
    int DeleteEsFromVertex(int index, bool directed) {
        int size = matrix.size(); //����� ������
        int deleted = 0;
        //�������� ����� �������
        if (index < 0 || index >= size) return 0;
        //������� ��������� � �������� ����
        for (int i = 0; i < size; i++) {
            if (matrix[i][index] != NULL) {
                delete matrix[i][index];
                matrix[i][index] = NULL;
                ++deleted;
                //������� ������������ �����
                if (directed == false)
                    matrix[index][i] = NULL;
            }
            if (matrix[index][i] != NULL) {
                delete matrix[index][i];
                matrix[index][i] = NULL;
                ++deleted;
            }
        }
        return deleted;
    }
    //�������� � ���������
    bool hasEdge(int v1, int v2) {
        int size = matrix.size(); //����� ������
        //�������� ����� �������
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            return false;
        if (v1 == v2) //�����
            return false;
        if (matrix[v1][v2] != NULL)
            return true;
        return false;
    }
    EdgeT* getEdge(int v1, int v2) {
        int size = matrix.size(); //����� ������
        //�������� ����� �������
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            throw 1;
        if (v1 == v2 || matrix[v1][v2] == NULL)//�����
            throw 1;
        return matrix[v1][v2];
    }

    //    ���������� ��������� ����
    class EdgeIterator {
        bool end;
        GraphMatrixForm* f;
    public:
        int curI, curJ;
        EdgeIterator(GraphMatrixForm* f) {
            this->f = f;
            begin();
        }
        bool begin() {
            for (int i = 0; i < f->matrix.size(); ++i)
                for (int j = 0; j < f->matrix.size(); ++j)
                    if (f->matrix[i][j]) {
                        curI = i;
                        curJ = j;
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
            for (int i = f->matrix.size() - 1; i >= 0; --i)
                for (int j = f->matrix.size() - 1; j >= 0; --j)
                    if (f->matrix[i][j]) {
                        curI = i;
                        curJ = j;
                        end = false;
                        return true;
                    }
            end = true;
            return false;
        }
        bool next() {
            if (end)
                return false;
            ++curJ;
            while (curI < f->matrix.size()) {
                while (curJ < f->matrix.size()) {
                    if (f->matrix[curI][curJ])
                        return true;
                    ++curJ;
                }
                ++curI;
                curJ = (f->directed ? 0 : curI + 1);
            }
            end = true;
            return false;
        }
        EdgeT* getEdge() {
            if (end)
                throw 1;
            if (!(f->matrix[curI][curJ]))
                throw 1;
            return f->matrix[curI][curJ];
        }
    };

//���������� ��������� ��������� ����

        class OutputEdgeIterator {
        int curI, curJ;
        bool end;
        GraphMatrixForm* f;
        public:
            OutputEdgeIterator(GraphMatrixForm* f, int vIndex) {
                this->f = f;
                curI = vIndex;
                begin();
            }
            bool begin() {
                for (curJ = 0; curJ < f->matrix.size(); ++curJ)
                    if (f->matrix[curI][curJ]) {
                        end = false;
                        return true;
                    }
                end = true;
                return false;
            }
            bool toend() {
                for (curJ = f->matrix.size() - 1; curJ >= 0; --curJ)
                    if (f->matrix[curI][curJ]) {
                        end = false;
                        return true;
                    }
                end = true;
                return false;
            }
            bool onEnd() {
                return end;
            }
            bool next() {
                if (end)
                    return false;
                ++curJ;
                while (curJ < f->matrix.size()) {
                    if (f->matrix[curI][curJ])
                        return true;
                    ++curJ;
                }
                end = true;
                return false;
            }
            EdgeT* getEdge() {
                if (end)
                    throw 1;
                return f->matrix[curI][curJ];
            }
    };
};
