﻿#include <iostream>
#include <vector>
#include "graph.h"
#include "vertex.h"
#include "edge.h"

int main() {
    int menu;
    bool on = false;        //Итератор исход реб
    Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>* graph = nullptr;
    Vertex<string, int>* vertex = nullptr;
    Edge<Vertex<string, int>, int, int>* edge = nullptr;

    Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::VertexIterator* vIt = nullptr;
    Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::EdgeIterator* eIt = nullptr;
    Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::OutputEdgeIterator* oIt = nullptr;
    Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::Euler* eIl = nullptr;
    Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::Bellman_ford* BF = nullptr;

    setlocale(0, "Rus");

    cout << "1. Создать пустой L-граф с нулевым числом вершин и ребер" << endl;
    cout << "2. Создать граф с V вершинами, без ребер, типа D, формы представления F" << endl;
    cout << "3. Создать граф с V вершинами, с E случайными ребрами, типа D , формы F" << endl;
    cout << "4. Выход" << endl;
    while (true) {
        cout << "Выберите операцию: ";
        cin >> menu;
        switch (menu) {
        case 1: {            //Создать пустой L-граф с нулевым числом вершин и ребер
            graph = new Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>();
            vIt = new Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::VertexIterator(*graph);
            eIt = new Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::EdgeIterator(*graph);
            cout << endl << "Граф создан" << endl;
            break;
        };
        case 2: {            //Создать граф с V вершинами, без ребер, типа D, формы представления F
            int tmp1, tmp2, tmp3;
            cout << "Введите количество вершин: ";
            cin >> tmp1;
            cout << "Ориентированный ли граф (0 - нет, 1 - да): ";
            cin >> tmp2;
            if (tmp2 == 1) on = true;
            cout << "Форму графа (0 - список, 1 - матрица): ";
            cin >> tmp3;
            graph = new Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>(tmp1, tmp2, tmp3);
            vIt = new Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::VertexIterator(*graph);
            eIt = new Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::EdgeIterator(*graph);
            cout << endl << "Граф создан" << endl;
            break;
        };
        case 3: {            //Создать граф с V вершинами, с E случайными ребрами, типа D , формы F
            int tmp1, tmp2, tmp3, tmp4;
            cout << "Введите количество вершин: ";
            cin >> tmp1;
            cout << "Введите количество ребер: ";
            cin >> tmp2;
            cout << "Ориентированный ли граф (0 - нет, 1 - да): ";
            cin >> tmp3;
            if (tmp3 == 1) on = true;
            cout << "Форму графа (0 - список, 1 - матрица): ";
            cin >> tmp4;
            graph = new Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>(tmp1, tmp2, tmp3, tmp4);
            vIt = new Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::VertexIterator(*graph);
            eIt = new Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::EdgeIterator(*graph);
            cout << endl << "Граф создан" << endl;
            break;
        };
        case 4: {            //выход
            return 0;
        };
        default: {
            cout << "Ошибка ввода" << endl;
        };
        }
        break;
    }

    while (true) {
        cout << "0. Распечатать граф" << endl;
        cout << "1. Опрос числа вершин в графе" << endl;
        cout << "2. Опрос числа ребер в графе" << endl;
        cout << "3. Опрос типа графа" << endl;
        cout << "4. Опрос формы представления графа" << endl;
        cout << "5. Опрос коэффициента насыщенности графа" << endl;
        cout << "6. Преобразовать граф к L-форме" << endl;
        cout << "7. Преобразовать граф к M-форме" << endl;
        cout << "8. Добавить вершину к графу" << endl;
        cout << "9. Удалить вершину из графа" << endl;
        cout << "10. Вставить ребро в граф" << endl;
        cout << "11. Удалить ребро из графа" << endl;

        cout << endl << "Операции над вершинами:" << endl;
        cout << "12. Прочитать данные о вершине" << endl;
        cout << "13. Записать данные о вершине" << endl;
        cout << "14. Перезаписать имя вершины" << endl;

        cout << endl << "Операции над ребрами:" << endl;
        cout << "15. Прочитать вес ребра" << endl;
        cout << "16. Прочитать данные о ребре" << endl;
        cout << "17. Записать данные о ребре" << endl;
        cout << "18. Записать вес ребра" << endl;

        cout << endl << "Итератор вершин:" << endl;
        cout << "19. Установить итератор вершин на начальную вершину" << endl;
        cout << "20. Установить итератор вершин на конечную вершину" << endl;
        cout << "21. Переход к следующей позиции" << endl;
        cout << "22. Прочитать вершину по текущей позиции итератора" << endl;
        cout << "23. Прочитать данные вершины по текущей позиции итератора" << endl;
        cout << "24. Записать данные вершины по текущей позиции итератора" << endl;
        cout << "25. Записать имя вершины по текущей позиции итератора" << endl;

        cout << endl << "Итератор ребер:" << endl;
        cout << "26. Установить итератор ребер на начальное ребро" << endl;
        cout << "27. Установить итератор ребер на конечное ребро" << endl;
        cout << "28. Переход к следующей позиции" << endl;
        cout << "29. Прочитать вершины ребра и вес по текущей позиции итератора" << endl;
        cout << "30. Прочитать данные ребра по текущей позиции итератора" << endl;
        cout << "31. Записать данные о ребре по текущей позиции итератора" << endl;
        cout << "32. Записать вес ребра по текущей позиции итератора" << endl;

        cout << endl << "33. Итератор исходящих ребер" << endl;

        cout << endl << "35. Двухпроходной Эйлеров цикл" << endl;

        cout << endl << "36. Алгоритм Беллмана - Форда" << endl;

        cout << endl << "40. Выход" << endl;

        cout << endl << "Выберите операцию: ";
        cin >> menu;
        switch (menu) {
        case 0: {
            graph->print_graph();
            break;
        };
        case 1: {
            cout << endl << "==============================================" << endl;
            cout << endl << "Число вершин в графе: " << graph->V() << endl;
            cout << endl << "==============================================" << endl;
            break;
        };
        case 2: {
            cout << endl << "==============================================" << endl;
            cout << endl << "Число ребер в графе: " << graph->E() << endl;
            cout << endl << "==============================================" << endl;
            break;
        };
        case 3: {
            cout << endl << "==============================================" << endl;
            cout << endl << "Тип графа (0 - неориентированный, 1 - ориентированный): " << graph->Directed() << endl;
            cout << endl << "==============================================" << endl;
            break;
        };
        case 4: {
            cout << endl << "==============================================" << endl;
            cout << endl << "Форма предстваления графа (0 - L-граф, 1 - M-граф): " << graph->Dense() << endl;
            cout << endl << "==============================================" << endl;
            break;
        };
        case 5: {
            cout << endl << "==============================================" << endl;
            cout << endl << "Коэффициент насыщенности: " << graph->K() << endl;
            cout << endl << "==============================================" << endl;
            break;
        };
        case 6: {
            graph->ToListGraph();
            cout << endl << "==============================================" << endl;
            cout << endl << "Граф преобразован" << endl;
            cout << endl << "==============================================" << endl;
            break;
        };
        case 7: {
            graph->ToMatrixGraph();
            cout << endl << "==============================================" << endl;
            cout << endl << "Граф преобразован" << endl;
            cout << endl << "==============================================" << endl;
            break;
        };
        case 8: {
            cout << endl << "==============================================" << endl;
            if (graph->InsertV()) cout << endl << "Вершина добавлена в граф" << endl;
            else cout << endl << "Вершина не добавлена в граф" << endl;
            cout << endl << "==============================================" << endl;
            break;
        };
        case 9: {
            string v1;
            cout << "Введите удаляемую вершину: ";
            cin >> v1;
            cout << endl << "==============================================" << endl;
            cout << endl << "Вершина удалена (1 - да, 0 - нет): " << graph->DeleteV(v1) << endl;
            cout << endl << "==============================================" << endl;
            break;
        }
        case 10: {
            string v1, v2;
            bool tmp;
            cout << "Введите вершину, из которой выходит ребро: ";
            cin >> v1;
            cout << "Введите вершину, в которую входит ребро: ";
            cin >> v2;
            cout << endl << "==============================================" << endl;
            cout << endl << "Ребро добавлено в граф (1 - да, 0 - нет): " << graph->InsertE(v1, v2) << endl;
            cout << endl << "==============================================" << endl;
            break;
        };
        case 11: {
            string v1, v2;
            cout << "Введите вершину для удаления 1: ";
            cin >> v1;
            cout << "Введите вершину для удаления 2: ";
            cin >> v2;
            cout << endl << "==============================================" << endl;
            cout << endl << "Ребро удалено (1 - да, 0 - нет): " << graph->DeleteE(v1, v2) << endl;
            cout << endl << "==============================================" << endl;
            break;
        };

               //-------------------------------------------------------
               //Операции над вершинами
        case 12: {            //Прочитать данные о вершине
            int tmp;
            string v;
            cout << "Введите имя вершины: ";
            cin >> v;
            cout << endl << "==============================================" << endl;
            tmp = graph->read_data_vertex(v);
            if (tmp != -1) cout << endl << "Данные вершины: " << tmp << endl;
            cout << endl << "==============================================" << endl;
            break;
        };
        case 13: {            //Записать данные о вершине
            int tmp;
            string v;
            cout << "Введите имя вершины: ";
            cin >> v;
            cout << "Введите данные: ";
            cin >> tmp;
            cout << endl << "==============================================" << endl;
            cout << endl << "Данные о вершине записаны (1 - да, 0 - нет): " << graph->write_data_vertex(v, tmp) << endl;
            cout << endl << "==============================================" << endl;
            break;
        };
        case 14: {            //Записать новое имя вершины
            string v1, v2;
            cout << "Введите старое имя вершины: ";
            cin >> v1;
            cout << "Введите новое имя: ";
            cin >> v2;
            cout << endl << "==============================================" << endl;
            cout << endl << "Имя вершины перезаписано (1 - да, 0 - нет): " << graph->write_name_vertex(v1, v2) << endl;
            cout << endl << "==============================================" << endl;
            break;
        };

               //-------------------------------------------------------
               //Операции над ребрами
        case 15: {            //Прочитать вес ребра
            int tmp;
            string v1, v2;
            cout << "Введите имя исходящей вершины: ";
            cin >> v1;
            cout << "Введите имя входящей вершины: ";
            cin >> v2;
            cout << endl << "==============================================" << endl;
            tmp = graph->read_weight_edge(v1, v2);
            if (tmp != -1) cout << endl << "Вес ребра: " << tmp << endl;
            cout << endl << "==============================================" << endl;
            break;
        };
        case 16: {            //Прочитать данные о ребре
            int tmp;
            string v1, v2;
            cout << "Введите имя исходящей вершины: ";
            cin >> v1;
            cout << "Введите имя входящей вершины: ";
            cin >> v2;
            cout << endl << "==============================================" << endl;
            tmp = graph->read_data_edge(v1, v2);
            if (tmp != -1) cout << endl << "Данные ребра: " << tmp << endl;
            cout << endl << "==============================================" << endl;
            break;
        };
        case 17: {            //Записать данные о ребре
            int tmp;
            bool tmp1;
            string v1, v2;
            cout << "Введите имя исходящей вершины: ";
            cin >> v1;
            cout << "Введите имя входящей вершины: ";
            cin >> v2;
            cout << "Введите данные: ";
            cin >> tmp;
            cout << endl << "==============================================" << endl;
            tmp1 = graph->write_data_edge(v1, v2, tmp);
            if (tmp1 == true)    cout << endl << "Данные о вершине записаны (1 - да, 0 - нет): " << tmp1 << endl;
            cout << endl << "==============================================" << endl;
            break;
        };
        case 18: {            //Записать вес ребра
            int tmp;
            bool tmp1;
            string v1, v2;
            cout << "Введите имя исходящей вершины: ";
            cin >> v1;
            cout << "Введите имя входящей вершины: ";
            cin >> v2;
            cout << "Введите вес: ";
            cin >> tmp;
            cout << endl << "==============================================" << endl;
            tmp1 = graph->write_weight_edge(v1, v2, tmp);
            if (tmp1 == true)    cout << endl << "Вес ребра перезаписан (1 - да, 0 - нет): " << tmp1 << endl;
            cout << endl << "==============================================" << endl;
            break;
        };

               //-------------------------------------------------------
               //Итератор вершин
        case 19: {                //Установить итератор вершин на начальную вершину
            cout << endl << "==============================================" << endl;
            cout << endl << "Итератор вершин графа установлен на первую вершину (1 - да, 0 - нет): " << vIt->begin() << endl;
            cout << endl << "==============================================" << endl;
            break;
        };
        case 20: {                //Установить итератор вершин на конечную вершину
            cout << endl << "==============================================" << endl;
            cout << endl << "Итератор вершин графа установлен на последнюю вершину (1 - да, 0 - нет): " << vIt->toend() << endl;
            cout << endl << "==============================================" << endl;
            break;
        };
        case 21: {                //Переход к следующей позиции
            bool tmp;
            cout << endl << "==============================================" << endl;
            tmp = ++ * vIt;
            if (tmp) cout << endl << "Итератор вершин графа установлен на следующую позицию (1 - да, 0 - нет): " << tmp << endl;
            cout << endl << "==============================================" << endl;
            break;
        };
        case 22: {                //Прочитать вершину по текущей позиции итератора
            string tmp;
            cout << endl << "==============================================" << endl;
            try {
                tmp = vIt->read_vertex();
            }
            catch (char* e) {
                cerr << endl << e << endl;
                cout << endl << "==============================================" << endl;
                break;
            }
            cout << endl << "Вершина на текущей позиции итератора: " << tmp << endl;
            cout << endl << "==============================================" << endl;
            break;
        };
        case 23: {                //Прочитать данные вершины по текущей позиции итератора
            int tmp;
            cout << endl << "==============================================" << endl;
            tmp = vIt->read_data_vertex();
            if (tmp != -1) cout << endl << "Данные вершины на текущей позиции итератора: " << tmp << endl;
            cout << endl << "==============================================" << endl;
            break;
        };
        case 24: {                //Записать данные о вершины по текущей позиции итератора
            int tmp;
            bool tmp2;
            cout << "Введите данные: ";
            cin >> tmp;
            cout << endl << "==============================================" << endl;
            tmp2 = vIt->write_data_vertex(tmp);
            if (tmp2) cout << endl << "Данные вершины записаны по текущей позиции итератора (1 - да): " << tmp2 << endl;
            cout << endl << "==============================================" << endl;
            break;
        };
        case 25: {                //Записать имя вершины по текущей позиции итератора
            string cur;
            bool tmp;
            cout << "Введите имя: ";
            cin >> cur;
            cout << endl << "==============================================" << endl;
            tmp = vIt->write_name_vertex(cur);
            if (tmp) cout << endl << "Имя вершины записано по текущей позиции итератора (1 - да): " << tmp << endl;
            cout << endl << "==============================================" << endl;
            break;
        };

               //-------------------------------------------------------
               //Итератор ребер
        case 26: {                //Установить итератор ребер на начальное ребро
            cout << endl << "==============================================" << endl;
            cout << endl << "Итератор установлен на начальное ребро (1 - д, 0 - нет): " << eIt->begin() << endl;
            cout << endl << "==============================================" << endl;
            break;
        };
        case 27: {                //Установить итератор ребер на конечное ребро
            cout << endl << "==============================================" << endl;
            cout << endl << "Итератор установлен на последнее ребро (1 - да, 0 - нет): " << eIt->toend() << endl;
            cout << endl << "==============================================" << endl;
            break;
        };
        case 28: {                //Переход к следующей позиции
            cout << endl << "==============================================" << endl;
            cout << endl << "Итератор ребер графа установлен на следующую позицию (1 - да, 0 - нет): " << ++ * eIt << endl;
            cout << endl << "==============================================" << endl;
            break;
        };
        case 29: {                //Прочитать вершины ребра и вес по текущей позиции итератора
            string tmp;
            cout << endl << "==============================================" << endl;
            try {
                tmp = eIt->read_edge();
            }
            catch (char* e) {
                cerr << endl << e << endl;
                cout << endl << "==============================================" << endl;
                break;
            }
            cout << endl << tmp << endl;
            cout << endl << "==============================================" << endl;
            break;
        };
        case 30: {                //Прочитать данные ребра по текущей позиции итератора
            int tmp;
            cout << endl << "==============================================" << endl;
            try {
                tmp = eIt->read_data_edge();
            }
            catch (char* e) {
                cerr << endl << e << endl;
                cout << endl << "==============================================" << endl;
                break;
            }
            cout << endl << "Данные ребра по текущей позиции итератора: " << tmp << endl;
            cout << endl << "==============================================" << endl;
            break;
        };
        case 31: {                //Записать данные о ребре по текущей позиции итератора
            int tmp;
            cout << "Введите данные: ";
            cin >> tmp;
            cout << endl << "==============================================" << endl;
            cout << endl << "Данные ребра записаны по текущей позиции итератора (1 - да, 0 - нет): " << eIt->write_data_edge(tmp) << endl;
            cout << endl << "==============================================" << endl;
            break;
        };
        case 32: {                //Записать вес ребра по текущей позиции итератора
            int tmp;
            cout << "Введите вес: ";
            cin >> tmp;
            cout << endl << "==============================================" << endl;
            cout << endl << "Вес ребра записан по текущей позиции итератора (1 - да, 0 - нет): " << eIt->write_weight_edge(tmp) << endl;
            cout << endl << "==============================================" << endl;
            break;
        };

               //-------------------------------------------------------
               //Итератор исходящих ребер
        case 33: {
            int tmp, tmp2;        //узел
            bool ex = false;            //выход
            cout << endl << "Введите веришну: ";
            cin >> tmp;
            oIt = new Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::OutputEdgeIterator(*graph, *graph->getVertex(tmp));

            while (true) {
                cout << endl << "Итератор исходящих ребер:" << endl;
                cout << "1. Установить итератор исходящих ребер на начальное ребро" << endl;
                cout << "2. Установить итератор исходящих ребер на конечное ребро" << endl;
                cout << "3. Переход к следующей позиции" << endl;
                cout << "4. Прочитать вершины ребра и вес по текущей позиции итератора" << endl;
                cout << "5. Прочитать данные ребра по текущей позиции итератора" << endl;
                cout << "6. Записать данные о ребре по текущей позиции итератора" << endl;
                cout << "7. Записать вес ребра по текущей позиции итератора" << endl;
                cout << "10. Вернуться в предыдущее меню" << endl;
                cout << endl << "Выберите операцию: ";
                cin >> tmp2;
                switch (tmp2) {
                case 1: {            //Установить итератор исходящих ребер на начальное ребро
                    cout << endl << "==============================================" << endl;
                    cout << endl << "Итератор исходящих ребер установлен на первое ребро (1 - да, 0 - нет): " << oIt->begin() << endl;
                    cout << endl << "==============================================" << endl;
                    break;
                };
                case 2: {            //Установить итератор исходящих ребер на конечное ребро
                    cout << endl << "==============================================" << endl;
                    cout << endl << "Итератор исходящих ребер установлен на последнее ребро (1 - да, 0 - нет): " << oIt->toend() << endl;
                    cout << endl << "==============================================" << endl;
                    break;
                };
                case 3: {            //Переход к следующей позиции
                    cout << endl << "==============================================" << endl;
                    cout << endl << "Итератор исходящих ребер установлен на следующую позицию (1 - да, 0 - нет): " << ++ * oIt << endl;
                    cout << endl << "==============================================" << endl;
                    break;
                };
                case 4: {            //Прочитать вершины ребра и вес по текущей позиции итератора
                    string tmp;
                    cout << endl << "==============================================" << endl;
                    try {
                        tmp = oIt->read_edge();
                    }
                    catch (char* e) {
                        cerr << endl << e << endl;
                        cout << endl << "==============================================" << endl;
                        break;
                    };
                    cout << endl << tmp << endl;
                    cout << endl << "==============================================" << endl;
                    break;
                };
                case 5: {            //Прочитать данные ребра по текущей позиции итератора
                    int tmp;
                    cout << endl << "==============================================" << endl;
                    try {
                        tmp = oIt->read_data_edge();
                    }
                    catch (char* e) {
                        cerr << endl << e << endl;
                        cout << endl << "==============================================" << endl;
                        break;
                    }
                    cout << endl << "Данные ребра по текущей позиции итератора: " << tmp << endl;
                    cout << endl << "==============================================" << endl;
                    break;
                };
                case 6: {            //Записать данные о ребре по текущей позиции итератора
                    int tmp;
                    cout << "Введите данные: ";
                    cin >> tmp;
                    cout << endl << "==============================================" << endl;
                    cout << endl << "Данные ребра записаны по текущей позиции итератора (1 - да, 0 - нет): " << oIt->write_data_edge(tmp) << endl;
                    cout << endl << "==============================================" << endl;
                    break;
                };
                case 7: {            //Записать вес ребра по текущей позиции итератора
                    int tmp;
                    cout << "Введите вес: ";
                    cin >> tmp;
                    cout << endl << "==============================================" << endl;
                    cout << endl << "Вес ребра записан по текущей позиции итератора (1 - да, 0 - нет): " << oIt->write_weight_edge(tmp) << endl;
                    cout << endl << "==============================================" << endl;
                    break;
                };
                case 10: {            //выход
                    ex = true;
                    break;
                };
                default: {
                    cout << "Ошибка ввода" << endl;
                };
                }
                if (ex) break;
            }
            break;
        }
        case 35: {                //формирование списка ребер неориентированного графа в порядке двухпроходного эйлерова цикла
            eIl = new Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::Euler(*graph);
            bool temp;
            cout << endl << "==============================================" << endl;
            temp = eIl->DFS();
            if (!temp) cout << endl << "Эйлеров цикл: " << temp << endl;
            cout << endl << "==============================================" << endl;
            break;
        }
        case 36: {                //определение центра взвешенного орграфа на основе алгоритма Беллмана - Форда
            BF = new Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::Bellman_ford(*graph);
            string temp;
            temp = BF->bellman_ford();
            cout << endl << "==============================================" << endl;
            cout << endl << "Беллман - Форд: " << temp << endl;
            cout << endl << "==============================================" << endl;
            break;
        }
        case 40: {                //выход
            return 0;
        };
               break;
        default: {
            cout << "Ошибка ввода" << endl;
        };
               break;
        }
    }
  
    return 0;
}
