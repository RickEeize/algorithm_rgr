#pragma once

using namespace std;

template <class EdgeT> class GraphForm {
public:
    //������� � �������� ������ � ����
    virtual bool InsertV(int index) = 0;
    virtual bool DeleteV(int index) = 0;
    virtual bool InsertE(int v1, int v2, EdgeT* t) = 0;
    virtual bool DeleteE(int v1, int v2) = 0;
    //������� �������� � ��������� �� ������� ����
    virtual int DeleteEsFromVertex(int index, bool directed) = 0;
    //�������� � ���������
    virtual bool hasEdge(int v1, int v2) = 0;
    virtual EdgeT* getEdge(int v1, int v2) = 0;
};