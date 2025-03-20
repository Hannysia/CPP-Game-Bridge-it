#pragma once
#include "pch.h"
#include "cmath"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drowings;

ref class Dot {
protected:
    int dotId;
    int x;
    int y;
    Brush^ c;
public:
    //конструктор за замовчуванням
    Dot() {
        dotId = 1;
        x = 1;
        y = 1;
        с
    }
    //Ініціалізуючий конструктор
    Dot(int id, int x1, int y1) {
        dotId = id;
        x = x1;
        y = y1;
    }
    //Копіюючий конструктор
    Dot(Dot^ d) {
        dotId = d->dotId;
        x = d->x;
        y = d->y;
    }
    //Функція для обчислення відстані між точками
    double Distance(Dot^ d1) {
        double dist;
        dist = sqrt(pow((x - d1->x), 2) + pow((y - d1->y), 2));
        return dist;
    }
    void Print() {
        Console::WriteLine("Id of the dot: " + dotId);
        Console::WriteLine("Coordinate x: " + x);
        Console::WriteLine("Coordinate y: " + y);
    }
};

int main(array<System::String^>^ args)
{
    Dot^ A = gcnew Dot(1, 1, 1);
    Dot^ B = gcnew Dot(2, 1, 2);
    Dot^ C = gcnew Dot(B);
    double distance = A->Distance(B);
    Console::WriteLine(distance);
    C->Print();


    return 0;
}