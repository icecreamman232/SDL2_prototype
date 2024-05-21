#pragma once
#include <vector>
#include "GameObject.h"
#include <string>

template<typename T> class ObjectPooler 
{
public:
    std::vector<T*> m_activeList;
private:
    std::vector<T*> m_pool;
    

public:
    ObjectPooler(int initialSize) {
        // Create the initial objects in the pool
        for (int i = 0; i < initialSize; ++i) {
            T* object = new T();
            m_pool.push_back(object);
        }
    }

    ~ObjectPooler() {
        // Cleanup the objects in the pool
        for (T* object : m_pool) {
            delete object;
        }
    }

    T* GetObject() {
        if (!m_pool.empty()) 
        {
            // Get an object from the pool
            T* object = m_pool.back();
            m_pool.pop_back();
            m_activeList.push_back(object);
            return object;
        }
        else 
        {
            // If no objects are available, create a new one
            T* object = new T();
            m_activeList.push_back(object);
            return object;
        }
    }

    void ReleaseObject(T* object) {
        // Release the object back to the pool
        auto it = std::find(m_activeList.begin(), m_activeList.end(), object);
        if (it != m_activeList.end()) 
        {
            m_activeList.erase(it);
            object->Reset();
            m_pool.push_back(object);
        }
    }
};
