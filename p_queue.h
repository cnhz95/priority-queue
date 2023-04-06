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
    void push(T e) {
        auto pos = std::find_if(pq.begin(), pq.end(), [&](const T& x) -> bool {
            return m_comparer(e, x);
        });
        pq.insert(pos, e);

        /*
        pq.push_back(e);
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