//======= Copyright (c) 2024, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - test suite
//
// $NoKeywords: $ivs_project_1 $white_box_tests.cpp
// $Author:     Aryna Zhukava <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2024-02-14
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Aryna Zhukava
 *
 * @brief Implementace testu hasovaci tabulky.
 */

#include <vector>

#include "gtest/gtest.h"

#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy hasovaci tabulky, testujte nasledujici:
// 1. Verejne rozhrani hasovaci tabulky
//     - Vsechny funkce z white_box_code.h
//     - Chovani techto metod testuje pro prazdnou i neprazdnou tabulku.
// 2. Chovani tabulky v hranicnich pripadech
//     - Otestujte chovani pri kolizich ruznych klicu se stejnym hashem
//     - Otestujte chovani pri kolizich hashu namapovane na stejne misto v
//       indexu
//============================================================================//

class EmptyHashMap : public ::testing::Test
{
protected:
    hash_map_t *map = hash_map_ctor();

    virtual void SetUp()
    {
        map = hash_map_ctor();
    }

    virtual void TearDown()
    {
        if (map != nullptr)
            hash_map_dtor(map);
    }
};

class NonEmptyHashMap : public ::testing::Test
{
protected:
    hash_map_t *map = hash_map_ctor();

    void SetUp()
    {
        map = hash_map_ctor();

        hash_map_put(map, "A", 1);
        hash_map_put(map, "obloucheck", 1);
        hash_map_put(map, "AaAaA", 1);
        hash_map_put(map, "Kakashka", 1);
    }

    void TearDown()
    {
        if (map != nullptr)
            hash_map_dtor(map);
    }
};

// ============================== EMPTY HASH MAP ==============================

TEST_F(EmptyHashMap, hash_map_ctor)
{
    ASSERT_NE(map, nullptr);
    EXPECT_EQ(hash_map_capacity(map), HASH_MAP_INIT_SIZE); // 8
}

TEST_F(EmptyHashMap, hash_map_dtor)
{
    ASSERT_NE(map, nullptr);
    EXPECT_EQ(hash_map_capacity(map), HASH_MAP_INIT_SIZE);

    hash_map_dtor(map);
    map = nullptr; // Avoid accessing a non-existent location
}

TEST_F(EmptyHashMap, hash_map_remove)
{
    EXPECT_EQ(hash_map_remove(map, "zhopa"), KEY_ERROR); // does not exist in our table. yet

    EXPECT_EQ(hash_map_put(map, "zhopa", 1), OK); // insert
    EXPECT_EQ(hash_map_put(map, "yaLubluArynu", 2), OK);
    EXPECT_EQ(hash_map_size(map), 2); // number of inserted elements (2)
    EXPECT_EQ(hash_map_remove(map, "zhopa"), OK);

    EXPECT_EQ(hash_map_size(map), 2); // unsuccessfully
}

TEST_F(EmptyHashMap, hash_map_size)
{
    EXPECT_EQ(hash_map_size(map), 0);
    hash_map_put(map, "test", 28);
    EXPECT_EQ(hash_map_size(map), 1);
}

TEST_F(EmptyHashMap, hash_map_capacity)
{
    EXPECT_EQ(hash_map_capacity(map), HASH_MAP_INIT_SIZE);
}

TEST_F(EmptyHashMap, hash_map_pop)
{
    int value;
    EXPECT_EQ(hash_map_pop(map, "nenene", &value), KEY_ERROR);

    EXPECT_EQ(hash_map_put(map, "nenene", 1), OK);      // Insert successfully
    EXPECT_EQ(hash_map_pop(map, "nenene", &value), OK); // Verifies that popping an element with key "test" from the hash map is successful
    EXPECT_EQ(value, 1);                                // value should be 1
    EXPECT_EQ(hash_map_size(map), 1);                   // The hash map's size is updated correctly
}

TEST_F(EmptyHashMap, hash_map_put)
{
    EXPECT_EQ(hash_map_put(map, "pisyapopa", 28), OK);
    EXPECT_EQ(hash_map_put(map, "pisyapopa", 29), KEY_ALREADY_EXISTS);
}

