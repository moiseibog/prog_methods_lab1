/**
 * @file football.h
 * @brief Заголовочный файл класса Football
 */

#ifndef FOOTBALL_H
#define FOOTBALL_H

#include <string>
#include <iostream>

/**
 * @class Football
 * @brief Класс, представляющий футболиста
 * 
 * Содержит информацию о футболисте: страну, ФИО, клуб, амплуа,
 * количество матчей и голов.
 */

class Football {
private:
    std::string country;
    std::string full_name;
    std::string club;
    std::string position;
    int matches;
    int goals;

public:
    Football();
    Football(std::string country, std::string full_name, std::string club, std::string position, int matches, int goals);
    Football(const Football& other);
    ~Football() = default;

    // Операторы сравнения
    bool operator>(const Football& other) const;
    bool operator<(const Football& other) const;
    bool operator<=(const Football& other) const;
    bool operator>=(const Football& other) const;
    bool operator==(const Football& other) const;
    Football& operator=(const Football& other);

    friend std::ostream& operator<<(std::ostream& out, const Football& football);
};

#endif