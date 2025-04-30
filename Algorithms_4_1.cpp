#include <iostream>

class DynamicArray
{
private:
    int* data = nullptr;
    int actualSize = 0;
    int logicalSize = 0;
    int resizeRange = 0;

public:
    DynamicArray(int resizeRange = 5) : resizeRange{(resizeRange < 1) ? 1 : resizeRange}
    {
        checkActualSize();
    }

    ~DynamicArray()
    {
        delete[] data;
    }

    void resize(int newSize)
    {
        if (newSize < 0)
            newSize = 0;

        int oldLogicalSize = logicalSize;
        logicalSize = newSize;
        checkActualSize(oldLogicalSize);

        if (logicalSize > oldLogicalSize)
        {
            for (int i = oldLogicalSize; i < logicalSize; ++i)
            {
                data[i] = 0;
            }
        }
    }

    void Add(int value)
    {
        if (logicalSize >= actualSize)
        {
            checkActualSize();
        }
        data[logicalSize] = value;
        ++logicalSize;
        checkActualSize();
    }

    void Set(int index, int value, bool resizeArr = false)
    {
        if (index < 0)
            return;

        if (index >= logicalSize)
        {
            if (resizeArr)
            {
                resize(index + 1);
            }
            else
            {
                return;
            }
        }
        data[index] = value;
    }

    void remove(int index)
    {
        if (!isValidIndex(index))
            return;
        for (int i = index; i < logicalSize - 1; ++i)
        {
            data[i] = data[i + 1];
        }
        --logicalSize;
        checkActualSize();
    }

    void removeLast()
    {
        if (logicalSize > 0)
        {
        --logicalSize;
        }
        checkActualSize();
    }

    bool isValidIndex(int index) const
    {
        return (index >= 0) && (index < logicalSize);
    }

    bool isLastElement(int index) const
    {
        return index + 1 == logicalSize;
    }

    int& operator[](int index)
    {
        if (!isValidIndex(index))
        {
            throw std::out_of_range("out_of_range");
        }
        return data[index];
    }

    const int& operator[](int index) const
    {
        if (!isValidIndex(index))
        {
            throw std::out_of_range("out_of_range");
        }
        return data[index];
    }

    int getActualSize() const
    {
        return actualSize;
    }

    int getSize() const
    {
        return logicalSize;
    }

private:
    void checkActualSize(int oldLogicalSize = -1)
    {
        if (oldLogicalSize == -1)
        {
            oldLogicalSize = logicalSize;
        }

        if (actualSize == 0)
        {
            actualSize = resizeRange;
            newData();
            return;
        }

        if (logicalSize >= actualSize)
        {
            while (actualSize <= logicalSize)
            {
                actualSize += resizeRange;
            }
            newData(oldLogicalSize);
            return;
        }

        if (actualSize - logicalSize > resizeRange * 2)
        {
            while (actualSize - logicalSize > resizeRange)
            {
                actualSize -= resizeRange;
            }
            newData(oldLogicalSize);
            return;
        }
    }

    void newData(int oldLogicalSize = -1)
    {
        int* newDataArray = new int[actualSize]();

        if (oldLogicalSize == -1)
        {
            oldLogicalSize = logicalSize;
        }
        else
        {
            oldLogicalSize = std::min(oldLogicalSize, logicalSize);
        }

        if (data)
        {
            for (int i = 0; i < oldLogicalSize; ++i)
            {
                newDataArray[i] = data[i];
            }
            delete[] data;
        }

        data = newDataArray;
    }
};

#define TEST(condition)                                                                                                \
    if (condition)                                                                                                     \
    {                                                                                                                  \
        std::cout << "True: " << #condition << std::endl;                                                              \
    }                                                                                                                  \
    else                                                                                                               \
    {                                                                                                                  \
        std::cout << "False: " << #condition << std::endl;                                                             \
    }

void print()
{
}

int main()
{
    // Тест 1: Добавление элементов
    {
        DynamicArray arr1;
        arr1.Add(10);
        TEST(arr1.getSize() == 1);
        TEST(arr1[0] == 10);

        arr1.Add(20);
        arr1.Add(30);
        TEST(arr1.getSize() == 3);
    }

    // Тест 2: Изменение размера
    {
        DynamicArray arr2(3);
        arr2.resize(5);
        TEST(arr2.getSize() == 5);
        TEST(arr2.getActualSize() == 6);

        for (int i = 0; i < 5; ++i)
        {
            TEST(arr2[i] == 0);
        }
    }

    // Тест 3: Установка значений с изменением размера
    {
        DynamicArray arr3(2);
        arr3.Set(5, 100, true);
        // std::cout << arr3.getActualSize();
        // std::cout << arr3[5];
        TEST(arr3.getSize() == 6);
        TEST(arr3.getActualSize() == 8);
        TEST(arr3[5] == 100);
    }

    // Тест 4: Удаление элементов
    {
        DynamicArray arr4;
        for (int i = 0; i < 5; ++i)
        {
            arr4.Add(i + 1);
        }
        arr4.remove(2);
        // std::cout << arr4.getSize();
        // std::cout << 
        // std::cout << arr4[2];
        TEST(arr4.getSize() == 4);
        TEST(arr4[2] == 4);

        arr4.removeLast();
        TEST(arr4.getSize() == 3);
    }

    // Тест 5: Автоматическое уменьшение размера
    {
        DynamicArray arr5(5);
        for (int i = 0; i < 15; ++i)
        {
            arr5.Add(i);
        }
        //std::cout << arr5.getActualSize();
        TEST(arr5.getActualSize() == 20);
        arr5.resize(5);
        //std::cout << arr5.getActualSize();
        TEST(arr5.getActualSize() == 10);
    }

    return 0;
}