TEST_F(EmptyHashMap, hash_map_get)
{
    int value;
    EXPECT_EQ(hash_map_get(map, "nenene", &value), KEY_ERROR);
}

// ============================== NON-EMPTY HASH MAP ==============================

TEST_F(NonEmptyHashMap, hash_map_ctor)
{
    ASSERT_NE(map, nullptr);
    EXPECT_EQ(hash_map_capacity(map), HASH_MAP_INIT_SIZE);
}

TEST_F(NonEmptyHashMap, hash_map_dtor)
{
    ASSERT_NE(map, nullptr);
    EXPECT_EQ(hash_map_capacity(map), HASH_MAP_INIT_SIZE);

    hash_map_dtor(map);
    map = nullptr; // Avoid accessing a non-existent location
}

TEST_F(NonEmptyHashMap, hash_map_clear)
{
    hash_map_clear(map);

    // Check if the hash map is empty after clearing
    EXPECT_EQ(hash_map_size(map), 0);
    EXPECT_EQ(hash_map_capacity(map), HASH_MAP_INIT_SIZE);
    EXPECT_EQ(map->first, nullptr);
    EXPECT_EQ(map->last, nullptr);
    EXPECT_EQ(map->used, 0);
}

TEST_F(NonEmptyHashMap, hash_map_remove)
{
	EXPECT_EQ(hash_map_remove(map, "doesNotExist"), KEY_ERROR);
}

TEST_F(NonEmptyHashMap, hash_map_reserve)
{
    EXPECT_EQ(hash_map_reserve(map, 0), VALUE_ERROR);
    EXPECT_EQ(hash_map_reserve(map, HASH_MAP_INIT_SIZE), OK);
    EXPECT_EQ(hash_map_reserve(map, SIZE_MAX), MEMORY_ERROR);
}

TEST_F(NonEmptyHashMap, hash_map_size)
{
	EXPECT_EQ(hash_map_size(map), 4);
}

TEST_F(NonEmptyHashMap, hash_map_capacity)
{
    EXPECT_EQ(hash_map_capacity(map), HASH_MAP_INIT_SIZE);

	EXPECT_EQ(hash_map_put(map, "elem1", 18), OK);
	EXPECT_EQ(hash_map_put(map, "elem2", 81), OK);

	EXPECT_EQ(hash_map_capacity(map), HASH_MAP_INIT_SIZE * 2);
}

TEST_F(NonEmptyHashMap, hash_map_contains)
{
	EXPECT_FALSE(hash_map_contains(map, "doesNotExist"));
	EXPECT_TRUE(hash_map_contains(map, "A"));
}

TEST_F(NonEmptyHashMap, hash_map_put)
{
	EXPECT_EQ(hash_map_put(map, "A", 70), KEY_ALREADY_EXISTS);
	EXPECT_EQ(hash_map_put(map, "NEW", 23), OK);
}

TEST_F(NonEmptyHashMap, hash_map_get)
{
	int value;
	EXPECT_EQ(hash_map_get(map, "A", &value), OK);
	EXPECT_EQ(value, 1); 

    EXPECT_EQ(hash_map_get(map, "doesNotExist", &value), KEY_ERROR);
}

TEST_F(NonEmptyHashMap, hash_map_pop)
{
	int value;
	EXPECT_EQ(hash_map_pop(map, "A", &value), OK);
	EXPECT_EQ(value, 1);

    EXPECT_EQ(hash_map_get(map, "doesNotExist", &value), KEY_ERROR);
}

TEST_F(NonEmptyHashMap, Collision){
    EXPECT_EQ(hash_map_put(map, "rrr", 6), OK);
    EXPECT_EQ(hash_map_put(map, "s", 7), OK);
    EXPECT_EQ(hash_map_put(map, "s", 8), KEY_ALREADY_EXISTS); // Key collision
}

/*** Konec souboru white_box_tests.cpp ***/
