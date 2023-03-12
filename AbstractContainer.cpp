#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class AbstractContainer {
public:
    virtual T getSize() const = 0;
    virtual bool isEmpty() const = 0;
};

template <typename T>
class AbstractStack : public AbstractContainer<T> {
public:
    virtual void Push(const int T) = 0;
    virtual void Pop() = 0;
    virtual T Top() const = 0;
};

template <typename T>
class LimitedArrayStack : public AbstractStack<T> {
public:
    LimitedArrayStack() : array_(nullptr), size_(0), limit_size_(10) { }

    LimitedArrayStack(int limit) : array_(new T[limit]), limit_size_(limit), size_(0) { }

    ~LimitedArrayStack() {
        delete[] array_;
    }

    LimitedArrayStack(const LimitedArrayStack& other) : limit_size_(other.limit_size_), size_(other.size_) {
        array_ = new T[other.size_];
        for (int i = 0; i < size_; ++i) {
            array_[i] = other.array_[i];
        }
    }

    LimitedArrayStack(LimitedArrayStack&& other) {
        array_ = other.array_;
        size_ = other.size_;
        limit_size_ = other.limit_size_;
        other.array_ = nullptr;
        other.size_ = 0;
        other.limit_size_ = 0;
    }

    void Print() {
        if (!isEmpty()) {
            cout << "In Print(): " << array_[size_ - 1] << endl;
        }
        else {
            throw runtime_error("Out of range");
        }
    }

    LimitedArrayStack& operator= (const LimitedArrayStack& other) {
        if (this != &other) {
            delete[] array_;
            array_ = new T[other.limit_size_];
            limit_size_ = other.limit_size_;
            size_ = other.size_;

            for (int i = 0; i < other.size_; ++i) {
                array_[i] = other.array_[i];
            }
        }
        return *this;
    }

    LimitedArrayStack& operator= (LimitedArrayStack&& other) {
        if (this != &other) {
            delete[] array_;
            array_ = other.array_;
            size_ = other.size_;
            limit_size_ = other.limit_size_;
            other.array_ = nullptr;
            other.size_ = 0;
            other.limit_size_ = 0;
        }
        return *this;
    }

    int getSize() const override {
        return size_;
    }

    bool isEmpty() const override {
        return (size_ == 0);
    }

    void Push(T value) override {
        if (limit_size_ == size_) {
            throw runtime_error("Out of range");
        }

        T* result_ = new T[size_ + 1];

        for (int i = 0; i < size_; ++i) {
            result_[i] = array_[i];
        }

        delete[] array_;
        array_ = result_;
        ++size_;
        array_[size_ - 1] = value;
    }


    void Pop() override {
        if (isEmpty()) {
            throw runtime_error("Out of range");
        }

        T temp = array_[size_ - 1];
        --size_;
    }

    T Top() const override {
        if (isEmpty()) {
            throw runtime_error("Out of range");
        }

        return array_[size_ - 1];
    }

private:
    T* array_;
    int size_;
    int limit_size_;
};

template <typename T>
class UnlimitedArrayStack : public AbstractStack<T> {
public:
    UnlimitedArrayStack() : array_(nullptr), size_(0) { }
    UnlimitedArrayStack(int size) : array_(T [size]), size_(size) { }

    ~UnlimitedArrayStack() {
        delete[] array_;
    }

    UnlimitedArrayStack(const UnlimitedArrayStack& other) {
        array_ = new T[other.size_];
        size_ = other.size_;
        for (int i = 0; i < size_; ++i) {
            array_[i] = other.array_[i];
        }
    }

    UnlimitedArrayStack(UnlimitedArrayStack&& other) {
        array_ = other.array_;
        size_ = other.size_;
        other.array_ = nullptr;
        other.size_ = 0;
    }

    void Push(T value) override {
        T* result_ = new T[size_ + 1];

        for (int i = 0; i < size_; ++i) {
            result_[i] = array_[i];
        }

        delete[] array_;
        array_ = result_;
        ++size_;
        array_[size_ - 1] = value;
    }


    int getSize() const override {
        return size_;
    }

    bool isEmpty() const override {
        return (size_ == 0);
    }


    T Top() const override {
        if (isEmpty()) {
            throw runtime_error("Out of range");
        }

        return array_[size_ - 1];
    }

