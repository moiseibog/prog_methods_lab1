import pandas as pd
import numpy as np
from faker import Faker
import random

# Инициализация Faker для генерации имен
fake = Faker()

# Список стран и клубов
countries = [
    'Россия', 'Бразилия', 'Германия', 'Испания', 'Франция',
    'Италия', 'Англия', 'Аргентина', 'Португалия', 'Нидерланды'
]
clubs = {
    'Россия': ['ЦСКА', 'Зенит', 'Спартак', 'Локомотив', 'Краснодар'],
    'Бразилия': ['Фламенго', 'Сантос', 'Палмейрас', 'Коринтианс'],
    'Германия': ['Бавария', 'Боруссия Дортмунд', 'РБ Лейпциг'],
    'Испания': ['Реал Мадрид', 'Барселона', 'Атлетико Мадрид'],
    'Франция': ['ПСЖ', 'Олимпик Марсель', 'Лион'],
    'Италия': ['Ювентус', 'Милан', 'Интер'],
    'Англия': ['Манчестер Юнайтед', 'Ливерпуль', 'Челси'],
    'Аргентина': ['Бока Хуниорс', 'Ривер Плейт'],
    'Португалия': ['Бенфика', 'Порту', 'Спортинг'],
    'Нидерланды': ['Аякс', 'ПСВ', 'Фейеноорд']
}

# Амплуа и их вероятности
positions = ['вратарь', 'защитник', 'полузащитник', 'нападающий']
position_probs = [0.1, 0.3, 0.3, 0.3]

# Список требуемых размеров выборок
sample_sizes = [100, 200, 500, 1000, 1200, 1500, 2000, 5000, 10000, 50000]

def generate_teams(n):
    data = []
    for _ in range(n):
        country = random.choice(countries)
        full_name = fake.name()
        club = random.choice(clubs[country])
        position = np.random.choice(positions, p=position_probs)
        matches = random.randint(1, 150)
        
        if position == 'вратарь':
            goals = -random.randint(0, 50)
        elif position == 'защитник':
            goals = random.randint(0, 20)
        elif position == 'полузащитник':
            goals = random.randint(5, 30)
        else:  # нападающий
            goals = random.randint(10, 50)
        
        data.append([country, full_name, club, position, matches, goals])
    return data

def saveCSV(data, filename):
    df = pd.DataFrame(data, columns=['country', 'full_name', 'club', 'position', 'matches', 'goals'])
    file_path = f"/Users/kirillmoiseenko/VS Code/MD hse/pm1_lab-laba1/datasets/{filename}" #f"/home/install/pm1_lab/datasets/{filename}"

    df.to_csv(file_path, index=False)

for i in sample_sizes:
    data = generate_teams(i)
    filename = f"dataset_{i}.csv"
    saveCSV(data, filename)