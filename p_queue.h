#ifndef PRIORITY_QUEUE_P_QUEUE_H
#define PRIORITY_QUEUE_P_QUEUE_H

#include <algorithm>
#include <cstddef>
#include <functional>
#include <vector>

template<typename T, typename Comp = std::less<T>> // Defaulttyp för jämförelsefunktionen
class p_queue {
public:
    explicit p_queue(Comp comparer = Comp{}) : m_comparer(comparer) {} // Defaultkonstruktion av kompareringsobjektet

    // Hämta och ta bort elementet som har högst prioritet
    T pop() {
        T val = pq.front();
        pq.erase(pq.begin());
        return val;
    }

    // Lägg till ett element
    void push(T elem) {
        auto pos = std::find_if(pq.begin(), pq.end(), [&](const T& e) {
            return m_comparer(elem, e);
        });
        pq.insert(pos, elem);
        /*
        pq.push_back(elem);
        std::sort(pq.begin(), pq.end(), m_comparer);
        */
    }

    size_t size() const {
        return pq.size();
    }

    bool empty() const {
        return pq.empty();
    }

private:
    std::vector<T> pq;
    Comp m_comparer;
};

#endif