# lem_in

## О проекте
**Дано:** двусвязный граф: ноды - комнаты, связи - проходы между ними; муравьи, находящиеся в стартовой ноде; финишная нода.  
В каждой комнате одновременно может находиться 1 муравей (кроме старта и финиша).  
**Задача:** за наименьшее число ходов (за один ход можно переместить любое количество муравьёв,  
не нарушая вышесказанного условия) провести всех муравьёв из старта в финиш.  
[Полное условие](https://github.com/liftchampion/lem_in/blob/master/lem-in.en.pdf)  
**Решение:**  
+ двусвязный граф преобразуется в односвязный, причём каждая нода превращается в 2:  
из одной "половины" выходят все связи, в другую - приходят.  
Это необходимо чтобы решать задачу в контексте *транспортных сетей*:  
в них оперируют пропусной способностью рёбер, в нашей задаче ей обладают вершины.  
+ Выполняется поиск **оптимального** (для данного количества муравьев) потока с помощью алгоритма *Эдмондса-Карпа*.  
Данный алгоритм используется с улучшением: вместо использования алгоритма *Форда-Беллмана* для поиска пути на графе,
используется алгоритм *Дейкстры* (используются *потенциалы Джонсона* для избавления от рёбер отрицательного веса).
+ Время прохождения муравьев по данному потоку, а также их распределение по путям рассчитывается исходя из того, что по кратчайшему пути должно идти минимальное количество муравьев, притом кратчайшей пути должен "завершиться" не ранее остальных.
+ Далее граф приводится к исходному виду и генерируются перемещения муравьёв в соответсвии с требуемым форматом вывода.  

**Итог:** Выбранный алгоритм идеально подошёл к задаче: среди критериев оценивания были время и точность  
(генератор также выдаёт ответ, оптимальный по его мнению).  
Требовалось уложиться в 3 секунды и не показывать количество ходов большее, чем предсказал генератор.
В итоге задача решается примерно за  0.1 секунды (с учётом затрат на чтение/запись), и при этом часто  
ответ получается лучше предсказанного генератором.

## Быстрый запуск (Docker)
`docker run --rm -d -p 6901:6901 -e VNC_RESOLUTION=2400x1200 -e VNC_COL_DEPTH=32 -e VNC_PW=gg ggerardy/school42-lem_in:demo xterm -geometry 173x59+660+145`  
Затем в браузере откройте `http://192.168.99.100:6901/?password=gg` с ip вашей виртуальной машины  
Размер образа 1.2гб  
Время запуска 1 минута 20 секунд  
*!На данной версии графической библиотеки другие параметры шрифтов, из-за чего те немного съезжают*  
## Запуск
`make`  
`./generetor --big-superposition | ./lem-in`  
(Для других опций генератора используйте `./generator --help`)  
## Флаги
![flags](https://raw.githubusercontent.com/liftchampion/lem_in/master/imgs/help.png)
## Визуализация
Задача представлена в виде таблицы: столбцы - ноды графа, строки - муравьи.  
Старт и финиш выделены цветом. В зависимости от размера графа выбирается размер ячейки, минимальный размер 1x1px.  
Таблица может переноситься.  
Использован HSV градиент для обозначения удаленности от старта.  
Равноудаленные ноды имеют одинаковый цвет.  
При простоте и *концептуальности* визуализации она отражает основные паттерны поведения муравьев:  
+ они идут по одним и тем же путям  
+ за раз из старта выходит *величина оптимального потока* муравьёв  
+ последние муравьи, идущие по кратчайшему, пути доходят до финиша одновременно с муравьями, идущими по более длинным путям  

Визуализация выполнена на библиотеке [minilibx](https://github.com/liftchampion/minilibx).  
![big_superposition](https://raw.githubusercontent.com/liftchampion/lem_in/master/imgs/big_superposition.png)
![thousand](https://raw.githubusercontent.com/liftchampion/lem_in/master/imgs/thousand.png)
![ten](https://raw.githubusercontent.com/liftchampion/lem_in/master/imgs/ten.png)
## Потоки
с флагом *--flows* можно получить информацию о найденных потоках и количестве муравьёв на их путях.  
![flows](https://raw.githubusercontent.com/liftchampion/lem_in/master/imgs/flows.png)

*C код написан в [Norminette code style](https://github.com/liftchampion/Norminette)*