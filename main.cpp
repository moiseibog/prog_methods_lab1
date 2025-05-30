/**
 * @file main.cpp
 * @brief Основной файл программы для сравнения алгоритмов сортировки
 * @author Кирилл Моисеенко
 * @date 2023
 * 
 * Программа считывает данные о футболистах из CSV-файлов,
 * выполняет сортировку четырьмя разными алгоритмами,
 * измеряет время выполнения и сохраняет результаты.
 */


 #include <iostream>
 #include <fstream>
 #include <sstream>
 #include <chrono>
 #include <algorithm>
 #include <functional>
 #include "football.h"

/**
 * @brief Быстрая сортировка (Quick Sort) по убыванию
 * @tparam T Тип элементов массива
 * @param a Указатель на массив
 * @param N Количество элементов
 * 
 * Алгоритм:
 * 1. Выбор опорного элемента (середина массива)
 * 2. Разделение массива на две части
 * 3. Рекурсивная сортировка частей
 */
template<class T>
void quickSort(T* a, long N) {
    long i = 0, j = N - 1;      // Initialize bounds
    T p = a[N >> 1];            // Pivot: middle element

    // Partitioning phase
    do {
        while (a[i] > p) i++;
        while (a[j] < p) j--;

        if (i <= j) {
            //std::swap(a[i], a[j]);
            T x = a[i];
            a[i] = a[j];
            a[j] = x;
            i++;
            j--;
        }
    } while (i <= j);

    // Recursively sort the partitions
    if (j > 0) quickSort(a, j + 1);
    if (N > i) quickSort(a + i, N - i);
}

/**
 * @brief Вспомогательная функция для пирамидальной сортировки (Heap Sort)
 * @tparam T Тип элементов массива
 * @param a Массив
 * @param k Текущий узел
 * @param n Размер кучи
 */
template<class T> void downHeap(T a[], long k, long n)
{
  //  before sift procedure: a[k+1]...a[n]  - is a pyramid 
  //  after:                 a[k]...a[n]  - is a pyramid
  T new_elem;
  long child;
  new_elem = a[k];
  
  while(k <= n/2)
  {  // while a[k] has childs 
    child = 2*k;
    //  choose bigger son 
    if( child < n && a[child] > a[child+1] ) 
		child++;
    if( new_elem <= a[child] ) break; 
    // otherwise 
    a[k] = a[child]; 	// move the son up 
    k = child;
  }
  a[k] = new_elem;
}


/**
 * @brief Пирамидальная сортировка (Heap Sort) по убыванию
 * @tparam T Тип элементов массива
 * @param a Массив
 * @param size Размер массива
 * 
 * Алгоритм:
 * 1. Построение пирамиды
 * 2. Последовательное извлечение максимальных элементов
 */
template<class T> void heapSort(T a[], long size)
{
  long i;
  T temp;

  for(i=size/2-1; i >= 0; i--)	 // build pyramid 
	downHeap(a, i, size-1);
					// now a[0]...a[size-1] is a pyramid 
  for(i=size-1; i > 0; i--)
  {
	//std::swap(a[i], a[0]);		// swap first and last 
	T x = a[i];
	a[i] = a[0];
	a[0] = x;
	downHeap(a, 0, i-1); 	// restore the pyramid a[0]...a[i-1]
  }
}

/**
 * @brief Обертка для стандартной сортировки (std::sort) по убыванию
 * @tparam T Тип элементов массива
 * @param arr Указатель на массив
 * @param size Размер массива
 */
template <class T>
void sort_new(T* arr, long size)
{
    std::sort(arr, arr + size, std::greater<T>());
}

/**
 * @brief Функция слияния для сортировки слиянием
 * @tparam T Тип элементов массива
 * @param arr Массив
 * @param l Левый индекс
 * @param m Серединный индекс
 * @param r Правый индекс
 */
template<class T>
void merge(T arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    T* L = new T[n1];
    T* R = new T[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] > R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++; k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++; k++;
    }

    delete[] L;
    delete[] R;
}

/**
 * @brief Рекурсивная часть сортировки слиянием
 * @tparam T Тип элементов массива
 * @param arr Массив
 * @param l Левый индекс
 * @param r Правый индекс
 */
