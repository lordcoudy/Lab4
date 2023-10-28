#include <stdcpp.h>

using namespace std;

#pragma region Класс дроби
class Fraction {
public:
#pragma region Конструкторы
    Fraction(int numerator, int denominator, int mod) {
        setNumerator(numerator);
        setDenominator(denominator);
        setMod(mod);
        setOrder(*this, *this);
    }
    Fraction() {
        setNumerator(0);
        setDenominator(1);
        setMod(2);
        setOrder(*this, *this);
    }
#pragma endregion
#pragma region Методы
    void setNumerator(int numerator) {
        this->numerator = numerator;
    }
    void setDenominator(int denominator) {
        this->denominator = denominator;
    }
    int getNumerator() const {
        return numerator;
    }
    int getDenominator() const {
        return denominator;
    }
    void setMod(int mod) {
        this->mod = mod;
        updateIntegerView();
    }
    int getMod() const {
        return mod;
    }
    void updateIntegerView() {
        integerView = (numerator % mod * inverse(denominator) % mod) % mod;
    }
    int getIntegerView() const {
        return integerView;
    }
    Fraction getFractionView() {
        return this->backReverse(this->getIntegerView());
    }
    void setFractionView(int num){
        this->numerator = this->backReverse(num).numerator;
        this->denominator = this->backReverse(num).denominator;
    }
    void setOrder(Fraction &f1, Fraction &f2){
        order = max(max(f1.getNumerator(), f2.getNumerator()), max(f1.getDenominator(), f2.getDenominator()));
    }
    int getOrder(){
        return order;
    }
    void forceOrder(int order){
        this->order = order;
    }
#pragma endregion
#pragma region Операторы
    Fraction operator+(Fraction& other){
        Fraction result;
        result.setOrder(*this, other);
        result.setMod(this->getMod());
        result.integerView = (this->getIntegerView() + other.getIntegerView()) % this->getMod();
        result = result.getFractionView();
        return result;
    }
    Fraction operator-(Fraction& other) {
        // Perform subtraction logic here
        Fraction result;
        result.setOrder(*this, other);
        result.setMod(this->getMod());
        result = result.backReverse((this->getIntegerView() - other.getIntegerView()) % this->getMod());
        return result;
    }
    Fraction operator*(Fraction& other) {
        // Perform multiplication logic here
        Fraction result;
        result.setOrder(*this, other);
        result.setMod(this->getMod());
        result = result.backReverse((this->getIntegerView() * other.getIntegerView()) % this->getMod());
        return result;
    }
    Fraction operator/(Fraction& other) {
        // Perform division logic here
        Fraction result;
        result.setMod(this->getMod());
        result.setOrder(*this, other);
        result = result.backReverse((this->getIntegerView() / other.getIntegerView()) % this->getMod());
        return result;
    }
#pragma endregion

private:
#pragma region Переменные
    int numerator;
    int denominator;
    int mod;
    int order;
    int integerView;
#pragma endregion
#pragma region Приватные методы
    int inverse(int num) const
    {
        for (int i = 0; i < INT32_MAX; ++i) {
            int tmpNumber = num * i;
            if (tmpNumber % mod == 1) {
                return i;
            }
        }
        return num;
    }
    Fraction backReverse(int num)
    {
        pair<int, int> middle(mod, num);
        int left, tmp;
        pair<int, int> right(0, 1);
        do
        {
            left = floor(middle.first / middle.second);
            tmp = middle.first - left * middle.second;
            middle.first = middle.second;
            middle.second = tmp;
            tmp = right.first - left * right.second;
            right.first = right.second;
            right.second = tmp;
        } while ((abs(middle.second) > order || abs(right.second) > order) && middle.second != 0);
        Fraction result (middle.second, right.second, mod);
        return result;
    }
#pragma endregion
};
#pragma endregion Класс дроби

//Составить программу для определения точного скалярного произведения двух векторов,
// координаты векторов являются дроби Фарея.
// Привести когда получаются корректные результаты и возникает псевдопереполнение.
// Подумать о выборе модуля.

