#pragma once

template <class VertexT, class WeightT, class DataT> class Edge {
    VertexT* v1, * v2;   //Вершины, которые соединяет ребро
    WeightT weight;     //Вес
    DataT data;         //Данные ребра
    bool weightSet, dataSet;
public:
    //Конструкторы
    Edge(VertexT* v1, VertexT* v2) :
        v1(v1),
        v2(v2),
        weightSet(false),
        weight(0),
        dataSet(false) {}
    Edge(VertexT* v1, VertexT* v2, WeightT weight) :
        v1(v1),
        v2(v2),
        weight(weight),
        weightSet(true),
        dataSet(false) {}
    Edge(VertexT* v1, VertexT* v2, WeightT weight, DataT data) :
        v1(v1),
        v2(v2),
        weight(weight),
        data(data),
        weightSet(true),
        dataSet(true) {}
    //Установка и получение веса и данных
    void setWeight(WeightT weight) {
        this->weight = weight;
        weightSet = true;
    }
    void setData(DataT data) {
        this->data = data;
        dataSet = true;
    }
    WeightT getWeight() {
        return weight;
    }
    DataT getData() {
        return data;
    }
    VertexT* getVertex1() {
        return v1;
    };
    VertexT* getVertex2() {
        return v2;
    };
    bool isWeightSet() {
        return weightSet;
    }
    bool isDataSet() {
        return dataSet;
    }
};