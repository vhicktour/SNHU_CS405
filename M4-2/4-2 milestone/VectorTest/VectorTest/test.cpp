// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}

// Code created by Vudeh
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);

    add_entries(1);

    ASSERT_FALSE(collection->empty());
    ASSERT_EQ(collection->size(), 1);
}

// Code created by Vudeh
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    add_entries(5);
    ASSERT_EQ(collection->size(), 5);
    ASSERT_FALSE(collection->empty());
}

// Code created by Vudeh
TEST_F(CollectionTest, MaxSizeShouldBeGreaterThanSize)
{
    EXPECT_GE(collection->max_size(), collection->size());

    add_entries(1);
    EXPECT_GE(collection->max_size(), collection->size());

    add_entries(4);
    EXPECT_GE(collection->max_size(), collection->size());

    add_entries(5);
    EXPECT_GE(collection->max_size(), collection->size());
}

// Code created by Vudeh
TEST_F(CollectionTest, CapacityShouldBeGreaterOrEqualToSize)
{
    EXPECT_GE(collection->capacity(), collection->size());

    add_entries(1);
    EXPECT_GE(collection->capacity(), collection->size());

    add_entries(4);
    EXPECT_GE(collection->capacity(), collection->size());

    add_entries(5);
    EXPECT_GE(collection->capacity(), collection->size());
}

// Code created by Vudeh
TEST_F(CollectionTest, ResizingIncreasesCollection)
{
    size_t originalSize = collection->size();
    collection->resize(10);
    ASSERT_GT(collection->size(), originalSize);
    ASSERT_EQ(collection->size(), 10);
}

// Code created by Vudeh
TEST_F(CollectionTest, ResizingDecreasesCollection)
{
    collection->resize(10);
    size_t originalSize = collection->size();
    collection->resize(5);
    ASSERT_LT(collection->size(), originalSize);
    ASSERT_EQ(collection->size(), 5);
}

// Code created by Vudeh
TEST_F(CollectionTest, ResizingToZeroEmptiesCollection)
{
    collection->resize(10);
    collection->resize(0);
    ASSERT_EQ(collection->size(), 0);
    ASSERT_TRUE(collection->empty());
}

// Code created by Vudeh
TEST_F(CollectionTest, ClearRemovesAllElements)
{
    add_entries(5);
    ASSERT_FALSE(collection->empty());
    collection->clear();
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);
}

// Code created by Vudeh
TEST_F(CollectionTest, EraseRemovesAllElements)
{
    add_entries(5);
    ASSERT_FALSE(collection->empty());
    collection->erase(collection->begin(), collection->end());
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);
}

// Code created by Vudeh
TEST_F(CollectionTest, ReserveIncreasesCapacityOnly)
{
    size_t originalCapacity = collection->capacity();
    size_t originalSize = collection->size();
    collection->reserve(20);
    ASSERT_GT(collection->capacity(), originalCapacity);
    ASSERT_EQ(collection->size(), originalSize);
}

// Code created by Vudeh
TEST_F(CollectionTest, AccessingOutOfRangeThrows)
{
    add_entries(5);
    EXPECT_THROW(collection->at(10), std::out_of_range);
}

// Code created by Vudeh - Custom positive test
TEST_F(CollectionTest, InsertingAtFrontAddsElement)
{
    int testValue = 42;
    collection->push_back(1);
    collection->insert(collection->begin(), testValue);
    ASSERT_EQ(collection->front(), testValue);
    ASSERT_EQ(collection->size(), 2);
}

// Code created by Vudeh - Custom negative test
TEST_F(CollectionTest, ReserveWithTooLargeSizeThrows)
{
    size_t tooLarge = collection->max_size() + 1;
    EXPECT_THROW(collection->reserve(tooLarge), std::length_error);
}