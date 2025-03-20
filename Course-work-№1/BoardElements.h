#include "cmath"
#include "typeinfo"
#include "time.h"


using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Collections::Generic;


ref class BoardElements {
};

ref class Dot : public BoardElements {
private:
    int dotId;
    double x;
    double y;
    Brush^ c;
    bool connection;
    double r;
public:
    //конструктор за замовчуванням
    Dot() {
        dotId = 1;
        x = 1;
        y = 1;
        c = gcnew SolidBrush(Color::Green);
        connection = false; //з'єднаний - значить true
        r = 1;
    }
    //Ініціалізуючий конструктор
    Dot(int id, double x1, double y1, Brush^ color, bool tf, double rad) {
        dotId = id;
        x = x1;
        y = y1;
        c = color;
        connection = tf;
        r = rad;
    }
    //Копіюючий конструктор
    Dot^ operator=(Dot^ d) {
        if (this != d) { //перевірка на чи не присвоюється об'єкт сам собі 
            this->dotId = d->dotId;
            this->x = d->x;
            this->y = d->y;
            this->c = d->c;
            this->connection = d->connection;
            this->r = d->r;
        }
        return this;
    }
    Dot(Dot^ d) {
        dotId = d->dotId;
        x = d->x;
        y = d->y;
        c = d->c;
        connection = d->connection;
        r = d->r;
    }
    //Конструткор з двома параметрами 
    Dot(double x1, double y1) {
        x = x1;
        y = y1;
    }
    //Функція для обчислення відстані між точками
    double Distance(Dot^ d1) {
        double dist;
        dist = sqrt(pow((x - d1->x), 2) + pow((y - d1->y), 2));
        return dist;
    }
    //Функція, що малює точку на дошці
    void DrawDot(Graphics^ g) {
        g->FillEllipse(c, (float)x, (float)y, r, r);
    }
    int getId() { return dotId; }
    double getX() { return x; }
    double getY() { return y; }
    Brush^ getColor() { return c; }
    bool getConnection() { return connection; }
    void setConnection(bool connect) {
        connection = connect;
    }

};
ref class Bridge : BoardElements {
private:
    Dot^ d1;
    Dot^ d2;
    double length;
    Brush^ colorBridge;

    //Функція для перевірки довжини моста
    bool CheckLength() {
        if (length >= 50 && length <= 150) {
            return true;
        }
        else { return false; }
    }
    //Функція для розрахунку довжини моста
    double CalcLength() {
        double x1, x2, y1, y2;
        x1 = d1->getX();
        x2 = d2->getX();
        y1 = d1->getY();
        y2 = d2->getY();
        length = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
        return length;
    }
public:
    //Ініціалізуючий конструктор
    Bridge(Dot^ D1, Dot^ D2) {
        d1 = D1;
        d2 = D2;
        colorBridge = D1->getColor();
        if (d1->getColor() == d2->getColor()) {
            length = CalcLength();
            bool checking_length = CheckLength();
            if (checking_length != true) {
                delete d1;
                delete d2;
            }
        }
    }
    //Функція для побудови моста між двома точками
    void DrawBridge(Graphics^ d) {
        bool connect1, connect2;
        Brush^ color1;
        Brush^ color2;
        connect1 = d1->getConnection();
        connect2 = d2->getConnection();
        color1 = d1->getColor();
        color2 = d2->getColor();
        bool checkingLength = CheckLength();
        if (color1 == color2 && connect1 == false && connect2 == false && checkingLength == true) {
            float lineWidth = 5.0f;
            Pen^ p = gcnew Pen(color1, lineWidth);
            Point from(d1->getX() + 7, d1->getY() + 6);
            Point to(d2->getX() + 7, d2->getY() + 6);
            d->DrawLine(p, from, to);
        }
        else {
            delete d1;
            delete d2;
        }
    }
    Brush^ getColor() {
        return colorBridge;
    }

    array<Dot^>^ getDots()
    {
        array<Dot^>^ dot = gcnew array<Dot^>(2);
        dot[0] = d1;
        dot[1] = d2;

        return dot;
    }
    Dot^ getFirstDot() {
        return d1;
    }
    Dot^ getSecondDot() {
        return d2;
    }
};

