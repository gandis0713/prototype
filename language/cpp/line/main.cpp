// #include <iostream>

// class Ret {
// public:
//     ~Ret() {
//         std::cout << "Ret:" << val << std::endl;
//     }
//     float val{ 0.f };
// };

// Ret some(int someValue) {
//     std::cout << someValue << std::endl;
//     Ret ret;
//     float factor = 0.f;
//     float result1 = someValue * factor;
//     float result2 = someValue / factor;
//     if (result1 == 0.f) throw -1;
//     ret.val = result2;
//     return ret;
// }
// int main() {
//     try {
//         some( 1024 );
//     } catch (int e) {
//         std::cout << e << std::endl;
//     }
//     return 0;
// }

// #include <iostream>
// class Base {
// public:
//     void doSomething1() {
//         std::cout << "Base::doSomething1" << std::endl;
//     }
//     virtual void doSomething2() {
//         std::cout << "Base::doSomething2" << std::endl;
//     }
// };

// class Derived : public Base {
// public:
//     void doSomething1() {
//         std::cout << "Derived::doSomething1" << std::endl;
//     }
//     void doSomething2() override {
//         std::cout << "Derived::doSomething2" << std::endl;
//     }
//     void doSomething2( int val ) {
//         std::cout << "Derived::doSomething2(" << val << ")" << std::endl;
//     }
// };

// int main() {
//     Derived* pDerived = new Derived();
//     pDerived->doSomething1();
//     Base* pBase = pDerived;
//     pBase->doSomething1();
//     pBase->doSomething2();
//     pDerived->doSomething2( 0 );
//     pBase->doSomething2( 0 );
//     delete pDerived;
// }


// class Item {
//     friend class Node;
//     // friend class MyNode;
//   protected:
//     void doSomething() {}
// };
// class Node {
// public:
//     virtual void run(Item* item) = 0;
// };
// class MyNode : public Node {
// public:
//     void run(Item* item) override {
//         item->doSomething();
//     }
// };

// int main()
// {
//   return 0;
// }

#include <thread>
#include <mutex>


// class Worker {
// public:
//     void work() {
//         checkStatus();
//         // ...
//     }
// private:
//     void checkStatus() {
//         std::lock_guard<std::mutex> lg(m_mutex);
//         //check status...
//     } 
// private:
//     std::mutex m_mutex;
// };
// int main() {
//     std::thread t([=] {
//         Worker worker;
//         worker.work();
//     });
//     t.join();
//     return 0;
// }

#include <iostream>

// namespace {
//     const int kSize = 10;
//     std::mutex mutex;
// }

// class Worker {
// public:
//     void printEven(int val) {
//         std::lock_guard<std::mutex> g2(m_mutex2);
//         std::cout << " " << val << " ";
//     }
//     void printOdd(int val) {
//         std::lock_guard<std::mutex> g2(m_mutex2);
//         std::cout << " " << val << " ";
//     }
// private:
//     std::mutex m_mutex2;
// };

// void print(int i) {
//     std::lock_guard<std::mutex> g(mutex);
//     std::cout << " " << i << " ";
// }

// void f(int n) {
//     Worker worker;
//     for (int i = kSize * (n - 1); i < kSize * n ; ++i) {
//         if (n % 2 == 0)
//             worker.printEven(i);
//         else
//             worker.printOdd(i);
//     }
// }

// int main() {
//     std::thread t1(f, 1);
//     std::thread t2(f, 2);
//     std::thread t3(f, 3);
//     std::thread t4(f, 4);
//     std::thread t5(f, 5);

//     for (int i = 0; i > -kSize; --i)
//         print(i);

//     t1.join();
//     t2.join();
//     t3.join();
//     t4.join();
//     t5.join();

//     return 0;
// }

// class Foo {
// public:
//     Foo() = default;
//     Foo(Foo&&) noexcept {
//         //...
//     }
//     int sum(int a, int b) {
//         return a + b;
//     }
// };

// class Bar : public Foo {
// public:
//     Bar() = default;
// };

// int main() {
//     Bar bar;
//     return bar.sum( 1, 2 );
// }

#include <atomic>
#include <string>
// class Nameable {
// public:
//     std::string getName() const noexcept {
//         return m_name;
//     }
// private:
//     std::string m_name;
// };

// class Indexable {
// public:
//     uint32_t getIndex() const noexcept {
//         return m_index;
//     }
// private:
//     uint32_t m_index{ 0 };
// };

// template <class T>
// class Foo : public T
// {
// public:
//     Foo() {
//         m_id = ms_uniqueId++;
//     }
//     uint64_t getId() const noexcept {
//         return m_id;
//     }
// private:
//     uint64_t m_id{ 0 };
//     inline static std::atomic<uint64_t> ms_uniqueId{ 0 };
// };

// int main() {
//     Foo<Nameable>  nameableFoo;
//     Foo<Indexable> indexableFoo;
//     std::cout << indexableFoo.getId() << std::endl; 
//     return 0;
// }

class Nameable {
public:
    std::string_view getName() const {
        return m_name.substr(0, 8);
    }
private:
    std::string m_name = "";
};

int main() {
    Nameable a;
    std::cout << a.getName() << std::endl; 
    return 0;
}
