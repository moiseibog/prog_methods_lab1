import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Загружаем данные
data = pd.read_csv('times.csv')

# 1. Основной график (все алгоритмы, линейная шкала)
plt.figure(figsize=(12, 7))
for col in data.columns[1:]:
    plt.plot(data['size'], data[col], marker='o', markersize=6, linewidth=2, label=col)

plt.xlabel('Размер массива (элементы)', fontsize=12)
plt.ylabel('Время сортировки (мс)', fontsize=12)
plt.title('Сравнение алгоритмов сортировки', fontsize=14)
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend(fontsize=10)
plt.tight_layout()
plt.savefig("sort_comparison.png", dpi=300)
#plt.show()

# 2. График с логарифмической шкалой Y (все алгоритмы)
plt.figure(figsize=(12, 7))
for col in data.columns[1:]:
    plt.plot(data['size'], data[col], marker='o', markersize=6, linewidth=2, label=col)

plt.yscale('log')
plt.xlabel('Размер массива (элементы)', fontsize=12)
plt.ylabel('Время сортировки (мс, логарифмическая шкала)', fontsize=12)
plt.title('Сравнение алгоритмов сортировки (логарифмическая шкала)', fontsize=14)
plt.grid(True, which="both", linestyle='--', alpha=0.7)
plt.legend(fontsize=10)
plt.tight_layout()
plt.savefig("sort_comparison_log.png", dpi=300)
#plt.show()

# 3. График без mergeSort (только heapSort, quickSort и std::sort)
plt.figure(figsize=(12, 7))
for col in data.columns[1:]:
    if col != 'mergeSort':  # Исключаем mergeSort
        plt.plot(data['size'], data[col], marker='o', markersize=6, linewidth=2, label=col)

plt.xlabel('Размер массива (элементы)', fontsize=12)
plt.ylabel('Время сортировки (мс)', fontsize=12)
plt.title('Сравнение быстрых алгоритмов сортировки', fontsize=14)
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend(fontsize=10)
plt.tight_layout()
plt.savefig("fast_sort_comparison.png", dpi=300)
#plt.show()

# Дополнительно: график для быстрых алгоритмов с логарифмической шкалой
plt.figure(figsize=(12, 7))
for col in data.columns[1:]:
    if col != 'mergeSort':  # Исключаем mergeSort
        plt.plot(data['size'], data[col], marker='o', markersize=6, linewidth=2, label=col)

plt.yscale('log')
plt.xlabel('Размер массива (элементы)', fontsize=12)
plt.ylabel('Время сортировки (мс, логарифмическая шкала)', fontsize=12)
plt.title('Сравнение быстрых алгоритмов сортировки (логарифмическая шкала)', fontsize=14)
plt.grid(True, which="both", linestyle='--', alpha=0.7)
plt.legend(fontsize=10)
plt.tight_layout()
plt.savefig("fast_sort_comparison_log.png", dpi=300)
#plt.show()