ref class Board {
    ref struct Element {
        BoardElements^ item;
        Element^ next;
    };
private:
    Element^ first;
    double width;
    double length;
    PictureBox^ PiB;
public:
    Board(PictureBox^ pb) {
        if (pb != nullptr) {
            PiB = pb;
            PiB->BackColor = Color::FromArgb(255, 255, 233);
            width = PiB->Width;
            length = PiB->Height;
        }
    }
    void Add(BoardElements^ be) {
        Element^ temp = gcnew Element;
        temp->item = be;

        if (temp->item->GetType() == Dot::typeid) {
            Dot^ dot = dynamic_cast<Dot^>(temp->item);
            temp->next = first;
            first = temp;
        }
        else if (temp->item->GetType() == Bridge::typeid) {
            Bridge^ bridge = dynamic_cast<Bridge^>(temp->item);
            temp->next = first;
            first = temp;
        }
    }
    void Draw() {
        Bitmap^ bt;
        bt = gcnew Bitmap(PiB->Width, PiB->Height);
        Graphics^ g = Graphics::FromImage(bt);
        g->Clear(PiB->BackColor);
        Element^ temp = first;
        while (temp != nullptr) {

            if (temp->item->GetType() == Dot::typeid) {
                Dot^ dot = dynamic_cast<Dot^>(temp->item);
                dot->DrawDot(g);
            }
            else if (temp->item->GetType() == Bridge::typeid) {
                Bridge^ bridge = dynamic_cast<Bridge^>(temp->item);
                bridge->DrawBridge(g);
            }
            temp = temp->next;
        }
        PiB->Image = bt;
    }
    List<Dot^>^ FindSecDot(Color c)
    {
        List<Dot^>^ myList = gcnew List<Dot^>();

        Element^ temp = first;
        while (temp != nullptr) {
            if (temp->item->GetType() == Dot::typeid) {
                Dot^ dot = dynamic_cast<Dot^>(temp->item);
                if (c == Color::Maroon) {

                    if (dot->getConnection() == true && dot->getColor()->Equals(Color::Maroon)) {
                        myList->Add(dot);
                    }
                }
                else if (c == Color::FromArgb(12, 125, 106)) {
                    if (dot->getConnection() == true && dot->getColor()->Equals(Color::FromArgb(12, 125, 106))) {
                        myList->Add(dot);
                    }
                }
            }
            temp = temp->next;
        }

        return myList;
    }
    bool FindBridge(Dot^ fm, Dot^ t) {
        Element^ temp = first;
        while (temp != nullptr) {
            if (temp->item->GetType() == Bridge::typeid) {
                Bridge^ bridge = dynamic_cast<Bridge^>(temp->item);

                array<Dot^>^ dots = bridge->getDots();

                if (((fm->getId() == dots[0]->getId()) && (t->getId() == dots[1]->getId())) || ((fm->getId() == dots[1]->getId()) && (t->getId() == dots[0]->getId()))) {

                    return true;
                }

            }
            temp = temp->next;
        }
        return false;
    }
    
};
bool CheckLength(Dot^ d1, Dot^ d2) {
    double x1, x2, y1, y2;
    x1 = d1->getX();
    x2 = d2->getX();
    y1 = d1->getY();
    y2 = d2->getY();
    if (abs(x1 - x2) == 75 && abs(y1 - y2) == 75) { return true; }
    else { return false; }
}
int ChooseFirst() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int randomValue = rand() % 2;
    return  randomValue;
}
int CalcLength(Dot^ d1, Dot^ d2) {
    double x1, x2, y1, y2;
    x1 = d1->getX();
    x2 = d2->getX();
    y1 = d1->getY();
    y2 = d2->getY();
    int length = int(sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)));
    return length;
}