template<class T>
void mergeSortRecursive(T arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortRecursive(arr, l, m);
        mergeSortRecursive(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

/**
 * @brief Сортировка слиянием (Merge Sort) по убыванию
 * @tparam T Тип элементов массива
 * @param arr Массив
 * @param size Размер массива
 */
template<class T>
void mergeSort(T arr[], long size) {
    mergeSortRecursive(arr, 0, size - 1);
}


/**
 * @brief Чтение данных из CSV-файла
 * @param filename Имя файла
 * @param N Количество записей для чтения
 * @param result Указатель на массив для результатов
 * 
 * Формат CSV-файла:
 * country,full_name,club,position,matches,goals
 */
void readCSV(std::string filename, int N, Football* result) {
  std::ifstream in(filename);
  std::string line, country, full_name, club, position, matches_str, goals_str;
  int i = 0;

  if (in.is_open()) {
      std::getline(in, line); // пропускаем заголовок

      while (std::getline(in, line) && i < N) {
          std::stringstream ss(line);
          std::getline(ss, country, ',');
          std::getline(ss, full_name, ',');
          std::getline(ss, club, ',');
          std::getline(ss, position, ',');
          std::getline(ss, matches_str, ',');
          std::getline(ss, goals_str, ',');

          int matches = std::stoi(matches_str);
          int goals = std::stoi(goals_str);

          result[i] = Football(country, full_name, club, position, matches, goals);
          i++;
      }
      in.close();
  }
}

/**
 * @brief Главная функция программы
 * @return 0 при успешном завершении
 * 
 * Выполняет следующие действия:
 * 1. Открывает файл для записи результатов времени
 * 2. Определяет наборы данных для обработки
 * 3. Для каждого набора данных:
 *    - Читает данные из CSV
 *    - Выполняет сортировку 4 алгоритмами
 *    - Измеряет время выполнения
 *    - Сохраняет отсортированные данные
 *    - Записывает результаты времени
 * 4. Закрывает файл результатов
 */
int main() {

    std::ofstream out("/Users/kirillmoiseenko/VS Code/MD hse/pm1_lab-laba1/times.csv");
    
    out << "size,std::sort,quickSort,heapSort,mergeSort\n";

    int sizes[10] = {100, 200, 500, 1000, 1200, 1500, 2000, 5000, 10000, 50000};

    std::string filenames[10] = {
        "dataset_100.csv",
        "dataset_200.csv",
        "dataset_500.csv",
        "dataset_1000.csv",
        "dataset_1200.csv",
        "dataset_1500.csv",
        "dataset_2000.csv",
        "dataset_5000.csv",
        "dataset_10000.csv",
        "dataset_50000.csv"
    };

    std::string path = "/Users/kirillmoiseenko/VS Code/MD hse/pm1_lab-laba1/datasets/";

    std::string path_sort = "/Users/kirillmoiseenko/VS Code/MD hse/pm1_lab-laba1/sorted_datasets/";

    for (int i = 0; i < 10; ++i) {
      std::string full_path = path + filenames[i];
      int N = sizes[i];
      Football* original = new Football[N];
      readCSV(full_path, N, original);

      // merge sort

      Football* arr_merge = new Football[N];
      std::copy(original, original + N, arr_merge);

      auto t_start_merge = std::chrono::high_resolution_clock::now();
      mergeSort(arr_merge, N);
      auto t_end_merge = std::chrono::high_resolution_clock::now();
      auto t_merge = std::chrono::duration<double, std::milli>(t_end_merge - t_start_merge).count();

      // --- STD::SORT  ---

      //std::copy(original, original + N, a1);
      Football* a1 = new Football[N];
      for (int i = 0; i < N; ++i) {
        a1[i] = original[i];  
      }
      auto t1_start = std::chrono::high_resolution_clock::now();
      sort_new(a1, N);
      auto t1_end = std::chrono::high_resolution_clock::now();
      auto t_stdsort = std::chrono::duration<double, std::milli>(t1_end - t1_start).count();

      // std::ofstream fout1(path_sort + "stdsort_" + std::to_string(N) + ".txt"); 
      // for (int j = 0; j < N; ++j) {
      //   fout1 << a1[j] << "\n"; 
      // }
      // fout1.close(); 
      // std::cout << "std::sort for dataset of size " << N << " is finished." << std::endl;

      // delete[] a1;

      // --- quickSort  ---

      //std::copy(original, original + N, a2);
      Football* a2 = new Football[N];
      for (int i = 0; i < N; ++i) {
        a2[i] = original[i];  
      }
      auto t2_start = std::chrono::high_resolution_clock::now();
      quickSort(a2, N);
      auto t2_end = std::chrono::high_resolution_clock::now();
      auto t_quicksort = std::chrono::duration<double, std::milli>(t2_end - t2_start).count();
      
      // std::ofstream fout2(path_sort + "quicksort_" + std::to_string(N) + ".txt"); 
      // for (int j = 0; j < N; ++j) {
      //   fout2 << a2[j] << "\n"; 
      // }
      // fout2.close(); 
      // std::cout << "quickSort for dataset of size " << N << " is finished." << std::endl;

      // delete[] a2;

      // --- heapSort  ---

      //std::copy(original, original + N, a3);
      Football* a3 = new Football[N];
      for (int i = 0; i < N; ++i) {
        a3[i] = original[i];  
      }
      auto t3_start = std::chrono::high_resolution_clock::now();
      heapSort(a3, N);
      auto t3_end = std::chrono::high_resolution_clock::now();
      auto t_heapsort = std::chrono::duration<double, std::milli>(t3_end - t3_start).count();
      
      // std::ofstream fout3(path_sort + "heapsort_" + std::to_string(N) + ".txt"); 
      // for (int j = 0; j < N; ++j) {
      //   fout3 << a3[j] << "\n"; 
      // }
      // fout3.close(); 
      // std::cout << "heapSort for dataset of size " << N << " is finished." << std::endl;

      // delete[] a3;

      out << N << "," << t_stdsort << "," << t_quicksort << "," << t_heapsort << "," << t_merge << "\n";
    }

    out.close();

    return 0;
}
