#pragma once


template <class NameT, class DataT> class Vertex {
    NameT name;     //��� �������
    DataT data;     //������ �������
public:
    bool nameSet, dataSet;
    //������������
    Vertex() :
        nameSet(false),
        dataSet(false) {}
    Vertex(NameT name, DataT data) :
        name(name),
        data(data),
        nameSet(true),
        dataSet(true) {}
    //���������, ��������� ����� � ������
    void setName(NameT name) {
        this->name = name;
        nameSet = true;
    }
    void setData(DataT data) {
        this->data = data;
        dataSet = true;
    }
    NameT getName() {
        return name;
    }
    DataT getData() {
        return data;
    }
    bool isNameSet() {
        return nameSet;
    }
    bool isDataSet() {
        return dataSet;
    }
};

