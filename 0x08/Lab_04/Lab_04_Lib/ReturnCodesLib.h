#ifndef RETURNCODESLIB_H
#define RETURNCODESLIB_H


#define SUCCESSFUL 0


#define FILE_UNSUCCESSFUL_MESSAGE "Не удалось открыть/прочитать/записать файл\n"

#define FILE_UNSUCCESSFUL (-1)


#define BAD_VALUE_MESSAGE "Введено неверное значение\n"

#define BAD_VALUE (-2)


#define NOT_FOUND_MESSAGE "Не найдено\n"

#define NOT_FOUND (-3)


#define FILE_NOT_EXIST_MESSAGE "Файл не существует\n"

#define FILE_NOT_EXIST (-5)


#define CLOSE_UNSUCCESSFUL_MESSAGE "Не удалось закрыть файл\n"

#define CLOSE_UNSUCCESSFUL (-6)


#define BAD_META_MESSAGE "Неправильный формат файла\n"

#define BAD_META (-7)


#define BAD_RECORD_MESSAGE "Неправильная запись в файле\n"

#define BAD_RECORD (-8)


#define ALLOCATION_ERROR_MESSAGE "Не удалось выделить память\n"

#define ALLOCATION_ERROR (-9)


#define RETURN_IF_NOT_SUCCESSFUL(f) do { \
    int tmp = (f); \
    if (tmp < SUCCESSFUL) \
    { \
        return tmp; \
    } \
} while (0)

#define RETURN_NULL_IF_NULLPTR(ptr) do { \
    if ((ptr) == NULL) \
    { \
        return NULL; \
    } \
} while (0)

#endif //RETURNCODESLIB_H
