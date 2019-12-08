/// \file
/// \brief Абстрактный набор тестов
/// \details Абстрактный набор тестов.

#ifndef SUITE_H
#define SUITE_H

#include <CUnit/Basic.h>

/// Создаёт набор тестов и запускает функцию добавления тестов в набор.
/// Требуется очистка с помощью SuiteDestroy().
///
/// \param name Название набора.
/// \param pAddTests Указатель на функцию, запускаемая для добавления тестов
/// в набор.
/// \return Указатель на созданный набор тестов.
CU_pSuite* SuiteCreate(char* name, void(* pAddTests)(CU_pSuite*));

/// Уничтожает набор тестов.
///
/// \param pSuite Указатель на набор тестов.
void SuiteDestroy(CU_pSuite* pSuite);

#endif //SUITE_H
