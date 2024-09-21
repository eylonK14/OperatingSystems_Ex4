#include <iostream>
#include <mutex>
#include <thread>

/**
 * @class A
 * @brief Singleton class A with thread-safe lazy initialization.
 *
 * This class implements the Singleton design pattern, ensuring that only one instance
 * of the class is created and providing a global point of access to it. The class is
 * thread-safe, using a mutex to protect the instance creation.
 *
 * @note The constructor is private to prevent direct instantiation. Copy constructor
 * and assignment operator are deleted to prevent copying.
 *
 * @var A::instance
 * Static pointer to the single instance of the class.
 *
 * @var A::mutex
 * Static mutex used to ensure thread-safe initialization of the instance.
 *
 * @fn A* A::getInstance()
 * @brief Returns the single instance of the class, creating it if necessary.
 *
 * This method uses double-checked locking to ensure that the instance is created
 * only once in a thread-safe manner.
 *
 * @return A* Pointer to the single instance of the class.
 *
 * @fn void A::Unlock()
 * @brief Resets the instance pointer to nullptr.
 *
 * This method allows the singleton instance to be destroyed and recreated.
 */
class A
{
private:
    A() {}
    static A *instance;

    A() = default;
    A(const A &) = delete;
    A &operator=(const A &) = delete;

public:
    static std::mutex mutex;

    static A *getInstance()
    {
        A *result = instance;

        if (result == nullptr)
        {
            std::lock_guard<std::mutex> lock(mutex);
            result = instance;
            if (result == nullptr)
                instance = result = new A();
        }
        return result;
    }

    void Unlock()
    {
        instance = nullptr;
    }
};

/**
 * @class AGuard
 * @brief A guard class that manages the locking and unlocking of a mutex associated with an object of type A.
 *
 * This class ensures that the mutex is properly locked and unlocked, providing exception safety and RAII-style management.
 *
 * @note The class assumes that the object of type A has a public member `mutex` of type `std::mutex`.
 *
 * @private
 * @var std::unique_lock<std::mutex> lock_
 * A unique lock that manages the locking and unlocking of the mutex.
 *
 * @private
 * @var bool locked_
 * A flag indicating whether the mutex is currently locked.
 *
 * @public
 * @fn explicit AGuard(A &obj)
 * @brief Constructs the guard and defers locking the mutex.
 * @param obj The object whose mutex will be managed by the guard.
 *
 * @public
 * @fn ~AGuard()
 * @brief Destructor that unlocks the mutex if it is locked.
 *
 * @public
 * @fn AGuard &operator=(A &obj)
 * @brief Locks the mutex and sets the locked flag.
 * @param obj The object whose mutex will be locked.
 * @return A reference to the current guard object.
 *
 * @public
 * @fn A &operator*() const
 * @brief Dereferences the object managed by the guard.
 * @return A reference to the object.
 *
 * @public
 * @fn A *operator->() const
 * @brief Provides pointer-like access to the object managed by the guard.
 * @return A pointer to the object.
 *
 * @private
 * @var A *obj
 * A pointer to the object whose mutex is managed by the guard.
 */
class AGuard
{
private:
    std::unique_lock<std::mutex> lock_;
    bool locked_ = false;

public:
    explicit AGuard(A &obj) : lock_(obj.mutex, std::defer_lock) {}

    ~AGuard()
    {
        if (locked_)
        {
            (*obj).Unlock();
        }
    }

    AGuard &operator=(A &obj)
    {
        lock_.lock();
        locked_ = true;
        return *this;
    }

    A &operator*() const { return *obj; }
    A *operator->() const { return &*obj; }

private:
    A *obj = nullptr;
};