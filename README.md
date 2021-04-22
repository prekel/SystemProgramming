# SystemProgramming

#### Лабараторные работы по системному программированию (3 семестр)

| Путь       | Описание           | Протестированные платформы | Отчёт |
| ------------- | ------------- |------------- | ------ |
| [`0x02/Lab_01`](https://github.com/prekel/SystemProgramming/tree/master/0x02/Lab_01)      | Спавнилка дочерней программы через fork-exec | Linux | [Отчёт](https://github.com/prekel/SystemProgramming/blob/master/0x02/Lab_01_Done_Prekel.pdf) |
| [`0x04/Lab_02`](https://github.com/prekel/SystemProgramming/tree/master/0x04/Lab_02)     | Задача об обедающих философах (синхронизация потоков). Используется библиотека SDL2 для интерактивного интерфейса. Была почти успешная попытка портировать на Android. А потом на WebAssembly с помощью Emscripten      | Linux, Windows (MinGW), Android (почти), [Wasm](https://prekel.github.io/SystemProgramming) | [Отчёт](https://github.com/prekel/SystemProgramming/blob/master/0x04/Lab_02_Prekel.pdf) |
| [`0x06/Lab_03`](https://github.com/prekel/SystemProgramming/tree/master/0x06/Lab_03)  | Программа, позволяющая вводить записи опредёленной струкруты ("архипелаги"), хранить их в связном списке и делать определённые запросы на них       | Linux, Windows (MSVC, MinGW) | [Отчёт](https://github.com/prekel/SystemProgramming/blob/master/0x06/Lab_03_Prekel.pdf) |
| [`0x08/Lab_04`](https://github.com/prekel/SystemProgramming/tree/master/0x08/Lab_04)  | Мини-БД для "архипелагов" с CLI-интерфейсом, хранящяя записи в бинарном файле | Linux, Windows (MSVC, MinGW) | [Отчёт](https://github.com/prekel/SystemProgramming/blob/master/0x08/Lab_04_Prekel.pdf)|
| [`0x0A/Lab_05`](https://github.com/prekel/SystemProgramming/tree/master/0x0A/Lab_05)  | Клиент отсылает серверу две квадратные матрицы. Сервер принимает их, а затем выводит на экран сумму матриц, а также определитель суммарной матрицы. Клиент и сервер имеют CLI-интерфейс | Linux, Windows (MSVC, MinGW), Android (Termux) | [Отчёт](https://github.com/prekel/SystemProgramming/blob/d16ab7172919d0e049a7973b87c1e71a25c0c881/0x0A/Lab_05_Prekel.pdf) |
| [`0x0E/Lab_06`](https://github.com/prekel/SystemProgramming/tree/master/0x0E/Lab_06)  | Некоторые операции над матрицами, реализованные на трёх ассемблерах, на C и тесты к ним. | `Lab_06_aarch64-gas` - Linux (qemu-aarch64), Android (Termux); `Lab_06_i386-gas` - Linux (qemu-i386), Linux x86; `Lab_06_mips-spim` - Linux (SPIM MIPS Simulator); `Lab_06_C`, `Lab_06_Tests` - Linux (qemu-aarch64), Android (Termux), Linux (qemu-i386), Linux x86` | [Отчёт](https://github.com/prekel/SystemProgramming/blob/master/0x0E/Lab_06_Prekel.pdf) |

[prekel.github.io/SystemProgramming](https://prekel.github.io/SystemProgramming)
