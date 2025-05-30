# Название исполняемого файла
TARGET = lab1

# Все .cpp в текущей директории
SRCS := main.cpp football.cpp

# Цель по умолчанию
all: $(TARGET)

# Сборка: все .cpp компилируются сразу в один бинарник
$(TARGET): $(SRCS)
	g++ $(SRCS) -o $(TARGET)

# Генерация датасетов
generate-datasets:
	python3 gendata.py

# Построение графиков
graphs:
	python3 plt.py

report :
	cd doc && \
	rm -rf latex html && \
	doxygen Doxyfile && \
	cd latex && \
	make

# Запуск
run: all
	./$(TARGET)

# Полный запуск
full: clean-all generate-datasets all run graphs report

# Очистка датасетов
clean-datasets:
	rm -f datasets/*.csv

# Очистка отсортированных датасетов
clean-sorted-datasets:
	rm -f sorted_datasets/*.txt

# Очистка результатов
clean-result:
	rm -f times.csv

# Очистка исполняемого файла
clean:
	rm -f $(TARGET)

# Полная очистка
clean-all: clean-datasets clean-sorted-datasets clean-result clean
