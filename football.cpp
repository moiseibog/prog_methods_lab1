/**
 * @file football.cpp
 * @brief Реализация методов класса Football
 * @author Кирилл Моисеенко
 * @date 2023
 */

#include "football.h"

/**
 * @brief Конструктор по умолчанию
 * 
 * Инициализирует все строковые поля пустыми строками, 
 * числовые поля - нулевыми значениями.
 */

Football::Football() {
    country = "";
    full_name = "";
    club = "";
    position = "";
    matches = 0;
    goals = 0;
}


/**
 * @brief Параметризованный конструктор
 * @param country Страна футболиста
 * @param full_name Полное имя футболиста
 * @param club Футбольный клуб
 * @param position Амплуа (вратарь, защитник и т.д.)
 * @param matches Количество проведенных матчей
 * @param goals Количество забитых мячей (для вратарей - отрицательное значение)
 * 
 * Создает объект Football с заданными характеристиками футболиста.
 */
Football::Football(std::string country, std::string full_name, std::string club, std::string position, int matches, int goals) {
    this->country = country;
    this->full_name = full_name;
    this->club = club;
    this->position = position;
    this->matches = matches;
    this->goals = goals;
}

/**
 * @brief Конструктор копирования
 * @param other Объект для копирования
 * 
 * Создает новый объект как копию переданного объекта.
 */
Football::Football(const Football& other) {
    country = other.country;
    full_name = other.full_name;
    club = other.club;
    position = other.position;
    matches = other.matches;
    goals = other.goals;
}

/**
 * @brief Оператор сравнения "больше"
 * @param other Объект для сравнения
 * @return true если текущий объект "больше" other, иначе false
 * 
 * Сравнение производится по трем критериям (в порядке приоритета):
 * 1. Количество матчей (по убыванию)
 * 2. ФИО (по возрастанию)
 * 3. Количество мячей (по убыванию)
 */
bool Football::operator>(const Football& other) const {
    if (matches != other.matches) 
        return matches > other.matches;
    if (full_name != other.full_name) 
        return full_name < other.full_name;
    return goals > other.goals;
}

/**
 * @brief Оператор сравнения "больше или равно"
 * @param other Объект для сравнения
 * @return true если текущий объект "больше или равен" other, иначе false
 */
bool Football::operator>=(const Football& other) const {
    return (*this > other) || (*this == other);
}

/**
 * @brief Оператор сравнения "меньше"
 * @param other Объект для сравнения
 * @return true если текущий объект "меньше" other, иначе false
 */
bool Football::operator<(const Football& other) const {
    return !(*this >= other);
}

/**
 * @brief Оператор сравнения "меньше или равно"
 * @param other Объект для сравнения
 * @return true если текущий объект "меньше или равен" other, иначе false
 */
bool Football::operator<=(const Football& other) const {
    return !(*this > other);
}

/**
 * @brief Оператор сравнения "равно"
 * @param other Объект для сравнения
 * @return true если объекты равны, иначе false
 * 
 * Объекты считаются равными, если совпадают:
 * - Количество матчей
 * - ФИО
 * - Количество мячей
 */
bool Football::operator==(const Football& other) const {
    return (matches == other.matches) && 
           (full_name == other.full_name) && 
           (goals == other.goals);
}

/**
 * @brief Оператор присваивания
 * @param other Объект для копирования
 * @return Ссылка на текущий объект
 */
Football& Football::operator=(const Football& other) {
    country = other.country;
    full_name = other.full_name;
    club = other.club;
    position = other.position;
    matches = other.matches;
    goals = other.goals;
    return *this;
}

/**
 * @brief Оператор вывода в поток
 * @param out Выходной поток
 * @param football Объект для вывода
 * @return Ссылка на выходной поток
 * 
 * Формат вывода: 
 * country,full_name,club,position,matches,goals
 */
std::ostream& operator<<(std::ostream& out, const Football& football) {
    out << football.country << ","
        << football.full_name << ","
        << football.club << ","
        << football.position << ","
        << football.matches << ","
        << football.goals;
    return out;
}