    UnlimitedArrayStack& operator= (const UnlimitedArrayStack& other) {
        if (this != &other) {
            delete[] array_;
            array_ = new T[other.size_];
            size_ = other.size_;

            for (int i = 0; i < other.size_; ++i) {
                array_[i] = other.array_[i];
            }
        }
        return *this;
    }

    UnlimitedArrayStack& operator= (UnlimitedArrayStack&& other) {
        if (this != &other) {
            delete[] array_;
            array_ = other.array_;
            size_ = other.size_;
            other.array_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

private:
    T* array_;
    int size_;
};

template <typename T>
struct Node {
public:
    T data_;
    Node* next_;
    Node(T value) : data_(value), next_(nullptr) {}
};

template <typename T>
class ListStack : public AbstractStack<T> {
public:
    ListStack() : top_(nullptr), size_(0) {}

    ~ListStack() {
        while (!isEmpty()) {
            Pop();
        }
    }

    ListStack (ListStack &&other) {
        top_ = other.top_;
        other.top_ = nullptr;
    }

    int getSize() const override {
        return size_;
    }

    bool isEmpty() const override {
        return size_ == 0;
    }

    void Push(T value) override {
        if (isEmpty()) {
            Node* temp = new Node(value);
            top_ = temp;
            return;
        }
        Node* new_top_ = new Node(value);
        new_top_->data_ = value;
        new_top_->next_ = top_;
        top_ = new_top_;
        ++size_;
    }

    void Pop() override {
        if (isEmpty()) {
            throw runtime_error("Out of range");
        }
        Node* pop = top_;
        top_ = top_->next_;
        delete pop;
    }

    T Top() const override {
        if (isEmpty()) {
            throw runtime_error("Out of range");
        }
        return top_->data_;
    }

private:
    Node<T>* top_;
    int size_;
};

template <typename T>
class AbstractQueue : public AbstractContainer<T> {
public:
    virtual void PushBack(T value) = 0;
    virtual void PopFront() = 0;
    virtual T Front() const = 0;
};

template <typename T>
class LimitedArrayQueue : public AbstractQueue<T> {
public:
    LimitedArrayQueue() : array_(nullptr), size_(0), limit_size_(10) {}

    LimitedArrayQueue(int limit) : array_(new T[limit]), limit_size_(limit), size_(0) {}

    LimitedArrayQueue(const LimitedArrayQueue& other) {
        size_ = other.size_;
        limit_size_ = other.size_;
        array_ = new int[size_];
        for (int i = 0; i < size_; i++) {
            array_[i] = other.array_[i];
        }
    }

    LimitedArrayQueue(LimitedArrayQueue&& other) {
        size_ = other.size_;
        limit_size_ = other.limit_size_;
        delete[] array_;
        array_ = other.array_;
        other.array_ = nullptr;
        other.size_ = 0;
        other.limit_size_ = 0;
    }

    ~LimitedArrayQueue() {
        delete[] array_;
    }

    LimitedArrayQueue& operator=(const LimitedArrayQueue& other) {
        if (&other == this) {
            return *this;
        }

        size_ = other.size_;
        limit_size_ = other.limit_size_;
        delete array_;
        array_ = new int[size_];
        for (int i = 0; i < size_; ++i) {
            array_[i] = other.array_[i];
        }

        return *this;
    }

    LimitedArrayQueue& operator=(LimitedArrayQueue&& other) {
        if (this == &other) {
            return *this;
        }

        delete array_;
        size_ = other.size_;
        limit_size_ = other.limit_size_;
        array_ = other.array_;

        other.array_ = nullptr;
        other.size_ = 0;
        other.limit_size_ = 0;

        return *this;
    }

    void PushBack(T value) override {
        if (limit_size_ == size_) {
            throw runtime_error("Out of range");
        }

        T* result_ = new T[size_ + 1];

        for (int i = 0; i < size_; ++i) {
            result_[i] = result_[i];
        }

        delete array_;
        array_ = result_;
        array_[size_++] = value;
    }

    T Front() const override {
        if (isEmpty()) {
            throw runtime_error("Out of range");
        }

        return array_[0];
    }

    bool isEmpty() const override {
        return (size_ == 0);
    }

    bool isFull() const {
        return size_ == limit_size_;
    }

    int getSize() const override {
        return size_;
    }

private:
    T* array_;
    int limit_size_;
    int size_;

};

int main() {
    return 0;
}