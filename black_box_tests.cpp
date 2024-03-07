//======= Copyright (c) 2024, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Aryna Zhukava <xzhuka01@stud.fit.vutbr.cz>
// $Date:       $2024-02-14
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Aryna Zhukava
 *
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

class EmptyTree : public ::testing::Test
{
protected:
    BinaryTree tree;
};

class NonEmptyTree : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        int values[] = {0, 100, 28, 04, 5, 10, 2024};
        for (auto value : values)
        {
            tree.InsertNode(value);
        }
    }

    BinaryTree tree;
};

class TreeAxioms : public ::testing::Test
{
protected:
    BinaryTree tree;

    virtual void SetUp()
    {
        int values[] = {0, 100, 28, 04, 5, 10, 2024};
        for (auto value : values)
        {
            tree.InsertNode(value);
        }
    }
};

// ============================== EMPTY TREE ==============================

TEST_F(EmptyTree, InsertNode) // ????????????????????????????????
{
    
    auto result = tree.InsertNode(28);
    ASSERT_TRUE(result.first);
    EXPECT_EQ(result.second->key, 28);

    result = tree.InsertNode(0);
    ASSERT_TRUE(result.first);
    EXPECT_EQ(result.second->key, 0);
}

TEST_F(EmptyTree, DeleteNode)
{
    auto result = tree.DeleteNode(1);
    EXPECT_FALSE(result);
}

TEST_F(EmptyTree, FindNode)
{
    tree.InsertNode(28);

    // Expects the node with a given key is found in the tree
    auto result = tree.FindNode(28);
    EXPECT_TRUE(!!result);
    EXPECT_EQ(result->key, 28);

    // Test finding a node that doesn't exist in the tree
    EXPECT_FALSE(tree.FindNode(1));
}

// ============================== NON-EMPTY TREE ==============================

TEST_F(NonEmptyTree, InsertNode)
{
    auto result = tree.InsertNode(19);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second->key, 19);
}

TEST_F(NonEmptyTree, DeleteNode)
{
    // Delete the existing node
    auto result = tree.DeleteNode(28);
    EXPECT_TRUE(result);

    // Does not exist
    result = tree.DeleteNode(1);
    EXPECT_FALSE(result);
}

TEST_F(NonEmptyTree, FindNode)
{
    tree.InsertNode(28);

    // The node with a given key is found in the tree
    auto result = tree.FindNode(28);
    EXPECT_TRUE(!!result); // !! - boolean value
    EXPECT_EQ(result->key, 28);

    // Doesn't exist in the tree
    EXPECT_FALSE(tree.FindNode(1));
}

// ============================== AXIOMS ==============================
// Všechny listové uzly (tedy uzly bez potomků) jsou „černé”.
TEST_F(TreeAxioms, Axiom1)
{
    std::vector<Node_t *> leaves{};
    tree.GetLeafNodes(leaves);

    // Each node should be BLACK
    for (auto leaf : leaves)
    {
        EXPECT_TRUE(leaf->color == BinaryTree::BLACK);
    }
}

// Pokud je uzel „červený”, pak jsou jeho oba potomci „černé”.
TEST_F(TreeAxioms, Axiom2)
{
    std::vector<Node_t *> nodes{};
    tree.GetNonLeafNodes(nodes);

    // If node color is RED => pLeft and pRight should be BLACK
    for (auto node : nodes)
    {
        if (node->color == BinaryTree::RED)
        {
            EXPECT_TRUE(node->pLeft->color == BinaryTree::BLACK);
            EXPECT_TRUE(node->pRight->color == BinaryTree::BLACK);
        }
    }
}

// Každá cesta od každého listového uzlu ke kořeni obsahuje stejný počet „černých” uzlů.
TEST_F(TreeAxioms, Axiom3)
{
    // Get and insert nodes into vector "nodes"
    std::vector<Node_t *> nodes{};
    tree.GetLeafNodes(nodes);

    auto node = nodes[0];
    int blackNodesCount = 0; // should be

    while (node != tree.GetRoot()) // while node is not the root, move up to the parent nodes
    {
        node = node->pParent;
        if (node->color == BinaryTree::BLACK) // and count all BLACK nodes on its way
            blackNodesCount += 1;
    }

    for (auto node : nodes)
    {
        int counterBlack = 0;

        while (node != tree.GetRoot())
        {
            node = node->pParent; // moves up
            if (node->color == BLACK)
                counterBlack += 1;
        }

        EXPECT_EQ(counterBlack, blackNodesCount); //
    }
}

//- Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//  *STEJNY* pocet cernych uzlu.

/*** Konec souboru black_box_tests.cpp ***/