#pragma region Функции
void manualInput(int n, int tmpMod)
{
#pragma region Переменные и вектора
    int tmpNumerator, tmpDenominator, tmpOrder;
    vector<Fraction> v1(n), v2(n);
    Fraction res(0, 1, tmpMod);
#pragma endregion
#pragma region Ввод векторов и вычисление произведения
    for (int i = 0; i < n; ++i) {
        v1[i].setMod(tmpMod);
        v2[i].setMod(tmpMod);
        cout << "Введите числитель и знаменатель для вектора 1: ";
        cin >> tmpNumerator;
        cout << " / ";
        cin >> tmpDenominator;
        v1[i].setNumerator(tmpNumerator);
        v1[i].setDenominator(tmpDenominator);
        cout << "Введите числитель и знаменатель для вектора 2: ";
        cin >> tmpNumerator;
        cout << " / ";
        cin >> tmpDenominator;
        v2[i].setNumerator(tmpNumerator);
        v2[i].setDenominator(tmpDenominator);
        Fraction tmp = v1[i] * v2[i];
        res = res + tmp;
    }
#pragma endregion
    cout << "Скалярное произведение: " << res.getNumerator() << "/" << res.getDenominator() << "\nПредставление: " << res.getIntegerView() << endl;
}

void autoInput(int n, int tmpMod)
{
    int tmpNumerator, tmpDenominator, tmpOrder;
#pragma region Ввод порядка
    cout << "Введите порядок:" << endl;
    cin >> tmpOrder;
#pragma endregion
#pragma region Инициализация векторов
    vector<Fraction> v1(n), v2(n);              // v1 - вектор 1, v2 - вектор 2
    for (int i = 6; i < n + 6; ++i) {
        v1[i-6].setMod(tmpMod);
        v2[i-6].setMod(tmpMod);
        v1[i-6].forceOrder(tmpOrder);
        v2[i-6].forceOrder(tmpOrder);
        v1[i-6].setFractionView(i);
        v2[i-6].setFractionView(i);
        cout << v1[i-6].getNumerator() << "/" << v1[i-6].getDenominator() << "\n";
        cout << v2[i-6].getNumerator() << "/" << v2[i-6].getDenominator() << "\n";
    }
    Fraction res(0, 1, tmpMod);
#pragma endregion
    for (int i = 0; i < n; ++i) {
#pragma region Скалярное произведение
        Fraction tmp = v1[i] * v2[i];
        res = res + tmp;
#pragma endregion
    }
    cout << "Скалярное произведение: " << res.getNumerator() << "/" << res.getDenominator() << "\nПредставление: " << res.getIntegerView() << endl;
}
#pragma endregion Функции

int main() {
#pragma region Задание 1
#pragma region Переменные
    Fraction f(1, 3, 19);
#pragma endregion
#pragma region Проверки
    cout << f.getNumerator() << "/" << f.getDenominator() << endl;
    cout << f.getMod() << endl;
    cout << f.getIntegerView() << endl;
    cout << f.getFractionView().getNumerator() << "/" << f.getFractionView().getDenominator() << endl;
    f = (f + f);
    cout << f.getNumerator() << "/" << f.getDenominator() << endl;
    cout << f.getMod() << endl;
    cout << f.getIntegerView() << endl;
    cout << f.getFractionView().getNumerator() << "/" << f.getFractionView().getDenominator() << endl;
#pragma endregion
#pragma endregion Задание 1
#pragma region Задание 2
#pragma region Переменные
    int n, tmpMod, choice;
    bool exit = false;
#pragma endregion
#pragma region Ввод размерности
    cout << "Введите размерность векторов:" << endl;
    cin >> n;
#pragma endregion
#pragma region Ввод модуля
    cout << "Введите модуль:" << endl;
    cin >> tmpMod;
#pragma endregion
#pragma region Выбор
    while (!exit) {
        cout << "Выберите режим ввода векторов:\n1 - ручной ввод\n2 - автоматический\n";
        cout << "Ваш выбор: ";
        cin >> choice;
        switch (choice) {
        case 1: {
            cout << "Выбран ручной ввод" << endl;
            manualInput(n, tmpMod);
            exit = true;
            break;
        }
        case 2: {
            cout << "Выбран автоматический ввод" << endl;
            autoInput(n, tmpMod);
            exit = true;
            break;
        }
            default:
                cout << "Некорректный ввод" << endl;
        }
    }
#pragma endregion
#pragma endregion Задание 2
    return 0;
}
