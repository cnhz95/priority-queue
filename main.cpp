#include "p_queue.h"
#include <chrono>
#include <iostream>
#include <random>
#include <string>

struct Broker {
    std::string m_name;
    unsigned long m_price;
};

template<typename T>
struct Compare_price {
    constexpr bool operator()(const T& lhs, const T& rhs) const {
        return lhs.m_price < rhs.m_price;
    }
};

int main() {
    std::mt19937 rng((uint32_t)std::chrono::steady_clock::now().time_since_epoch().count());
    constexpr int ORDERS = 21;

    p_queue<Broker, Compare_price<Broker>> buy_orders, sell_orders;
    std::string names[3] { "Erik Pendel", "Jarl Wallenburg", "Joakim von Anka" };

    for (int i = 0; i < ORDERS; i++) {
        buy_orders.push({ names[i % 3], rng() % 16 + 15 });
        sell_orders.push({ names[i % 3], rng() % 16 + 15 });
    }

    while (!buy_orders.empty() && !sell_orders.empty()) {
        auto seller = sell_orders.pop();
        auto buyer = buy_orders.pop();
        if (seller.m_price <= buyer.m_price) {
            std::cout << buyer.m_name << " bought from " << seller.m_name << " at the price " << seller.m_price << '\n';
        }
        else {
            sell_orders.push({ seller.m_name, seller.m_price });
        }
    }

    return 0;
}