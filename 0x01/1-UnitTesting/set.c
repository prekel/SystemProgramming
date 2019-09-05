/*! \file    set.c
 *  \brief   Library of functions to operate on sets.
 *
 *  \details Unit-testing for library of functions to operate on sets.
 *           CUnit library to be linked ($gcc <filename> -lcunit).
 */
#include <stdlib.h>
#include <CUnit/Basic.h>

/*! \brief Set datatype */
struct _Set
{
    int* data;
    int size;
};

typedef struct _Set Set;

/* Success code */
#define SUCCESS 1

/* Fail code */
#define FAIL 0

/*! \brief int as Result datatype */
typedef int Result;

int contains(Set* set, int elem);

Result insert(Set* set, int elem);

Result Remove(Set* set, int elem);

/*! \brief Binary search in ordered array.
 *
 *  \details Binary search in ordered list of integers.
 *
 *  \param   array          Ordered list of integers.
 *  \param   len            Ordered list length.
 *  \param   elem           Integer value to search.
 *  \param   posBefore      Nearest element is less than Elem parameter.
 *
 *  \return  Index of the element if found.
 *           -1, otherwise. Index of nearest element via posBefore parameter.
 */
static int _bsearch (int* array, int len, int elem, int* posBefore)
{
    int low = 0, high = len - 1;
    while(low <= high)
    {
        int mid = (low + high) / 2;
        if (elem == array[mid])
            return mid;
        else if (elem < array[mid])

            high = mid - 1;
        else
            low = mid + 1;
    }
    if(NULL != posBefore)
        *posBefore = high;
    return -1;
}


/*! \brief Is the element in given set.
 *
 *  \details Check is there an element in given set.
 *
 *  \param   set            Set to check availability the element.
 *  \param   elem           Element value to check availability in the set 
 *
 *  \return  0, if the element if not found.
 *           nonzero, otherwise.
 */
int contains(Set* set, int elem)
{
    return indexOf(set, elem) != -1;
}

/*! \brief Search an element in given set.
 *
 *  \details Get the index of the element in given set.
 *
 *  \param   set            Set to search index of the element.
 *  \param   elem           Element value to search by index in the set 
 *
 *  \return  -1, if the element if not found.
 *           integer index of the element, otherwise.
 */
int indexOf(Set * set, int elem)
{
    return _bsearch(set->data, set->size - 1, elem, NULL);
}

/*! \brief Insert an element to given set.
 *
 *  \details Insert an element to the set, if it was not found there.
 *
 *  \param   set            Set to insert the element.
 *  \param   elem           Element value to insert to the set 
 *
 *  \return  FAIL, if the element is already in the set.
 *           SUCCESS, otherwise.
 */
Result insert(Set* set, int elem)
{
    int index, posBefore;
    index = _bsearch(set->data, set->size, elem, &posBefore);
    if(index != -1)
        return FAIL;
    set->data = realloc(set->data, sizeof(int) * (set->size + 1));
    memmove(set->data + posBefore + 2, set->data + posBefore + 1,
        sizeof(int) * (set->size - posBefore - 1));
    set->data[posBefore + 1] = elem;
    set->size++;
    return SUCCESS;
}

/*! \brief Remove an element from given set.
 *
 *  \details Remove an element from the set, if it was found there.
 *
 *  \param   set            Set to remove the element from it.
 *  \param   elem           Element value to remove from the set 
 *
 *  \return  FAIL, if the element is not in the set.
 *           SUCCESS, otherwise.
 */
Result Remove(Set* set, int elem)
{
    int index, posBefore;
    index = _bsearch(set->data, set->size, elem, &posBefore);
    if(index == -1)
        return FAIL;
    set->data = realloc(set->data, sizeof(int) * (set->size - 1));
    memmove(set->data + index, set->data + index + 1, sizeof(int) *
        (set->size - index - 1));
    set->size--;
    return SUCCESS;
}


/*! \brief Unit test for insertion using size checking. */
void test1(void)
{
    Set s = {0};
    CU_ASSERT_EQUAL(s.size, 0);
    insert(&s, 3);
    CU_ASSERT_EQUAL(s.size, 1);
    insert(&s, 1);
    CU_ASSERT_EQUAL(s.size, 2);
    CU_ASSERT_EQUAL(s.data[0], 1);
    CU_ASSERT_EQUAL(s.data[1], 3);
}

/*! \brief Other unit test for insertion. */
void test2(void)
{
    Set s = {0};
    CU_ASSERT_EQUAL(insert(&s, 1), SUCCESS);
    CU_ASSERT_EQUAL(insert(&s, 1), FAIL);
}

/*! \brief Unit test for insertion and removing. */
void test3(void)
{
    Set s = {0};
    insert(&s, 1);
    CU_ASSERT_EQUAL(Remove(&s, 2), FAIL);
    CU_ASSERT_EQUAL(Remove(&s, 1), SUCCESS);
}

/*! \brief Unit test for binary searching. */
void test4()
{
    int array[] = {1, 3, 5, 11};
    int size = sizeof(array) / sizeof(int);
    int posBefore;

    CU_ASSERT_EQUAL(_bsearch(array, size, 4, &posBefore),
        -1);
    CU_ASSERT_EQUAL(posBefore, 1);
    CU_ASSERT_EQUAL(_bsearch(array, size, 19,
        &posBefore), -1);
    CU_ASSERT_EQUAL(posBefore, 3);
    CU_ASSERT_EQUAL(_bsearch(array, size, 5, &posBefore),
        2);
}

/*! \brief Main function
 *  \return Unit testing error code
 */
int main()
{
    CU_pSuite suite;
    CU_initialize_registry();
    suite = CU_add_suite("main_suite", NULL, NULL);
    CU_ADD_TEST(suite, test1);
    CU_ADD_TEST(suite, test2);
    CU_ADD_TEST(suite, test3);
    CU_ADD_TEST(suite, test4);
    CU_basic_run_tests();

    CU_cleanup_registry();
    return CU_get_error();
}
