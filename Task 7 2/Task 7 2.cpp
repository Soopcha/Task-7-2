#include <iostream>
using namespace std;


// Два варианта десертиков: торт и мороженко
struct Dessert
{
    Dessert* Next;   // Указатель на следующую структуру в списке.
    char Case;
    union // Различающиеся элементы вариантов: 
    {
        struct { char Smell[15], Filling[10]; long Layers; } Cake;
        struct { char Taste[40]; int numOfBalls; } IceCream;
    };
    char Name[40];
};
// Указатель начала списка - базы данных:
Dessert* DataBase = NULL;

// Ввод информации о десерте варианта cs :
Dessert inpDessertInf(char cs)
{
    Dessert dessert;
    if (dessert.Case == cs)
    { // Вводим элементы варианта для мороженка: 
        cout << "Taste: ";
        cin >> dessert.IceCream.Taste;
        cout << "number of balls: ";
        cin >> dessert.IceCream.numOfBalls;
    }
    else // Вводим элементы для квартирного варианта: 
    {
        cout << "Smell: "; cin >> dessert.Cake.Smell;
        cout << "Filling: "; cin >> dessert.Cake.Filling;
        cout << "Layers: "; cin >> dessert.Cake.Layers;
    } // Вводим общие элементы вариантов: 
    cout << "Name: "; cin >> dessert.Name;
    return dessert;
}
// Вывод информации о телефонном абоненте:
// Вывод информации о телефонном абоненте: 
void printDesser(Dessert dessert)
{
    if (dessert.Case) // Вариант - учреждение. 
    {
        cout << dessert.IceCream.Taste << " |";
        cout << dessert.IceCream.numOfBalls << " |";
    } // Вариант - квартира. 
    else cout << dessert.Cake.Smell << ' ' << dessert.Cake.Filling << " | " << dessert.Cake.Layers;
    cout << dessert.Name << endl;
}

/* Поиск в списке десерта с заданным порядковым номером num в списке
(нумеруем, начиная с 0):   */
Dessert* FoundDessertNum(int num)
{
    Dessert* p = DataBase;
    while (p != NULL && num--)   // Пока не конец списка и не найден номер,
        p = p->Next;            // продвигаем указатель вдоль списка.
    return p;   // Возвращаем указатель на найденный элемент или NULL,
}              /* если элемент не найден.
   Добавить нового абонента в список за номером num:   */
void AddDessert(int num, char cs)
{
    Dessert* q = new Dessert;// Создали новую структуру.
    *q = inpDessertInf(cs);    // Заполнили ее информацией.
    if (DataBase == NULL) num = 0;   // Если список пустой - добавим в начало.
    if (num)
    {
        Dessert* p = DataBase;      // Ищем указатель
        while (p->Next != NULL && --num) // на предыдущую структуру.
            p = p->Next;
        q->Next = p->Next; p->Next = q;// Вставляем новую структуру после *p
    }
    else { q->Next = DataBase; DataBase = q; } // Добавим в начало списка.
}
// Удалить абонента с номером num из списка:
void DeleteDessert(int num)
{
    Dessert* q;
    if (DataBase == NULL) return;
    if (num)
    {
        Dessert* p = DataBase;// Ищем указатель на предыдущую структуру.
        while (p->Next != NULL && --num) p = p->Next;
        if ((q = p->Next) != NULL) { p->Next = q->Next; delete q; }
    }                           // Удаляем начальный элемент:
    else { q = DataBase; DataBase = q->Next; delete q; }
}

void main()
{
    Dessert* p;   int i, j;
    while (1)
    {
        cout << " MENU:" << endl
            << "1. Data entry." << endl
            << "2. Output of information about the dessert." << endl
            << "3. Output of all desserts." << endl
            << "4. Delete information about the dessert." << endl
            << "5. Finish." << endl
            << ">";
        cin >> i;
        switch (i)
        {
        case 1: cout << "Choise number dessert: "; cin >> i;
            cout << "Choise (0-Ice Cream, 1-Cake): "; cin >> j;
            AddDessert(i, j); break;
        case 2: cout << "Choise number dessert: "; cin >> i;
            if ((p = FoundDessertNum(i)) != NULL)
                printDesser(*p);
            else cout << "ERROR!" << endl;
            break;
        case 3: p = DataBase; i = 0;
            while (p != NULL)
            {
                cout << "Number" << i++ << ':' << endl;
                printDesser(*p); p = p->Next;
            }
            break;
        case 4: cout << "Choise number dessert: "; cin >> i;
            DeleteDessert(i); break;
        case 5: while (DataBase != NULL)   // Удаляем весь список.
        {
            p = DataBase; DataBase = p->Next; delete p;
        }
              return;
        default: cout << "Repeat the input." << endl;
        }
    }
}
